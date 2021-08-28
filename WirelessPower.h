#pragma once
#include<vector>
#include<iostream>
#include<iomanip>
#include <fstream>
#include <iterator>
#include <sstream>
#include <numeric>
#include <complex>
#include <sstream>
#include <matrix.h>
using namespace std;


class WirelessPower
{
public:
	WirelessPower()
	{
	}
	WirelessPower(Complex_matrix v)
	{
		V = v;
	}
	double Power(size_t r, size_t c)
	{
		return pow(abs(V.GetItem(r,c)), 2);
	}
	double Phase(size_t r, size_t c)
	{
		return arg(V.GetItem(r, c));
	}
	Double_matrix Power()
	{
		size_t r{ 0 }, c{ 0 };
		Double_matrix m;
		for (auto row : this->V.Rows)
		{
			for (auto item : row)
			{
				m.AddItem(r, c, pow(abs(item), 2));
				c++;
			}
			r++;
		}
		return m;
	}
	Double_matrix Phase()
	{
		size_t r, c{ 0 };
		Double_matrix m;
		for (vector< complex<double>> row : this->V.Rows)
		{
			for (complex<double> item : row)
			{
				m.AddItem(r, c, arg(item));
				c++;
			}
			r++;
		}
		return m;
	}
	Complex_matrix  PowerPhasor()
	{
	//	size_t r{ 0 }, c{ 0 };
		Complex_matrix m;
		for (size_t r = 0; r < V.Rows_Count;r++)// (auto row : this->V.Rows)
		{
			for (size_t c = 0; c < V.Columns_Count; c++)//(auto item : row)
			{
				m.AddItem(r, c, complex<double>(this->Power(r,c)*cos(this->Phase(r, c)), this->Power(r, c) * sin(this->Phase(r, c))));
			//	c++;
			}
		//	r++;
		}
		return m;
	}
	Complex_matrix  Shrink()// Shrink don the matrix ito one row contains the sum of columns
	{
		complex<double> s = complex<double>(0, 0);
		Complex_matrix S;
		
		for (size_t j = 0; j < V.Columns_Count; j++)
		{
			for (size_t i = 0; i < V.Rows_Count; i++)
			{
				s = s + V.GetItem(i, j);
			}
			S.AddItem(0, j, s);
			s = complex<double>(0, 0);
		}
		return WirelessPower(S).PowerPhasor();
	}
	Complex_matrix  Shrink_Horizontal()// Shrink don the matrix ito one row contains the sum of columns
	{
		complex<double> s = complex<double>(0, 0);
		Complex_matrix S;

		for (size_t j = 0; j < V.Rows_Count; j++)
		{
			for (size_t i = 0; i < V.Columns_Count; i++)
			{
				s = s + V.GetItem(j, i);
			}
			S.AddItem(j, 0, s);
			s = complex<double>(0, 0);
		}
		return WirelessPower(S).PowerPhasor();
	}
	Complex_matrix  Transmitter_Diagonal()// creat diagonal matrix of the transmitted power per transmitter
	{
		Complex_matrix  transmited_power = this->Shrink_Horizontal();
		Complex_matrix  d;
		size_t n = transmited_power.Rows_Count;
		for(size_t i=0;i<n;i++)
			for (size_t j = 0; j < n; j++)
			{
				if (i != j)
					d.AddItem(i, j, std::complex<double>(0, 0));
				else
					d.AddItem(i, j, std::complex<double>(abs(transmited_power.GetItem(i,0)),0));
			}
		return d;
	}
	Complex_matrix  Rceiver_Diagonal()// creat diagonal matrix of the transmitted power per transmitter
	{
		Complex_matrix  transmited_power = this->Shrink();
		Complex_matrix  d;
		size_t n = transmited_power.Columns_Count;
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
			{
				if (i != j)
					d.AddItem(i, j, std::complex<double>(0, 0));
				else
					d.AddItem(i, j, std::complex<double>(abs(transmited_power.GetItem(0, i)), 0));
			}
		return d;
	}
	double Rceiver_Average_Power()// Return average power received by a teriminal
	{
		Complex_matrix  transmited_power = this->Shrink();
		size_t n = transmited_power.Columns_Count;
		double p{ 0.0 };
		for (size_t i = 0; i < n; i++)p = p + abs(transmited_power.GetItem(0, i));
		p = p / static_cast<double>(n);
		return p;
	}
	double GetPower_dBm()// Return average power received by a teriminal
	{
		return 10 * log10(Rceiver_Average_Power() * 1000);
	}
	double GetPhase_Deg()// Return phase of the first item in the matrix ( used for SISO)
	{
	//	if(this->V.Columns_Count==1 && this->V.Rows_Count==1)
			return arg(this->V.GetItem(0,0))*180*7/22;
	//	else
		{
	//		cout << " IMPROPER USE OF THE FUNCTION GETPHASE_DEG , PROBABLY NOT A SISO ." << endl;
	//		return 0.0;
		}
	}
	void AddItem(size_t r, size_t c, const double power, const double phase)
	{
		V.AddItem(r,c,complex<double>(sqrt(power) * cos(phase), sqrt(power) * sin(phase)));
	}
	complex<double> GetItem(size_t r, size_t c)
	{
		return complex<double>(Power(r, c), Phase(r, c));
	}
	WirelessPower& operator=(const WirelessPower& rhs)
	{
		this->V = rhs.V;
		return *this;
	}	
	WirelessPower& operator+(const WirelessPower& rhs)
	{
		WirelessPower x(V + rhs.V);
		return x;
	}
	/*
	bool operator==(const WirelessPower& rhs)
	{
		if (this->V == rhs.V) return true;
		return false;
	}
	WirelessPower&& operator+(const WirelessPower& rhs)  // return rvlue
	{
		return WirelessPower (V + rhs.V);
	}
	inline std::ostream& operator<<(std::ostream& Str)
	{
		std::string str;
		Str <<" Power: " << Power << " Phase: " << Phase;
		return Str;
	}
	const char* toString() {
		std::stringstream converter;
		std::string str;
		converter << " Power: " <<Power << " Phase: " << Phase; converter >> str;		converter.clear();
		const char* s = str.c_str();
		return s;
	}
	*/
	WirelessPower& operator*(const WirelessPower& rhs)
	{
		WirelessPower x(V * rhs.V);
		return x;
	}
	
	void Show(size_t r, size_t c)
	{
		cout << " Power : " << this->Power(r,c) << " Phase : " << this->Phase(r,c) <<" "<<V.GetItem(r,c)<< endl;
	}	
	void Show()
	{
		Complex_matrix  p=this->PowerPhasor();
		p.Show(POLAR);
	}
public:
	Complex_matrix V;
};
/*
bool operator==(const WirelessPower& lhs, const WirelessPower& rhs)
{
	if (lhs.Power == rhs.Power && lhs.Phase == rhs.Phase && lhs.V == rhs.V) return true;
	return false;
}

std::ostream& operator<<(std::ostream& Str, WirelessPower const& mc)
{
	std::string str;
	Str << " Power: " << mc.Power << " Phase: " << mc.Phase;
	return Str;
}
*/