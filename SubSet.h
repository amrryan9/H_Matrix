#pragma once
#include "Set_Line.h"
enum CRITERIA     { DISTANCE, HEIGHT , ELEVATION_ANGLE , AZIMUTH_ANGLE, RADIAL_DISTANCE };
struct     RULE { double Minimum_Value; double Step; RULE(double min_value, double step) { Minimum_Value = min_value; Step = step; } bool Test(double value) { if (value >= Minimum_Value && value < Minimum_Value + Step)return true; else return false; } void show() { cout << " START : " << setw(10) << Minimum_Value << " END : " << setw(10) << Minimum_Value + Step << setw(7); } };
struct     CRITERIAS
{
	CRITERIA C;
	std::vector<RULE> RULES;
	CRITERIAS(CRITERIA criteria, double min_value, double step)	  { C = criteria;AddRule(criteria,min_value, step);}
	bool AddRule(CRITERIA criteria, double min_value, double step) { if (criteria == C) { RULES.push_back(RULE(min_value, step)); return true; } else return false; }
	bool Test(Set_Line& line)
	{
		switch (C)
		{
		case CRITERIA::DISTANCE:		for (auto& rule : RULES)if (rule.Test(line.Position.Distance))return true;
		case CRITERIA::HEIGHT:			for (auto& rule : RULES)if (rule.Test(line.Position.Height))return true;
		case CRITERIA::ELEVATION_ANGLE:	for (auto& rule : RULES)if (rule.Test(line.Position.Theta))return true;
		case CRITERIA::AZIMUTH_ANGLE:	for (auto& rule : RULES)if (rule.Test(line.Position.Phi))return true;
		case CRITERIA::RADIAL_DISTANCE:	for (auto& rule : RULES)if (rule.Test(line.Position.R))return true;
		}
		return false;
	}
	std::string ShowName(std::string& units) {
		std::string name;
		switch (C)
		{
		case CRITERIA::DISTANCE:		 units = "METERS"; name = " DISTANCE"; break;
		case CRITERIA::HEIGHT:			 units = "METERS"; name = " Height  "; break;
		case CRITERIA::ELEVATION_ANGLE:	 units = "RADS  "; name = " THETA   "; break;
		case CRITERIA::AZIMUTH_ANGLE:	 units = "RADS  "; name = " PHI     "; break;
		case CRITERIA::RADIAL_DISTANCE:	 units = "METERS"; name = " R       "; break;
		}
		return name;
	}
	void Show()
	{
		cout << " CREITERIA TYPE      :";
		std::string units;
		std::string name = this->ShowName(units);
		switch (C)
		{
		case CRITERIA::DISTANCE:		cout << name << endl; units = "METERS"; break;
		case CRITERIA::HEIGHT:			cout << name << endl; units = "METERS"; break;
		case CRITERIA::ELEVATION_ANGLE:	cout << name << endl; units = "RADS"  ; break;
		case CRITERIA::AZIMUTH_ANGLE:	cout << name << endl; units = "RADS"  ; break;
		case CRITERIA::RADIAL_DISTANCE:	cout << name << endl; units = "METERS"; break;
		}
		for (auto rule: RULES)
		{
			rule.show(); cout<< units << endl;
		}
	}
};
class SubSet
{
public:
	SubSet()
	{
		TransmitterID	=0;
		ReceiverID		=0;
		TXPt			=0;
		RXPt			=0;
	}
	SubSet(size_t transmitterID,	size_t receiverID,	size_t txPt)
	{
		TransmitterID	=transmitterID	;
		ReceiverID		=receiverID		;
		TXPt				=txPt		;
	}
	bool SetCriteria(CRITERIA criteria, double min_value, double step)
	{
		for (auto& c : Crieteria)if (c.AddRule(criteria, min_value, step))return true;
		if (Crieteria.size() < 4) { Crieteria.push_back(CRITERIAS(criteria, min_value, step)); return true; }
		cout << " Too Many Crieterias !!!" << endl;
		return false;
	}
	bool AddItem(Set_Line& line)
	{
		if (Pick(line)){this->Terminals.push_back(line); return true;}
		return false;
	}
	bool AddItemDirect(Set_Line& line)
	{
		this->Terminals.push_back(line); return true;
	}
	bool Pick(Set_Line& line)
	{
		for (auto& c : this->Crieteria)if((!c.Test(line)))return false;
		return true;
	}
	Complex_matrix GetAverageH_matrix_2()
	{
		float sample_size = static_cast<float>(this->Terminals.size());
		Complex_matrix H;
		Double_matrix Q_Mean;
		for (auto& t : this->Terminals)
		{
			H = H + t.M/t.Q;
		}
		return (H / static_cast<double>(sample_size));
	}
	double GetAveragePower()
	{
		float sample_size = static_cast<float>(this->Terminals.size());
		double power{ 0 };
		for (auto t : this->Terminals)
		{
			power = power + t.GetPower();
		}
		if (sample_size > 0)return power / sample_size;
		else return power;
	}
	size_t GetSampleSize()
	{
		return this->Terminals.size();
	}
	float GetAverageR()
	{
		float sample_size = static_cast<float>(this->Terminals.size());
		float r{ 0 };
		for (auto t : this->Terminals) {
			r = r + t.Position.R;
		}
		if (sample_size > 0)return r / sample_size;
		else return r;
	}
	float GetAverageD()
	{
		float sample_size = static_cast<float>(this->Terminals.size());
		float d{ 0 };
		for (auto t : this->Terminals) {
			d = d + t.Position.Distance;
		}
		if (sample_size > 0)return d / sample_size;
		else return d;
	}
	float GetAveragePhi()
	{
		float sample_size = static_cast<float>(this->Terminals.size());
		float phi{ 0 };
		for (auto t : this->Terminals) {
			phi = phi + t.Position.Phi;
		}
		if (sample_size > 0)return phi / sample_size;
		else return phi;
	}
	float GetAverageTheta()
	{
		float sample_size = static_cast<float>(this->Terminals.size());
		float theta{ 0 };
		for (auto t : this->Terminals) {
			theta = theta + t.Position.Theta;
		}
		if (sample_size > 0)return theta / sample_size;
		else return theta;
	}
	bool operator==( const SubSet& rhs)
	{
		if (this->Crieteria.size() == rhs.Crieteria.size())
		{
			for (size_t i = 0; i < this->Crieteria.size(); i++)
			{
				if (this->Crieteria.at(i).C == rhs.Crieteria.at(i).C)
				{
					if (this->Crieteria.at(i).RULES.size() == rhs.Crieteria.at(i).RULES.size())
					{
						for (size_t j = 1; j < this->Crieteria.at(i).RULES.size(); j++)
						{
							if (this->Crieteria.at(i).RULES.at(j).Minimum_Value != rhs.Crieteria.at(i).RULES.at(j).Minimum_Value || this->Crieteria.at(i).RULES.at(j).Step != rhs.Crieteria.at(i).RULES.at(j).Step)return false;
						}
						return true;
					}
					else return false;
				}
				else return false;
			}
		}
		return false;
	}
	void Reset()
	{
		this->Terminals.clear();
	}
	void ShowCriteria()
	{
		for (auto c : this->Crieteria)c.Show();
	}
	void Show()
	{
		cout << " *******************************************" << endl;
		size_t i{ 0 };
		
		for (auto& c : this->Crieteria)
		{
			cout << " CRITERIA #          : " << i << endl;
			c.Show();
			i++;
		}
		cout << " CRITERIA TYPE       :" << setw(10);
		cout << " LINKS IN THE SUBSET : " <<endl;
		cout << " LINKS COUNT LISTED  : " << Terminals.size() << endl;
	}
public:
	vector<Set_Line> Terminals				;
	size_t TransmitterID					;
	size_t ReceiverID						;
	size_t TXPt								;
	size_t RXPt								;
	std::vector<CRITERIAS> Crieteria		;
	Complex_matrix AverageH					;
	Double_matrix AverageQ					;
	Complex_matrix AverageGG_Her			;
};

