#include "PlayerStrategiesDriver.h"
#include "PlayerStrategy.h"
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>


void testPlayerStrategies() {
    GameEngine game;
    CommandProcessor commandProcessor;
    MapLoader mapLoader;
    Map loadedMap;
    mapLoader.loadMap(loadedMap,"../res/maps/smallAfrica.txt");
   
    game.gameMap = new Map(loadedMap);
    bool result = loadedMap.validate();
    cout << "Map validation is: " << result << endl;
    //Player* player1 = new Player("bob", "human");
    //Player* player2 = new Player("kevin", "aggressive");
    Player* player3 = new Player("jeremy", "benevolent");
    //Player* player4 = new Player("louis", "neutral");
    Player* player5 = new Player("simon", "cheater");
    //game.playerList.push_back(player1);
    cout << "adding player bob" << endl;
    
    //game.playerList.push_back(player2);
    cout << "adding player kevin" << endl;
    
    game.playerList.push_back(player3);
    cout << "adding player jeremey" << endl;
   
    //game.playerList.push_back(player4);
    cout << "adding player louis" << endl;
   
    game.playerList.push_back(player5);
    cout << "adding player simon" << endl;
   
    game.assignTerritoriesToPlayers(loadedMap, game.playerList);
    cout << "Setting Reinforcement pools" << endl;
    //game.setReinforcementPools(game.playerList); gamestart up give 50 troops
    Deck* deck = new Deck();
    deck->generateDeck();
   // player1->getHand()->draw(deck);
   // player1->getHand()->draw(deck);
    //player2->getHand()->draw(deck);
   // player2->getHand()->draw(deck); */
    player3->getHand()->draw(deck);
    player3->getHand()->draw(deck);
   // player4->getHand()->draw(deck);
   // player4->getHand()->draw(deck);
    player5->getHand()->draw(deck);
    player5->getHand()->draw(deck);


  //  cout << *player1 << endl;

    bool play = true;
     while (play) {
       
        game.resetPlayerStatuses(game.playerList, deck);
        cout << "PLAYER RESET" << endl;

        game.reinforcementPhase(loadedMap, game.playerList);
        cout << "END OF REINFORCEMENT" << endl;
        
        game.issueOrdersPhase(loadedMap, game.playerList);
        cout << "END OF ISSUE ORDERS" << endl;

        game.orderExecutionPhase(game.playerList);
        cout << "END OF ORDER EXECUTION" << endl;

        if (game.playerList.size() <= 1) {
            cout << game.playerList[0]->getName() << " wins the game"<< endl;
            play = false;
        }
     }
}