

#include "File_Processing.h"
#include "WirelessInsiteFiles.h"
#include <iostream>


int main()
{
	auto* E = new Environment();
	auto* f = new File_Processing();
	auto* W = new WirelessInsiteFiles();
	Set S;
	/** Creat Communication System **/
	CommunicationSystem* System = new CommunicationSystem();
	System->AddNewCarrier(2800000000, 1000000," Carrier Frequency");
	System->AddNewCarrier(2800000000, 1000000, " Carrier Frequency");
	System->AddNewAntennaType("Isotropic", "isotropic");
	System->AddNewAntennaArray("BS", "Base Station");
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

	/********************************/
	W->CommSystem = *System;
	W->City_File = "City.city";
	W->TxRx_File = "ProjectName.txrx";
	W->WriteFiles_1("D:/file_1.txt");
	W->WriteFiles_2("D:/file_2.txt");
	E->SetTerminalsPositionsFileDirectory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(847));

	
//	S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(847) + "/MIMO_BS_UAV_TERMINALS/cir");
//	S.GetEXPO(EXPOSURE::NLOS).Filter(PROPERITIES::POWER_dBm, 0, -32, PROPERITIES::DIRECT_DISTANCE, 112, 12.9, PROPERITIES::RADIAL_DISTANCE, 25)->ShowRXPoints(POLAR);//WriteRXPoints("./trail.csv", POLAR);// 

}