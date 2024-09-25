// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ---- Written By: Nektarios Zampetoulakis (40211948) ---- 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

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
    vector<Territory*> connectedTerritories;
    int owner = -1;  
    int armies = 0;

public:
    // Constructor
    Territory(const std::string& name, const std::pair<int, int>& coordinates, Continent* continent, int owner, int armies)
        : name(name), coordinates(coordinates), continent(continent), owner(owner), armies(armies) {}

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

    void setContinent(Continent* con) {  // Accept a pointer to Continent
        continent = con;
    }

    Continent* getContinent() const {  // Return a pointer to Continent
        return continent;
    }

    void addConnectedTerritory(const std::string& territoryName) {
        connectedTerritories.push_back(territoryName);
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
        cout << "Territory: " << name << endl;
        cout << "Coordinates: (" << coordinates.first << ", " << coordinates.second << ")" << endl;
        if (continent) {
            cout << "Continent: " << continent->getName() << endl;  // Access continent name
        } else {
            cout << "Continent: None" << endl;  // Handle case where continent is not set
        }
        cout << "Owner: " << owner << endl; 
        cout << "Armies: " << armies << endl;
        cout << "Connected Territories: ";
        for (const auto& territory : connectedTerritories) {
            cout << territory << " ";
        }
        cout << endl;
    }
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------ MAP LOADER --------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Load map
Map MapLoader(const std::string& path) {
    Map map;

    std::ifstream inputFile(path);
    
    if (!inputFile.is_open()) {
        throw std::runtime_error("Could not open file: " + path);
        return map; 
    }

    std::string line;
    std::string section;

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

            while (std::getline(inputFile, line)) {
                if (line.find('=') == std::string::npos) {
                    continue;
                } 
                if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                    // Remove potential leading/trailing spaces
                    key = key.substr(0, key.find_last_not_of(" \t") + 1);
                    value = value.substr(value.find_first_not_of(" \t"));

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
            }
        } else if (section == "Continents") {
            std::istringstream iss(line);
            std::string name;
            std::string bonusStr;

            if (std::getline(iss, name, '=') && std::getline(iss, bonusStr)) {
                // Trim whitespace from name and bonus
                name.erase(0, name.find_first_not_of(" \t"));
                name.erase(name.find_last_not_of(" \t") + 1);
                bonusStr.erase(0, bonusStr.find_first_not_of(" \t"));
                
                // Create a new Continent object
                int bonus = std::stoi(bonusStr);  // Convert the value to an integer

                Continent* newContinent = new Continent(name, bonus);
                map.addContinent(newContinent); 
            }
        } else if (section == "Territories") {
            std::istringstream iss(line);
            std::string name;
            std::string x;
            std::string y;
            Continent* continent;

        }
    }

    inputFile.close(); 
    return map; 
};






