#include <vector>
#include "gtest/gtest.h"
#include "kernels/Nonlinear_Reservoir.hpp"
#include <memory>

class NonlinearReservoirKernelTest : public ::testing::Test {

    protected:

    //Nonlinear_Reservoir NoOutletReservoir;

/*
    std::vector<hymod_params> params_examples;

    std::vector<std::shared_ptr<double>> storage_res_ptr_examples;
    std::vector<hymod_state> h_state_examples;

    std::vector<hymod_fluxes> ks_fluxes_examples;

    std::vector<std::shared_ptr<double>> new_storage_res_ptr_examples;
    std::vector<hymod_state> new_state_examples;

    std::vector<hymod_fluxes> new_fluxes_examples;

    std::vector<double> input_flux_examples;

    std::vector<std::shared_ptr<double>> et_params_db_examples;
*/

/*
    HymodKernelTest() {

    }

    ~HymodKernelTest() override {

    }
*/

    //Nonlinear_Reservoir NoOutletReservoir;

    void SetUp() override;

    void TearDown() override;

    //void setupArbitraryExampleCase();

    void setupNoOutletNonlinearReservoir();

    void setupOneOutletNonlinearReservoir();

    void setupMultipleOutletNonlinearReservoir();

    void setupVectorOfOutlets();

    std::shared_ptr<Nonlinear_Reservoir> NoOutletReservoir; //pointer to a Nonlinear_Reservoir
    //c++ smart ptrs

    std::shared_ptr<Nonlinear_Reservoir> OneOutletReservoir; //pointer to a Nonlinear_Reservoir

    std::shared_ptr<Nonlinear_Reservoir> MultipleOutletReservoir; //pointer to a Nonlinear_Reservoir

    std::shared_ptr<Reservoir_Outlet> ReservoirOutlet1;

    std::shared_ptr<Reservoir_Outlet> ReservoirOutlet2;

    std::shared_ptr<Reservoir_Outlet> ReservoirOutlet3;

    //std::vector<std::shared_ptr<Reservoir_Outlet>> ReservoirOutletsVector;

    std::vector<Reservoir_Outlet*> ReservoirOutletsVector;

    //std::vector<Reservoir_Outlet *> ReservoirOutletsVector;

};

void NonlinearReservoirKernelTest::SetUp() {
    
    setupNoOutletNonlinearReservoir();

    setupOneOutletNonlinearReservoir();

    setupVectorOfOutlets();

    setupMultipleOutletNonlinearReservoir();


    
//setupArbitraryExampleCase();
    //noutlet
 //1 outlet
//multiple outlet 

}

//LEAVE EMPTY FOR NOW
void NonlinearReservoirKernelTest::TearDown() {

}


void NonlinearReservoirKernelTest::setupNoOutletNonlinearReservoir()
{
    NoOutletReservoir = std::make_shared<Nonlinear_Reservoir>(0.0, 0.0, 0.0); //make a shared ptr using the constructor


}


void NonlinearReservoirKernelTest::setupOneOutletNonlinearReservoir()
{
    OneOutletReservoir = std::make_shared<Nonlinear_Reservoir>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    //Nonlinear_Reservoir OneOutletReservoir(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

}


void NonlinearReservoirKernelTest::setupMultipleOutletNonlinearReservoir()
{

    ReservoirOutlet1 = std::make_shared<Reservoir_Outlet>(0.0, 0.0, 0.0);

    //ReservoirOutlet1 = Reservoir_Outlet(0.0, 0.0, 0.0);

    ReservoirOutlet2 = std::make_shared<Reservoir_Outlet>(0.0, 0.0, 0.0);

    ReservoirOutlet3 = std::make_shared<Reservoir_Outlet>(0.0, 0.0, 0.0);



    //std::vector<Reservoir_Outlet> ReservoirOutletsVector;

    //&ReservoirOutletsVector.push_back(ReservoirOutlet1);

    ReservoirOutletsVector.push_back(ReservoirOutlet1);

    //ReservoirOutletsVector.push_back(ReservoirOutlet2);

    //ReservoirOutletsVector.push_back(ReservoirOutlet3);




    //Nonlinear_Reservoir OneOutletReservoir(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    //MultipleOutletReservoir = std::make_shared<Nonlinear_Reservoir>(0.0, 0.0, 0.0, ReservoirOutletsVector);

}


void NonlinearReservoirKernelTest::setupVectorOfOutlets()
{
    //Nonlinear_Reservoir OneOutletReservoir(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    //std::shared_ptr<Reservoir_Outlet> ReservoirOutlet;

/*
    ReservoirOutlet1 = std::make_shared<Reservoir_Outlet>(0.0, 0.0, 0.0);

    ReservoirOutlet2 = std::make_shared<Reservoir_Outlet>(0.0, 0.0, 0.0);

    ReservoirOutlet3 = std::make_shared<Reservoir_Outlet>(0.0, 0.0, 0.0);

    ReservoirOutletsVector.push_back(ReservoirOutlet1);

    ReservoirOutletsVector.push_back(ReservoirOutlet2);

    ReservoirOutletsVector.push_back(ReservoirOutlet3);
*/

//ReservoirOutletsVector = std::make_shared

//    std::vector<std::shared_ptr<Reservoir_Outlet>> ReservoirOutletsVector;

}





//! Setup an arbitrary example case with essentially made-up values for the components, and place the components in the
/*!
 *  Setup an arbitrary example case with essentially made-up values for the components, and place the components in the
 *  appropriate member collections.
 */
/*
void HymodKernelTest::setupArbitraryExampleCase() {

    struct hymod_params params = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    params_examples.push_back(params);

    std::shared_ptr<double> storage_res_ptr = std::make_shared<double>(1.0);
    storage_res_ptr_examples.push_back(storage_res_ptr);
    struct hymod_state h_state = {1.0, storage_res_ptr.get()};
    h_state_examples.push_back(h_state);

    struct hymod_fluxes ks_fluxes = {1.0, 1.0, 1.0, 1.0};
    ks_fluxes_examples.push_back(ks_fluxes);

    std::shared_ptr<double> new_storage_res_ptr = std::make_shared<double>(2.0);
    new_storage_res_ptr_examples.push_back(new_storage_res_ptr);
    struct hymod_state new_state = {2.0, new_storage_res_ptr.get()};
    new_state_examples.push_back(new_state);

    struct hymod_fluxes new_fluxes = {2.0, 2.0, 2.0, 2.0};
    new_fluxes_examples.push_back(new_fluxes);

    double input_flux = 2.0;
    input_flux_examples.push_back(input_flux);

    std::shared_ptr<double> et_params_db = std::make_shared<double>(3.0);
    et_params_db_examples.push_back(et_params_db);
}
*/



TEST_F(NonlinearReservoirKernelTest, TestRunNoOutletReservoir) 
{
    cout << "Hi David";
    //cout << NonlinearReservoirKernelTest::NoOutletReservoir.state.current_storage_height_meters;
    //cout << Nonlinear_Reservoir::current_storage_height_meters
    

    //NonlinearReservoirKernelTest::NoOutletReservoir.get_storage_meters();

    cout << NoOutletReservoir->get_storage_meters();


    //cout << ReservoirOutletsVector;

    ASSERT_TRUE(true);
}

/*
//! Test that Hymod executes its 'run' function fully when passed arbitrary valid arguments.
TEST_F(HymodKernelTest, TestRun0) {

    int test_case_index = 0;

    void* et_param = et_params_db_examples[0].get();

    //hymod_kernel::run(params, h_state, ks_fluxes, new_state, new_fluxes, input_flux, et_params);
    hymod_kernel::run(params_examples[test_case_index],
            h_state_examples[test_case_index],
            ks_fluxes_examples[test_case_index],
            new_state_examples[test_case_index],
            new_fluxes_examples[test_case_index],
            input_flux_examples[test_case_index],
            et_param);
    ASSERT_TRUE(true);    //JUST ENSURES FINSISHED. LOOK AT GOOGLE TEST DOC. ASSERT EQUAL TO A VALUE. TEST OBJECT EXIST
}
*/

//! Test that Hymod executes its 'calc_et' function and returns the expected result.
/*!
    In the current implementation (at the time this test was created), the static method simple returns 0.0 regardless
    of the parameters.
*/

/*
TEST_F(HymodKernelTest, TestCalcET0) {
    // Since currently the function doesn't care about params, borrow this from example 0 ...
    void* et_param = et_params_db_examples[0].get();

    ASSERT_EQ(hymod_kernel::calc_et(3.0, et_param), 0.0);
}
*/

