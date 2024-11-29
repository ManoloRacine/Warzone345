//
// Created by Ryad on 2024-11-26.
//

#include "Player.h"
#include "PlayerStrategy.h"
#include <algorithm>
#include <climits>

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

string HumanPlayerStrategy::getType(){
    return "human";
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

    if (leastTroopsTerritory) {
        //deploy orders
        Deploy* deploy = new Deploy(getPlayer(), nullptr, (getPlayer()->getReinforcements()/2), nullptr, leastTroopsTerritory);
        getPlayer()->getOrdersList()->add(deploy);
    }

    if (secondLeastTroopsTerritory) {
        Deploy* deploy2 = new Deploy(getPlayer(), nullptr, getPlayer()->getReinforcements(), nullptr, secondLeastTroopsTerritory);
        getPlayer()->getOrdersList()->add(deploy2);
    }

    //setup for advance order
    bool NotNull = false;
    Territory* advanceSource = nullptr;
    if (thirdLeastTroopsTerritory) {
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
    }

    //Airlift order setup
    Territory* maxTroopsTerritory = nullptr;
        int maxTroops = -1;
        for(Territory* territory : getPlayer()->getTerritories()){
            if (territory->getArmies() > maxTroops){
                maxTroops = territory->getArmies();
                maxTroopsTerritory = territory;
            }
        }
    //airlift order (added in some chance to use a card for some fun and it say that benevolent Players may use cards)
    if (hasCard("airlift", getPlayer())){
        if (rand() % 100 < 50 && fourthLeastTroopsTerritory && maxTroopsTerritory){
            Airlift* airlift = new Airlift(getPlayer(), getPlayer(), (maxTroopsTerritory->getArmies()/3), maxTroopsTerritory, fourthLeastTroopsTerritory);
            getPlayer()->getOrdersList()->add(airlift);
        }
    }

     //blockade order (added in some chance to use a card for some fun and it say that benevolent Players may use cards)
    if (hasCard("blockade", getPlayer()) && leastTroopsTerritory){
        if (rand() % 100 < 25){
            Blockade* blockade = new Blockade(getPlayer(), getPlayer(), 0, leastTroopsTerritory, leastTroopsTerritory);
            getPlayer()->getOrdersList()->add(blockade);
        }
    }

     //diplomacy order (added in some chance to use a card for some fun and it say that benevolent Players may use cards)
    if (hasCard("diplomacy", getPlayer()) && leastTroopsTerritory){
        if (rand() % 100 < 75){
            if(leastTroopsTerritory->getConnectedTerritories()[1]){
                if (leastTroopsTerritory->getConnectedTerritories()[1]->getOwner() != leastTroopsTerritory->getOwner()){
                    Negotiate* negotiate1 = new Negotiate(player, leastTroopsTerritory->getConnectedTerritories()[1]->getOwner(), 0, leastTroopsTerritory, leastTroopsTerritory->getConnectedTerritories()[1]);
                    getPlayer()->getOrdersList()->add(negotiate1);
                }
            }
        }
    }
}
string BenevolentPlayerStrategy::getType(){
    return "benevolent";
}

//===================================
//------------Cheater------------------
//===================================
//constructor
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player)
    :player(player){}

//destructor
CheaterPlayerStrategy::~CheaterPlayerStrategy(){
    delete player;
}

//getter for player
Player* CheaterPlayerStrategy::getPlayer(){
    return player;
}

// Method to return a list of territories to defend
vector<Territory*> CheaterPlayerStrategy::toDefend(Territory* defendingTerritories) {
    getPlayer()->getTerritoriesToDefend().push_back(defendingTerritories);
    cout<< "Defending territory is " << defendingTerritories->getName()<< endl;
    return getPlayer()->getTerritoriesToDefend();
}

// Method to return a list of territories to attack
vector<Territory*> CheaterPlayerStrategy::toAttack(Territory* attackingTerritories) {
    getPlayer()->getTerritoriesToAttack().push_back(attackingTerritories);
    return getPlayer()->getTerritoriesToAttack();
}

// Method to issue an order
void CheaterPlayerStrategy::issueOrder(){
    //loop through all owned territories
    for(int i = 0; i < getPlayer()->getTerritories().size(); i++) {

       int numTroopsOnTerritory = getPlayer()->getTerritories()[i]->getArmies();
       int numAdjacentTerritories = getPlayer()->getTerritories()[i]->getConnectedTerritories().size();

       //number of troops to send in advance order
       int numAttackTroops = numTroopsOnTerritory/numAdjacentTerritories;

        for (int j = 0; j < numAdjacentTerritories; j++) {
            //check each territory in the adjacency list
            //compare territory owner's name with the current cheater player's name
            if (getPlayer()->getTerritories()[i]->getConnectedTerritories()[j]->getOwner()->getName() != getPlayer()->getName()){
                //before adding advance order check that the territory has not been attacked yet this turn
                bool territoryAttacked = false;
                for(int k = 0; k < getPlayer()->getTerritoriesToAttack().size(); k++) {
                    //territory names found in the attacked territories vector with current territory name
                    if(getPlayer()->getTerritoriesToAttack()[k]->getName() == getPlayer()->getTerritories()[i]->getConnectedTerritories()[j]->getName()) {
                        territoryAttacked = true;
                    }
                }

                //if the territory has not been attacked advance onto it
                if(territoryAttacked == false) {
                //advance order contents
                //Current player
                //Same player       (unnecessary for this order could have been a null pointer)
                //Attack troops     calculated earlier
                //Source Territory  current iteration of the outer most for loop
                //Target Territory  current iteration of the inner most for loop
                Advance* advance = new Advance(getPlayer(), getPlayer(), numAttackTroops, getPlayer()->getTerritories()[i], getPlayer()->getTerritories()[i]->getConnectedTerritories()[j]);
                //add advance onto orderlist
                getPlayer()->getOrdersList()->add(advance);
                //note what territory is being attacked
                getPlayer()->getPlayerStrategy()->toAttack(getPlayer()->getTerritories()[i]->getConnectedTerritories()[j]);

                }
            }
        }
    }
}

string CheaterPlayerStrategy::getType(){
    return "cheater";
}

//===================================
//------------Aggressive-------------
//===================================
    AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) : player(player){
}

    AggressivePlayerStrategy::~AggressivePlayerStrategy() {delete this->player;}

    Player * AggressivePlayerStrategy::getPlayer() {return this->player;}

    vector<Territory *> AggressivePlayerStrategy::toDefend(Territory *defendingTerritories) {
    getPlayer()->getTerritoriesToDefend().push_back(defendingTerritories);
    cout<< "Defending territory is " << defendingTerritories->getName()<< endl;
    return getPlayer()->getTerritoriesToDefend();
}

    vector<Territory *> AggressivePlayerStrategy::toAttack(Territory *attackingTerritories) {
    getPlayer()->getTerritoriesToAttack().push_back(attackingTerritories);
    cout<< "Attacking territory is " << attackingTerritories->getName()<<endl;
    return getPlayer()->getTerritoriesToAttack();
}

void AggressivePlayerStrategy::issueOrder() {
    //get strong country
    Territory* maxTroopsTerritory = nullptr;
    int maxTroops = -1;
    for(Territory* territory : getPlayer()->getTerritories()) {
        if (territory->getArmies() > maxTroops){
            maxTroops = territory->getArmies();
            maxTroopsTerritory = territory;
        }
    }

    // if reinforcement available, deploy troops on strong country
    if (player->getReinforcements() > 0) {
        std::cout << "aggressive player " << this->player->getName() << " is Deploying " << player->getReinforcements() << " to strongest territory "
                  << maxTroopsTerritory->getName() << std::endl;
    }

    // add order to player's orders list
    player->getOrdersList()->add(new Deploy(player, player, player->getReinforcements(), nullptr, maxTroopsTerritory));

    // looking for the strongest opponent connect to my strongest territory and therefore weaker
    Territory* strongestWeakTerritory = nullptr;
    int biggerOpponent = -1;
    for(Territory* territory : maxTroopsTerritory->getConnectedTerritories()){
        if (territory->getOwner() != getPlayer() && // not the same player
            territory->getArmies() < maxTroopsTerritory->getArmies() && // armies in enemy territory is lesser
            territory->getArmies() > biggerOpponent){ // update max armies in adjacent territories

            strongestWeakTerritory = territory;
            biggerOpponent = territory->getArmies();

            }
    }

    if (hasCard("bomb", getPlayer()) && strongestWeakTerritory){
        Bomb* bomb = new Bomb(getPlayer(), nullptr, 0, maxTroopsTerritory, strongestWeakTerritory);
        getPlayer()->getOrdersList()->add(bomb);
    }
    if (strongestWeakTerritory){
        player->getOrdersList()->add(new Advance(player, strongestWeakTerritory->getOwner(), maxTroopsTerritory->getArmies(), maxTroopsTerritory, strongestWeakTerritory));
    }
}

string AggressivePlayerStrategy::getType() {
    return "aggressive";
}

//===================================
//------------Neutral-------------
//===================================
NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) : player(player){
}

NeutralPlayerStrategy::~NeutralPlayerStrategy() {delete this->player;}

Player * NeutralPlayerStrategy::getPlayer() {
    return this->getPlayer();
}

void NeutralPlayerStrategy::issueOrder() {
}

string NeutralPlayerStrategy::getType() {
    return "neutral";
}

vector<Territory *> NeutralPlayerStrategy::toDefend(Territory *defendingTerritories) {
    // creating strategy and setting neutral player to aggressive player
    PlayerStrategy* strat = createStrategy(this->player, "aggressive");
    this->player->setPlayerStrategy(strat);

    //pushing back territory to defend
    getPlayer()->getTerritoriesToDefend().push_back(defendingTerritories);
    cout << "Neutral Player is under attack, and becomes aggressive" << endl;

    cout<< "Defending territory is " << defendingTerritories->getName()<< endl;

    return getPlayer()->getTerritoriesToDefend();
}

vector<Territory *> NeutralPlayerStrategy::toAttack(Territory *attackingTerritories) {
    getPlayer()->getTerritoriesToAttack().push_back(attackingTerritories);
    cout<< "Attacking territory is " << attackingTerritories->getName()<<endl;
    return getPlayer()->getTerritoriesToAttack();
}





