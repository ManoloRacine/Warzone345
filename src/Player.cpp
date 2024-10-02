#include "Player.h"
#include <iostream>
#include <algorithm> // for std::copy

// Default constructor
Player::Player() {
    territories = new std::vector<Territory*>();
    orders = new std::vector<Order*>();
    handOfCards = new std::vector<Card*>();
}

// Copy constructor
Player::Player(const Player& other) {
    territories = new std::vector<Territory*>(*(other.territories));
    orders = new std::vector<Order*>(*(other.orders));
    handOfCards = new std::vector<Card*>(*(other.handOfCards));
}

// Destructor
Player::~Player() {
    delete territories;
    delete orders;
    delete handOfCards;
}

// Assignment operator
Player& Player::operator=(const Player& other) {
    if (this == &other) return *this;

    delete territories;
    delete orders;
    delete handOfCards;

    territories = new std::vector<Territory*>(*(other.territories));
    orders = new std::vector<Order*>(*(other.orders));
    handOfCards = new std::vector<Card*>(*(other.handOfCards));

    return *this;
}

// Method to return a list of territories to defend
std::vector<Territory*> Player::toDefend(vector<Territory*> defendingTerritories) {
    for (int i = 0; i < defendingTerritories.size() - 1; i++) {
        std::cout << defendingTerritories[i]->getName() << " defending with " << defendingTerritories[i]->getArmies();
    }
    return defendingTerritories;
}

// Method to return a list of territories to attack
std::vector<Territory*> Player::toAttack(vector<Territory*> attackingTerritories) {
    for (int i = 0; i < attackingTerritories.size() - 1; i++) {
        std::cout << attackingTerritories[i]->getName() << " attacking with " << attackingTerritories[i]->getArmies();
    }
    return attackingTerritories;
}

// Method to issue an order
void Player::issueOrder(Order* order) {
    orders->push_back(order);
}

// Stream insertion operator for Player
std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << "Player owns " << player.territories->size() << " territories and has issued "
        << player.orders->size() << " orders." << std::endl;
    return out;
}
