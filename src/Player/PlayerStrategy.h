//
// Created by Ryad on 2024-11-26.
//

#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

#include <iostream>
#include <vector>


class PlayerStrategy {
public:
    Player* player;

public:
    virtual void issueOrder() = 0; // to override
    virtual std::vector<Territory *> toDefend() = 0; // to override
    virtual std::vector<Territory *> toAttack() = 0; // to override

    static PlayerStrategy* createStrategy(Player* player, const std::string& strategy); // creation of strategy on demand
};

#endif //PLAYERSTRATEGY_H
