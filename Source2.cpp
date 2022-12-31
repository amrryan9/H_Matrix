#include "File_Processing.h"
#include "WirelessInsiteFiles.h"
#include "Application.h"
#include <iostream>
int main(void)
{
	
	float carrier_frequency = 30e9;
	float lamda = 3.0e8 / carrier_frequency;
	size_t n = 8;
	float s = lamda / 2.0;
	float phi = 60 * 22 / (7.0 * 180.0);
	float theta=90 * 22 / (7.0 * 180.0);
	ULA UAV_ULA(n, s, phi, theta);
	VERTIX UAV = VERTIX(500, 500, 120);
	valarray<VERTIX> UAV_COR =UAV_ULA.GetCorrdinates(UAV);
	for (auto& c : UAV_COR)
	{
		cout << " item : " << endl;
		cout << c.x << endl;
		cout << c.y << endl;
		cout << c.z << endl;
		cout << endl;
	}
//	int x;
//	std::cin >> x;
		
	return 0;
}