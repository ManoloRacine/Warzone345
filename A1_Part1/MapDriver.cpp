// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ---- Written By: Nektarios Zampetoulakis (40211948) ---- 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <string>
#include "Map.h"

using std::cout;
using std::string;

int main() {

    cout << "Docker Sucks" << endl;

//     Continent europe("Europe", 5);

//     europe.displayInfo();

//     //Creating Territory objects
//    Territory* ireland = new Territory("Ireland", {81, 320}, &europe);
//     Territory* northernIreland = new Territory("Northern Ireland", {90, 300}, &europe);

//     // Connecting territories
//     ireland->addConnectedTerritory(northernIreland);
//     northernIreland->addConnectedTerritory(ireland);

//     // Setting properties for Ireland
//     ireland->setOwner(1); // Owner ID 
//     ireland->setArmies(50); // Armies stationed in Ireland

//     //Display information
//    ireland->displayInfo();
//     northernIreland->displayInfo();

//     //Clean up
//     delete ireland;
//     delete northernIreland;


    string filePath = "./maps/USA.txt";

    MapLoader mapLoader;

    try {
        // Load the map using the MapLoader
        Map loadedMap = mapLoader.loadMap(filePath);


        loadedMap.displayInfo();


    } catch (const std::runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
