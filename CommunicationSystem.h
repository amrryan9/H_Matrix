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
	size_t  Index; // Unique index for each antenna type-configuration(Object)
	size_t Carrier_Index;
	ANTENNA_TYPE()
	{
		Name = "";
		Type = "";
		Index = 0;
		Polarization ="vertical";
	}
	ANTENNA_TYPE(std::string name, std::string type, size_t index, std::string polarization = "vertical")
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
	size_t Carrier_Index;
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
		Carrier_Index=0;
	}
	ANTENNA_ELEMENT(ANTENNA_TYPE* element_type, size_t carrier_index)
	{
		if (element_type != nullptr)
		{
			ElementType = element_type;
			ElementType->Carrier_Index = carrier_index;
		}
		Rotation_x = 0.0;
		Rotation_y = 0.0; 
		Rotation_z = 0.0; 
		Position_x = 0.0; 
		Position_y = 0.0; 
		Position_z = 0.0;
		Carrier_Index = carrier_index;
	}
	ANTENNA_ELEMENT(ANTENNA_TYPE* element_type, size_t carrier_index, float R_x, float R_y, float R_z, float P_x, float P_y, float P_z)
	{
		if (element_type != nullptr)
		{
			ElementType = element_type;
			ElementType->Carrier_Index = carrier_index;
		}
		SetPosition(P_x, P_y, P_z);
		SetRotation(R_x, R_y, R_z);
		Carrier_Index = carrier_index;
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
	size_t Index; // Unique index for each antenna type-configuration(Object)
	size_t Carrier_Index;
	vector<ANTENNA_ELEMENT*>Elements;
	ANTENNA_ARRAY()
	{
		Name = "";
		Description = "";
		Index = 0;
		Carrier_Index = 0;
	}
	ANTENNA_ARRAY(std::string name,size_t index, size_t carrier_index,std::string description="")
	{
		Name = name;
		Description = description;
		Index = index;
		Carrier_Index = carrier_index;
	}
	void AddElement(ANTENNA_TYPE* p_element_type, float R_x, float R_y, float R_z, float P_x, float P_y, float P_z)
	{
		Elements.push_back(new ANTENNA_ELEMENT(p_element_type, Carrier_Index, R_x, R_y, R_z, P_x, P_y, P_z));
	}
	void SetCarrierIndex(size_t carrier_index)
	{
		Carrier_Index = carrier_index;
		for (auto ele : Elements)
		{
			if (ele != nullptr)
			{
				ele->Carrier_Index = carrier_index;
				if (ele->ElementType != nullptr)
				{
					ele->ElementType->Carrier_Index = carrier_index;
				}
				else
					cout << " ERROR : Antenna Type is not set ." << endl;
			}
			else
				cout << " ERROR : Antenna Element is not set ." << endl;
		}
	}
};
struct RECEIVER
{
	RECEIVER()
	{
		NoiseFigure = 3.00000;
		Carrier = new CARRIER();
		Antenna_Array = new ANTENNA_ARRAY();
		Antenna_Array->SetCarrierIndex(Carrier->Index);
	}
	RECEIVER(CARRIER* carrier, ANTENNA_ARRAY* antenna_array, float noisefigure = 3.00000)
	{
		if (carrier != nullptr)
		{
			Carrier = carrier;
			if (antenna_array != nullptr)
			{
				Antenna_Array = antenna_array;
				Antenna_Array->SetCarrierIndex(Carrier->Index);
			}
		}
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
		Antenna_Array->SetCarrierIndex(Carrier->Index);
	}
	TRANSMITTER(CARRIER* carrier, ANTENNA_ARRAY* antenna_array, float power_dBm = 0)
	{
		if (carrier != nullptr)
		{
			Carrier = carrier;
			if (antenna_array != nullptr)
			{
				Antenna_Array = antenna_array;
				Antenna_Array->SetCarrierIndex(Carrier->Index);
			}
		}
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
		TX = new TRANSMITTER();
		RX = new RECEIVER();
		Transmitter_exist = false;
		Receiver_exist = false;
		Name = "";
	}
	POINTS(size_t index, string name = "")
	{
		Project_id = index;
		TX = new TRANSMITTER();
		RX = new RECEIVER();
		Transmitter_exist = false;
		Receiver_exist = false;
		Name = name;
	}
	POINTS(size_t index, string name,TRANSMITTER* TX, RECEIVER* rx=nullptr)
	{
		Project_id = index; Name = name;
		if (TX != nullptr) { TX = TX; Transmitter_exist = true; }else { TX = new TRANSMITTER(); Transmitter_exist = false; }
		if (rx != nullptr) { RX = rx; Receiver_exist = true; }else { RX = new RECEIVER(); Receiver_exist = false; }
	}
	POINTS(size_t index, string name, RECEIVER* rx, TRANSMITTER* TX = nullptr)
	{
		Project_id = index; Name = name;
		if (TX != nullptr) { TX = TX; Transmitter_exist = true; }else {TX = new TRANSMITTER(); Transmitter_exist = false;}
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
	size_t Project_id;
	TRANSMITTER* TX;
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
		this->AntennaArrays.push_back(new ANTENNA_ARRAY(name,Antenna_Array_Index,0, description));
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
	void Show()
	{
		for (auto& p : PointsSets)
		{
			cout << "Points Project_id : " << static_cast<size_t>(p->Project_id) << endl;
			
			if (p->Transmitter_exist)
			{
				cout << "	Transmitter power at each antenna item : " << p->TX->Power_dBm << endl;
				cout << "		Carrier Frequency :                  " << p->TX->Carrier->Frequency << " Hz" << endl;
				cout << "		Carrier Bandwidth :                  " << p->TX->Carrier->Band_Width << " Hz" << endl;
				cout << "		Antenna Array index :				 " << static_cast<size_t>(p->TX->Antenna_Array->Index) << endl;
				for (auto a_element : p->TX->Antenna_Array->Elements)
				{
					cout << "			Elements Position At : " << a_element->Position_x << "," << a_element->Position_y << "," << a_element->Position_z << endl;
					cout << "			Elements Rotation At : " << a_element->Rotation_x << "," << a_element->Rotation_y << "," << a_element->Rotation_z << endl;
					cout << "				Element antenna type Index : " << static_cast<size_t>(a_element->ElementType->Index) << endl;
					cout << "				Element antenna description : " << a_element->ElementType->Name << endl;
					cout << "				Element antenna type : " << a_element->ElementType->Type << endl;
					cout << "				Element antenna Polarization : " << a_element->ElementType->Polarization << endl;
				}
			}
			if (p->Receiver_exist)
			{
				cout << "	Receiver Noise Figure : " << p->RX->NoiseFigure << endl;
				cout << "		Carrier Frequency :                  " << p->RX->Carrier->Frequency << " Hz" << endl;
				cout << "		Carrier Bandwidth :                  " << p->RX->Carrier->Band_Width << " Hz" << endl;
				cout << "		Antenna Array index :				 " << p->RX->Antenna_Array->Index << endl;
				for (auto a_element : p->RX->Antenna_Array->Elements)
				{
					cout << "			Elements At : " << a_element->Position_x << "," << a_element->Position_y << "," << a_element->Position_z << endl;
					cout << "			Elements Rotation At : " << a_element->Rotation_x << "," << a_element->Rotation_y << "," << a_element->Rotation_z << endl;
					cout << "				Element antenna type Index : " << static_cast<size_t>(a_element->ElementType->Index) << endl;
					cout << "				Element antenna description : " << a_element->ElementType->Name << endl;
					cout << "				Element antenna type : " << a_element->ElementType->Type << endl;
					cout << "				Element antenna Polarization : " << a_element->ElementType->Polarization << endl;
				}
			}
			for (auto& location : p->Point_locations)
			{
				cout << "		Point at : " << location->X << "," << location->Y << "," << location->Z << endl;
			}
		}
	}
public:
	static size_t Antenna_Type_Index;
	static size_t Antenna_Array_Index;
	static size_t Carrier_Index;
	static size_t Points_Set_Index;
	vector<ANTENNA_TYPE*>AntennaTypes;
	vector<ANTENNA_ARRAY*>AntennaArrays;
	vector<CARRIER*>Carriers;
	vector<POINTS*>PointsSets;
};

