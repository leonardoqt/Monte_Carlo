#ifndef __MC__
#define __MC__

#include <vector>

using namespace std;

class thermo_profile
{
private:
	double T_max, T_min;
	double T;
	int period;
	int iter;
public:
	void init(int Period, double T_Max, double T_Min);
	double gen_T(int Iter);
	double gen_T();
};

class mc
{
private:
	int num_kind;
	int check_point;
	vector <int> num_param;
	vector <double> lambda;
	vector <int> num_run;
	vector <int> num_accept;
	vector < vector <double> > pre_param;
	vector < vector <double> > opt_param;
	vector < vector <double> > new_param;
	double pre_ene;
	double opt_ene;
	double new_ene;
	int kind_change, param_change;
public:
	void init(int &Num_kind, int Check_point, vector <int> &Num_param, vector <double> &Lambda, vector < vector <double> > &Ini_param, double Ini_ene);
	void gen_param(vector < vector <double> >& param);
	void gen_param_kind(vector < vector <double> >& param);
	int evaluate(thermo_profile& thermo, double ene);
	
	void get_param_ene(vector < vector <double> >& Pre_param, vector < vector <double> >& Opt_param, double& Pre_ene, double& Opt_ene);
	void print();
};

#endif
