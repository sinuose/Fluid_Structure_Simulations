// This file will contain information of the setup before solving the system

#ifndef UTILS
#define UTILS

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct fluidProperties
{
    float dens;
    float visc;
    std::vector<float>  gravFrc;
};

// -----------------------------------------------------------------------------

struct solidProperties
{
    float mass;

    // damping as [Cxx, Cyy, Cxy]
    std::vector<float> damping;

    // stiffness as [Kxx, Kyy, Kxy];
    std::vector<float> stiffness;

    // direction of movement
    // written as [x ; y]
    std::vector<float> dom;
    std::vector<float> gravity;
};

// -----------------------------------------------------------------------------

struct solverProperties
{
    int nLIterMin;
    int nLIterMax;
    float dt;
    int maxSteps;
    float rhoinfty;
    float nLTol;
    float outFreq;
    int intgOutFreq;
};

std::vector<float> parseVector(const std::string& str);
void loadFSIProperties(const std::string& filename, solverProperties &solver, fluidProperties &fluid, solidProperties &solid);
void printSettings(solverProperties &solver, fluidProperties &fluid, solidProperties &solid);

#endif
