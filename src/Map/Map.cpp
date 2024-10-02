// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ---- Written By: Nektarios Zampetoulakis (40211948) ----
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <stdexcept>
#include <numeric>
#include <set>
#include "Map.h"

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;
using std::basic_ostream;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ CONTINENT ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Construcotr
Continent::Continent(const std::string &name, int bonus)
    : name(name), bonus(bonus) {}

// Copy Constructor
Continent::Continent(const Continent& other) 
    : name(other.name), bonus(other.bonus) {
    // Deep copy the territories
    for (auto territory : other.territories) {
        territories.push_back(new Territory(*territory));
    }
}

// Assignment Operator
Continent& Continent::operator=(const Continent& other) {
    if (this != &other) { // Check for self-assignment
        name = other.name;
        bonus = other.bonus;

        // Clear existing territories
        for (auto territory : territories) {
            delete territory;
        }
        territories.clear();

        // Deep copy the territories
        for (auto territory : other.territories) {
            territories.push_back(new Territory(*territory));
        }
    }
    return *this;
}

// Stream Insertion Operator
std::ostream& operator<<(std::ostream& os, const Continent& continent) {
    os << "Continent Name: " << continent.getName() << ", Bonus: " << continent.getBonus();
    return os;
}


// Setters and Getters

void Continent::setName(const std::string &n)
{
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


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ TERRITORY ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Constructor
Territory::Territory(const std::string &name, const std::pair<int, int> &coordinates, Continent *continent, int owner, int armies)
    : name(name), coordinates(coordinates), continent(continent), owner(owner), armies(armies) {}

// Overloaded constructor with name, coordinates, and continent
Territory::Territory(const std::string &name, const std::pair<int, int> &coordinates, Continent *continent)
    : Territory(name, coordinates, continent, 0, 0) {}

// Copy Constructor
Territory::Territory(const Territory& other) 
    : name(other.name),
      coordinates(other.coordinates),
      continent(other.continent), 
      connectedTerritories(other.connectedTerritories), 
      owner(other.owner),
      armies(other.armies) {}


// Assignment Operator
Territory& Territory::operator=(const Territory& other) {
    if (this != &other) { // Self-assignment check
        name = other.name;
        coordinates = other.coordinates;
        continent = other.continent; 
        connectedTerritories = other.connectedTerritories;
        owner = other.owner;
        armies = other.armies;
    }
    return *this;
}


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


//Stream Display Territory in csv format
std::ostream& operator<<(std::ostream& os, const Territory& territory) {
    os << territory.name << " , "
       << territory.coordinates.first << " , "
       << territory.coordinates.second << " , "
       << (territory.continent ? territory.continent->getName() : "None") << " , "
       << territory.owner << " [owner] ,"
       << territory.armies << " [armies] ,"
       << " Connected Territories: ";

    // Concatenate the names of connected territories
    os << std::accumulate(
        territory.connectedTerritories.begin(),
        territory.connectedTerritories.end(),
        std::string{},
        [](const std::string& a, const Territory* b) {
            return a + (a.length() > 0 ? "," : "") + b->getName();
        });

    os << std::endl;
    return os;
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

// Copy Constructor
Map::Map(const Map& other)
    : author(other.author),
      warn(other.warn),
      imgPath(other.imgPath),
      wrap(other.wrap),
      scrollType(other.scrollType) { // Copy the scroll type
    // Deep copy of continents and territories
    for (const auto& continent : other.Continents) {
        Continent* newContinent = new Continent(*continent); // Assuming you have a proper copy constructor in Continent
        Continents.push_back(newContinent);
    }
    for (const auto& pair : other.mapData) {
        mapData[pair.first] = new Territory(*pair.second); // Assuming you have a proper copy constructor in Territory
    }
}

// Assignment Operator
Map& Map::operator=(const Map& other) {
    if (this != &other) { // Self-assignment check
        // Clean up existing data
        for (auto continent : Continents) {
            delete continent; // Clean up existing continents
        }
        for (auto pair : mapData) {
            delete pair.second; // Clean up existing territories
        }

        // Copy new data
        author = other.author;
        warn = other.warn;
        imgPath = other.imgPath;
        wrap = other.wrap;
        scrollType = other.scrollType;

        // Deep copy of continents and territories
        for (const auto& continent : other.Continents) {
            Continent* newContinent = new Continent(*continent);
            Continents.push_back(newContinent);
        }
        for (const auto& pair : other.mapData) {
            mapData[pair.first] = new Territory(*pair.second);
        }
    }
    return *this;
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
    {                              
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


std::ostream& operator<<(std::ostream& os, const Map& map) {
    os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    os << "~~~~~~~~~~~~~~~~~~~~~~ MAP DATA ~~~~~~~~~~~~~~~~~~~~~~~~\n";
    os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    os << "Map Author: " << map.getAuthor() << "\n";
    os << "Image Path: " << map.getImgPath() << "\n";
    os << "Wrap: " << (map.getWrap() ? "Yes" : "No") << "\n";
    
    os << "Scroll Type: ";
    switch (map.getScrollType()) {
        case Map::Scroll::horizontal:
            os << "Horizontal\n";
            break;
        case Map::Scroll::vertical:
            os << "Vertical\n";
            break;
        case Map::Scroll::none:
            os << "None\n";
            break;
    }

    os << std::endl;
    os << std::endl;

    for (const auto& continent : map.Continents) {
        os << *continent << "\n";  // Using the stream operator for Continent

        os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        os << "Territories in " << continent->getName() << ":\n";
        os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

        for (const auto& pair : map.mapData) {
            if (pair.second->getContinent() == continent) {
                os << *(pair.second) << "\n";  // Using the stream operator for Territory
            }
        }
        os << "\n";
    }

    return os;
}




// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ MAP VALIDATION ----------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ---------------------------- Griffin Sin-Chan (40278049) ------------------------------------


// Depth-first search takes in a starting node and a set tracking the visited nodes
void Map::DFS(Territory* territory, std::unordered_set<Territory*>& visitedNodes) {
    if (!territory) return; // Check for null pointer

    // Track the current node that is being visited
    visitedNodes.insert(territory);
    
    // From the current node check the vector of adjacent territories
    for (Territory* adjacent : territory->getConnectedTerritories()) {

        // Error checking for max num adjacent territories
        if (adjacent->getConnectedTerritories().size() > 10) {
            throw std::runtime_error("Error, max number of adjacent territories exceeded, exiting!");
        }
        // Check if the adjacent territory has not been visited
        if (visitedNodes.find(adjacent) == visitedNodes.end()) {
            DFS(adjacent, visitedNodes);
        }
    }
}


bool Map::validateUniqueness(unordered_map<std::string, Territory*> mapData,vector<Continent*> Continents) {
 //checking that the territory is part of only one continent
    //iteration is index in the map
  
    for(const auto &[name, ptrTerritory] : mapData) {
          int k= 0;
       
        for (const auto & iterator : Continents) {
        //use territories list from each cotinent, iterate trough all territories
            if (iterator->territories.size() == 0) {
                throw std::runtime_error("Empty Continent");
            }
            
            for (int j = 0; j <= iterator->territories.size()-1; j++ ) { 
               
                
                //from the map grab the value in the second position which is a territory ptr and point to territory name
                if (name == iterator->territories[j]->getName()) {
                        k++;
                    if (k > 1) {
                        throw std::runtime_error("Error, territory is part of more than one continent!");
                        return false;
                       
                    }
                }
            } 
        } 
    }
    
    return true;
       
    }
 
bool Map::mapFullyConnected(unordered_map<std::string, Territory*> mapData) {
    if (mapData.empty()) {
        std::cout << "Map is empty" << std::endl;
        return false; // Indicate the map is not connected
    }

    // Create an empty unordered set to store visited nodes
    std::unordered_set<Territory*> visitedNodes;

    auto iteration = mapData.begin();
    Territory* startNode = iteration->second; // Grab the first territory pointer

    // Start DFS from the initial territory
    DFS(startNode, visitedNodes);

    // Check if the number of visited territories matches the total number of territories
    bool isConnected = (visitedNodes.size() == mapData.size());
    std::cout << "Is the map fully connected? " << (isConnected ? "Yes" : "No") << std::endl;

    // Check that the number of territories does not exceed 255
    if (mapData.size() > 255) {
        std::cout << "Warning: Number of territories exceeds the limit of 255." << std::endl;
    }


    return isConnected;
}

// ----------------------------------------------------------------------------------------


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

                    // Add territoryPTR to map
                    map.addTerritory(name, newTerritory);

                    // Add territoryPTR to continent
                    continent->addTerritory(newTerritory);

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




