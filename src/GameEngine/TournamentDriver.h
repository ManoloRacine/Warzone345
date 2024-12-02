//
// Created by Nektarios on 11/30/2024.
//

#ifndef TOURNAMENTDRIVER_H
#define TOURNAMENTDRIVER_H

#include "GameEngine.h"


void testTournament(GameEngine & game,CommandProcessor & commandProcessor,TournamentSetup tournamentSetup);
void tournamentPlay(GameEngine & game, int maxTurnCount);


#endif //TOURNAMENTDRIVER_H
