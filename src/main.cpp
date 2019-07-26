#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <chrono>
#include "mc.h"

using namespace std;

double get_ene(vector < vector <double> >& param, vector < vector <double> >& target)
{
	double ene = 0;
	for(size_t t1=0; t1<param.size(); t1++)
		for(size_t t2=0; t2<param[t1].size(); t2++)
			ene += (param[t1][t2]-target[t1][t2])*(param[t1][t2]-target[t1][t2]);
	return ene;
}

int main()
{
	chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
	srand(now.time_since_epoch().count());
	mc mc1;
	thermo_profile Tem1;
	int T_max, T_min;
	int period = 300;
	int num_kind = 3;
	int check_point = 30;
	vector <int> num_param;
	vector <double> lambda;
	vector < vector <double> > param, target;
	double ene = 0.0;
	double count = 0.0;
	
	for(size_t t1=0; t1<num_kind; t1++)
	{
		num_param.push_back(t1+2);
		lambda.push_back(1);
	}
	target.resize(num_kind);
	param.resize(num_kind);
	count = 0.0;
	for(size_t t1=0; t1<num_kind; t1++)
		for(size_t t2=0; t2<num_param[t1]; t2++)
		{
			count += 1.0;
			target[t1].push_back(count);
			param[t1].push_back(0);
			
		}
	ene = get_ene(param,target);
	T_max = ene/1000;
	T_min = T_max/1000;
	
	mc1.init(num_kind, check_point, num_param, lambda, param, ene);
	Tem1.init(period,T_max,T_min);
	for(size_t t1=0; t1<3*period; t1++)
	{
		mc1.gen_param_kind(param);
		ene = get_ene(param,target);
		Tem1.gen_T(t1,"log");
		mc1.evaluate(Tem1,ene);
	}
	mc1.print();
	return 0;
}
