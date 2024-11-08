#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <set>
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
    vector<Territory*> territoriesToDefend; //For toDefend gets wiped every execute orders
    vector<Territory*> territoriesToAttack; //For toAttack gets wiped every execute orders
    bool conqueredATerritory; //To give card at end of turn
    set<Player*> negotiatedPlayers; //players that are negociating with you

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

    // Getters and Setters for territoriestoDefend
    vector<Territory*> getTerritoriesToDefend() const;
    void setTerritoriesToDefend(const vector<Territory*>& newTerritoriesToDefend);

    // Getters and Setters for territoriestoAttack
    vector<Territory*> getTerritoriesToAttack() const;
    void setTerritoriesToAttack(const vector<Territory*>& newTerritoriesToAttack);

    // Getters and Setters for conqueredATerritory
    bool getConqueredATerritory() const;
    void setConqueredATerritory(const bool& captured);

     // Getters and Setters for for NegociatePlayers
     set<Player*> getNegotiatedPlayers() const;
     void setNegotiatedPlayers(set<Player*>& newNegociatedPlayers);

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Player& player);  

    // Display player information
    void printPlayer() const;

    // Player methods
    vector<Territory*> toDefend(Territory*);
    vector<Territory*> toAttack(Territory*);
    void issueOrder(Order* order);
    void addTerritories(Territory*);
    bool removeTerritories(Territory*);



//for negociating with a player
void addNegotiateEffect(Player* other);
bool isNegotiatedWith(Player* other);

void clearNegotiations();

//reset statuses that may have been altered during play
void resetPlayerStatuses(std::vector<Player*>& players, Deck* deck);
};

//checks if a player has a card in hand
bool hasCard(string card, Player* player);
#endif // PLAYER_H