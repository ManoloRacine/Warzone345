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

using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::vector;
using std::unordered_map;

class Territory;
class Continent;
class Map;

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
unordered_map<string,Territory*> mapData;


// Destructor
 ~Map() {
        for (auto continent : Continents) {
            delete continent;  // Free allocated memory for continents
        }
        for (auto pair : mapData) {
            delete pair.second;  // Free allocated memory for territories
        }
    }


    // Setters
    void setAuthor(const std::string& author) {
        this->author = author;
    }

    void setWarn(bool warn) {
        this->warn = warn;
    }

    void setImgPath(const std::string& imgPath) {
        this->imgPath = imgPath;
    }

    void setWrap(bool wrap) {
        this->wrap = wrap;
    }

    void setScrollType(Scroll scrollType) {
        this->scrollType = scrollType;
    }

    // Getters
    std::string getAuthor() const {
        return author;
    }

    bool getWarn() const {
        return warn;
    }

    std::string getImgPath() const {
        return imgPath;
    }

    bool getWrap() const {
        return wrap;
    }

    Scroll getScrollType() const {
        return scrollType;
    }

     void addContinent(Continent* continent) {
        if (continent != nullptr) { 
            Continents.push_back(continent);
        }
    }

    void addTerritory(const std::string& name, Territory* territory) {
        if (territory != nullptr) { // Ensure the territory pointer is valid
            mapData[name] = territory; // Add the territory to the hashmap with its name as the key
        }
    }
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ CONTINENT ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Continent {
   
    private:
       std::string name;
       int bonus;

    public: 
    
    vector<Territory*> territories;

    // Construcotr
    Continent(const std::string& name, int bonus)
        : name(name), bonus(bonus) {}

    // Setters and Getters

       void setName(const std::string& n) {
        name = n;
    }

    std::string getName() const {
        return name;
    }

    void setBonus(int b) {
        bonus = b;
    }

    int getBonus() const {
        return bonus;
    }

    void addTerritory(Territory* territory) {
        if (territory != nullptr) {  // Ensure the territory pointer is valid
            territories.push_back(territory);
        }
    }

    void displayInfo() const {
        cout << " Continent : " << name << ", Bonus : " << bonus << endl;
    }

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
    // Constructor
    Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent, int owner, int armies)
        : name(name), coordinates(coordinates), continent(continent), owner(owner), armies(armies) {}

    // Overloaded constructor with name, coordinates, and continent
    Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent) 
        : Territory(name, coordinates, continent, 0, 0) {} 

    // Setters and Getters
    void setName(const std::string& name) {
        this->name = name;
    }

    std::string getName() const {
        return name;
    }

    void setCoordinates(const std::pair<int, int>& c) {
        coordinates = c;
    }

    std::pair<int, int> getCoordinates() const {
        return coordinates;
    }

    void setContinent(Continent* con) {  
        continent = con;
    }

    Continent* getContinent() const {  
        return continent;
    }

    void addConnectedTerritory(Territory* territory) {  
        connectedTerritories.push_back(territory);
    }

    void setOwner(int newOwner) {
        owner = newOwner;  
    }

    int getOwner() const {
        return owner;  
    }

    void setArmies(int numArmies) {
        armies = numArmies;
    }

    int getArmies() const {
        return armies;
    }

    // Method to display territory information
    void displayInfo() const {
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
};



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ MAP LOADER --------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class MapLoader {
public:
    struct Connector {
        Territory* territory;
        std::vector<std::string> connectedT;

        Connector(Territory* t) : territory(t) {}

        void addConnectedTerritory(const std::string& connTerritory) {
        connectedT.push_back(connTerritory);
        }

        void addConnector(Territory* newTerritory, const std::string& connectedTerritoriesStr) {
        Connector newConnector(newTerritory);
        }

    };

    private:
    std::vector<Connector> connectors;

    public:

    // Load map
    Map loadMap(const std::string& path) {
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
};





