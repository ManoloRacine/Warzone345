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

    string filePath = "../res/maps/USAError.txt";

    MapLoader mapLoader;

    try {
        // Load the map using the MapLoader
        Map loadedMap = mapLoader.loadMap(filePath);


        //loadedMap.displayInfo();

        cout << "Map loaded succesfully...";

        bool isConnected = loadedMap.mapFullyConnected(loadedMap.mapData);
        if (!isConnected) { cout << "Map is not connected"; } else { cout << "Map Connected!"; };



    } catch (const std::runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
