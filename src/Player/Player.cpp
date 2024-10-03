#include "PLayer/Player.h"
#include <iostream>
#include <algorithm> // for std::copy

using namespace std;

// Default constructor
Player::Player(const string& playerName)
    : name(playerName), hand(new Hand()), ordersList(new OrdersList()) {
    // Initialize player with empty territories, hand, and order list
}

// Copy Constructor
Player::Player(const Player& other)
    : name(other.name), territories(other.territories), hand(new Hand(*other.hand)), ordersList(new OrdersList(*other.ordersList)) {
    // Copy territories, hand, and ordersList from the other player
}

// Destructor
Player::~Player() {
    vector<Territory*>().swap(territories);
    delete ordersList;
    delete hand;
}

// Getters and Setters for Name
string Player::getName() const {
    return name;
}

void Player::setName(string& s) {
    name = s;
}

// Getters and Setters for Territories
vector<Territory*> Player::getTerritories() const {
    return territories;
}

void Player::setTerritories(const vector<Territory*>& newTerritories) {
    territories = newTerritories;
}

// Getters and Setters for Orders
OrdersList* Player::getOrdersList() const {
    return ordersList;
}

void Player::setOrdersList(OrdersList* newOrdersList) {
    if (ordersList != nullptr) {
        delete ordersList;
    }
    ordersList = newOrdersList;
}

// Getters and Setters for Hand (Cards)
Hand* Player::getHand() const {
    return hand;
}

void Player::setHand(Hand* newHand) {
    if (hand != nullptr) {
        delete hand;
    }
    hand = newHand;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player territories: " << player.getTerritories().size() << " | Orders: " << player.ordersList->getList() << " | Cards in hand: " << player.hand->getCards().size() << "\n";
    return os;
}

// Display player information
void Player::printPlayer() const {
    cout << "Player Name: " << name << endl;

    for (int i = 0; i < territories.size(); i++) {
        cout << "Territories: \n" << territories[i]->getName() << "\n";
    }

    cout << "Cards in Hand: " << endl;
    for (Card* card : hand->getCards()) {
        cout << *card << endl;  // Assuming Card class has operator<< overloaded
    }

    cout << "Orders in Order List: " << endl;
    for (Order* order : *ordersList->getList()) {
        cout << *order << endl;  // Assuming Order class has operator<< overloaded
    }
}

// Method to return a list of territories to defend
vector<Territory*> Player::toDefend(vector<Territory*> defendingTerritories) {
    for (int i = 0; i < defendingTerritories.size(); i++) {
        cout << defendingTerritories[i]->getName() << " defending with " << defendingTerritories[i]->getArmies() << "\n";
    }
    return defendingTerritories;
}

// Method to return a list of territories to attack
vector<Territory*> Player::toAttack(vector<Territory*> attackingTerritories) {
    for (int i = 0; i < attackingTerritories.size(); i++) {
        cout << attackingTerritories[i]->getName() << " attacking with " << attackingTerritories[i]->getArmies() << "\n";
    }
    return attackingTerritories;
}

// Method to issue an order
void Player::issueOrder(Order* order) {
    ordersList->add(order);
}

// Adding a Territories
void Player::addTerritories(Territory* territory) {
    territories.push_back(territory);
}