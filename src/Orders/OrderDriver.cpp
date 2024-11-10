

#include "../Orders/Order.h"
#include "../Orders/OrderDriver.h"
#include "../GameEngine/GameEngine.h"


void testOrdersLists()
{
    //creation of the players and game
    GameEngine game;
    MapLoader mapLoader;
    Map loadedMap;
    mapLoader.loadMap(loadedMap,"../res/maps/usa.txt");
    cout << "loadingMap: usa.txt..." << endl;
    game.gameMap = new Map(loadedMap);
    bool result = loadedMap.validate();
    cout << "Map validation is: " << result << endl;
    Player* player1 = new Player("Logan");
    game.playerList.push_back(player1);
    cout << "adding player Logan" << endl;
    Player* player2 = new Player("Sam");
    game.playerList.push_back(player2);
    cout << "adding player sam" << endl;
    cout << "Setting Reinforcement pools" << endl;
    game.setReinforcementPools(game.playerList);
    //game.draw2cards(game.playerList);

      // Create a deck and some cards
    Deck* deck = new Deck();
    deck->generateDeck();

    //adding cards to players hand
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);

    //creation of a mini map for testing purposes
    Continent* asia = new Continent("Asia", 5);
    Continent* europe = new Continent("Europe", 4);

    Territory* china = new Territory("Lousiana", { 0, 0 }, asia, player1, 50);
    Territory* india = new Territory("Arkansas", { 1, 0 }, asia, player2, 2);
    Territory* spain = new Territory("Missouri", { 1, 1 }, europe, player1, 4);
    Territory* portugal = new Territory("Detroit", { 1, 2 }, europe, player2, 2);
    Territory* england = new Territory("England", { 2, 2}, europe, player1, 4);
    Territory* romania = new Territory("Kansas", { 1, 3 }, europe, player1, 10);

    india->addConnectedTerritory(china);
    china->addConnectedTerritory(india);
    spain->addConnectedTerritory(china);
    spain->addConnectedTerritory(china);
    china->addConnectedTerritory(portugal);
    portugal->addConnectedTerritory(china);

    player1->addTerritories(china);
    player2->addTerritories(india);
    player1->addTerritories(spain);
    player2->addTerritories(portugal);
    player1->addTerritories(england);
    player1->addTerritories(romania);
    
    //creation of orders
    Deploy *deployOrder1 = new Deploy(player1, nullptr, 4, nullptr, china);
    Advance *advanceOrder = new Advance(player1, player2, 4, china, india);
    Bomb *bombOrder = new Bomb(player1, player2, 4, india, china);
    Airlift *airliftOrder = new Airlift(player1, nullptr, 2, china, spain);
    Blockade *blockadeOrder = new Blockade(player1, nullptr, 0, romania, romania);
    Negotiate *negotiate = new Negotiate(player1, player2, 0, nullptr, nullptr);
    Advance *advanceOrder2 = new Advance(player1, player2, 0, china, nullptr);

    //demonstrating the Orders
    cout << "\nOrder's start below:" << endl;

    cout << "\nAirlift Order:"<< endl;
    airliftOrder->validate(player1, 2, spain, england);

    cout << "\nBomb Order:"<< endl;
    bombOrder->validate(player1, india);

    cout << "\nBlockade Order:" << endl;
    blockadeOrder->validate(player1, romania);
    cout << romania->getName() << " is now owned by " << romania->getOwner()->getName() << endl;

    cout << "\nDeploy Order:"<< endl;
    deployOrder1->validate(player1, 4, china);

    cout << "\nAdvance Order:"<< endl;
    advanceOrder->validate(player1, 8, china, india);

    cout << "\nNegociate Order:"<< endl;
    negotiate->validate(player1, player2);

    cout << "\nAdvance Order:"<< endl;
    advanceOrder2->validate(player1,1,china, portugal);

   //end of turn
   cout << "\nEnd of turn" << endl;
   game.resetPlayerStatuses(game.playerList, deck); 
   
   //cleanup for memory
    delete deployOrder1;
    delete advanceOrder;
    delete bombOrder;
    delete airliftOrder;
    delete blockadeOrder;
    delete negotiate;
    delete advanceOrder2;
    delete asia;
    delete europe;
    delete player1;
    delete player2;
    delete deck;

}