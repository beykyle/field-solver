#ifndef _UTILITIES_HEADER_
#define _UTILITIES_HEADER_

#include <cmath>
#include <vector>
#include <iostream>
#include <cassert>

using std::vector;

double sum(vector <double> values );

double mean(vector <double> values);

double dot(vector <double> vals1 , vector <double> vals2);

double normL2(vector <double> vals1 , vector <double> vals2 );

bool testConvergence(vector <double> oldPot , vector<double> currentPot , vector<double> &diff , double condition );

#endif
