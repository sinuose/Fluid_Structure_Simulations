// -----------------------------------------------------------------------------
//	MAIN
//  
//	MARTIN JASINSKI
//  FEB/20/2025
// 
//  FLUID - STRUCTURE SOLVER USING FINITE ELEMENT ANALYSIS
// 
// 
// -----------------------------------------------------------------------------

#include "hdr/mj_Solver.h"

// main
int main()
{
	// -----------------------------------------------------------------------------
	// Start Fluid Settings
	// -----------------------------------------------------------------------------

	printf("Program Start.\n");
	// Edit to your directory;
	std::string settingsPath = "C:/Users/mj/Documents/GitHub/Fluid_Structure_Simulations/FSI_Project/settings.txt";

	// initialize strucutres for settings
	fluidProperties fluidSettings;
	solverProperties solverSettings;
	solidProperties solidSettings;

	// load settings from settings.txt
	loadFSIProperties(settingsPath, solverSettings, fluidSettings, solidSettings);
	// Output settings
	printSettings(solverSettings, fluidSettings, solidSettings);



	return 0;
}
