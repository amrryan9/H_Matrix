#include"Environment.h"

double  Environment::CarrierFrequency = 2.8e9;
//double  Environment::NoisePower = 4.1419e-13;
//double  Environment::Temperature = 298.15;
double  Environment::Samples_Count = 0;
float   Environment::Test_Case = 0;
float   Environment::Spacing = 0;
float   Environment::Phi_array = 0;
double	Environment::Transmitter_power = 1;
float	Environment::Transmitter_height = 120.0;
string  Environment::Test_Case_str = "";
string  Environment::RESULTSFolder = "D:/RESULTS_5/";
std::filesystem::path Environment::Cir_Folder = std::filesystem::current_path();
std::filesystem::path Environment::StudyArea_Folder = std::filesystem::current_path();
Float_matrix Environment::data_file = Float_matrix();

