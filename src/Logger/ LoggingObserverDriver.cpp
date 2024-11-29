//
// Created by Ryad on 2024-11-10.
//

/*

#include "../GameEngine/GameEngine.h"
#include " LoggingObserverDriver.h"
//#include "../Orders/Order.h"

class OrdersList;
void testLoggingObserver() {
    GameEngine game;


    cout << "**********************************\n"
            "*                                *  \n"
            "*         TESTING LOGGER         *  \n"
            "*                                *  \n";
    cout<<  "**********************************\n";

    //testing game engine and state change/ state setup
    while (true) {
        string input;
        cout << "current state : " << game.getCurrentState()->getName() << endl;
        cout << "enter the next state you want to go to" << endl;
        cin >> input;
        if (input != "exit") {game.changeState(input);}
        else {break;}
    }



    // testing order list and order execution -- USING VOID TESTLISTORDERS() function



    // Create a deck and some cards
    Deck* deck = new Deck();
    deck->generateDeck();



    // generating two players
    Player* player1 = new Player( "player1");
    Player* player2 = new Player( "player2");
    vector<Player*> players;
    players.push_back(player1);
    players.push_back(player2);

    //loading a map to show functionality
    MapLoader mapLoader;
    Map loadedMap;
    mapLoader.loadMap(loadedMap,"../res/maps/usa.txt");

    int playerIndex = 0;
    int totalPlayers = players.size();


    Continent* asia = new Continent("Asia", 5);
    Continent* europe = new Continent("Europe", 4);

    Territory* china = new Territory("China", { 0, 0 }, asia, player1, 5);
    Territory* india = new Territory("India", { 1, 0 }, asia, player2, 3);
    Territory* spain = new Territory("Spain", { 1, 1 }, europe, player1, 4);
    Territory* portugal = new Territory("portugal", { 1, 2 }, europe, player2, 2);
    Territory* england = new Territory("England", { 2, 2}, europe, player2, 4);

    india->addConnectedTerritory(china);
    china->addConnectedTerritory(india);
    spain->addConnectedTerritory(china);
    china->addConnectedTerritory(india);

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

    auto advance = new Advance(&game, nullptr, nullptr, 1, nullptr, nullptr);
    auto negotiate = new Negotiate(&game, nullptr, nullptr, 1, nullptr, nullptr);
    negotiate->execute(player1, player2);
    advance->execute(player1, 1, china, india);

    auto list = new OrdersList(&game);
    list->add(advance);
    list->add(negotiate);

    CommandProcessor* commandProcessor = new CommandProcessor(&game);

    while (true) {
        cout << "manually enter a command : ";
        Command* command = commandProcessor->getCommand(&game);
        if (command->getSuccess()) {
            cout << "command was successful : " << command->getCommand() << endl;

            if (command->getType() == GameStart) {
                break;
            }
        }
        else {
            cout << "command was invalid : " << command->getCommand() << endl;
        }
    }
}

*/