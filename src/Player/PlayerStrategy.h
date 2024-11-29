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
    virtual string getType() = 0; // to override

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
    //function to indicate type
    string getType();    

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
    //function to indicate type
    string getType();  
    vector<Territory*> toDefend(Territory* territory);
    vector<Territory*> toAttack(Territory* territory);
};

class CheaterPlayerStrategy: public PlayerStrategy {
private:
    Player* player;
public:
    //constructor
    CheaterPlayerStrategy(Player* player);
    //destructor
    ~CheaterPlayerStrategy();
    //getter for player
    Player* getPlayer();
    //function to override
    void issueOrder() override;
    //function to indicate type
    string getType();  

    vector<Territory*> toDefend(Territory* territory) override;
    vector<Territory*> toAttack(Territory* territory) override;
};

#endif //PLAYERSTRATEGY_H
