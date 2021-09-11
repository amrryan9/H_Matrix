

#include "File_Processing.h"
#include "WirelessInsiteFiles.h"
#include <iostream>


int main()
{

	auto* E = new Environment();
	auto* f = new File_Processing();
	auto* W = new WirelessInsiteFiles();
	Set S;
	// Creat Communication System 
	CommunicationSystem* System = new CommunicationSystem();
	System->AddNewCarrier(2800000000, 1000000,"Carrier_Frequency");
	System->AddNewCarrier(2800000000, 1000000, "Carrier_Frequency");
	System->AddNewAntennaType("Isotropic", "isotropic");
	System->AddNewAntennaArray("BS", "Base_Station");
	System->AddNewAntennaArray("Terminal", "Terminal");
	
	System->AntennaArrays.at(0)->AddElement(System->AntennaTypes.at(0), 0, 0, 0, 10, 10, 10);
	System->AntennaArrays.at(0)->AddElement(System->AntennaTypes.at(0), 0, 0, 0, 11, 11, 11);
	System->AntennaArrays.at(0)->AddElement(System->AntennaTypes.at(0), 0, 0, 0, 12, 12, 12);
	System->AntennaArrays.at(0)->AddElement(System->AntennaTypes.at(0), 0, 0, 0, 13, 13, 13);

	System->AntennaArrays.at(1)->AddElement(System->AntennaTypes.at(0), 0, 0, 0, 10.5, 10.5, 10.5);
	System->AntennaArrays.at(1)->AddElement(System->AntennaTypes.at(0), 0, 0, 0, 11, 11.5, 11.5);

	System->AddNewPoints("Base_Station");
	System->AddNewPoints("Terminals");
	System->PointsSets.at(0)->TX = new TRANSMITTER(System->Carriers.at(1), System->AntennaArrays.at(0), 30);

	System->PointsSets.at(0)->AddNewPointAt(0,0,0);
	System->PointsSets.at(0)->Transmitter_exist = true;
	System->PointsSets.at(1)->RX = new RECEIVER(System->Carriers.at(1), System->AntennaArrays.at(1), 3);
	System->PointsSets.at(1)->Receiver_exist=true;
	System->PointsSets.at(1)->AddNewPointAt(20, 22, 23);
	System->PointsSets.at(1)->AddNewPointAt(30, 33, 34);
	System->Show();
	
	System->WriteTofile("D:/test2.ssv");
	/*
	//*****************************
	W->CommSystem = *System;
	W->City_File = "City.city";
	W->Project_Folder = "D:/Test_H_Matrix";
	W->Project_Name = "Test_Project_1";
	W->Study_Area_Folder = "Test_Project_1_Study_Area_Folder_Name";
	W->WriteFiles_1();
	W->WriteFiles_2();
	//*****************************

	E->SetTerminalsPositionsFileDirectory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(847));

	
	S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(847) + "/MIMO_BS_UAV_TERMINALS/cir");
	S.GetEXPO(EXPOSURE::NLOS).Filter(PROPERITIES::POWER_dBm, 0, -32, PROPERITIES::DIRECT_DISTANCE, 112, 12.9, PROPERITIES::RADIAL_DISTANCE, 25)->WriteRXPoints("D:/trail.csv", POLAR);// ShowRXPoints(POLAR);//
*/
	cout << "***************************************************" << endl;
	CommunicationSystem* System_2 = new CommunicationSystem();
	System_2->RestoreFromFile("D:/test2.ssv");
	System_2->Show();
}