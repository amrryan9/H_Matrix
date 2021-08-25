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
enum version { v3_0_01, v3_3_31 };
enum FILES { CIR, POWER };

class File_Processing
{
public:
	File_Processing() = default;
	inline Set read_directory(const std::string& cir_path)
	{
		version wireless_inSite;
		std::vector<std::string> parts;
		std::string::size_type position{ 0 };
		Set MIMO_H_MATRIX;
	std:string key{ "" };
		unsigned transmitter_id;
		unsigned receiver_id;
		unsigned transmitter_pt;
		unsigned receiver_pt;
		unsigned transmitter_element;
		unsigned receiver_element;
		std::stringstream converter;
		unsigned start_at;
		unsigned path_id;
		double power;
		double phase;
		double time;
		int i = 0;
		Ray* r;
		std::vector<Ray> pathes;
		Tools T;

		///**************** Reading Transmitter Power****************************
		string file_in_transmitter_power{ "D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/Transmitter_power.txt" };
		std::ifstream in_transmitter_power{ file_in_transmitter_power };
		if (!in_transmitter_power)
		{
			std::cerr << " Transmitter_Power file is not open." << std::endl;
			exit(1);
		}
		std::vector<string> transmitter_power_file{ std::istream_iterator<string>(in_transmitter_power),std::istream_iterator<string>() };
		double transmitter_power_watt;
		for (auto xx : transmitter_power_file) { converter << static_cast<std::string>(xx); converter >> transmitter_power_watt;	converter.clear(); }

		if (transmitter_power_watt <= 0) {
			cout << " Error with Transmitter Power Value , it sould be > 0" << endl;
			exit;
		}
		//***************** Creating Power Folder Path ****************************
		std::string power_path = cir_path;
		std::string last_folder = cir_path.substr(cir_path.find_last_of('/'));
		power_path.replace(cir_path.find_last_of('/'), last_folder.size(), "/power");
		//*************************************************************************
		array<FILES, 2> READ = { CIR, POWER };
		std::string path;
		//	for (auto files_type : READ)
		{
			/*	switch (files_type)
				{
				case CIR:
					path = cir_path;
					break;
				case POWER:
					path = power_path;
					break;
				} */
			path = cir_path;
			cout << path << endl;
			string_vector v;
			try {
				for (const auto& entry : std::filesystem::directory_iterator(path))
				{
					v.push_back(entry.path().filename().generic_string());
				}
			}
			catch (const char aMessage[]) {
				cout << " ERROR IN DIRECTORY DISCRIPTION OR DIRECTORY NOT FOUND " << aMessage << endl;
				exit(1);
			}
			cout << " Number of files found : " << v.size() << endl;;
			for (auto& file_name : v)
			{
				//	cout << " File Under test :" << file_name << endl;
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
				//	if (files_type == CIR)//parts.size() == 9 && static_cast<std::string>(*(parts.end() - 1)) == "csv") //&& files_type==CIR) || ((parts.size() == 8 && static_cast<std::string>(*(parts.end() - 1)) == "csv") && files_type == POWER))
				{
					if (static_cast<std::string>(*(parts.begin())) == "cir")//&& files_type == CIR) 
					{
						converter << static_cast<std::string>(*(parts.begin() + 1)).substr(5, 3); converter >> transmitter_id;	converter.clear();	// Transmitter Set
						converter << static_cast<std::string>(*(parts.begin() + 2)).substr(4); converter >> transmitter_pt;	converter.clear();	// Transmitter Point
						converter << static_cast<std::string>(*(parts.begin() + 3)).substr(5, 3); converter >> receiver_id;	converter.clear();	// Receiver Set
						converter << static_cast<std::string>(*(parts.begin() + 4)).substr(4); converter >> receiver_pt;	converter.clear();	// Receiver Point
						converter << static_cast<std::string>(*(parts.begin() + 5)).substr(4, 3); converter >> transmitter_element; converter.clear();	// Transmitter Element  
						converter << static_cast<std::string>(*(parts.begin() + 6)).substr(4, 3); converter >> receiver_element;	converter.clear();	// Receiver Element
						converter.flush();

						key = static_cast<std::string>(*(parts.begin() + 1)).substr(5, 3) + static_cast<std::string>(*(parts.begin() + 2)).substr(4, 3) + static_cast<std::string>(*(parts.begin() + 3)).substr(5, 3) + static_cast<std::string>(*(parts.begin() + 4)).substr(4, 3);

						string file_in{ file_open };
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
							if (xx == "(s)>")
							{
								start_at = i;
								break;
							}
						}
						i = 0;
						path_id = 0;
						power = 0.0;
						phase = 0.0;
						time = 0.0;
						pathes.clear();
						while (i < (cir_file.size() - 9))
						{
							unsigned char k = 0;
							std::string reading{ "" };
							std::string line = static_cast<std::string>(cir_file.at(9 + i));
							while (line.size() > 0)
							{
								if (k < 4)
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
								case 0:	converter << reading; converter >> path_id;	converter.clear(); break;
								case 2:	converter << reading; converter >> power;	converter.clear(); break;
								case 3:	converter << reading; converter >> phase;	converter.clear(); break;
								case 4:	converter << reading; converter >> time;	converter.clear(); break;
								default:															   break;
								}
								k++;
								line.erase(0, reading.size() + 1);
							}
							converter.flush();
							r = new Ray(path_id, power, phase, time);
							pathes.push_back(*r);
							i++;
						}
						/////   ALL PATHES ARE ADDED 
						complex<double>ray_sum = complex<double>(0, 0);
						complex<double>ray_Power_sum = complex<double>(0, 0);
						for (auto& p : pathes)
						{
							Ray ray_path(p.Path_ID, p.Power / transmitter_power_watt, p.Phase, p.Arrival_Time);
							Ray power_ray(p.Path_ID, p.Power, p.Phase, p.Arrival_Time);
							ray_sum = ray_sum + ray_path.Voltage_Value;
							ray_Power_sum = ray_Power_sum + power_ray.Voltage_Value;
						}
						MIMO_H_MATRIX.AddItem(transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element - 1, receiver_element - 1, std::conj(ray_sum), pow(std::abs(ray_Power_sum), 2));
						//	MIMO_H_MATRIX.AddItem(transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element - 1, receiver_element - 1, std::conj(ray_sum));
						MIMO_H_MATRIX.AddTopologyItem(transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element, receiver_element);
						in.close();
					}
					/*	else if (static_cast<std::string>(*(parts.begin())) == "power" && files_type == POWER)
						{

							converter << static_cast<std::string>(*(parts.begin() + 1)).substr(5, 3); converter >> transmitter_id;		converter.clear();	// Transmitter Set
							converter << static_cast<std::string>(*(parts.begin() + 2)).substr(4);	  converter >> transmitter_pt;		converter.clear();	// Transmitter Point
							converter << static_cast<std::string>(*(parts.begin() + 3)).substr(5, 3); converter >> receiver_id;			converter.clear();	// Receiver Set
							converter << static_cast<std::string>(*(parts.begin() + 4)).substr(4, 3); converter >> transmitter_element; converter.clear();	// Transmitter Element
							converter << static_cast<std::string>(*(parts.begin() + 5)).substr(4, 3); converter >> receiver_element;	converter.clear();	// Receiver Element
							converter.flush();
							string file_in{ file_open };
							std::ifstream in{ file_in };
							if (!in)
							{
								std::cerr << file_in << " not open." << std::endl;
								std::cout << file_in << " not open." << std::endl;
								exit(1);
							}
							std::vector<string> power_file{ std::istream_iterator<string>(in),std::istream_iterator<string>() };
							power = 0.0;
							phase = 0.0;
							receiver_pt = 0;
							while (receiver_pt < (power_file.size() - 1))
							{
								cout << transmitter_id << transmitter_pt << receiver_id << transmitter_element << receiver_element << endl;
								unsigned char k = 0;
								std::string reading{ "" };
								std::string line = static_cast<std::string>(power_file.at(1 + receiver_pt));
								while (line.size() > 0)
								{
									if (k < 1)
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
									case 0: converter << reading; converter >> power; converter.clear(); break;
									case 1: converter << reading; converter >> phase; converter.clear(); break;
									default:																break;
									}
									k++;
									line.erase(0, reading.size() + 1);
								}
								MIMO_H_MATRIX.AddItemPower(transmitter_id, receiver_id, transmitter_pt, receiver_pt, transmitter_element - 1, receiver_element - 1, power, phase);
								converter.flush();
								receiver_pt++;
							}
						}
						else cout<< " something went wrong " <<endl; */
				}
			}
		}

		//************** CREATING TERMINALS DATA SET **********************************
		std::vector<Terminal> Terminal_data_set;
		//************** READING TERMINALS _POSITIONS FILE*****************************
		string file_in_teminals_positions{ "D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/Terminals_positions.txt" };
		std::ifstream in_Terminals_positions{ file_in_teminals_positions };
		if (!in_Terminals_positions)
		{
			std::cerr << " Terminals_Positions file is not open." << std::endl;
			exit(1);
		}
		std::vector<string> Terminals_positions_file{ std::istream_iterator<string>(in_Terminals_positions),std::istream_iterator<string>() };
		size_t i_Terminals_positions = 0;
		double Distance;
		double Height;
		double Phi;
		double Theta;
		for (auto xx : Terminals_positions_file)
		{
			if (i_Terminals_positions % 4 == 0) { converter << static_cast<std::string>(xx); converter >> Distance;	converter.clear(); }
			else if (i_Terminals_positions % 4 == 1) { converter << static_cast<std::string>(xx); converter >> Height;	converter.clear(); }
			else if (i_Terminals_positions % 4 == 2) { converter << static_cast<std::string>(xx); converter >> Phi;		converter.clear(); }
			else if (i_Terminals_positions % 4 == 3) { converter << static_cast<std::string>(xx); converter >> Theta;		converter.clear(); }
			i_Terminals_positions++;

			// Adding to the terminals data set //////////////////////////////////
			if (i_Terminals_positions > 0 && i_Terminals_positions % 4 == 0)Terminal_data_set.push_back(Terminal(Distance, Height, Phi, Theta));
			//////////////////////////////////////////////////////////////////////	
		}
		in_Terminals_positions.close();
		cout << " Total Number of Lines :" << i_Terminals_positions / 4 << endl;
		//**********WORKS ONLY FOR 1 TRANSMITTER AND BUNCH OF RECEIVERS***************************
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
							//////////////////////////////////////////////////////////////////////
							i_terminal++;
						}
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
		MIMO_H_MATRIX.SetCapacity("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/MIMO_BS_UAV_TERMINALS/Capacity.txt");
		return MIMO_H_MATRIX;
	}


};

