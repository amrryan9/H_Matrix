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
#include "H_Item.h"						//////////////////////////////////////////
#include "Ray.h"
#include "Set.h"
#include "Tools.h"
#include "Environment.h"
#include "CommunicationSystem.h"

using namespace std;

typedef std::vector<std::string> string_vector;
//enum version{v3_0_01,v3_3_31 };
enum class POINTS_SOURCE{FILE,SYST};
struct TX_POWER
{
	TX_POWER()
	{
		TX_SET = 0;
		TX_POINT = 0;
		TX_POWER_WATT = 0.0;
	}
	TX_POWER(unsigned tx_set,unsigned tx_point,	float tx_power_watt)
	{
		TX_SET = tx_set;
		TX_POINT = tx_point;
		TX_POWER_WATT = tx_power_watt;
	}
	unsigned TX_SET;
	unsigned TX_POINT;
	float TX_POWER_WATT;
};
struct TRANSMITTER_POWER
{
	TRANSMITTER_POWER() {}
	TRANSMITTER_POWER(CommunicationSystem& syst)
	{
		for (auto& point_set : syst.PointsSets)
			if (point_set->Transmitter_exist)
			{
				unsigned j = 0;
				for (auto& i : point_set->Point_locations)
				{
					j++;
					AddTransmitter(point_set->Project_id, j, pow(10.0, point_set->TX->Power_dBm / 10) / 1000);
				}
			}
	}
	float GetPower(unsigned tx_set, unsigned tx_point)
	{
		for(auto& t: POWER_WATT)
			if (t.TX_POINT == tx_point && t.TX_SET == tx_set)
			{
				return t.TX_POWER_WATT;
			}
	}
	void AddTransmitter(unsigned tx_set, unsigned tx_point, float tx_power_watt)
	{
		POWER_WATT.push_back(TX_POWER(tx_set, tx_point, tx_power_watt));
	}
	void AddTransmitters(CommunicationSystem& syst)
	{
		for (auto& point_set : syst.PointsSets)
			if (point_set->Transmitter_exist)
			{
				unsigned j = 0;
				for (auto& i : point_set->Point_locations)
				{
					j++;
					AddTransmitter(point_set->Project_id, j, pow(10.0, point_set->TX->Power_dBm / 10) / 1000);
				}
			}
	}
	void Show()
	{
		cout << setw(8) << "Tx Set" << setw(9) << "Tx Point" << setw(9) << "Power(W)" << endl;
		for (auto& t : POWER_WATT)
			cout << setw(8) << t.TX_SET << setw(9) << t.TX_POINT << setw(9) << t.TX_POWER_WATT << endl;
	}
	std::vector<TX_POWER> POWER_WATT;
};
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
			Environment::data_file.WriteFile(Environment::RESULTSFolder + Environment::GetTestCase() + "/Capacity_Test_Data.txt");
		}
		else
		{
			cout << case_path.string() << "Already EXISTS " << endl;
			Environment::data_file.WriteFile(Environment::RESULTSFolder + Environment::GetTestCase() + "/Capacity_Test_Data.txt");
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
	
	inline Set read_directory(const std::string& cir_path, CommunicationSystem* syst=nullptr)
	{
		std::stringstream converter;
		//*************************************************************************
		Environment::Cir_Folder = cir_path;
		///**************** Get directory that contains the files ***************
		
		std::string Position_Power_directory{ cir_path };
		for (char folder = 0; folder < 2; folder++)//2 normal
		{
			std::string last_folder = Position_Power_directory.substr(Position_Power_directory.find_last_of('/'));
			Position_Power_directory.replace(Position_Power_directory.find_last_of('/'), last_folder.size(), "");
			if (folder == 0)Environment::StudyArea_Folder = Position_Power_directory;
		}
		cout << " EBERY THING POSITION :" << Position_Power_directory << endl;
		cout << " STUDY AREA FOLDER    :" << Environment::StudyArea_Folder << endl;
		///**************** Reading Transmitter Power****************************
		
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
		TRANSMITTER_POWER transmitter_power_watt;
		if (syst != nullptr)
			transmitter_power_watt.AddTransmitters(*syst);
		else
			transmitter_power_watt.AddTransmitter(1,1, Environment::ReadTestCaseData(Position_Power_directory + "/Transmitter_power.txt"));

		transmitter_power_watt.Show();
		Set MIMO_H_MATRIX;
		ReadDirection(cir_path, transmitter_power_watt, MIMO_H_MATRIX, FILES::CIR);
		if(CheckIfFolderExist(dod_path))
			ReadDirection(dod_path, transmitter_power_watt, MIMO_H_MATRIX, FILES::DOD);
		MIMO_H_MATRIX.SetExposure();
		//************************* END APPLY *****************************************
		//************** CREATING TERMINALS DATA SET **********************************
		//************** READING TERMINALS _POSITIONS FILE*****************************
		std::vector<Terminal> Terminal_data_set;
		CommunicationSystem Syst;
		string file_in_teminals_positions{ Position_Power_directory + "/Terminals_positions.txt" };
		if(syst!=nullptr)
			/***Update the Set with points positions********/
			SetPointsPositions(MIMO_H_MATRIX, *syst);
			/***********************************************/
		else
		{
			Terminal_data_set = Environment::GetPositionDataSetFromFile(file_in_teminals_positions);
			/***Update the Set with points positions**************/
			SetPointsPositions(MIMO_H_MATRIX, Terminal_data_set);
			/*****************************************************/
			//*****************************************************************************
			Environment::CreateResultsFolder(file_in_teminals_positions, Position_Power_directory + "/Transmitter_power.txt");//file_in_transmitter_power
			//*****************************************************************************
		}
		

	//	MIMO_H_MATRIX.PermutateBack();

		return MIMO_H_MATRIX;
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
							p=Permutate(i_terminal, SetSize);
						//	p = i_terminal;
							// Adding RxPosition to Set_Line ///////////////////////////////////////
							s.RxPosition.Distance = Terminal_data_set.at(p).Distance;
							s.RxPosition.Height = Terminal_data_set.at(p).Height;
							s.RxPosition.Theta = Terminal_data_set.at(p).Theta;
							s.RxPosition.Phi = Terminal_data_set.at(p).Phi;
							s.RxPosition.R = Terminal_data_set.at(p).R;
							s.RxPosition.X = s.RxPosition.R * cos(s.RxPosition.Phi);
							s.RxPosition.Y = s.RxPosition.R * sin(s.RxPosition.Phi);
							s.RxPosition.Z = s.RxPosition.Distance * cos(s.RxPosition.Theta);
							s.TxPosition.Z = 500; // For testing
							s.TxPosition.X = 0; // For testing
							s.TxPosition.Y = 0; // For testing
							s.DirectDistance = sqrt(pow(s.TxPosition.X - s.RxPosition.X, 2) + pow(s.TxPosition.Y - s.RxPosition.Y, 2) + pow(s.TxPosition.Z - s.RxPosition.Z, 2));
							s.ElevationAngle = asin(abs(s.TxPosition.Z - s.RxPosition.Z) / s.DirectDistance);// The Elevation angle magnitude is < 90 Degres, when it is positive the transmitter is higher , when negative , the transmitter is lower than the receiver
							//while (s.ElevationAngle > (22.0 / 7.0))s.ElevationAngle = s.ElevationAngle- (44.0 / 7.0); s.ElevationAngle = abs(s.ElevationAngle);

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
				s.ElevationAngle = asin(abs(s.TxPosition.Z - s.RxPosition.Z) / s.DirectDistance);// The Elevation angle magnitude is < 90 Degres, when it is positive the transmitter is higher , when negative , the transmitter is lower than the receiver
				//while (s.ElevationAngle > (22.0 / 7.0))s.ElevationAngle = s.ElevationAngle-(44.0 / 7.0); s.ElevationAngle = abs(s.ElevationAngle);

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
		if (DOD_EXIST)TEST = WirelessInsiteFiles::WirelessInsiteVersion_DOD;
		else TEST = WirelessInsiteFiles::WirelessInsiteVersion;
		size_t LOS_Path_ID{ 1 };
		switch (WirelessInsiteFiles::WirelessInsiteVersion_DOD)
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
	//	if (ARRIVAL_TIME >= 0.0)
	//	{
			Ray r(PATH_ID, SOURCE_ID, POWER, PHASE, ARRIVAL_TIME, ARRIVAL_PHI, ARRIVAL_THETA, DEPARTURE_PHI, DEPARTURE_THETA);
			pathes.push_back(r);
	//	}
	//	else
	//	{
		//	cout << " ERROR RAY : " << endl;
	//		Ray r(PATH_ID, SOURCE_ID, POWER, PHASE, ARRIVAL_TIME, ARRIVAL_PHI, ARRIVAL_THETA, DEPARTURE_PHI, DEPARTURE_THETA);
	//		pathes.push_back(r);// Added Also here , to be rejected at "Set::updateItem()"
		//	r.Show();
	//	}
		
	}
	//////////////////////////////////////////////////////////
	void ReadDirection(std::string path_folder, TRANSMITTER_POWER&  transmitter_power_watt, Set& MIMO_H_MATRIX, FILES FILE_TYPE)
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
						WirelessInsiteFiles::WirelessInsiteVersion = v3_0_01;
						WirelessInsiteFiles::WirelessInsiteVersion_DOD = v3_0_01;
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
						WirelessInsiteFiles::WirelessInsiteVersion = v3_3_31;
						WirelessInsiteFiles::WirelessInsiteVersion_DOD = v3_3_31;
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
							ray_path.Set(p.Path_ID, p.Source_ID, p.Power / transmitter_power_watt.GetPower(transmitter_id, transmitter_pt), p.Phase, p.Arrival_Time);
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

