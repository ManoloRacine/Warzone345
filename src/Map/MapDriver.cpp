// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ---- Written By: Nektarios Zampetoulakis (40211948) ---- 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <string>
#include "Map.h"

using std::cout;
using std::string;

void testLoadMaps() {
    std::cout << "----------------------------------------" << std::endl; 
    std::cout << "Initiating testLoadMaps..." << std::endl;

    std::vector<std::string> map_files {
        "../res/maps/USA.txt",
        "../res/maps/USAError.txt",
        "../res/maps/Europe.txt"
    };

    // Loop over each map file path in the vector
    for (const std::string& filePath : map_files) {
        try {
            // Initialize MapLoader and attempt to load the map
            MapLoader mapLoader;
            Map loadedMap = mapLoader.loadMap(filePath);

            std::cout << "Map loaded successfully from: " << filePath << std::endl;
            std::cout << loadedMap; // Display loaded map data

            // Validate the loaded map
            std::cout << "is Map valid = " << (loadedMap.validate() ? "True" : "False") << std::endl;

        } catch (const std::runtime_error& e) {
            // Catch any errors and print the error message
            std::cout << "Map Format is Invalid for file " << filePath << ": " << e.what() << std::endl;
        }

        std::cout << "----------------------------------------" << std::endl; 
    }
}

