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
    virtual void issueOrder() = 0; // to override
    virtual std::vector<Territory*>toDefend(Territory* territory) = 0; // to override
    virtual std::vector<Territory*>toAttack(Territory* territory) = 0; // to override

    static PlayerStrategy* createStrategy(Player* player, const std::string& strategy); // creation of strategy on demand
};

class HumanPlayerStrategy: public PlayerStrategy {
private:
    Player* player;
public:
    //constructor
    HumanPlayerStrategy(Player* player);
    //destructor
    ~HumanPlayerStrategy();
    //getter for player
    Player* getPlayer();
    //function to override
    void issueOrder() override;

    vector<Territory*> toDefend(Territory* territory) override;
    vector<Territory*> toAttack(Territory* territory) override;
};

class BenevolentPlayerStrategy: public PlayerStrategy {
private:
    Player* player;
public:
    //constructor
    BenevolentPlayerStrategy(Player* player);
    //destructor
    ~BenevolentPlayerStrategy();
    //getter for player
    Player* getPlayer();
    //function to override
    void issueOrder();
    vector<Territory*> toDefend(Territory* territory);
    vector<Territory*> toAttack(Territory* territory);
};

#endif //PLAYERSTRATEGY_H
