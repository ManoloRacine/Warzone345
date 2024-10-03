<<<<<<< HEAD:src/Player/Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Map.h"   
#include "Order.h"       
#include "Cards.h"   

using namespace std;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------   PLAYER  ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Player {
private:
    string name;
    vector<Territory*> territories;  // Collection of territories
    OrdersList* ordersList;           // List of orders
    Hand* hand;       // Hand of cards

public:
    // Constructors
    Player();

    Player(const string& playerName);

    // Copy constructor
    Player(const Player& other); 

    // Destructor
    ~Player();

    // Getters and Setters for Name
    string getName() const;
    void setName(string& newName);

    // Getters and Setters for Territories
    vector<Territory*> getTerritories() const;
    void setTerritories(const vector<Territory*>& newTerritories);

    // Getters and Setters for Orders
    OrdersList* getOrdersList() const;
    void setOrdersList(OrdersList* newOrdersList);

    // Getters and Setters for Hand (Cards)
    Hand* getHand() const;
    void setHand(Hand* newHand);

    // Display player information
    void printPlayer() const;

    // Player methods
    vector<Territory*> toDefend(vector<Territory*>);
    vector<Territory*> toAttack(vector<Territory*>);
    void issueOrder(Order* order);
    void addTerritories(Territory*);
};

#endif // PLAYER_H
=======
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Map.h"   
#include "Order.h"       
#include "Cards.h"   

using namespace std;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------------------   PLAYER  ---------------------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Player {
private:
    string name;
    vector<Territory*> territories;  // Collection of territories
    OrdersList* ordersList;           // List of orders
    Hand* hand;       // Hand of cards

public:
    // Constructors
    Player();

    Player(const string& playerName);

    // Copy constructor
    Player(const Player& other); 

    // Destructor
    ~Player();

    // Getters and Setters for Name
    string getName() const;
    void setName(string& newName);

    // Getters and Setters for Territories
    vector<Territory*> getTerritories() const;
    void setTerritories(const vector<Territory*>& newTerritories);

    // Getters and Setters for Orders
    OrdersList* getOrdersList() const;
    void setOrdersList(OrdersList* newOrdersList);

    // Getters and Setters for Hand (Cards)
    Hand* getHand() const;
    void setHand(Hand* newHand);

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Player& player);  


    // Display player information
    void printPlayer() const;

    // Player methods
    vector<Territory*> toDefend(vector<Territory*>);
    vector<Territory*> toAttack(vector<Territory*>);
    void issueOrder(Order* order);
    void addTerritories(Territory*);
};

#endif // PLAYER_H
>>>>>>> d7486e98d6d9b9a6fbac2618f3925d86af305017:src/Player.h
