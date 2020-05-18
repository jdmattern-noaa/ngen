#include <iostream>
#include <string>
#include <unordered_map>

#include <FeatureBuilder.hpp>
#include <FeatureVisitor.hpp>

#include <HY_HydroNexus.hpp>
#include <HY_Catchment.hpp>
#include <Simple_Lumped_Model_Realization.hpp>
#include <HY_PointHydroNexus.hpp>

#include "NGenConfig.h"

std::string catchmentRealizationFile = "/Users/nels.frazier/workspace/ngen/data/sugar_creek/catchment_data_subset.geojson";
std::string nexusRealizationFile = "/Users/nels.frazier/workspace/ngen/data/sugar_creek/nexus_data_subset.geojson";

//TODO this is possible, but ASSUMES realizations based on feature geom type, so not quite ready for prime time
class RealizaitonVisitor : public geojson::FeatureVisitor {

};

void prepare_features(geojson::GeoJSON& nexus, geojson::GeoJSON& catchments, bool validate=false)
{
  for(auto& feature: *nexus){
    feature->set_id(feature->get_property("ID").as_string());
    //std::cout << "Got Nexus Feature " << feature->get_id() << std::endl;
  }
  nexus->update_ids();
  //Now read the collection of catchments, iterate it and add them to the nexus collection
  //also link them by to->id
  //std::cout << "Iterating Catchment Features" << std::endl;
  for(auto& feature: *catchments){
    feature->set_id(feature->get_property("ID").as_string());
    nexus->add_feature(feature);
    //std::cout<<"Catchment "<<feature->get_id()<<" -> Nexus "<<feature->get_property("toID").as_string()<<std::endl;
  }
  std::string linkage = "toID";
  nexus->link_features_from_property(nullptr, &linkage);

  if(validate){
    //Convience check on linkage
    for(auto& feature: *nexus){
      //feature->set_id(feature->get_property("ID").as_string());
      //std::cout << "Got Nexus Feature " << feature->get_id() << std::endl;
      if( feature->get_id().substr(0, 3) == "cat") {
        auto downstream = feature->downstream_features();
        if(downstream.size() > 1) {
          std::cerr << "catchment " << feature->get_id() << " has more than one downstream connection" << std::endl;
        }
        else if(downstream.size() == 0) {
            std::cerr << "catchment " << feature->get_id() << " has NO downstream connection" << std::endl;
        }
        else {
          std::cout <<"catchment feature " << feature->get_id() << " to nexus feature " << downstream[0]->get_id() << std::endl;
        }
       }
     }//end for(feature: nexus)
   }//end if(validate)
}


std::unordered_map<std::string, std::shared_ptr<HY_CatchmentRealization>>  catchment_realizations;
std::unordered_map<std::string, std::shared_ptr<HY_HydroNexus>> nexus_realizations;
std::unordered_map<std::string, std::string> catchment_to_nexus;
std::unordered_map<std::string, std::string> nexus_to_catchment;
//TODO move catchment int identity to relization, and update nexus to use string id
std::unordered_map<std::string, int> catchment_id;

// create the struct used for ET
pdm03_struct pdm_et_data;

typedef Simple_Lumped_Model_Realization _hymod;

int main(int argc, char *argv[]) {
    std::cout << "Hello there " << ngen_VERSION_MAJOR << "."
              << ngen_VERSION_MINOR << "."
              << ngen_VERSION_PATCH << std::endl;

    //Read the collection of nexus
    std::cout << "Building Nexus collection" << std::endl;
    geojson::GeoJSON nexus_collection = geojson::read(nexusRealizationFile);
    std::cout << "Iterating Nexus Features" << std::endl;


    std::cout << "Building Catchment collection" << std::endl;
    geojson::GeoJSON catchment_collection = geojson::read(catchmentRealizationFile);

    prepare_features(nexus_collection, catchment_collection, true);

    //TODO don't really need catchment_collection once catchments are added to nexus collection
    catchment_collection.reset();

    pdm_et_data.B = 1.3;
    pdm_et_data.Kv = 0.99;
    pdm_et_data.modelDay = 0.0;
    pdm_et_data.Huz = 400.0;
    pdm_et_data.Cpar = pdm_et_data.Huz / (1.0+pdm_et_data.B);

    double storage = 1.0;
    double max_storage = 1000.0;
    double a = 1.0;
    double b = 10.0;
    double Ks = 0.1;
    double Kq = 0.01;
    long n = 3;
    double t = 0;
    std::vector<double> sr_tmp = {1.0, 1.0, 1.0};
    for(auto& feature : *nexus_collection)
    {
      if( feature->get_id().substr(0, 3) == "cat" ){
        //Create catchment realization, add to map
        catchment_realizations[feature->get_id()] = std::make_shared<_hymod>( _hymod(storage, max_storage, a, b, Ks, Kq, n, sr_tmp, t) );
        if(feature->get_number_of_downstream_features() == 1)
        {
          catchment_to_nexus[feature->get_id()] = feature->downstream_features()[0]->get_id();
        }
        else
        {
          //TODO
        }
        catchment_id[feature->get_id()] = std::stoi(feature->get_id().substr(4));
      }else{
        //Create nexus realization, add to map
        int num = std::stoi( feature->get_id().substr(4) );
        nexus_realizations[feature->get_id()] = std::make_shared<HY_PointHydroNexus>(
                                      HY_PointHydroNexus(num, feature->get_id(),
                                                         feature->get_number_of_downstream_features()));
       if(feature->get_number_of_downstream_features() == 1)
       {
         nexus_to_catchment[feature->get_id()] = feature->downstream_features()[0]->get_id();
       }
       else
       {
         //TODO
       }
      }

    }

    //Now loop some time, iterate catchments, do stuff
    for(int time_step = 0; time_step < 5; time_step++)
    {
      for(auto &catchment: catchment_realizations)
      {
        double response = catchment.second->get_response(0, 0, &pdm_et_data);
        nexus_realizations[ catchment_to_nexus[catchment.first] ]->add_upstream_flow(response, catchment_id[catchment.first], time_step);
        std::cout<<"Reporting water for time_step "<<time_step<<std::endl<<\
                   "Nexus "<<catchment_to_nexus[catchment.first]<<" has "<<\
                   response<<" meters of water ready to route downstream."<<std::endl;
      }
    }
    /*
        The basic driving algorithm looks something like this:

        Iteration 1: Only read catchments and nexus
        Read configuration;
        From configuration, read inputs
        inputs: id, realization enum, input file (geojson), forcing provider (enum)

        loop:
          id -> read geojson -> lookup by id -> construct catchment realization and nexus
        TODO catchment realizations will need to construct forcing objects (implement forcing provider interface) upon constructuion
        One INDEPDENT timestep
        run catchment A -> forcing.get(time, dt, <grid?> ) -> run_model(time, dt, forcing)
        run catchment B

        Iteration 2: Read waterbodies, build linkage between nexus/waterbody, apply routing, multiple timesteps

    */
}
