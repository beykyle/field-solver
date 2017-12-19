#include "Simulation.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */


// functions
bool Simulation::readInput(std::string XML_FILE_PATH , vector<int> &bins, vector<double> &boundaryPotentials , 
        vector <bool> &holdPotentials , vector <double> &cavityDimensions , std::string &shape , 
        std::string &name , std::string &method) {
/*
*   Parse input file and determine simulation parameters
*/

    std::cout << "Now parsing " << XML_FILE_PATH << std::endl; 

    std::string tmpDim;
    std::string tmpBin;
    std::string tmpPot;

    // load document
    pugi::xml_document doc;
   
    pugi::xml_parse_result result =  doc.load_file(XML_FILE_PATH.c_str());
    pugi::xml_node root           = doc.document_element();
   
    // parse cavity 
    for (pugi::xml_node cavity: root.children("cavity")) {
        for (pugi::xml_attribute attr: cavity.attributes()) {
            if (std::string(attr.name()).compare("Type") != 0) {
                shape = attr.value();
            }
            if (std::string(attr.name()).compare("Name") != 0) {
                name = attr.value();
            }
        }
        for (pugi::xml_node child: cavity.children("dimensions")) {
            tmpDim = child.child_value();
        }
        for (pugi::xml_node child: cavity.children("boundaryPotentials")) {
            tmpPot = child.child_value();
        }
    }      
          
    // parse mesh
    for (pugi::xml_node mesh: root.children("mesh")) {
        for (pugi::xml_node child: mesh.children("bins")) {
            tmpBin  = child.child_value();
        }
        for (pugi::xml_node child: mesh.children("method")) {
            method  = child.value();
        }
    }
   
    std::stringstream ss(tmpBin);
    while( ss.good() ) {
        std::string substr;
        getline(ss , substr , ',');
        bins.push_back(stoi(substr));
    }
   
    std::stringstream os(tmpDim);
    while( os.good() ) {
        std::string substr;
        getline(os , substr , ',');
        cavityDimensions.push_back(stod(substr));
    }
   
    std::stringstream ls(tmpPot);
    while( ls.good() ) {
        std::string substr;
        getline(ls , substr , ',');
        boundaryPotentials.push_back(stod(substr));
    }

    holdPotentials.assign(boundaryPotentials.size() , true); //TODO fix this 
   
    // TODO check inputs
    return(true);

}


bool Simulation::setupFromInputFiles(vector <std::string> paths ) {
/*
*   Construct Cavity and Mesh Objects and add them to Simulation
*/
 
    int counter = 1;

    // iterate over input files
    for (std::string XML_FILE_PATH : paths) {
        
        // declare mesh and cavity pointers
        Cavity_Ptr myCavityPtr;
        Mesh_Ptr   myMeshPtr;

        // containers for inputs from file
        vector <int>    bins;
        vector <double> binWidths;
        vector <double> boundaryPotentials;
        vector <bool>   holdPotentials;
        vector <double> cavityDimensions;
        
        std::string shape;
        std::string name;
        std::string method;

        bool goodRead;
        
        // read from input file
        goodRead = readInput(XML_FILE_PATH , bins , boundaryPotentials , holdPotentials , 
                cavityDimensions , shape , name , method);

        if (goodRead == false) {
            std::cerr << "Trouble with input file " << counter+1 << std::endl;
            return(false);
        }
        else {
            
            // calculate bin Widths
            binWidths.push_back(cavityDimensions.at(0) / double(bins.at(0)) );
            binWidths.push_back(cavityDimensions.at(1) / double(bins.at(1)) );
            binWidths.push_back(cavityDimensions.at(2) / double(bins.at(2)) );

            if (shape.compare(std::string("Rectangular")) != 0) {
        
            RectangularCavity myCavity( name , cavityDimensions , boundaryPotentials , holdPotentials);
        
            // make a pointer to the cavity, upcasting cavity type
            Cavity_Ptr myCavityPtr = std::make_shared<RectangularCavity>(myCavity);
        
            }
            else {
                std::cerr << "Error! cavity type not recognized. quitting." << std::endl;
                return(false);
            }

            // add cavity to the simulation
            cavitySet.push_back(myCavityPtr);

            // construct and set Mesh
            Mesh mesh(myCavityPtr, bins , binWidths);

            // make a pointer to the mesh
            myMeshPtr = std::make_shared<Mesh>(mesh);
        
            // add mesh to the simulation
            meshSet.push_back(myMeshPtr);
    
            // specify solve method for this mesh
            methodSet.push_back(method);
        }

        ++counter;
    }

};



void Simulation::run() {

    clock_t t;

    for(int i = 0; i < meshSet.size(); ++i) {
        
        std::cout << std::endl << " Beginning solve for Cavity " << i + 1 << std::endl;
        
        // run and time field solve
        t = clock();
        meshSet.at(i)->solve(methodSet.at(i));
        t = clock() - t;
        
        std::cout<<"Solved cavity " << i +1 << " in " << ((float)t)/CLOCKS_PER_SEC << " seconds" << std::endl;
    
        // calculate E
        meshSet.at(i)->calculateE();

        // write output
        meshSet.at(i)->writeE();
        meshSet.at(i)->writePotential();
    }
};
