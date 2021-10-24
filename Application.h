#pragma once
#include"Set.h"

struct ULA {
	ULA()
	{
		Unit_Vector.resize(3);
	}
	ULA(size_t n, float s, float phi, float theta)
	{
		NumberOfElements = n;
		Spacing = s;
		Line_Direction.Phi = phi;
		Line_Direction.Theta = theta;
		Unit_Vector.resize(3);
		Unit_Vector[0] = cos(phi) * sin(theta);
		Unit_Vector[1] = sin(phi) * sin(theta);
		Unit_Vector[2] = cos(theta);
	}
	size_t NumberOfElements;
	float Spacing;
	Direction Line_Direction;
	valarray<float> Unit_Vector;
};
struct UPA {
	UPA(size_t n1, size_t n2, float s, float phi1, float phi2, float theta1, float theta2)
	{
		ULA One(n1, s, phi1, theta1);
		ULA Two(n2, s, phi2, theta2);
	}
	ULA One;
	ULA Two;
};
class Application
{
public:
	Application() {};
	static valarray<ComplexF> Steering(PATHS& p, ULA ula_R,ULA ula_T, float frequency) // for each item // Assumed the same ULA, or UPA at the transmitter and the receiver
	{
		valarray<ComplexF> Alpha_Delay(p.RAYS.size());
		size_t N_T = ula_T.NumberOfElements;
		size_t N_R = ula_R.NumberOfElements;
		float wave_length = 3.0e8 / frequency;
		valarray<float> Rx_path_direction(3);
		valarray<float> Tx_path_direction(3);
		valarray<ComplexF> Rx(N_R);
		valarray<ComplexF> Tx(N_T);
		ComplexF Path_Delay;
		float Theta_R, Theta_T;
		size_t i_n{ 0 };
		for (auto& n : p.RAYS)
		{
			//UnitVectors UV = p.DirectionUnitVectors();
			Rx_path_direction = n.Arrival.UnitVector() * ula_R.Unit_Vector;
			Tx_path_direction = n.Departure.UnitVector() * ula_T.Unit_Vector;
			Theta_R = (-44.0 / 7) * (ula_R.Spacing / wave_length) * (Rx_path_direction.sum());
			Theta_T = (-44.0 / 7) * (ula_T.Spacing / wave_length) * (Tx_path_direction.sum());
			
			for (float i = 0; i < N_T; i = i + 1.0)
			{
				Tx[i] = std::polar<float>(1, i * Theta_T);
			}
			for (float i = 0; i < N_R; i = i + 1.0)
			{
				Rx[i] = std::polar<float>(1, i * Theta_R);
			}
			Path_Delay = std::polar<float>(1.0, (-44.0 / 7) * static_cast<float>(n.Arrival_Time) * frequency);
			Alpha_Delay[i_n] = (Rx * Conjugate<float>(Tx)).sum() * Path_Delay;
			i_n++;
		}
		return Alpha_Delay; // everything except the doplar effect
	}
	
	static valarray<ComplexF> Steering(PATHS& p, UPA upa_R, UPA upa_T, float frequency) // for each item
	{

		valarray<ComplexF> Alpha_Delay(p.RAYS.size());
		size_t N1_R= upa_R.One.NumberOfElements;
		size_t N2_R = upa_R.Two.NumberOfElements;

		size_t N1_T = upa_T.One.NumberOfElements;
		size_t N2_T = upa_T.Two.NumberOfElements;

		float wave_length = 3.0e8 / frequency;

		valarray<float> Rx1_path_direction(3);
		valarray<float> Tx1_path_direction(3);
		valarray<float> Rx2_path_direction(3);
		valarray<float> Tx2_path_direction(3);

		valarray<ComplexF> Rx1(N1_R);
		valarray<ComplexF> Tx1(N1_T);
		valarray<ComplexF> Rx2(N2_R);
		valarray<ComplexF> Tx2(N2_T);

		valarray<ComplexF> Rx(N1_R * N2_R);
		valarray<ComplexF> Tx(N1_T * N2_T);

		ComplexF Path_Delay;
		float Theta_R1, Theta_T1, Theta_R2, Theta_T2;
		size_t i_n{ 0 };
		for (auto& n : p.RAYS)
		{
			Rx1_path_direction = n.Arrival.UnitVector() * upa_R.One.Unit_Vector;
			Tx1_path_direction = n.Departure.UnitVector() * upa_T.One.Unit_Vector;
			Rx2_path_direction = n.Arrival.UnitVector() * upa_R.Two.Unit_Vector;
			Tx2_path_direction = n.Departure.UnitVector() * upa_T.Two.Unit_Vector;

			Theta_R1 = (-44.0 / 7) * (upa_R.One.Spacing / wave_length) * (Rx1_path_direction.sum());
			Theta_T1 = (-44.0 / 7) * (upa_T.One.Spacing / wave_length) * (Tx1_path_direction.sum());
			Theta_R2 = (-44.0 / 7) * (upa_R.Two.Spacing / wave_length) * (Rx2_path_direction.sum());
			Theta_T2 = (-44.0 / 7) * (upa_T.Two.Spacing / wave_length) * (Tx2_path_direction.sum());

			for (float i = 0; i < N1_R; i = i + 1.0)
			{
				Rx1[i] = std::polar<float>(1, i * Theta_R1);
			}
			for (float i = 0; i < N2_R; i = i + 1.0)
			{
				Rx2[i] = std::polar<float>(1, i * Theta_R2);
			}
			for (float i = 0; i < N1_T; i = i + 1.0)
			{
				Tx1[i] = std::polar<float>(1, i * Theta_T1);
			}
			for (float i = 0; i < N2_T; i = i + 1.0)
			{
				Tx2[i] = std::polar<float>(1, i * Theta_T2);
			}
			Rx = Kronecker<ComplexF>(Rx1, Rx2);
			Tx = Kronecker<ComplexF>(Tx1, Tx2);
			Path_Delay = std::polar<float>(1.0, (-44.0 / 7) * static_cast<float>(n.Arrival_Time) * frequency);
			Alpha_Delay[i_n]=(Rx * Conjugate<float>(Tx)).sum() * Path_Delay;
			i_n++;
		}
		return Alpha_Delay; // everything except the doplar effect
	}
	static void OutputFiles(Set& set, ULA ula_R, ULA ula_T, float frequency,float tx_power, std::string data_file,std::string output_file)
	{
		size_t point{ 0 };
		size_t line{ 0 };
		float N{ 0 };//rays count
		float  effective_N{ 0 };//rays count
		size_t shift{ 0 };//rays count
		size_t m{ 0 }, k{ 0 };//rays count
		valarray<ComplexF> Alpha_delay;
		valarray<ComplexF> Beta;
		DirectionStatistics stat;
		Float_matrix Output;
		Float_matrix Data;
		//float norm_H{ 0.0 };
		for (auto& l : set.S)
		{
			for (auto& element_p : l.Pathes)
			{
				effective_N = static_cast<float>(element_p.RAYS.size());
				if (effective_N > N)
				{
					N = effective_N;
				}
			}
		}

		for (auto& l : set.S)
		{
			//norm_H = Norm<Complex>(l.M, 2);
			for (auto& element_p : l.Pathes)
			{
				Alpha_delay = Steering(element_p, ula_R, ula_T, frequency);
				Beta = Proposed_Beta(element_p, tx_power, Alpha_delay);
				effective_N = static_cast<float>(Alpha_delay.size());
				stat=element_p.Statistics();
				m = element_p.TX_ELEMENT;
				k = element_p.RX_ELEMENT;
				Output.AddItem(line, 0, point+1);
				Output.AddItem(line, 1, m);
				Output.AddItem(line, 2, k);
				Output.AddItem(line, 3, static_cast<float>(l.M.GetItem(m - 1, k - 1).real()));
				Output.AddItem(line, 4, static_cast<float>(l.M.GetItem(m - 1, k - 1).imag()));
				Output.AddItem(line, 5, effective_N);
				for (size_t i = 0; i < Alpha_delay.size(); i++)
				{
					Output.AddItem(line, 6 + 4 * i, Alpha_delay[i].real()); 
					Output.AddItem(line, 7 + 4 * i, Alpha_delay[i].imag()); 
					Output.AddItem(line, 8 + 4 * i, Beta[i].real());// Normalized
					Output.AddItem(line, 9 + 4 * i, Beta[i].imag());// Normalized
				}
				shift = 6 + (4* N);
				Output.AddItem(line, 0 + shift, stat.Arrival_Mean.Phi);
				Output.AddItem(line, 1 + shift, stat.Arrival_Mean.Theta);
				Output.AddItem(line, 2 + shift, stat.Departure_Mean.Phi);
				Output.AddItem(line, 3 + shift, stat.Departure_Mean.Theta);
				Output.AddItem(line, 4 + shift, stat.Arrival_AngularSpread.Phi);
				Output.AddItem(line, 5 + shift, stat.Arrival_AngularSpread.Theta);
				Output.AddItem(line, 6 + shift, stat.Departure_AngularSpread.Phi);
				Output.AddItem(line, 7 + shift, stat.Departure_AngularSpread.Theta);
				Output.AddItem(line, 8 + shift, stat.Delay_Mean);
				Output.AddItem(line, 9 + shift, stat.Arrival_Std.Phi); //cout << stat.Arrival_Std.Phi << endl;
				Output.AddItem(line, 10 + shift, stat.Arrival_Std.Theta);
				Output.AddItem(line, 11 + shift, stat.Departure_Std.Phi);
				Output.AddItem(line, 12 + shift, stat.Departure_Std.Theta);
				Output.AddItem(line, 13 + shift, l.DirectDistance);
				Output.AddItem(line, 14 + shift, l.ElevationAngle*180*7.0/22.0);
				Output.AddItem(line, 15 + shift, l.RxPosition.Height);
				Output.AddItem(line, 16 + shift, l.RxPosition.Phi);
				Output.AddItem(line, 17 + shift, l.RxPosition.Theta);
				Output.AddItem(line, 18 + shift, l.RxPosition.R);  // Add More ( X Y Z) when needed

				line++;
			}
			point++;
		}
		Data.AddItem(0, 0, point);
		Data.AddItem(0, 1, m);
		Data.AddItem(0, 2, k);
		Data.AddItem(0, 3, N); 
		Data.AddItem(0, 4, static_cast<double>(frequency));
		Data.Show();
	//	Output.Show();
		Data.WriteFile_NonComplex(data_file);
		Output.WriteFile_NonComplex(output_file);

	}
	static valarray<ComplexF>Proposed_Beta(PATHS& p,float tx_power, valarray<ComplexF> Alpha_delay)
	{
		valarray<ComplexF> beta(p.RAYS.size());
		size_t i{ 0 };
		for (auto& n : p.RAYS)
		{
			beta[i] = Beta_n(n, tx_power, Alpha_delay[i]);
			i++;
		}
		return beta;
	}
	static ComplexF Beta_n(Ray r, double tx_power, ComplexF alfa_delay)
	{
		Ray ray_path;
		ray_path.Set(r.Path_ID, r.Source_ID, r.Power / tx_power, r.Phase, r.Arrival_Time);
		return static_cast<ComplexF>(std::conj(ray_path.Voltage_Value)) / alfa_delay;

	}
	static ComplexF Beta(PATHS& p, double tx_power)
	{
		size_t i{ 0 };
		Ray ray_path;
		valarray<ComplexF> rays_power;
		rays_power.resize(p.RAYS.size());
		for (auto& r : p.RAYS)
		{
			ray_path.Set(r.Path_ID, r.Source_ID, r.Power / tx_power, r.Phase, r.Arrival_Time);
			rays_power[i] = static_cast<ComplexF>(ray_path.Voltage_Value);
			i++;
		}
		return rays_power.sum();
		
	}
	
	static void Test(Set& set)
	{
		
		size_t i{ 0 };
		double tx_power = 4000;// pow(10.0, 400.0) * 0.001;
		Complex ray_sum = Complex(0, 0);
		
		for (auto& l : set.S)
		{
			for (auto& p : l.Pathes)
			{
				ray_sum=Beta(p, tx_power);
				cout << " Rays Sum :" << std::conj(ray_sum) << " h(" << p.TX_ELEMENT << "," << p.RX_ELEMENT << ") : " << l.M.GetItem(p.TX_ELEMENT - 1, p.RX_ELEMENT - 1) << endl;
			}
		}
	}
	
};

 