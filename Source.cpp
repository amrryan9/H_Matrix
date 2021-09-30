

#include "File_Processing.h"
#include "WirelessInsiteFiles.h"
#include <iostream>


int main()
{
	
	auto* E = new Environment();
	auto* f = new File_Processing();
	auto* W = new WirelessInsiteFiles();
	Set S,S1;
	/*
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
	
	//*****************************
	W->CommSystem = *System;
	W->City_File = "City.city";
	W->Project_Folder = "D:/Test_H_Matrix";
	W->Project_Name = "Test_Project_1";
	W->Study_Area_Folder = "Test_Project_1_Study_Area_Folder_Name";
	W->WriteFiles_1();
	W->WriteFiles_2();
	//*****************************
*/

//	E->SetTerminalsPositionsFileDirectory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(847));
//	S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(847) + "/MIMO_BS_UAV_TERMINALS/cir");
//	S.Save("D:/first_set2.set");
	S1.Load("D:/first_set.set");
	S1.GetEXPO(EXPOSURE::NLOS).ShowRXPoints(POLAR);// .Filter(PROPERITIES::POWER_dBm, 0, -32, PROPERITIES::DIRECT_DISTANCE, 112, 12.9, PROPERITIES::RADIAL_DISTANCE, 25)->ShowRXPoints(POLAR);//WriteRXPoints("D:/trail.csv", POLAR);// 
//	S.ShowRXPoints(POLAR);
//	S1.ShowRXPoints(POLAR);
// 
// 
//	cout << "***************************************************" << endl;
//	CommunicationSystem* System_2 = new CommunicationSystem();
//	System_2->RestoreFromFile("D:/test2.ssv");
//	System_2->Show();



/*

	POSITION Ps1(0.1, 2.0, 33, 22.2, 10.25, 0.2, 0.5, 0.6);
	POSITION Ps2;
	Ray r1(12, 20, 2.35, 2.3, 0.0025);
	Ray r2;
	PATHS path1(1, 5), path2;
	path1.RAYS.push_back(r1);
	Set_Line L, M;
	L = S.S[0];
	T_R_Set TSET1, TSET2;
	TSET1 = S.Receivers[0]; TSET1.SHOW();
	Complex_matrix C , D;//, E;
	
	C.AddItem(0, 0, complex<double>(12.3, 3.1));
	C.AddItem(0, 1, complex<double>(1.3, -3.1));
	C.AddItem(0, 2, complex<double>(2.3, 0.1));

	C.AddItem(1, 0, complex<double>(-12.3, 3.1));
	C.AddItem(1, 1, complex<double>(10.3, 3.1));
	C.AddItem(1, 2, complex<double>(-9.3, 3.1));

	C.AddItem(2, 0, complex<double>(12.3, 3.1));
	C.AddItem(2, 1, complex<double>(10.3, -7.1));
	C.AddItem(2, 2, complex<double>(12.0, 5.1));


	WirelessPower P1(C); 
	std::ofstream ofile2("D:/sample2.bin", std::ios::binary);
	if (ofile2.is_open())
	{
		if (!TSET1.write(ofile2))cout << "LLLLLLLLLLLLLLLLL" << endl;
		if (!L.write(ofile2))cout << "LLLLLLLLLLLLLLLLL" << endl;
		if (!path1.write(ofile2))cout << "MMMMMMMMMMMMMMMM" << endl;
		C.Inverse().write(ofile2);
		
		if (!P1.write(ofile2))cout << "LLLLLLLLLLLLLLLLL" << endl;
		Ps1.write(ofile2);
		ofile2.close();
	}
	WirelessPower P2;
	std::ifstream ifile2("D:/sample2.bin", std::ios::binary);
	if (ifile2.is_open())
	{
		if (!TSET2.read(ifile2))cout << "LLLLLLLLLLLLLLLLL" << endl;
		if (!M.read(ifile2))cout << "LLLLLLLLLLLLLLLLL" << endl;
		if (!path2.read(ifile2))cout << "KKKKKKKKKKKKKKGGGGGG" << endl;
		if (!D.read(ifile2))cout << "KKKKKKKKKKKKKKGGGGGG" << endl;
		
		if (!P2.read(ifile2))cout << "KKKKKKKKKKKKKKKKKKK" << endl;
		if (!Ps2.read(ifile2))cout << "KKKKKKKKKKKKKKKKKKK" << endl;
		ifile2.close();
	}
	C.Inverse().Show();
	D.Show();
	path1.SHOWPATH();
	path2.SHOWPATH();
	P1.Show();
	P2.Show();
	Ps1.Show();
	Ps2.Show();
	L.Show();
	M.Show();
	*/
	return 0;
}