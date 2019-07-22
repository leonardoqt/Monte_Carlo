#ifndef __MC__
#define __MC__
#include <vector>
class mc
{
private:
	int num_kind;
	vector <int> num_param;
	vector < vector <double> > pre_param;
	vector < vector <double> > opt_param;
	vector < vector <double> > new_param;
	vector < vector <double> > lambda;
	double pre_ene;
	double opt_ene;
	double new_ene;
};
#endif
