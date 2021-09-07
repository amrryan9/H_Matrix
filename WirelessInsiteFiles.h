#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include<sstream>
#include<iomanip>
#include"Tools.h"
#include"CommunicationSystem.h"
using namespace std;
class WirelessInsiteFiles
{
public:
	WirelessInsiteFiles() {}
	bool SetCommunicationSystem(CommunicationSystem* system)
	{
		if (system != nullptr)
		{
			this->CommSystem = *system;
			return true;
		}
		return false;
	}
	void WriteFiles_1(std::string file_out)
	{

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
		//****************************************************************************************
		vector<std::string>row;
	//	std::stringstream converter;
	//	std::string Line{ "" };
		//****************************************************************************************
		// Writing The file
		//********************** BEGIN SET OF POINTS *********************************
		for (auto& p_set : CommSystem.PointsSets)
		{
			if (p_set != nullptr)ConfigureSetOfPoints(row, *p_set);
			else
				cout << " ERROR : Points Set Null pointer AT :  " << endl;
		}
		
	//	ConfigureSetOfPoints(row, Points);
		//********************** END SET OF POINTS *********************************
		//********************** BEGIN SET OF POINTS *********************************
	//	ConfigureSetOfPoints(row, Points);
		//********************** END SET OF POINTS *********************************
		cout << row.size() << endl;
		std::copy(std::begin(row), std::end(row), out_iter2);
		out_iter2 = "\n";
		row.clear();

	}
	void WriteFiles_2(std::string file_out)
	{
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
		std::string Line{ "" };
		//****************************************************************************************
		// Writing The file
		char Feature{ 0 }; // This to be changed
		std::string Parent_Directory{ "" };
		//****************************************************************************************
		row.push_back("Format type:keyword version: 1.1.0\n");
		row.push_back("begin_<project> Untitled Project\n");
		row.push_back("project_id 5368\n");
		row.push_back("begin_<globals> \n");
		row.push_back("longitude 0\n");
		row.push_back("latitude 0\n");
		row.push_back("end_<globals>\n");
		row.push_back("FirstAvailableUnknownLayoutNumber 0\n");
		row.push_back("FirstAvailableStudyAreaNumber 1\n");
		// ----------------New Version------------------------ -
		row.push_back("begin_<caches> \n");
		row.push_back("begin_<cache> \n");
		row.push_back("type X3DGeometry\n");
		row.push_back("filename ./MIMO_UAV_10_LOS.X3DGeometry.cache\n");
		row.push_back("valid false\n");
		row.push_back("end_<cache>\n");
		row.push_back("end_<caches>\n");
		// ----------------New Version-------------------- -
		row.push_back("begin_<studyarea> MIMO_BS_UAV_TERMINALS\n");
		row.push_back("StudyAreaNumber 0\n");
		row.push_back("active\n");
		row.push_back("begin_<partitioning> \n");
		row.push_back("partitioning_type disabled\n");
		row.push_back("queuing_type disabled\n");
		row.push_back("max_threads 0\n");
		row.push_back("num_partitions 0\n");
		row.push_back("end_<partitioning>\n");
		row.push_back("begin_<apg_acceleration> \n");
		row.push_back("enabled yes\n");
		row.push_back("workflow_mode full\n");
		row.push_back("binary_output_mode per_path_utm\n");
		row.push_back("binary_rate 0 active\n");
		row.push_back("database_mode write_siso\n");
		row.push_back("path_depth 25\n");
		row.push_back("adjacency_distance 10\n");
		row.push_back("end_<apg_acceleration>\n");
		row.push_back("begin_<diffuse_scattering> \n");
		row.push_back("enabled no\n");
		row.push_back("diffuse_reflections 2\n");
		row.push_back("diffuse_diffractions 1\n");
		row.push_back("diffuse_transmissions 0\n");
		// ----------------New Version-------------------- -
		row.push_back("final_interaction_only no\n");
		// ----------------New Version-------------------- -
		row.push_back("end_<diffuse_scattering>\n");
		row.push_back("autoboundary 0\n");
		row.push_back("begin_<model> \n");
		row.push_back("x3d\n");
		row.push_back("num_threads 4\n");
		// row.push_back("use_gpu Yes\n");
		row.push_back("initial_ray_mode uniform_sweep\n");
		// row.push_back("foliage_model 0\n");
		row.push_back("foliage_model 2\n");
		// row.push_back("foliage_attenuation_vert 1\n");
		// row.push_back("foliage_attenuation_hor 1\n");
		// ----------------New Version-------------------- -
		row.push_back("foliage_attenuation 1\n");
		// ----------------New Version-------------------- -
		row.push_back("plane_wave_phase_reference automatic\n");
		// row.push_back("250 250 21\n");

		if (Feature == 1)
			row.push_back("500 500 31.5\n");
		else if (Feature == 0)
			row.push_back("0 0 0\n");

		// ----------------New Version-------------------- -
		row.push_back("max_reflections 1\n");
		row.push_back("max_transmissions 1\n");
		// ----------------New Version-------------------- -
		row.push_back("begin_<OutputRequests> \n");
		row.push_back("CEF no\n");
		row.push_back("ComplexImpulseResponse yes\n");
		row.push_back("DelaySpread no\n");
		row.push_back("DirectionOfArrival no\n");
		row.push_back("DirectionOfDeparture no\n");
		row.push_back("ElectroMagneticFields no\n");
		row.push_back("FSPathloss no\n");
		row.push_back("FSPower no\n");
		row.push_back("MeanDirectionOfArrival no\n");
		row.push_back("MeanDirectionOfDeparture no\n");
		row.push_back("MeanTimeOfArrival no\n");
		row.push_back("Pathloss yes\n");
		row.push_back("Paths yes\n");
		row.push_back("Power yes\n");
		row.push_back("TimeOfArrival no\n");
		row.push_back("XPathloss no\n");
		row.push_back("end_<OutputRequests>\n");
		row.push_back("end_<model>\n");
		row.push_back("begin_<boundary> \n");
		row.push_back("begin_<reference> \n");
		row.push_back("cartesian\n");
		row.push_back("longitude 0\n");
		row.push_back("latitude 0\n");
		row.push_back("visible no\n");
		row.push_back("terrain\n");
		row.push_back("end_<reference>\n");
		row.push_back("zmin 0\n");
		row.push_back("zmax 120\n");
		row.push_back("nVertices 4\n");
		row.push_back("0 0 0\n");
		row.push_back("1000 0 0\n");
		row.push_back("1000 1000 0\n");
		row.push_back("0 1000 0\n");
		row.push_back("end_<boundary>\n");
		row.push_back("begin_<MonteCarlo> \n");
		row.push_back("monte_carlo_updated no\n");
		row.push_back("monte_carlo_active no\n");
		row.push_back("monte_carlo_mean yes\n");
		row.push_back("monte_carlo_min no\n");
		row.push_back("monte_carlo_max no\n");
		row.push_back("monte_carlo_median no\n");
		row.push_back("monte_carlo_sdev no\n");
		row.push_back("monte_carlo_iterations 10\n");
		row.push_back("monte_carlo_seed 1\n");
		row.push_back("end_<MonteCarlo>\n");
		row.push_back("begin_<MPE> \n");
		row.push_back("mpe_is_active inactive\n");
		row.push_back("mpestandard controlled\n");
		row.push_back("mpe_averaging_time 300\n");
		row.push_back("mpe_averaging_time_short 0.1\n");
		row.push_back("mpe_user_efield_peak 100000\n");
		row.push_back("mpe_user_efield_rms 61.4\n");
		row.push_back("mpe_user_hfield_rms 0.163\n");
		row.push_back("mpe_user_power_short 10\n");
		row.push_back("mpe_user_power 2\n");
		row.push_back("end_<MPE>\n");
		row.push_back("end_<studyarea>\n");
		if (Feature == 1)
			this->City_File = "/ ITU_City.city";
		else
			this->City_File = "/Empty_City(2).city";

	///	if (Feature == 1)
	//	{
			row.push_back("begin_<feature> \n");
			row.push_back("feature 0\n");
			row.push_back("city\n");
			row.push_back("active\n");
			row.push_back("filename "+ Parent_Directory+ this->City_File +"\n");
			row.push_back("end_<feature>\n");
	//	}
	/*	else if (Feature == 0)  I HOPE IT WORKS
		{
			row.push_back("begin_<feature> \n");
			row.push_back("feature 0\n");
			row.push_back("city\n");
			row.push_back("inactive\n");
			row.push_back("filename "+ Parent_Directory+"/ ITU_City.city\n");
			row.push_back("end_<feature>\n");
			row.push_back("begin_<feature> \n");
			row.push_back("feature 1\n");
			row.push_back("city\n");
			row.push_back("active\n");
			row.push_back("filename"+ Parent_Directory+"/Empty_City(2).city\n");
			row.push_back("end_<feature>\n");
		}*/
		row.push_back("begin_<txrx_sets> \n");
		row.push_back("filename "+this->TxRx_File+"\n");//./MIMO_UAV_10_LOS.txrx
		row.push_back("FirstAvailableTxRxNumber 3\n");
		row.push_back("end_<txrx_sets>\n");
		row.push_back("FirstAvailableCommSystemNumber 0\n");
		//******* Configuration of the antenna of an Wireless Point********************
		for(auto& ant_array:this->CommSystem.AntennaArrays)
			ConfigureAntennaArray(row, *ant_array);

	//	ConfigureAntennaArray(row, this->Antenna_Array_BS, Waveform_Index);
		//SOLVE// row.push_back("position -//d -//1.7f -0\r\n', sin(Rotation_Angle) * Antenna_Element_spacing * 3 / 2, cos(Rotation_Angle) * Antenna_Element_spacing * 3 / 2);//, Antenna_Element_spacing / 2);
		//SOLVE// row.push_back("position -//d -//1.7f -0\r\n', sin(Rotation_Angle) * Antenna_Element_spacing / 2, cos(Rotation_Angle) * Antenna_Element_spacing / 2);//, Antenna_Element_spacing / 2);
		//SOLVE// row.push_back("position //d //1.7f -0\r\n', sin(Rotation_Angle) * Antenna_Element_spacing / 2, cos(Rotation_Angle) * Antenna_Element_spacing / 2);//, Antenna_Element_spacing / 2);
		//SOLVE// row.push_back("position //d //1.7f -0\r\n', sin(Rotation_Angle) * Antenna_Element_spacing * 3 / 2, cos(Rotation_Angle) * Antenna_Element_spacing * 3 / 2);//, Antenna_Element_spacing / 2);
		//******* END Configuration of the antenna of an Wireless Point****************
		//******* Configuration of the antenna of an Wireless Point********************
	//	ConfigureAntennaArray(row, this->Antenna_Array_Terminal, Waveform_Index);
		//SOLVE// row.push_back("position -//d -//1.7f -0\r\n', sin(Rotation_Angle) * Antenna_Element_spacing / 2, cos(Rotation_Angle) * Antenna_Element_spacing / 2);
		//SOLVE// row.push_back("position //d //1.7f -0\r\n', sin(Rotation_Angle) * Antenna_Element_spacing / 2, cos(Rotation_Angle) * Antenna_Element_spacing / 2);
		//******* END Configuration of the antenna of an Wireless Point****************
		
		//****************** Configuration of the Carrier *****************************
		for (auto& c : this->CommSystem.Carriers)
			ConfigureCarrier(row,*c);
		//****************** END Configuration of the Carrier *************************
		row.push_back("FirstAvailableFilterNumber 0\n");
		/**********************     CALCULATION REQUESTS *****************************/
		row.push_back("begin_<requests> \n");
		row.push_back("cartesian\n");
		row.push_back("sealevel\n");
		row.push_back("local\n");
		row.push_back("CalculationMode New\n");
		row.push_back("MaxRenderedPaths 25\n");
		row.push_back("FieldAnimationIncrement 10\n");
		row.push_back("FieldAnimationTimeAveraged yes\n");
		row.push_back("CEF no\n");
		row.push_back("ComplexImpulseResponse yes\n");
		row.push_back("DelaySpread no\n");
		row.push_back("FieldAnimation no\n");
		row.push_back("DirectionOfArrival no\n");
		row.push_back("DirectionOfDeparture no\n");
		row.push_back("ElectricFieldVsFrequency no\n");
		row.push_back("ElectricFieldVsTime no\n");
		row.push_back("EMFields no\n");
		row.push_back("FSPathloss no\n");
		row.push_back("FSPower no\n");
		row.push_back("InputData no\n");
		row.push_back("MeanDirectionOfArrival no\n");
		row.push_back("MeanDirectionOfDeparture no\n");
		row.push_back("MeanTimeOfArrival no\n");
		row.push_back("Pathloss yes\n");
		row.push_back("Paths yes\n");
		row.push_back("Power yes\n");
		row.push_back("PowerDelayProfile no\n");
		row.push_back("TimeOfArrival no\n");
		row.push_back("XPathloss no\n");
		row.push_back("TerrainProfile no\n");
		row.push_back("end_<requests>\n");
		/********************** END CALCULATION REQUESTS *****************************/
		row.push_back("begin_<Scales> \n");
		row.push_back("begin_<MpeThreshhold> \n");
		row.push_back("AutoScaling 0\n");
		row.push_back("DrawValues 0\n");
		row.push_back("AutoUpdating 0\n");
		row.push_back("Discrete 1\n");
		row.push_back("UseGlobalOpacity 1\n");
		row.push_back("ManualValuesSet 1\n");
		row.push_back("ClampedHigh 1\n");
		row.push_back("ClampedLow 1\n");
		row.push_back("Alpha 1.000e+000\n");
		row.push_back("ManualMin 0.000e+000\n");
		row.push_back("ManualMax 2.000e+002\n");
		row.push_back("TextColor 1.000 1.000 1.000\n");
		row.push_back("Colors 4\n");
		row.push_back("0.300 0.000 0.500\n");
		row.push_back("0.000 1.000 0.000\n");
		row.push_back("1.000 1.000 0.000\n");
		row.push_back("1.000 0.000 0.000\n");
		row.push_back("PartitionValues \n");
		row.push_back("3\n");
		row.push_back("0.001 50.000 100.000 \n");
		row.push_back("end_<MpeThreshhold>\n");
		row.push_back("end_<Scales>\n");
		row.push_back("end_<project>\n");
		//****************************************************************************************
		std::copy(std::begin(row), std::end(row), out_iter2);
		out_iter2 = "\n";
		row.clear();
		
	}
	void ConfigureCarrier(vector<std::string>& row,CARRIER Carrier)
	{
		std::string carrier_frequency, band_width, index;
		std::stringstream converter;
		std::string Line1{ "" }, Line2{ "" };

		converter << Carrier.Index; converter >> index; converter.clear();
		converter << static_cast<float>(Tools::Round(Carrier.Frequency, 0)); converter >> carrier_frequency; converter.clear();
		converter << static_cast<float>(Tools::Round(Carrier.Band_Width, 0)); converter >> band_width; converter.clear();

		Line1 = "CarrierFrequency " + carrier_frequency + "\n"; //10.3f  , Possible cause of a problem because the number will be print with exponent
		Line2 = "bandwidth " + band_width + "\n"; //10.3f  , Possible cause of a problem because the number will be print with exponent
		//**********************************************************************
		row.push_back("begin_<Waveform> Sinusoid\n");
		row.push_back("description                   "+ Carrier.Description+"\n");
		row.push_back("Sinusoid\n");
		row.push_back("waveform "+index+"\n");
		row.push_back("frequencyDistribution Uniform 500.000 1500.000 inactive nosampling 10\n");
		row.push_back(Line1); Line1.clear();
		row.push_back("phase 0.000\n");
		row.push_back(Line2); Line2.clear();
		row.push_back("end_<Waveform>\n");
		//**********************************************************************
	}
	void ConfigureMIMOElement(vector<std::string>& row, ANTENNA_ELEMENT Element)
	{
		std::string index,rotation_x, rotation_y, rotation_z, position_x, position_y, position_z;
		std::stringstream converter;

		if (Element.ElementType != nullptr)
		{
			converter << Element.ElementType->Index; converter >> index; converter.clear();
		}
		else
			index = "";
		converter << Tools::Round(Element.Rotation_x, 7); converter >> rotation_x; converter.clear();
		converter << Tools::Round(Element.Rotation_y, 7); converter >> rotation_y; converter.clear();
		converter << Tools::Round(Element.Rotation_z, 7); converter >> rotation_z; converter.clear();
		converter << Tools::Round(Element.Position_x, 7); converter >> position_x; converter.clear();
		converter << Tools::Round(Element.Position_y, 7); converter >> position_y; converter.clear();
		converter << Tools::Round(Element.Position_z, 7); converter >> position_z; converter.clear();

		//**********************************************************************
		row.push_back("begin_<MimoElement> \n");
		row.push_back("position " + position_x + " " + position_y + " " + position_z + "\n");
		row.push_back("antenna "+index+"\n");
		row.push_back("rotation " + rotation_x + " " + rotation_y + " " + rotation_z + "\n");
		row.push_back("end_<MimoElement>\n");
		//**********************************************************************
	}
	void ConfigureAntennaType(vector<std::string>& row, ANTENNA_TYPE Antenna) // To Be continued with antenna types
	{
		std::string index, waveform_index;
		std::stringstream converter;

		converter << Antenna.Index; converter >> index; converter.clear();
		converter << Antenna.Carrier_Index; converter >> waveform_index; converter.clear();

		//**********************************************************************
		row.push_back("begin_<antenna> "+Antenna.Name+"\n");//Isotropic
		row.push_back("antenna "+index+"\n");
		row.push_back("type "+Antenna.Type+"\n");//isotropic
		row.push_back("waveform "+ waveform_index +"\n");
		row.push_back("polarization "+Antenna.Polarization+"\n");
		row.push_back("power_threshold -250\n");
		row.push_back("cable_loss 0\n");
		row.push_back("VSWR 1\n");
		// row.push_back("temperature 293\n");
		row.push_back("component TotalGain\n");
		row.push_back("gain_range 40\n");
		row.push_back("show_arrow no\n");
		row.push_back("is_sphere no\n");
		row.push_back("end_<antenna>\n");
		//**********************************************************************
	}
	void ConfigureAntennaArray(vector<std::string>& row, ANTENNA_ARRAY& Antenna_Array)
	{
		std::string index, waveform_index, rotation_y, rotation_z, position_x, position_y, position_z;
		std::stringstream converter;

		converter << Antenna_Array.Index; converter >> index; converter.clear();
		converter << Antenna_Array.Carrier_Index; converter >> waveform_index; converter.clear();

		//******* Configuration of the antenna of an Wireless Point********************
		row.push_back("begin_<antenna> "+Antenna_Array.Name+"\n");//MIMO_Terminal
		row.push_back("description "+ Antenna_Array.Description+"\n");//MIMO_Terminal
		row.push_back("antenna "+index+"\n");//1
		row.push_back("type MIMO\n");
		row.push_back("waveform "+ waveform_index +"\n");//0
		row.push_back("selectedElement 0\n");//-1
		row.push_back("renderingSize 0.024\n");//0.00973352
		//************** ANTENNA TYPE(s) *******************
		int i = static_cast<size_t>(-1);
		for (auto& p_element : Antenna_Array.Elements)
		{
			if (p_element != nullptr)
				if(p_element->ElementType!=nullptr)
					if (p_element->ElementType->Index != i)
					{
						i = p_element->ElementType->Index;
						ConfigureAntennaType(row, *p_element->ElementType);
					}
		}
		//************** END ANTENNA TYPE(s) ******************
		//****** Configuration of MIMO Antenna Elements********
		for (auto& p_element : Antenna_Array.Elements)
		{
			if (p_element != nullptr)
				ConfigureMIMOElement(row, *p_element);
		}
		//****** End Configuration of MIMO Antenna Elements*****
		row.push_back("end_<antenna>\n");
		//******* END Configuration of the antenna of an Wireless Point****************

	}
	void ConfigureTransmitter(vector<std::string>& row, TRANSMITTER& Tx)
	{
		std::string index, waveform_index, power_dbm;
		std::stringstream converter;
		converter << Tx.Antenna_Array->Index; converter >> index; converter.clear();
		converter << Tx.Carrier->Index; converter >> waveform_index; converter.clear();
		converter << Tools::Round(Tx.Power_dBm,3); converter >> power_dbm; converter.clear();
		
		/***************TRABSMITTER *************************/
		row.push_back("begin_<transmitter> \n");
		row.push_back("begin_<pattern> \n");
		row.push_back("antenna "+index+"\n");   // Antenna array Index Used
		row.push_back("waveform "+ waveform_index +"\n");
		row.push_back("rotation_x 0.00000\n");
		row.push_back("rotation_y 0.00000\n");
		row.push_back("rotation_z 0.00000\n");
		row.push_back("end_<pattern>\n");
		row.push_back("power "+ power_dbm +"\n");  // Transmitter Power
		row.push_back("end_<transmitter>\n");
		/***************************************************/
	}
	void ConfigureReceiver(vector<std::string>& row, RECEIVER& Rx)
	{
		std::string index, waveform_index, noise_figure;
		std::stringstream converter;

		converter << Rx.Antenna_Array->Index; converter >> index; converter.clear();
		converter << Rx.Carrier->Index; converter >> waveform_index; converter.clear();
		converter << Tools::Round(Rx.NoiseFigure, 5); converter >> noise_figure; converter.clear();

		/*************** RECEIVER   *************************/
		row.push_back("begin_<receiver> \n");
		row.push_back("begin_<pattern> \n");
		row.push_back("antenna " + index + "\n");  // Receiver array index. 1
		row.push_back("waveform " + waveform_index + "\n"); // Carrier index
		row.push_back("rotation_x 0.00000\n");
		row.push_back("rotation_y 0.00000\n");
		row.push_back("rotation_z 0.00000\n");
		row.push_back("end_<pattern>\n");
		row.push_back("NoiseFigure "+ noise_figure +"\n");
		row.push_back("end_<receiver>\n");
		/***************END RECEIVER   *********************/
	}
	void ConfigureSetOfPoints(vector<std::string>& row, POINTS& Points)
	{
		std::string index, number_of_points, x,y,z, tx_exist, rx_exist;
		std::stringstream converter;

		converter << Points.Project_id; converter >> index; converter.clear();
		converter << Points.GetNumberOfPoints(); converter >> number_of_points; converter.clear();
		if (Points.Transmitter_exist)tx_exist = "yes"; else tx_exist = "no";
		if (Points.Transmitter_exist)tx_exist = "yes"; else tx_exist = "no";
		//********************** BEGIN SET OF POINTS *********************************
		row.push_back("begin_<points> "+Points.Name+"\n"); //Terminal
		row.push_back("project_id "+ index +"\n");// 2
		row.push_back("active\n");
		row.push_back("vertical_line no\n");
		row.push_back("cube_size 2.50000\n");
		row.push_back("CVxLength 10.00000\n");
		row.push_back("CVyLength 10.00000\n");
		row.push_back("CVzLength 10.00000\n");
		row.push_back("AutoPatternScale\n");
		row.push_back("ShowDescription no\n"); // Can be yes to the point description in Wireless Insite Display
		row.push_back("CVsVisible no\n");
		row.push_back("CVsThickness 3\n");
		/*************LOCATION ****************/
		row.push_back("begin_<location> \n");
		row.push_back("begin_<reference> \n");
		row.push_back("cartesian\n");
		row.push_back("longitude 0.000000000000000\n");
		row.push_back("latitude 0.000000000000000\n");
		row.push_back("visible no\n");
		row.push_back("terrain\n");
		row.push_back("end_<reference>\n");
		//******************************************************************************
		row.push_back("nVertices "+ number_of_points +"\n");
		for (auto& location : Points.Point_locations)
		{
			if (location != nullptr)
			{
				converter << location->X; converter >> x; converter.clear();
				converter << location->Y; converter >> y; converter.clear();
				converter << location->Z; converter >> z; converter.clear();
				row.push_back(x + " " + y + " " + z + "\n");// , BS_x, BS_y, BS_z);
			}
			else
				cout << " ERROR : Null Pointer At Point Location :" << endl;
		}
		
		//SOLVE// Random_gen(fid, Number_of_points, BS_x, BS_y, BS_z, SAB_x_L, SAB_y_L, SAB_y_U, SAB_x_U, SAB_z_U, SAB_z_L, Transmitter_Power, Carrier_Frequency, Bandwidth, Spacing, Samples_Count, MIMO_ELEMENTS_TRANSMITTER, MIMO_ELEMENTS_RECEIVER, Case, groups, Centered, Feature, Destination_folder, Origin);
		//******************************************************************************
		row.push_back("end_<location>\n");
		/************* END LOCATION ***********/
		row.push_back("pattern_show_arrow no\n");
		row.push_back("pattern_show_as_sphere no\n");
		row.push_back("generate_p2p yes\n");
		row.push_back("use_apg_acceleration yes\n");
		row.push_back("is_transmitter "+ tx_exist +"\n");// Transmitter and receiver properities // no
		row.push_back("is_receiver "+ rx_exist +"\n"); // yes
		/***************TRABSMITTER *************************/
		ConfigureTransmitter(row, *(Points.TX));
		/*************** END TRABSMITTER ********************/
		/*************** RECEIVER   *************************/
		if(Points.Receiver_exist)ConfigureReceiver(row, *(Points.RX));
		/***************END RECEIVER   *********************/
		row.push_back("powerDistribution Uniform 10.00000 10.00000 inactive nosampling 10\n");
		row.push_back("end_<points>\n");
		//********************** END SET OF POINTS *********************************
	}
	public:
		std::string City_File;
		std::string TxRx_File;
		//ANTENNA_ARRAY Antenna_Array_Terminal;
		//ANTENNA_ARRAY Antenna_Array_BS;
		//CARRIER Carrier;
		//TRANSMITTER Tx;
		//RECEIVER Rx;
		//POINTS Points;
		CommunicationSystem CommSystem;
};

