#ifndef __MC__
#define __MC__

#include <vector>
#include <string>

class thermo_profile
{
private:
	double T_max, T_min;
	double T;
	int period;
	int iter;
public:
	void init(int Period, double T_Max, double T_Min);
	double gen_T(int Iter,std::string profile);
	double gen_T(int Iter);
	double gen_T();
};

class mc
{
private:
	int num_kind;
	int check_point;
	std::vector <int> num_param;
	std::vector <double> lambda;
	std::vector <double> max_param;
	std::vector <double> min_param;
	std::vector <int> num_run;
	std::vector <int> num_accept;
	std::vector < std::vector <double> > pre_param;
	std::vector < std::vector <double> > opt_param;
	std::vector < std::vector <double> > new_param;
	double pre_ene;
	double opt_ene;
	double new_ene;
	int kind_change, param_change;
public:
	void init(int &Num_kind, int Check_point, std::vector <int> &Num_param, std::vector <double> &Lambda, std::vector <double> &Max_param, std::vector <double> &Min_param, std::vector < std::vector <double> > &Ini_param, double Ini_ene);
	void gen_param(std::vector < std::vector <double> >& param);
	void gen_param_kind(std::vector < std::vector <double> >& param);
	int evaluate(thermo_profile& thermo, double ene);
	
	void get_param_ene(std::vector < std::vector <double> >& Pre_param, std::vector < std::vector <double> >& Opt_param, double& Pre_ene, double& Opt_ene, double& New_ene);
	void print();
	void print_ene();
};

#endif
