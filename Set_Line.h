#pragma once
#include<string>
#include<complex>
#include<iostream>
#include<sstream>
#include<matrix.h>
#include"WirelessPower.h"
#include"WirelessInsiteFiles.h"
#include"Ray.h"
enum class SHOW_HEADER { HEADER_ON, HEADER_OFF };
enum class PROPERITIES { EMPTY_PROP, TX_SET, RX_SET, TX_POINT, RX_POINT, DIRECT_DISTANCE, RADIAL_DISTANCE, HEIGHT, THETA, PHI, POWER_dBm, MEAN_ARRIVAL_TIME};
using namespace std;

struct POSITION {
	float Distance;
	float Height;
	float Theta;
	float Phi;
	float R;
	float X;
	float Y;
	float Z;

	POSITION()
	{
		Distance = 0.0;
		Height = 0.0;
		Theta = 0.0;
		Phi = 0.0;
		R = 0.0;
		X = 0.0;
		Y = 0.0;
		Z = 0.0;

	}
	POSITION(
		float distance,
		float height,
		float theta,
		float phi,
		float r,
		float x,
		float y,
		float z)
	{
		Distance = distance;
		Height = height;
		Theta = theta;
		Phi = phi;
		R = r;
		X = x;
		Y = y;
		Z = z;
	}
	void Show()
	{
		cout << " POSITION TX-RX  \n\t DISTANCE      : " << setw(10) << Distance << " METERS\n\t HEIGHT        : " << setw(10) << Height << " METERS\n\t ANGLE_ELEV    : " << setw(10) << Theta << "   RADS\n\t ANGLE_AZIMUTH : " << setw(10) << Phi << "   RADS\n\t R             : " << setw(10) << R << " METERS" << endl;
	}
	bool write(std::ofstream& ofile)const
	{
		ofile.write(reinterpret_cast<const char*>(&Distance), sizeof(float));
		ofile.write(reinterpret_cast<const char*>(&Height), sizeof(float));
		ofile.write(reinterpret_cast<const char*>(&Theta), sizeof(float));
		ofile.write(reinterpret_cast<const char*>(&Phi), sizeof(float));
		ofile.write(reinterpret_cast<const char*>(&R), sizeof(float));
		ofile.write(reinterpret_cast<const char*>(&X), sizeof(float));
		ofile.write(reinterpret_cast<const char*>(&Y), sizeof(float));
		ofile.write(reinterpret_cast<const char*>(&Z), sizeof(float));
		return !ofile.fail();
	}
	bool read(std::ifstream& ifile)
	{
		ifile.read(reinterpret_cast<char*>(&Distance), sizeof(float));
		ifile.read(reinterpret_cast<char*>(&Height), sizeof(float));
		ifile.read(reinterpret_cast<char*>(&Theta), sizeof(float));
		ifile.read(reinterpret_cast<char*>(&Phi), sizeof(float));
		ifile.read(reinterpret_cast<char*>(&R), sizeof(float));
		ifile.read(reinterpret_cast<char*>(&X), sizeof(float));
		ifile.read(reinterpret_cast<char*>(&Y), sizeof(float));
		ifile.read(reinterpret_cast<char*>(&Z), sizeof(float));
		return !ifile.fail();
	}
};

struct PATHS
{
	PATHS()
	{
		TX_ELEMENT = 0;
		RX_ELEMENT = 0;
		KEY = "";
		EXPO = NLOS;
		DELAY_SPREAD = 0.0;
		K_FACTOR = 0.0;
	}
	PATHS(unsigned tx_ele,unsigned rx_ele)
	{
		TX_ELEMENT= tx_ele;
		RX_ELEMENT= rx_ele;
		KEY = "";
		EXPO = NLOS;
		DELAY_SPREAD = 0.0;
		K_FACTOR = 0.0;
	}
	void SHOW()
	{
		cout << " *************************** " << endl;
		cout << " TX_ELEMENT : " << TX_ELEMENT << endl;
		cout << " RX_ELEMENT : " << RX_ELEMENT << endl;
		for (auto& r : RAYS)
		{
			cout << " KEY                   :" << KEY << setw(20);
			cout << " PATH ID				:" << r.Path_ID <<setw(20);
			cout << " SOURCE ID				:" << r.Source_ID << setw(20);
			cout << " POWER(W)				:" << r.Power << setw(20);
			cout << " PHSE(RAD)				:" << r.Phase << setw(20);
			cout << " ARRIVAL TIME(S)		:" << r.Arrival_Time << setw(20);
			cout << " ARRIVAL PHI(RAD)		:" << r.Arrival.Phi << setw(20);
			cout << " ARRIVAL THETA(RAD)	:" << r.Arrival.Theta << setw(20);
			cout << " DEPARTURE PHI(RAD)	:" << r.Departure.Phi << setw(20);
			cout << " DEPARTURE THETA(RAD)	:" << r.Departure.Theta << setw(20);
			cout << " DEALY SPREAD(S)	    :" << DELAY_SPREAD<< endl;
			cout << " K FACTOR	            :" << K_FACTOR << endl;
		}
		cout << " *************************** " << endl;
	}
	void SHOWPATH()
	{
		cout << " *************************** " << endl;
		cout << " KEY        : " << KEY << endl;
		cout << " TX_ELEMENT : " << TX_ELEMENT << endl;
		cout << " RX_ELEMENT : " << RX_ELEMENT << endl;
		cout << " SPACING    : " << Environment::Spacing << endl;
		cout << " Array AZIMUTH ANGLE : " << Environment::Phi_array << endl;
		cout << " DEALY SPREAD(S)	  :" << DELAY_SPREAD << endl;
		cout << " K FACTOR	          :" << K_FACTOR << endl;

		cout << " PATH ID" << setw(20);
		cout << " SOURCE ID" << setw(20);
		cout << " POWER(W)" << setw(20);
		cout << " PHSE(DEG)" << setw(20);
		cout << " CALCULATED PHSE(DEG)" << setw(20);
		cout << " ARRIVAL TIME(S)" << setw(20);
		cout << " ARRIVAL PHI(RAD)" << setw(20);
		cout << " ARRIVAL THETA(RAD)" << setw(20);
		cout << " DEPARTURE PHI(RAD)" << setw(20);
		cout << " DEPARTURE THETA(RAD)" << endl;
		
		for (auto r : RAYS)
		{
			r.ShowRay();
		}
		cout << " *************************** " << endl;
	}
	void SHOWPATHS(SHOW_HEADER h=SHOW_HEADER::HEADER_OFF)
	{
		// Print a path as a line, with only IDs , power and geometry
		if(h==SHOW_HEADER::HEADER_ON)cout << setw(10) << "PATH ID" << setw(10) << "SOURCE ID" << setw(20) << "POWER(dBm)" << setw(20) << "PHASE(RAD)" << setw(20) << "ARRIVAL TIME(S)" << setw(25) << "ARRIVAL AZIMUTH(DEG)" << setw(25) << "ARRIVAL ZENITH(DEG)" << setw(25) << "DEPARTURE AZIMUTH(DEG)" << setw(25) << "DEPARTURE ZENITH(DEG)" << endl;
		for(auto& r:RAYS)
			cout << setw(10) << r.Path_ID << setw(10) << r.Source_ID << setw(20) << Tools::Round(20*log10(r.Power*1000),2) << setw(20) << Tools::Round(r.Phase,2) << setw(20) << Tools::Round2(r.Arrival_Time,2) << setw(25) << Tools::Round((r.Arrival.Phi*180*7/22),2) << setw(25) << Tools::Round((r.Arrival.Theta * 180 * 7 / 22), 2) << setw(25) << Tools::Round((r.Departure.Phi * 180 * 7 / 22), 2) << setw(25) << Tools::Round((r.Departure.Theta * 180 * 7 / 22), 2) << endl;
	}
	void SETKEY(std::string key)
	{
		KEY = key;
	}
	bool FOUND(unsigned tx_ele, unsigned rx_ele)
	{
		if (TX_ELEMENT == tx_ele && RX_ELEMENT == rx_ele)
			return true;
		else
			return false;
	}
	void SETDELAYSPREAD()
	{
		double PR{ 0 }, PT{ 0 }, TM{ 0.0 }, TI{ 0.0 };//total power in paths without phase info
		for (auto& r : RAYS)
		{
			PR = PR + r.Power;
			PT = PT + (r.Power * r.Arrival_Time);
		}
		if (PR > 0)
		{
			TM = PT / PR;
			for (auto& r : RAYS)
			{
				TI = TI + (pow(r.Arrival_Time - TM, 2) * r.Power);
			}
			if ((TI / PR) < 0)
				cout << " ERROR in POWER VALUE - NEGATIVE " << endl;
			else
				DELAY_SPREAD = sqrt(TI / PR);
		}
		else
			DELAY_SPREAD = 0.0;
	}
	UnitVectors DirectionUnitVectors() // Mean arrrival and departure directin unit vectors
	{
		size_t N = RAYS.size();
		valarray<float> Arrival_phi(N);
		valarray<float> Arrival_theta(N);
		valarray<float> Departure_phi(N);
		valarray<float> Departure_theta(N);
		valarray<float> Delay(N);
		size_t i{ 0 };
		for (auto& p : RAYS)
		{
			Arrival_phi[i] = p.Arrival.Phi;
			Arrival_theta[i] = p.Arrival.Theta;
			Departure_phi[i]= p.Departure.Phi;
			Departure_theta[i] = p.Departure.Theta;
			Delay[i] = p.Arrival_Time;
			i++;
		}
		float mean_Arrival_phi = Arrival_phi.sum() / N;
		float mean_Arrival_theta = Arrival_theta.sum() / N;
		float mean_Departure_phi = Departure_phi.sum() / N;
		float mean_Departure_theta = Departure_theta.sum() / N;
		
		UnitVectors a_v;
		a_v.Arrival_UV[0] = cos(mean_Arrival_phi) * sin(mean_Arrival_theta);
		a_v.Arrival_UV[1] = sin(mean_Arrival_phi) * sin(mean_Arrival_theta);
		a_v.Arrival_UV[2] =                         cos(mean_Arrival_theta);

		a_v.Departure_UV[0] = cos(mean_Departure_phi) * sin(mean_Departure_theta);
		a_v.Departure_UV[1] = sin(mean_Departure_phi) * sin(mean_Departure_theta);
		a_v.Departure_UV[2] = cos(mean_Departure_theta);

		a_v.Delay = Delay.sum() / N;
	}
	DirectionStatistics Statistics()
	{
		DirectionStatistics stat;
		size_t N = RAYS.size();
		valarray<float> Arrival_phi(N);
		valarray<float> Arrival_theta(N);
		valarray<float> Departure_phi(N);
		valarray<float> Departure_theta(N);
		valarray<float> Delay(N);
		size_t i{ 0 };
		for (auto& p : RAYS)
		{
			Arrival_phi[i] = p.Arrival.Phi;
			Arrival_theta[i] = p.Arrival.Theta;
			Departure_phi[i] = p.Departure.Phi;
			Departure_theta[i] = p.Departure.Theta;
			Delay[i] = p.Arrival_Time;
			if (Delay[i] < 0)
			{
				cout << " at i :" << i << "\t" << Delay[i] << endl;
				cout << p.Arrival_Time << endl;
				p.Show();
			}
			i++;
		}
		float mean_Arrival_phi = 0;
		float mean_Arrival_theta = 0;
		float mean_Departure_phi = 0;
		float mean_Departure_theta = 0;
		float mean_Delay = 0.0;
		if (N > 0)
		{
			mean_Arrival_phi = Arrival_phi.sum() / static_cast<float>(N);
			mean_Arrival_theta = Arrival_theta.sum() / static_cast<float>(N);
			mean_Departure_phi = Departure_phi.sum() / static_cast<float>(N);
			mean_Departure_theta = Departure_theta.sum() / static_cast<float>(N);
			mean_Delay = Delay.sum() / static_cast<float>(N); if(mean_Delay<0)cout <<" Mean Delay:"<< mean_Delay << endl;
			stat.Arrival_AngularSpread.Phi = Arrival_phi.max() - Arrival_phi.min();
			stat.Arrival_AngularSpread.Theta = Arrival_theta.max() - Arrival_theta.min();
			stat.Departure_AngularSpread.Phi = Departure_phi.max() - Departure_phi.min();
			stat.Departure_AngularSpread.Theta = Departure_theta.max() - Departure_theta.min();
			stat.Arrival_Mean.Phi = mean_Arrival_phi;
			stat.Arrival_Mean.Theta = mean_Arrival_theta;
			stat.Departure_Mean.Phi = mean_Departure_phi;
			stat.Departure_Mean.Theta = mean_Departure_theta;
			stat.Arrival_Std.Phi = Tools::Std(Arrival_phi);
			stat.Arrival_Std.Theta = Tools::Std(Arrival_theta);
			stat.Departure_Std.Phi = Tools::Std(Departure_phi);
			stat.Departure_Std.Theta = Tools::Std(Departure_theta);
			stat.Delay_Mean = mean_Delay;// because DELAY_SPREAD is power dependant.
			// add the std if needed
		}
		
		
		return stat;
	}
	bool write(std::ofstream& ofile)
	{
		bool flag{ true };
		ofile.write(reinterpret_cast<const char*>(&TX_ELEMENT), sizeof(unsigned));
		ofile.write(reinterpret_cast<const char*>(&RX_ELEMENT), sizeof(unsigned));
		unsigned size_1 = KEY.size();
		ofile.write(reinterpret_cast<const char*>(&size_1), sizeof(unsigned));
		ofile.write(reinterpret_cast<const char*>(&KEY[0]), size_1*sizeof(char));
		unsigned size_2 = RAYS.size();
		ofile.write(reinterpret_cast<const char*>(&size_2), sizeof(unsigned));
		for (auto& r : RAYS)
			flag=flag* r.write(ofile);
		ofile.write(reinterpret_cast<const char*>(&EXPO), sizeof(EXPOSURE));
		ofile.write(reinterpret_cast<const char*>(&DELAY_SPREAD), sizeof(double));
		ofile.write(reinterpret_cast<const char*>(&K_FACTOR), sizeof(double));
		return flag * !ofile.fail();
	}
	bool read(std::ifstream& ifile)
	{
		bool flag{ true };
		ifile.read(reinterpret_cast<char*>(&TX_ELEMENT), sizeof(unsigned));
		ifile.read(reinterpret_cast<char*>(&RX_ELEMENT), sizeof(unsigned));
		unsigned size_1 = 0;
		ifile.read(reinterpret_cast<char*>(&size_1), sizeof(unsigned));
		string buffer; buffer.resize(size_1);
		ifile.read(reinterpret_cast<char*>(&buffer[0]), size_1 * sizeof(char));
		KEY = buffer;
		unsigned size_2 = 0;
		ifile.read(reinterpret_cast<char*>(&size_2), sizeof(unsigned));
		this->RAYS.clear();
		
		for (size_t i = 0; i < size_2; i++)
		{
			Ray ray;
			flag = flag * ray.read(ifile);
			RAYS.push_back(ray);
		}
		ifile.read(reinterpret_cast<char*>(&EXPO), sizeof(EXPOSURE));
		ifile.read(reinterpret_cast<char*>(&DELAY_SPREAD), sizeof(double));
		ifile.read(reinterpret_cast<char*>(&K_FACTOR), sizeof(double));
		return flag *!ifile.fail();
	}

	unsigned TX_ELEMENT;
	unsigned RX_ELEMENT;
	std::string KEY;
	std::vector<Ray> RAYS;
	EXPOSURE EXPO;
	double DELAY_SPREAD;
	double K_FACTOR; //The ration between the Los power and the average NLOS power rays 
};
class Set_Line
{
public:
	Set_Line() = default;
	Set_Line(unsigned  t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point)
	{
		Transmitter_Set		= t_set;
		Receiver_Set		= r_set;
		Transmitter_Point	= t_point;
		Receiver_Point		= r_point;
		DirectDistance = 0;
		RadialDistance = 0;
		ElevationAngle = 0;
		AzimuthAngle = 0;
		std::stringstream converter;
		converter << t_set<< r_set<< t_point<< r_point; converter >> this->Key;
		Expose = NON;
	}
	Set_Line(unsigned  t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned tx_ele, unsigned rx_ele,std::vector<Ray>& pathes)
	{
		Transmitter_Set = t_set;
		Receiver_Set = r_set;
		Transmitter_Point = t_point;
		Receiver_Point = r_point;
		DirectDistance = 0;
		RadialDistance = 0;
		ElevationAngle = 0;
		AzimuthAngle = 0;
		std::stringstream converter;
		converter << t_set << r_set << t_point << r_point; converter >> this->Key; converter.clear();
		std::string key1, key;
		converter << tx_ele << rx_ele; converter >> key1;
		key = this->Key + key1;
		PATHS P(tx_ele, rx_ele);
		for (auto& p : pathes)
		{
			P.RAYS.push_back(p);
		}
		P.SETKEY(key);
		this->Pathes.push_back(P);
		Expose = NON;
	}
	void SetPathes(unsigned  t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned tx_ele, unsigned rx_ele, std::vector<Ray> pathes)
	{
		std::string key1,key;
		std::stringstream converter;
		converter << tx_ele << rx_ele ; converter >> key1;
		key = this->Key + key1;
		if(this->Transmitter_Set == t_set)
			if(this->Transmitter_Point== t_point)
				if(this->Receiver_Set==r_set)
					if (this->Receiver_Point == r_point)
					{
						for (auto& p : this->Pathes)
						{
							if (p.FOUND(tx_ele, rx_ele)) {
								p.RAYS.empty();
								cout << " FOUND A RAY WITH TX ELE:" << tx_ele << " AND RX_ELE:" << rx_ele << endl;
								cout << " THAT SHOULDN'T HAVE HAPPENED" << endl;
								return;
							}
						}
						//// Add
						PATHS P(tx_ele, rx_ele); 
						for (auto& p : pathes)
						{
							P.RAYS.push_back(p);
						}
						P.SETKEY(key);
						this->Pathes.push_back(P);
					}
	}
	double Mean_Arrival_Time_All_elements()
	{
		double sum{ 0.0 };
		for (auto& p : this->Pathes)
			sum=sum+p.Statistics().Delay_Mean;
		if (this->Pathes.size() > 1)
			return sum / static_cast<double>(this->Pathes.size());
		else
			return sum;
	}
	PATHS& GetPathes(unsigned tx_ele, unsigned rx_ele)
	{
		PATHS Nothing;
		for (auto& p : this->Pathes)
		{
			if (p.FOUND(tx_ele, rx_ele)) {
				return (p);
			}
		}
		cout << " PATHES ATTACHED to TX_ELE: " << tx_ele << " and RX_ELE: " << rx_ele << " ARE NOT FOUND " << endl;
		return Nothing;
	}
	double GetPower()
	{
		return this->Power.Rceiver_Average_Power();
	}
	void SetDelaySpread()
	{
		for (auto& p : this->Pathes)p.SETDELAYSPREAD();
	}
	void SetKFactor() // sets the K factor for each element in a point
	{
		double Los_Power{ 0 }, Nlos_power_sum{ 0 };
		for (auto& p : this->Pathes)
		{
			if (p.EXPO == EXPOSURE::LOS)
			{
				if (p.RAYS.size() > 1) //has more than the LOS Ray
				{
					Los_Power = p.RAYS.at(0).Power;
					if (Los_Power > 0)
					{
						Nlos_power_sum = 0.0;
						for (auto& r : p.RAYS)
						{
							Nlos_power_sum = Nlos_power_sum + r.Power;
						}
						Nlos_power_sum = (Nlos_power_sum - Los_Power) / (p.RAYS.size() - 1);
						p.K_FACTOR = Los_Power / Nlos_power_sum;
					}
					else
					{
						p.K_FACTOR = 0.0;
					}
				}
				else
					p.K_FACTOR = -1;// NON Applicabale;
			}
			else
				p.K_FACTOR = 0.0;
		}
	}
	EXPOSURE SetExposure()
	{
		bool goforward = false;
		for (auto& p : this->Pathes)
		{
			if (p.RAYS.size() > 0)
			{
				goforward = true;
				break;
			}
		}

		if (!goforward)
		{
			this->Expose = NON;
			return NON;
		}

		size_t LOS_Path_ID{ 1 };
		switch (WirelessInsiteFiles::WirelessInsiteVersion)
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
		for (auto& p : this->Pathes)
		{
			p.EXPO = NON;
			for (auto& r : p.RAYS)
			{
				if (r.Path_ID == LOS_Path_ID)
				{
					p.EXPO = LOS;
					break;
				}
				else if (r.Path_ID != -1)
				{
					p.EXPO = NLOS;
				}
				else if (r.Path_ID == -1)//SISO
				{
					if (r.Interactions == 0)
					{
						p.EXPO = LOS;
						break;
					}
					else if (r.Interactions != -1)
					{
						p.EXPO = NLOS;
					}
					else
					{
						//	p.EXPO = NON;
						//	break;
					}
				}
			}
		}
		for (auto& p : this->Pathes)
		{
			if (p.EXPO == LOS)
			{
				this->Expose = LOS;
				return LOS;
			}
		}
		for (auto& p : this->Pathes)
			if (p.EXPO == NLOS)
			{
				this->Expose = NLOS;
				return NLOS;
			}
		this->Expose = NON;
		return NON;

	}
	static std::string PrintExposure(EXPOSURE expose)
	{
		switch (expose)
		{
		case EXPOSURE::ALL:
			return "ALL";
		case EXPOSURE::LOS:
			return "LOS";
		case EXPOSURE::NLOS:
			return "NLOS";
		case EXPOSURE::NON:
			return "NON";
		}
	}
	void Show()
	{
		cout << endl;
		cout << "    ____________________________ START LINK _________________________"<<endl;
		
		cout << " \t NUMBER OF TRANSMITTER ELEMENTS IN THE TRANSMITTER ARRAY : " << M.Rows_Count << endl;
		cout << " \t NUMBER OF RECEIVER    ELEMENTS IN THE RECEIVER    ARRAY : " << M.Columns_Count << endl;
		std::cout << " KEY :" << this->Key << endl;
		std::cout << " TRANSMITTER SET	: " << Transmitter_Set << endl;
		std::cout << " RECEIVER    SET	: " << Receiver_Set    << endl;
		std::cout << " TRANSMITTER  PT	: " << Transmitter_Point << endl;
		std::cout << " RECEIVER     PT	: " << Receiver_Point << endl;
		std::cout << " POWER			: " << endl; this->Power.PowerPhasor().Show(POLAR);
		std::cout << " POWER AT RX ELE	: " << endl; this->Power.Shrink().Show(POLAR);
		std::cout << " POWER FROM TX ELE: " << endl; this->Power.Shrink_Horizontal().Show(POLAR);
		std::cout << " POWER AVRAG AT RX: " << this->Power.Rceiver_Average_Power() << " WATTS  " << endl;
		std::cout << " EXPOSURE         : " << PrintExposure(Expose) << endl;
		std::cout << " DIRECT DISTANCE  : " << this->DirectDistance << endl;
		std::cout << " RADIAL DISTANCE  : " << this->RadialDistance << endl;
		std::cout << " ELEVATION ANGLE  : " << this->ElevationAngle<< endl;
		std::cout << " AZIMUTH ANGLE  : " << this->AzimuthAngle<< endl;
		this->RxPosition.Show();
		std::cout << " H                : "<< endl;
		this->M.Show(RECT);
		cout << "    _______________________________ END LINK ___________________________" << endl;
	}
	void ShowBrief()
	{
		cout << " AT DISTANCE " << this->RxPosition.Distance << " . AT PHI :" << this->RxPosition.Phi <<endl;
	}
	void ShowPower(size_t tx_element,size_t rx_element)
	{
		cout<<Power.GetItem(tx_element, rx_element)<<endl;
	}
	void ShowPathes(SHOW_HEADER h = SHOW_HEADER::HEADER_OFF)
	{
		if (h == SHOW_HEADER::HEADER_ON)cout << setw(10) << "PATH ID" << setw(10) << "SOURCE ID" << setw(20) << "POWER(dBm)" << setw(20) << "PHASE(RAD)" << setw(20) << "ARRIVAL TIME(S)" << setw(25) << "ARRIVAL AZIMUTH(DEG)" << setw(25) << "ARRIVAL ZENITH(DEG)" << setw(25) << "DEPARTURE AZIMUTH(DEG)" << setw(25) << "DEPARTURE ZENITH(DEG)" << endl;
		for (auto p : this->Pathes)
		{
			p.SHOWPATHS(SHOW_HEADER::HEADER_OFF);
		}
	}
	void ShowPathes(unsigned tx_ele, unsigned rx_ele)
	{
		for (auto p : this->Pathes)
		{
			if (p.FOUND(tx_ele, rx_ele))
			{
				p.SHOWPATH();
			}
		}
	}
	void ShowAllPathes()
	{
		for (auto p : this->Pathes)
			p.SHOWPATH();
	}
	
	bool CheckProperity(PROPERITIES properity, double max, double min=0.0)
	{
		switch (properity)
		{
		case PROPERITIES::EMPTY_PROP:
			return true;
			break;
		case PROPERITIES::TX_SET:
			if (static_cast<unsigned>(max) >= this->Transmitter_Set && static_cast<unsigned>(min) <= this->Transmitter_Set)return true;
			else
				return false;
			break;
		case PROPERITIES::RX_SET:
			if (static_cast<unsigned>(max) >= this->Receiver_Set && static_cast<unsigned>(min) <= this->Receiver_Set)return true;
			else
				return false;
			break;
		case PROPERITIES::TX_POINT:
			if (static_cast<unsigned>(max) >= this->Transmitter_Point && static_cast<unsigned>(min) <= this->Transmitter_Point)return true;
			else
				return false;
			break;
		case PROPERITIES::DIRECT_DISTANCE:
			if (static_cast<double>(max) >= this->RxPosition.Distance && static_cast<double>(min) <= this->RxPosition.Distance)return true;
			else
				return false;
			break;
		case PROPERITIES::RADIAL_DISTANCE:
			if (static_cast<double>(max) >= this->RxPosition.R && static_cast<double>(min) <= this->RxPosition.R)return true;
			else
				return false;
			break;
		case PROPERITIES::HEIGHT:
			if (static_cast<double>(max) >= this->RxPosition.Height && static_cast<double>(min) <= this->RxPosition.Height)return true;
			else
				return false;
			break;
		case PROPERITIES::THETA:
			if (static_cast<double>(max) >= this->RxPosition.Theta && static_cast<double>(min) <= this->RxPosition.Theta)return true;
			else
				return false;
			break;
		case PROPERITIES::PHI:
			if (static_cast<double>(max) >= this->RxPosition.Phi && static_cast<double>(min) <= this->RxPosition.Phi)return true;
			else
				return false;
			break;
		case PROPERITIES::POWER_dBm:
			if (static_cast<double>(max) >= this->Power.GetPower_dBm() && static_cast<double>(min) <= this->Power.GetPower_dBm())return true;
			else
				return false;
			break;
		case PROPERITIES::MEAN_ARRIVAL_TIME:
			if (static_cast<double>(max) >= this->Mean_Arrival_Time_All_elements() && static_cast<double>(min) <= this->Mean_Arrival_Time_All_elements())return true;
			else
				return false;
			break;
		}
	}
	bool write(std::ofstream& ofile)
	{
		bool flag{ true };
		unsigned size_1 = Key.size();
		ofile.write(reinterpret_cast<const char*>(&size_1), sizeof(unsigned));
		ofile.write(reinterpret_cast<const char*>(&Key[0]), size_1 * sizeof(char));
		ofile.write(reinterpret_cast<const char*>(&Transmitter_Set), sizeof(unsigned));
		ofile.write(reinterpret_cast<const char*>(&Receiver_Set), sizeof(unsigned));
		ofile.write(reinterpret_cast<const char*>(&Transmitter_Point), sizeof(unsigned));
		ofile.write(reinterpret_cast<const char*>(&Receiver_Point), sizeof(unsigned));
		ofile.write(reinterpret_cast<const char*>(&DirectDistance), sizeof(float));
		ofile.write(reinterpret_cast<const char*>(&RadialDistance), sizeof(float));
		ofile.write(reinterpret_cast<const char*>(&ElevationAngle), sizeof(float));
		ofile.write(reinterpret_cast<const char*>(&AzimuthAngle), sizeof(float));
		flag = flag * M.write(ofile);
		flag = flag * this->Q.write(ofile);
		flag = flag * this->RxPosition.write(ofile);
		flag = flag * this->TxPosition.write(ofile);
		flag = flag * this->Power.write(ofile);

		unsigned size_2 = Pathes.size();
		ofile.write(reinterpret_cast<const char*>(&size_2), sizeof(unsigned));
		for (auto& p : this->Pathes)
			flag=flag*p.write(ofile);
		ofile.write(reinterpret_cast<const char*>(&Expose), sizeof(EXPOSURE));
	
		return flag * !ofile.fail();
	}
	bool read(std::ifstream& ifile)
	{
		bool flag{ true };
		unsigned size_1 = 0;
		ifile.read(reinterpret_cast<char*>(&size_1), sizeof(unsigned));
		string buffer; buffer.resize(size_1);
		ifile.read(reinterpret_cast<char*>(&buffer[0]), size_1 * sizeof(char));
		Key = buffer;

		ifile.read(reinterpret_cast<char*>(&Transmitter_Set), sizeof(unsigned));
		ifile.read(reinterpret_cast<char*>(&Receiver_Set), sizeof(unsigned));
		ifile.read(reinterpret_cast<char*>(&Transmitter_Point), sizeof(unsigned));
		ifile.read(reinterpret_cast<char*>(&Receiver_Point), sizeof(unsigned));
		ifile.read(reinterpret_cast<char*>(&DirectDistance), sizeof(float));
		ifile.read(reinterpret_cast<char*>(&RadialDistance), sizeof(float));
		ifile.read(reinterpret_cast<char*>(&ElevationAngle), sizeof(float));
		ifile.read(reinterpret_cast<char*>(&AzimuthAngle), sizeof(float));
		flag = flag * M.read(ifile);
		flag = flag * this->Q.read(ifile);
		flag = flag * this->RxPosition.read(ifile);
		flag = flag * this->TxPosition.read(ifile);
		flag = flag * this->Power.read(ifile);
		
		unsigned size_2 = 0;
		ifile.read(reinterpret_cast<char*>(&size_2), sizeof(unsigned));
		
		this->Pathes.clear();
		for (size_t i = 0; i < size_2; i++)
		{
			PATHS path;
			flag = flag * path.read(ifile);
			this->Pathes.push_back(path);
		}
		ifile.read(reinterpret_cast<char*>(&Expose), sizeof(EXPOSURE));
		
		return !ifile.fail();
	}
public:
	std::string Key;
	unsigned  Transmitter_Set;
	unsigned  Receiver_Set;
	unsigned  Transmitter_Point;
	unsigned  Receiver_Point;
	float DirectDistance; // Distance between the transmitter point and the receiver point
	float RadialDistance; // The projection on th ehorizontal plan of th eline betwen th etransmitter and the receiver
	float ElevationAngle; // angel between the horizontal plane and the line between the transmitter and the receiver points
	float AzimuthAngle;//angle between the horizontal and the projection of the line between the transmitter and the receiver point as seen from the transmitter
	Complex_matrix M;
	Double_matrix Q;
	POSITION RxPosition;
	POSITION TxPosition;
	WirelessPower Power;
	std::vector<PATHS> Pathes;
	EXPOSURE Expose;
};


