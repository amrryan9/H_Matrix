#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<array>
#include <filesystem>					
#include <sstream>
#include <matrix.h>
using namespace std;
// This class creates the terminals position destribution and simulation environment 
enum class configuration { MIMO, SISO };
enum EXPOSURE { ALL, NLOS, LOS, NON };
constexpr auto FULL = unsigned(1);;


struct Terminal
{
	float Distance;						// Universal Distance from origin (Polar Cordinate)
	float Height;						// Height from BS
	float Phi;							// Universal Azimuth angle(Polar Cordinate)
	float Theta;						// Universal Elevation angle (Polar Cordinate)
	float R;							// Universal Radial Distance from Origin
	float X;							// Universal x cordinate
	float Y;							// Universal y cordinate
	float Z;							// Universal z cordinate
	float DirectDistance;				// Relative Distance from Tx 
	float AzimuthAngle;					// Relative Azimuth angle from Tx
	float ElevationAngle;				// Relative  Elevation angle to Tx , as seen from the terminal
	float RadialDistance;				// Relative  Radial Distance from Tx
	Terminal(float d, float h, float phi, float theta, float r)
	{
		Distance = d;					// Distance from BS
		Height = h;						// Height from BS
		Phi = phi;						// Azimuth from BS
		Theta = theta;					// Elevation from BS
		R = r;
		X = 0;							// Universal x cordinate
		Y = 0;							// Universal y cordinate
		Z = 0;							// Universal z cordinate
		DirectDistance = 0;				// Relative Distance from Tx 
		AzimuthAngle = 0;				// Relative Azimuth angle from Tx
		ElevationAngle = 0;				// Relative  Elevation angle to Tx , as seen from the terminal
		RadialDistance = 0;				// Relative  Radial Distance from Tx
	}
	Terminal(float d, float h, float phi, float theta, float r, float dd, float az, float el, float rd)
	{
		Distance = d;					// Distance from BS
		Height = h;						// Height from BS
		Phi = phi;						// Azimuth from BS
		Theta = theta;					// Elevation from BS
		R = r;
		X = 0;							// Universal x cordinate
		Y = 0;							// Universal y cordinate
		Z = 0;							// Universal z cordinate
		DirectDistance = dd;			// Relative Distance from Tx 
		AzimuthAngle = az;				// Relative Azimuth angle from Tx
		ElevationAngle = el;			// Relative  Elevation angle to Tx , as seen from the terminal
		RadialDistance = rd;			// Relative  Radial Distance from Tx
	}
	Terminal(float d, float h, float phi, float theta, float r,float x, float y, float z, float dd, float az, float el, float rd)
	{
		Distance = d;					// Distance from BS
		Height = h;						// Height from BS
		Phi = phi;						// Azimuth from BS
		Theta = theta;					// Elevation from BS
		R = r;
		X = x;							// Universal x cordinate
		Y = y;							// Universal y cordinate
		Z = z;							// Universal z cordinate
		DirectDistance = dd;			// Relative Distance from Tx 
		AzimuthAngle = az;				// Relative Azimuth angle from Tx
		ElevationAngle = el;			// Relative  Elevation angle to Tx , as seen from the terminal
		RadialDistance = rd;			// Relative  Radial Distance from Tx
	}
	void Show()
	{
		cout << "********************** UNIVERSAL ********************************" << endl;
		cout << setw(12) << "Distance(m)" << setw(12) << "Height(m)" << setw(12) << "Phi(rad)" << setw(12) << "Theta(rad)" << setw(12) << "R(m)" << endl;
		cout << "_________________________________________________________________" << endl;
		cout << setw(12) << Distance << setw(12) << Height << setw(12) << Phi << setw(12) << Theta << setw(12) << R << endl;
	}
};
class Environment
{
public:
	Environment() {
		TerminalPositionsFile = "";
	}
	static std::vector<Terminal> GetPositionDataSetFromFile(std::string file_in_teminals_positions,unsigned version=FULL)
	{
		if (file_in_teminals_positions == "")
		{
			cout << " Terninals Positions File has not been set !!" << endl;
			return std::vector<Terminal>();
		}
		std::stringstream converter;
		std::vector<Terminal> Terminal_data_set;
		std::ifstream in_Terminals_positions{ file_in_teminals_positions };
		if (!in_Terminals_positions)
		{
			std::cerr << " Terminals_Positions file is not open." << std::endl;
			exit(1);
		}
		std::vector<string> Terminals_positions_file{ std::istream_iterator<string>(in_Terminals_positions),std::istream_iterator<string>() };
		size_t i_Terminals_positions = 0;
		float Distance;
		float Height;
		float Phi;
		float Theta;
		float R;
		float X;							
		float Y;							
		float Z;							
		float DirectDistance;				 
		float AzimuthAngle;					
		float ElevationAngle;				
		float RadialDistance;
		for (auto xx : Terminals_positions_file)
		{
			if (version == FULL)
			{
				if (i_Terminals_positions % 12 == 0)       { converter << static_cast<std::string>(xx); converter >> Distance;			converter.clear(); }
				else if (i_Terminals_positions % 12 == 1)  { converter << static_cast<std::string>(xx); converter >> Height;			converter.clear(); }
				else if (i_Terminals_positions % 12 == 2)  { converter << static_cast<std::string>(xx); converter >> Phi;				converter.clear(); }
				else if (i_Terminals_positions % 12 == 3)  { converter << static_cast<std::string>(xx); converter >> Theta;				converter.clear(); }
				else if (i_Terminals_positions % 12 == 4)  { converter << static_cast<std::string>(xx); converter >> R;					converter.clear(); }
				else if (i_Terminals_positions % 12 == 5)  { converter << static_cast<std::string>(xx); converter >> X;					converter.clear(); }
				else if (i_Terminals_positions % 12 == 6)  { converter << static_cast<std::string>(xx); converter >> Y;					converter.clear(); }
				else if (i_Terminals_positions % 12 == 7)  { converter << static_cast<std::string>(xx); converter >> Z;					converter.clear(); }
				else if (i_Terminals_positions % 12 == 8)  { converter << static_cast<std::string>(xx); converter >> DirectDistance;	converter.clear(); }
				else if (i_Terminals_positions % 12 == 9)  { converter << static_cast<std::string>(xx); converter >> AzimuthAngle;		converter.clear(); }
				else if (i_Terminals_positions % 12 == 10) { converter << static_cast<std::string>(xx); converter >> ElevationAngle;	converter.clear(); }
				else if (i_Terminals_positions % 12 == 11) { converter << static_cast<std::string>(xx); converter >> RadialDistance;	converter.clear(); }
				i_Terminals_positions++;

				// Adding to the terminals data set //////////////////////////////////
				if (i_Terminals_positions > 0 && i_Terminals_positions % 12 == 0)Terminal_data_set.push_back(Terminal(Distance, Height, Phi, Theta, R, X, Y, Z, DirectDistance, AzimuthAngle, ElevationAngle, RadialDistance));
			}
			else
			{
				if (i_Terminals_positions % 5 == 0) { converter << static_cast<std::string>(xx); converter >> Distance;	converter.clear(); }
				else if (i_Terminals_positions % 5 == 1) { converter << static_cast<std::string>(xx); converter >> Height;	converter.clear(); }
				else if (i_Terminals_positions % 5 == 2) { converter << static_cast<std::string>(xx); converter >> Phi;		converter.clear(); }
				else if (i_Terminals_positions % 5 == 3) { converter << static_cast<std::string>(xx); converter >> Theta;		converter.clear(); }
				else if (i_Terminals_positions % 5 == 4) { converter << static_cast<std::string>(xx); converter >> R;			converter.clear(); }
				i_Terminals_positions++;

				// Adding to the terminals data set //////////////////////////////////
				if (i_Terminals_positions > 0 && i_Terminals_positions % 5 == 0)Terminal_data_set.push_back(Terminal(Distance, Height, Phi, Theta, R));
				//////////////////////////////////////////////////////////////////////	
			}
		}
		in_Terminals_positions.close();
		cout << " Total Number of Lines :" << i_Terminals_positions / 5 << endl;
		return Terminal_data_set;
	}
	std::vector<Terminal> GetPositionDataSet()
	{
		return GetPositionDataSetFromFile(this->TerminalPositionsFile);
	}
	void SetTerminalsPositionsFile(std::string file) {
		TerminalPositionsFile = file;
	}
	void SetTerminalsPositionsFileDirectory(std::string Position_Power_directory) {
		///**************** Get directory that contains the files ***************
		string file_in_teminals_positions{ Position_Power_directory + "/Terminals_positions.txt" };
		TerminalPositionsFile = file_in_teminals_positions;
	}
	static double ReadTestCaseData(string file_path)
	{
		std::stringstream converter;
		//string file_in_transmitter_power{ Position_Power_directory + "/Transmitter_power.txt" }; PREVIOUSLAY NAMMED Transmitter_power.txt
		std::ifstream in_transmitter_power{ file_path };    //file_in_transmitter_power 
		if (!in_transmitter_power)
		{
			std::cerr << " Transmitter_Power file is not open." << std::endl;
			exit(1);
		}
		std::vector<string> transmitter_power_file{ std::istream_iterator<string>(in_transmitter_power),std::istream_iterator<string>() };
		float transmitter_power_watt;
		size_t Total_receiver_points;
		float Carrier_Frequency;
		float Bandwidth, Spacing, Phi_array;
		size_t Samples_Count;
		size_t item = 0;
		size_t Transmitter_Elements_Count, Receiver_Elements_Count;
		float Case;
		size_t groups, Centered, Feature;
		for (auto xx : transmitter_power_file) {
			if (item == 0) { converter << static_cast<std::string>(xx); converter >> transmitter_power_watt;				converter.clear(); }
			else if (item == 1) { converter << static_cast<std::string>(xx); converter >> Environment::Transmitter_height;		converter.clear(); }
			else if (item == 2) { converter << static_cast<std::string>(xx); converter >> Total_receiver_points;			converter.clear(); }
			else if (item == 3) { converter << static_cast<std::string>(xx); converter >> Carrier_Frequency; 				converter.clear(); }
			else if (item == 4) { converter << static_cast<std::string>(xx); converter >> Bandwidth;						converter.clear(); }
			else if (item == 5) { converter << static_cast<std::string>(xx); converter >> Spacing;							converter.clear(); }
			else if (item == 6) { converter << static_cast<std::string>(xx); converter >> Samples_Count;					converter.clear(); }
			else if (item == 7) { converter << static_cast<std::string>(xx); converter >> Transmitter_Elements_Count;		converter.clear(); }
			else if (item == 8) { converter << static_cast<std::string>(xx); converter >> Receiver_Elements_Count; 		converter.clear(); }
			else if (item == 9) { converter << static_cast<std::string>(xx); converter >> Case; Environment::Test_Case_str = xx;	converter.clear(); }
			else if (item == 10) { converter << static_cast<std::string>(xx); converter >> groups; 							converter.clear(); }
			else if (item == 11) { converter << static_cast<std::string>(xx); converter >> Centered; 						converter.clear(); }
			else if (item == 12) { converter << static_cast<std::string>(xx); converter >> Feature; 						converter.clear(); }
			else if (item == 13) { converter << static_cast<std::string>(xx); converter >> Phi_array; 						converter.clear(); }
			item++;
		}
		cout << " Transmitter Power     : " << 10 * log10(1000 * transmitter_power_watt) << " dBm" << endl; Environment::Transmitter_power = transmitter_power_watt;
		cout << " Transmitter Height    : " << Environment::Transmitter_height << " Meters" << endl;
		cout << " Total Receiver Points : " << Total_receiver_points << endl;
		cout << " Carrier Frequency     : " << Carrier_Frequency << " Hz" << endl; //Environment::CarrierFrequency = Carrier_Frequency;
		cout << " Bandwidth             : " << Bandwidth << " Hz" << endl;
		cout << " Spacing               : " << Spacing << " Lambda" << endl; Environment::Spacing = Spacing;
		cout << " Samples Count         : " << Samples_Count << endl;
		cout << " Transmitter Elements  : " << Transmitter_Elements_Count << endl;
		cout << " Receiver Elements     : " << Receiver_Elements_Count << endl;
		cout << " Case#                 : " << Case << endl;
		cout << " Aixes Groups          : " << groups << endl;
		cout << " Centerted             : " << Centered << endl;
		cout << " Feature               : " << Feature << "(0:No, 1: City)" << endl;
		cout << " Array Azimuth angle   : " << Phi_array << endl; Environment::Phi_array = Phi_array * 22.0 / (7.0 * 180.0);
		cout << " Beam Angle            : " << 90 - Phi_array << endl;
		if (transmitter_power_watt <= 0) {
			cout << " Error with Transmitter Power Value , it sould be > 0" << endl;
			exit;
		}

		Environment::data_file.AddItem(0, 0, 10 * log10(1000 * transmitter_power_watt));
		Environment::data_file.AddItem(0, 1, Environment::Transmitter_height);
		Environment::data_file.AddItem(0, 2, Total_receiver_points);
		Environment::data_file.AddItem(0, 3, Carrier_Frequency);
		Environment::data_file.AddItem(0, 4, Bandwidth);
		Environment::data_file.AddItem(0, 5, Spacing);
	//	Environment::data_file.AddItem(0, 6, Environment::CalculateNoisePower(Bandwidth));
		Environment::data_file.AddItem(0, 7, Environment::Samples_Count = static_cast<double>(Samples_Count));
		Environment::data_file.AddItem(0, 8, static_cast<double>(Transmitter_Elements_Count));
		Environment::data_file.AddItem(0, 9, static_cast<double>(Receiver_Elements_Count));
		Environment::data_file.AddItem(0, 10, Environment::Test_Case = Case);
		Environment::data_file.AddItem(0, 11, static_cast<double>(groups));
		Environment::data_file.AddItem(0, 12, static_cast<double>(Centered));
		Environment::data_file.AddItem(0, 13, static_cast<double>(Feature));
		//	Environment::data_file.AddItem(0, 14, static_cast<size_t>(exposure));
		Environment::data_file.AddItem(0, 15, static_cast<double>(Phi_array)); // If needed

		return transmitter_power_watt;
	}

	static void CreateResultsFolder(std::string file_in_teminals_positions, std::string file_in_transmitter_power)
	{
		std::array< EXPOSURE, 3>Expo = { LOS,NLOS,ALL };
		for (EXPOSURE exposure : Expo)
		{
			Environment::SetRESULTSFolder(exposure);
			//	cout << file_in_teminals_positions << endl; cout << Environment::RESULTSFolder + Environment::GetTestCase() + "/Terminals_positions.txt" << endl;
			std::filesystem::create_directory(Environment::RESULTSFolder + Environment::GetTestCase());
			//**********COPYING TERMINALS POSITION FILE TO RESULTS FOLDER ****************************
			std::filesystem::copy_file(file_in_teminals_positions, Environment::RESULTSFolder + Environment::GetTestCase() + "/Terminals_positions.txt", filesystem::copy_options::overwrite_existing);
			//**********COPYING TRANSMITTER POWER FILE TO RESULTS FOLDER ****************************
			std::filesystem::copy_file(file_in_transmitter_power, Environment::RESULTSFolder + Environment::GetTestCase() + "/Transmitter_power.txt", filesystem::copy_options::overwrite_existing);
			//**********WORKS ONLY FOR 1 TRANSMITTER AND BUNCH OF RECEIVERS***************************
		}
	}
	static std::string GetTestCase()
	{
		return (Test_Case_str);
	}
	static void SetRESULTSFolder(EXPOSURE check)
	{
		switch (check)
		{
		case LOS:
			Environment::RESULTSFolder = "D:/RESULTS_5/LOS/";//"D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/RESULTS/LOS/";
			break;
		case NLOS:
			Environment::RESULTSFolder = "D:/RESULTS_5/NLOS/";//"D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/RESULTS/NLOS/";
			break;
		case ALL:
			Environment::RESULTSFolder = "D:/RESULTS_5/ALL/";
			break;
		}
	}
//	static double CalculateNoisePower(double BandWidth)
//	{
//		double K = 1.38064852e-23;
//		return NoisePower = K * Temperature * BandWidth;
//	}
public:
	static double CarrierFrequency;
	//static double NoisePower;
	//static double Temperature;
	static double Samples_Count;
	static float  Test_Case;
	static float  Spacing;
	static float  Phi_array;
	static double Transmitter_power;
	static float Transmitter_height;
	static string Test_Case_str;
	static string RESULTSFolder;
	static std::filesystem::path Cir_Folder;
	static std::filesystem::path StudyArea_Folder;
	std::string TerminalPositionsFile;
	static Float_matrix data_file;
};

