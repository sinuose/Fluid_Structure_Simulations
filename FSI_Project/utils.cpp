// Files


// -----------------------------------------------------------------------------
//	Containers for fluid, structure, and boundary properties. 
//  
// Idea is to take these variables, save them to memory as when to read them from
// the file, then use these chunks of memory as addresses for all remaining 
// calculations.
// -----------------------------------------------------------------------------
#include "hdr/utils.h"
	
// -----------------------------------------------------------------------------

// Function to parse a string into a vector of floats
std::vector<float> parseVector(const std::string& str) {
    std::vector<float> vec;
    std::stringstream ss(str);
    float value;
    while (ss >> value) {
        vec.push_back(value);
        // Skip commas or other delimiters if necessary
        if (ss.peek() == ',' || ss.peek() == ' ') {
            ss.ignore();
        }
    }
    return vec;
}

void loadFSIProperties(const std::string& filename, solverProperties& solver, fluidProperties& fluid, solidProperties& solid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        // Remove comments and trim whitespace
        line = line.substr(0, line.find("//"));
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string key;
        ss >> key;

        // Solver Properties
        if (key == "nLIterMin") ss >> solver.nLIterMin;
        else if (key == "nLIterMax") ss >> solver.nLIterMax;
        else if (key == "dt") ss >> solver.dt;
        else if (key == "maxSteps") ss >> solver.maxSteps;
        else if (key == "rhoinfty") ss >> solver.rhoinfty;
        else if (key == "nLTol") ss >> solver.nLTol;
        else if (key == "outFreq") ss >> solver.outFreq;
        else if (key == "intgOutFreq") ss >> solver.intgOutFreq;

        // Fluid Properties
        else if (key == "dens") ss >> fluid.dens;
        else if (key == "visc") ss >> fluid.visc;
        else if (key == "gravFrc") {
            std::string vecStr;
            std::getline(ss, vecStr);
            fluid.gravFrc = parseVector(vecStr);
        }

        // Solid Properties
        else if (key == "mass") ss >> solid.mass;
        else if (key == "damping") {
            std::string vecStr;
            std::getline(ss, vecStr);
            solid.damping = parseVector(vecStr);
        }
        else if (key == "stiffness") {
            std::string vecStr;
            std::getline(ss, vecStr);
            solid.stiffness = parseVector(vecStr);
        }
        else if (key == "dom") {
            std::string vecStr;
            std::getline(ss, vecStr);
            solid.dom = parseVector(vecStr);
        }
        else if (key == "gravity") {
            std::string vecStr;
            std::getline(ss, vecStr);
            solid.gravity = parseVector(vecStr);
        }
        else {
            std::cerr << "Warning: Unknown key '" << key << "' in input file.\n";
        }
    }
}

// -----------------------------------------------------------------------------

void printSettings(solverProperties& solver, fluidProperties& fluid, solidProperties& solid)
{
    // Solver
    std::cout << "\nSolver Settings:\n";
    std::cout << "nLIterMin: " << solver.nLIterMin << "\n";
    std::cout << "nLIterMax: " << solver.nLIterMax << "\n";
    std::cout << "dt: " << solver.dt << "\n";
    std::cout << "maxSteps: " << solver.maxSteps << "\n";
    std::cout << "rhoinfty: " << solver.rhoinfty << "\n";
    std::cout << "nLTol: " << solver.nLTol << "\n";
    std::cout << "outFreq: " << solver.outFreq << "\n";
    std::cout << "intgOutFreq: " << solver.intgOutFreq << "\n";
    // Fluid
    std::cout << "\nFluid Properties:\n";
    std::cout << "dens: " << fluid.dens << "\n";
    std::cout << "visc: " << fluid.visc << "\n";
    std::cout << "gravFrc: [";
    for (double val : fluid.gravFrc) std::cout << val << " ";
    std::cout << "]\n";
    // solid
    std::cout << "\nSolid Properties:\n";
    std::cout << "mass: " << solid.mass << "\n";
    std::cout << "damping: [";
    for (double val : solid.damping) std::cout << val << " ";
    std::cout << "]\n";
    std::cout << "stiffness: [";
    for (double val : solid.stiffness) std::cout << val << " ";
    std::cout << "]\n";
    std::cout << "dom: [";
    for (int val : solid.dom) std::cout << val << " ";
    std::cout << "]\n";
    std::cout << "gravity: [";
    for (int val : solid.gravity) std::cout << val << " ";
    std::cout << "]\n";
}