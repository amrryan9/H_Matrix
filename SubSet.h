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
		if (Pick(line)){if (line.IsValid())this->Terminals.push_back(line); return true;}
		return false;
	}
	bool AddItemDirect(Set_Line& line)
	{
		this->Terminals.push_back(line); return true;
	}
	bool Pick(Set_Line& line)
	{
		for (auto& c : this->Crieteria)if((!line.IsValid()) || (!c.Test(line)))return false;
		return true;
	}
	double GetAverageCapacity()
	{
		double sample_size = static_cast<double>(this->Terminals.size());
		double capacity{ 0 };
		for (auto& t : this->Terminals)
		{
			capacity = capacity + t.GetCapacity();
		}
		if (sample_size > 0){return capacity / sample_size;  }
		else return 0.0;
	}
	double GetAverageCapacity_SISO()
	{
		double sample_size = static_cast<double>(this->Terminals.size());
		double capacity_siso{ 0 };
		for (auto& t : this->Terminals)
		{
			capacity_siso = capacity_siso + t.GetCapacitySISO();// cout << "Capacity_siso: " << capacity_siso << endl;
		}
		
		if (sample_size > 0) {return capacity_siso / sample_size; }
		else return 0.0;
	}
	Complex_matrix GetAverageH_matrix_1()
	{
		float sample_size = static_cast<float>(this->Terminals.size());
		Complex_matrix H;
		Complex_matrix gg_her;
		Complex_matrix GG_Her;
		Double_matrix Q_Mean;
		Double_matrix Q;
		for (auto& t : this->Terminals)
		{
			H.Increment(t.M);
			Q.Increment(t.Q);
			gg_her = t.M.Transposed() * (t.M.Conjugate());
			GG_Her.Increment(gg_her);
	//		cout << "*************** GG_HER*****************" << endl;
	//		GG_Her.Show();
	//		cout << "*************** t.Q*****************" << endl;
	//		t.Q.Show();
	//		cout << "*************** Q*****************" << endl;
	//		Q.Show();
	//		cout << "*************** t.M*****************" << endl;
	//		t.M.Show();
	//		cout << "*************** H*****************" << endl;
	//		H.Show();
		}
		
		Q_Mean = Q/static_cast<double>(sample_size);
		this->AverageH = (H / Q);
		this->AverageQ = Q_Mean;
		this->AverageGG_Her = (GG_Her / static_cast<double>(sample_size));
	//	cout << "Sample size: " << sample_size<< endl;
		
	//	cout<<"*************** Q_Mean*****************"<<endl;
	//	Q_Mean.Show();
	//	cout << "*************** H_Mean*****************" << endl;
	//	AverageH.Show();
	//	AverageGG_Her.Show();
		return this->AverageH;
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
	bool Status()
	{
		for (auto r : this->Terminals)
			if (!r.IsValid())
			{
				cout << " INVALID TERMINAL FOUND " << endl;
				return false;
			}
		return true;
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
	//	for (auto& t : this->Terminals) t.Show();
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

