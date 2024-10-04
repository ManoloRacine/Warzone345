#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <stdexcept>
//#include "Player.h"

using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::vector;
using std::unordered_map;


// Forward declarations
class Territory;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ CONTINENT ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Continent {
private:
    // Continent Attributes
    std::string name;
    int bonus;
    vector<Territory*> territories;

public:

    // Constructor
    Continent(const std::string& name, int bonus);

    // Copy Constructor
    Continent(const Continent& other);

    // Assignment Operator
    Continent& operator=(const Continent& other);

    // Stream Insertion Operator
    friend std::ostream& operator<<(std::ostream& os, const Continent& continent);

    // Setters and Getters
    void setName(const std::string& n);
    std::string getName() const;
    void setBonus(int b);
    int getBonus() const;

    void addTerritory(Territory* territory);
    std::vector<Territory*> getTerritories() const;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ TERRITORY ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Territory {
private:
    // Territory Attributes
    std::string name;
    std::pair<int, int> coordinates;
    Continent* continent; 
    std::vector<Territory*> connectedTerritories; 
    //TO BE CHANGED
    int owner = -1;
    //Player* = nullptr;  
    int armies = 0;

public:
    // Constructors
    Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent, int owner, int armies);
    //Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent, Player* owner, int armies);  // TO BE CHANGED
    Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent);

    // Copy Constructor
    Territory(const Territory& other);

    // Assignment Operator
    Territory& operator=(const Territory& other);

    // Stream Insertion Operator
    friend std::ostream& operator<<(std::ostream& os, const Territory& territory);

    // Setters and Getters
    void setName(const std::string& name);
    std::string getName() const;
    void setCoordinates(const std::pair<int, int>& c);
    std::pair<int, int> getCoordinates() const;
    void setContinent(Continent* con);  
    Continent* getContinent() const;  
    void addConnectedTerritory(Territory* territory);  
    void setArmies(int numArmies);
    int getArmies() const;
    const std::vector<Territory*>& getConnectedTerritories() const;

    // TO BE CHANGED 
    void setOwner(int newOwner);
    // void setOwner(Player* newOwner)
    int getOwner() const;
    // Player* getOwner() const;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// --------------------  MAP ------------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Map {

public:
    enum Scroll {
        horizontal,
        vertical,
        none
    };

private:
    std::string author;
    bool warn;
    std::string imgPath;
    bool wrap;
    Scroll scrollType;
    vector<Continent*> Continents;
    unordered_map<std::string, Territory*> mapData; //its just a dictionary of key = territory name, value = territory pointer.
    
public:

    // Destructor
    ~Map();

    // Constructors
    Map() = default; // Default constructor
    
    Map(const Map& other); // Copy constructor

    // Assignment operator
    Map& operator=(const Map& other);

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Map& map);

    // Setters
    void setAuthor(const std::string& author);
    void setWarn(bool warn);
    void setImgPath(const std::string& imgPath);
    void setWrap(bool wrap);
    void setScrollType(Scroll scrollType);

    // Getters
    std::string getAuthor() const;
    bool getWarn() const;
    std::string getImgPath() const;
    bool getWrap() const;
    Scroll getScrollType() const;
    vector<Continent*> getContinents() const;
    unordered_map<std::string, Territory*> getMapData() const;


    void addContinent(Continent* continent);
    void addTerritory(const std::string& name, Territory* territory);
    Territory* getTerritoryPtr(const std::string& name);


   // -------- validation ----------
    void DFS(Territory* territory, std::unordered_set<Territory*>& visitedNodes);
    bool mapFullyConnected(unordered_map<std::string, Territory*> mapData);
    bool validateUniqueness(unordered_map<std::string, Territory*> mapData, vector<Continent*> Continents);
    bool subGraphCheck(unordered_map<std::string, Territory*> mapData, vector<Continent*> Continents);
    void DFSsubGraph(Territory* territory, std::unordered_set<Territory*> visitedNodes, Continent* Continent);
    void SubGraphDFS(Territory* territory, std::unordered_set<Territory*>& visitedNodes, Continent* Continent, vector<Territory*> &traversal);
    bool validate();

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ MAP LOADER --------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class MapLoader {

public:
    // Load map
    Map loadMap(const std::string& path);

private:
     // Load map helpers
    void trim(std::string &line);
    void processMapSection(const std::string &line, Map &map);
    void setScrollType(Map &map, const std::string &value);
    void processContinentsSection(const std::string &line, Map &map);
    void processTerritoriesSection(const std::string &line, Map &map, std::unordered_map<Territory *, std::vector<std::string>> &associationsMap);
    Continent* findContinentByName(Map &map, const std::string &continentName);
    std::vector<std::string> parseConnectedTerritories(std::istringstream &iss);
    void setupTerritoryConnections(Map &map, const std::unordered_map<Territory *, std::vector<std::string>> &associationsMap);
    void validateCoordinates(int x, int y);
};

#endif 
