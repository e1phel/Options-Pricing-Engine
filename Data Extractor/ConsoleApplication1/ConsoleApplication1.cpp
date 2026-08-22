#include<iostream>
#include<math.h>
#include<fstream>

using namespace std;

class data_read
{
protected:
	double spot,strike,vol,exp,risk,
public:
	ifstream file{ "C:\\Users\\pc\\Documents\\GitHub\\Options-Pricing-Engine\\Data Extractor\\Data Extractor\\data_inputs.csv" };

};
int main()
{
	data_read d;
	d.run();
}

