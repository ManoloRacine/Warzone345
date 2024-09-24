// Written By: Nektarios Zampetoulakis (40211948)
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::vector;


//------------------ TERRITORY --------------------------------

class Territory {

private:
    // Territory Attributes
    std::string name;
    std::pair<int, int> coordinates;
    std::string continent;
    std::vector<std::string> connectedTerritories;
    int* owner = nullptr;  // Owner initialized as pointer
    int armies = 0;

public:
    // Constructor
    Territory(const string& name, const pair<int, int>& coordinates, const string& continent, int ownerVal = 0, int armies = 0)
        : name(name), coordinates(coordinates), continent(continent), armies(armies) {
            owner = new int(ownerVal);  // Dynamically allocate memory for owner
        }

    // Destructor to clean up dynamic memory
    ~Territory() {
        delete owner;  // Clean up the owner pointer
    }

    // Setters and Getters
    void setName(const std::string& n) {
        name = n;
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

    void setContinent(const std::string& con) {
        continent = con;
    }

    std::string getContinent() const {
        return continent;
    }

    void addConnectedTerritory(const std::string& territoryName) {
        connectedTerritories.push_back(territoryName);
    }

    void setOwner(int newOwner) {
        *owner = newOwner;  // Set new owner value
    }

    int getOwner() const {
        return *owner;  // Dereference pointer to return value
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
        cout << "Continent: " << continent << endl;
        if (owner) {  // Check if owner is not null
            cout << "Owner: " << *owner << endl;  // Dereference pointer to show owner
        } else {
            cout << "Owner: None" << endl;
        }
        cout << "Armies: " << armies << endl;
        cout << "Connected Territories: ";
        for (const auto& territory : connectedTerritories) {
            cout << territory << " ";
        }
        cout << endl;
    }
};

