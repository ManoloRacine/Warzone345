//
// Created by Ryad on 2024-11-26.
//

#include "Player.h"
#include "PlayerStrategy.h"
#include "Player.cpp"
#include <algorithm>

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
void HumanPlayerStrategy::issueOrder(){
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

// Method to return a list of territories to attack kind of redundent as Benevolent player cannot attack
vector<Territory*> BenevolentPlayerStrategy::toAttack(Territory* attackingTerritories) {
    getPlayer()->getTerritoriesToAttack().push_back(attackingTerritories);
    cout<< "Attacking territory is " << attackingTerritories->getName()<<endl;
    return getPlayer()->getTerritoriesToAttack();
}

// issue order for the benevolent player
void BenevolentPlayerStrategy::issueOrder() {
    //setup for deploy order
    Territory* thirdLeastTroopsTerritory = nullptr;
    Territory* leastTroopsTerritory = nullptr;
    Territory* secondLeastTroopsTerritory = nullptr;
    Territory* fourthLeastTroopsTerritory = nullptr;
        int minTroops = INT_MAX;
        for(Territory* territory : getPlayer()->getTerritories()){
            if (territory->getArmies() < minTroops){
                minTroops = territory->getArmies();
                fourthLeastTroopsTerritory = thirdLeastTroopsTerritory;
                thirdLeastTroopsTerritory = secondLeastTroopsTerritory;
                secondLeastTroopsTerritory = leastTroopsTerritory;
                leastTroopsTerritory = territory;
            }
        }

    //deploy orders
    Deploy* deploy = new Deploy(getPlayer(), nullptr, (getPlayer()->getReinforcements()/2), nullptr, leastTroopsTerritory);
    getPlayer()->getOrdersList()->add(deploy);
    Deploy* deploy2 = new Deploy(getPlayer(), nullptr, getPlayer()->getReinforcements(), nullptr, secondLeastTroopsTerritory);
    getPlayer()->getOrdersList()->add(deploy2);

    //setup for advance order
    bool NotNull = false;
    Territory* advanceSource = nullptr;
    for(Territory* territory : thirdLeastTroopsTerritory->getConnectedTerritories()){
      if (territory->getOwner() == getPlayer()){
        advanceSource = territory;
      }
    }
    for(Territory* territory : thirdLeastTroopsTerritory->getConnectedTerritories()){
      if (territory->getOwner() == getPlayer() && territory->getArmies() > advanceSource->getArmies()){
        advanceSource = territory;
        NotNull = true;
      }
    }
    //Advance order
    if(NotNull){
       Advance* advance = new Advance(getPlayer(), getPlayer(), (advanceSource->getArmies()/4), advanceSource, thirdLeastTroopsTerritory);
       getPlayer()->getOrdersList()->add(advance);
    }
    //Airlift order setup
    Territory* maxTroopsTerritory = nullptr;
        int maxTroops = 0;
        for(Territory* territory : getPlayer()->getTerritories()){
            if (territory->getArmies() > maxTroops){
                maxTroops = territory->getArmies();
                maxTroopsTerritory = territory;
            }
        }
    //airlift order (added in some chance to use a card for some fun and it say that benevolent Players may use cards)
    if (hasCard("airlift", getPlayer())){
        if (rand() % 100 < 50){
            Airlift* airlift = new Airlift(getPlayer(), getPlayer(), (maxTroopsTerritory->getArmies()/3), maxTroopsTerritory, fourthLeastTroopsTerritory);
            getPlayer()->getOrdersList()->add(airlift);
        }
    }

     //blockade order (added in some chance to use a card for some fun and it say that benevolent Players may use cards)
    if (hasCard("blockade", getPlayer())){
        if (rand() % 100 < 25){
            Blockade* blockade = new Blockade(getPlayer(), getPlayer(), 0, leastTroopsTerritory, leastTroopsTerritory);
            getPlayer()->getOrdersList()->add(blockade);
        }
    }

     //diplomacy order (added in some chance to use a card for some fun and it say that benevolent Players may use cards)
    if (hasCard("diplomacy", getPlayer())){
        if (rand() % 100 < 75){
            if(!leastTroopsTerritory->getConnectedTerritories()[1]){
                if (leastTroopsTerritory->getConnectedTerritories()[1]->getOwner() != leastTroopsTerritory->getOwner()){
                    Negotiate* negotiate = new Negotiate(player, leastTroopsTerritory->getConnectedTerritories()[1]->getOwner(), 0, leastTroopsTerritory, leastTroopsTerritory->getConnectedTerritories()[1]);
                    getPlayer()->getOrdersList()->add(negotiate);
                }
            }
        }
    }
}