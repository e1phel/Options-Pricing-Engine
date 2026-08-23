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
	string line, stock, temp,exp;
	ifstream data, options;
	vector<vector<string>>inputs;
	vector<vector<string>>call;
	bool run = false;
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
	int loc=0,loc1 = 0;
	loc=inputs[1][0].find("<");
	loc1 = inputs[1][0].find(">");
	stock = inputs[1][0].substr(loc+1, loc1-1);
	cout << stock;
	///////
	spot = stod(inputs[1][1]);
	vol = stod(inputs[1][2]);
	risk = stod(inputs[1][3]);
	exp = inputs[1][4];
    }
	void read_strike_data()
	{
		int x=1;
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
		strike = stod(call[x][0]);
		deflt = stod(call[x][1]);
		if (run == true)
		{
			x++;
			strike = stod(call[x][0]);
			deflt = stod(call[x][1]);
		}
	}
	
};
class call:public data_read
{
protected:
	double d1, d2, num, denm,d1b,d1a;
public:
	void generate_call()
	{
		d1b = log(spot / strike);
		d1a = (risk + (pow(vol, 2) / 2)) * time;
		denm = vol * sqrt(time);
		d1 = num / denm;
		d2 = d1 - denm;
		return (spot * norm(d1)) - (strike * exp(-(risk * time)) * norm(d2));
	}
};
int main()
{
	data_read d;
	d.read_spot_data();
	d.read_strike_data();
}

