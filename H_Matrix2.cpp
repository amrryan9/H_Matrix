// H_Matrix2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// This is The new Branch Modification

#include "File_Processing.h"
#include "File_Processing_SISO.h"
#include <iostream>

int main()
{
	auto* f = new File_Processing();
	auto* g = new File_Processing_SISO();

//	(g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m")).CreatDistanceSubsets(SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //

/*
		%********************** 0 deg * ******************************
		%        60    70    80    90   100   110   120
		cases = [30.0 106.0 136.0 105.0 126.0 116.0 31.0]; %
		 0:21 ,   300:320   , 411:432, 506:516 , 517:527 , 628:538
		%**********************60 deg * ******************************
		%        60   120    70    110     80     90    100
		cases = [14.0 15.0 135.0 115.0  145.0    125.0 155.0]; %

		433:609
		%%**********************30 deg * ******************************
		%%       60   70    80    90    100   110   120
		cases = [214.0 314.0 315.0 338.0 318.0 414.0 514.0]; %
		610:630 633:653  731:763
		%**********************45 deg * ******************************
		%         60   120    70    110     80     90    100
		cases = [614.0 914.0 714.0 814.0  1114.0 1214.0 1014.0]; %
		654:730
*/
	Set S;
	std::array<int, 12>folders = { 9700, 9730, 9745, 9760, 9800, 9830, 9845, 9860, 9900, 9930, 9945, 9960 };
	std::vector<size_t> zero_points_los;
	std::vector<size_t> zero_points_nlos;

	/*		//	for (int x :folders)
	{
		int x = 9700;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");
		zero_points_los = S.CreatOneDistanceSubsets(true,LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true,NLOS);
		//for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}
//	for (int x = 1; x <= 21; x = x + 2) // 120 Street
	{
//		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
//		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false,LOS);
//		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false,NLOS);
	}
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9800;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
	//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}

	for (int x = 422; x <= 432; x = x + 1) // 110 Street
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}

	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9900;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
	//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}

	for (int x =528; x <= 538; x = x + 1) // 100 Street
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}
		for (int x = 517; x <= 527; x = x + 1) // 90 Street
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	for (int x = 506; x <= 516; x = x + 1) // 80 Street
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	for (int x = 411; x <= 421; x = x + 1) // 70 Street
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	for (int x = 0; x <= 20; x = x + 2) // 60 Street
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9960;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
	//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}

	for (int x = 499; x <= 505; x = x +1) // 100 cross 60-part1
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}
	for (int x = 606; x <= 609; x++) // 100 cross 60-part2
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}
	
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9860;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
	//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}

	for (int x = 455; x <= 465; x++) // 110 cross 60
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}
	
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9760;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
	//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}
	
	for (int x = 444; x <= 454; x++) // 120 cross 60
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}

	for (int x = 466; x <= 476; x++) // 90 cross 60
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	for (int x = 488; x <= 498; x++) // 80 cross 60
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	for (int x = 477; x <= 487; x++) // 70 cross 60
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	for (int x = 433; x <= 443; x++) // 60 cross 60
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	
	/// //////////////////////////////////////////////////////
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9745;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
		//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}
	for (int x = 687; x <= 697; x++) // 120 cross 45
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9845;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
		//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}
	for (int x = 676; x <= 686; x++) // 110 cross 45
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9945;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
		//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}
	for (int x = 698; x <= 708; x++) // 100 cross 45
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}
	for (int x = 720; x <= 730; x++) // 90 cross 45
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	for (int x = 709; x <= 719; x++) // 80 cross 45
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	for (int x = 665; x <= 675; x++) // 70 cross 45
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	for (int x = 654; x <= 664; x++) // 120 cross 45
	{
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", LOS)).CreatOneDistanceSubsets();//(MIMO);// .GetDistribution();//.ShowAllPathes(1, 1, 1, 100);// , 1, 1);//
//		(f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir", NLOS)).CreatOneDistanceSubsets();
	}
	/// ////////////////////////////////////////////////////////////////
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9930;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
		//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}
	for (int x = 742; x <= 752; x++) // 100 cross 30
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9730;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
		//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}
	for (int x = 634; x <= 644; x++) // 120 cross 30
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 9830;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
		zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);
		//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
	}
	for (int x = 844; x <= 854; x++) // 110 cross 30
	{
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, LOS);
		(S.RemoveLines(zero_points_nlos)).CreatOneDistanceSubsets2(false, NLOS);
	}
	*/


	/*	zero_points_los.clear();
		zero_points_nlos.clear();
		int x = 10001;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, ALL);
		//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;

		x = 10005;
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, ALL);
	*/
	for (int x = 10009; x <= 10018; x++)
	{
		zero_points_los.clear();
		zero_points_nlos.clear();
		int y = 10002;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(y) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, ALL);

		//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, ALL);

	}
	/*
		zero_points_los.clear();
		zero_points_nlos.clear();
		x = 10003;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, ALL);


		//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
		x = 10007;
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, ALL);


		zero_points_los.clear();
		zero_points_nlos.clear();
		x = 10004;
		S = g->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");// .CreatOneDistanceSubsets();// (SISO); //.ShowH();////.ShowCapacity();//  .ShowValid();//.ShowPower();// .ShowPower(0, 0); //
		zero_points_los = S.CreatOneDistanceSubsets(true, ALL);

		//	for (auto z : zero_points_los) std::cout << " Point # : " << z << " has zero Capacity." << endl;
		x = 10008;
		S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/cir");
		(S.RemoveLines(zero_points_los)).CreatOneDistanceSubsets2(false, ALL);

		*/


	system("pause");
	return 0;
}

