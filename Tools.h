#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

enum version { v3_0_01, v3_3_31 };
enum configuration { MIMO, SISO };
enum angle_unit{ RAD, DEG};
enum EXPOSURE { ALL, NLOS, LOS,NON};
enum FILES { CIR, DOD };
struct RECORD
{
	RECORD()
	{
		Receiver_pt = 0;
		LOS_FLAG = false;
	}
	RECORD(size_t tx_pt, bool los)
	{
		Receiver_pt = tx_pt;
		LOS_FLAG = los;
	}
	void SHOW()
	{
		cout << " RECEIVER POINT # : " << Receiver_pt << " LOS FLAG : " << LOS_FLAG << endl;
	}
	size_t Receiver_pt;
	bool LOS_FLAG;
};
struct FILE_COLUMN
{
	FILE_COLUMN() {}
	FILE_COLUMN(std::string name, unsigned char place, double value)
	{
		NAME = name;
		PLACE = place;
		VALUE = value;
	}
	void SET_FILE_COLUMN(std::string name, unsigned char place, double value)
	{
		NAME = name;
		PLACE = place;
		VALUE = value;
	}
	const unsigned char Place() { return PLACE; }
	std::string		NAME;
	unsigned char	PLACE;
	double
		VALUE;
};

class Tools
{
public:
	Tools() = default;
	static unsigned int ConvertToUnsigned(std::string str)
	{
		unsigned x = 0;
		unsigned y = 0;
		unsigned C[3] = { 0,0,0 };
		for (char c : str)
		{
			if (x < 3)
			{
				if (c == '0')
					C[x] = 0;
				else if (c == '1')
					C[x] = 1;
				else if (c == '2')
					C[x] = 2;
				else if (c == '3')
					C[x] = 3;
				else if (c == '4')
					C[x] = 4;
				else if (c == '5')
					C[x] = 5;
				else if (c == '6')
					C[x] = 6;
				else if (c == '7')
					C[x] = 7;
				else if (c == '8')
					C[x] = 8;
				else if (c == '9')
					C[x] = 9;
				else
				{
					cout << " ERROR : SET : CONVERTER : Out Of Range" << endl;
					return 0;
				}
			}
			else
			{
				cout << " ERROR : SET : CONVERTER : Out Of Range" << endl;
				return 0;
			}
			x++;
		}
		y = C[0] * 100 + C[1] * 10 + C[2];
		return y;
	}
	static unsigned int ConvertToUnsigned_general(std::string str)
	{
		unsigned y = 0;
		std::vector<unsigned> C;
		for (char c : str)
		{
			if (c == '0')
			{
				if (C.size() > 0) C.push_back(0);
			}
			else if (c == '1')
				C.push_back(1);
			else if (c == '2')
				C.push_back(2);
			else if (c == '3')
				C.push_back(3);
			else if (c == '4')
				C.push_back(4);
			else if (c == '5')
				C.push_back(5);
			else if (c == '6')
				C.push_back(6);
			else if (c == '7')
				C.push_back(7);
			else if (c == '8')
				C.push_back(8);
			else if (c == '9')
				C.push_back(9);
		}
		double C_size = static_cast<double>(C.size() - 1);
		for (auto p : C)
		{
			y = y + p * pow(10, C_size);
			C_size--;
		}
		return y;
	}
	static double ConvertToDouble(std::string str)
	{
		string mantessa, exponenet;
		std::array<std::string, 2>Parts;
		std::array<double, 2>Dici_Parts;
		vector<double>Number;
		double mant, expo;
		size_t position_e = str.find_first_of("e", 0);
		size_t position_E = str.find_first_of("E", 0);
		size_t e;

		if (position_e != std::string::npos && position_E == std::string::npos)
		{
			e = position_e;
		}
		else if (position_e == std::string::npos && position_E != std::string::npos)
		{
			e = position_E;
		}
		else
		{
			e = str.size();
		}
		if (e < str.size() - 1)
		{
			mantessa = str.substr(0, e);
			exponenet = str.substr(e + 1, str.size() - e);
		}
		else if (e <= str.size())
		{
			mantessa = str.substr(0, e);
			exponenet = "0";
		}
		else
		{
			return 0.0;
		}
		//cout << " Matessa : " << mantessa << " Exponenet : " << exponenet << endl;
		Parts[0] = mantessa;
		Parts[1] = exponenet;
		std::string before, after;
		double sign = 1.0;
		size_t dicimal_point = 0;

		for (auto p : Parts)
		{
			if (p.size() > 0)
			{
				sign = 1.0;
				if (p.at(0) == '-')
				{
					sign = -1;
					p.erase(0, 1);
				}

				dicimal_point = p.find_first_of('.', 0);
				before = {};
				after = {};
				if (dicimal_point != std::string::npos)//  && dicimal_point < str.size() - 1)
				{
					after = p.substr(dicimal_point + 1, p.size() - dicimal_point);
					before = p.substr(0, dicimal_point);
					Dici_Parts[0] = static_cast<double>(ConvertToUnsigned_general(before));
					Dici_Parts[1] = static_cast<double>(ConvertToUnsigned_general(after)) / pow(10, after.size());
				}
				else
				{
					after = "";
					before = p;
					Dici_Parts[0] = static_cast<double>(ConvertToUnsigned_general(before));
					Dici_Parts[1] = 0.0;
				}
				Number.push_back((Dici_Parts[0] + Dici_Parts[1]) * sign);
			}
			else
			{
				Number.push_back(0.0);
			}
		}
		if (Number.size() > 1)
		{
			return Number.at(0) * pow(10, Number.at(1));
		}
		else if (Number.size() > 0)
		{
			return Number.at(0);
		}
		else
		{
			return 0.0;
		}
	}
	static std::string ConvertToString(unsigned x)
	{
		std::string result{ "" };
		int y = x; int z{ 0 };
		if (y == 0)
			return "0";
		else {
			while (y > 0)
			{
				z = y % (10);
				if (z == 0)result = "0" + result;
				else if (z == 1)result = "1" + result;
				else if (z == 2)result = "2" + result;
				else if (z == 3)result = "3" + result;
				else if (z == 4)result = "4" + result;
				else if (z == 5)result = "5" + result;
				else if (z == 6)result = "6" + result;
				else if (z == 7)result = "7" + result;
				else if (z == 8)result = "8" + result;
				else if (z == 9)result = "9" + result;
				y = static_cast<unsigned> (floor(static_cast<float>(y) / 10));
			}
			return result;
		}
	}
	static void WiteDoubleVectorToFile(std::string file_out, std::vector<double> data)
	{
		// this function writes the vector to a file
		std::ofstream out{ file_out, std::ios_base::out | std::ios_base::trunc };
		std::ostream_iterator<string> out_iter2{ out, "" };
		vector<std::string>row;
		std::stringstream converter;
		std::string d;
		for (double r : data)
		{
			converter << r; converter >> d; converter.clear();
			row.push_back(d);
			row.push_back("\t");
			std::copy(std::begin(row), std::end(row), out_iter2);
			out_iter2 = "\n";
			row.clear();
		}

	}
	static double CalculateNoisePower(double BandWidth)
	{
		double K = 1.38064852e-23;
		return NoisePower = K * Temperature * BandWidth;
	}
	static std::string GetWord(std::string source, size_t position)
	{
		if (source.size() > position)
		{
			string s = source;
			vector<string>words;
			size_t i{ 0 };
			while (s.size() > 0)
			{
				i = s.find_first_of(" ");
				if (i >= s.size()) {
					words.push_back(s); s.erase(0,s.size());
				}
				else if (i > 0 && i < s.size()) { words.push_back(s.substr(0, i)); s.erase(0, i + 1); }
				else s.erase(0, i + 1);
			}
			if (words.size() > position)return words.at(position);
		}
		cout << " Error in conversion GetWord at position: "<<position <<" from string :"+ source<< endl;
		return "";
	}
	static std::string GetTestCase()
	{
		return (Test_Case_str);
	}
	static size_t Permute(size_t n,size_t s)
	{
		float N = static_cast<float>(n);
		float S = static_cast<float>(s);
		float L{ 0 };
		float M{ 0 };
		float T{ 0 };
		float R{ 0 };
		float Limit = (((S / 10) - 100) * 11) + 1 + 100;
		size_t Result{ 0 };
		if (n > 100)
		{
			L = (N - 100) / 11;
			M = floor(L);
			T = (M * 10) + 1000;
			R = round(((L - M) * 11) - 1);
			if (N<=Limit)//T < S || (T==S && R==0))
			{
				if (R < 0)
				{
					Result = static_cast<size_t>(M+100);
				}
				else
				{
					Result = static_cast<size_t>(T + R);
				}
			}
			else Result = static_cast<size_t>(N-(S-1000)-1);
		}
		else
			Result = n;
	//	cout << " " << N << " " << S << " " << L << " " << M << " " << (L - M) <<" "<< R << " "<< T << endl;
	//	cout << " " << n << " IS PERMUTED TO :" << Result << endl;
		return Result;

	}
	static double Round(double n,float d)
	{
		double value = static_cast<int>((n) * pow(10.0,d) + .5);
			return static_cast<double>(value / pow(10.0, d));
	}
	static size_t RePermute(size_t n, size_t s)
	{
		float N = static_cast<float>(n);
		float S = static_cast<float>(s);
		
		size_t Result{ 0 };
		if (n > 100 && n <= static_cast<size_t>(S / 10))
		{
			Result = (n - 100) * 10 + n;
		}
		else if (n <= 100)
			Result = n;
		else if (n >= 1000)
		{
			float range = N - 1000;
			size_t tens = static_cast<size_t>(floor(range / 10));
			Result = n - 900 + tens+1;
		}
		else
			Result = n+(s-999);
		//	cout << " " << N << " " << S << " " << L << " " << M << " " << (L - M) <<" "<< R << " "<< T << endl;
		//	cout << " " << n << " IS PERMUTED TO :" << Result << endl;
		return Result;

	}
	static float RoundAngles(angle_unit unit, float angle, size_t round_digits)
	{
		float pi;
		switch (unit)
		{
		case RAD:
			pi = 22 / 7;
			break;
		case DEG:
			pi = 180;
			angle = angle * (180 * 7 / 22);
			break;
		default:
			break;
		}
		while (angle > 2*pi)
		{
			angle = angle - (2 * pi);
		}
		while (angle < 0)
		{
			angle = angle + (2 * pi);
		}
		float fraction = pow(10, round_digits);
		angle = angle * fraction;
		return (std::round(angle)) / fraction;
	}
	static void SetRESULTSFolder(EXPOSURE check)
	{
		switch (check)
		{
		case LOS:
			Tools::RESULTSFolder = "D:/RESULTS_2/LOS/";//"D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/RESULTS/LOS/";
			break;
		case NLOS:
			Tools::RESULTSFolder = "D:/RESULTS_2/NLOS/";//"D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/RESULTS/NLOS/";
			break;
		case ALL:
			Tools::RESULTSFolder = "D:/RESULTS_2/ALL/";
			break;
		}
	}
	static double ModelChannelGain(double spacing, double frequency, double phi_array, double departure_phi, double departure_theta)
	{
		double psi;
		psi = (2.0 * (22.0 / 7.0) * spacing) * (sin(phi_array) / (sin(departure_phi) * sin(departure_theta)));
		return psi;
	}
	public:
		static double CarrierFrequency;
		static double NoisePower;
		static double Temperature;
		static double Samples_Count;
		static float  Test_Case;
		static float  Spacing;
		static float  Phi_array;
		static double Transmitter_power;
		static float Transmitter_height;
		static string Test_Case_str;
		static string RESULTSFolder;
		static version WirelessInsiteVersion;
		static version WirelessInsiteVersion_DOD;
		static std::filesystem::path Cir_Folder;
		static std::filesystem::path StudyArea_Folder;
};

