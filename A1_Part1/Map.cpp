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
#include <numeric>
#include <unordered_set>
#include "Map.h"

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ CONTINENT ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Construcotr
Continent::Continent(const std::string &name, int bonus)
    : name(name), bonus(bonus) {}

// Setters and Getters

void Continent::setName(const std::string &n) {
    name = n;
}

std::string Continent::getName() const
{
    return name;
}

void Continent::setBonus(int b)
{
    bonus = b;
}

int Continent::getBonus() const
{
    return bonus;
}

void Continent::addTerritory(Territory *territory)
{
    if (territory != nullptr)
    {
        territories.push_back(territory);
    }
}

void Continent::displayInfo() const
{
    std::cout << "Continent : " << name << ", Bonus : " << bonus << std::endl;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ TERRITORY ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Constructor
Territory::Territory(const std::string &name, const std::pair<int, int> &coordinates, Continent *continent, int owner, int armies)
    : name(name), coordinates(coordinates), continent(continent), owner(owner), armies(armies) {}

// Overloaded constructor with name, coordinates, and continent
Territory::Territory(const std::string &name, const std::pair<int, int> &coordinates, Continent *continent)
    : Territory(name, coordinates, continent, 0, 0) {}

// Setters and Getters
void Territory::setName(const std::string &name)
{
    this->name = name;
}

std::string Territory::getName() const
{
    return name;
}

void Territory::setCoordinates(const std::pair<int, int> &c)
{
    coordinates = c;
}

std::pair<int, int> Territory::getCoordinates() const
{
    return coordinates;
}

void Territory::setContinent(Continent *con)
{
    continent = con;
}

Continent *Territory::getContinent() const
{
    return continent;
}

void Territory::addConnectedTerritory(Territory *territory)
{
    connectedTerritories.push_back(territory);
}

void Territory::setOwner(int newOwner)
{
    owner = newOwner;
}

int Territory::getOwner() const
{
    return owner;
}

void Territory::setArmies(int numArmies)
{
    armies = numArmies;
}

int Territory::getArmies() const
{
    return armies;
}

const std::vector<Territory *> &Territory::getConnectedTerritories() const
{
    return connectedTerritories;
}

void Territory::displayInfo() const
{
    std::cout << name << ","
              << coordinates.first << ","
              << coordinates.second << ","
              << (continent ? continent->getName() : "None") << ","
              << owner << ","
              << armies << ","
              << std::accumulate(connectedTerritories.begin(), connectedTerritories.end(), std::string{},
                                 [](const std::string &a, const Territory *b)
                                 {
                                     return a + (a.length() > 0 ? "," : "") + b->getName();
                                 })
              << std::endl;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// --------------------  MAP ------------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Destructor
Map::~Map()
{
    for (auto continent : Continents)
    {
        delete continent; // Free allocated memory for continents
    }
    for (auto pair : mapData)
    {
        delete pair.second; // Free allocated memory for territories
    }
}

// Setters
void Map::setAuthor(const std::string &author)
{
    this->author = author;
}

void Map::setWarn(bool warn)
{
    this->warn = warn;
}

void Map::setImgPath(const std::string &imgPath)
{
    this->imgPath = imgPath;
}

void Map::setWrap(bool wrap)
{
    this->wrap = wrap;
}

void Map::setScrollType(Scroll scrollType)
{
    this->scrollType = scrollType;
}

void Map::setNumTerritories(int numTerritories)
{
    this->numTerritories = numTerritories;
}

// Getters
std::string Map::getAuthor() const
{
    return author;
}

bool Map::getWarn() const
{
    return warn;
}

std::string Map::getImgPath() const
{
    return imgPath;
}

bool Map::getWrap() const
{
    return wrap;
}

Map::Scroll Map::getScrollType() const
{
    return scrollType;
}

unordered_map<std::string, Territory*> Map::getMapData() const {
    return mapData;
}

void Map::addContinent(Continent *continent)
{
    if (continent != nullptr)
    {
        Continents.push_back(continent);
    }
}

void Map::addTerritory(const std::string &name, Territory *territory)
{
    if (territory != nullptr)
    {                              // Ensure the territory pointer is valid
        mapData[name] = territory; // Add the territory to the hashmap with its name as the key
    }
}

// Get territory by name
Territory *Map::getTerritoryPtr(const std::string &name)
{
    auto it = mapData.find(name);
    if (it != mapData.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void Map::displayInfo() const
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~ MAP DATA ~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Map Author: " << getAuthor() << std::endl;
    std::cout << "Image Path: " << getImgPath() << std::endl;
    std::cout << "Wrap: " << (getWrap() ? "Yes" : "No") << std::endl;
    std::cout << "Scroll Type: ";

    switch (getScrollType())
    {
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

    // Display Continents and their Territories
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "\nContinents and Territories:" << std::endl;

    for (const auto &continent : Continents)
    {
        continent->displayInfo();

        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Territories in " << continent->getName() << ":" << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

        for (const auto &pair : mapData)
        {
            if (pair.second->getContinent() == continent)
            {
                pair.second->displayInfo();
            }
        }
        std::cout << std::endl;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ MAP LOADER --------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Load map
Map MapLoader::loadMap(const std::string &path)
{
    Map map;
    std::ifstream inputFile(path);
    std::unordered_map<Territory *, std::vector<std::string>> associationsMap;

    if (!inputFile.is_open())
    {
        throw std::runtime_error("Could not open file: " + path);
    }

    std::string line;
    std::string section;

    while (std::getline(inputFile, line))
    {
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // Skip empty lines and comments
        if (line.empty() || line[0] == ';')
            continue;

        // Check for section headers
        if (line[0] == '[')
        {
            section = line.substr(1, line.find(']') - 1);
            continue;
        }

        // Parse the contents based on the section
        if (section == "Map")
        {
            std::istringstream iss(line);
            std::string key, value;

            try
            {
                // Parse key-value pairs for Map settings
                if (line.find('=') != std::string::npos && std::getline(iss, key, '=') && std::getline(iss, value))
                {

                    // Remove potential leading/trailing spaces
                    key.erase(0, key.find_first_not_of(" \t"));
                    value.erase(0, value.find_first_not_of(" \t"));
                    if (key == "author")
                    {
                        if (!value.empty())
                        {
                            map.setAuthor(value);
                        }
                        else
                        {
                            throw std::runtime_error("Missing value for 'author'.");
                        }
                    }
                    else if (key == "warn")
                    {
                        if (value == "yes" || value == "no")
                        {
                            map.setWarn(value == "yes");
                        }
                        else
                        {
                            throw std::runtime_error("Invalid value for 'warn'. Expected 'yes' or 'no'.");
                        }
                    }
                    else if (key == "image")
                    {
                        if (!value.empty())
                        {
                            map.setImgPath(value);
                        }
                        else
                        {
                            throw std::runtime_error("Missing value for 'image'.");
                        }
                    }
                    else if (key == "wrap")
                    {
                        if (value == "yes" || value == "no")
                        {
                            map.setWrap(value == "yes");
                        }
                        else
                        {
                            throw std::runtime_error("Invalid value for 'wrap'. Expected 'yes' or 'no'.");
                        }
                    }
                    else if (key == "scroll")
                    {
                        if (value == "horizontal")
                        {
                            map.setScrollType(Map::Scroll::horizontal);
                        }
                        else if (value == "vertical")
                        {
                            map.setScrollType(Map::Scroll::vertical);
                        }
                        else if (value == "none")
                        {
                            map.setScrollType(Map::Scroll::none);
                        }
                        else
                        {
                            throw std::runtime_error("Invalid value for 'scroll'. Expected 'horizontal', 'vertical', or 'none'.");
                        }
                    }
                    else
                    {
                        throw std::runtime_error("Unknown key: '" + key + "'");
                    }
                }
                else
                {
                    throw std::runtime_error("Invalid line format. Expected key=value.");
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error processing line in Map section: " << e.what() << std::endl;
            }
        }
        else if (section == "Continents")
        {
            std::istringstream iss(line);
            std::string name, bonusStr;

            try
            {
                // Parse continent data
                if (line.find('=') != std::string::npos && std::getline(iss, name, '=') && std::getline(iss, bonusStr))
                {
                    // Trim whitespace from name and bonus
                    name.erase(0, name.find_first_not_of(" \t"));
                    bonusStr.erase(0, bonusStr.find_first_not_of(" \t"));

                    // Validate that name is not empty
                    if (name.empty())
                    {
                        throw std::runtime_error("Continent name is missing.");
                    }

                    // Validate and convert bonus value
                    int bonus;
                    try
                    {
                        bonus = std::stoi(bonusStr); // Convert the value to an integer
                    }
                    catch (const std::invalid_argument &)
                    {
                        throw std::runtime_error("Invalid bonus value for continent '" + name + "'. Expected an integer.");
                    }
                    catch (const std::out_of_range &)
                    {
                        throw std::runtime_error("Bonus value for continent '" + name + "' is out of range.");
                    }

                    // Create a new Continent object and add it to the map
                    Continent *newContinent = new Continent(name, bonus);
                    map.addContinent(newContinent);
                }
                else
                {
                    throw std::runtime_error("Invalid format for continent data. Expected 'name=bonus'.");
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error processing line in Continents section: " << e.what() << std::endl;
            }
        }
        else if (section == "Territories")
        {
            std::istringstream iss(line);
            std::string name, x, y, continentName;

            try
            {
                // Read the territory line and extract data
                if (std::getline(iss, name, ',') && std::getline(iss, x, ',') &&
                    std::getline(iss, y, ',') && std::getline(iss, continentName, ','))
                {

                    // Trim whitespace
                    name.erase(0, name.find_first_not_of(" \t"));
                    continentName.erase(0, continentName.find_first_not_of(" \t"));
                    x.erase(0, x.find_first_not_of(" \t"));
                    y.erase(0, y.find_first_not_of(" \t"));

                    // Validate the territory name and continent name
                    if (name.empty())
                    {
                        throw std::runtime_error("Territory name is missing.");
                    }
                    if (continentName.empty())
                    {
                        throw std::runtime_error("Continent name is missing for territory '" + name + "'.");
                    }

                    // Convert coordinates to integers
                    int coordX, coordY;
                    try
                    {
                        coordX = std::stoi(x);
                        coordY = std::stoi(y);
                    }
                    catch (const std::invalid_argument &)
                    {
                        throw std::runtime_error("Invalid coordinates for territory '" + name + "'. Expected integers.");
                    }
                    catch (const std::out_of_range &)
                    {
                        throw std::runtime_error("Coordinates for territory '" + name + "' are out of range.");
                    }

                    // Check if coordinates are within the allowed range (0-1000)
                    if (coordX < 0 || coordX > 1000 || coordY < 0 || coordY > 1000)
                    {
                        throw std::runtime_error("Coordinates for territory '" + name + "' are out of bounds. "
                                                                                        "Expected values between 0 and 1000.");
                    }

                    // Find the corresponding continent
                    Continent *continent = nullptr;
                    for (auto *cont : map.Continents)
                    {
                        if (cont->getName() == continentName)
                        {
                            continent = cont;
                            break;
                        }
                    }

                    // Throw runtime error if continent is not found
                    if (!continent)
                    {
                        throw std::runtime_error("Error: Continent '" + continentName + "' does not exist.");
                    }

                    // Create the Territory object
                    Territory *newTerritory = new Territory(name, {coordX, coordY}, continent);
                    map.addTerritory(name, newTerritory);

                    std::vector<std::string> connectedList;

                    // Read the remaining connected territories
                    std::string connTerritory;
                    while (std::getline(iss, connTerritory, ','))
                    {
                        // Trim whitespace
                        connTerritory.erase(0, connTerritory.find_first_not_of(" \t"));
                        if (!connTerritory.empty())
                        {
                            connectedList.push_back(connTerritory);
                        }
                    }

                    // Insert the territory and its connections into the associations map
                    associationsMap.insert({newTerritory, connectedList});
                }
                else
                {
                    throw std::runtime_error("Invalid format for territory data. Expected 'name,x,y,continent'.");
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error processing line in Territories section: " << e.what() << std::endl;
            }
        }
        else
        {
            throw std::runtime_error("Invalid Header Name.");
        }
    }
    inputFile.close();

    // Set up the connections
    for (const auto &[currentT, connectedTerritoryNames] : associationsMap)
    {
        for (const auto &territoryName : connectedTerritoryNames)
        {
            // Get the pointer to the territory by its name
            Territory *territoryPtr = map.getTerritoryPtr(territoryName);

            // Check if the territory exists before adding it as a connection
            if (territoryPtr)
            {
                currentT->addConnectedTerritory(territoryPtr);
            }
            else
            {
                std::cerr << "Territory '" << territoryName << "' not found in the map." << std::endl;
            }
        }
    }
    return map;
}
//Map Validation Written By Griffin Sin-Chan (40278049)
//Depth first search takes in a starting node and a has a list tracking the visited nodes
void DFS(Territory *territory, std::unordered_set<Territory*>& visitedNodes) {
    //track the current node that is being visited
    visitedNodes.insert(territory);
    
    //From the current node check the vector of adjacent territories
    for (Territory* adjacent : territory->getConnectedTerritories()) {
        
        //This is error checking for max num adjacent territories
        if (adjacent->getConnectedTerritories().size()> 10) {
           //throw std::runtime_error("Max number of adjacent territories exceeded, exiting!");
        } 

        std::cout<<"Visiting: " << territory->getName()<<std::endl;
            
        if (visitedNodes.find(adjacent) == visitedNodes.end()){
            DFS(adjacent,visitedNodes);
        }
    }
}

void mapFullyConnected(unordered_map<std::string, Territory*> mapData) {
   
    if (mapData.empty()) {
    std::cout<<"Map is empty";
    return;
    }

    //create an empty unordered set to store visited nodes
    std::unordered_set<Territory*> visitedNodes;

    auto it = mapData.begin();

    //grab the territory pointer from map data which is stored in the maps second position
    Territory* startNode = it->second;
    DFS(startNode,visitedNodes);

    //using the size of the vector in mapData check if that number matches the number of visited territories
    std::cout<<(visitedNodes.size() == mapData.size());
    //check that num territories do not exceed 255
    std::cout<<(mapData.size() <= 255);
    return;
    
}

