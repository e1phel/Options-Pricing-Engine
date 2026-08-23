#include<iostream>
#include<math.h>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<iomanip>
using namespace std;

class data_read
{
protected:
	double spot, strike, vol,risk, expire,deflt;
	int x = 1;
	const double euler = 2.718;
	string line, stock, temp;
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
	int loc=0,loc1 = 0;
	loc=inputs[1][0].find("<");
	loc1 = inputs[1][0].find(">");
	stock = inputs[1][0].substr(loc+1, loc1-1);
	///////
	spot = stod(inputs[1][1]);
	vol = stod(inputs[1][2]);
	risk = stod(inputs[1][3]);
	expire = stod(inputs[1][4]);
    }
	void read_strike_data(bool run)
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
		if (run == true) { x++; }
		strike = stod(call[x][0]);
		deflt = stod(call[x][1]);
	}
	double get_spot() { return spot; }
	string get_stock() { return stock; }
	double get_vol() { return vol; }
	double get_risk() { return risk; }
	double get_exp() { return expire; }
	double get_strike() { return strike; }
	double get_market() { return deflt; }
	
	
};
class call:public data_read
{
protected:
	double d1, d2, num, denm,d1b,d1a;
public:
	double norm(double x) {
		return 0.5 * (1 + erf(x / sqrt(2)));
	}
	double generate_call()
	{
		d1b = log(spot / strike);
		d1a = (risk + (pow(vol, 2) / 2)) * expire;
		num = d1b + d1a;
		denm = vol * sqrt(expire);
		d1 = num / denm;
		d2 = d1 - denm;
		return (spot * norm(d1)) - (strike * exp(-risk * expire) * norm(d2));;
	}
};
int main()
{
	bool run = false;
	data_read d;
	call c;
	double diff;
	double cundiff=0;
	double avg;
	int cont = 6;
	c.read_spot_data();
	cout << fixed << setprecision(2);
	cout << "========== Pricing Engine ==========" << endl;
	cout << "Ticker : " << c.get_stock()<<endl;
	cout << "Spot Price : $" << c.get_spot()<<endl;
	cout << "Volatality : " << c.get_vol()<<"%"<<endl;
	cout << "Risk-Free Rate : " << c.get_risk()<<"%"<<endl;
	cout << "Expiry : " << c.get_exp()<<" Years"<<endl;
	cout << "===================================="<<endl;
	cout << endl;
	cout << left << setw(10) << "Strike" << "| "<< setw(14) << "Theoretical" << "| "<< setw(12) << "Market" << "| "<< setw(12) << "Diff" << endl;
	cout << string(60, '-') << endl; 
	for (int i = 0; i < cont; i++)
	{
		c.read_strike_data(run);
		double call_price = c.generate_call();
		diff = abs(call_price - c.get_market());
		cout << left << setw(10) << c.get_strike() << "| "<< setw(14) << call_price << "| "<< setw(12) << c.get_market() << "| "<< setw(12)
			 << diff << endl;
		cundiff += diff;
		run = true;
	}
	avg = cundiff / cont;
	cout << "===================================="<<endl;
	cout << "Difference Average $" << avg<<endl;
	cout << "====================================" << endl;
}

