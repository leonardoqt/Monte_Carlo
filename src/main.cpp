#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <chrono>
#include "mc.h"

using namespace std;

double get_ene(vector < vector <double> >& param)
{
	double ene = 0;
	for(size_t t1=0; t1<param.size(); t1++)
	{
		for(size_t t2=0; t2<param[t1].size()-1; t2++)
			ene += 100*pow(param[t1][t2+1]-pow(param[t1][t2],2),2) + pow((1-param[t1][t2]),2);
//		ene += 100*pow(param[t1][0]-pow(param[t1][param[t1].size()-1],2),2) + pow((1-param[t1][param[t1].size()-1]),2);
	}
	return ene;
}

int main()
{
	chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
	srand(now.time_since_epoch().count());
	mc mc1;
	thermo_profile Tem1;
	int T_max, T_min;
	int num_kind = 1;
	int check_point = 100;
	int period;
	vector <int> num_param;
	vector <double> lambda,max_param,min_param;
	vector < vector <double> > param;
	double ene = 0.0;
	double count = 0.0;
	
	for(size_t t1=0; t1<num_kind; t1++)
	{
		num_param.push_back(20);
		lambda.push_back(1);
		max_param.push_back(3);
		min_param.push_back(-3);
	}
	param.resize(num_kind);
	count = 0.0;
	for(size_t t1=0; t1<num_kind; t1++)
		for(size_t t2=0; t2<num_param[t1]; t2++)
		{
			param[t1].push_back(0);
			count++;
		}
	ene = get_ene(param);
	T_max = 100;
	T_min = 1e-10;
	period = 10*count*check_point;
	
	mc1.init(num_kind, check_point, num_param, lambda, max_param, min_param, param, ene);
	Tem1.init(period,T_max,T_min);
	for(size_t t1=0; t1<100*period; t1++)
	{
		mc1.gen_param_kind(param);
		ene = get_ene(param);
		Tem1.gen_T(t1,"log");
		mc1.evaluate(Tem1,ene);
		if((t1+1)%period==0)
			cout<<ene<<endl;
		if(ene < 1e-8)
			break;
	}
	mc1.print();
	return 0;
}
