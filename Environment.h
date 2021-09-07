#pragma once
#include<iostream>
#include<iomanip>
using namespace std;
// This class creates the terminals position destribution and simulation environment 

struct Terminal
{
	float Distance;						// Distance from BS
	float Height;						// Height from BS
	float Phi;							// Azimuth from BS
	float Theta;						// Elevation from BS
	float R;							// Radial Distance from BS
	Terminal(float d, float h, float phi, float theta, float r)
	{
		Distance = d;					// Distance from BS
		Height = h;						// Height from BS
		Phi = phi;						// Azimuth from BS
		Theta = theta;					// Elevation from BS
		R = r;
	}
	void Show()
	{
		cout << "******************************************************" << endl;
		cout << setw(12) << "Distance(m)" << setw(12) << "Height(m)" << setw(12) << "Phi(rad)" << setw(12) << "Theta(rad)" << setw(12) << "R(m)" << endl;
		cout << "______________________________________________________" << endl;
		cout << setw(12) << Distance << setw(12) << Height << setw(12) << Phi << setw(12) << Theta << setw(12) << R << endl;
	}
};
class Environment
{
public:
	Environment() {
		TerminalPositionsFile = "";
	}
	static std::vector<Terminal> GetPositionDataSetFromFile(std::string file_in_teminals_positions)
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
		for (auto xx : Terminals_positions_file)
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
	void CreateProject()
	{

	}
	void WirelessInSite_3()
	{
		
		
	}
public:
	std::string TerminalPositionsFile;
};

