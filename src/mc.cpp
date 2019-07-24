#include <iostream>
#include "mc.h"

using namespace std;

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
