#include "CommunicationSystem.h"
size_t CommunicationSystem::Antenna_Type_Index = 0;
size_t CommunicationSystem::Antenna_Array_Index = 0;
size_t CommunicationSystem::Points_Set_Index = 1;
size_t CommunicationSystem::Carrier_Index= 0;
void CommunicationSystem::RestoreFromFile(std::string file_name)
{
	//check the file get string vector
	std::vector<string> ss = Tools::Read_ssv_File(file_name);
	//rest current
	this->Reset();
	//restore from the string vector
	std::stringstream converter;
	/*************************************/
	bool F_Anttena_type_index{ false };
	bool F_Anttena_Array_index{ false };
	bool F_Carrier_index{ false };
	bool F_Points_Set_index{ false };
	bool F_Antenna_Types{ false };
	bool F_Antenna_TYPE{ false };
	bool F_Antenna_Arrays{ false };
	bool F_Antenna_ARRAY{ false };
	bool F_Antennna_ELEMENT{ false };
	bool F_Antennna_ELEMENT_TYPE{ false };
	bool F_Carriers{ false };
	bool F_CARRIER{ false };
	bool F_Points_sets{ false };
	bool F_Points_SET{ false };
	bool F_Points_RX{ false };
	bool F_Points_RX_ANTENNA_ARRAY{ false };
	bool F_Points_RX_CARRIER{ false };
	bool F_Points_TX{ false };
	bool F_Points_TX_ANTENNA_ARRAY{ false };
	bool F_Points_TX_CARRIER{ false };
	bool F_Points_POINTS_LOCATIONS{ false };
	bool F_Points_POINT{ false };
	/************************************/

	size_t I_Antenna_Types{ 0 };
	size_t C_Antenna_Types{ 0 };

	size_t I_Antenna_Arrays{ 0 };
	size_t C_Antenna_Arrays{ 0 };

	size_t I_Antenna_Element{ 0 };
	size_t C_Antenna_Element{ 0 };

	size_t I_Carriers{ 0 };
	size_t C_Carriers{ 0 };

	size_t I_Points_Sets{ 0 };
	size_t C_Points_Sets{ 0 };

	size_t I_Point_SET{ 0 };
	size_t C_Point_SET{ 0 };

	size_t I_RX{ 0 };
	size_t C_RX{ 0 };

	size_t I_TX{ 0 };
	size_t C_TX{ 0 };

	size_t I_Points_locations{ 0 };
	size_t C_Points_locations{ 0 };

	size_t I_POINT{ 0 };
	size_t C_POINT{ 0 };

	size_t I_Antenna_Element_type{ 0 };
	size_t I_Points_Rx_Antenna_array{ 0 };
	size_t I_Points_Rx_Carrier{ 0 };

	size_t I_Points_Tx_Antenna_array{ 0 };
	size_t I_Points_Tx_Carrier{ 0 };

	size_t index1{ 0 };

	for (auto& line : ss)
	{
		if (line == "#ANTENNA_TYPE_INDEX")// Pass once
		{
			/*************************************/
			F_Anttena_type_index=true;
			F_Anttena_Array_index=false;
			F_Carrier_index=false;
			F_Points_Set_index=false;
			F_Antenna_Types=false;
			F_Antenna_TYPE=false;
			F_Antenna_Arrays=false;
			F_Antenna_ARRAY=false;
			F_Antennna_ELEMENT=false;
			F_Antennna_ELEMENT_TYPE=false;
			F_Carriers=false;
			F_CARRIER=false;
			F_Points_sets=false;
			F_Points_SET=false;
			F_Points_RX=false;
			F_Points_RX_ANTENNA_ARRAY=false;
			F_Points_RX_CARRIER=false;
			F_Points_TX=false;
			F_Points_TX_ANTENNA_ARRAY=false;
			F_Points_TX_CARRIER=false;
			F_Points_POINTS_LOCATIONS=false;
			F_Points_POINT=false;
			/************************************/
		}
		else if (line == "#ANTENNA_ARRAY_INDEX")// Pass once
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = true;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "#CARRIER_INDEX")// Pass once
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = true;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "POINTS_SET_INDEX")// Pass once
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = true;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "#ANTENNA_TYPES")// Pass once
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = true;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
			C_Antenna_Types = 0;
			I_Antenna_Types = 0;
		}
		else if (line == "##ANTENNA_TYPE")// Pass once
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = true;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "#ANTENNA_ARRAYS")// Pass once
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = true;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
			C_Antenna_Arrays = 0;
			I_Antenna_Arrays = 0;
		}
		else if (line == "##ANTENNA_ARRAY")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = true;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
			C_Antenna_Element=0;
			I_Antenna_Element = 0;
		}
		else if (line == "###ANTENNA_ELEMENT")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = true;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
			I_Antenna_Element_type = 0;
		}
		else if (line == "####ANTENNA_ELEMENT_TYPE")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = true;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "#CARRIERS")// Pass once
		{
			/*************************************/
			F_Anttena_type_index=false;
			F_Anttena_Array_index=false;
			F_Carrier_index=false;
			F_Points_Set_index=false;
			F_Antenna_Types=false;
			F_Antenna_TYPE=false;
			F_Antenna_Arrays=false;
			F_Antenna_ARRAY=false;
			F_Antennna_ELEMENT=false;
			F_Antennna_ELEMENT_TYPE=false;
			F_Carriers=true;
			F_CARRIER=false;
			F_Points_sets=false;
			F_Points_SET=false;
			F_Points_RX=false;
			F_Points_RX_ANTENNA_ARRAY=false;
			F_Points_RX_CARRIER=false;
			F_Points_TX=false;
			F_Points_TX_ANTENNA_ARRAY=false;
			F_Points_TX_CARRIER=false;
			F_Points_POINTS_LOCATIONS=false;
			F_Points_POINT=false;
			/************************************/
			C_Carriers=0;
			I_Carriers = 0;
		}
		else if (line == "##CARRIER")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = true;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "#POINTS_SETS")// Pass once
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = true;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
			C_Point_SET=0;
			I_Point_SET = 0;
		}
		else if (line == "##POINT_SET")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = true;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
			I_RX = 0;
			I_Points_Rx_Antenna_array = 0;
			I_Points_Rx_Carrier = 0;
			I_TX = 0;
			I_Points_Tx_Antenna_array = 0;
			I_Points_Tx_Carrier = 0;
		}
		else if (line == "###RX")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = true;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/

		}
		else if (line == "####RX_ANTENNA_ARRAY")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = true;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "####RX_CARRIER")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = true;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "###TX")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = true;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "####TX_ANTENNA_ARRAY")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = true;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "####TX_CARRIER")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = true;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = false;
			/************************************/
		}
		else if (line == "###POINTS_LOCATIONS")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = true;
			F_Points_POINT = false;
			/************************************/
			C_POINT=0;
			I_POINT = 0;
		}
		else if (line == "####POINT")
		{
			/*************************************/
			F_Anttena_type_index = false;
			F_Anttena_Array_index = false;
			F_Carrier_index = false;
			F_Points_Set_index = false;
			F_Antenna_Types = false;
			F_Antenna_TYPE = false;
			F_Antenna_Arrays = false;
			F_Antenna_ARRAY = false;
			F_Antennna_ELEMENT = false;
			F_Antennna_ELEMENT_TYPE = false;
			F_Carriers = false;
			F_CARRIER = false;
			F_Points_sets = false;
			F_Points_SET = false;
			F_Points_RX = false;
			F_Points_RX_ANTENNA_ARRAY = false;
			F_Points_RX_CARRIER = false;
			F_Points_TX = false;
			F_Points_TX_ANTENNA_ARRAY = false;
			F_Points_TX_CARRIER = false;
			F_Points_POINTS_LOCATIONS = false;
			F_Points_POINT = true;
			/************************************/
		}
		else
		{
			/// Seems nothing to do here
		}
		///////////////////////////////////////////////////////////
	//	converter << line;
	//	cout << line << endl;
		if (F_Anttena_type_index)
		{
			if (index1 == 0)
				index1++;
			else if (index1 == 1)
			{
				index1 = 0;
				converter<<line;converter>>this->Antenna_Type_Index; converter.clear();
			}
		}
		if (F_Anttena_Array_index)
		{
			if (index1 == 0)
				index1++;
			else if (index1 == 1)
			{
				index1 = 0;
				converter<<line;converter>>this->Antenna_Array_Index; converter.clear();
			}
		}
		if (F_Carrier_index)
		{
			if (index1 == 0)
				index1++;
			else if (index1 == 1)
			{
				index1 = 0;
				converter<<line;converter>>this->Carrier_Index; converter.clear();
			}
		}
		if (F_Points_Set_index)
		{
			if (index1 == 0)
				index1++;
			else if (index1 == 1)
			{
				index1 = 0;
				converter<<line;converter>>this->Points_Set_Index; converter.clear();
			}
		}
		if (F_Antenna_Types)
		{
			/// Seems nothing to do here
		}
		if (F_Antenna_TYPE)
		{
			if (I_Antenna_Types == 0)
			{
				this->AntennaTypes.push_back(new ANTENNA_TYPE());
				C_Antenna_Types++;
				I_Antenna_Types++;
			}
			else if (I_Antenna_Types == 1)
			{
				converter<<line;converter>>this->AntennaTypes.at(C_Antenna_Types - 1)->Carrier_Index; converter.clear();
				I_Antenna_Types++;
			}
			else if (I_Antenna_Types == 2)
			{
				converter<<line;converter>>this->AntennaTypes.at(C_Antenna_Types - 1)->Index; converter.clear();
				I_Antenna_Types++;
			}
			else if (I_Antenna_Types == 3)
			{
				converter<<line;converter>>this->AntennaTypes.at(C_Antenna_Types - 1)->Name; converter.clear();
				I_Antenna_Types++;
			}
			else if (I_Antenna_Types == 4)
			{
				converter<<line;converter>>this->AntennaTypes.at(C_Antenna_Types - 1)->Polarization; converter.clear();
				I_Antenna_Types++;
			}
			else if (I_Antenna_Types == 5)
			{
				converter<<line;converter>>this->AntennaTypes.at(C_Antenna_Types - 1)->Type; converter.clear();
				I_Antenna_Types++;
			}
			else
			{
				cout << " ERROR : SHULD NOT BE HERE 1" << endl;
			}
		}
		if (F_Antenna_Arrays)
		{
			/// Seems nothing to do here
		}
		if (F_Antenna_ARRAY)
		{
			if (I_Antenna_Arrays == 0)
			{
				this->AntennaArrays.push_back(new ANTENNA_ARRAY);
				C_Antenna_Arrays++;
				I_Antenna_Arrays++;
			}
			else if (I_Antenna_Arrays == 1)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Carrier_Index; converter.clear();
				I_Antenna_Arrays++;
			}
			else if (I_Antenna_Arrays == 2)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Description; converter.clear();
				I_Antenna_Arrays++;
			}
			else if (I_Antenna_Arrays == 3)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Index; converter.clear();
				I_Antenna_Arrays++;
			}
			else if (I_Antenna_Arrays == 4)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Name; converter.clear();
				I_Antenna_Arrays=0;
			}
			else
			{
				cout << " ERROR : SHULD NOT BE HERE 2" << endl;
			}
		}
		if (F_Antennna_ELEMENT)
		{
			if (I_Antenna_Element == 0)
			{
				this->AntennaArrays.at(C_Antenna_Arrays - 1)->Elements.push_back(new ANTENNA_ELEMENT());
				C_Antenna_Element++;
				I_Antenna_Element++;
			}
			else if (I_Antenna_Element == 1)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Elements.at(C_Antenna_Element - 1)->Carrier_Index; converter.clear();
				I_Antenna_Element++;
			}
			else if (I_Antenna_Element == 2)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Elements.at(C_Antenna_Element - 1)->Position_x; converter.clear();
				I_Antenna_Element++;
			}
			else if (I_Antenna_Element == 3)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Elements.at(C_Antenna_Element - 1)->Position_y; converter.clear();
				I_Antenna_Element++;
			}
			else if (I_Antenna_Element == 4)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Elements.at(C_Antenna_Element - 1)->Position_z; converter.clear();
				I_Antenna_Element++;
			}
			else if (I_Antenna_Element == 5)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Elements.at(C_Antenna_Element - 1)->Rotation_x; converter.clear();
				I_Antenna_Element++;
			}
			else if (I_Antenna_Element == 6)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Elements.at(C_Antenna_Element - 1)->Rotation_y; converter.clear();
				I_Antenna_Element++;
			}
			else if (I_Antenna_Element == 7)
			{
				converter<<line;converter>>this->AntennaArrays.at(C_Antenna_Arrays - 1)->Elements.at(C_Antenna_Element - 1)->Rotation_z; converter.clear();
				I_Antenna_Element=0;
			}
			else
			{
				cout << " ERROR : SHULD NOT BE HERE 16" << endl;
			}
		}
		if (F_Antennna_ELEMENT_TYPE)
		{
			if (I_Antenna_Element_type == 0)
			{
				I_Antenna_Element_type++;
			}
			else if (I_Antenna_Element_type == 1)
			{
				size_t index{ 0 };
				converter<<line;converter>>index; converter.clear();
				this->AntennaArrays.at(C_Antenna_Arrays - 1)->Elements.at(C_Antenna_Element - 1)->ElementType = this->AntennaTypes.at(index);
				I_Antenna_Element_type = 0;
			}
		}
		if (F_Carriers)
		{
			/// Seems nothing to do here
		}
		if (F_CARRIER)
		{
			if (I_Carriers == 0)
			{
				this->Carriers.push_back(new CARRIER());
				C_Carriers++;
				I_Carriers++;
				
			}
			else if (I_Carriers == 1)
			{
				converter<<line;converter>>this->Carriers.at(C_Carriers - 1)->Band_Width; converter.clear();
				I_Carriers++; 
			}
			else if (I_Carriers == 2)
			{
				converter<<line;converter>>this->Carriers.at(C_Carriers - 1)->Description; converter.clear();
				I_Carriers++;
			}
			else if (I_Carriers == 3)
			{
				converter<<line;converter>>this->Carriers.at(C_Carriers - 1)->Frequency; converter.clear();
				I_Carriers++;
			}
			else if (I_Carriers == 4)
			{
				converter<<line;converter>>this->Carriers.at(C_Carriers - 1)->Index; converter.clear();
				I_Carriers=0;
				
			}
			else
			{
				cout << " ERROR : SHULD NOT BE HERE 6" << endl;
			}
		}
		if (F_Points_sets)
		{
			// Seems not much to do here
		}
		if (F_Points_SET)
		{
			if (I_Point_SET == 0)
			{
				this->PointsSets.push_back(new POINTS());
				C_Point_SET++;
				I_Point_SET++;
			}
			else if (I_Point_SET == 1)
			{
				converter<<line;converter>>this->PointsSets.at(C_Point_SET - 1)->Name; converter.clear();
				I_Point_SET++;
			}
			else if (I_Point_SET == 2)
			{
				converter<<line;converter>>this->PointsSets.at(C_Point_SET - 1)->Project_id; converter.clear();
				I_Point_SET++;
			}
			else if (I_Point_SET == 3)
			{
				converter<<line;converter>>this->PointsSets.at(C_Point_SET - 1)->Receiver_exist; converter.clear();
				I_Point_SET++;
			}
			else if (I_Point_SET == 4)
			{
				converter<<line;converter>>this->PointsSets.at(C_Point_SET - 1)->Transmitter_exist; converter.clear();
				I_Point_SET=0;
			}
			else
			{
				cout << " ERROR : SHULD NOT BE HERE 6" << endl;
			}
		}
		if (F_Points_RX)
		{
			if (I_RX == 0)
			{
				this->PointsSets.at(C_Point_SET - 1)->RX = new RECEIVER();
				I_RX++;
			}
			else if (I_RX == 1)
			{
				converter<<line;converter>>this->PointsSets.at(C_Point_SET - 1)->RX->NoiseFigure; converter.clear();
				I_RX = 0;
			}
			else
				cout << " ERROR : SHULD NOT BE HERE 7" << endl;
		}
		if (F_Points_RX_ANTENNA_ARRAY)
		{
			if (I_Points_Rx_Antenna_array == 0)
			{
				I_Points_Rx_Antenna_array++;
			}
			else if (I_Points_Rx_Antenna_array == 1)
			{
				size_t index{ 0 };
				converter<<line;converter>>index; converter.clear();
				if (this->AntennaArrays.at(index) != nullptr)
					this->PointsSets.at(C_Point_SET - 1)->RX->Antenna_Array = this->AntennaArrays.at(index);
				else
					cout << " ERROR : SHULD NOT BE HERE 8" << endl;
			}
		}
		if (F_Points_RX_CARRIER)
		{
			if (I_Points_Rx_Carrier == 0)
				I_Points_Rx_Carrier++;
			else if (I_Points_Rx_Carrier == 1)
			{
				size_t index{ 0 };
				converter<<line;converter>>index; converter.clear();
				if (this->Carriers.at(index) != nullptr)
					this->PointsSets.at(C_Point_SET - 1)->RX->Carrier = this->Carriers.at(index);
				else
					cout << " ERROR : SHULD NOT BE HERE 10" << endl;
			}
			else
				cout << " ERROR : SHULD NOT BE HERE 9" << endl;
		}

		if (F_Points_TX)
		{
			if (I_TX == 0)
			{
				this->PointsSets.at(C_Point_SET - 1)->TX = new TRANSMITTER();
				I_TX++;
			}
			else if (I_TX == 1)
			{
				converter<<line;converter>> this->PointsSets.at(C_Point_SET - 1)->TX->Power_dBm; converter.clear();
				I_TX = 0;
			}
			else
				cout << " ERROR : SHULD NOT BE HERE 7" << endl;
		}
		if (F_Points_TX_ANTENNA_ARRAY)
		{
			if (I_Points_Tx_Antenna_array == 0)
			{
				I_Points_Tx_Antenna_array++;
			}
			else if (I_Points_Tx_Antenna_array == 1)
			{
				size_t index{ 0 };
				converter<<line;converter>>index; converter.clear();
				if (this->AntennaArrays.at(index) != nullptr)
					this->PointsSets.at(C_Point_SET - 1)->TX->Antenna_Array = this->AntennaArrays.at(index);
				else
					cout << " ERROR : SHULD NOT BE HERE 8" << endl;
			}
		}
		if (F_Points_TX_CARRIER)
		{
			if (I_Points_Tx_Carrier == 0)
				I_Points_Tx_Carrier++;
			else if (I_Points_Tx_Carrier == 1)
			{
				size_t index{ 0 };
				converter<<line;converter>>index; converter.clear();
				if (this->Carriers.at(index) != nullptr)
					this->PointsSets.at(C_Point_SET - 1)->TX->Carrier = this->Carriers.at(index);
				else
					cout << " ERROR : SHULD NOT BE HERE 10" << endl;
			}
			else
				cout << " ERROR : SHULD NOT BE HERE 9" << endl;
		}

		if (F_Points_POINTS_LOCATIONS)
		{
			// seems not much to do here
		}
		if (F_Points_POINT)
		{
			if (I_POINT == 0)
			{
				this->PointsSets.at(C_Point_SET - 1)->Point_locations.push_back(new POINT_LOCATION());
				C_POINT++;
				I_POINT++;
			}
			else if (I_POINT == 1)
			{
				converter<<line;converter>>this->PointsSets.at(C_Point_SET - 1)->Point_locations.at(C_POINT - 1)->X; converter.clear();
				I_POINT++;
			}
			else if (I_POINT == 2)
			{
				converter<<line;converter>>this->PointsSets.at(C_Point_SET - 1)->Point_locations.at(C_POINT - 1)->Y; converter.clear();
				I_POINT++;
			}
			else if (I_POINT == 3)
			{
				converter<<line;converter>>this->PointsSets.at(C_Point_SET - 1)->Point_locations.at(C_POINT - 1)->Z; converter.clear();
				I_POINT = 0;
			}
			else
				cout << " ERROR : SHULD NOT BE HERE 15" << endl;
		}
	}
}