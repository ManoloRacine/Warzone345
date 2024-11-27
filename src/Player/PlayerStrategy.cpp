//
// Created by Ryad on 2024-11-26.
//

#include "Player.h"
#include "PlayerStrategy.h"

PlayerStrategy* PlayerStrategy::createStrategy(Player *player, const std::string& strategy) {

    std::string strategy_name;
    for(auto& c : strategy){strategy_name += (char)std::tolower(c);} // to lower case for comparaison

    if(strategy_name == "human") {
        return new Human(player);
    } else if(strategy_name == "aggressive") {
        return new Aggressive(player);
    } else if(strategy_name == "benevolent") {
        return new Benevolent(player);
    } else if(strategy_name == "neutral") {
        return new Neutral(player);
    } else if (strategy_name == "cheater") {
        return new Cheater(player);
    } else {
        throw std::runtime_error("no such strategy");
    }
}