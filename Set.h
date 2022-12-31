#pragma once
#include "Set_Line.h"

#define element unsigned int


struct T_R_Set
{
	T_R_Set()
	{
		Id = 0;
		T_R_Points.clear();
	}
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
	bool write(std::ofstream& ofile)
	{
		ofile.write(reinterpret_cast<const char*>(&Id), sizeof(unsigned));
		unsigned size_1 = T_R_Points.size();
		ofile.write(reinterpret_cast<const char*>(&size_1), sizeof(unsigned));
		ofile.write(reinterpret_cast<const char*>(&T_R_Points[0]), size_1 * sizeof(element));
		return !ofile.fail();
	}
	bool read(std::ifstream& ifile)
	{
		ifile.read(reinterpret_cast<char*>(&Id), sizeof(unsigned));
		unsigned size_1 = 0;
		ifile.read(reinterpret_cast<char*>(&size_1), sizeof(unsigned));
		T_R_Points.resize(size_1);
		ifile.read(reinterpret_cast<char*>(&T_R_Points[0]), size_1 * sizeof(element));//
		return !ifile.fail();
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
	bool UpdateItem(std::vector<Ray> pathes_angles, unsigned t_set, unsigned  r_set, unsigned  t_point, unsigned  r_point, unsigned r, unsigned c)
	{
		//Update rays with angles 
		//Get Ray 
		PATHS& P = (this->GetPathes(t_set, r_set, t_point, r_point, r, c));
		bool found = false;
		if (pathes_angles.size() == P.RAYS.size()) // Modified Like that because there are error rays that is rejected at CIR and isn't at DOD
		{ 
			//*****************START************************
			size_t i{ 0 };
			for (auto& ray : pathes_angles)
			{
				if (ray.CheckTheSameRay(P.RAYS.at(i)))
				{
					P.RAYS.at(i).Arrival = ray.Arrival;
					P.RAYS.at(i).Departure = ray.Departure;
				}
				else
				{
					cout << " MISMATCH #2" << endl;
					P.RAYS.at(i).Show();
					ray.Show();
				}
				i++;
			}
			// Check for error rays and delete them
			PATHS CopyP = P;
			P.RAYS.clear();
			for (auto& rr : CopyP.RAYS)
				if (rr.Arrival_Time >= 0.0)
					P.RAYS.push_back(rr);
			
			// Is It Done ::
			
			for (auto& rr : (this->GetPathes(t_set, r_set, t_point, r_point, r, c)).RAYS)
				if (rr.Arrival_Time < 0)
				{
					cout << " Double Check :";
					rr.Show();
				}
			//******************END*************************
		}
		else
		{
			cout << " MISMATCH #3" << endl;
			cout << " CIR Pathes count : " << P.RAYS.size() << endl;
			cout << " DOD Pathes count : " << pathes_angles.size() << endl;
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
		GetDistribution(Environment::RESULTSFolder + Environment::GetTestCase() + "/test_rect", Environment::RESULTSFolder + Environment::GetTestCase() + "/test_polar");
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
	void SetExposure() // Also set DElay Spread and the K factor 
	{
		for (auto& s : this->S)
		{
			s.SetExposure();
			s.SetKFactor();
			s.SetDelaySpread();
		}
	}
	Set GetEXPO(EXPOSURE check)
	{
		size_t i_index{ 0 };
		Set* SS=new Set();
		SS->Receivers = this->Receivers;
		SS->Transmitters = this->Transmitters;
		if (check != EXPOSURE::ALL )//&& check !=EXPOSURE::NON
		{
			for(auto& l : this->S)
			{
				if (l.Expose == check) //.SetExposure()
					SS->AddItem(l);
			}
			cout << " Total Number of Points is : " << this->S.size() << " . Number of " << Set_Line::PrintExposure(check) << " Points is " << SS->S.size() << endl;
		}
		return *SS;
	}
	Set GetPureLOS() // Remove all other rays than the LOS one
	{
		size_t i_index{ 0 };
		Set S_LOS = this->GetEXPO(EXPOSURE::LOS);
		for (auto& l : S_LOS.S)
		{
			for (auto& p : l.Pathes)
			{
				if (p.RAYS.size() > 1) //has more than the LOS Ray
					p.RAYS.resize(1);
			}
		}
		return S_LOS;
	}
	Set OmitLOS() // Remove all LOS rays from a LOS points
	{
		size_t i_index{ 0 };
		Set S_LOS = this->GetEXPO(EXPOSURE::LOS);
		Ray r;
		size_t LOS_Path_ID{ 1 },Size{0}; //v3_3_31:
		Set* SS = new Set();
		SS->Receivers = S_LOS.Receivers;
		SS->Transmitters = S_LOS.Transmitters;
		bool Fit{ true };
		for (auto& l : S_LOS.S)
		{
			for (auto& p : l.Pathes)
			{
				if (p.RAYS.size() <= 1)
					Fit = false;
			}
			if (Fit)
			{
				SS->AddItem(l);
			}
		}
		/*
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
		*/
		for (auto& l : SS->S)
		{
			for (auto& p : l.Pathes)
			{
				if (p.RAYS.size() > 1)
				{
					r = p.RAYS.at(0);
					//make sure it is the LOS ray
					if (r.Path_ID == LOS_Path_ID)
					{
						Size = p.RAYS.size() - 1;
						r = p.RAYS.at(Size);
						p.RAYS.resize(Size);
						p.RAYS.at(0) = r;
					}
					else
						cout << " Something is Wrong !!!" << endl;
				}
			}
		}
		return *SS;
	}
	Set GetNormDelayLOS() // normalize delays of los points to the los component and sets the K factor for each element in a point
	{
		size_t i_index{ 0 };
		Set S_NORM_LOS = this->GetEXPO(EXPOSURE::LOS);
		Set* SS = new Set();
		double Los_Arrival_Time{ 0 };
		double Los_Power{ 0 };
		SS->Receivers = this->Receivers;
		SS->Transmitters = this->Transmitters;
		bool found{ true };
		for (auto& l : S_NORM_LOS.S)
		{
			found = true;
			for (auto& p : l.Pathes)
			{
				if (p.RAYS.size() > 1) //has more than the LOS Ray
				{
					Los_Arrival_Time = p.RAYS.at(0).Arrival_Time;
					Los_Power = p.RAYS.at(0).Power;
					if (Los_Arrival_Time > 0)
					{
						for (auto& r : p.RAYS)
						{
							r.Arrival_Time = r.Arrival_Time / Los_Arrival_Time;
						}
						found = found * true;
					}
					else
					{
						cout << " ERROR : ZERO TIME " << endl;
						found = false;
					}
				}
				else
					found = false;
			}
			if (found)
			{
			//	l.Show();
				SS->AddItem(l);
			}
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
			cout << setw(10) << i << " :," << L.RxPosition.Distance << " :," << setw(10) << L.RxPosition.Height << " :," << setw(10) << L.RxPosition.Phi << " :," << setw(10) << L.RxPosition.Theta << " :," << setw(10) << L.RxPosition.R; L.ShowPower(txEle, rxEle);// << endl;
		}
		cout << " Number of Terminals :" << S_size << endl;
	}
	void ShowPower(size_t tx_set, size_t tx_pt, size_t tx_ele, size_t rx_set, size_t rx_pt, size_t rx_ele)   // Print power as it would appear in wireless insite. from the transmitter Element to receiver Element for all terminal points
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
			cout << " RX POINT # : " << l.Receiver_Point << endl;
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

	void ShowRXPoints(ComplexForm form = RECT)
	{
		/// Show The world
		size_t rx_elements, tx_elements;
		size_t index{ 1 };
		cout << setw(10) << "item #  " << setw(10) << "RX Point #" << setw(10) << "RX Set#" << setw(32) << "Position RX         " <<setw(32)<<"Position TX         " << setw(26) << "Power(dBm)     " << setw(16) << "Exposure" << setw(15) << "TX set" << setw(15) << "TX Point" << setw(100) << "H_Matrix                              " << endl;
		cout << setw(27) << " " << setw(8) << "D  " << setw(8) << "R " << setw(8) << "Phi " << setw(8) << "Theta"<< setw(8) << "D  " << setw(8) << "R " << setw(8) << "Phi " << setw(8) << "Theta";
		if (this->S.size() > 0)
		{
			rx_elements=this->S.at(0).M.Columns_Count;
			tx_elements = this->S.at(0).M.Rows_Count;
			for (size_t i = 0; i < rx_elements; i++)
				cout <<setw(static_cast<size_t>(26.0/ static_cast<float>(rx_elements)))<< "Rx Ele(" << i + 1 << ")";
			cout << setw(46) << " ";
			for (size_t i = 0; i < tx_elements; i++)
				for (size_t j = 0; j < rx_elements; j++)
					cout << setw(static_cast<size_t>(150.0 / (static_cast<float>(rx_elements)* static_cast<float>(tx_elements)))) << "    h(" << i + 1 <<","<<j+1 << ")     ";
			cout << endl;
			for (auto l : this->S)
			{
				cout << setw(5) << index << setw(10) << l.Receiver_Point << setw(12) << l.Receiver_Set << setw(8) << l.RxPosition.Distance << setw(8) << l.RxPosition.R << setw(8) << l.RxPosition.Phi << setw(8) << l.RxPosition.Theta << setw(6) << l.TxPosition.Distance << setw(9) << l.TxPosition.R << setw(8) << l.TxPosition.Phi << setw(8) << l.TxPosition.Theta;
				for (size_t i = 0; i < rx_elements; i++)
					cout << setw(static_cast<size_t>(26.0 / static_cast<float>(rx_elements))+2) << Tools::Round2(l.Power.Shrink().GetItem(0, i), 3);
				switch (l.Expose)
				{
				case EXPOSURE::NON:
					cout << setw(12) << "NON";
					break;
				case EXPOSURE::LOS:
					cout << setw(12) << "LOS";
					break;
				case EXPOSURE::NLOS:
					cout << setw(12) << "NLOS";
					break;
				case EXPOSURE::ALL:
					cout << setw(12) << "ALL";
					break;
				}
				cout << setw(16) << l.Transmitter_Set << setw(12) << l.Transmitter_Point;
				cout << setw(10) << " ";
				for (size_t i = 0; i < tx_elements; i++)
					for (size_t j = 0; j < rx_elements; j++)
					{
						cout << setw(static_cast<size_t>(200.0 / (static_cast<float>(rx_elements) * static_cast<float>(tx_elements)))) << Tools::PrintComplex(l.M.GetItem(i, j), form, 3)<<"  ";
					}
				cout << endl;
			//	l.ShowPathes(SHOW_HEADER::HEADER_ON);
				index++;

			}
		}
	}
	void WriteRXPoints(std::string file_out,ComplexForm form = RECT)
	{
		// this function writes the Receiver Points show to a .csv file the input file name is assumed t have the extension already
		std::string parent_directory = file_out;
		size_t position = file_out.find_last_of("/");
		std::string file_name = parent_directory.substr(position);
		parent_directory.erase(position, file_name.size());
		file_name.erase(0, 1);
		if (!std::filesystem::exists(parent_directory))
		{
			if (std::filesystem::create_directory(parent_directory))cout << parent_directory << " Directory Created" << endl; else { cout << parent_directory << " Directory can't be created " << endl; exit(0); }
		}
		std::ofstream out{ file_out , std::ios_base::out | std::ios_base::trunc };//+ extension
		std::ostream_iterator<string> out_iter2{ out, " " };

		vector<std::string>row;
		std::stringstream converter;
		std::string Line{""};
		string i_1,j_1;
		/// Show The world
		size_t rx_elements, tx_elements;
		size_t index{ 1 };	
			
		if (this->S.size() > 0)
		{
			rx_elements = this->S.at(0).M.Columns_Count;
			tx_elements = this->S.at(0).M.Rows_Count;
			Line = "item #,RX Point #,RX Set#,RX Position,,,,TX Position,,,,Direct Distance,Elevation Angle,Power(dBm),";
			for (size_t i = 1; i < rx_elements; i++)Line = Line + ",";
			Line = Line + "Exposure,TX set,TX Point,H_Matrix" + "\n";
			row.push_back(Line); Line.clear();
			Line = ",,,D,R,Phi,Theta,D,R,Phi,Theta,,";
			for (size_t i = 0; i < rx_elements; i++)
			{
				converter << (i + 1); converter >> i_1; converter.clear();
				Line = Line + ",Rx Ele(" + i_1 + ")";
			}
			Line = Line +",,,";
			i_1.clear();
			for (size_t i = 0; i < tx_elements; i++)
				for (size_t j = 0; j < rx_elements; j++)
				{
					converter << (i + 1); converter >> i_1; converter.clear();
					converter << (j + 1); converter >> j_1; converter.clear();
					Line = Line + ",h("+i_1+"-"+j_1+")" ;//\",\"
				}	
		row.push_back(Line + "\n"); Line.clear();
		string index_,l_Receiver_Point, l_Receiver_Set, l_rxPosition_Distance, l_rxPosition_R, l_rxPosition_Phi, l_rxPosition_Theta, l_txPosition_Distance, l_txPosition_R, l_txPosition_Phi, l_txPosition_Theta, l_Transmitter_Set, l_Transmitter_Point,l_Direct_Distance,l_Elevation_Angle,power_;
		
		for (auto l : this->S)
		{
			converter << index;							converter >> index_;					converter.clear();
			converter << l.Receiver_Point;				converter >> l_Receiver_Point;			converter.clear();
			converter << l.Receiver_Set;				converter >> l_Receiver_Set;			converter.clear();
			converter << l.RxPosition.Distance;			converter >> l_rxPosition_Distance;		converter.clear();
			converter << l.RxPosition.Phi;				converter >> l_rxPosition_Phi;			converter.clear();
			converter << l.RxPosition.Theta;			converter >> l_rxPosition_Theta;		converter.clear();
			converter << l.RxPosition.R;				converter >> l_rxPosition_R;			converter.clear();
			converter << l.TxPosition.Distance;			converter >> l_txPosition_Distance;		converter.clear();
			converter << l.TxPosition.Phi;				converter >> l_txPosition_Phi;			converter.clear();
			converter << l.TxPosition.Theta;			converter >> l_txPosition_Theta;		converter.clear();
			converter << l.TxPosition.R;				converter >> l_txPosition_R;			converter.clear();
			converter << l.Transmitter_Set;				converter >> l_Transmitter_Set;			converter.clear();
			converter << l.Transmitter_Point;			converter >> l_Transmitter_Point;		converter.clear();
			converter << l.DirectDistance;				converter >> l_Direct_Distance;			converter.clear();
			converter << l.ElevationAngle;				converter >> l_Elevation_Angle;			converter.clear();

			Line= index_+","+l_Receiver_Point +"," + l_Receiver_Set + "," + l_rxPosition_Distance + "," + l_rxPosition_R +"," + l_rxPosition_Phi +","+ l_rxPosition_Theta+"," + l_txPosition_Distance + "," + l_txPosition_R + "," + l_txPosition_Phi + "," + l_txPosition_Theta+","+l_Direct_Distance+","+l_Elevation_Angle;
			for (size_t i = 0; i < rx_elements; i++)
			{
				converter << Tools::Round2(l.Power.Shrink().GetItem(0, i), 3); converter >> power_; converter.clear();
				Line = Line +"," + power_;
			}
			switch (l.Expose)
			{
			case EXPOSURE::NON:
				Line=Line+"," + "NON";
				break;
			case EXPOSURE::LOS:
				Line=Line+ "," + "LOS";
				break;
			case EXPOSURE::NLOS:
				Line=Line+ "," + "NLOS";
				break;
			case EXPOSURE::ALL:
				Line=Line+ "," + "ALL";
				break;
			}
			Line= Line+ "," + l_Transmitter_Set + "," + l_Transmitter_Point;
			for (size_t i = 0; i < tx_elements; i++)
				for (size_t j = 0; j < rx_elements; j++)
				{
					Line=Line+ "," + Tools::PrintComplex(l.M.GetItem(i, j), form, 3);
				}
			row.push_back(Line + "\n"); Line.clear();
			index++;
			}
		}
		std::copy(std::begin(row), std::end(row), out_iter2);
		out_iter2 = "\n";
		row.clear();
	}

	Set* Filter(PROPERITIES p0,double p0_max, double p0_min=0.0, PROPERITIES p1= PROPERITIES::EMPTY_PROP, double p1_max=0.0, double p1_min = 0.0, PROPERITIES p2 = PROPERITIES::EMPTY_PROP,double p2_max = 0.0, double p2_min = 0.0, PROPERITIES p3 = PROPERITIES::EMPTY_PROP, double p3_max = 0.0, double p3_min = 0.0, PROPERITIES p4 = PROPERITIES::EMPTY_PROP, double p4_max = 0.0, double p4_min = 0.0, PROPERITIES p5 = PROPERITIES::EMPTY_PROP, double p5_max = 0.0, double p5_min = 0.0, PROPERITIES p6 = PROPERITIES::EMPTY_PROP, double p6_max = 0.0, double p6_min = 0.0, PROPERITIES p7 = PROPERITIES::EMPTY_PROP, double p7_max = 0.0, double p7_min = 0.0, PROPERITIES p8 = PROPERITIES::EMPTY_PROP, double p8_max = 0.0, double p8_min = 0.0, PROPERITIES p9 = PROPERITIES::EMPTY_PROP, double p9_max = 0.0, double p9_min = 0.0)
	{
		Set* pSS = new Set();
		pSS->Receivers = this->Receivers;
		pSS->Transmitters = this->Transmitters;
		for (auto& l : this->S)
		{
			if (l.CheckProperity(p0, p0_max, p0_min) && l.CheckProperity(p1, p1_max, p1_min) && l.CheckProperity(p2, p2_max, p2_min) && l.CheckProperity(p3, p3_max, p3_min) && l.CheckProperity(p4, p4_max, p4_min) && l.CheckProperity(p5, p5_max, p5_min) && l.CheckProperity(p6, p6_max, p6_min) && l.CheckProperity(p7, p7_max, p7_min) && l.CheckProperity(p8, p8_max, p8_min) && l.CheckProperity(p9, p9_max, p9_min))
			{
				pSS->AddItem(l);
			}
		}
		return pSS;
	}
	bool Save(std::string file)
	{
		bool flag{ true };
		std::ofstream ofile2(file, std::ios::binary);
		unsigned size_1,size_2,size_3;
		size_1 = this->S.size(); 
		size_2 = this->Transmitters.size(); 
		size_3 = this->Receivers.size();
		if (ofile2.is_open())
		{
			ofile2.write(reinterpret_cast<const char*>(&size_1), sizeof(unsigned));
			ofile2.write(reinterpret_cast<const char*>(&size_2), sizeof(unsigned));
			ofile2.write(reinterpret_cast<const char*>(&size_3), sizeof(unsigned)); 
			for (auto& s : this->S)
				flag = flag * s.write(ofile2);
			for (auto& s : this->Transmitters)
				flag = flag * s.write(ofile2);
			for (auto& s : this->Receivers)
				flag = flag * s.write(ofile2);
			ofile2.close();
		}
		return flag * !ofile2.fail();
	}
	bool Load(std::string file)
	{
		std::ifstream ifile2(file, std::ios::binary);
		unsigned size_1{ 0 }, size_2{ 0 }, size_3{ 0 };
		bool flag{ true };

		if (ifile2.is_open())
		{
			ifile2.read(reinterpret_cast<char*>(&size_1), sizeof(unsigned)); 
			ifile2.read(reinterpret_cast<char*>(&size_2), sizeof(unsigned)); 
			ifile2.read(reinterpret_cast<char*>(&size_3), sizeof(unsigned)); 
			this->S.clear();
			for (size_t i = 0; i < size_1; i++)
			{
				Set_Line l;
				flag=flag * l.read(ifile2);
				this->S.push_back(l);
			}
			this->Transmitters.clear();
			for (size_t i = 0; i < size_2; i++)
			{
				T_R_Set tr;
				flag = flag * tr.read(ifile2);
				this->Transmitters.push_back(tr);
			}
			this->Receivers.clear();
			for (size_t i = 0; i < size_3; i++)
			{
				T_R_Set tr;
				flag = flag * tr.read(ifile2);
				this->Receivers.push_back(tr);
			}
			ifile2.close();
		}
		return flag * !ifile2.fail();
	}
//////////////////// Creating another set based on a criteria ///////////////////////////////////////////////////////

public:
	std::vector<Set_Line> S;
	std::vector<T_R_Set > Transmitters;
	std::vector<T_R_Set > Receivers   ;
};

