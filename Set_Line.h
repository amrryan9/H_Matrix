#pragma once
#include<string>
#include<complex>
#include<iostream>
#include<sstream>
#include"MatrixMIMO.h"
#include"WirelessPower.h"
#include"Ray.h"
using namespace std;
struct POSITION { 
	double Distance;
	double Height;
	double Theta;
	double Phi;
	double R;
	float abs_Height;//
	float abs_Theta;//
	void Show()
	{
		cout<< " POSITION TX-RX   :\n\t DISTANCE      : "<<setw(10)<< Distance <<" METERS\n\t HEIGHT        : " << setw(10) << Height   <<" METERS\n\t ANGLE_ELEV    : " << setw(10) << Theta    <<"   RADS\n\t ANGLE_AZIMUTH : " << setw(10)<< Phi      <<"   RADS\n\t R" << setw(10) << R << "   METERS" << endl;
	}
	float X()
	{
		return (static_cast<float>(R * std::cos(Phi))+500.0);
	}
	float Y()
	{
		return (static_cast<float>(R * std::sin(Phi))+500.0);
	}
	float Z()
	{
		abs_Height = Tools::Transmitter_height - (std::abs(Height));
		return static_cast<float>(abs_Height);
	}
	float absTheta()
	{
		abs_Height = Tools::Transmitter_height - (std::abs(Height));
		abs_Theta = std::atan(R / abs_Height);
		return static_cast<float>(abs_Theta);
	}
	float absPhi()
	{
		return static_cast<float>(Phi);
	}
	float absDistance()
	{
		abs_Height = Tools::Transmitter_height - (std::abs(Height));
		return static_cast<float>(sqrt(pow(abs_Height,2.0)+pow(R,2.0)));
	}
	float DirectDistance()
	{
		return static_cast<float>(Distance);
	}
	float ElevationAngle()
	{
		return static_cast<float>(Theta);
	}
};
struct PATHS
{
	PATHS(unsigned tx_ele,unsigned rx_ele)
	{
		TX_ELEMENT= tx_ele;
		RX_ELEMENT= rx_ele;
		KEY = "";
		EXPO = NLOS;
	}
	void SHOW()
	{
		cout << " *************************** " << endl;
		cout << " TX_ELEMENT : " << TX_ELEMENT << endl;
		cout << " RX_ELEMENT : " << RX_ELEMENT << endl;
		/*
		cout << " PATH ID				:" ;
		cout << " SOURCE ID				:" ;
		cout << " POWER(W)				:" ;
		cout << " PHSE(RAD)				:" ;
		cout << " ARRIVAL TIME(S)		:" ;
		cout << " ARRIVAL PHI(RAD)		:" ;
		cout << " ARRIVAL THETA(RAD)	:" ;
		cout << " DEPARTURE PHI(RAD)	:" ;
		cout << " DEPARTURE THETA(RAD)	:" ;
		*/
		for (auto r : RAYS)
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
			cout << " DEPARTURE THETA(RAD)	:" << r.Departure.Theta << endl;
		}
		cout << " *************************** " << endl;
	}
	void SHOWPATH()
	{
		cout << " *************************** " << endl;
		cout << " TX_ELEMENT : " << TX_ELEMENT << endl;
		cout << " RX_ELEMENT : " << RX_ELEMENT << endl;
		cout << " SPACING : " << Tools::Spacing << endl;
		cout << " Array AZIMUTH ANGLE : " << Tools::Phi_array << endl;


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
	unsigned TX_ELEMENT;
	unsigned RX_ELEMENT;
	std::string KEY;
	std::vector<Ray> RAYS;
	EXPOSURE EXPO;
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
		std::stringstream converter;
		converter << t_set<< r_set<< t_point<< r_point; converter >> this->Key;

		Gd = 0;
		Gx = 0;
		Gy = 0;
		Gphi = 0;
		Gtheta = 0;
		GdGphi = 0;
		Capacity_Set_Flag = false;
	//	Permutation_Index = 0;
		Expose = NLOS;
	}
	Set_Line(unsigned  t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned tx_ele, unsigned rx_ele,std::vector<Ray> pathes)
	{
		Transmitter_Set = t_set;
		Receiver_Set = r_set;
		Transmitter_Point = t_point;
		Receiver_Point = r_point;
		std::stringstream converter;
		converter << t_set << r_set << t_point << r_point; converter >> this->Key; converter.clear();

		Gd = 0;
		Gx = 0;
		Gy = 0;
		Gphi = 0;
		Gtheta = 0;
		GdGphi = 0;
		Capacity_Set_Flag = false;
	//	Permutation_Index = 0;
		std::string key1, key;
		converter << tx_ele << rx_ele; converter >> key1;
		key = this->Key + key1;
		PATHS P(tx_ele, rx_ele);
		for (auto p : pathes)
		{
			P.RAYS.push_back(p);
		}
		P.SETKEY(key);
		this->Pathes.push_back(P);
		Expose = NLOS;
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
						for (auto p : this->Pathes)
						{
							if (p.FOUND(tx_ele, rx_ele)) {
								p.RAYS.empty();
								cout << " FOUND A RAY WITH TX ELE:" << tx_ele << " AND RX_ELE:" << rx_ele << endl;
								cout << " THAT SHOULDN'T HAVE HAPPENED" << endl;
								return;
							}
						}
						//// Add
				//		cout << "CREATE A RAY WITH TX ELE:" << tx_ele << " AND RX_ELE:" << rx_ele << endl;
						PATHS P(tx_ele, rx_ele); 
						for (auto p : pathes)
						{
							P.RAYS.push_back(p);
						}
						P.SETKEY(key);
						this->Pathes.push_back(P);
					//	P.SHOW();
					//	cout << " PATH ADDED" << endl;
					}
		
	}
	void SetCapacity()
	{
		if (this->IsValid())
		{
			MatrixMIMO<std::complex<double>> H = this->M;
			MatrixMIMO<std::complex<double>> H_SISO;
			MatrixMIMO<std::complex<double>> Power_Matrix;
			for (int i = 0; i < this->M.Rows_Count; i++)Power_Matrix.AddItem(i, i, std::complex<double>(Tools::Transmitter_power, 0));// Power_Matrix.Show();
			H.Transposed();
			H_SISO.AddItem(0, 0, H.GetAverage_All_Items());//H.GetItem(0, 0)
			double Noise_Power = Tools::NoisePower; // Watt , for 300 K  put it -114 dbm 
			double Receiver_Elements = static_cast<double>(this->M.Columns_Count);
			double Transmitter_Elements = static_cast<double>(this->M.Rows_Count);
			double Transmitter_Elements_SISO = 1;
			
		
			
		
			MatrixMIMO<std::complex<double>> I_R = H.GetIdentity_Row();
			MatrixMIMO<std::complex<double>> I_R_SISO = H_SISO.GetIdentity_Row();
			MatrixMIMO<std::complex<double>> I_C = H.GetIdentity_Column();
			MatrixMIMO<std::complex<double>> P_T = this->Power.Transmitter_Diagonal();
			MatrixMIMO<std::complex<double>> P_R = this->Power.Rceiver_Diagonal();	  
			
			////////////// RESULTS_3 ///////////////////
	//		double SNR = this->Power.Rceiver_Average_Power() / Noise_Power;	// 
	//		double SNR_SISO = this->Power.Power(0, 0) * Transmitter_Elements / Noise_Power; // multiplied by transmitter and receie elements //Receiver_Elements*  //
	//		MatrixMIMO<std::complex<double>> C_3 = (I_R + H *  H.GetConjugateTransposed() * SNR * (1 / Transmitter_Elements));//bits/sec/Hz   // //Power_Matrix *
			////////////// RESULTS_2 ///////////////////
			double SNR = 1 / Noise_Power;	// this->Power.Rceiver_Average_Power()
			double SNR_SISO = Tools::Transmitter_power * Transmitter_Elements / Noise_Power; // multiplied by transmitter and receie elements //Receiver_Elements*  //this->Power.Power(0,0) 
			MatrixMIMO<std::complex<double>> C_3 = (I_R + H * Power_Matrix * H.GetConjugateTransposed() * SNR);//bits/sec/Hz   // * (1 / Transmitter_Elements)
			/////////////////////////////////////
			MatrixMIMO<std::complex<double>> C_3_SISO = (I_R_SISO + H_SISO * H_SISO.GetConjugateTransposed() * SNR_SISO );//bits/sec/Hz //* (1 / Transmitter_Elements_SISO)
			this->Capacity = log2(abs(C_3.GetDeterminant())); 
			this->Capacity_SISO = log2(abs(C_3_SISO.GetDeterminant()));
		//	this->Capacity_SISO = log2(abs((1 + (SNR_SISO * pow(abs(H.GetItem(0, 0)), 2) / 1.0))));// Transmitter_Elements))));
			// Write into a file
			this->Capacity_Set_Flag = true;
		}
		else this->Capacity = 0.0;
	}
	void GetCapacity(std::vector<double>& capacity_array)
	{
		SetCapacity();
		if (this->IsValid())capacity_array.push_back(this->Capacity);  // Only write valid ones
	}
	void GetCapacity(std::vector<double>& capacity_array , std::vector<double>& capacity_array_siso)
	{
		SetCapacity();
		if (this->IsValid()) {
			capacity_array.push_back(this->Capacity);  // Only write valid ones
			capacity_array_siso.push_back(this->Capacity_SISO);  // Only write valid ones
		}
	}
	double GetCapacity()
	{
		if(!Capacity_Set_Flag)SetCapacity(); return this->Capacity;
	}
	double GetCapacitySISO()
	{
		if (!Capacity_Set_Flag)SetCapacity();
		 return this->Capacity_SISO;
	}  
	bool GetPathes(unsigned  t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned tx_ele, unsigned rx_ele, std::vector<Ray>* p_rays)
	{
		vector<Ray> Nothing;
		if (this->Transmitter_Set == t_set)
			if (this->Transmitter_Point == t_point)
				if (this->Receiver_Set == r_set)
					if (this->Receiver_Point == r_point)
					{
						for (auto p : this->Pathes)
						{
							if (p.FOUND(tx_ele, rx_ele)) {
								cout << " PATHES ATTACHED to TX_ELE: "<<tx_ele<<" and RX_ELE: "<<rx_ele<<" ARE FOUND " << endl;
								p_rays = &(p.RAYS);
								return true;
							}
						}
					}
		return false;
	}
	double GetPower()
	{
		return this->Power.Rceiver_Average_Power();
	}
	void Show()
	{
		cout << endl;
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
		std::cout << " LINK CAPACITY    : " << this->Capacity                      << " B/S/HZ "        ;if (this->IsValid())std::cout << " :: LINK VALID ::" << endl; else std::cout << " :: LINK NOT VALID ::" << endl;
		std::cout << " EXPOSURE         : " << Expose << endl;
		this->Position.Show();
		this->M.Show(RECT);
	}
	void ShowBrief()
	{
		cout << " AT DISTANCE " << this->Position.Distance << " . AT PHI :" << this->Position.Phi <<endl;
	}
	void ShowPower(size_t tx_element,size_t rx_element)
	{
		cout<<Power.GetItem(tx_element, rx_element)<<endl;
	}
	void ShowValid()
	{
		if (M.IsValid())this->Show();
	}
	void ShowPathes()
	{
		for (auto p : this->Pathes)
		{
		//	p.SHOW();
			
		}
	}
	void ShowPathes(unsigned tx_ele, unsigned rx_ele)
	{
		//double PI = 22 / 7;
		//cout << "PATH ID" << setw(20) << "SOURCE ID" << setw(20) << "DEPARTUER PHI" << setw(20) << "ARRIVAL PHI" << setw(20) << "POSITION PHI" << setw(20) << "DEPARTUER THETA" << setw(20) << "ARRIVAL THETA" << setw(20) << "POSITION THETA" << endl;
		for (auto p : this->Pathes)
		{
			if (p.FOUND(tx_ele, rx_ele))
			{
				p.SHOWPATH();
			//	for (auto& r : p.RAYS)
				{
				//	cout << "PATH ID" << setw(20) << "SOURCE ID" << setw(20) << "DEPARTUER PHI" << setw(20) << "ARRIVAL PHI" << setw(20) << "POSITION PHI"     << setw(20) << "DEPARTUER THETA"  << setw(20) << "ARRIVAL THETA" << setw(20) << "POSITION THETA" << endl;
				//	cout << r.Path_ID  << setw(20) << r.Source_ID << setw(20) <<Tools::RoundAngles(DEG,r.Departure.Phi,1)  << setw(20) << Tools::RoundAngles(DEG, r.Arrival.Phi, 1)<< setw(20) << Tools::RoundAngles(DEG, this->Position.Phi, 1) << setw(20) << Tools::RoundAngles(DEG, r.Departure.Theta, 1) << setw(20) << Tools::RoundAngles(DEG, r.Arrival.Theta, 1) << setw(20) << Tools::RoundAngles(DEG, ((PI/2)+this->Position.Theta), 1) << endl;
				//	r.ShowRay();
				}
			}//<< std::setprecision(2)
		}
	}
	void ShowAllPathes()
	{
		for (auto p : this->Pathes)
			p.SHOWPATH();
	}
	bool IsValid()
	{
		return this->M.IsValid();
	}
	void SetGd(size_t group)
	{
		this->Gd = group;
	}
	void SetGx(size_t group)
	{
		this->Gx = group;
	}
	void SetGy(size_t group)
	{
		this->Gy= group;
	}
	void SetGphi(size_t group)
	{
		this->Gphi = group;
	}
	void SetGtheta(size_t group)
	{
		this->Gtheta = group;
	}
	void SetGdGphi(size_t group)
	{
		this->GdGphi = group;
	}
	EXPOSURE SetExposure()
	{
		size_t LOS_Path_ID{1};
		switch (Tools::WirelessInsiteVersion)
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
	//	cout << " LOS PATH ID : " << LOS_Path_ID << " VERSION : "<< Tools::WirelessInsiteVersion <<endl;
		for (auto& p : this->Pathes)
		{
			p.EXPO = NON;
		//	p.SHOW();
			for (auto& r : p.RAYS)
			{
				if (r.Path_ID== LOS_Path_ID)
				{
				//	r.Show();
					p.EXPO = LOS;
				//	ShowPathes(p.TX_ELEMENT, p.RX_ELEMENT);
				//	r.Show();
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
				//		cout << "LOS SISO" << endl;
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
		return NON;
		
	}
public:
	std::string Key;
	unsigned  Transmitter_Set;
	unsigned  Receiver_Set;
	unsigned  Transmitter_Point;
	unsigned  Receiver_Point;
	MatrixMIMO<std::complex<double>> M;
	MatrixMIMO<double> Q;
	POSITION Position;
	WirelessPower Power;
	double Capacity;
	double Capacity_SISO;
	size_t Gd; // Distance Group Number
	size_t Gx;
	size_t Gy;
	size_t Gphi;
	size_t Gtheta;
	size_t GdGphi;
	bool Capacity_Set_Flag;
//	size_t Permutation_Index;
	std::vector<PATHS> Pathes;
	EXPOSURE Expose;
};

