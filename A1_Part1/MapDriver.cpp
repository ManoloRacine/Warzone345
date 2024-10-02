
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ---- Written By: Nektarios Zampetoulakis (40211948) ---- 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <string>
#include "Map.h"

using std::cout;
using std::string;

int main() {

    cout << "Initiating Map Driver..." << endl;

    string filePath = "USAERROR.txt";

    MapLoader mapLoader;

    try {
        // Load the map using the MapLoader
        Map loadedMap = mapLoader.loadMap(filePath);


        //loadedMap.displayInfo();

        cout << "Map loaded succesfully...";

       bool isConnected = loadedMap.mapFullyConnected(loadedMap.mapData);
        if (!isConnected) { cout << "Map is not connected"; } else { cout << "Map Connected!"; };

        std::cout << "\n SKIPPING LINE";
        bool territoryPartOfContinent = loadedMap.validateUniqueness(loadedMap.mapData,loadedMap.Continents);
        if (territoryPartOfContinent) { cout << "All Territories unique"; } else { cout << "A territory was part of multiple continents"; };
        std::cout << "\n SKIPPING LINE AGAIN";

    } catch (const std::runtime_error& e) {
        cout << "Error: " << e.what() << endl;

    }

    return 0;
}
