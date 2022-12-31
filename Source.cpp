

#include "File_Processing.h"
#include "WirelessInsiteFiles.h"
#include "Application.h"
#include <iostream>


int main()
{
	
	auto* E = new Environment();
	auto* f = new File_Processing();
	auto* W = new WirelessInsiteFiles();
	Set S,S1,S2,S3;
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
//	S.ShowPathes();
//	S.ShowRXPoints(POLAR);
//	S.Save("D:/first_set3.set");
 

	S1.Load("D:/first_set3.set");
//	S2 = *(S1.GetEXPO(EXPOSURE::LOS).Filter(PROPERITIES::POWER_dBm, 0, -32));// ->ShowRXPoints(POLAR);//WriteRXPoints("D:/trail.csv", POLAR);//,PROPERITIES::RADIAL_DISTANCE, 25 , PROPERITIES::RADIAL_DISTANCE, 25, PROPERITIES::DIRECT_DISTANCE, 112, 12.9
//	S1 = S.OmitLOS();// .ShowPathes();
//	S2.ShowRXPoints(RECT);
/*
	cout << " BEFORE :" << endl;
	for (auto& l : S.S)
		for (auto& p : l.Pathes)
			for (auto& r : p.RAYS)
				if (r.Arrival_Time < 0)
				{
					cout << " POINT # : " << l.Receiver_Point << endl;
					r.Show();
					l.ShowAllPathes();
				}
	
//	S3=(S1.GetPureLOS());//.Filter(PROPERITIES::MEAN_ARRIVAL_TIME,5.0e-7,0)
 	S3 = (S1.GetNormDelayLOS().OmitLOS());//
	cout << " AFTER :" << endl;
	for (auto& l : S3.S)
		for (auto& p : l.Pathes)
			for (auto& r : p.RAYS)
				if (r.Arrival_Time < 0)
					r.Show();
*/
//	S3 = (S1.GetPureLOS());//.Filter(PROPERITIES::MEAN_ARRIVAL_TIME,5.0e-7,0)
//	S3 = (S1.GetNormDelayLOS().OmitLOS());//
	//S3.ShowRXPoints();
//	S3.ShowPathes();
	S2 = S1.GetEXPO(EXPOSURE::NLOS);

	size_t array_elements_UAV{ 4 };
	size_t array_elements_UE{ 2 };
	float s = 0.0536; //(3e8 / (2 * 2.8e9));
	float tx_power = Environment::ReadTestCaseData("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(847) + "/Transmitter_power.txt"); cout << " POwer : " << tx_power << endl;
	ULA UAV_ula(array_elements_UAV, s, 0.0, 0.0);
	ULA UE_ula(array_elements_UE, s, 0.0, 0.0);
	Application::OutputFiles(S2, UE_ula, UAV_ula, 2800000.03, tx_power, "D:/data_file", "D:/output_file");



	valarray<ComplexF> x(4);
	x[0] = ComplexF(0.0757 - 1.0097i);
	x[1] = ComplexF(0.0387 + 1.0129i);
	x[2] = ComplexF(-3.9858 + 0.3364i);
	x[3] = ComplexF(0.5877 + 0.8909i);
	cout << " std : " << Std<ComplexF>(x) << endl;

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