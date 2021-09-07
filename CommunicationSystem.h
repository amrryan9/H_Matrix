#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include<sstream>
#include<iomanip>
#include"Tools.h"


struct CARRIER
{
	float Frequency;
	float Band_Width;
	std::string Description;
	size_t Index;
	CARRIER() {
		Frequency = 0;
		Band_Width = 0;
		Description = "";
		Index = 0;
	}
	CARRIER(float frequency, float band_width,size_t index, std::string description="")
	{
		Frequency=frequency;
		Band_Width=band_width;
		Description=description;
		Index=index;
	}
};
struct ANTENNA_TYPE
{
	std::string Name;
	std::string Type;
	std::string Polarization;
	char Index; // Unique index for each antenna type-configuration(Object)
	ANTENNA_TYPE()
	{
		Name = "";
		Type = "";
		Index = 0;
		Polarization ="vertical";
	}
	ANTENNA_TYPE(std::string name, std::string type, char index, std::string polarization = "vertical")
	{
		Name = name;
		Type = type;
		Index = index;
		Polarization = polarization;
	}
};
struct ANTENNA_ELEMENT
{
	ANTENNA_TYPE* ElementType;
	float Rotation_x, Rotation_y, Rotation_z, Position_x, Position_y, Position_z;
	ANTENNA_ELEMENT()
	{
		ElementType;
		Rotation_x = 0.0;
		Rotation_y = 0.0;
		Rotation_z = 0.0;
		Position_x = 0.0;
		Position_y = 0.0;
		Position_z = 0.0;
		ElementType = new ANTENNA_TYPE();
	}
	ANTENNA_ELEMENT(ANTENNA_TYPE* element_type)
	{
		if(element_type!=nullptr)ElementType = element_type;
		Rotation_x = 0.0;
		Rotation_y = 0.0; 
		Rotation_z = 0.0; 
		Position_x = 0.0; 
		Position_y = 0.0; 
		Position_z = 0.0;
	}
	ANTENNA_ELEMENT(ANTENNA_TYPE* element_type, float R_x, float R_y, float R_z, float P_x, float P_y, float P_z)
	{
		if (element_type != nullptr)ElementType = element_type;
		SetPosition(P_x, P_y, P_z);
		SetRotation(R_x, R_y, R_z);
	}
	void SetPosition(float x, float y, float z)
	{
		Position_x = x;
		Position_y = y;
		Position_z = z;
	}
	void SetRotation(float x, float y, float z)
	{
		Rotation_x = x;
		Rotation_y = y;
		Rotation_z = z;
	}
};
struct ANTENNA_ARRAY // Every antenna set is an array even if it is a single element
{
	std::string Name;
	std::string Description;
	char Index; // Unique index for each antenna type-configuration(Object)
	vector<ANTENNA_ELEMENT*>Elements;
	ANTENNA_ARRAY()
	{
		Name = "";
		Description = "";
		Index = 0;
	}
	ANTENNA_ARRAY(std::string name,char index,std::string description="")
	{
		Name = name;
		Description = description;
		Index = index;
	}
	void AddElement(ANTENNA_TYPE* p_element_type, float R_x, float R_y, float R_z, float P_x, float P_y, float P_z)
	{
		Elements.push_back(new ANTENNA_ELEMENT(p_element_type, R_x, R_y, R_z, P_x, P_y, P_z));
	}
};
struct RECEIVER
{
	RECEIVER()
	{
		NoiseFigure = 3.00000;
		Carrier = new CARRIER();
		Antenna_Array = new ANTENNA_ARRAY();
	}
	RECEIVER(CARRIER* carrier, ANTENNA_ARRAY* antenna_array, float noisefigure = 3.00000)
	{
		if (carrier != nullptr)Carrier = carrier;
		if (antenna_array != nullptr)Antenna_Array = antenna_array;
		NoiseFigure = noisefigure;
	}
	CARRIER* Carrier;
	ANTENNA_ARRAY* Antenna_Array;
	float NoiseFigure;
};
struct TRANSMITTER
{
	TRANSMITTER()
	{
		Power_dBm = 0.0;
		Carrier = new CARRIER();
		Antenna_Array = new ANTENNA_ARRAY();
	}
	TRANSMITTER(CARRIER* carrier, ANTENNA_ARRAY* antenna_array, float power_dBm = 0)
	{
		if (carrier != nullptr)Carrier = carrier;
		if (antenna_array != nullptr)Antenna_Array = antenna_array;
		Power_dBm = power_dBm;
	}
	CARRIER* Carrier;
	ANTENNA_ARRAY* Antenna_Array;
	float Power_dBm;
};
struct POINT_LOCATION
{
	POINT_LOCATION()
	{
		X = 0.0;
		Y = 0.0;
		Z = 0.0;
	}
	POINT_LOCATION(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
	float X;
	float Y;
	float Z;
};
struct POINTS
{
	POINTS()
	{
		Project_id = 0;
		Tx = new TRANSMITTER();
		RX = new RECEIVER();
		Transmitter_exist = false;
		Receiver_exist = false;
		Name = "";
	}
	POINTS(char index, string name = "")
	{
		Project_id = index;
		Tx = new TRANSMITTER();
		RX = new RECEIVER();
		Transmitter_exist = false;
		Receiver_exist = false;
		Name = name;
	}
	POINTS(char index, string name,TRANSMITTER* tx, RECEIVER* rx=nullptr)
	{
		Project_id = index; Name = name;
		if (tx != nullptr) { Tx = tx; Transmitter_exist = true; }else { Tx = new TRANSMITTER(); Transmitter_exist = false; }
		if (rx != nullptr) { RX = rx; Receiver_exist = true; }else { RX = new RECEIVER(); Receiver_exist = false; }
	}
	POINTS(char index, string name, RECEIVER* rx, TRANSMITTER* tx = nullptr)
	{
		Project_id = index; Name = name;
		if (tx != nullptr) { Tx = tx; Transmitter_exist = true; }else {Tx = new TRANSMITTER(); Transmitter_exist = false;}
		if (rx != nullptr) { RX = rx; Receiver_exist = true; }else { RX = new RECEIVER(); Receiver_exist = false; }
	}
	size_t GetNumberOfPoints()
	{
		return Point_locations.size();
	}
	void AddNewPointAt(float x, float y, float z)
	{
		Point_locations.push_back(new POINT_LOCATION(x, y, z));
	}
	bool AddPointAt(POINT_LOCATION* location)
	{
		if (location != nullptr)
		{
			Point_locations.push_back(location); return true;
		}
		return false;
	}
	std::string Name;
	char Project_id;
	TRANSMITTER* Tx;
	RECEIVER* RX;
	vector< POINT_LOCATION*>Point_locations;
	bool Transmitter_exist;
	bool Receiver_exist;
};

class CommunicationSystem
{
public:
	CommunicationSystem() {  }
	void AddNewAntennaType(std::string name, std::string type, std::string polarization = "vertical")
	{
		this->AntennaTypes.push_back(new ANTENNA_TYPE(name, type, Antenna_Type_Index, polarization));
		Antenna_Type_Index++;
	}
	bool AddAntennaType(ANTENNA_TYPE* p_antenna_type)
	{
		if (p_antenna_type != nullptr)
		{
			if (p_antenna_type->Index >= Antenna_Type_Index)
				Antenna_Array_Index = p_antenna_type->Index;
			else
			{
				for (auto& p : AntennaTypes)
				{
					if (p->Index == p_antenna_type->Index)
					{
						p = p_antenna_type;
						return true;
					}
				}
			}
			this->AntennaTypes.push_back(p_antenna_type);
			return true;
		}
		return false;
	}
	void AddNewAntennaArray(std::string name, std::string description ="")
	{
		this->AntennaArrays.push_back(new ANTENNA_ARRAY(name,Antenna_Array_Index, description));
		Antenna_Array_Index++;
	}
	bool AddAntennaArray(ANTENNA_ARRAY* p_antenna_array)
	{
		if (p_antenna_array != nullptr)
		{
			if (p_antenna_array->Index >= Antenna_Array_Index)
				Antenna_Array_Index = p_antenna_array->Index;
			else
			{
				for (auto& p : AntennaArrays)
				{
					if (p->Index == p_antenna_array->Index)
					{
						p = p_antenna_array;
						return true;
					}
				}
			}
			this->AntennaArrays.push_back(p_antenna_array);
			return true;
		}
		return false;
	}
	void AddNewCarrier(float frequency, float band_width,std::string description = "")
	{
		this->Carriers.push_back(new CARRIER(frequency, band_width, Carrier_Index,description));
		Carrier_Index++;
	}
	bool AddCarrier(CARRIER* p_carrier)
	{
		if (p_carrier != nullptr)
		{
			if (p_carrier->Index >= Carrier_Index)
				Carrier_Index = p_carrier->Index;
			else
			{
				for (auto& p : Carriers)
				{
					if (p->Index == p_carrier->Index)
					{
						p = p_carrier;
						return true;
					}
				}
			}
			this->Carriers.push_back(p_carrier);
			return true;
		}
		return false;
	}
	void AddNewPoints(std::string description = "")
	{
		this->PointsSets.push_back(new POINTS(Points_Set_Index,description));
		Points_Set_Index++;
	}
	bool AddPoints(POINTS* p_points)
	{
		if (p_points != nullptr)
		{
			if (p_points->Project_id >= Points_Set_Index)
				Points_Set_Index = p_points->Project_id;
			else
			{
				for (auto& p : PointsSets)
				{
					if (p->Project_id == p_points->Project_id)
					{
						p = p_points;
						return true;
					}
				}
			}
			this->PointsSets.push_back(p_points);
			return true;
		}
		return false;
	}
public:
	static char Antenna_Type_Index;
	static char Antenna_Array_Index;
	static char Carrier_Index;
	static char Points_Set_Index;
	vector<ANTENNA_TYPE*>AntennaTypes;
	vector<ANTENNA_ARRAY*>AntennaArrays;
	vector<CARRIER*>Carriers;
	vector<POINTS*>PointsSets;
};

