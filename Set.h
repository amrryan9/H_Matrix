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
	/*
	bool AddItem(std::vector<Ray> pathes,unsigned t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned r, unsigned c, std::complex<double> x)
	{
		Set_Line l(t_set, r_set, t_point, r_point);
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
							//	entry.Power.AddItem(r, c, total_power, -arg(x));
								entry.SetPathes(t_set, r_set, t_point, r_point, r + 1, c + 1, pathes);
								return true;
							}
						}
					}
				}
			}
			l.M.AddItem(r, c, x);
			l.Q.AddItem(r, c, pathes.size());
		//	l.Power.AddItem(r, c, total_power, -arg(x));
			l.SetPathes(t_set, r_set, t_point, r_point, r + 1, c + 1, pathes);
			this->S.push_back(l);
		}
		return false;
	}
	*/
	Set_Line* AddItem(const std::vector<Ray>& pathes,unsigned t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned r, unsigned c, std::complex<double> x,double total_power)
	{
		
		for (auto& entry : this->S)
		{
			if (entry.Transmitter_Set == t_set)
			{
		//		cout << " Match found # 1" << endl;
				if (entry.Receiver_Set == r_set)
				{
		//			cout << " Match found # 2" << endl;
					if (entry.Transmitter_Point == t_point)
					{
		//				cout << " Match found # 3" << endl;
						if (entry.Receiver_Point == r_point)
						{
		//					cout << " Match found # 4" << endl;
							entry.M.AddItem(r, c, x);
							entry.Q.AddItem(r, c, pathes.size());
							entry.Power.AddItem(r, c, total_power, -arg(x));
							entry.SetPathes(t_set, r_set, t_point, r_point, r + 1, c + 1, pathes);
							return &entry;
						}
		//				else cout << " ITEM ADD ERROR #4 " << endl;
					}
		//			else cout << " ITEM ADD ERROR #3 " << endl;
				}
		//		else cout << " ITEM ADD ERROR #2 " << endl;
			}
		//	else cout << " ITEM ADD ERROR #1 " << endl;
		}
		Set_Line* l = new Set_Line(t_set, r_set, t_point, r_point);
		l->M.AddItem(r, c, x);
		l->Q.AddItem(r, c, pathes.size());
		l->Power.AddItem(r, c, total_power, -arg(x));
		l->SetPathes(t_set, r_set, t_point, r_point, r+1, c+1, pathes);
		this->S.push_back(*l);
		return l;
	}
	/*
	bool AddItem(std::vector<Ray> pathes,unsigned t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned r, unsigned c, std::complex<double> x, double total_power, double total_power_phase)
	{
		Set_Line l(t_set, r_set, t_point, r_point);
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
								entry.Power.AddItem(r, c, total_power, total_power_phase);
								entry.SetPathes(t_set, r_set, t_point, r_point, r + 1, c + 1, pathes);
								entry.SetExposure();
								return true;
							}
						}
					}
				}
			}
			l.M.AddItem(r, c, x);
			l.Q.AddItem(r, c, pathes.size());
			l.Power.AddItem(r, c, total_power, total_power_phase);
			l.SetPathes(t_set, r_set, t_point, r_point, r + 1, c + 1, pathes);
			l.SetExposure();
			this->S.push_back(l);
		}
		return false;
	}
	*/
	void AddItemPower(unsigned t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned r, unsigned c, double total_power, double power_phase)
	{
		std::string key;
		std::stringstream converter;
		converter << t_set << r_set << t_point << r_point; converter >> key;
		for (auto& l : this->S)
		{
			if (l.Key == key)
			{
			//	cout << " ITEM FOUND at point :"<<r_point<<"  - " <<r<<" , "<<c<<" Power: "<< total_power <<" phase "<< power_phase << endl;
				l.Power.AddItem(r, c, total_power, power_phase);
			}
		}
	}
	bool UpdateItem(std::vector<Ray> pathes_angles, unsigned t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned r, unsigned c)
	{
		//Update rays with angles 
		//Get Ray 
		//this->GetPathes(t_set, r_set, t_point, r_point, r, c).SHOWPATH();
		
		PATHS& P = (this->GetPathes(t_set, r_set, t_point, r_point, r, c));
	//	cout << "******************************** UPDATING *********************************" << endl;
	//	cout << " Transmitter set : " << t_set << endl;
	//	cout << " Receiver set    : " << r_set << endl;
	//	cout << " Transmitter point : " << t_point << endl;
	//	cout << " Receiver point : " << r_point << endl;
	//	cout << " Transmitter ele : " << r << endl;
	//	cout << " Receiver ele : " << c << endl;
	//	P.SHOWPATH();
	//	cout << " ******************************* FINISH UPDATING ***************************" << endl;

		
	//	if (P != nullptr)
	//	{
			//Check if it is the same 
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
	//	}
	//		cout << " ************* PINGO *******************************" << endl;
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
	void SetCapacity(std::string file_name)
	{
		std::vector<double> capacity_array;
		for (auto& m : S)
		{
			m.GetCapacity(capacity_array);
		}
		matrix Capacity(capacity_array); 
	//	Capacity.Show();
		Capacity.WriteFile(file_name);
	}
	void SetExposure()
	{
		for (auto& s : this->S)
		{
			s.SetExposure();
		}
	}
	/*
	void UpdateDirections(std::vector<Set_Line>& s_dod)
	{
		std::vector<Ray>* p_Rays = nullptr;
		for (auto& s : s_dod)
		{
			for (auto& sp : s.Pathes)
			{
				if (this->GetPathes(sp.KEY, p_Rays))
				{
					if (p_Rays != nullptr)
					{
						if ((p_Rays)->size() == sp.RAYS.size())
						{
							for (size_t i = 0; i < sp.RAYS.size(); i++)
							{
								p_Rays->at(i).SetDirections(sp.RAYS.at(i).Path_ID, sp.RAYS.at(i).Source_ID, sp.RAYS.at(i).Arrival.Phi, sp.RAYS.at(i).Arrival.Theta, sp.RAYS.at(i).Departure.Phi, sp.RAYS.at(i).Departure.Theta);
								p_Rays->at(i).Show();
							}
						}
						else
							cout << " SOMETHING WRONG 1 :  (SET)" << endl;
					}
					else
						cout << " SOMETHING WRONG 2 : NULLPTR (SET)" << endl;
				}
			}
		}
		   
	}
	*/
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
	void GetDistribution(size_t transmitter_set, size_t transmitter_pt, std::string file_out_rect, std::string file_out_polar) // All receivers from a single transmitting point
	{
		Complex_matrix result;
		//bool valid;
		Float_vector angles_and_capacity;
		for (auto m : S)
		{
			if (m.Transmitter_Set == transmitter_set && m.Transmitter_Point == transmitter_pt)
			{
				angles_and_capacity.clear();
				angles_and_capacity.push_back(static_cast<float>(m.Gd));
				angles_and_capacity.push_back(static_cast<float>(m.Gx));
				angles_and_capacity.push_back(static_cast<float>(m.Gy));
				angles_and_capacity.push_back(static_cast<float>(m.Gphi));
				angles_and_capacity.push_back(static_cast<float>(m.Gtheta));
				angles_and_capacity.push_back(static_cast<float>(m.GdGphi));
				angles_and_capacity.push_back(static_cast<float>(m.GetCapacity()));
				AppendToTable<Complex,float>(result, m.M, angles_and_capacity);
			}
		}
		cout << " SUCCESSFUL TERMINALS : " << result.Rows_Count << endl;
		result.WriteFile(file_out_polar, POLAR);
		result.WriteFile(file_out_rect, RECT);
	}
	void GetDistribution()
	{
		GetDistribution(1, 1, Tools::RESULTSFolder + Tools::GetTestCase() + "/test_polar.txt", Tools::RESULTSFolder + Tools::GetTestCase() + "/test_rect.txt");
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
	bool GetPathes(std::string key, std::vector<Ray>* p_Rays)
	{
		for (auto& l : this->S)
		{
			for(auto& p:l.Pathes)
			{
				if (p.KEY == key)
				{
					p_Rays=&p.RAYS;
					return true;
				}
			}
		}
		cout << " PATHES ARE NOT FOUND !!!!!!!!!!" << endl;
		return false;
	}
	Set GetEXPO(EXPOSURE check)
	{
		Tools::SetRESULTSFolder(check);
		size_t i_index{ 0 };
		Set SS;
		SS = *this;
		if (check != ALL)
		{
			while (i_index < SS.S.size())
			{
				if (SS.S.at(i_index).SetExposure() == check)i_index++;
				else
				{
					if (SS.RemoveLine(i_index))
					{
				//				cout << " LINE Number " << i_index << " HAS BEEN ERASED" << endl;
					}
				}

			}
			cout << " Total Number of Points" << this->S.size() << " Number of " << check << " Points is " << SS.S.size() << endl;
		}
		return SS;
	}
	Set GetEXPO(EXPOSURE check, std::vector<size_t>& remove_points)
	{
		Tools::SetRESULTSFolder(check);
		size_t i_index{ 0 };
		Set SS;
		SS = *this;
		if (check != ALL)
		{
			for (size_t n = 0; n < S.size(); n++)
			{
				if (this->S.at(n).SetExposure() == check)
				{
					i_index++;
				}
				else
				{
					SS.RemoveLine(i_index);
					remove_points.push_back(n);
				}
			}
			cout << " Total Number of Points" << this->S.size() << " Number of " << check << " Points is " << SS.S.size() << endl;
		}
		return SS;
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
	void ShowPosition()  
	{
		cout << " Distance ," << setw(10) << " Height ," << setw(10) << " Phi ," << setw(10) << " Theta ," << setw(10)<< " R " << endl;
		size_t S_size = S.size();
		for (size_t i = 1; i <= S_size; i++)
		{
			auto L = S.at(Tools::RePermute(i, S_size) - 1);
			cout << setw(10) << i << " :," << L.Position.Distance << " :," << setw(10) << L.Position.Height << " :," << setw(10) << L.Position.Phi << " :," << setw(10) << L.Position.Theta << " :," << setw(10) << L.Position.R << endl;
		}
		cout << " Number of Terminals :" << S_size << endl;
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
				z = s.Power.PowerPhasor().GetItem(tx_ele, rx_ele);
				s.Power.PowerPhasor().GetItem(tx_ele, rx_ele);
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
		case MIMO:
			cout << " " << i << setw(20) << "# X(m)" << setw(20) << "Y(m)" << setw(20) << "Z(m)" << setw(20) << "Distance(m)" << setw(20) << "Power(dBm)" << setw(20) << "Phase(deg)" << endl;
			cout << "________________________________________________________________________________________________________________________________________________" << endl;
			for (auto& s : this->S)
			{
				cout << " " << i << setw(20) << s.Position.X() << setw(20) << s.Position.Y() << setw(20) << s.Position.Z() << setw(20) << s.Position.DirectDistance() << setw(20); s.ShowPower(0, 0);
				i++;
			}
			cout << "________________________________________________________________________________________________________________________________________________" << endl;
			break;
		case SISO:
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
	void ShowCapacity()
	{
		cout << " Capacity OutPut" << endl;
		cout << " LINK #" << ": CAPACITY" << endl;
		size_t i{ 0 };
		for (auto s : this->S)
		{
			i++;
			if (s.IsValid())cout << " " << setw(6) << i << ": " << s.Capacity << endl;
		}
	}
	void ShowValid()
	{
		cout << endl;
		ShowTopology();
		cout << " NUMBER OF TRANSMITTER - RECEIVER PAIRS ( LINKS ) : " << S.size() << endl;
		int i = 0;
		for (auto s : S)
		{
			i++;
			cout << " LINK #              : " << i << endl;
			s.ShowValid();
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
		//	if (s.Transmitter_Set == t_set)
		//		if (s.Transmitter_Point == t_point)
		//			if (s.Receiver_Set == r_set)
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
			//	if (s.Transmitter_Set == t_set)
			//		if (s.Transmitter_Point == t_point)
			//			if (s.Receiver_Set == r_set)
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
	
	////////////////// Didiving into SubSets //////////////////////////////////
	std::vector<SubSet> CreateCriteria(CRITERIA criteria, double test_start, double test_end, size_t test_steps, size_t transmitterID, size_t receiverID, size_t txPt)//, size_t rxPt)
	{
		std::vector<SubSet>set;
		double step = (test_end - test_start) / static_cast<double>(test_steps);
		double start = test_start;
		double end = start + step;
		for (size_t i = 0; i < test_steps; i++)
		{
			SubSet s(transmitterID, receiverID, txPt);
			s.SetCriteria(criteria, start, step);
			set.push_back(s);//, rxPt));
			start = end;
			end = start + step;
		}
		return set;
	}
	void AddCriteria(CRITERIA criteria, double test_start, double test_end, std::vector<SubSet>& set) // add a signle rule to each group
	{
		//	size_t test_steps = set.size();
		double step = (test_end - test_start);// / static_cast<double>(test_steps);
		double start = test_start;
		//	double end = test_end;// start + step;
		for (auto& s : set)
		{
			s.SetCriteria(criteria, start, step);
			//	start = end;
			//	end = start + step;
		}
	}
	void CreateSubSets(std::vector<SubSet>& set)
	{
		for (auto s : this->S)
		{
			for (auto& t : set)if (t.AddItem(s))break;
		}
	}
	void CreateSubSets(std::vector<SubSet>& set, size_t dxy)
	{
		for (auto& s : this->S)
		{
			size_t i{ 1 };
			for (auto& t : set)
			{
				if (t.AddItem(s))
				{
					if (dxy == 0)s.SetGd(i);
					else if (dxy == 1)s.SetGx(i);
					else if (dxy == 2)s.SetGy(i);
					else if (dxy == 3)s.SetGphi(i);
					else if (dxy == 4)s.SetGtheta(i);
					else if (dxy == 5)s.SetGdGphi(i);
					break;
				}
				i++;
			}
		}
	}
	void CombineSubSets(vector<SubSet>& new_subsets,std::vector<SubSet>& first_set,std::vector<SubSet>& second_set, size_t dxy)
	{
		size_t m = first_set.size();
		size_t n = second_set.size();
		Size_t_matrix subset_Indexes;
		new_subsets.resize(m * n);
		size_t k{ 1 };
		for(size_t i=0;i<m;i++)
			for (size_t j = 0; j < n; j++)
			{
				subset_Indexes.AddItem(i, j, k);
				k++;
			}
		size_t size = first_set.size();
		for (auto& s : this->S)
		{
			size_t i{ 0 }; 
			for (auto& t1 : first_set)
			{
				if (t1.Pick(s))
				{
					size_t j{ 0 };
					for (auto& t2 : second_set)
					{
						if (t2.Pick(s))
						{
							new_subsets.at(subset_Indexes.GetItem(i, j) - 1).AddItemDirect(s);
							if		(dxy == 0)s.SetGd	 (subset_Indexes.GetItem(i, j));
							else if (dxy == 1)s.SetGx    (subset_Indexes.GetItem(i, j));
							else if (dxy == 2)s.SetGy	 (subset_Indexes.GetItem(i, j));
							else if (dxy == 3)s.SetGphi	 (subset_Indexes.GetItem(i, j));
							else if (dxy == 4)s.SetGtheta(subset_Indexes.GetItem(i, j));
							else if (dxy == 5)s.SetGdGphi(subset_Indexes.GetItem(i, j));
							break;
						}
						j++;
					}
				}
				i++;
			}
		}
	}
	void ShowSubSets(std::vector<SubSet>& set)
	{
		size_t total{ 0 };
		for (auto& ss : set) { ss.Show(); total=total+ss.GetSampleSize(); }
		cout << " *******************************************" << endl;
		cout << " TOTAL LINKS CHOSEN  : " << total << endl;
	}
	void ResetSubSets(std::vector<SubSet>& set)
	{
		for (auto& s : set)
			s.Reset();
		set.clear();
		set.erase(set.begin(), set.end());
	}

	void GetAverageHSubSet(std::vector<SubSet>& set, string file) // All receivers from a single transmitting point
	{
		Complex_matrix H;
		
		Complex_matrix result_H;
		Double_matrix result_Q;
		Complex_matrix result_GG;
		//bool valid;
		for (auto s : set)
		{
		//	s.Show();
			s.GetAverageH_matrix_1();
		//	H.Show();
			matrix<std::complex<double>>::AppendToTable(result_H, s.AverageH);
			matrix<double>::AppendToTable(result_Q, s.AverageQ);
			matrix<std::complex<double>>::AppendToTable(result_GG, s.AverageGG_Her);
		}
	//	result_H.Show();
	//	result_Q.Show();

		cout << " SUCCESSFUL TERMINALS : " << result_H.Rows_Count << endl;
		

		string file_out_polar_H; string file_out_rect_H;
		string file_out_polar_GG; string file_out_rect_GG;
		string file_out_Q; 
		file_out_polar_H = file;
		file_out_polar_H.replace(file.find_last_of('.'), 4, "_Average_polar_H.txt");
		file_out_rect_H = file;
		file_out_rect_H.replace(file.find_last_of('.'), 4, "_Average_rect_H.txt");

	//	cout << file_out_polar_H << endl;
	//	cout << file_out_rect_H << endl;

		file_out_Q = file;
		file_out_Q.replace(file.find_last_of('.'), 4, "_Average_Q.txt");

	//	cout << file_out_Q << endl;

		file_out_polar_GG = file;
		file_out_polar_GG.replace(file.find_last_of('.'), 4, "_Average_polar_GG.txt");
		file_out_rect_GG = file;
		file_out_rect_GG.replace(file.find_last_of('.'), 4, "_Average_rect_GG.txt");


		result_H.WriteFile(file_out_polar_H, POLAR);
		result_H.WriteFile(file_out_rect_H, RECT);
		result_Q.WriteFile(file_out_Q);
		result_GG.WriteFile(file_out_polar_GG, POLAR);
		result_GG.WriteFile(file_out_rect_GG, RECT);
	}
	void PrintSubSets(std::vector<SubSet>& set,string file)//,string file2)
	{
		if (set.size() > 0)
		{
			Double_matrix subSet;
			double mid;
			std::string units;
			cout << endl;
			for (size_t i = 1; i < set.at(0).Crieteria.size(); i++)set.at(0).Crieteria.at(i).Show();
			cout << endl;
			std::string name = set.at(0).Crieteria.at(0).ShowName(units);
			cout <<setw(5)<<"SUBSET#"<< setw(15) << name<<"("<<units<<")" << setw(12) << " TERMINALS# " <<setw(15)<<" MIMO CAPACITY"<< setw(20) << " SISO CAPACITY" << setw(20)<< "AVERAGE POWER(W)"<< setw(20)<< "D(METERS)"<< setw(20) << "Phi(RAD)"<<setw(20) << "Theta(RAD)" << setw(20) << "R(METERS)" <<endl;
			cout << " __________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;
			size_t j{ 0 };
			for (auto& s : set)
			{	
				if (s.GetSampleSize() > 0  && s.Status())
				{
					if (set.at(0) == s) {

					}
					else
					{
						cout << " MISMATCH FOUND AT SUBSET # :"; s.Show();
					}

					mid = s.Crieteria.at(0).RULES.at(0).Minimum_Value +(s.Crieteria.at(0).RULES.at(0).Step / 2);
					cout << setw(5) << j << setw(20) << mid << setw(10) << s.GetSampleSize() << setw(20) << s.GetAverageCapacity() << setw(20)<<s.GetAverageCapacity_SISO() << setw(20) <<s.GetAveragePower() << setw(20) << s.GetAverageD()<< setw(20) << s.GetAveragePhi()<< setw(20) << s.GetAverageTheta() << setw(20) << s.GetAverageR() << endl;
					subSet.AddItem(j, 0, static_cast<double>(s.GetSampleSize())); subSet.AddItem(j, 1, mid); subSet.AddItem(j, 2, s.GetAverageCapacity()); subSet.AddItem(j, 3, s.GetAverageCapacity_SISO()); subSet.AddItem(j, 4, s.GetAveragePower()); subSet.AddItem(j, 5, s.GetAverageD()); subSet.AddItem(j, 6, s.GetAveragePhi()); subSet.AddItem(j, 7, s.GetAverageTheta()); subSet.AddItem(j, 8, s.GetAverageR());
				//	for (auto t : s.Terminals)t.ShowBrief();
					j++;
				}
			}
			cout << " ___________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;
			for (size_t i = 0; i < j; i++)subSet.AddItem(i, 9, j);
			subSet.WriteFile(file);
		//	if(file2!="")subSet.WriteFile(file2);
		}
		
		GetAverageHSubSet(set, file);
	}
	std::vector<size_t> CreatOneDistanceSubsets2(bool remove_zero_cap, EXPOSURE check)
	{
		Tools::SetRESULTSFolder(check);
		std::string file=Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_Distance_Only.txt";
		Double_matrix subSet;
		std::vector<size_t> Zero_points;
		double mid;
		cout << setw(5) << "POINT #" << setw(15) << "RADIAL DISTANCE" << "(METERS)" << setw(12) << " MIMO CAPACITY" << setw(20) << " SISO CAPACITY" << setw(20) << "AVERAGE POWER(W)" << setw(20) << "D(METERS)" << setw(20) << "Phi(RAD)" << setw(20) << "Theta(RAD)" << setw(20) << "R(METERS)" << setw(20) << "GAIN" << endl;
		cout << " __________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;
		size_t j{ 0 }, jj{ 0 };
		for (auto& s : this->S)
		{
			mid = s.Position.R;
			cout << setw(5) << j << setw(20) << mid << setw(10) << s.GetCapacity() << setw(20) << s.GetCapacitySISO() << setw(20) << s.GetPower() << setw(20) << s.Position.Distance << setw(20) << s.Position.Phi << setw(20) << s.Position.Theta << setw(20) << s.Position.R << setw(20) << s.GetCapacity() / s.GetCapacitySISO() << endl;
			if (remove_zero_cap)
			{
				if (s.GetCapacity() != 0)
				{
					subSet.AddItem(jj, 0, static_cast<double>(1)); subSet.AddItem(jj, 1, Tools::Round(mid, 1)); subSet.AddItem(jj, 2, s.GetCapacity()); subSet.AddItem(jj, 3, s.GetCapacitySISO()); subSet.AddItem(jj, 4, s.GetPower()); subSet.AddItem(jj, 5, s.Position.Distance); subSet.AddItem(jj, 6, s.Position.Phi); subSet.AddItem(jj, 7, s.Position.Theta); subSet.AddItem(jj, 8, s.Position.R); subSet.AddItem(jj, 10, s.GetCapacity() / s.GetCapacitySISO());
					jj++;
				}
				else
					Zero_points.push_back(j);
			}
			else
			{
				subSet.AddItem(jj, 0, static_cast<double>(1)); subSet.AddItem(jj, 1, Tools::Round(mid, 1)); subSet.AddItem(jj, 2, s.GetCapacity()); subSet.AddItem(jj, 3, s.GetCapacitySISO()); subSet.AddItem(jj, 4, s.GetPower()); subSet.AddItem(jj, 5, s.Position.Distance); subSet.AddItem(jj, 6, s.Position.Phi); subSet.AddItem(jj, 7, s.Position.Theta); subSet.AddItem(jj, 8, s.Position.R); subSet.AddItem(jj, 10, s.GetCapacity() / s.GetCapacitySISO());
				jj++;
			}

			j++;
		}
		cout << " ___________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;
		
	//	subSet.SortOnColumn(1);
	//	subSet.Show();
	//	subSet.MakeTidyOnReferenceColumn(1);
	//	subSet.Show();
		for (size_t i = 0; i < subSet.Rows_Count; i++)subSet.AddItem(i, 9, subSet.Rows_Count);
		subSet.WriteFile(file); 
		GetDistribution(1, 1, Tools::RESULTSFolder + Tools::GetTestCase() + "/test_polar.txt", Tools::RESULTSFolder + Tools::GetTestCase() + "/test_rect.txt");
	//	GetAverageHSubSet(set, file);
		return Zero_points;
		
	}
	std::vector<size_t> CreatOneDistanceSubsets(bool remove_zero_cap, EXPOSURE check)
	{
		Tools::SetRESULTSFolder(check);
		std::string file = Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_Distance_Only.txt";
		Double_matrix subSet;
		std::vector<size_t> Zero_points;
		double mid;
		cout << setw(5) << "POINT #" << setw(15) << "RADIAL DISTANCE" << "(METERS)" << setw(12) << " MIMO CAPACITY" << setw(20) << " SISO CAPACITY" << setw(20) << "AVERAGE POWER(W)" << setw(20) << "D(METERS)" << setw(20) << "Phi(RAD)" << setw(20) << "Theta(RAD)" << setw(20) << "R(METERS)" << setw(20) << "GAIN" << endl;
		cout << " __________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;
		size_t j{ 0 }, jj{ 0 };
		;
		for (auto& s : this->GetEXPO(check, Zero_points).S)
		{
			mid = s.Position.R;
			cout << setw(5) << j << setw(20) << mid << setw(10) << s.GetCapacity() << setw(20) << s.GetCapacitySISO() << setw(20) << s.GetPower() << setw(20) << s.Position.Distance << setw(20) << s.Position.Phi << setw(20) << s.Position.Theta << setw(20) << s.Position.R << setw(20) << s.GetCapacity() / s.GetCapacitySISO() << endl;
			if (remove_zero_cap)
			{
				if (s.GetCapacity() != 0)
				{
					subSet.AddItem(jj, 0, static_cast<double>(1)); subSet.AddItem(jj, 1, Tools::Round(mid, 1)); subSet.AddItem(jj, 2, s.GetCapacity()); subSet.AddItem(jj, 3, s.GetCapacitySISO()); subSet.AddItem(jj, 4, s.GetPower()); subSet.AddItem(jj, 5, s.Position.Distance); subSet.AddItem(jj, 6, s.Position.Phi); subSet.AddItem(jj, 7, s.Position.Theta); subSet.AddItem(jj, 8, s.Position.R); subSet.AddItem(jj, 10, s.GetCapacity() / s.GetCapacitySISO());
					jj++;
				}
				else
					Zero_points.push_back(j);
			}
			else
			{
				subSet.AddItem(jj, 0, static_cast<double>(1)); subSet.AddItem(jj, 1, Tools::Round(mid, 1)); subSet.AddItem(jj, 2, s.GetCapacity()); subSet.AddItem(jj, 3, s.GetCapacitySISO()); subSet.AddItem(jj, 4, s.GetPower()); subSet.AddItem(jj, 5, s.Position.Distance); subSet.AddItem(jj, 6, s.Position.Phi); subSet.AddItem(jj, 7, s.Position.Theta); subSet.AddItem(jj, 8, s.Position.R); subSet.AddItem(jj, 10, s.GetCapacity() / s.GetCapacitySISO());
				jj++;
			}

			j++;
		}
		cout << " ___________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;

		//	subSet.SortOnColumn(1);
		//	subSet.Show();
		//	subSet.MakeTidyOnReferenceColumn(1);
		//	subSet.Show();
		for (size_t i = 0; i < subSet.Rows_Count; i++)subSet.AddItem(i, 9, subSet.Rows_Count);
		subSet.WriteFile(file);
		GetDistribution(1, 1, Tools::RESULTSFolder + Tools::GetTestCase() + "/test_polar.txt", Tools::RESULTSFolder + Tools::GetTestCase() + "/test_rect.txt");
		//	GetAverageHSubSet(set, file);
		return Zero_points;

	}
	std::vector<size_t> CreatOneDistanceSubsets(std::vector<size_t> remove_points)
	{
		std::string file = Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_Distance_Only.txt";
		Double_matrix subSet;
		std::vector<size_t> Zero_points;
		double mid;
		cout << setw(5) << "POINT #" << setw(15) << "RADIAL DISTANCE" << "(METERS)" << setw(12) << " MIMO CAPACITY" << setw(20) << " SISO CAPACITY" << setw(20) << "AVERAGE POWER(W)" << setw(20) << "D(METERS)" << setw(20) << "Phi(RAD)" << setw(20) << "Theta(RAD)" << setw(20) << "R(METERS)" << setw(20) << "GAIN" << endl;
		cout << " __________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;
		size_t j{ 0 }, jj{ 0 };
		bool add{true};
		for (auto& s : this->S)
		{
			add = true;
			mid = s.Position.R;
			cout << setw(5) << j << setw(20) << mid << setw(10) << s.GetCapacity() << setw(20) << s.GetCapacitySISO() << setw(20) << s.GetPower() << setw(20) << s.Position.Distance << setw(20) << s.Position.Phi << setw(20) << s.Position.Theta << setw(20) << s.Position.R << setw(20) << s.GetCapacity() / s.GetCapacitySISO() << endl;
			for (size_t z : remove_points)
			{
				if (z == j) {
					add = false; break;
				}
			}
			if (add)
			{
				subSet.AddItem(jj, 0, static_cast<double>(1)); subSet.AddItem(jj, 1, Tools::Round(mid, 1)); subSet.AddItem(jj, 2, s.GetCapacity()); subSet.AddItem(jj, 3, s.GetCapacitySISO()); subSet.AddItem(jj, 4, s.GetPower()); subSet.AddItem(jj, 5, s.Position.Distance); subSet.AddItem(jj, 6, s.Position.Phi); subSet.AddItem(jj, 7, s.Position.Theta); subSet.AddItem(jj, 8, s.Position.R); subSet.AddItem(jj, 10, s.GetCapacity() / s.GetCapacitySISO());
				jj++;
			}
			if (s.GetCapacity() == 0)Zero_points.push_back(j);
			j++;
		}
		cout << " ___________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;

		//	subSet.SortOnColumn(1);
		//	subSet.Show();
		//	subSet.MakeTidyOnReferenceColumn(1);
		//	subSet.Show();
		for (size_t i = 0; i < subSet.Rows_Count; i++)subSet.AddItem(i, 9, subSet.Rows_Count);
		subSet.WriteFile(file);
		GetDistribution(1, 1, Tools::RESULTSFolder + Tools::GetTestCase() + "/test_polar.txt", Tools::RESULTSFolder + Tools::GetTestCase() + "/test_rect.txt");
		//	GetAverageHSubSet(set, file);
		return Zero_points;

	}
	void CreatDistanceSubsets(configuration config) // Temp
	{
		float  D_TEST_START = 0;// 100.0338;
		float  D_TEST_END = 353.5534;// 278.5678;
		size_t D_TEST_POINTS = Tools::Samples_Count;

	//	float  PHI_TEST_START = 0;// 100.0338;
	//	float  PHI_TEST_END = (360 / 180.0) * (22.0 / 7.0);
	//	size_t PHI_TEST_POINTS = Tools::Samples_Count;

	//	float  THETA_TEST_START = 0;// 100.0338;
	//	float  THETA_TEST_END = (90 / 180.0) * (22.0 / 7.0);
	//	size_t THETA_TEST_POINTS = Tools::Samples_Count;

	//	std::vector<SubSet> SUBSETS=CreateSubSets(CreateCriteria(CRITERIA::DISTANCE, D_TEST_START, D_TEST_END, D_TEST_POINTS, 3, 4, 1));//, size_t rxPt)
		std::vector<SubSet> SUBSETS = CreateCriteria(CRITERIA::RADIAL_DISTANCE, D_TEST_START, D_TEST_END, D_TEST_POINTS, 1, 2, 1);
		std::vector<SubSet> SUBSETS_x = CreateCriteria(CRITERIA::RADIAL_DISTANCE, D_TEST_START, D_TEST_END, D_TEST_POINTS, 1, 2, 1);
		std::vector<SubSet> SUBSETS_y = CreateCriteria(CRITERIA::RADIAL_DISTANCE, D_TEST_START, D_TEST_END, D_TEST_POINTS, 1, 2, 1);
	//	std::vector<SubSet> SUBSETS_Phi = CreateCriteria(CRITERIA::AZIMUTH_ANGLE, PHI_TEST_START, PHI_TEST_END, PHI_TEST_POINTS, 1, 2, 1);
	//	std::vector<SubSet> SUBSETS_Theta = CreateCriteria(CRITERIA::ELEVATION_ANGLE, THETA_TEST_START, THETA_TEST_END, THETA_TEST_POINTS, 1, 2, 1);
		double margin = 10;//deg
		double a1 = ((0   - margin) / 180.0) * (22.0 / 7.0);
		double a2 = ((0   + margin) / 180.0) * (22.0 / 7.0);
		double b1 = ((180 - margin) / 180.0) * (22.0 / 7.0);
		double b2 = ((180 + margin) / 180.0) * (22.0 / 7.0);
		double c1 = ((90  - margin) / 180.0) * (22.0 / 7.0);
		double c2 = ((90  + margin) / 180.0) * (22.0 / 7.0);
		double d1 = ((270 - margin) / 180.0) * (22.0 / 7.0);
		double d2 = ((270 + margin) / 180.0) * (22.0 / 7.0);

		CreateSubSets(SUBSETS,0);
	//	this->ShowSubSets(SUBSETS);
		if (std::filesystem::create_directory(Tools::RESULTSFolder))cout << " RESULTS Directory Created" << endl; else { cout << " Directory is already created " << endl;}
		PrintSubSets(SUBSETS, Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_SubSets_Distance_Only.txt");
		ResetSubSets (SUBSETS);
	//	AddCriteria(CRITERIA::AZIMUTH_ANGLE, a1, a2, SUBSETS_x);
	//	AddCriteria(CRITERIA::AZIMUTH_ANGLE, b1, b2, SUBSETS_x);
	//	CreateSubSets(SUBSETS_x,1);
	//	PrintSubSets (SUBSETS_x, Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_SubSets_X.txt");
	//	ResetSubSets (SUBSETS_x);
	//	AddCriteria(CRITERIA::AZIMUTH_ANGLE, c1, c2, SUBSETS_y);
	//	AddCriteria(CRITERIA::AZIMUTH_ANGLE, d1, d2, SUBSETS_y);
	//	CreateSubSets(SUBSETS_y,2);
	//	PrintSubSets (SUBSETS_y, Tools::RESULTSFolder + Tools::GetTestCase() +"/Capacity_SubSets_Y.txt");
	//	CreateSubSets(SUBSETS_Phi, 3);
	//	PrintSubSets (SUBSETS_Phi, Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_SubSets_Phi.txt");
	//	CreateSubSets(SUBSETS_Theta, 4);
	//	PrintSubSets(SUBSETS_Theta, Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_SubSets_Theta.txt");
	////////////////////////////////////////////////////// COMBINED D & PHI  /////////////////////////////////////////////////////////
	//	size_t PHI_TEST_POINTS_2 = static_cast<float>(Tools::Samples_Count)/10;
		
	//	std::vector<SubSet> SUBSETS_Phi_2= CreateCriteria(CRITERIA::AZIMUTH_ANGLE, PHI_TEST_START, PHI_TEST_END, PHI_TEST_POINTS_2, 1, 2, 1);
	//	CreateSubSets(SUBSETS_Phi_2, 6);

		size_t D_TEST_POINTS_2 = static_cast<float>(Tools::Samples_Count) /10;

		std::vector<SubSet> SUBSETS_D = CreateCriteria(CRITERIA::RADIAL_DISTANCE, D_TEST_START, D_TEST_END, D_TEST_POINTS_2, 1, 2, 1);
		CreateSubSets(SUBSETS_D, 6);
		
		size_t D_PHI_TEST_POINTS = static_cast<float>(Tools::Samples_Count * Tools::Samples_Count)/100;
	//	std::vector<SubSet> SUBSETS_D_Phi = CreateCriteria(CRITERIA::AZIMUTH_ANGLE, PHI_TEST_START, PHI_TEST_END, D_PHI_TEST_POINTS, 1, 2, 1);
	//	CombineSubSets(SUBSETS_D_Phi,SUBSETS_D, SUBSETS_Phi_2, 5);
	//	PrintSubSets(SUBSETS_D_Phi, Tools::RESULTSFolder + Tools::GetTestCase() + "/Capacity_SubSets_D_Phi.txt");
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//	ShowPower(0, 1); 
		GetDistribution(1,1, Tools::RESULTSFolder + Tools::GetTestCase() + "/test_polar.txt", Tools::RESULTSFolder + Tools::GetTestCase() + "/test_rect.txt");
	///////////////////////////////////// Move cir foldrer to the corresponding case results folder and delete study area folder/////
		std::filesystem::path Case_Folder = Tools::RESULTSFolder + Tools::GetTestCase();
		cout << Case_Folder.string() << endl;
		std::uintmax_t n;
		switch (config)
		{
		case configuration::MIMO:
		//	std::filesystem::rename(Tools::Cir_Folder, Case_Folder / "cir");
		//	n = std::filesystem::remove_all(Tools::StudyArea_Folder);
		//	std::cout << "Deleted " << n << " files in directory:" << Tools::StudyArea_Folder.string() << endl;
			break;
		case configuration::SISO:
		//	std::filesystem::rename(Tools::Cir_Folder, Case_Folder / "MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");
			break;
		}
	}
//////////////////// Creating another set based on a criteria ///////////////////////////////////////////////////////

public:
	std::vector<Set_Line> S;
	std::vector<T_R_Set > Transmitters;
	std::vector<T_R_Set > Receivers   ;
};

