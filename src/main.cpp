#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <cmath>
#include "mc.h"

using namespace std;

//Rosenbrock
double get_ene(vector < vector <double> >& param)
{
	double ene = 0;
	for(size_t t1=0; t1<param.size(); t1++)
		for(size_t t2=0; t2<param[t1].size()-1; t2++)
			ene += pow((1-param[t1][t2]),2)+100*pow(param[t1][t2+1]-pow(param[t1][t2],2),2);
	return ene;
}

int main()
{
	mc mc1;
	thermo_profile Tem1;
	int T_max, T_min;
	int num_kind = 2;
	int check_point = 100;
	int period = num_kind*check_point*200;
	vector <int> num_param;
	vector <double> lambda;
	vector < vector <double> > param;
	double ene = 0.0;
	double count = 0.0;
	double ene0,ene1,ene2;
	
	for(size_t t1=0; t1<num_kind; t1++)
	{
		num_param.push_back((t1+1)*50);
		lambda.push_back(1);
	}
	param.resize(num_kind);
	for(size_t t1=0; t1<num_kind; t1++)
		for(size_t t2=0; t2<num_param[t1]; t2++)
			param[t1].push_back(2);
	ene = get_ene(param);
	T_max = ene*1;
	T_min = ene/10000;
	
	mc1.init(num_kind, check_point, num_param, lambda, param, ene);
	Tem1.init(period,T_max,T_min);
	for(size_t t1=0; t1<100*period; t1++)
	{
		mc1.gen_param_kind(param);
		ene = get_ene(param);
		Tem1.gen_T(t1,"mixed");
		mc1.evaluate(Tem1,ene);
		if ((t1+1)%period==0)
		{
			mc1.get_param_ene(param,param,ene0,ene1,ene2);
			cout<<fixed<<setprecision(6)<<setw(15)<<ene0<<setw(15)<<ene1<<setw(15)<<ene2<<endl;
		}
	}
	mc1.print();
	return 0;
}
