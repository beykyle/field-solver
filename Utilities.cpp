#include "Utilities.h"

double sum(vector <double> values ) {
    double sum  = 0.0;
    for (auto v : values) {
        sum += v;
    };
    return(sum);
};

double mean(vector <double> values) {
    return(sum(values) / double(values.size()) );
};

double dot(vector <double> vals1 , vector <double> vals2) {
    if (vals1.size() != vals2.size() ) {
        std::cerr << "Runtime error: dot() requires vectors of the same size" <<std::endl; 
        return(0);
    }
    
    double runningSum = 0.0;
    for (int i = 0; i < vals1.size(); ++i) {
        runningSum += vals1.at(i) * vals2.at(i);
    }

    return(runningSum);
};


double normL2(vector <double> vals1 , vector <double> vals2 ) {
    if (vals1.size() != vals2.size() ) {
        std::cerr << "Cannot do L2 with vectors of size " << vals1.size() << " and " << vals2.size() << std::endl;
        std::cerr << "Runtime error: normL2() requires vectors of the same size" <<std::endl;
    }
    
    double runningDiff   = 0.0;
    double runningProd1  = 0.0;

    for (int i = 0; i < vals1.size(); ++i) {
        runningDiff  += pow(vals1.at(i) -  vals2.at(i),2);
        runningProd1 +=  pow(vals1.at(i) , 2) +  pow(vals2.at(i) , 2);
    }

    if (runningProd1 == 0) {
        std::cerr << "Runtime error: normL2() requires non-zero vectors" <<std::endl;
    }

    return( pow( (runningDiff / runningProd1 ) , 0.5) );
};


bool testConvergence(vector <double> oldPot , vector<double> currentPot , vector<double> &diff , double condition ) {
   
    bool converge = false;
    
    diff.push_back( normL2( oldPot , currentPot ) );

    // if the normalized L2 reflects 10% difference in potentials
    // between iterations, convergence is satisfied
    if (( pow( diff.at(diff.size() -1) - diff.at(diff.size() - 2) , 2) ) < pow(condition,2) ) {
        converge = true;
    };

    return(converge);

};

