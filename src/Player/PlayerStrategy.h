//
// Created by Ryad on 2024-11-26.
//

#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

#include <iostream>
#include <vector>

using namespace std;


class PlayerStrategy {
private:
    Player* player;

public:
    virtual void issueOrder(Order* order) = 0; // to override
    virtual std::vector<Territory*>toDefend(Territory* territory) = 0; // to override
    virtual std::vector<Territory*>toAttack(Territory* territory) = 0; // to override

    static PlayerStrategy* createStrategy(Player* player, const std::string& strategy); // creation of strategy on demand
};

class HumanPlayerStrategy: public PlayerStrategy {
private:
    Player* player;
public:
    //consturctor
    HumanPlayerStrategy(Player* player);
    //destructor
    ~HumanPlayerStrategy();
    //getter for player
    Player* getPlayer();
    //function to override
    void issueOrder(Order* order);
    vector<Territory*> toDefend(Territory* territory);
    vector<Territory*> toAttack(Territory* territory);
};

class BenevolentPlayerStrategy: public PlayerStrategy {
private:
    Player* player;
public:
    BenevolentPlayerStrategy(Player* player);
    ~BenevolentPlayerStrategy();
    void issueOrder(Order* order);
    vector<Territory*> toDefend(Territory* territory);
    vector<Territory*> toAttack(Territory* territory);
};

#endif //PLAYERSTRATEGY_H
