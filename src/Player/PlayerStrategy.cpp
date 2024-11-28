//
// Created by Ryad on 2024-11-26.
//

#include "Player.h"
#include "PlayerStrategy.h"
#include "Player.cpp"

PlayerStrategy* PlayerStrategy::createStrategy(Player *player, const std::string& strategy) {

    std::string strategy_name;
    for(auto& c : strategy){strategy_name += (char)std::tolower(c);} // to lower case for comparaison

    if(strategy_name == "human") {
        return new HumanPlayerStrategy(player);
    } else if(strategy_name == "aggressive") {
        return new AggressivePlayerStrategy(player);
    } else if(strategy_name == "benevolent") {
        return new BenevolentPlayerStrategy(player);
    } else if(strategy_name == "neutral") {
        return new NeutralPlayerStrategy(player);
    } else if (strategy_name == "cheater") {
        return new CheaterPlayerStrategy(player);
    } else {
        throw std::runtime_error("no such strategy");
    }
}

//===================================
//------------Human------------------
//===================================
//constructor
HumanPlayerStrategy::HumanPlayerStrategy(Player* player)
    :player(player){}

//destructor
HumanPlayerStrategy::~HumanPlayerStrategy(){
    delete player;
}

//getter for player
Player* HumanPlayerStrategy::getPlayer(){
    return player;
}

// Method to return a list of territories to defend
vector<Territory*> HumanPlayerStrategy::toDefend(Territory* defendingTerritories) {
    getPlayer()->getTerritoriesToDefend().push_back(defendingTerritories);
    cout<< "Defending territory is " << defendingTerritories->getName()<< endl;
    return getPlayer()->getTerritoriesToDefend();
}

// Method to return a list of territories to attack
vector<Territory*> HumanPlayerStrategy::toAttack(Territory* attackingTerritories) {
    getPlayer()->getTerritoriesToAttack().push_back(attackingTerritories);
    cout<< "Attacking territory is " << attackingTerritories->getName()<<endl;
    return getPlayer()->getTerritoriesToAttack();
}

// Method to issue an order
void HumanPlayerStrategy::issueOrder(Order* order) {
    getPlayer()->getOrdersList()->add(order);
}

//===================================
//------------Benevolent-------------
//===================================
//constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player)
    :player(player){}

//destructor
BenevolentPlayerStrategy::~BenevolentPlayerStrategy(){
    delete player;
}

//getter for player
Player* BenevolentPlayerStrategy::getPlayer(){
    return player;
}

// Method to return a list of territories to defend
vector<Territory*> BenevolentPlayerStrategy::toDefend(Territory* defendingTerritories) {
    getPlayer()->getTerritoriesToDefend().push_back(defendingTerritories);
    cout<< "Defending territory is " << defendingTerritories->getName()<< endl;
    return getPlayer()->getTerritoriesToDefend();
}

// Method to return a list of territories to attack
vector<Territory*> BenevolentPlayerStrategy::toAttack(Territory* attackingTerritories) {
    getPlayer()->getTerritoriesToAttack().push_back(attackingTerritories);
    cout<< "Attacking territory is " << attackingTerritories->getName()<<endl;
    return getPlayer()->getTerritoriesToAttack();
}

// issue order for the benevolent player
void BenevolentPlayerStrategy::issueOrder(Order* order) {
    if (order->getLabel() == "bomb"){
        return;
    }
    else if (order->getLabel() == "blockade"){
        getPlayer()->getOrdersList()->add(order);
        return;
    }
    else if (order->getLabel() == "diplomacy"){
        getPlayer()->getOrdersList()->add(order);
        return;
    }
    else if (order->getLabel() == "airlift"){
        getPlayer()->getOrdersList()->add(order);
        return;
    }
    else if (order->getLabel() == "deploy"){
        int minTroops = INT_MAX;
        for(Territory* territory : getPlayer()->getTerritories()){
            if (territory->getArmies() < minTroops){
                minTroops = territory->getArmies();
            }
        }
        if( order->getTarget()->getArmies() == minTroops){
            getPlayer()->getOrdersList()->add(order);
        return;
        }
        else{
         return;
        }
    }
    else if (order->getLabel() == "advance"){
        if(order->getSource()->getOwner() == order->getTarget()->getOwner()){
        int minTroops = INT_MAX;
        for(Territory* territory : getPlayer()->getTerritories()){
            if (territory->getArmies() < minTroops){
                minTroops = territory->getArmies();
            }
        }
        if( order->getTarget()->getArmies() == minTroops){
            getPlayer()->getOrdersList()->add(order);
        return;
        }
        else{
         return;
        }
        }
        else{
            return;
        }
    }
    else
    return;

}