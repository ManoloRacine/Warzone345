#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Map.h"   
#include "Order.h"       
#include "Cards.h"      

class Player {
private:
    std::vector<Territory*>* territories;  // Collection of territories
    std::vector<Order*>* orders;           // List of orders
    std::vector<Card*>* handOfCards;       // Hand of cards

public:
    // Constructors
    Player();
    Player(const Player& other); // Copy constructor

    // Destructor
    ~Player();

    // Assignment operator
    Player& operator=(const Player& other);

    // Player methods
    std::vector<Territory*> toDefend();
    std::vector<Territory*> toAttack();
    void issueOrder(Order* order);

    // Stream insertion operator for printing player details
    friend std::ostream& operator<<(std::ostream& out, const Player& player);
};

#endif // PLAYER_H
