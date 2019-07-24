#include <iostream>
#include <vector>
#include "mc.h"

using namespace std;

int main()
{
	mc mc1;
	int num_kind = 3;
	int check_point = 1000;
	vector <int> num_param;
	vector <double> lambda;
	vector < vector <double> > param;
	double ene = 0.0;
	double count = 0.0;

	for(size_t t1=0; t1<num_kind; t1++)
	{
		num_param.push_back(t1+2);
		lambda.push_back((t1+2)*0.1);
	}

	param.resize(num_kind);
	count = 0.0;
	for(size_t t1=0; t1<num_kind; t1++)
		for(size_t t2=0; t2<num_param[t1]; t2++)
		{
			count += 1.0;
			param[t1].push_back(count);
			
		}
	mc1.init(num_kind, check_point, num_param, lambda, param, ene);
	mc1.print();
	return 0;
}
