#include "Player.h"
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
    : name(other.name), territories(other.territories), hand(new Hand(*other.hand)), ordersList(new OrdersList(*other.ordersList)), territoriesToDefend(other.territoriesToDefend), territoriesToAttack(other.territoriesToAttack){
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

void Player::setName(const string& s) {
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

// Getters and Setters for TerritoriesToDefend
vector<Territory*> Player::getTerritoriesToDefend() const {
    return territoriesToDefend;
}

void Player::setTerritoriesToDefend(const vector<Territory*>& newTerritoriesToDefend) {
    territoriesToDefend = newTerritoriesToDefend;
}

// Getters and Setters for TerritoriesToAttack
vector<Territory*> Player::getTerritoriesToAttack() const {
    return territoriesToAttack;
}

void Player::setTerritoriesToAttack(const vector<Territory*>& newTerritoriesToAttack) {
    territoriesToAttack = newTerritoriesToAttack;
}

// Getters and Setters for conqueredATerritory
bool Player::getConqueredATerritory() const {
    return conqueredATerritory;
}

void Player::setConqueredATerritory(const bool& captured) {
    name = captured;
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
vector<Territory*> Player::toDefend(Territory* defendingTerritories) {
    territoriesToDefend.push_back(defendingTerritories);
    for (int i = 0; i < territoriesToDefend.size(); i++) {
        cout << territoriesToDefend[i]->getName() << " defending with " << territoriesToDefend[i]->getArmies() << "\n";
    }
    return territoriesToDefend;
}

// Method to return a list of territories to attack
vector<Territory*> Player::toAttack(Territory* attackingTerritories) {
    territoriesToAttack.push_back(attackingTerritories);
    for (int i = 0; i < territoriesToAttack.size(); i++) {
         cout << territoriesToAttack[i]->getName() << " attacking with " << territoriesToAttack[i]->getArmies() << "\n";
    }
    return territoriesToAttack;
}

// Method to issue an order
void Player::issueOrder(Order* order) {
    ordersList->add(order);
}

// Adding a Territories
void Player::addTerritories(Territory* territory) {
    territories.push_back(territory);
}

//removing a Territory
bool Player::removeTerritories(Territory* territory){
 auto it = std::find(territories.begin(), territories.end(), territory);
        
     if (it != territories.end()) {
        territories.erase(it);  // Remove the territory if found
        return true;
     } else {
        std::cout << "Territory not found." << std::endl;
        return false;
   }
    
}