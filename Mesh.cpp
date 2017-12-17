#include "Mesh.h"
#include <time.h>

// other functions
enum string_code {
        eRelax,
        eFFT,
        eMatrix,
        eGreen,
        eFMM,
        eFinite,
        eMonte
};

string_code hashit (std::string const& inString) {
        if (inString == "relax"          )   return eRelax;
        if (inString == "fft"            )   return eFFT;
        if (inString == "matrix"         )   return eMatrix;
        if (inString == "green"          )   return eGreen;
        if (inString == "fmm"            )   return eFMM;
        if (inString == "finite_element" )   return eFinite;
        if (inString == "monte_carlo"    )   return eMonte;
};


// Constructrs


// Functions

void Mesh::solve(string method) {
// allowed methods: 'relax', 'fft', 'matrix', 'green', 'fmm' , 'finite_element', 'monte_carlo'
    std::cout << "Running " << method << " on " << cavity->getName() << std::endl;
    bool write = true;
    switch( hashit(method)) {
        case eRelax :
            relax();
            break;
        case eFFT :
            break;
        case eMatrix :
            break;
        case eGreen :
            break;
        case eFMM :
            break;
        case eFinite :
            break;
        case eMonte :
            break;
        default:
            write = false;
            std::cerr << method <<" is not a recognized solve method for Mesh.solve()" << std::endl;
            break;
    }

    if (write = true) {
        cavity->writePotential();
        cavity->calculateE();
        cavity->writeE();
    };

};


void Mesh::relax( ) {
    bool  converge   = false;
    int   count      = 0;
    int   wcount     = 0;
    int   size       = cavity->getPotential().size();

    vector <double>  neighbors;
    vector <double>  diff = {1.0};
    vector <double>  oldPot;

    clock_t t;

    // while the simulation hasn't converged
    while (converge == false) {
        // every 3 steps store current potential
        if (count % 3 == 0) {
            t = clock();
            oldPot = cavity->getPotential();
        }
        // iterate over non-boundary bins
        for (int n = 0; n < cavity->getPotential().size(); ++n) {
            if (cavity->isBoundary(n) == false) {
                // do relaxation on this bin
                neighbors = cavity->getNeighbors(n);
                cavity->setPotential(n , mean(neighbors));
            }
        }
        count++;   
        // every 3 steps re-evaluate convergence
        if (count % 3 == 0) {
            
            converge = testConvergence(oldPot , cavity->getPotential() , diff , 0.001 );
            
            std::cout << "<";
            wcount = (count/3 > 20 ? count - 60 : count);
            for (int i = 0; i < wcount/3; ++i)      {std::cout << "=="; }
            for (int i = 1; i < 20 - wcount/3 - 1; ++i) {std::cout << "  ";  }
            t = t - clock();
            std::cout << "Doing relaxation... step: " << count 
                      << ", normalized L2: " << diff.at(diff.size() - 1 )  
                      << ", time: " << ((float)t)/CLOCKS_PER_SEC  << std::endl;
    
        }
    } 
};
