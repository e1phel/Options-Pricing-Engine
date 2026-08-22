#include<iostream>
#include<math.h>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class data_read
{
protected:
	double spot, strike, vol,risk,deflt;
	const double euler = 2.718;
	int loc = 0;
	string line, stock, temp,exp;
public:
	vector<vector<string>>inputs;
	void read_data()
	{
	ifstream data{ "C:\\Users\\pc\\Documents\\GitHub\\Options-Pricing-Engine\\Data Extractor\\Data Extractor\\data_inputs.csv" };
	ifstream options{ "C:\\Users\\pc\\Documents\\GitHub\\Options-Pricing-Engine\\Data Extractor\\Data Extractor\\call_info.csv" };
	getline(data, line);
	getline(data, line);
	loc = line.find(",");
	stock = line.substr(0,loc);
	cout << stock << endl;
	temp = line.substr(loc+1, line.length());
	loc = temp.find(",");
	spot = stod(temp.substr(0, loc));
	cout << spot<<endl;
	temp = temp.substr(loc + 1, temp.length());
	loc = temp.find(",");
	vol = stod(temp.substr(0, loc));
	cout << vol << endl;
	temp = temp.substr(loc + 1, temp.length());
	loc = temp.find(",");
	risk = stod(temp.substr(0, loc));
	cout << risk<<endl;
	temp = temp.substr(loc + 1, temp.length());
	loc = temp.find(",");
	exp = temp.substr(0, loc);
	cout << exp << endl;
    }
};
class call:public data_read
{
protected:
	double d1, d2, num, denm,d1b,d1a;
};
int main()
{
	data_read d;
	d.read_data();
}

