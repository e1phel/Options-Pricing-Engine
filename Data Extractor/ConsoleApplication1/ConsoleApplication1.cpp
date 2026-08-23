#include<iostream>
#include<math.h>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

class data_read
{
protected:
	double spot, strike, vol,risk,deflt;
	const double euler = 2.718;
	int loc = 0;
	string line, stock, temp,exp;
	ifstream data, options;
	vector<vector<string>>inputs;
	vector<vector<string>>call;
public:
	data_read():
		 data{ "C:\\Users\\pc\\Documents\\GitHub\\Options-Pricing-Engine\\Data Extractor\\Data Extractor\\data_inputs.csv" },
		options{ "C:\\Users\\pc\\Documents\\GitHub\\Options-Pricing-Engine\\Data Extractor\\Data Extractor\\call_info.csv" }
	{
	}
	void read_spot_data()
	{
	while (getline(data, line))
	{
		vector<string>rows;
		stringstream ss(line);
		string word;
		while (getline(ss,word, ','))
		{
			rows.push_back(word);
		}
		inputs.push_back(rows);
	}
	//stock settings


    }
	void read_strike_data()
	{
		while (getline(options, line))
		{
			vector<string>rows;
			stringstream ss(line);
			string word;
			while (getline(ss, word, ','))
			{
				rows.push_back(word);
			}
			call.push_back(rows);
		}
		
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
	d.read_spot_data();
	d.read_strike_data();
}

