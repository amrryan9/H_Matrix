#pragma once
#pragma once
#include"Tools.h"
#include"Ray.h"
struct VERTIX {
	VERTIX()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	VERTIX(float x1, float y1, float z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
	float x;
	float y;
	float z;
};
struct PATH {
	size_t path_number;
	size_t total_interactions_for_path;
	float received_power_dBm;
	float phase_deg;
	float time_of_arrival_sec;
	float arrival_theta_deg;
	float arrival_phi_deg;
	float departure_theta_deg;
	float departure_phi_deg;
	string interactions_summary;
	vector<VERTIX> interaction_points;
};
struct POINT {
	std::vector<PATH> Point_Paths;
	float received_power_dBm;
	float mean_time_of_arrival_sec;
	float delay_spread_sec;
	bool LOS; // true for LOS , false for NLOS
	VERTIX Position;
};
vector<float> Reflections(std::vector<PATH> Point_Paths, float total_received_power_dBm)
{
	float total_received_power_watt{ 0 };// = pow(10.0, total_received_power_dBm / 10) * 0.001;
	float received_power_watt = 0.0;
	vector<float>reflections(7); for (auto& r : reflections)r = 0.0;
	vector<float>reflections_dBm(7);
	float previous{ 0 };
	size_t n{ 0 };
	size_t i{ 0 };
	for (auto& p : Point_Paths)
	{
		received_power_watt = pow(10.0, p.received_power_dBm / 10) * 0.001;
		total_received_power_watt = total_received_power_watt + received_power_watt;
	}
	previous = 0;
	for (auto& p : Point_Paths)
	{
		n = p.total_interactions_for_path;
		if (n < 7)
		{
			received_power_watt = pow(10.0, p.received_power_dBm / 10) * 0.001;
			previous = reflections.at(n);
			reflections.at(n) = previous + received_power_watt / total_received_power_watt;
			if (received_power_watt / total_received_power_watt >= 1.0)
				cout << "Point # : " << i << " Total Power Watt : " << total_received_power_watt << " Path Power : " << received_power_watt << " Ratio : " << received_power_watt / total_received_power_watt << " Interactions : " << n << endl;
		}
		i++;
	}
	for (auto& r : reflections)
	{
		reflections_dBm.push_back(10 * log10(r / 0.001));
	}
	return reflections;
}
std::vector<bool> LOS(std::string pathes_file, std::string summary_file) // Read the paths files and return a LOS /NLOS flags . True LOS
{
	std::vector<bool> los_flag;
	std::vector<string> output = Tools::Read_ssv_File(pathes_file);
	std::stringstream converter;

	size_t NumberOfPoints{ 0 }, NumberOfPaths{ 0 };
	size_t file_size = output.size();
	if (file_size > 106) { converter << output.at(106); converter >> NumberOfPoints; converter.clear(); }
	std::vector<POINT>Points(NumberOfPoints);
	size_t j{ 107 };

	for (size_t i = 0; i < NumberOfPoints; i++)
	{
		j++;
		if (file_size > j) { converter << output.at(j); converter >> NumberOfPaths; converter.clear(); j++; }
		Points.at(i).Point_Paths.resize(NumberOfPaths);
		//	cout << " the read line is : " << output.at(j-1) << endl;
		//	cout << " point #: " << i + 1 << " Number of paths :" << NumberOfPaths <<" at line # "<<j<< endl;
		if (file_size > j) { converter << output.at(j); converter >> Points.at(i).received_power_dBm; converter.clear(); j++; }
		if (file_size > j) { converter << output.at(j); converter >> Points.at(i).mean_time_of_arrival_sec; converter.clear(); j++; }
		if (file_size > j) { converter << output.at(j); converter >> Points.at(i).delay_spread_sec; converter.clear(); j++; }
		for (size_t i1 = 0; i1 < NumberOfPaths; i1++)
		{
			if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).path_number; converter.clear(); j++; }
			if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).total_interactions_for_path; converter.clear(); j++; }
			if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).received_power_dBm; converter.clear(); j++; }
			if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).phase_deg; converter.clear(); j++; }
			if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).time_of_arrival_sec; converter.clear(); j++; }
			if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).arrival_theta_deg; converter.clear(); j++; }
			if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).arrival_phi_deg; converter.clear(); j++; }
			if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).departure_theta_deg; converter.clear(); j++; }
			if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).departure_phi_deg; converter.clear(); j++; }
			if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).interactions_summary; converter.clear(); j++; }
			Points.at(i).Point_Paths.at(i1).interaction_points.resize(Points.at(i).Point_Paths.at(i1).total_interactions_for_path + 2);
			//	cout <<"At path # : "<<i1 << " number of interactions : " << Points.at(i).Point_Paths.at(i1).total_interactions_for_path << " At line #" << j << endl;
			for (size_t i2 = 0; i2 < Points.at(i).Point_Paths.at(i1).total_interactions_for_path + 2; i2++)
			{
				//cout << output.at(j) << endl;
				//cout << Points.at(i).Point_Paths.at(i1).interaction_points.size() << endl;
				if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).interaction_points.at(i2).x; converter.clear(); j++; }
				if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).interaction_points.at(i2).y; converter.clear(); j++; }
				if (file_size > j) { converter << output.at(j); converter >> Points.at(i).Point_Paths.at(i1).interaction_points.at(i2).z; converter.clear(); j++; }
				//	cout << " interaction point : " << Points.at(i).Point_Paths.at(i1).interaction_points.at(i2).x << " " << Points.at(i).Point_Paths.at(i1).interaction_points.at(i2).y << " " << Points.at(i).Point_Paths.at(i1).interaction_points.at(i2).z << endl;
			}
		}
	}

	return los_flag;
}
