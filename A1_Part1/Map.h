#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <unordered_set>

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
    std::string name;
    int bonus;

public:

    vector<Territory*> territories;

    // Constructor
    Continent(const std::string& name, int bonus);

    // Setters and Getters
    void setName(const std::string& n);
    std::string getName() const;
    void setBonus(int b);
    int getBonus() const;

    void addTerritory(Territory* territory);
    void displayInfo() const;
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
    int owner = -1;  
    int armies = 0;

public:
    // Constructors
    Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent, int owner, int armies);
    Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent);

    // Setters and Getters
    void setName(const std::string& name);
    std::string getName() const;
    void setCoordinates(const std::pair<int, int>& c);
    std::pair<int, int> getCoordinates() const;
    void setContinent(Continent* con);  
    Continent* getContinent() const;  
    void addConnectedTerritory(Territory* territory);  
    void setOwner(int newOwner);
    int getOwner() const;
    void setArmies(int numArmies);
    int getArmies() const;
    const std::vector<Territory*>& getConnectedTerritories() const;

    // Method to display territory information
    void displayInfo() const;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// --------------------  MAP ------------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Map {
private:
    std::string author;
    bool warn;
    std::string imgPath;
    bool wrap;
    int numTerritories;

public:
    enum Scroll {
        horizontal,
        vertical,
        none 
    };
    Scroll scrollType;

    vector<Continent*> Continents;
    unordered_map<std::string, Territory*> mapData;


    // Destructor
    ~Map();

    // Setters
    void setAuthor(const std::string& author);
    void setWarn(bool warn);
    void setImgPath(const std::string& imgPath);
    void setWrap(bool wrap);
    void setScrollType(Scroll scrollType);
    void setNumTerritories(const int numTerritories);

    // Getters
    std::string getAuthor() const;
    bool getWarn() const;
    std::string getImgPath() const;
    bool getWrap() const;
    Scroll getScrollType() const;
    int getNumTerritories() const;
    unordered_map<std::string, Territory*> getMapData() const;


    void addContinent(Continent* continent);
    void addTerritory(const std::string& name, Territory* territory);
    Territory* getTerritoryPtr(const std::string& name);
    void displayInfo() const;

    void DFS(Territory *territory, std::unordered_set<Territory*>& visitedNodes);
    void mapFullyConnected(unordered_map<std::string, Territory*> mapData);
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ MAP LOADER --------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class MapLoader {

public:
    // Load map
    Map loadMap(const std::string& path);
};

#endif 
