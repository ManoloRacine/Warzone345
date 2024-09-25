// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ---- Written By: Nektarios Zampetoulakis (40211948) ---- 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include "Map.h"

using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::vector;
using std::unordered_map;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ CONTINENT ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // Construcotr
    Continent::Continent(const std::string& name, int bonus)
        : name(name), bonus(bonus) {}

    // Setters and Getters

       void Continent::setName(const std::string& n) {
        name = n;
    }

    std::string Continent::getName() const {
        return name;
    }

    void Continent::setBonus(int b) {
        bonus = b;
    }

    int Continent::getBonus() const {
        return bonus;
    }

    void Continent::addTerritory(Territory* territory) {
        if (territory != nullptr) {  // Ensure the territory pointer is valid
            territories.push_back(territory);
        }
    }

    void Continent::displayInfo() const {
        std::cout << " Continent : " << name << ", Bonus : " << bonus << std::endl;
    }


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ TERRITORY ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // Constructor
    Territory::Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent, int owner, int armies)
        : name(name), coordinates(coordinates), continent(continent), owner(owner), armies(armies) {}

    // Overloaded constructor with name, coordinates, and continent
    Territory::Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent) 
        : Territory(name, coordinates, continent, 0, 0) {} 

    // Setters and Getters
    void Territory::setName(const std::string& name) {
        this->name = name;
    }

    std::string Territory::getName() const {
        return name;
    }

    void Territory::setCoordinates(const std::pair<int, int>& c) {
        coordinates = c;
    }

    std::pair<int, int> Territory::getCoordinates() const {
        return coordinates;
    }

    void Territory::setContinent(Continent* con) {  
        continent = con;
    }

    Continent* Territory::getContinent() const {  
        return continent;
    }

    void Territory::addConnectedTerritory(Territory* territory) {  
        connectedTerritories.push_back(territory);
    }

    void Territory::setOwner(int newOwner) {
        owner = newOwner;  
    }

    int Territory::getOwner() const {
        return owner;  
    }

    void Territory::setArmies(int numArmies) {
        armies = numArmies;
    }

    int Territory::getArmies() const {
        return armies;
    }

    // Method to display territory information
    void Territory::displayInfo() const {
        std::cout << "Territory: " << name << std::endl;
        std::cout << "Coordinates: (" << coordinates.first << ", " << coordinates.second << ")" << std::endl;
        if (continent) {
            std::cout << "Continent: " << continent->getName() << std::endl;  // Access continent name
        } else {
            std::cout << "Continent: None" << std::endl;  // Handle case where continent is not set
        }
        std::cout << "Owner: " << owner << std::endl; 
        std::cout << "Armies: " << armies << std::endl;
        std::cout << "Connected Territories: ";
        for (const auto& territory : connectedTerritories) {
            std::cout << territory->getName() << " ";  // Display territory names
        }
        std::cout << std::endl;
    }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// --------------------  MAP ------------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// Destructor
 Map::~Map() {
        for (auto continent : Continents) {
            delete continent;  // Free allocated memory for continents
        }
        for (auto pair : mapData) {
            delete pair.second;  // Free allocated memory for territories
        }
    }


    // Setters
    void Map::setAuthor(const std::string& author) {
        this->author = author;
    }

    void Map::setWarn(bool warn) {
        this->warn = warn;
    }

    void Map::setImgPath(const std::string& imgPath) {
        this->imgPath = imgPath;
    }

    void Map::setWrap(bool wrap) {
        this->wrap = wrap;
    }

    void Map::setScrollType(Scroll scrollType) {
        this->scrollType = scrollType;
    }

    // Getters
    std::string Map::getAuthor() const {
        return author;
    }

    bool Map::getWarn() const {
        return warn;
    }

    std::string Map::getImgPath() const {
        return imgPath;
    }

    bool Map::getWrap() const {
        return wrap;
    }

    Map::Scroll Map::getScrollType() const {
        return scrollType;
    }

     void Map::addContinent(Continent* continent) {
        if (continent != nullptr) { 
            Continents.push_back(continent);
        }
    }

    void Map::addTerritory(const std::string& name, Territory* territory) {
        if (territory != nullptr) { // Ensure the territory pointer is valid
            mapData[name] = territory; // Add the territory to the hashmap with its name as the key
        }
    }

    void Map::displayInfo() const{
    std::cout << "Map Author: " << getAuthor() << std::endl;
    std::cout << "Image Path: " << getImgPath() << std::endl;
    std::cout << "Wrap: " << (getWrap() ? "Yes" : "No") << std::endl;
    std::cout << "Scroll Type: ";
    switch (getScrollType()) {
        case Map::Scroll::horizontal:
            std::cout << "Horizontal" << std::endl;
            break;
        case Map::Scroll::vertical:
            std::cout << "Vertical" << std::endl;
            break;
        case Map::Scroll::none:
            std::cout << "None" << std::endl;
            break;
    }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ MAP LOADER --------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



    MapLoader::Connector::Connector(Territory* t) : territory(t) {}



    void MapLoader::Connector::addConnectedTerritory(const std::string& connTerritory) {
        connectedT.push_back(connTerritory);
        }

    void MapLoader::Connector::addConnector(Territory* newTerritory, const std::string& connectedTerritoriesStr) {
        Connector newConnector(newTerritory);
        }


    // Load map
    Map MapLoader::loadMap(const std::string& path) {
        Map map;
        std::ifstream inputFile(path);
        
        if (!inputFile.is_open()) {
            throw std::runtime_error("Could not open file: " + path);
        }

        std::string line;
        std::string section;
        std::vector<Connector> connectors;  // Vector to store connections
        std::unordered_map<std::string, Territory*> territoryMap; // Map to associate territory names with pointers

        while (std::getline(inputFile, line)) {
            // Trim whitespace
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);

            // Skip empty lines and comments
            if (line.empty() || line[0] == ';') continue;

            // Check for section headers
            if (line[0] == '[') {
                section = line.substr(1, line.find(']') - 1);
                continue;
            }
        
            // Parse the contents based on the section
            if (section == "Map") {
                std::istringstream iss(line);
                std::string key, value;

                // Parse key-value pairs for Map settings
                if (line.find('=') != std::string::npos && std::getline(iss, key, '=') && std::getline(iss, value)) {
                    // Remove potential leading/trailing spaces
                    key.erase(0, key.find_first_not_of(" \t"));
                    value.erase(0, value.find_first_not_of(" \t"));

                    // Map key to setters in MapSettings
                    if (key == "author") {
                        map.setAuthor(value);
                    } else if (key == "warn") {
                        map.setWarn(value == "yes");
                    } else if (key == "image") {
                        map.setImgPath(value);
                    } else if (key == "wrap") {
                        map.setWrap(value == "yes");
                    } else if (key == "scroll") {
                        if (value == "horizontal") {
                            map.setScrollType(Map::Scroll::horizontal);
                        } else if (value == "vertical") {
                            map.setScrollType(Map::Scroll::vertical);
                        } else {
                            map.setScrollType(Map::Scroll::none);
                        }
                    }
                }
            } else if (section == "Continents") {
                std::istringstream iss(line);
                std::string name, bonusStr;

                // Parse continent data
                if (line.find('=') != std::string::npos && std::getline(iss, name, '=') && std::getline(iss, bonusStr)) {
                    // Trim whitespace from name and bonus
                    name.erase(0, name.find_first_not_of(" \t"));
                    bonusStr.erase(0, bonusStr.find_first_not_of(" \t"));

                    // Create a new Continent object
                    int bonus = std::stoi(bonusStr);  // Convert the value to an integer
                    Continent* newContinent = new Continent(name, bonus);
                    map.addContinent(newContinent); 
                }
            } else if (section == "Territories") {
                std::istringstream iss(line);
                std::string name, x, y, continentName;

                // Read the territory line and extract data
                if (std::getline(iss, name, ',') && std::getline(iss, x, ',') &&
                    std::getline(iss, y, ',') && std::getline(iss, continentName)) {
                    
                    // Trim whitespace
                    name.erase(0, name.find_first_not_of(" \t"));
                    continentName.erase(0, continentName.find_first_not_of(" \t"));
                    x.erase(0, x.find_first_not_of(" \t"));
                    y.erase(0, y.find_first_not_of(" \t"));

                    // Convert coordinates to integers
                    int coordX = std::stoi(x);
                    int coordY = std::stoi(y);

                    // Find the corresponding continent
                    Continent* continent = nullptr;
                    for (auto* cont : map.Continents) {
                        if (cont->getName() == continentName) {
                            continent = cont;
                            break;
                        }
                    }

                    // Throw runtime error if continent is not found
                    if (!continent) {
                        throw std::runtime_error("Error: Continent '" + continentName + "' does not exist.");
                    }

                    // Create the Territory object
                    Territory* newTerritory = new Territory(name, {coordX, coordY}, continent);
                    map.addTerritory(name,newTerritory);

                    Connector newConnector(newTerritory);

                    // Now read the remaining connected territories
                    std::string connTerritory;
                    while (std::getline(iss, connTerritory, ',')) {
                        // Trim whitespace
                        connTerritory.erase(0, connTerritory.find_first_not_of(" \t"));
                        if (!connTerritory.empty()) {
                            newConnector.addConnectedTerritory(connTerritory); // Store connected territories
                        }
                    }
                    connectors.push_back(newConnector); 
                }
            }
        }

        // Set up the connections based on the stored connectors
            for (const auto& connector : connectors) {
                Territory* territory = connector.territory;
                for (const auto& connName : connector.connectedT) {
                    auto it = territoryMap.find(connName);
                    if (it != territoryMap.end()) {
                        territory->addConnectedTerritory(it->second); 
                    }
                }
            }

         inputFile.close(); 
         return map; 
    }






