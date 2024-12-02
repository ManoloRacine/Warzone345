//
// Created by Nektarios on 11/30/2024.
//

#ifndef TOURNAMENTDRIVER_H
#define TOURNAMENTDRIVER_H

#include "GameEngine.h"


void testTournament(GameEngine & game,CommandProcessor & commandProcessor,TournamentSetup tournamentSetup);
void tournamentPlay(GameEngine & game, int maxTurnCount,vector<string>& winners);
void printMode(const TournamentSetup & tournamentSetup);
void printVictory(int nbMaps,int nBGames,vector<string>& winners);


#endif //TOURNAMENTDRIVER_H
