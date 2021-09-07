

#include "File_Processing.h"
#include "WirelessInsiteFiles.h"
#include <iostream>


int main()
{
	auto* E = new Environment();
	auto* f = new File_Processing();
	auto* W = new WirelessInsiteFiles();
	Set S;
	
	W->WriteFiles_1("D:/file_1.txt");
	W->WriteFiles_2("D:/file_2.txt");
	E->SetTerminalsPositionsFileDirectory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(847));

	
//	S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(847) + "/MIMO_BS_UAV_TERMINALS/cir");
//	S.GetEXPO(EXPOSURE::NLOS).Filter(PROPERITIES::POWER_dBm, 0, -32, PROPERITIES::DIRECT_DISTANCE, 112, 12.9, PROPERITIES::RADIAL_DISTANCE, 25)->ShowRXPoints(POLAR);//WriteRXPoints("./trail.csv", POLAR);// 

}