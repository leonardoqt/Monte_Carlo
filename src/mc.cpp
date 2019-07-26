#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "mc.h"

using namespace std;

void thermo_profile :: init(int Period, double T_Max, double T_Min)
{
	T_max = T_Max;
	T_min = T_Min;
	period = Period;
	T = 1;
	iter = 0;
}

double thermo_profile :: gen_T(int Iter, string profile)
{
	iter = Iter%period;
	if(profile.find("linear")!=string::npos)
		T = T_max - ((T_max-T_min)*iter)/(period-1);
	else if(profile.find("log")!=string::npos)
		T = T_max*exp(log(T_min/T_max)*iter/(period-1));
	else if (profile.find("mixed")!=string::npos)
	{
		if (iter < period/2)
			T = T_max - ((T_max-T_min)*iter)/(period-1);
		else
			T = (T_max+T_min)/2*exp(log(T_min*2/(T_max+T_min))*(iter-period/2)*2/(period-2));
	}
	else
	{
		cout<<"Error, need to specify temperature profile";
		exit(EXIT_FAILURE);
	}
	return T;
}

double thermo_profile :: gen_T()
{
	return T;
}

void mc :: init(int &Num_kind, int Check_point, vector <int> &Num_param, vector <double> &Lambda, vector < vector <double> > &Ini_param, double Ini_ene)
{
	//
	num_kind = Num_kind;
	check_point = Check_point;
	//
	num_param.resize(Num_kind);
	lambda.resize(Num_kind);
	num_run.resize(Num_kind);
	num_accept.resize(Num_kind);
	for(size_t t1=0; t1<Num_kind; t1++)
	{
		num_param[t1] = Num_param[t1];
		lambda[t1] = Lambda[t1];
		num_run[t1] = 0;
		num_accept[t1] = 0;
	}
	//
	pre_param.resize(Num_kind);
	opt_param.resize(Num_kind);
	new_param.resize(Num_kind);
	for(size_t t1=0; t1<Num_kind; t1++)
	{
		pre_param[t1].resize(Num_param[t1]);
		opt_param[t1].resize(Num_param[t1]);
		new_param[t1].resize(Num_param[t1]);
		for(size_t t2=0; t2<Num_param[t1]; t2++)
			pre_param[t1][t2] = opt_param[t1][t2] = Ini_param[t1][t2];
	}
	//
	pre_ene = opt_ene = Ini_ene;
	new_ene = 0;
}

void mc :: gen_param(vector < vector <double> >& param)
{
	new_param = pre_param;
	kind_change = rand()%num_kind;
	param_change = rand()%num_param[kind_change];
	new_param[kind_change][param_change] = pre_param[kind_change][param_change] + ((rand()/(double)RAND_MAX)*2-1)*lambda[kind_change];
	param = new_param;
}

void mc :: gen_param_kind(vector < vector <double> >& param)
{
	new_param = pre_param;
	kind_change = rand()%num_kind;
	for(size_t t1 = 0; t1<num_param[kind_change]; t1++)
		new_param[kind_change][t1] = pre_param[kind_change][t1] + ((rand()/(double)RAND_MAX)*2-1)*lambda[kind_change];
	param = new_param;
}

int mc :: evaluate(thermo_profile& thermo, double ene)
{
	int if_accept;
	double rate;
	// check if accept
	new_ene = ene;
	if (new_ene <= pre_ene)
	{
		pre_param = new_param;
		pre_ene = new_ene;
		num_accept[kind_change]++;
		if_accept = 1;
		if (new_ene < opt_ene)
		{
			opt_param = new_param;
			opt_ene = new_ene;
		}
	}
	else if (rand()/(double)RAND_MAX < exp((pre_ene - new_ene)/thermo.gen_T()))
	{
		pre_param = new_param;
		pre_ene = new_ene;
		num_accept[kind_change]++;
		if_accept = 1;
	}
	else
		if_accept = 0;
	
	// adjust lambda
	num_run[kind_change]++;
	if (num_run[kind_change]==check_point)
	{
		rate = (double)num_accept[kind_change]/check_point;
		num_run[kind_change] = 0;
		num_accept[kind_change] = 0;
		if (rate < 0.2)
			lambda[kind_change]/=2;
		else if (rate > 0.4)
			lambda[kind_change]*=1.618;
	}
	
	return if_accept;
}

void mc :: get_param_ene(vector < vector <double> >& Pre_param, vector < vector <double> >& Opt_param, double& Pre_ene, double& Opt_ene, double& New_ene)
{
	Pre_param = pre_param;
	Opt_param = opt_param;
	Pre_ene = pre_ene;
	Opt_ene = opt_ene;
	New_ene = new_ene;
}


void mc :: print()
{
	cout<<"Kind of parameters                : "<<num_kind<<endl;
	cout<<"Check point                       : "<<check_point<<endl;
	cout<<"Number of each kind of parameter  : "<<endl;
	for(size_t t1=0; t1<num_kind; t1++)
		cout<<'\t'<<num_param[t1];
	cout<<endl;
	cout<<"Lambda                            : "<<endl;
	for(size_t t1=0; t1<num_kind; t1++)
		cout<<'\t'<<lambda[t1];
	cout<<endl;
	cout<<"Number of runs                    : "<<endl;
	for(size_t t1=0; t1<num_kind; t1++)
		cout<<'\t'<<num_run[t1];
	cout<<endl;
	cout<<"Number accepted                   : "<<endl;
	for(size_t t1=0; t1<num_kind; t1++)
		cout<<'\t'<<num_accept[t1];
	cout<<endl;
	cout<<"Previous parameters               : "<<endl;
	for(size_t t1=0; t1<num_kind; t1++)
	{
		for(size_t t2=0; t2<num_param[t1]; t2++)
			cout<<'\t'<<pre_param[t1][t2];
		cout<<endl;
	}
	cout<<"Best parameters                   : "<<endl;
	for(size_t t1=0; t1<num_kind; t1++)
	{
		for(size_t t2=0; t2<num_param[t1]; t2++)
			cout<<'\t'<<opt_param[t1][t2];
		cout<<endl;
	}
	cout<<"New parameters                    : "<<endl;
	for(size_t t1=0; t1<num_kind; t1++)
	{
		for(size_t t2=0; t2<num_param[t1]; t2++)
			cout<<'\t'<<new_param[t1][t2];
		cout<<endl;
	}
	cout<<"Previous penalty                  : "<<pre_ene<<endl;
	cout<<"Minimum penalty                   : "<<opt_ene<<endl;
	cout<<"New penalty                       : "<<new_ene<<endl;
}
