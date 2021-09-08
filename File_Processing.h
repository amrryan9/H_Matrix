#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>						///////////////////////////////////////////
#include <map>							//// This Class Reads the 'cir' and 'dod' folders at
#include <algorithm>					//// Wireless Insite StudyArea folder wihic are 
#include <iterator>						//// Created using MIMO output feature.
#include <filesystem>					//// It is used only for a MIMO simulation
#include <sstream>						//// The output is a Data set contains all the links between the transmitter(s) and 
#include <numeric>						//// the receiver(s) points. each link contains the rays , or the propagation paths 
#include <complex>						//// between each antenna element of each transmitter to each antenna element 
#include <iomanip>						//// at each receiver, plus a topology data, with positions of the receiver points
#include <cmath>						//// and the orientation of the antenna array
#include "H_Item.h"
#include "Ray.h"
#include "Set.h"
#include "Tools.h"
#include "Environment.h"
#include "CommunicationSystem.h"

using namespace std;

typedef std::vector<std::string> string_vector;
//enum version{v3_0_01,v3_3_31 };

class File_Processing
{
public:
	File_Processing() = default;
	
	size_t Permutate(size_t i, size_t s)
	{
		i++;
		return (Tools::Permute(i, s)) - 1;
	}
	void Write_Test_Data(const std::string& file_path)
	{
		//***************** Creat The file directories if don't exist ********
		std::filesystem::path case_path = file_path; //Tools::RESULTSFolder + Tools::GetTestCase();
		if (std::filesystem::create_directories(case_path))
		{
			cout << case_path.string() << " EXISTS " << endl;
			Tools::data_file.WriteFile(Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_Test_Data.txt");
		}
		else
		{
			cout << case_path.string() << "Already EXISTS " << endl;
			Tools::data_file.WriteFile(Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_Test_Data.txt");
			//	exit(1);
		}
	}
	bool CheckIfFolderExist(const std::string& folder_path)
	{
		//***************** Check if the folder exists **************************
		if (std::filesystem::exists(folder_path)) {
			cout << " PATH TO THE TARGET FOLDER IS :" << folder_path << endl;
		}
		else
		{
			cout << " PATH TO THE TARGET FOLDER IS :" << folder_path << " DOES NOT EXIST" << endl;
			return false;
		}
		return true;
	}
	
	void CreateResultsFolder(std::string file_in_teminals_positions, std::string file_in_transmitter_power)
	{
		std::array< EXPOSURE, 3>Expo = { LOS,NLOS,ALL };
		for (EXPOSURE exposure : Expo)
		{
			Tools::SetRESULTSFolder(exposure);
		//	cout << file_in_teminals_positions << endl; cout << Tools::RESULTSFolder + Tools::GetTestCase() + "/Terminals_positions.txt" << endl;
			std::filesystem::create_directory(Tools::RESULTSFolder + Tools::GetTestCase());
			//**********COPYING TERMINALS POSITION FILE TO RESULTS FOLDER ****************************
			std::filesystem::copy_file(file_in_teminals_positions, Tools::RESULTSFolder + Tools::GetTestCase() + "/Terminals_positions.txt", filesystem::copy_options::overwrite_existing);
			//**********COPYING TRANSMITTER POWER FILE TO RESULTS FOLDER ****************************
			std::filesystem::copy_file(file_in_transmitter_power, Tools::RESULTSFolder + Tools::GetTestCase() + "/Transmitter_power.txt", filesystem::copy_options::overwrite_existing);
			//**********WORKS ONLY FOR 1 TRANSMITTER AND BUNCH OF RECEIVERS***************************
		}
	}
	inline Set read_directory(const std::string& cir_path,Environment* environ=0)
	{
		std::stringstream converter;
		//*************************************************************************
		Tools::Cir_Folder = cir_path;
		///**************** Get directory that contains the files ***************
		
		std::string Position_Power_directory{ cir_path };
		for (char folder = 0; folder < 2; folder++)//2 normal
		{
			std::string last_folder = Position_Power_directory.substr(Position_Power_directory.find_last_of('/'));
			Position_Power_directory.replace(Position_Power_directory.find_last_of('/'), last_folder.size(), "");
			if (folder == 0)Tools::StudyArea_Folder = Position_Power_directory;
		}
		cout << " EBERY THING POSITION :" << Position_Power_directory << endl;
		cout << " STUDY AREA FOLDER    :" << Tools::StudyArea_Folder << endl;
		///**************** Reading Transmitter Power****************************
		string file_in_transmitter_power{ Position_Power_directory + "/Transmitter_power.txt" }; 
		std::ifstream in_transmitter_power{ file_in_transmitter_power };
		if (!in_transmitter_power)
		{
			std::cerr << " Transmitter_Power file is not open." << std::endl;
			exit(1);
		}
		std::vector<string> transmitter_power_file{ std::istream_iterator<string>(in_transmitter_power),std::istream_iterator<string>() };
		double transmitter_power_watt;
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
			else if (item == 1)  { converter << static_cast<std::string>(xx); converter >> Tools::Transmitter_height;		converter.clear(); }
			else if (item == 2)  { converter << static_cast<std::string>(xx); converter >> Total_receiver_points;			converter.clear(); }
			else if (item == 3)  { converter << static_cast<std::string>(xx); converter >> Carrier_Frequency; 				converter.clear(); }
			else if (item == 4)  { converter << static_cast<std::string>(xx); converter >> Bandwidth;						converter.clear(); }
			else if (item == 5)  { converter << static_cast<std::string>(xx); converter >> Spacing;							converter.clear(); }
			else if (item == 6)  { converter << static_cast<std::string>(xx); converter >> Samples_Count;					converter.clear(); }
			else if (item == 7)  { converter << static_cast<std::string>(xx); converter >> Transmitter_Elements_Count;		converter.clear(); }
			else if (item == 8)  { converter << static_cast<std::string>(xx); converter >> Receiver_Elements_Count; 		converter.clear(); }
			else if (item == 9)  { converter << static_cast<std::string>(xx); converter >> Case; Tools::Test_Case_str = xx;	converter.clear(); }
			else if (item == 10) { converter << static_cast<std::string>(xx); converter >> groups; 							converter.clear(); }
			else if (item == 11) { converter << static_cast<std::string>(xx); converter >> Centered; 						converter.clear(); }
			else if (item == 12) { converter << static_cast<std::string>(xx); converter >> Feature; 						converter.clear(); }
			else if (item == 13) { converter << static_cast<std::string>(xx); converter >> Phi_array; 						converter.clear(); }
			item++;
		}
		cout << " Transmitter Power     : " << 10 * log10(1000 * transmitter_power_watt) << " dBm" << endl; Tools::Transmitter_power = transmitter_power_watt;
		cout << " Transmitter Height    : " << Tools::Transmitter_height << " Meters" << endl;
		cout << " Total Receiver Points : " << Total_receiver_points << endl;
		cout << " Carrier Frequency     : " << Carrier_Frequency << " Hz" << endl; Tools::CarrierFrequency = Carrier_Frequency;
		cout << " Bandwidth             : " << Bandwidth << " Hz" << endl;
		cout << " Spacing               : " << Spacing << " Lambda" << endl; Tools::Spacing = Spacing;
		cout << " Samples Count         : " << Samples_Count << endl;
		cout << " Transmitter Elements  : " << Transmitter_Elements_Count << endl;
		cout << " Receiver Elements     : " << Receiver_Elements_Count << endl;
		cout << " Case#                 : " << Case << endl;
		cout << " Aixes Groups          : " << groups << endl;
		cout << " Centerted             : " << Centered << endl;
		cout << " Feature               : " << Feature << "(0:No, 1: City)" << endl;
		cout << " Array Azimuth angle   : " << Phi_array << endl; Tools::Phi_array = Phi_array*22.0/(7.0*180.0);
		cout << " Beam Angle            : " << 90-Phi_array << endl;
		if (transmitter_power_watt <= 0) {
			cout << " Error with Transmitter Power Value , it sould be > 0" << endl;
			exit;
		}
		
		Tools::data_file.AddItem(0, 0, 10 * log10(1000 * transmitter_power_watt));
		Tools::data_file.AddItem(0, 1, Tools::Transmitter_height);
		Tools::data_file.AddItem(0, 2, Total_receiver_points);
		Tools::data_file.AddItem(0, 3, Carrier_Frequency);
		Tools::data_file.AddItem(0, 4, Bandwidth);
		Tools::data_file.AddItem(0, 5, Spacing);
		Tools::data_file.AddItem(0, 6, Tools::CalculateNoisePower(Bandwidth));
		Tools::data_file.AddItem(0, 7, Tools::Samples_Count = static_cast<double>(Samples_Count));
		Tools::data_file.AddItem(0, 8, static_cast<double>(Transmitter_Elements_Count));
		Tools::data_file.AddItem(0, 9, static_cast<double>(Receiver_Elements_Count));
		Tools::data_file.AddItem(0, 10, Tools::Test_Case = Case);
		Tools::data_file.AddItem(0, 11, static_cast<double>(groups));
		Tools::data_file.AddItem(0, 12, static_cast<double>(Centered));
		Tools::data_file.AddItem(0, 13, static_cast<double>(Feature));
	//	Tools::data_file.AddItem(0, 14, static_cast<size_t>(exposure));
		Tools::data_file.AddItem(0, 15, static_cast<double>(Phi_array)); // If needed
		
		//***************** Creating Power Folder Path ******************************
		std::string power_path = cir_path;
		std::string last_folder = cir_path.substr(cir_path.find_last_of('/'));
		power_path.replace(cir_path.find_last_of('/'), last_folder.size(), "/power");
		cout << " POWER PATH IS : " << power_path << endl;
		//****************************************************************************
		//***************** Creating DoD Folder Path *********************************
		std::string dod_path = cir_path;
		last_folder = cir_path.substr(cir_path.find_last_of('/'));
		dod_path.replace(cir_path.find_last_of('/'), last_folder.size(), "/dod");
		std::filesystem::path dod = dod_path;
		cout << " DOD PATH IS : " << dod_path << endl;
		//************************* APPLY *********************************************
		Set MIMO_H_MATRIX;
		ReadDirection(cir_path,transmitter_power_watt, MIMO_H_MATRIX, FILES::CIR);
		if(CheckIfFolderExist(dod_path))
			ReadDirection(dod_path, transmitter_power_watt, MIMO_H_MATRIX, FILES::DOD);
		MIMO_H_MATRIX.SetExposure();
		//************************* END APPLY *****************************************
		//************** CREATING TERMINALS DATA SET **********************************
		//************** READING TERMINALS _POSITIONS FILE*****************************
		std::vector<Terminal> Terminal_data_set;
//		if(environ!=0)Terminal_data_set = environ->GetPositionDataSet(); // This has to be changed when the environment class is finished
//		else
	//	{
			string file_in_teminals_positions{ Position_Power_directory + "/Terminals_positions.txt" };
			Terminal_data_set = Environment::GetPositionDataSetFromFile(file_in_teminals_positions);
			//*****************************************************************************
			CreateResultsFolder(file_in_teminals_positions, file_in_transmitter_power);
			//*****************************************************************************
		//	return MIMO_H_MATRIX;
	//	}
		
		/***********Update the Set with points positions************************************/
		SetPointsPositions(MIMO_H_MATRIX, Terminal_data_set);
		/***********************************************/
		
		
	//	cout << " Total Number of Points" << MIMO_H_MATRIX.S.size() << " Number of " << " LOS" << " Points is " << MIMO_H_MATRIX.GetEXPO(EXPOSURE::LOS).S.size() << endl;
	//	MIMO_H_MATRIX.PermutateBack();
	//	MIMO_H_MATRIX.Show();
		return MIMO_H_MATRIX;// .GetEXPO(exposure);
	}
	//////////////////////////////////////////////////////////
	void SetPointsPositions(Set& MIMO_H_MATRIX, std::vector<Terminal>& Terminal_data_set)
	{
		size_t p = 0;
		size_t i_terminal = 0;
		size_t SetSize = MIMO_H_MATRIX.S.size();
		if (MIMO_H_MATRIX.Transmitters.size() == 1)
			if (MIMO_H_MATRIX.Transmitters.at(0).T_R_Points.size() == 1)
				if (MIMO_H_MATRIX.Receivers.size() == 1)
					if (MIMO_H_MATRIX.S.size() <= Terminal_data_set.size()) // ==
					{
						for (auto& s : MIMO_H_MATRIX.S)
						{
							//	p=Permutate(i_terminal, SetSize);
							p = i_terminal;
							// Adding RxPosition to Set_Line ///////////////////////////////////////
							s.RxPosition.Distance = Terminal_data_set.at(p).Distance;
							s.RxPosition.Height = Terminal_data_set.at(p).Height;
							s.RxPosition.Theta = Terminal_data_set.at(p).Theta;
							s.RxPosition.Phi = Terminal_data_set.at(p).Phi;
							s.RxPosition.R = Terminal_data_set.at(p).R;
							s.TxPosition.Z = 500; // For testing
							s.DirectDistance = sqrt(pow(s.TxPosition.X - s.RxPosition.X, 2) + pow(s.TxPosition.Y - s.RxPosition.Y, 2) + pow(s.TxPosition.Z - s.RxPosition.Z, 2)); cout << " Direct Distance :" << s.DirectDistance << endl;
							s.ElevationAngle = asin((s.TxPosition.Z - s.RxPosition.Z) / s.DirectDistance);// The Elevation angle magnitude is < 90 Degres, when it is positive the transmitter is higher , when negative , the transmitter is lower than the receiver
							if (s.ElevationAngle > (22.0 / 7.0))s.ElevationAngle = s.ElevationAngle - (44.0 / 7.0);
							//////////////////////////////////////////////////////////////////////
							i_terminal++;
						}
						cout << " OK !!!" << endl;
					}
					else cout << " Receiver points in The Set :" << MIMO_H_MATRIX.S.size() << " Terminals in Positions file:" << Terminal_data_set.size() << endl;
				else cout << " Receivers are :" << MIMO_H_MATRIX.Receivers.size() << endl;
			else cout << " Transmitters points :" << MIMO_H_MATRIX.Transmitters.at(0).T_R_Points.size() << endl;
		else cout << " Transmetters are :" << MIMO_H_MATRIX.Transmitters.size() << endl;
		//	for (auto t : Terminal_data_set)
		{
			//		t.Show();
		}
		//****************************************************************************************

	}
	void SetPointsPositions(Set& MIMO_H_MATRIX, CommunicationSystem& Comm)
	{

		size_t p = 0;
		size_t i_terminal = 0;
		size_t SetSize = MIMO_H_MATRIX.S.size();
		for (auto& s : MIMO_H_MATRIX.S)
		{
			
			//	p=Permutate(i_terminal, SetSize);
			//p = i_terminal;
			auto location_pointer_tx = Comm.GetPointLocation(s.Transmitter_Set, s.Transmitter_Point);
			auto location_pointer_rx = Comm.GetPointLocation(s.Receiver_Set, s.Receiver_Point);
			if (location_pointer_tx != nullptr  && location_pointer_rx != nullptr)
			{
				// Adding TxPosition to Set_Line ///////////////////////////////////////
				s.TxPosition.Distance = sqrt(pow(location_pointer_tx->X, 2.0) + pow(location_pointer_tx->Y, 2.0) + pow(location_pointer_tx->Z, 2.0));
				s.TxPosition.Height = location_pointer_tx->Z;
				s.TxPosition.R = (sqrt(pow(location_pointer_tx->X, 2.0) + pow(location_pointer_tx->Y, 2.0)));// Radial Distance
				s.TxPosition.Theta = asin(s.TxPosition.R / s.TxPosition.Distance);// Zenth Angle in Rads
				s.TxPosition.Phi = asin(location_pointer_tx->Y/ s.TxPosition.Distance);// Azimuth angle in Rads.
				s.TxPosition.X = location_pointer_tx->X;
				s.TxPosition.Y = location_pointer_tx->Y;
				s.TxPosition.Z = location_pointer_tx->Z;
				/////////////////////////////////////////////////////////////////////
			
				// Adding RxPosition to Set_Line ///////////////////////////////////////
				s.RxPosition.Distance = sqrt(pow(location_pointer_rx->X, 2.0) + pow(location_pointer_rx->Y, 2.0) + pow(location_pointer_rx->Z, 2.0));
				s.RxPosition.Height = location_pointer_rx->Z;
				s.RxPosition.R = (sqrt(pow(location_pointer_rx->X, 2.0) + pow(location_pointer_rx->Y, 2.0)));// Radial Distance
				s.RxPosition.Theta = asin(s.RxPosition.R / s.RxPosition.Distance);// Zenth Angle in Rads
				s.RxPosition.Phi = asin(location_pointer_rx->Y / s.RxPosition.Distance);// Azimuth angle in Rads.
				s.RxPosition.X = location_pointer_rx->X;
				s.RxPosition.Y = location_pointer_rx->Y;
				s.RxPosition.Z = location_pointer_rx->Z;
				/////////////////////////////////////////////////////////////////////
				s.DirectDistance = sqrt(pow(s.TxPosition.X-s.RxPosition.X, 2) + pow(s.TxPosition.Y - s.RxPosition.Y, 2) + pow(s.TxPosition.Z - s.RxPosition.Z, 2)); cout << " Direct Distance :" << s.DirectDistance << endl;
				s.ElevationAngle = asin((s.TxPosition.Z - s.RxPosition.Z) / s.DirectDistance);// The Elevation angle magnitude is < 90 Degres, when it is positive the transmitter is higher , when negative , the transmitter is lower than the receiver
				if (s.ElevationAngle > (22.0 / 7.0))s.ElevationAngle = s.ElevationAngle - (44.0 / 7.0);

			}
		//	i_terminal++;
		}
		cout << " OK !!!" << endl;
					
		//	for (auto t : Terminal_data_set)
		{
			//		t.Show();
		}
		//****************************************************************************************

	}
	EXPOSURE CheckPathes(std::vector<Ray> pathes, bool DOD_EXIST)
	{
		version TEST;
		if (DOD_EXIST)TEST = Tools::WirelessInsiteVersion_DOD;
		else TEST = Tools::WirelessInsiteVersion;
		size_t LOS_Path_ID{ 1 };
		switch (Tools::WirelessInsiteVersion_DOD)
		{
		case v3_0_01:
			LOS_Path_ID = 0;
			break;
		case v3_3_31:
			LOS_Path_ID = 1;
			break;
		default:
			LOS_Path_ID = 1;
			break;
		}
		for (auto& r : pathes)
		{
			if (r.Path_ID == static_cast<int>(LOS_Path_ID))
			{
				return LOS;
			}
		}
		return NLOS;
	}
	bool CheckPathes(std::vector<Ray> pathes,bool DOD_EXIST, EXPOSURE check)
	{
		if (check != ALL)
			if (CheckPathes(pathes, DOD_EXIST) == check)return true;
			else return false;
		else
			return true;
	}
	void UpdatePathes(FILES FILE_TYPE, unsigned path_id, unsigned source_id, std::vector<FILE_COLUMN> ITEM, std::vector<Ray>& pathes)
	{
		unsigned PATH_ID= path_id;
		unsigned SOURCE_ID= source_id;
		double POWER;
		double PHASE;
		double ARRIVAL_TIME;
		double ARRIVAL_PHI;
		double ARRIVAL_THETA;
		double DEPARTURE_PHI;
		double DEPARTURE_THETA;
		switch (FILE_TYPE)
		{
		case CIR:
			POWER= ITEM.at(0).VALUE;
			PHASE= ITEM.at(1).VALUE;
			ARRIVAL_TIME= ITEM.at(2).VALUE;
			ARRIVAL_PHI=0.0;
			ARRIVAL_THETA=0.0;
			DEPARTURE_PHI=0.0;
			DEPARTURE_THETA=0.0;
			break;
		case DOD:
			POWER= ITEM.at(4).VALUE;
			PHASE=0.0;
			ARRIVAL_TIME=0.0;
			ARRIVAL_PHI= ITEM.at(0).VALUE;
			ARRIVAL_THETA= ITEM.at(1).VALUE;
			DEPARTURE_PHI= ITEM.at(2).VALUE;
			DEPARTURE_THETA= ITEM.at(3).VALUE;
			break;
		}
		Ray r(PATH_ID, SOURCE_ID, POWER, PHASE, ARRIVAL_TIME, ARRIVAL_PHI, ARRIVAL_THETA, DEPARTURE_PHI, DEPARTURE_THETA);
		pathes.push_back(r);
	}
	//////////////////////////////////////////////////////////
	void ReadDirection(std::string path_folder, double transmitter_power_watt, Set& MIMO_H_MATRIX, FILES FILE_TYPE)
	{
		///////////////////////////////// START //////////////////////////////////////////////////////
		std::string path;
		std::string file_name;
		std::vector<Ray> pathes;
		//*************************************************************************
		unsigned char FILE_NAME_PARTS_COUNT;
		std::string FILE_NAME_TYPE;
		std::string START_SYMBOL;
		int NUMBER_OF_COLUMNS;
		unsigned NUMBER_OF_ITEMS;
		std::vector<FILE_COLUMN> ITEM;
		//*************************************************************************
		version wireless_inSite;
		std::vector<std::string> parts;
		std::string::size_type position{ 0 };
		std:string key{ "" };
		unsigned transmitter_id;
		unsigned receiver_id;
		unsigned transmitter_pt;
		unsigned receiver_pt;
		int transmitter_element;
		int receiver_element;
		std::stringstream converter;
		int start_at;
		int cir_file_size;
		int path_id;
		unsigned source_id;
		int i = 0;
		int j = 0;
		//*************************************************************************	
		path = path_folder;
		switch (FILE_TYPE)
		{
		case CIR:
			FILE_NAME_PARTS_COUNT = 9;
			FILE_NAME_TYPE = "cir";
			NUMBER_OF_COLUMNS = 5;
			NUMBER_OF_ITEMS = NUMBER_OF_COLUMNS - 2;
			for (unsigned item = 0; item < NUMBER_OF_ITEMS; item++)ITEM.push_back(FILE_COLUMN());
			ITEM.at(0).SET_FILE_COLUMN("Power(W)", 2, 0);
			ITEM.at(1).SET_FILE_COLUMN("Phase(Rad)", 3, 0);
			ITEM.at(2).SET_FILE_COLUMN("Arrival Time(s)", 4, 0);
			break;
		case DOD:
			FILE_NAME_PARTS_COUNT = 8;
			FILE_NAME_TYPE = "angles";
			NUMBER_OF_COLUMNS = 7;
			NUMBER_OF_ITEMS = NUMBER_OF_COLUMNS - 2;
			for (unsigned item = 0; item < NUMBER_OF_ITEMS; item++)ITEM.push_back(FILE_COLUMN());
			ITEM.at(0).SET_FILE_COLUMN("Arrival Phi(Rad)", 2, 0);
			ITEM.at(1).SET_FILE_COLUMN("Arrival Theta(Rad)", 3, 0);
			ITEM.at(2).SET_FILE_COLUMN("Departure Phi(Rad)", 4, 0);
			ITEM.at(3).SET_FILE_COLUMN("Departure Theta(Rad)", 5, 0);
			ITEM.at(4).SET_FILE_COLUMN("Power(W)", 6, 0);
			break;
		}
		//**********************************************************************
		string_vector v;
		try {
			for (const auto& entry : std::filesystem::directory_iterator(path_folder))
			{  
				v.push_back(entry.path().filename().generic_string());
			}
		}
		catch (const char aMessage[]) {
			cout << " ERROR IN DIRECTORY DISCRIPTION OR DIRECTORY NOT FOUND " << aMessage << endl;
			exit(1);
		}
		//************************** READ FILES ****************************
		for (size_t file_count=0;file_count<v.size();file_count++)// the file is chosen
		{
			// Cleaning for each file ////
			//////////////////////////////
			for (auto& item : ITEM)item.VALUE = 0.0;
			parts.clear();
			pathes.clear();
			//////////////////////////////
			file_name = v.at(file_count);
			
			// Get Files from the folder				
			auto file_open = path + "/" + file_name;
	//		cout << file_open << endl;
			position = 0;
			while ((file_name.find(".")) != std::string::npos)
			{
				position = file_name.find_first_of('.', 0);
				parts.push_back(file_name.substr(0, position));
				file_name.erase(0, static_cast<std::string>(*(parts.end() - 1)).size() + 1);
			}
			
			parts.push_back(file_name);
			if (parts.size() == FILE_NAME_PARTS_COUNT && static_cast<std::string>(*(parts.end() - 1)) == "csv")
			{
				if (static_cast<std::string>(*(parts.begin())) == FILE_NAME_TYPE)
				{
					converter << static_cast<std::string>(*(parts.begin() + 1)).substr(5, 3);	converter >> transmitter_id;	    converter.clear();	// Transmitter Set
					converter << static_cast<std::string>(*(parts.begin() + 2)).substr(4);		converter >> transmitter_pt;		converter.clear();	// Transmitter Point
					converter << static_cast<std::string>(*(parts.begin() + 3)).substr(5, 3);	converter >> receiver_id;		    converter.clear();	// Receiver Set
					converter << static_cast<std::string>(*(parts.begin() + 4)).substr(4);		converter >> receiver_pt;		    converter.clear();	// Receiver Point
					converter << static_cast<std::string>(*(parts.begin() + 5)).substr(4, 3);	converter >> transmitter_element;	converter.clear();	// Transmitter Element  
					converter << static_cast<std::string>(*(parts.begin() + 6)).substr(4, 3);	converter >> receiver_element;		converter.clear();	// Receiver Element
					converter.flush();
					key = static_cast<std::string>(*(parts.begin() + 1)).substr(5, 3) + static_cast<std::string>(*(parts.begin() + 2)).substr(4, 3) + static_cast<std::string>(*(parts.begin() + 3)).substr(5, 3) + static_cast<std::string>(*(parts.begin() + 4)).substr(4, 3);
					string file_in{ file_open };  // the file is open
					std::ifstream in{ file_in };
					if (!in)
					{
						std::cerr << file_in << " not open." << std::endl;
						std::cout << file_in << " not open." << std::endl;
						exit(1);
					}
					std::vector<string> cir_file{ std::istream_iterator<string>(in),std::istream_iterator<string>() };
					
					///////////////////////// CHECK VERSION ////////////////////////////////////
					if (cir_file.at(0) == "Path" && cir_file.at(1) == "Id,Source"/* && cir_file.at(2) == "Id,Received" && cir_file.at(3) == "Power"*/)wireless_inSite = v3_0_01; else wireless_inSite = v3_3_31;
					////////////////////////////////////////////////////////////////////////////
					switch (FILE_TYPE)
					{
					case CIR:
					switch (wireless_inSite) { case v3_0_01:START_SYMBOL = "(s)"; break; case v3_3_31:START_SYMBOL = "(s)>"; break; }
														   break;
					case DOD:
					switch (wireless_inSite) { case v3_0_01:START_SYMBOL = "(W)"; break; case v3_3_31:START_SYMBOL = "(W)>"; break; }
														   break;
					}
					////////////// Get the Start point
					i = 0;
					for (auto xx : cir_file)
					{
						i++;
						if (xx == START_SYMBOL)
						{
							start_at = i;
							break;
						}
					}
					switch (wireless_inSite)
					{
					case v3_0_01:
						///////////// READING ///////////////////
						//cout << "Version : 3.0.01" << endl;
						Tools::WirelessInsiteVersion = v3_0_01;
						Tools::WirelessInsiteVersion_DOD = v3_0_01;
						//////////////////////////////////////////
						i = 0;
						path_id = 0;
						source_id = 0;
						while (i < (cir_file.size() - 9))
						{
							for (auto& item : ITEM)item.VALUE = 0.0;
							unsigned char k = 0;
							std::string reading{ "" };
							std::string line = static_cast<std::string>(cir_file.at(9 + i));
							while (line.size() > 0)
							{
								if (k < NUMBER_OF_COLUMNS)
								{
									unsigned j = line.find_first_of(",");
									reading = line.substr(0, j);
								}
								else
								{
									reading = line;
								}
								switch (k)
								{
								case 0:	converter << reading; converter >> path_id;		converter.clear(); break;
								case 1:	converter << reading; converter >> source_id;	converter.clear(); break;
								default:
									if ((k - 2) < ITEM.size())
									{
										converter << reading; converter >> ITEM.at(k - 2).VALUE;	converter.clear(); break;
									}
									else
										cout << " ERROR : ITEM RECORD DOSN'T HAVE ENOUGH FIELDS !!" << endl;
									break;
								}
								k++;
								line.erase(0, reading.size() + 1);
							}
							converter.flush();
							UpdatePathes(FILE_TYPE, path_id, source_id, ITEM, pathes);
							i++;
						}
						/////   ALL PATHES ARE ADDED 
						/////////////////////////////////////////
						break;
					case v3_3_31:
						///////////// READING ///////////////////
						//cout << "Version : 3.3.31" << endl;
						i = 0;
						Tools::WirelessInsiteVersion = v3_3_31;
						Tools::WirelessInsiteVersion_DOD = v3_3_31;
						//////////////////////////////////////////
						cir_file_size = static_cast<int>(cir_file.size());
						while (i < (cir_file_size - (start_at + 4)))
						{
							for (auto& item : ITEM)item.VALUE = 0.0;
							path_id = Tools::ConvertToUnsigned_general(static_cast<std::string>(*(cir_file.begin() + (start_at + i))));//cout << " at position : "<< static_cast<std::string>(*(cir_file.begin() + (start_at + i))) << " Path Id : " << path_id << endl;
							source_id = Tools::ConvertToUnsigned_general(static_cast<std::string>(*(cir_file.begin() + 1 + (start_at + i))));// cout << source_id << endl;
							j = 0;
							for (size_t j = 0; j < NUMBER_OF_ITEMS; j++)
							{
								if ((start_at + 2 + j + i) < cir_file.size())
									ITEM.at(j).VALUE = Tools::ConvertToDouble(static_cast<std::string>(*(cir_file.begin() + (start_at + 2 + j + i)))); //cout << ITEM.at(j).VALUE << endl;
								else
									cout << "ERROR : THE CIR FILE ENDED TOO EARLY !!" << endl;
							}
							UpdatePathes(FILE_TYPE, path_id, source_id, ITEM, pathes); 
							i = i + NUMBER_OF_COLUMNS;
						}
						/////////////////////////////////////////
						break;
					default:
						cout << " UNKNOWN " << endl;
					}
					complex<double>ray_sum = complex<double>(0, 0);
					complex<double>ray_Power_sum = complex<double>(0, 0);
					Ray ray_path;
					Ray power_ray; 
					
					switch (FILE_TYPE)
					{
					case FILES::CIR:
						for (auto& p : pathes)
						{
							ray_path.Set(p.Path_ID, p.Source_ID, p.Power / transmitter_power_watt, p.Phase, p.Arrival_Time);
							ray_sum = ray_sum + ray_path.Voltage_Value;
							power_ray.Set(p.Path_ID, p.Source_ID, p.Power, p.Phase, p.Arrival_Time);
							ray_Power_sum = ray_Power_sum + power_ray.Voltage_Value;
						}
						MIMO_H_MATRIX.AddTopologyItem(transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element, receiver_element);
						(MIMO_H_MATRIX.AddItem(pathes, transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element - 1, receiver_element - 1, std::conj(ray_sum), pow(std::abs(ray_Power_sum), 2)));
						break;
					case FILES::DOD:
						if (!MIMO_H_MATRIX.UpdateItem(pathes, transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element, receiver_element))
							cout << " ERROR : RAYS MISMATCH !!" << endl;
						break;
					}	
					in.close(); // the file is closed 
				}
			}
		}
		///////////////////////////  END  ////////////////////////////////////////////////
	}
};

