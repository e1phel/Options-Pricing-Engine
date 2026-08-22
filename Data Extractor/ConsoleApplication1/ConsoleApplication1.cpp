#include<iostream>
#include<math.h>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class data_read
{
protected:
	double spot, strike, vol, exp, risk;
	const double euler = 2.718;
	int size = 0;
public:
	vector<vector<string>>inputs;
	void read_data()
	{
	ifstream data{ "C:\\Users\\pc\\Documents\\GitHub\\Options-Pricing-Engine\\Data Extractor\\Data Extractor\\data_inputs.csv" };
	string line,temp;
	getline(data, line);
	getline(data, line);
	size = line.find(",");
	temp = line.substr(0,size);
	cout << temp;
	
    }

};
int main()
{
	data_read d;
	d.read_data();
}

