#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "../Map/Map.h"
#include "../Orders/Order.h"
#include "../Cards/Cards.h"

class Territory;

using namespace std;

class Player {
private:
    string name;
    vector<Territory*> territories;  // Collection of territories
    OrdersList* ordersList;           // List of orders
    Hand* hand;       // Hand of cards
    int reinforcementPool; //Needed for A2-Part2 - Nek

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
    void setName(const string& newName);

    // Getters and Setters for Reinforcemnts -ADDED IN P2-A2 - Nektarios
    inline int getReinforcements() const { return this->reinforcementPool;};
    inline void setReinforcements(const int& newReinforcments) { this->reinforcementPool = newReinforcments; };

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