// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ---- Written By: Nektarios Zampetoulakis (40211948) ---- 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <string>
#include "map.h"  // Include your map header file

using namespace std;

int main() {

    string filePath = "..\A1_Part1\maps\Europe.txt";

    MapLoader mapLoader;
    try {
        // Load the map using the MapLoader
        Map loadedMap = mapLoader.loadMap(filePath);

        // Display map information
        cout << "Map Author: " << loadedMap.getAuthor() << endl;
        cout << "Image Path: " << loadedMap.getImgPath() << endl;
        cout << "Wrap: " << (loadedMap.getWrap() ? "Yes" : "No") << endl;
        cout << "Scroll Type: ";
        switch (loadedMap.getScrollType()) {
            case Map::Scroll::horizontal:
                cout << "Horizontal" << endl;
                break;
            case Map::Scroll::vertical:
                cout << "Vertical" << endl;
                break;
            case Map::Scroll::none:
                cout << "None" << endl;
                break;
        }

        // Display continents and their territories
        cout << "\nContinents and Territories:\n";
        for (const auto& continent : loadedMap.Continents) {
            continent->displayInfo();
            for (const auto& territory : continent->territories) {
                territory->displayInfo();
            }
            cout << endl;
        }

    } catch (const std::runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
