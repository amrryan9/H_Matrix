#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <iterator>
#include <filesystem>
#include <sstream>
#include <numeric>
#include <complex>
#include <iomanip>
#include <cmath>
#include "H_Item.h"
#include "Ray.h"
#include "MatrixMIMO.h"
#include "Set.h"
#include "Tools.h"

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
	inline Set read_directory(const std::string& cir_path)// , EXPOSURE exposure)
	{
		std::stringstream converter;
		Set MIMO_H_MATRIX;
		//*************************************************************************
	//	Tools::SetRESULTSFolder(exposure);
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
		string file_in_transmitter_power{ Position_Power_directory + "/Transmitter_power.txt" }; //"D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/Transmitter_power.txt" };
		std::ifstream in_transmitter_power{ file_in_transmitter_power };
		if (!in_transmitter_power)
		{
			std::cerr << " Transmitter_Power file is not open." << std::endl;
			exit(1);
		}
		std::vector<string> transmitter_power_file{ std::istream_iterator<string>(in_transmitter_power),std::istream_iterator<string>() };
		double transmitter_power_watt;
	//	double transmitter_height;
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
			else if (item == 1)  { converter << static_cast<std::string>(xx); converter >> Tools::Transmitter_height;				converter.clear(); }
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
		MatrixMIMO<float> data_file;
		data_file.AddItem(0, 0, 10 * log10(1000 * transmitter_power_watt));
		data_file.AddItem(0, 1, Tools::Transmitter_height);
		data_file.AddItem(0, 2, Total_receiver_points);
		data_file.AddItem(0, 3, Carrier_Frequency);
		data_file.AddItem(0, 4, Bandwidth);
		data_file.AddItem(0, 5, Spacing);
		data_file.AddItem(0, 6, Tools::CalculateNoisePower(Bandwidth));
		data_file.AddItem(0, 7, Tools::Samples_Count = static_cast<double>(Samples_Count));
		data_file.AddItem(0, 8, static_cast<double>(Transmitter_Elements_Count));
		data_file.AddItem(0, 9, static_cast<double>(Receiver_Elements_Count));
		data_file.AddItem(0, 10, Tools::Test_Case = Case);
		data_file.AddItem(0, 11, static_cast<double>(groups));
		data_file.AddItem(0, 12, static_cast<double>(Centered));
		data_file.AddItem(0, 13, static_cast<double>(Feature));
	//	data_file.AddItem(0, 14, static_cast<size_t>(exposure));
		data_file.AddItem(0, 15, static_cast<double>(Phi_array)); // If needed
		//***************** Creat RESULTS and case directories if doesn't exist ********
		std::filesystem::path case_path = Tools::RESULTSFolder + Tools::GetTestCase();
		cout << case_path << endl;
		if (std::filesystem::create_directories(case_path))
		{
			cout << case_path.string() << " EXISTS " << endl;
			data_file.WriteFile(Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_Test_Data.txt");
		}
		else
		{
			cout << case_path.string() << "Already EXISTS " << endl;
			data_file.WriteFile(Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_Test_Data.txt");
		//	exit(1);
		}
		//***************** Creating Power Folder Path ****************************
		std::string power_path = cir_path;
		std::string last_folder = cir_path.substr(cir_path.find_last_of('/'));
		power_path.replace(cir_path.find_last_of('/'), last_folder.size(), "/power");
		//*************************************************************************
		//***************** Creating DoD Folder Path ****************************
		std::string dod_path = cir_path;
		last_folder = cir_path.substr(cir_path.find_last_of('/'));
		dod_path.replace(cir_path.find_last_of('/'), last_folder.size(), "/dod");
		std::filesystem::path dod = dod_path;
		//***************** Check if the folder exists **************************
		bool DOD_EXIST = false;
		if (std::filesystem::exists(dod)) {
			cout << " dod folder exists " << endl;
			DOD_EXIST = true;
			cout << " PATH TO THE TARGET FOLDER IS :" << dod_path << endl;
		}
		else
		{
			cout << " PATH TO THE TARGET FOLDER IS :" << dod_path << " DOES NOT EXIST"<<endl;
		}
		
		//************************* APPLY *****************************************
		//std::vector<RECORD>Rejected;
		//std::vector<bool>Rejected_brief;
		ReadDirection(cir_path, dod_path, DOD_EXIST, transmitter_power_watt, MIMO_H_MATRIX);
		//************************* END APPLY *****************************************
				
		//************** CREATING TERMINALS DATA SET **********************************
		std::vector<Terminal> Terminal_data_set;
		//std::vector<Terminal> Terminal_data_set_Expo;
		//************** READING TERMINALS _POSITIONS FILE*****************************
		string file_in_teminals_positions{ Position_Power_directory + "/Terminals_positions.txt" };// "D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/Terminals_positions.txt"};
		std::ifstream in_Terminals_positions{ file_in_teminals_positions };
		if (!in_Terminals_positions)
		{
			std::cerr <<" Terminals_Positions file is not open." << std::endl;
			exit(1);
		}
		std::vector<string> Terminals_positions_file{ std::istream_iterator<string>(in_Terminals_positions),std::istream_iterator<string>() };
		size_t i_Terminals_positions = 0;
		float Distance;
		float Height;
		float Phi;
		float Theta;
		float R;
		for (auto xx : Terminals_positions_file)
		{
			if      (i_Terminals_positions % 5 == 0){converter << static_cast<std::string>(xx); converter >> Distance;	converter.clear();}
			else if (i_Terminals_positions % 5 == 1){converter << static_cast<std::string>(xx); converter >> Height;	converter.clear();}
			else if (i_Terminals_positions % 5 == 2){converter << static_cast<std::string>(xx); converter >> Phi;		converter.clear();}
			else if (i_Terminals_positions % 5 == 3){converter << static_cast<std::string>(xx); converter >> Theta;		converter.clear();}
			else if (i_Terminals_positions % 5 == 4){converter << static_cast<std::string>(xx); converter >> R;			converter.clear();}
			i_Terminals_positions++;
			
			// Adding to the terminals data set //////////////////////////////////
			if(i_Terminals_positions >0 && i_Terminals_positions %5==0)Terminal_data_set.push_back(Terminal(Distance, Height, Phi, Theta, R));
			//////////////////////////////////////////////////////////////////////	
		}
		in_Terminals_positions.close();
		cout << " Total Number of Lines :" << i_Terminals_positions/5 << endl;

		std::array< EXPOSURE, 3>Expo = { LOS,NLOS,ALL };
		for (EXPOSURE exposure : Expo)
		{
			Tools::SetRESULTSFolder(exposure);
			cout << file_in_teminals_positions << endl; cout << Tools::RESULTSFolder + Tools::GetTestCase() + "/Terminals_positions.txt" << endl;
			std::filesystem::create_directory(Tools::RESULTSFolder + Tools::GetTestCase());
			//**********COPYING TERMINALS POSITION FILE TO RESULTS FOLDER ****************************
			std::filesystem::copy_file(file_in_teminals_positions, Tools::RESULTSFolder + Tools::GetTestCase() + "/Terminals_positions.txt", filesystem::copy_options::overwrite_existing);
			//**********COPYING TRANSMITTER POWER FILE TO RESULTS FOLDER ****************************
			std::filesystem::copy_file(file_in_transmitter_power, Tools::RESULTSFolder + Tools::GetTestCase() + "/Transmitter_power.txt", filesystem::copy_options::overwrite_existing);
			//**********WORKS ONLY FOR 1 TRANSMITTER AND BUNCH OF RECEIVERS***************************
		}
		size_t p{ 0 };
		size_t i_terminal = 0;
		size_t SetSize = MIMO_H_MATRIX.S.size();
		if (MIMO_H_MATRIX.Transmitters.size() == 1)
			if (MIMO_H_MATRIX.Transmitters.at(0).T_R_Points.size() == 1)
				if (MIMO_H_MATRIX.Receivers.size() == 1)
					if (MIMO_H_MATRIX.S.size() == Terminal_data_set.size())
					{
						for (auto& s : MIMO_H_MATRIX.S)
						{
							p=Permutate(i_terminal, SetSize);
							// Adding Position to Set_Line ///////////////////////////////////////
							s.Position.Distance = Terminal_data_set.at(p).Distance;
							s.Position.Height = Terminal_data_set.at(p).Height;
							s.Position.Theta = Terminal_data_set.at(p).Theta;
							s.Position.Phi = Terminal_data_set.at(p).Phi;
							s.Position.R = Terminal_data_set.at(p).R;
						//	s.Permutation_Index = p;
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
	//	MIMO_H_MATRIX.SetCapacity("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/MIMO_BS_UAV_TERMINALS/Capacity.txt");
	//	MIMO_H_MATRIX.SetExposure();
	//	cout << " Total Number of Points" << MIMO_H_MATRIX.S.size() << " Number of " << exposure << " Points is " << MIMO_H_MATRIX.GetEXPO(exposure).S.size() << endl;
		MIMO_H_MATRIX.Permutate();
		return MIMO_H_MATRIX;// .GetEXPO(exposure);
	}
	//////////////////////////////////////////////////////////
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
	//////////////////////////////////////////////////////////
	void ReadDirection(std::string path_cir, std::string path_dod,bool DOD_EXIST,double transmitter_power_watt, Set& MIMO_H_MATRIX)
	{
		///////////////////////////////// START //////////////////////////////////////////////////////
		std::string path;
		bool Flag = false;
		float file_count_float;
		std::string file_name;
		size_t last_cir_file_size;
		size_t last_dod_file_size;
		std::vector<Ray> pathes;
		std::vector<Set_Line>S_DOD;
		FILES FILE_TYPE;
		
		//*************************************************************************
		unsigned char FILE_NAME_PARTS_COUNT;
		std::string FILE_NAME_TYPE;
		std::string START_SYMBOL;
		int NUMBER_OF_COLUMNS;
		unsigned NUMBER_OF_ITEMS;
		std::vector<FILE_COLUMN> ITEM; //less than 8
		for (unsigned item = 0; item < 8; item++)ITEM.push_back(FILE_COLUMN());
		//////////////////
		version wireless_inSite;
		std::vector<std::string> parts;
		std::string::size_type position{ 0 };

	std:string key{ "" };
		unsigned transmitter_id;
		unsigned receiver_id;
		unsigned transmitter_pt;
		unsigned receiver_pt;
		unsigned transmitter_element;
		unsigned receiver_element;
		std::stringstream converter;
		int start_at;
		int cir_file_size;
		int path_id;
		unsigned source_id;
		int i = 0;
		int j = 0;
		Ray* r;
		Tools T;
		//**********************************************************************
		string_vector v_CIR;
		try {
			for (const auto& entry : std::filesystem::directory_iterator(path_cir))
			{
				v_CIR.push_back(entry.path().filename().generic_string());
			}
		}
		catch (const char aMessage[]) {
			cout << " ERROR IN DIRECTORY DISCRIPTION OR DIRECTORY NOT FOUND " << aMessage << endl;
			exit(1);
		}
		//**********************************************************************
		string_vector v_DOD;
		if (DOD_EXIST)
		{
			try {
				for (const auto& entry : std::filesystem::directory_iterator(path_dod))
				{
					v_DOD.push_back(entry.path().filename().generic_string());
				}
			}
			catch (const char aMessage[]) {
				cout << " ERROR IN DIRECTORY DISCRIPTION OR DIRECTORY NOT FOUND " << aMessage << endl;
				exit(1);
			}
		}
		//**********************************************************************
		// Check if CIR and DOD contains the same information
		size_t limit_which = 1;
		if (DOD_EXIST)
		{
			if (v_DOD.size() != v_CIR.size())
			{
				cout << " UNMATECHED CIR AND DOD FILES " << endl; exit(1);
			}
			limit_which = 2;
		}
		for (size_t file_count=0;file_count<v_CIR.size();file_count++)// the file is chosen/////////////////////////////////
		{
			for (size_t which = 0; which < limit_which; which++)
			{
				if (which == 0) //CIR
				{
					file_name = v_CIR.at(file_count);
					FILE_TYPE = CIR;
					path = path_cir;
					last_cir_file_size = 0; 
				}
				else //DOD
				{
					file_name = v_DOD.at(file_count); 
					FILE_TYPE = DOD;
					path = path_dod;
					last_dod_file_size = 0;
				}
				switch (FILE_TYPE)
				{
				case CIR:
					FILE_NAME_PARTS_COUNT = 9;
					FILE_NAME_TYPE = "cir";
					START_SYMBOL = "(s)>";
					NUMBER_OF_COLUMNS = 5;
					ITEM.at(0).SET_FILE_COLUMN("Power(W)", 2, 0);
					ITEM.at(1).SET_FILE_COLUMN("Phase(Rad)", 3, 0);
					ITEM.at(2).SET_FILE_COLUMN("Arrival Time(s)", 4, 0);
					pathes.clear();
					break;
				case DOD:
					FILE_NAME_PARTS_COUNT = 8;
					FILE_NAME_TYPE = "angles";
					START_SYMBOL = "(W)>";
					NUMBER_OF_COLUMNS = 7; 
					NUMBER_OF_ITEMS = NUMBER_OF_COLUMNS - 2;
					ITEM.resize(NUMBER_OF_ITEMS);
					ITEM.at(0).SET_FILE_COLUMN("Arrival Phi(Rad)", 2, 0); 
					ITEM.at(1).SET_FILE_COLUMN("Arrival Theta(Rad)", 3, 0); 
					ITEM.at(2).SET_FILE_COLUMN("Departure Phi(Rad)", 4, 0); 
					ITEM.at(3).SET_FILE_COLUMN("Departure Theta(Rad)", 5, 0); 
					ITEM.at(4).SET_FILE_COLUMN("Power(W)", 6, 0);
					break;
				}
				auto file_open = path + "/" + file_name;
				parts.clear();
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
		
						string file_in{ file_open };  // the file is opened/////////////////////////////////
						std::ifstream in{ file_in };
						if (!in)
						{
							std::cerr << file_in << " not open." << std::endl;
							std::cout << file_in << " not open." << std::endl;
							exit(1);
						}
						std::vector<string> cir_file{ std::istream_iterator<string>(in),std::istream_iterator<string>() };
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
						///////////////////////// CHECK VERSION ////////////////////////////////////
						if (cir_file.at(0) == "Path" && cir_file.at(1) == "Id,Source"/* && cir_file.at(2) == "Id,Received" && cir_file.at(3) == "Power"*/)wireless_inSite = v3_0_01; else wireless_inSite = v3_3_31;
						switch (wireless_inSite)
						{
						case v3_0_01:
							///////////// READING ///////////////////
						//	cout << "Version : 3.0.01" << endl;
							
							
							i = 0;
							path_id = 0;
							source_id = 0;
							///////////////
							for (auto& item : ITEM)item.VALUE = 0.0;
							///////////////
							while (i < (cir_file.size() - 9))
							{
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
										converter << reading; converter >> ITEM.at(k - 2).VALUE;	converter.clear(); break;
										break;
									}
									k++;
									line.erase(0, reading.size() + 1);
								}
								converter.flush();
								//	cout << path_id << setw(15) << source_id << setw(15) << ITEM.at(0).VALUE << setw(15) << ITEM.at(1).VALUE << setw(15) << ITEM.at(2).VALUE << endl;
								Ray r(path_id, source_id); 
								switch (FILE_TYPE)
								{
								case CIR:
									Tools::WirelessInsiteVersion = v3_0_01;
									r.Set(ITEM.at(0).VALUE, ITEM.at(1).VALUE, ITEM.at(2).VALUE);//power, phase, time);
									pathes.push_back(r);
									break;
								case DOD:
									Tools::WirelessInsiteVersion_DOD = v3_0_01;
									if (last_dod_file_size < pathes.size())
									{
										pathes.at(last_dod_file_size).SetDirections(path_id, source_id, ITEM.at(0).VALUE, ITEM.at(1).VALUE, ITEM.at(2).VALUE, ITEM.at(3).VALUE);
										last_dod_file_size++;
									}
									break;
								}
								i++;
							}
							/////   ALL PATHES ARE ADDED 
							/////////////////////////////////////////
							break;
						case v3_3_31:
							///////////// READING ///////////////////
						//	cout << "Version : 3.3.31" << endl;
							i = 0;
							///////////////
							for (auto& item : ITEM)item.VALUE = 0.0;

							cir_file_size = static_cast<int>(cir_file.size());
							while (i < (cir_file_size - (start_at + 4)))
							{
								path_id = T.ConvertToUnsigned_general(static_cast<std::string>(*(cir_file.begin() + (start_at + i))));// cout << path_id << endl;
								source_id = T.ConvertToUnsigned_general(static_cast<std::string>(*(cir_file.begin() + 1 + (start_at + i))));// cout << source_id << endl;
								j = 0;
								for (size_t j = 0; j < NUMBER_OF_COLUMNS-2;j++)
								{
									ITEM.at(j).VALUE = T.ConvertToDouble(static_cast<std::string>(*(cir_file.begin() + (start_at + 2 + j + i)))); //cout << ITEM.at(j).VALUE << endl;
								}
								Ray r(path_id, source_id);
								switch (FILE_TYPE)
								{
								case CIR:	
									Tools::WirelessInsiteVersion = v3_3_31;
									r.Set(ITEM.at(0).VALUE, ITEM.at(1).VALUE, ITEM.at(2).VALUE);//power, phase, time);
									pathes.push_back(r); 
									break;
								case DOD:
									Tools::WirelessInsiteVersion_DOD = v3_3_31;	
									if (last_dod_file_size < pathes.size())
									{
										pathes.at(last_dod_file_size).SetDirections(path_id, source_id, ITEM.at(0).VALUE, ITEM.at(1).VALUE, ITEM.at(2).VALUE, ITEM.at(3).VALUE);
										last_dod_file_size++;
									}
									break;
								}
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
						case DOD:   // Creat the Pathes and add Matrix Item
							for (auto& p : pathes)
							{
								ray_path.Set(p.Path_ID, p.Source_ID, p.Power / transmitter_power_watt, p.Phase, p.Arrival_Time);
								ray_sum = ray_sum + ray_path.Voltage_Value;
								power_ray.Set(p.Path_ID, p.Source_ID, p.Power, p.Phase, p.Arrival_Time);
								ray_Power_sum = ray_Power_sum + power_ray.Voltage_Value;
							}
							MIMO_H_MATRIX.AddTopologyItem(transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element, receiver_element);
							MIMO_H_MATRIX.AddItem(pathes, transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element - 1, receiver_element - 1, std::conj(ray_sum), pow(std::abs(ray_Power_sum), 2));// ->ShowPathes();
							break;
						case CIR:  // Only Modify the Pathes
							if (!DOD_EXIST)
							{
								for (auto& p : pathes)
								{
									ray_path.Set(p.Path_ID, p.Source_ID, p.Power / transmitter_power_watt, p.Phase, p.Arrival_Time);
									ray_sum = ray_sum + ray_path.Voltage_Value;
									power_ray.Set(p.Path_ID, p.Source_ID, p.Power, p.Phase, p.Arrival_Time);
									ray_Power_sum = ray_Power_sum + power_ray.Voltage_Value;
								}
								MIMO_H_MATRIX.AddTopologyItem(transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element, receiver_element);
								MIMO_H_MATRIX.AddItem(pathes, transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element - 1, receiver_element - 1, std::conj(ray_sum), pow(std::abs(ray_Power_sum), 2));// ->ShowPathes();
							}
							break;
						}
						in.close(); // the file is closed/////////////////////////////////
					}
				}
			}
		}
		///////////////////////////  END  ////////////////////////////////////////////////
	}
};

