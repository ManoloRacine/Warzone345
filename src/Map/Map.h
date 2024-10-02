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
    void setOwner(int newOwner);
    int getOwner() const;
    void setArmies(int numArmies);
    int getArmies() const;
    const std::vector<Territory*>& getConnectedTerritories() const;

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

public:
    enum Scroll {
        horizontal,
        vertical,
        none 
    };
    Scroll scrollType;

    vector<Continent*> Continents;
    unordered_map<std::string, Territory*> mapData; //its just a dictionary of key = territory name, value = territory pointer.
    

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

    void addContinent(Continent* continent);
    void addTerritory(const std::string& name, Territory* territory);
    Territory* getTerritoryPtr(const std::string& name);


    // -------- validation ----------
    void DFS(Territory* territory, std::unordered_set<Territory*>& visitedNodes);
    bool mapFullyConnected(unordered_map<std::string, Territory*> mapData);

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
