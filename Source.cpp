

#include "File_Processing.h"
#include <iostream>


int main()
{

	auto* f = new File_Processing();
	Set S;
	//dstd::array<int, 12>folders = { 9700, 9730, 9745, 9760, 9800, 9830, 9845, 9860, 9900, 9930, 9945, 9960 };
	std::vector<size_t> zero_points_los;
//	std::vector<size_t> zero_points_nlos;
//	int x = 9700;
//	S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(x) + "/MIMO_BS_UAV_TERMINALS/MIMO_UAV_10_LOS.cir.t001_01.r002.p2m");
//	zero_points_los = S.CreatOneDistanceSubsets(true, LOS);
//	zero_points_nlos = S.CreatOneDistanceSubsets(true, NLOS);

	S = f->read_directory("D:/Wireless Insite/MIMO_UAV_Projects/DATA_SET/" + Tools::ConvertToString(847) + "/MIMO_BS_UAV_TERMINALS/cir");
	S.GetEXPO(EXPOSURE::NLOS).Filter(PROPERITIES::POWER_dBm, 0, -32, PROPERITIES::DIRECT_DISTANCE, 112, 12.9, PROPERITIES::RADIAL_DISTANCE, 25)->WriteRXPoints("./trail.csv", POLAR);// ShowRXPoints(POLAR);
}