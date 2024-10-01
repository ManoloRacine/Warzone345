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
 //Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent);
    try {
        Continent* cont = new Continent("adasd", 121);
        Territory* ptr = new Territory("Bob Island", {1,2}, cont);
        // Load the map using the MapLoader
        Map loadedMap = mapLoader.loadMap(filePath);
        unordered_map<std::string, Territory*> mapData = {{"Bob Island", ptr}};


        
        loadedMap.displayInfo();
        std::cout <<"111\n";
        std::cout <<"222\n";
        std::cout <<"333\n";
      // loadedMap.mapFullyConnected(mapData);
        std::cout <<"HOWDY THERE";
        


    } catch (const std::runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
