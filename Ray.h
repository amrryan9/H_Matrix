#pragma once
#include<complex>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<math.h>
#include <functional> 
#include"Tools.h"
#include"Environment.h"
#include<matrix.h>
using namespace std;
struct Direction
{
	Direction() { Theta = 0.0; Phi = 0.0; }
	Direction(double t, double p)
	{
		Theta = t;
		Phi = p;
	}
	void Set(double t, double p)
	{
		Theta = t;
		Phi = p;
	}
	double Theta;
	double Phi;
};
class Ray
{
public:
	Ray()
	{
		this->Arrival.Phi = 0;
		this->Arrival.Theta =0;
		this->Departure.Phi = 0;
		this->Departure.Theta = 0;
		this->Arrival_Time = 0;
		this->Path_ID = 0;
		this->Path_Number = 0;
		this->Phase = 0;
		this->Power = 0;
		this->Source_ID = 0;
		this->Voltage_Value = static_cast<Complex>(0);
		this->Interactions = 0;
	}
	Ray(const Ray& ray)
	{
		this->Arrival.Phi = ray.Arrival.Phi;
		this->Arrival.Theta = ray.Arrival.Theta;
		this->Departure.Phi = ray.Departure.Phi;
		this->Departure.Theta = ray.Departure.Theta;
		this->Arrival_Time = ray.Arrival_Time;
		this->Path_ID = ray.Path_ID;
		this->Path_Number = ray.Path_Number;
		this->Phase = ray.Phase;
		this->Power = ray.Power;
		this->Source_ID = ray.Source_ID;
		this->Voltage_Value = ray.Voltage_Value;
		this->Interactions = ray.Interactions;
	}
	Ray(unsigned path_id, unsigned source_id)
	{
		Path_ID = path_id;
		Source_ID = source_id;
		Power = 0; // Power magnitude in Watts
		Phase = 0; // Phase Angle in rad of the voltage value , NOT power
		Arrival_Time = 0; // Time in seconds
		Voltage_Value = complex(0, 0);
	}
	Ray(unsigned path_id,unsigned source_id, double power, double phase, double arrival_time)
	{
		Path_ID = path_id;
		Source_ID = source_id;
		Power = power; // Power magnitude in Watts
		Phase = phase; // Phase Angle in rad of the voltage value , NOT power
		Arrival_Time = arrival_time; // Time in seconds
		Voltage_Value = complex(sqrt(power) * cos(phase), sqrt(power) * sin(phase));
	}
	Ray(unsigned path_number,unsigned total_interactions, double power, double phase, double arrival_time, float arrival_theta, float arrival_phi, float departure_theta, float departure_phi)
	{
		Path_ID = -1;//SISO
		Source_ID = 0;
		Interactions = total_interactions;
		Power = power; // Power magnitude in Watts
		Phase = phase; // Phase Angle in rad of the voltage value , NOT power
		Arrival_Time = arrival_time; // Time in seconds
		Voltage_Value = complex(sqrt(power) * cos(phase), sqrt(power) * sin(phase));
		Arrival.Theta = arrival_theta;
		Arrival.Phi = arrival_phi;
		Departure.Theta = departure_theta;
		Departure.Phi = departure_phi;
	}
	Ray(unsigned path_id, unsigned source_id, double power, double phase, double arrival_time, double Arrival_Phi, double Arrival_Theta, double Departure_Phi, double Departure_Theta)
	{
		Path_ID = path_id;
		Source_ID = source_id;
		Power = power; // Power magnitude in Watts
		Phase = phase; // Phase Angle in rad of the voltage value , NOT power
		Arrival_Time = arrival_time; // Time in seconds
		Voltage_Value = complex(sqrt(power) * cos(phase), sqrt(power) * sin(phase));
		this->SetArrival(Arrival_Theta, Arrival_Phi);
		this->SetDeparture(Departure_Theta, Departure_Phi);
	}
	Ray(unsigned int path_id, unsigned int source_id, double Arrival_Phi, double Arrival_Theta, double Departure_Phi, double Departure_Theta, double power)
	{
		Ray(0, 0, 0, 0, 0);
		SetDirections(path_id, source_id, Arrival_Phi, Arrival_Theta, Departure_Phi, Departure_Theta,power);

	}
	Ray operator+(const Ray rhs)
	{
		std::complex<double> v = this->Voltage_Value + rhs.Voltage_Value;
		double power = pow(std::abs(v), 2);
		double phase = std::arg(v);
		return Ray(this->Path_ID, this->Source_ID, power, phase, this->Arrival_Time);
	}
	Ray& operator+=(const Ray rhs)
	{
		*this = *this+rhs;
		return *this;
	}
	Ray& operator=(const Ray rhs)
	{
		this->Arrival.Phi = rhs.Arrival.Phi;
		this->Arrival.Theta = rhs.Arrival.Theta;
		this->Departure.Phi = rhs.Departure.Phi;
		this->Departure.Theta = rhs.Departure.Theta;
		this->Arrival_Time = rhs.Arrival_Time;
		this->Path_ID = rhs.Path_ID;
		this->Path_Number = rhs.Path_Number;
		this->Phase = rhs.Phase;
		this->Power = rhs.Power;
		this->Source_ID = rhs.Source_ID;
		this->Voltage_Value = rhs.Voltage_Value;
		this->Interactions = rhs.Interactions;
		return *this;
	}
	void SetArrival(double theta, double phi)
	{
		this->Arrival.Set(theta, phi);
	}
	void SetDeparture(double theta, double phi)
	{
		this->Departure.Set(theta, phi);
	}
	bool SetDirections(unsigned int path_id, unsigned int source_id, double Arrival_Phi, double Arrival_Theta, double Departure_Phi, double Departure_Theta, double power)
	{
		this->SetArrival(Arrival_Theta, Arrival_Phi);
		this->SetDeparture(Departure_Theta, Departure_Phi);
		this->Power = power;
		return true;
	}
	bool CheckTheSameRay(Ray r)
	{
		if (this->Path_ID == r.Path_ID && this->Source_ID == r.Source_ID && this->Power == r.Power)
		{
			return true;
		//	cout << " Rays match " << endl;
		}
		cout << " Rays don't match " << endl;
		return false;
	}
	void Set(double power, double phase, double arrival_time)
	{
		Power = power; // Power magnitude in Watts
		Phase = phase; // Phase Angle in rad of the voltage value , NOT power
		Arrival_Time = arrival_time; // Time in seconds
		Voltage_Value = complex<double>(sqrt(power) * cos(phase), sqrt(power) * sin(phase));
	}
	void Set(unsigned path_id, unsigned source_id, double power, double phase, double arrival_time)
	{
		Path_ID = path_id;
		Source_ID = source_id;
		Power = power; // Power magnitude in Watts
		Phase = phase; // Phase Angle in rad of the voltage value , NOT power
		Arrival_Time = arrival_time; // Time in seconds
		Voltage_Value = complex<double>(sqrt(power) * cos(phase), sqrt(power) * sin(phase));
	}
	void Reset()
	{
		Path_ID = 0;
		Power = 0; // Power magnitude in Watts
		Phase = 0; // Phase Angle in rad
		Arrival_Time = 0; // Time in seconds
		Voltage_Value = complex<double>(0.0,0.0);
	}
	void Show() const
	{
		cout << "***********************************" << endl;
		cout << "RAY ID          :"  << Path_ID << endl;
		cout << "Phase           :"  << Phase <<" rad"<< endl;
		cout << "Arrival_Time    :"  << Arrival_Time <<" s"<< endl;
		cout << "Power           :"  << Power <<" W"<< endl;
		cout << "Voltage         :"  << Voltage_Value.real() <<"+i "<< Voltage_Value .imag()<< " V" << endl;
		cout << " Arrival Phi    :"  << Arrival.Phi << " Rad" << endl;
		cout << " Arrival Theta  :"  << Arrival.Theta << " Rad" << endl;
		cout << " Departure Phi  :"  << Departure.Phi << " Rad" << endl;
		cout << " Departure Theta:"  << Departure.Theta << " Rad" << endl;
		cout << " Interactions   :"  << Interactions  << endl;

	}
	void ShowRay()
	{
		size_t n = 20;
		double Calculated_Phase = (2 * (22.0 / 7.0) * Environment::CarrierFrequency * Arrival_Time);// -Tools::ModelChannelGain(Tools::Spacing, Tools::CarrierFrequency, Tools::Phi_array, Departure.Phi, Departure.Theta);//
		double Calculated_Phase_mod =-1* std::fmod(Calculated_Phase,(44.0 / 7.0));
		cout << Path_ID;				space<unsigned int>(Path_ID, n);
		cout << Source_ID ;				space<unsigned int>(Source_ID, n);
		cout << Power ;					space<double>(Power, n);
		cout << Phase * (180.0 * 7.0 / 22.0);					space<double>(Phase * (180.0 * 7.0 / 22.0), n);
		cout << Calculated_Phase_mod * (180.0 * 7.0 / 22.0);	space<double>(Calculated_Phase_mod*(180.0*7.0/22.0), n);
		cout << Arrival_Time ;			space<double>(Arrival_Time, n);
		cout << Arrival.Phi;			space<double>(Arrival.Phi, n);
		cout << Arrival.Theta ;			space<double>(Arrival.Theta, n);
		cout << Departure.Phi ;			space<double>(Departure.Phi, n);
		cout << Departure.Theta;		space<double>(Departure.Theta, n); cout << endl;
		
		//Tools::RoundAngles(DEG, r.Departure.Phi, 1)
	}
	template<class T>
	void space(T p, size_t n)
	{
		string s = std::to_string(p);
		string space = "";
		for (size_t i = 0; i < n-s.size(); i++)
			space = space + " ";
		cout << space;
	}
	void Show_SISO() const
	{
		cout << "***********************************" << endl;
		cout << "RAY ID         :" << setw(15) << Path_ID << endl;
		cout << "Phase          :" << setw(15) << Phase*180*7/22 << " deg" << endl;
		cout << "Arrival_Time   :" << setw(15) << Arrival_Time << " s" << endl;
		cout << "Power          :" << setw(15) << 10*log10(Power*1000) << " dBm" << endl;
		cout << "Voltage        :" << setw(15) << 20 * log10(abs(Voltage_Value)) << "|_ " << arg(Voltage_Value) * 180 * 7 / 22 << " V dB|_deg" << endl;

	}
	bool write(std::ofstream& ofile)
	{
		ofile.write(reinterpret_cast<char*>(&(this->Path_ID)), sizeof(this->Path_ID));
		ofile.write(reinterpret_cast<char*>(&(this->Path_Number)), sizeof(unsigned));
		ofile.write(reinterpret_cast<char*>(&(this->Interactions)), sizeof(unsigned));
		ofile.write(reinterpret_cast<char*>(&(this->Source_ID)), sizeof(unsigned));
		ofile.write(reinterpret_cast<char*>(&(this->Power)), sizeof(double));
		ofile.write(reinterpret_cast<char*>(&(this->Phase)), sizeof(double));
		ofile.write(reinterpret_cast<char*>(&(this->Arrival_Time)), sizeof(double));
		ofile.write(reinterpret_cast<char*>(&(this->Arrival.Phi)), sizeof(double));
		ofile.write(reinterpret_cast<char*>(&(this->Arrival.Theta)), sizeof(double));
		ofile.write(reinterpret_cast<char*>(&(this->Departure.Phi)), sizeof(double));
		ofile.write(reinterpret_cast<char*>(&(this->Departure.Theta)), sizeof(double));
		ofile.write(reinterpret_cast<char*>(&(this->Voltage_Value)), sizeof(complex<double>));

		return !ofile.fail();
	}

	bool read(std::ifstream& ifile)
	{
		ifile.read(reinterpret_cast<char*>(&(this->Path_ID)), sizeof(this->Path_ID));
		ifile.read(reinterpret_cast<char*>(&(this->Path_Number)), sizeof(unsigned));
		ifile.read(reinterpret_cast<char*>(&(this->Interactions)), sizeof(unsigned));
		ifile.read(reinterpret_cast<char*>(&(this->Source_ID)), sizeof(unsigned));
		ifile.read(reinterpret_cast<char*>(&(this->Power)), sizeof(double));
		ifile.read(reinterpret_cast<char*>(&(this->Phase)), sizeof(double));
		ifile.read(reinterpret_cast<char*>(&(this->Arrival_Time)), sizeof(double));
		ifile.read(reinterpret_cast<char*>(&(this->Arrival.Phi)), sizeof(double));
		ifile.read(reinterpret_cast<char*>(&(this->Arrival.Theta)), sizeof(double));
		ifile.read(reinterpret_cast<char*>(&(this->Departure.Phi)), sizeof(double));
		ifile.read(reinterpret_cast<char*>(&(this->Departure.Theta)), sizeof(double));
		ifile.read(reinterpret_cast<char*>(&(this->Voltage_Value)), sizeof(complex<double>));

		return !ifile.fail();
	}
	friend std::ofstream& operator<<(std::ofstream& ofile, Ray const& r);
	friend std::ifstream& operator>>(std::ifstream& ifile, Ray& r);
public:
	int Path_ID;
	unsigned Path_Number;
	unsigned Interactions;
	unsigned Source_ID;
	double Power; // Power magnitude in Watts
	double Phase; // Phase Angle in rad of power vector
	double Arrival_Time; // Time in seconds
	Direction Arrival;
	Direction Departure;
	Complex Voltage_Value;
};
/*
std::ofstream& operator<<(std::ofstream& ofile, Ray const& r)
{
	ofile.write(reinterpret_cast<const char*>(&r.Path_ID), sizeof(r.Path_ID));
	ofile.write(reinterpret_cast<const char*>(&r.Path_Number), sizeof(r.Path_Number));
	ofile.write(reinterpret_cast<const char*>(&r.Interactions), sizeof(r.Interactions));
	ofile.write(reinterpret_cast<const char*>(&r.Source_ID), sizeof(r.Source_ID));
	ofile.write(reinterpret_cast<const char*>(&r.Power), sizeof(r.Power));
	ofile.write(reinterpret_cast<const char*>(&r.Phase), sizeof(r.Phase));
	ofile.write(reinterpret_cast<const char*>(&r.Arrival_Time), sizeof(r.Arrival_Time));
	ofile.write(reinterpret_cast<const char*>(&r.Arrival.Phi), sizeof(r.Arrival.Phi));
	ofile.write(reinterpret_cast<const char*>(&r.Arrival.Theta), sizeof(r.Arrival.Theta));
	ofile.write(reinterpret_cast<const char*>(&r.Departure.Phi), sizeof(r.Departure.Phi));
	ofile.write(reinterpret_cast<const char*>(&r.Departure.Theta), sizeof(r.Departure.Theta));
	ofile.write(reinterpret_cast<const char*>(&r.Voltage_Value), sizeof(r.Voltage_Value));

	return ofile;
}

std::ifstream& operator>>(std::ifstream& ifile,Ray& r)
{
	ifile.read(reinterpret_cast<char*>(&r.Path_ID), sizeof(r.Path_ID));
	ifile.read(reinterpret_cast<char*>(&r.Path_Number), sizeof(r.Path_Number));
	ifile.read(reinterpret_cast<char*>(&r.Interactions), sizeof(r.Interactions));
	ifile.read(reinterpret_cast<char*>(&r.Source_ID), sizeof(r.Source_ID));
	ifile.read(reinterpret_cast<char*>(&r.Power), sizeof(r.Power));
	ifile.read(reinterpret_cast<char*>(&r.Phase), sizeof(r.Phase));
	ifile.read(reinterpret_cast<char*>(&r.Arrival_Time), sizeof(r.Arrival_Time));
	ifile.read(reinterpret_cast<char*>(&r.Arrival.Phi), sizeof(r.Arrival.Phi));
	ifile.read(reinterpret_cast<char*>(&r.Arrival.Theta), sizeof(r.Arrival.Theta));
	ifile.read(reinterpret_cast<char*>(&r.Departure.Phi), sizeof(r.Departure.Phi));
	ifile.read(reinterpret_cast<char*>(&r.Departure.Theta), sizeof(r.Departure.Theta));
	ifile.read(reinterpret_cast<char*>(&r.Voltage_Value), sizeof(r.Voltage_Value));

	return ifile;
}
*/