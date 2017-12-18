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
Mesh::Mesh(RectangularCavity_ptr cavIn , vector<int> binsi) {
    bins = binsi;
    cavity = cavIn;

    vector <double> pot(bins.at(0)*bins.at(1)*bins.at(2) , 0.0);
    vector <bool>   inBound(bins.at(0)*bins.at(1)*bins.at(2) , false);
    vector <bool>   geoBound(bins.at(0)*bins.at(1)*bins.at(2) , false);

    cavity->boundaries2Mesh(bins , geoBound , inBound , pot);

    potential  = pot;
    onBoundary = inBound;
    geoBoundary = geoBound;
};

// Functions

int Mesh::ijk2n(int i , int j , int k) {
// bins are indexed from 0
    return(k * bins.at(0) * bins.at(1) + j * bins.at(1) + i );
};

vector <int>  Mesh::n2ijk(int n) {
// bins are indexed from 0

    vector <int> ijk;
    ijk.push_back(n % bins.at(0));
    ijk.push_back( (n % (bins.at(0)*bins.at(1)) ) / bins.at(0));
    ijk.push_back(n / (bins.at(0) * bins.at(1)) );

    return(ijk);
};

void Mesh::solve(string method) {
// allowed methods: 'relax', 'fft', 'matrix', 'green', 'fmm' , 'finite_element', 'monte_carlo'
    std::cout << "Running " << method << " on " << cavity->getName() << std::endl;
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
            std::cerr << method <<" is not a recognized solve method for Mesh.solve()" << std::endl;
            break;
    }

};


void Mesh::calculateE(vector <double> binWidths) {
    
    int i , j , k;
    
    double delx = binWidths.at(0);
    double dely = binWidths.at(1);
    double delz = binWidths.at(2);
    
    vector <int> tmpijk;

    for (int n = 0; n < potential.size() ; ++n) {
        tmpijk = n2ijk(n);

        i = tmpijk.at(0);
        j = tmpijk.at(1);
        k = tmpijk.at(2);

        if (geoBoundary.at(n) == false) {
            Ex.push_back( -0.5 * ( potential.at(ijk2n(i+1,j,k)) - potential.at(ijk2n(i-1,j,k)) ) / delx );
            Ey.push_back( -0.5 * ( potential.at(ijk2n(i,j+1,k)) - potential.at(ijk2n(i,j-1,k)) ) / dely );
            Ez.push_back( -0.5 * ( potential.at(ijk2n(i,j,k+1)) - potential.at(ijk2n(i,j,k-1)) ) / delz );
        }
        else {
            Ex.push_back(0.0);
            Ey.push_back(0.0);
            Ez.push_back(0.0);
        }
    };
};

void Mesh::writePotential() {
    
    std::cout << "Writing potential to file "  << std::endl;
    std::ofstream pot;
    pot.open(getName().append("_V.out"));

    int n;

    for (int i = 0; i < bins.at(0); ++i) {
        for (int j = 0; j < bins.at(1); ++j) {
            for(int k = 0; k < bins.at(2); ++k) {
                n = ijk2n(i,j,k);
                pot << i << "," << j << "," << k << "," << potential.at(n) << std::endl;
            }
        }
    }

    pot.close();
};

void Mesh::writeE() {

    std::cout << "Writing E field to file "  << std::endl;
    std::ofstream pot;
    pot.open(getName().append("_E.out"));

    int n;

    for (int i = 0; i < bins.at(0); ++i) {
        for (int j = 0; j < bins.at(1); ++j) {
            for(int k = 0; k < bins.at(2); ++k) {
                n = ijk2n(i,j,k);
                pot << i << "," << j << "," << k << "," << Ex.at(n) << "," << Ey.at(n) << "," << Ez.at(n)  << std::endl;
            }
        }
    }

    pot.close();
};


void Mesh::relax() {
    bool  converge   = false;
    int   count      = 0;
    int   wcount     = 0;
    int   size       = potential.size();

    vector <double>  neighbors;
    vector <double>  diff = {1.0};
    vector <double>  oldPot;


    // while the simulation hasn't converged
    while (converge == false) {
        // every 3 steps store current potential
        if ((count+1) % 3 == 0) {
            oldPot = potential;
        }
        clock_t t;
        t = clock();
        // iterate over non-boundary bins
        for (int n = 0; n < potential.size(); ++n) {
            if (onBoundary.at(n) == false and geoBoundary.at(n) == false) {
                // do relaxation on this bin
                neighbors = getNeighbors(n);
                potential.at(n) =  mean(neighbors);
            }
        }
        t = clock() - t;
        // every 3 steps re-evaluate convergence
        if ((count+1) % 3 == 0) {

            converge = testConvergence(oldPot , potential , diff , 0.01 );
            
            std::cout << "<";
            wcount = (count/3 > 18 ? 18  : count);
            for (int i = 0; i < wcount/3; ++i)      {std::cout << "=="; }
            for (int i = 1; i < 20 - wcount/3 - 1; ++i) {std::cout << "  ";  }
            std::cout << "Doing relaxation... step: " << count 
                      << ", normalized L2: " << diff.at(diff.size() - 1 )  
                      << ", time: " << ((float)t)/CLOCKS_PER_SEC  << std::endl;
    
        }
        count++;   
    } 
};

vector <double> Mesh::getNeighbors(int n) {
    vector<int> bins = n2ijk(n);
    
    int i = bins.at(0);
    int j = bins.at(1);
    int k = bins.at(2);

    vector<double> neighbors;
    neighbors.push_back( potential.at( ijk2n(i+1,j  ,k  ) ) );
    neighbors.push_back( potential.at( ijk2n(i+1,j+1,k  ) ) );
    neighbors.push_back( potential.at( ijk2n(i+1,j-1,k  ) ) );
    neighbors.push_back( potential.at( ijk2n(i-1,j  ,k  ) ) );
    neighbors.push_back( potential.at( ijk2n(i-1,j+1,k  ) ) );
    neighbors.push_back( potential.at( ijk2n(i-1,j-1,k  ) ) );
    neighbors.push_back( potential.at( ijk2n(i  ,j+1,k  ) ) );
    neighbors.push_back( potential.at( ijk2n(i  ,j-1,k  ) ) );
    neighbors.push_back( potential.at( ijk2n(i+1,j  ,k+1) ) );
    neighbors.push_back( potential.at( ijk2n(i+1,j+1,k+1) ) );
    neighbors.push_back( potential.at( ijk2n(i+1,j-1,k+1) ) );
    neighbors.push_back( potential.at( ijk2n(i-1,j  ,k+1) ) );
    neighbors.push_back( potential.at( ijk2n(i-1,j+1,k+1) ) );
    neighbors.push_back( potential.at( ijk2n(i-1,j-1,k+1) ) );
    neighbors.push_back( potential.at( ijk2n(i  ,j+1,k+1) ) );
    neighbors.push_back( potential.at( ijk2n(i  ,j-1,k+1) ) );
    neighbors.push_back( potential.at( ijk2n(i+1,j  ,k-1) ) );
    neighbors.push_back( potential.at( ijk2n(i+1,j+1,k-1) ) );
    neighbors.push_back( potential.at( ijk2n(i+1,j-1,k-1) ) );
    neighbors.push_back( potential.at( ijk2n(i-1,j  ,k-1) ) );
    neighbors.push_back( potential.at( ijk2n(i-1,j+1,k-1) ) );
    neighbors.push_back( potential.at( ijk2n(i-1,j-1,k-1) ) );
    neighbors.push_back( potential.at( ijk2n(i  ,j+1,k-1) ) );
    neighbors.push_back( potential.at( ijk2n(i  ,j-1,k-1) ) );
    neighbors.push_back( potential.at( ijk2n(i  ,j  ,k+1) ) );
    neighbors.push_back( potential.at( ijk2n(i  ,j  ,k-1) ) );
 
    return(neighbors);
};
