#include "Tools.h"
double  Tools::CarrierFrequency=2.8e9;
double  Tools::NoisePower = 4.1419e-13;
double  Tools::Temperature =298.15;
double  Tools::Samples_Count = 0;
float   Tools::Test_Case = 0;
float   Tools::Spacing = 0;
float   Tools::Phi_array = 0;
double	Tools::Transmitter_power = 1;
float	Tools::Transmitter_height= 120.0;
string  Tools::Test_Case_str ="";
string  Tools::RESULTSFolder= "D:/RESULTS_5/";
version Tools::WirelessInsiteVersion= version::v3_0_01;
version Tools::WirelessInsiteVersion_DOD = version::v3_0_01;
std::filesystem::path Tools::Cir_Folder= std::filesystem::current_path();
std::filesystem::path Tools::StudyArea_Folder = std::filesystem::current_path();
Float_matrix Tools::data_file = Float_matrix();