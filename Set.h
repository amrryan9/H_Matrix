#pragma once
#include "SubSet.h"

#define element unsigned int

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
		cout << setw(12) << "Distance(m)"<<setw(12)<<"Height(m)"<< setw(12) <<"Phi(rad)" << setw(12) << "Theta(rad)" << setw(12) << "R(m)" << endl;
		cout << "______________________________________________________" << endl;
		cout << setw(12) << Distance << setw(12) << Height << setw(12) << Phi << setw(12) << Theta << setw(12) << R << endl;
	}
};

struct T_R_Set
{
	T_R_Set(unsigned id, unsigned points, unsigned e)
	{
		Id = id;
		for (unsigned p = 0; p < points - 1; p++)T_R_Points.push_back(0);
		T_R_Points.push_back(e);
	}
	void SHOW()
	{
		cout << " T/R SET ID : " << Id << endl;
		size_t i{ 0 };
		for (auto& t_r : T_R_Points)
		{
			cout << " T/R Point # : " <<i <<" HAS ELEMENTs count: "<<  t_r << endl;
		}
	}
	unsigned Id;
	vector<element>T_R_Points;
};
class Set
{
public:
	Set()
	{
	}
	void AddItem(Set_Line& l)
	{
		this->S.push_back(l);
	}
	Set_Line* AddItem(const std::vector<Ray>& pathes,unsigned t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned r, unsigned c, std::complex<double> x,double total_power)
	{
		
		for (auto& entry : this->S)
		{
			if (entry.Transmitter_Set == t_set)
			{
				if (entry.Receiver_Set == r_set)
				{
					if (entry.Transmitter_Point == t_point)
					{
						if (entry.Receiver_Point == r_point)
						{
							entry.M.AddItem(r, c, x);
							entry.Q.AddItem(r, c, pathes.size());
							entry.Power.AddItem(r, c, total_power, -arg(x));
							entry.SetPathes(t_set, r_set, t_point, r_point, r + 1, c + 1, pathes);
							return &entry;
						}
					}
				}
			}
		}
		Set_Line* l = new Set_Line(t_set, r_set, t_point, r_point);
		l->M.AddItem(r, c, x);
		l->Q.AddItem(r, c, pathes.size());
		l->Power.AddItem(r, c, total_power, -arg(x));
		l->SetPathes(t_set, r_set, t_point, r_point, r+1, c+1, pathes);
		this->S.push_back(*l);
		return l;
	}
	void AddItemPower(unsigned t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned r, unsigned c, double total_power, double power_phase)
	{
		std::string key;
		std::stringstream converter;
		converter << t_set << r_set << t_point << r_point; converter >> key;
		for (auto& l : this->S)
		{
			if (l.Key == key)
			{
				l.Power.AddItem(r, c, total_power, power_phase);
			}
		}
	}
	bool UpdateItem(std::vector<Ray> pathes_angles, unsigned t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned r, unsigned c)
	{
		//Update rays with angles 
		//Get Ray 
		PATHS& P = (this->GetPathes(t_set, r_set, t_point, r_point, r, c));
		unsigned i = 0;
		if (pathes_angles.size() == P.RAYS.size())
		{
			for (auto& ray : pathes_angles)
			{
				if (i < P.RAYS.size())
				{
					if (ray.CheckTheSameRay(P.RAYS.at(i)))
					{
						//Update
						P.RAYS.at(i).SetArrival(ray.Arrival.Theta, ray.Arrival.Phi);
						P.RAYS.at(i).SetDeparture(ray.Departure.Theta, ray.Departure.Phi);
						i++;
					}
					else
					{
						cout << " MISMATCH #1" << endl;
						return false;
					}
				}
				else
				{
					cout << " MISMATCH #2" << endl;
					return false;
				}
			}
		}
		else
		{
			cout << " MISMATCH #3" << endl;
			cout << " CIR Pathes count : " << P.RAYS.size() << endl;
			cout << " DOD Pathes count : " << pathes_angles.size() << endl;
			return false;
		}
		return true;
	}
	void AddTopologyItem(unsigned t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned t_element, unsigned r_element)
	{
		unsigned i = 0;
		if (Transmitters.size()==0)Transmitters.push_back(T_R_Set(t_set, t_point, t_element));
		else {
			for (auto& p : Transmitters)
			{
				i++;
				if (p.Id == t_set)
				{
					if (p.T_R_Points.size() >= t_point)
					{
						if (p.T_R_Points.at(t_point - 1) < t_element)
						{
							p.T_R_Points.at(t_point - 1) = t_element;
						}
						break;
					}
					else
					{
						p.T_R_Points.push_back(t_element);
					}
				}
				else
				{
					if (i == Transmitters.size())Transmitters.push_back(T_R_Set(t_set, t_point, t_element));
				}
			}
		}
		////
		if (Receivers.size()==0)Receivers.push_back(T_R_Set(r_set, r_point, r_element));
		else
		{
			i = 0;
			for (auto& p : Receivers)
			{
				i++;
				if (p.Id == r_set)
				{
					if (p.T_R_Points.size() >= r_point)
					{
						if (p.T_R_Points.at(r_point - 1) < r_element)
						{
							p.T_R_Points.at(r_point - 1) = r_element;
						}
						break;
					}
					else
					{
						p.T_R_Points.push_back(r_element);
					}
				}
				else
				{
					if (i == Receivers.size())Receivers.push_back(T_R_Set(r_set, r_point, r_element));
				}
			}
		}
	}
	bool RemoveReceiverPoint(unsigned  r_point)
	{
		if ((r_point - 1) < this->Receivers.at(0).T_R_Points.size())
		{
			this->Receivers.at(0).T_R_Points.erase(this->Receivers.at(0).T_R_Points.begin() + r_point - 1);
			return true;
		}
		else
			cout << " POINT INDEX "<< (r_point - 1) <<" IS LARGER THAN RECEIVERS SIZE" << this->Receivers.at(0).T_R_Points.size() <<endl;
		return false;
	}
	bool RemoveLine(unsigned  n)
	{
		if (RemoveReceiverPoint(n + 1))
		{
			if (n < S.size())
			{
				S.erase(S.begin() + n);
				return true;
			}
		}
		else
		{
			cout << " FAILED REMOVAL OF A RECEIVER POINT " << endl;
		}
		return false;
	}

	void SetExposure()
	{
		for (auto& s : this->S)
		{
			s.SetExposure();
		}
	}
	size_t GetSize()
	{
		if (this->S.size() == this->Receivers.size())
			return this->S.size();
		else
		{
			return 0;
			cout << " THERE IS A PROBLEM : LINES ARE NOT EQUAL TO RECEIVER POINTS" << endl;
		}
	}
	void GetDistribution(std::string file_out_rect, std::string file_out_polar) // All receivers from a single transmitting point
	{
		Complex_matrix result;
		Float_vector angles_and_capacity;
		string header, r_, c_; header = "(row  column)";
		std::stringstream converter;
		if(this->S.size()>0)
			for (size_t r = 0; r < this->S.at(0).M.Rows_Count; r++)
				for (size_t c = 0; c < this->S.at(0).M.Columns_Count; c++)
				{
					converter << r; converter >> r_; converter.clear();
					converter << c; converter >> c_; converter.clear();
					header = header + ",(" + r_ + "\," + c_ + ")";
				}

		for (auto& m : S)
		{
			angles_and_capacity.clear();
			AppendToTable<Complex,float>(result, m.M, angles_and_capacity);
		}
		cout << " SUCCESSFUL TERMINALS : " << result.Rows_Count << endl;// result.Show();
		result.WriteFile(file_out_polar, POLAR,FileForm::DECORATED, header);
		result.WriteFile(file_out_rect, RECT, FileForm::DECORATED, header);
	}
	void GetDistribution()
	{
		GetDistribution(Tools::RESULTSFolder + Tools::GetTestCase() + "/test_rect", Tools::RESULTSFolder + Tools::GetTestCase() + "/test_polar");
	}
	PATHS& GetPathes(unsigned  t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned tx_ele, unsigned rx_ele)
	{
		PATHS Nothing;
		for (auto& l : this->S)
		{
			if (l.Transmitter_Set == t_set && l.Receiver_Set==r_set && l.Transmitter_Point==t_point && l.Receiver_Point==r_point)
			{
				return l.GetPathes(tx_ele, rx_ele);
			}
		}
		cout << " PATHES ARE NOT FOUND !!!!!!!!!!" << endl;
		return Nothing;
	}
	Set GetEXPO(EXPOSURE check)
	{
		size_t i_index{ 0 };
		Set* SS=new Set();
		if (check != EXPOSURE::ALL && check !=EXPOSURE::NON)
		{
			for(auto& l : this->S)
			{
				if (l.SetExposure() == check) 
					SS->AddItem(l);
			}
			cout << " Total Number of Points is : " << this->S.size() << " . Number of " << Set_Line::PrintExposure(check) << " Points is " << SS->S.size() << endl;
		}
		return *SS;
	}
	Set RemoveLines(std::vector<size_t> remove_points)
	{
		Set SS;
		SS = *this;
		int j{ 0 };
		for (size_t n = 0; n < this->S.size(); n++)
		{
			for (size_t m : remove_points)
			{
				if (m == n)
				{
					SS.RemoveLine(j);
					cout << " Line :" << m << " is removed " << endl;
					j--;
					break;
				}
			}
			j++;
		}
		return SS;
	}
	void Show()
	{
		cout << endl;
		ShowTopology();
		cout << " NUMBER OF TRANSMITTER - RECEIVER PAIRS ( LINKS ) : " << S.size() << endl;
		int i = 0;
		for (auto s : S)
		{
			i++;
			cout << " LINK # : " << i << endl;
			s.Show();
		}
	}
	void ShowTopology()
	{
		cout << " TOPOLOGY     : " << endl;
		cout << " TRANSMITTERS : " << endl;
		cout << "		SET ID\tPOINT\tELEMENTS" << endl;
		for (auto t : Transmitters)
		{
			for (unsigned p = 0; p < t.T_R_Points.size();p++)
			{
				cout << "\t\t" << t.Id << "\t";
				cout << p + 1 << "\t" << t.T_R_Points.at(p) << endl;
			}
		}
		cout << "******************************************" << endl;
		cout << " RECEIVERS    : " << endl;
		for (auto r : Receivers)
		{
			for (unsigned p = 0; p < r.T_R_Points.size(); p++)
			{
				cout << "\t\t" << r.Id << "\t";
				cout << p + 1 << "\t" << r.T_R_Points.at(p) << endl;
			}
		}
		cout << "******************************************" << endl;
	}
	void ShowPositionWithPower(size_t txEle, size_t rxEle)
	{
		cout << " Distance ," << setw(10) << " Height ," << setw(10) << " Phi ," << setw(10) << " Theta ," << setw(10) << " R " << endl;
		size_t S_size = S.size();
		for (size_t i = 1; i <= S_size; i++)
		{
			auto L = S.at(Tools::RePermute(i, S_size) - 1);
			cout << setw(10) << i << " :," << L.Position.Distance << " :," << setw(10) << L.Position.Height << " :," << setw(10) << L.Position.Phi << " :," << setw(10) << L.Position.Theta << " :," << setw(10) << L.Position.R; L.ShowPower(txEle, rxEle);// << endl;
		}
		cout << " Number of Terminals :" << S_size << endl;
	}
	void ShowPower(size_t tx_set, size_t tx_pt, size_t tx_ele, size_t rx_set, size_t rx_pt, size_t rx_ele)// Print power as it would appear in wireless insite. from the transmitter Element to receiver Element for all terminal points
	{
		cout << " Power OutPut" << endl;
		complex<double> z;
		size_t i{ 0 };
		for (auto s : this->S)
		{
			{
				z = s.Power.PowerPhasor().GetItem(tx_ele-1, rx_ele-1);
				s.Power.PowerPhasor().GetItem(tx_ele-1, rx_ele-1);
				cout <<setw(6)<<i<<": "<< abs(z)<< " |_ "<< arg(z) << endl;
				i++;
			}
		}
	}
	void ShowPower(size_t txEle, size_t rxEle)  // shows power from the txEle in each transmitter point to all txEle for all receiver points
	{
		size_t S_size = S.size();
		for (size_t i = 1; i <= S_size;i++)// (auto L : S)
		{
			auto L = S.at(i);  // Pemutation is considered already done !!!!
			cout << setw(10) << i <<" :,"<<  " :,"; L.ShowPower(txEle, rxEle);
		}
		cout << " Number of Terminals :" << S_size << endl;
	}
	void PermutateBack()
	{
		std::vector<Set_Line> SP;
		size_t S_size = S.size();
		for (size_t i = 1; i <= S_size; i++)// (auto L : S)
		{
			SP.push_back(S.at(Tools::RePermute(i, S_size) - 1));
		}
		this->S.clear();
		this->S = SP;
	}
	void ShowPower_file(configuration conf)  // shows power from the txEle in each transmitter point to all txEle for all receiver points
	{
		size_t i{ 1 };
		switch (conf)
		{
		case configuration::MIMO:
			cout << " " << i << setw(20) << "# X(m)" << setw(20) << "Y(m)" << setw(20) << "Z(m)" << setw(20) << "Distance(m)" << setw(20) << "Power(dBm)" << setw(20) << "Phase(deg)" << endl;
			cout << "________________________________________________________________________________________________________________________________________________" << endl;
			for (auto& s : this->S)
			{
				cout << " " << i << setw(20) << s.Position.X() << setw(20) << s.Position.Y() << setw(20) << s.Position.Z() << setw(20) << s.Position.DirectDistance() << setw(20); s.ShowPower(0, 0);
				i++;
			}
			cout << "________________________________________________________________________________________________________________________________________________" << endl;
			break;
		case configuration::SISO:
			cout << " " << i << setw(20) << "# X(m)" << setw(20) << "Y(m)" << setw(20) << "Z(m)" << setw(20) << "Distance(m)" << setw(20) << "Power(dBm)" << setw(20) << "Phase(deg)" << endl;
			cout << "________________________________________________________________________________________________________________________________________________" << endl;
			for (auto& s : this->S)
			{
				cout << " " << i << setw(20) << s.Position.X() << setw(20) << s.Position.Y() << setw(20) << s.Position.Z() << setw(20) << s.Position.DirectDistance() << setw(20) << s.Power.GetPower_dBm() << setw(20) << s.Power.GetPhase_Deg() << endl;
				i++;
			}
			cout << "________________________________________________________________________________________________________________________________________________" << endl;
			break;
		}

	}
	void ShowH()
	{
		size_t S_size = S.size();
		for (size_t i = 1; i <= S_size; i++)// (auto L : S)
		{
			auto L = S.at(Tools::RePermute(i, S_size) - 1);
			cout << " " << i << " : " << endl;
			L.M.Show(RECT);
			cout << " ---------------------------------------- " << endl;
		}
	}
	void ShowPathes(unsigned  t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned tx_ele, unsigned rx_ele)
	{
		for (auto s : this->S)
		{
			if (s.Receiver_Point == r_point)
				s.ShowPathes(tx_ele, rx_ele);
		}
	}
	void ShowPathes()
	{
		for (auto& l : this->S)
		{
			cout << endl;
			for (auto& p : l.Pathes)
				p.SHOWPATH();
			cout << endl;
			cout << "*************************************************" << endl;
		}
	}
	void ShowAllPathes(unsigned  t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point)
	{
		for (auto s : this->S)
		{
			if (s.Receiver_Point == r_point)
				s.ShowAllPathes();
		}
	}
	void ShowLos()
	{
		size_t i{ 1 };
		for (auto& l : this->S)
		{
			if(l.Expose == LOS)
				cout << " LOS  POINT # :" << setw(4) << i << endl;
			else
			cout <<     " NLOS POINT # :" << setw(4) << i << endl;

			i++;
		}
	}

	Set* Filter(PROPERITIES p0,double p0_max, double p0_min=0.0, PROPERITIES p1= PROPERITIES::EMPTY_PROP, double p1_max=0.0, double p1_min = 0.0, PROPERITIES p2 = PROPERITIES::EMPTY_PROP,double p2_max = 0.0, double p2_min = 0.0, PROPERITIES p3 = PROPERITIES::EMPTY_PROP, double p3_max = 0.0, double p3_min = 0.0, PROPERITIES p4 = PROPERITIES::EMPTY_PROP, double p4_max = 0.0, double p4_min = 0.0, PROPERITIES p5 = PROPERITIES::EMPTY_PROP, double p5_max = 0.0, double p5_min = 0.0, PROPERITIES p6 = PROPERITIES::EMPTY_PROP, double p6_max = 0.0, double p6_min = 0.0, PROPERITIES p7 = PROPERITIES::EMPTY_PROP, double p7_max = 0.0, double p7_min = 0.0, PROPERITIES p8 = PROPERITIES::EMPTY_PROP, double p8_max = 0.0, double p8_min = 0.0, PROPERITIES p9 = PROPERITIES::EMPTY_PROP, double p9_max = 0.0, double p9_min = 0.0)
	{
		Set* pSS = new Set();
		for (auto& l : this->S)
		{
			if (l.CheckProperity(p0, p0_max, p0_min) && l.CheckProperity(p1, p1_max, p1_min) && l.CheckProperity(p2, p2_max, p2_min) && l.CheckProperity(p3, p3_max, p3_min) && l.CheckProperity(p4, p4_max, p4_min) && l.CheckProperity(p5, p5_max, p5_min) && l.CheckProperity(p6, p6_max, p6_min) && l.CheckProperity(p7, p7_max, p7_min) && l.CheckProperity(p8, p8_max, p8_min) && l.CheckProperity(p9, p9_max, p9_min))
			{
				pSS->AddItem(l);
			}
		}
		return pSS;
	}
//////////////////// Creating another set based on a criteria ///////////////////////////////////////////////////////

public:
	std::vector<Set_Line> S;
	std::vector<T_R_Set > Transmitters;
	std::vector<T_R_Set > Receivers   ;
};

