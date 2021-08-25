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
#include"Tools.h"

using namespace std;

typedef std::vector<std::string> string_vector;
class File_Processing_SISO
{
public:
	File_Processing_SISO() = default;
	inline void Read_Paths(Set& MIMO_H_MATRIX, std::vector<std::string>& parts, std::string cir_path, double transmitter_power_watt)
	{
		//************ get Paths File Name ***********************
		std::vector<std::string> paths_file_parts = parts;
		std::string paths_file_path{ "" };
		paths_file_parts.at(1) = "paths";
		for (auto pp : paths_file_parts) {
			cout << pp << endl;
			if (pp != "p2m")paths_file_path = paths_file_path + pp + ".";
			else paths_file_path = paths_file_path + pp;
		}
		cout << paths_file_path << endl;
		cout << cir_path << endl;
		//********************************************************
		version wireless_inSite;
		std:string key{ "" };
		unsigned transmitter_id;
		unsigned receiver_id;
		unsigned transmitter_pt;
		unsigned receiver_pt;
		unsigned transmitter_element;
		unsigned receiver_element;
		std::stringstream converter;
		unsigned start_at;
		int path_number;
		int interactions{ -1 };
		double power;
		double phase;
		double time;
		double delay_spread;
		float arrival_theta;
		float arrival_phi;
		float departure_theta;
		float departure_phi;
		unsigned Number_of_paths;
		int i = 0;
		Ray* r;
		std::vector<Ray> pathes;
		Tools T;
		if (paths_file_parts.size() == 5 && static_cast<std::string>(*(paths_file_parts.end() - 1)) == "p2m")
		{
			if (static_cast<std::string>(*(paths_file_parts.begin() + 1)) == "paths")
			{
				converter << static_cast<std::string>(*(paths_file_parts.begin() + 2)).substr(1, 3);	converter >> transmitter_id;	    converter.clear();	// Transmitter Set
				converter << static_cast<std::string>(*(paths_file_parts.begin() + 2)).substr(5, 2);	converter >> transmitter_pt;	    converter.clear();	// Transmitter Point
				converter << static_cast<std::string>(*(paths_file_parts.begin() + 3)).substr(1, 3);	converter >> receiver_id;		    converter.clear();	// Receiver Set
				transmitter_element = 0;	// Transmitter Element  
				receiver_element = 0;	// Receiver Element

				string file_in{ cir_path+"/"+paths_file_path };
				cout << file_in << endl;
				std::ifstream in{ file_in };
				if (!in)
				{
					std::cerr << file_in << " not open." << std::endl;
					exit(1);
				}
				std::vector<string> paths_file;
				std::string line{};
				while (std::getline(in, line, '\n'))
				{
					paths_file.push_back(line);
				}

				size_t Total_Receiver_Points;
				cout << "***************" << endl;
			//	for (auto z : paths_file)cout << z << endl;
				cout << "***************" << endl;
				unsigned Total_receive_points = Tools::ConvertToUnsigned_general(Tools::GetWord(paths_file.at(21), 0)); cout << " Total Receiver Points:"<<Total_receive_points << endl;
			// ************ READING SECTIONS ***************************
				if (Tools::GetWord(paths_file.at(21), 1) == "#")
				{
					wireless_inSite = version::v3_3_31;
					Tools::WirelessInsiteVersion = v3_3_31;
					start_at = 22;
				}
				else
				{
					wireless_inSite = version::v3_0_01;
					Tools::WirelessInsiteVersion = v3_0_01;
					start_at = 19;
					Read_Cir(MIMO_H_MATRIX, parts, cir_path, transmitter_power_watt);
				}
				
				for (size_t n_receiver_pts = 0; n_receiver_pts < Total_receive_points; n_receiver_pts++)
				{
					Number_of_paths = Tools::ConvertToUnsigned_general(Tools::GetWord(paths_file.at(start_at), 1));
					receiver_pt = Tools::ConvertToUnsigned_general(Tools::GetWord(paths_file.at(start_at), 0));
					//	cout << " Number of pathes for point :" << receiver_pt << " is :" << Number_of_paths << endl;
					power = 1e-28;
					phase = 0.0;
					time = 0.0;
					interactions = -1;
					arrival_theta = 0.0;
					arrival_phi = 0.0;
					departure_theta = 0.0;
					departure_phi = 0.0;
					pathes.clear();
					if (Number_of_paths > 0)
					{
						delay_spread = Tools::ConvertToDouble(Tools::GetWord(paths_file.at(start_at + 1), 2));
						start_at = start_at + 2;
						for (size_t n_paths = 0; n_paths < Number_of_paths; n_paths++)
						{
							path_number = Tools::ConvertToUnsigned_general(Tools::GetWord(paths_file.at(start_at), 0));
							interactions = Tools::ConvertToUnsigned_general(Tools::GetWord(paths_file.at(start_at), 1));
							power = Tools::ConvertToDouble(Tools::GetWord(paths_file.at(start_at), 2));
							if(wireless_inSite == version::v3_3_31)phase = Tools::ConvertToDouble(Tools::GetWord(paths_file.at(start_at), 3));
							time = Tools::ConvertToDouble(Tools::GetWord(paths_file.at(start_at), 4));
							arrival_theta = static_cast<float>(Tools::ConvertToDouble(Tools::GetWord(paths_file.at(start_at), 5)));
							arrival_phi = static_cast<float>(Tools::ConvertToDouble(Tools::GetWord(paths_file.at(start_at), 6)));
							departure_theta = static_cast<float>(Tools::ConvertToDouble(Tools::GetWord(paths_file.at(start_at), 7)));
							departure_phi = static_cast<float>(Tools::ConvertToDouble(Tools::GetWord(paths_file.at(start_at), 8)));
							// *************** ADD RAY to Pathes****************************
							r = new Ray(path_number, interactions, pow(10, (power / 10.0)) / 1000, phase * 22 / (7 * 180), time, arrival_theta * 22 / (7 * 180), arrival_phi * 22 / (7 * 180), departure_theta * 22 / (7 * 180), departure_phi * 22 / (7 * 180));
							pathes.push_back(*r);
							//**************************************************************
							start_at = start_at + 4 + interactions;
						}
					}
					else
					{
						start_at = start_at + 1;
						// *************** ADD EMPTY RAY to Pathes****************************
						r = new Ray(path_number, interactions, 0, phase * 22 / (7 * 180), time, arrival_theta * 22 / (7 * 180), arrival_phi * 22 / (7 * 180), departure_theta * 22 / (7 * 180), departure_phi * 22 / (7 * 180));
						pathes.push_back(*r); //cout << " Empty ray added" << endl; r->Show();
						//**************************************************************
					}
					complex<double>ray_sum = complex<double>(0, 0);
					complex<double>ray_Power_sum = complex<double>(0, 0);
					for (auto& p : pathes)
					{
						Ray ray_path(p.Path_ID, 0, p.Power / transmitter_power_watt, p.Phase, p.Arrival_Time);
						ray_sum = ray_sum + ray_path.Voltage_Value;
						Ray power_ray(p.Path_ID, 0, p.Power, p.Phase, p.Arrival_Time);
						ray_Power_sum = ray_Power_sum + power_ray.Voltage_Value;
					}
					MIMO_H_MATRIX.AddItem(pathes, transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element, receiver_element, std::conj(ray_sum), pow(std::abs(ray_Power_sum), 2));//pow(10, (power / 10)) / 1000, phase * 22 / (7 * 180));//
					MIMO_H_MATRIX.AddTopologyItem(transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element + 1, receiver_element + 1);
				}
			// *********************************************************
				
				in.close();
			}
		}
	}
	inline void Read_Cir(Set& MIMO_H_MATRIX, std::vector<std::string>& parts, std::string cir_path,double transmitter_power_watt)
	{
		version wireless_inSite;
		std:string key{ "" };
		unsigned transmitter_id;
		unsigned receiver_id;
		unsigned transmitter_pt;
		unsigned receiver_pt;
		unsigned transmitter_element;
		unsigned receiver_element;
		std::stringstream converter;
		unsigned start_at;
		int path_id;
		double power;
		double phase;
		double time;
		int i = 0;
		Ray* r;
		std::vector<Ray> pathes;
		Tools T;
		if (parts.size() == 5 && static_cast<std::string>(*(parts.end() - 1)) == "p2m")
		{
			if (static_cast<std::string>(*(parts.begin() + 1)) == "cir")
			{

				converter << static_cast<std::string>(*(parts.begin() + 2)).substr(1, 3);	converter >> transmitter_id;	    converter.clear();	// Transmitter Set
				converter << static_cast<std::string>(*(parts.begin() + 2)).substr(5, 2);	converter >> transmitter_pt;	    converter.clear();	// Transmitter Point
				converter << static_cast<std::string>(*(parts.begin() + 3)).substr(1, 3);	converter >> receiver_id;		    converter.clear();	// Receiver Set
				transmitter_element = 0;	// Transmitter Element  
				receiver_element = 0;	// Receiver Element

				string file_in{ cir_path };
				cout << file_in << endl;
				std::ifstream in{ file_in };
				if (!in)
				{
					std::cerr << file_in << " not open." << std::endl;
					exit(1);
				}
				std::vector<string> cir_file;// { std::istream_iterator<string>(in), std::istream_iterator<string>() };
				std::string line{};
				while (std::getline(in, line, '\n'))
				{
					cir_file.push_back(line);
				}
				size_t Total_Receiver_Points;
				std::string Third_Line = Tools::GetWord(cir_file.at(2), 0);
				if (Third_Line._Equal("#"))wireless_inSite = version::v3_3_31; else wireless_inSite = version::v3_0_01;
				switch (wireless_inSite)
				{
				case version::v3_0_01:
					Tools::WirelessInsiteVersion = v3_0_01;
					cout << " Version : v3_0_01 " << endl;
					converter << Third_Line;				converter >> Total_Receiver_Points;	converter.clear();	// Receiver Point
					converter.flush();
					start_at = 3;
					break;
				case version::v3_3_31:
					Tools::WirelessInsiteVersion = v3_3_31;
					cout << " Version : v3_3_31 " << endl;
					converter << Tools::GetWord(cir_file.at(5), 0);				converter >> Total_Receiver_Points;	converter.clear();	// Receiver Point
					converter.flush();
					start_at = 6;
					break;
				}
				for (size_t p = 0; p < Total_Receiver_Points; p++)
				{
					//	size_t Receiver_Points;
					size_t rays;
					converter << Tools::GetWord(cir_file.at(start_at), 0);	converter >> receiver_pt;		    converter.clear();	// Receiver Point
					converter << Tools::GetWord(cir_file.at(start_at), 1);	converter >> rays;		    converter.clear();
					//	cout << " RECEIVER POINTS IN THIS SECTION " << receiver_pt << " RAYS :" << rays<< endl;
					i = 0;
					path_id = 0;
					power = 1e-28;
					phase = 0.0;
					time = 0.0;
					pathes.clear();
					if (rays > 0)
					{
						while (i < rays)
						{
							unsigned char k = 0;
							std::string reading{ "" };
							std::string line = cir_file.at(i + start_at + 1);
							//			cout << line << endl;
							while (line.size() > 0)
							{
								if (k < 3)
								{
									unsigned j = line.find_first_of(" ");
									reading = line.substr(0, j);
								}
								else
								{
									reading = line;
								}
								switch (k)
								{
								case 0:	converter << reading; converter >> path_id;	converter.clear(); break;
								case 1:	converter << reading; converter >> phase;	converter.clear(); break;
								case 2:	converter << reading; converter >> time;	converter.clear(); break;
								case 3:	converter << reading; converter >> power;	converter.clear(); break;
								default:															   break;
								}

								k++;
								line.erase(0, reading.size() + 1);
								//	cout << line << endl;
							}
							//	cout << path_id << " " << phase << " " << time << " " << power << endl;
							converter.flush();
							r = new Ray(path_id, 0, pow(10, (power / 10.0)) / 1000, phase * 22 / (7 * 180), time);
							pathes.push_back(*r);
							i++;
						}
					}
					else if (rays == 0)
					{
						r = new Ray(path_id, 0, power, phase, time);
						pathes.push_back(*r);
					}
					start_at = start_at + rays + 1;
					//	cout << transmitter_id << transmitter_pt << receiver_id << receiver_pt << transmitter_element << receiver_element << endl;
					complex<double>ray_sum = complex<double>(0, 0);
					complex<double>ray_Power_sum = complex<double>(0, 0);
					for (auto& p : pathes)
					{
						Ray ray_path(p.Path_ID, 0, p.Power / transmitter_power_watt, p.Phase, p.Arrival_Time);
						ray_sum = ray_sum + ray_path.Voltage_Value;
						Ray power_ray(p.Path_ID, 0, p.Power, p.Phase, p.Arrival_Time);
						ray_Power_sum = ray_Power_sum + power_ray.Voltage_Value;
					}
					MIMO_H_MATRIX.AddItem(pathes, transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element, receiver_element, std::conj(ray_sum), pow(std::abs(ray_Power_sum), 2));//pow(10, (power / 10)) / 1000, phase * 22 / (7 * 180));//
					MIMO_H_MATRIX.AddTopologyItem(transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element + 1, receiver_element + 1);
				}
				converter.flush();
				in.close();
			}
		}
	}
	inline Set read_directory(const std::string& cir_path)//, EXPOSURE exposure)
	{
		version wireless_inSite;
		std::string paths_path{""};
		std::vector<std::string> parts;
		std::string::size_type position{ 0 };
		Set MIMO_H_MATRIX;
		std::stringstream converter;
		Tools T;
		//*************************************************************************
		Tools::Cir_Folder = cir_path;
		///**************** Get directory that contains the files ***************
		std::string Position_Power_directory{ cir_path };
		for (char folder = 0; folder < 2; folder++)
		{
			std::string last_folder = Position_Power_directory.substr(Position_Power_directory.find_last_of('/'));
			Position_Power_directory.replace(Position_Power_directory.find_last_of('/'), last_folder.size(), "");
			if (folder == 0)paths_path = Position_Power_directory;
		}
		cout << " EBERY THING POSITIN :" << Position_Power_directory << endl;
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
			if (item == 0) { converter << static_cast<std::string>(xx); converter >> transmitter_power_watt;			converter.clear(); }
			else if (item == 1 ) { converter << static_cast<std::string>(xx); converter >> Tools::Transmitter_height;	converter.clear(); }
			else if (item == 2 ) { converter << static_cast<std::string>(xx); converter >> Total_receiver_points;			converter.clear(); }
			else if (item == 3 ) { converter << static_cast<std::string>(xx); converter >> Carrier_Frequency;				converter.clear(); }
			else if (item == 4 ) { converter << static_cast<std::string>(xx); converter >> Bandwidth;						converter.clear(); }
			else if (item == 5 ) { converter << static_cast<std::string>(xx); converter >> Spacing;							converter.clear(); }
			else if (item == 6 ) { converter << static_cast<std::string>(xx); converter >> Samples_Count;					converter.clear(); }
			else if (item == 7 ) { converter << static_cast<std::string>(xx); converter >> Transmitter_Elements_Count;		converter.clear(); }
			else if (item == 8 ) { converter << static_cast<std::string>(xx); converter >> Receiver_Elements_Count; 			converter.clear(); }
			else if (item == 9 ) { converter << static_cast<std::string>(xx); converter >> Case; Tools::Test_Case_str = xx;	converter.clear(); }
			else if (item == 10) { converter << static_cast<std::string>(xx); converter >> groups; 			converter.clear(); }
			else if (item == 11) { converter << static_cast<std::string>(xx); converter >> Centered; 			converter.clear(); }
			else if (item == 12) { converter << static_cast<std::string>(xx); converter >> Feature; converter.clear(); }
			else if (item == 13) { converter << static_cast<std::string>(xx); converter >> Phi_array; converter.clear(); }
			item++;
		}
		cout << " Transmitter Power     : " << 10 * log10(1000 * transmitter_power_watt) << " dBm" << endl;
		cout << " Transmitter Height    : " << Tools::Transmitter_height << " Meters" << endl;
		cout << " Total Receiver Points : " << Total_receiver_points << endl;
		cout << " Carrier Frequency     : " << Carrier_Frequency << " Hz" << endl;
		cout << " Bandwidth             : " << Bandwidth << " Hz" << endl;
		cout << " Spacing               : " << Spacing << " Lambda" << endl;
		cout << " Samples Count         : " << Samples_Count << " Lambda" << endl;
		cout << " Transmitter Elements  : " << Transmitter_Elements_Count << endl;
		cout << " Receiver Elements     : " << Receiver_Elements_Count << endl;
		cout << " Case#                 : " << Case << endl;
		cout << " Aixes Groups          : " << groups << endl;
		cout << " Centerted             : " << Centered << endl;
		cout << " Feature               : " << Feature << "(0:No, 1: City)" << endl;
		cout << " Array Azimuth angle   : " << Phi_array << endl; Tools::Phi_array = Phi_array * 22.0 / (7.0 * 180.0);
		cout << " Beam Angle            : " << 90 - Phi_array << endl;
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
		if (std::filesystem::create_directories(case_path))
		{
			cout << case_path.string() << " EXISTS " << endl;
			data_file.WriteFile(Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_Test_Data.txt");
		}
		else
		{
			cout << case_path.string() << " TO BE CREATED " << endl;
			data_file.WriteFile(Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_Test_Data.txt");
		}
		//	exit(1);
		//***************** Creating Power Folder Path ****************************
		std::string power_path = cir_path;
		std::string last_folder = cir_path.substr(cir_path.find_last_of('/'));  
		power_path.replace(cir_path.find_last_of('/'), last_folder.size(), "/power"); 
		//*************************************************************************
		std::string path;
		path = cir_path;
		cout << path << endl;
		string_vector v;

		position = 0;
		position = path.find_last_of("/");
		path.erase(0, position+1);
		std::string File_Name = path;
		cout << File_Name <<endl; 
		
		auto file_open = path;
		parts.clear();
		position = 0;
		while ((path.find(".")) != std::string::npos)
		{
			position = path.find_first_of('.', 0);
			parts.push_back(path.substr(0, position));
			path.erase(0, static_cast<std::string>(*(parts.end() - 1)).size() + 1);
		}
		parts.push_back(path); for (auto pp : parts)cout << pp << endl;
		//*****************************************************************************
		Read_Cir(MIMO_H_MATRIX, parts,cir_path, transmitter_power_watt);
	//	Read_Paths(MIMO_H_MATRIX, parts, paths_path, transmitter_power_watt);
		//************** CREATING TERMINALS DATA SET **********************************
		std::vector<Terminal> Terminal_data_set;
		//************** READING TERMINALS _POSITIONS FILE*****************************
		string file_in_teminals_positions{ Position_Power_directory + "/Terminals_positions.txt" }; // "D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/Terminals_positions.txt"};
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
		cout << " Total Number of Lines :" << i_Terminals_positions / 5 << endl; 
		//********** SET RESULTS FOLDER **********************************************************
		std::array< EXPOSURE, 3>Expo = { LOS,NLOS,ALL };
		for (EXPOSURE exposure : Expo)
		{
			Tools::SetRESULTSFolder(exposure);
			cout << file_in_teminals_positions << endl; cout << Tools::RESULTSFolder + Tools::GetTestCase() << endl;
			std::filesystem::create_directory(Tools::RESULTSFolder + Tools::GetTestCase()); 
			//**********COPYING TERMINALS POSITION FILE TO RESULTS FOLDER ****************************
			std::filesystem::copy_file(file_in_teminals_positions, Tools::RESULTSFolder + Tools::GetTestCase() + "/Terminals_positions.txt",filesystem::copy_options::overwrite_existing);
			//**********COPYING TRANSMITTER POWER FILE TO RESULTS FOLDER ****************************
			std::filesystem::copy_file(file_in_transmitter_power, Tools::RESULTSFolder + Tools::GetTestCase() + "/Transmitter_power.txt", filesystem::copy_options::overwrite_existing);
			//**********WORKS ONLY FOR 1 TRANSMITTER AND BUNCH OF RECEIVERS***************************
		}
		size_t i_terminal = 0;
		if (MIMO_H_MATRIX.Transmitters.size() == 1)
			if (MIMO_H_MATRIX.Transmitters.at(0).T_R_Points.size() == 1)
				if (MIMO_H_MATRIX.Receivers.size() == 1)
					if (MIMO_H_MATRIX.S.size() == Terminal_data_set.size())
					{
						cout << " OK !!!" << endl;
						for (auto& s : MIMO_H_MATRIX.S)
						{
							// Adding Position to Set_Line ///////////////////////////////////////
							s.Position.Distance = Terminal_data_set.at(i_terminal).Distance;
							s.Position.Height = Terminal_data_set.at(i_terminal).Height;
							s.Position.Theta = Terminal_data_set.at(i_terminal).Theta;
							s.Position.Phi = Terminal_data_set.at(i_terminal).Phi;
							s.Position.R = Terminal_data_set.at(i_terminal).R;
							//////////////////////////////////////////////////////////////////////
							i_terminal++;
						}
						cout << " OK !!!" << endl;
					}
					else cout << " Receiver points " << MIMO_H_MATRIX.S.size() << " Terminals " << Terminal_data_set.size() << endl;
				else cout << " Receivers are :" << MIMO_H_MATRIX.Receivers.size() << endl;
			else cout << " Transmitters points :" << MIMO_H_MATRIX.Transmitters.at(0).T_R_Points.size() << endl;
		else cout << " Transmetters are :" << MIMO_H_MATRIX.Transmitters.size() << endl;
	//	for (auto t : Terminal_data_set)
		{
	//		t.Show();
		}
		//****************************************************************************************
	//	MIMO_H_MATRIX.SetCapacity("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/MIMO_BS_UAV_TERMINALS/Capacity.txt");
		
		return MIMO_H_MATRIX;
	}
};

