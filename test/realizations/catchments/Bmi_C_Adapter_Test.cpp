#include "gtest/gtest.h"
#include <vector>
#include <exception>
#include "FileChecker.h"
#include "Bmi_C_Adapter.hpp"

using namespace models::bmi;

class Bmi_C_Adapter_Test : public ::testing::Test {
protected:

    void SetUp() override;

    void TearDown() override;

    std::string config_file_name_0;
    std::vector<std::string> expected_output_var_names = {
            "SCHAAKE_OUTPUT_RUNOFF",
            "GIUH_RUNOFF",
            "NASH_LATERAL_RUNOFF",
            "DEEP_GW_TO_CHANNEL_FLUX",
            "Q_OUT"
    };
};

void Bmi_C_Adapter_Test::SetUp() {
    std::vector<std::string> config_path_options = {
            "test/data/bmi/c/cfe/",
            "./test/data/bmi/c/cfe/",
            "../test/data/bmi/c/cfe/",
            "../../test/data/bmi/c/cfe/",
    };

    std::string config_basename_0 = "cat_87_bmi_config.txt";

    // Build vector of names by building combinations of the path and basename options
    std::vector<std::string> config_file_names_0(config_path_options.size());

    // Build so that all path names are tried for given basename before trying a different basename option
    for (auto & path_option : config_path_options) {
        std::string string_combo = path_option + config_basename_0;
        config_file_names_0.push_back(string_combo);
    }

    // Then go through in order and find the fist existing combination
    config_file_name_0 = utils::FileChecker::find_first_readable(config_file_names_0);
}

void Bmi_C_Adapter_Test::TearDown() {

}

/** Simple test to make sure the model initializes. */
TEST_F(Bmi_C_Adapter_Test, Initialize_0_a) {
    Bmi_C_Adapter adapter(config_file_name_0, utils::StreamHandler());
    adapter.Initialize();
    adapter.Finalize();
}

/** Test output variables can be retrieved. */
TEST_F(Bmi_C_Adapter_Test, GetOutputVarNames_0_a) {
    Bmi_C_Adapter adapter(config_file_name_0, utils::StreamHandler());
    try {
        ASSERT_EQ(adapter.GetOutputVarNames(), expected_output_var_names);
    }
    catch (std::exception& e) {
        printf("Exception getting output var names: %s", e.what());
    }
}

/** Test output variables item count can be retrieved. */
TEST_F(Bmi_C_Adapter_Test, GetOutputItemCount_0_a) {
    Bmi_C_Adapter adapter(config_file_name_0, utils::StreamHandler());
    try {
        ASSERT_EQ(adapter.GetOutputItemCount(), expected_output_var_names.size());
    }
    catch (std::exception& e) {
        printf("Exception getting output var count: %s", e.what());
    }
}

/** Test that the update function works. */
TEST_F(Bmi_C_Adapter_Test, Update_0_a) {
    Bmi_C_Adapter adapter(config_file_name_0, utils::StreamHandler());
    adapter.Initialize();
    adapter.Update();
    adapter.Finalize();
}

/** Test that the update function works for the 720 time steps. */
TEST_F(Bmi_C_Adapter_Test, Update_0_b) {
    Bmi_C_Adapter adapter(config_file_name_0, utils::StreamHandler());
    adapter.Initialize();
    for (int i = 0; i < 720; ++i)
        adapter.Update();

    adapter.Finalize();
}

/** Test that the update function works for the 720 time steps and gets the expected outputs. */
TEST_F(Bmi_C_Adapter_Test, Update_0_c) {
    Bmi_C_Adapter adapter(config_file_name_0, utils::StreamHandler());
    adapter.Initialize();
    for (int i = 0; i < 720; ++i)
        adapter.Update();
    std::vector<double> q_out_vals = adapter.GetValue<double>("Q_OUT");
    // TODO: actually assert these values are correct
    adapter.Finalize();
}

/** Test that the update function works for the 720 time steps and gets the expected Schaake runoff. */
TEST_F(Bmi_C_Adapter_Test, Update_0_d) {
    Bmi_C_Adapter adapter(config_file_name_0, utils::StreamHandler());
    adapter.Initialize();
    for (int i = 0; i < 720; ++i)
        adapter.Update();
    std::vector<double> q_out_vals = adapter.GetValue<double>("SCHAAKE_OUTPUT_RUNOFF");
    // TODO: actually assert these values are correct
    adapter.Finalize();
}

/** Test that the update function works for the 720 time steps and gets the expected GIUH runoff. */
TEST_F(Bmi_C_Adapter_Test, Update_0_e) {
    Bmi_C_Adapter adapter(config_file_name_0, utils::StreamHandler());
    adapter.Initialize();
    for (int i = 0; i < 720; ++i)
        adapter.Update();
    std::vector<double> q_out_vals = adapter.GetValue<double>("GIUH_RUNOFF");
    // TODO: actually assert these values are correct
    adapter.Finalize();
}

/** Test that the update function works for the 720 time steps and gets the expected Nash lateral flow runoff. */
TEST_F(Bmi_C_Adapter_Test, Update_0_f) {
    Bmi_C_Adapter adapter(config_file_name_0, utils::StreamHandler());
    adapter.Initialize();
    for (int i = 0; i < 720; ++i)
        adapter.Update();
    std::vector<double> q_out_vals = adapter.GetValue<double>("NASH_LATERAL_RUNOFF");
    // TODO: actually assert these values are correct
    adapter.Finalize();
}

/** Test that the update function works for the 720 time steps and gets the expected deep groundwater to channel flux. */
TEST_F(Bmi_C_Adapter_Test, Update_0_g) {
    Bmi_C_Adapter adapter(config_file_name_0, utils::StreamHandler());
    adapter.Initialize();
    for (int i = 0; i < 720; ++i)
        adapter.Update();
    std::vector<double> q_out_vals = adapter.GetValue<double>("DEEP_GW_TO_CHANNEL_FLUX");
    // TODO: actually assert these values are correct
    adapter.Finalize();
}