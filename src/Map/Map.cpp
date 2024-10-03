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

 std::vector<Territory*> Continent::getTerritories() const {
    return this->territories;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ TERRITORY ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//TO BE CHANGED

// Constructor
Territory::Territory(const std::string &name, const std::pair<int, int> &coordinates, Continent *continent, int owner, int armies)
    : name(name), coordinates(coordinates), continent(continent), owner(owner), armies(armies) {}

    // Territory::Territory(const std::string &name, const std::pair<int, int> &coordinates, Continent *continent, Player* owner, int armies)
    // : name(name), coordinates(coordinates), continent(continent), owner(owner), armies(armies) {}

// Overloaded constructor with name, coordinates, and continent
Territory::Territory(const std::string &name, const std::pair<int, int> &coordinates, Continent *continent)
    : Territory(name, coordinates, continent, 0, 0) {}

    // Territory::Territory(const std::string &name, const std::pair<int, int> &coordinates, Continent *continent)
    // : Territory(name, coordinates, continent, nullptr, 0) {}

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
       //<< territory.owner.getName() << " [owner] ,"   //TO BE CHANGED
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


//To be CHANGED
void Territory::setOwner(int newOwner)
{   owner = newOwner; }

// void Territory::setOwner(Player* newOwner){ this->newOwner = newOwner}

int Territory::getOwner() const {
    return owner; }

//Player* Territory::getOwner() const { return owner}


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
      scrollType(other.scrollType) {
    // Deep copy of continents and territories
    for (const auto& continent : other.Continents) {
        Continent* newContinent = new Continent(*continent); 
        Continents.push_back(newContinent);
    }
    for (const auto& pair : other.mapData) {
        mapData[pair.first] = new Territory(*pair.second);
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

std::vector<Continent*> Map::getContinents() const{
    return this->Continents;
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

// get MapData ( all territories)
unordered_map<std::string, Territory*> Map::getMapData() const{
    return this->mapData;
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

    if (Continents.size() > 32) {
            throw std::runtime_error("Error, max number of continents exceeded, exiting!");
        }
  
    for(const auto &[name, ptrTerritory] : mapData) {
          int k= 0;
       
        for (const auto & iterator : Continents) {
        //use territories list from each cotinent, iterate trough all territories
            if (iterator->getTerritories().size() == 0) { //CHECK
                throw std::runtime_error("Empty Continent");
            }
            
            for (int j = 0; j <= iterator->getTerritories().size()-1; j++ ) {  //CHECK
               
                
                //from the map grab the value in the second position which is a territory ptr and point to territory name
                if (name == iterator->getTerritories()[j]->getName()) { //CHECK
                        k++;
                    if (k > 1) {
                        throw std::runtime_error("Error, territory is part of more than one continent or contienent is empty!");
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

    // Check that the number of territories does not exceed 255
    if (mapData.size() > 255) {
        std::cout << "Warning: Number of territories exceeds the limit of 255." << std::endl;
    }


    return isConnected;
}

void Map::DFSsubGraph(Territory* territory, std::unordered_set<Territory*> visitedNodes, Continent* Continent) {
    if (!territory) return; // Check for null pointer


    //Creating a new vector of lands common between Continents Territories and Territories found on the adjacency list
    vector<Territory*> commonLands;
    for (int i = 0; i < territory->getConnectedTerritories().size(); i++) {
        for (int j = 0; j < Continent->getTerritories().size(); j++) {
            //if a common land is found store it in the vector and stop inner loop
            if (territory->getConnectedTerritories()[i]->getName() == Continent->getTerritories()[j]->getName()) {
                commonLands.push_back(territory->getConnectedTerritories()[i]);
                break;
            }
        }
    }
    // Track the current node that is being visited
    visitedNodes.insert(territory);
    std::cout << "Visiting: " << territory->getName() <<"Part of Continent: "<< Continent->getName()<< std::endl;

    // From the current node check the vector of adjacent territories
    for (Territory* adjacent : commonLands) {
       
            // Check if the adjacent territory has not been visited
            if (visitedNodes.find(adjacent) == visitedNodes.end()) {
            DFSsubGraph(adjacent, visitedNodes, Continent);
        }
        
    
    }
    return;
}


bool Map::subGraphCheck(unordered_map<std::string, Territory*> mapData, vector<Continent*> Continents) {

    bool valid = false;
    //loop through all of the continents
    for(int i = 0; i <= Continents.size()-1; i++) {

        std::unordered_set<Territory*> visitedNodes;

        if (Continents[i]->getTerritories()[0]->getConnectedTerritories().size() == 0) {
            std::cout <<"Continent territory is disconnected";
            return false;
        }
        //takes in the current continents first territory as the starting node, 
        //has a empty vector to track visited nodes
        //Gives the current continent
        DFSsubGraph(Continents[i]->getTerritories()[0], visitedNodes,Continents[i]);

        bool isConnected = (visitedNodes.size() == Continents[i]->getTerritories().size());
        valid = isConnected;
    std::cout << "Is the continent connected? " << (isConnected ? "Yes" : "No") << std::endl;
    if (valid = false) {
        return false;
    }
    }
    return valid;

}



bool Map::validate() {
    try {
        // Check for uniqueness of territories across continents
        if (!validateUniqueness(this->mapData, this->Continents)) {
            std::cout << "Validation failed: Territories are not unique across continents!" << std::endl;
            return false;
        }

        // Check if the map is fully connected
        if (!mapFullyConnected(this->mapData)) {
             std::cout << "Validation failed: Map is not fully connected!" << std::endl;
             return false;
         }

        //ADD CHECK FOR SUBGRAPHS
        if (!subGraphCheck(this->mapData,this->Continents)) {
            std::cout << "Validation failed: Map subgraph is not fully connected!" << std::endl;
            return false;
        } 
        
        return true;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Validation failed: " << e.what() << std::endl;
        return false;
    }
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
        trim(line);

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
            processMapSection(line, map);
        }
        else if (section == "Continents")
        {
            processContinentsSection(line, map);
        }
        else if (section == "Territories")
        {
            processTerritoriesSection(line, map, associationsMap);
        }
        else
        {
            throw std::runtime_error("Invalid Header Name.");
        }
    }

    inputFile.close();
    setupTerritoryConnections(map, associationsMap);

    return map;
}

// Helper method to trim whitespace
void MapLoader::trim(std::string &line)
{
    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);
}

// Process the Map section
void MapLoader::processMapSection(const std::string &line, Map &map)
{
    std::istringstream iss(line);
    std::string key, value;

    if (line.find('=') != std::string::npos && std::getline(iss, key, '=') && std::getline(iss, value))
    {
        trim(key);
        trim(value);

        if (key == "author")
        {
            if (!value.empty()) map.setAuthor(value);
            else throw std::runtime_error("Missing value for 'author'.");
        }
        else if (key == "warn")
        {
            map.setWarn(value == "yes");
        }
        else if (key == "image")
        {
            if (!value.empty()) map.setImgPath(value);
            else throw std::runtime_error("Missing value for 'image'.");
        }
        else if (key == "wrap")
        {
            map.setWrap(value == "yes");
        }
        else if (key == "scroll")
        {
            setScrollType(map, value);
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

// Set scroll type for Map
void MapLoader::setScrollType(Map &map, const std::string &value)
{
    if (value == "horizontal") map.setScrollType(Map::horizontal);
    else if (value == "vertical") map.setScrollType(Map::vertical);
    else if (value == "none") map.setScrollType(Map::none);
    else throw std::runtime_error("Invalid value for 'scroll'.");
}

// Process the Continents section
void MapLoader::processContinentsSection(const std::string &line, Map &map)
{
    std::istringstream iss(line);
    std::string name, bonusStr;

    if (line.find('=') != std::string::npos && std::getline(iss, name, '=') && std::getline(iss, bonusStr))
    {
        trim(name);
        trim(bonusStr);

        if (name.empty()) throw std::runtime_error("Continent name is missing.");

        int bonus = std::stoi(bonusStr);
        Continent *newContinent = new Continent(name, bonus);
        map.addContinent(newContinent);
    }
    else
    {
        throw std::runtime_error("Invalid format for continent data. Expected 'name=bonus'.");
    }
}

// Process the Territories section
void MapLoader::processTerritoriesSection(const std::string &line, Map &map, std::unordered_map<Territory *, std::vector<std::string>> &associationsMap)
{
    std::istringstream iss(line);
    std::string name, x, y, continentName;

    if (std::getline(iss, name, ',') && std::getline(iss, x, ',') &&
        std::getline(iss, y, ',') && std::getline(iss, continentName, ','))
    {
        trim(name);
        trim(continentName);
        trim(x);
        trim(y);

        if (name.empty()) throw std::runtime_error("Territory name is missing.");
        if (continentName.empty()) throw std::runtime_error("Continent name is missing for territory '" + name + "'.");

        int coordX = std::stoi(x);
        int coordY = std::stoi(y);

        // Validate coordinates
        validateCoordinates(coordX, coordY);

        Continent *continent = findContinentByName(map, continentName);
        Territory *newTerritory = new Territory(name, {coordX, coordY}, continent);

        map.addTerritory(name, newTerritory);
        continent->addTerritory(newTerritory);

        std::vector<std::string> connectedList = parseConnectedTerritories(iss);
        associationsMap.insert({newTerritory, connectedList});
    }
    else
    {
        throw std::runtime_error("Invalid format for territory data. Expected 'name,x,y,continent'.");
    }
}

// Helper to find continent by name
Continent *MapLoader::findContinentByName(Map &map, const std::string &continentName)
{
    for (auto *cont : map.getContinents())
    {
        if (cont->getName() == continentName)
        {
            return cont;
        }
    }
    throw std::runtime_error("Error: Continent '" + continentName + "' does not exist.");
}

// Parse connected territories
std::vector<std::string> MapLoader::parseConnectedTerritories(std::istringstream &iss)
{
    std::vector<std::string> connectedList;
    std::string connTerritory;

    while (std::getline(iss, connTerritory, ','))
    {
        trim(connTerritory);
        if (!connTerritory.empty()) connectedList.push_back(connTerritory);
    }

    return connectedList;
}

// Set up connections between territories
void MapLoader::setupTerritoryConnections(Map &map, const std::unordered_map<Territory *, std::vector<std::string>> &associationsMap)
{
    for (const auto &[currentT, connectedTerritoryNames] : associationsMap)
    {
        for (const auto &territoryName : connectedTerritoryNames)
        {
            Territory *territoryPtr = map.getTerritoryPtr(territoryName);

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
}

// Validates coordinates for range between 0 and 1000
void MapLoader::validateCoordinates(int x, int y) {
    if (x < 0 || x > 1000 || y < 0 || y > 1000) {
        throw std::runtime_error("Coordinates are out of bounds. Expected values between 0 and 1000.");
    }
}





