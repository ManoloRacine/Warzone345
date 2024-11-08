

#include "../Orders/Order.h"
#include "../Orders/OrderDriver.h"
#include "../GameEngine/GameEngine.h"


void testOrdersLists()
{

    // Create a deck and some cards
    Deck* deck = new Deck();
    deck->generateDeck();

    // generating two players
    Player* player1 = new Player("player1");
    Player* player2 = new Player("player2");
    vector<Player*> players;
    players.push_back(player1);
    players.push_back(player2);

    //loading a map to show functionality
    MapLoader mapLoader;
    Map loadedMap;
    mapLoader.loadMap(loadedMap,"../res/maps/usa.txt");

   int playerIndex = 0;
    int totalPlayers = players.size();

    // Traverse mapData and assign each territory to a player in round-robin fashion
    for (auto& pair : loadedMap.getMapData()) {
        Territory* territory = pair.second;

        // Assign the territory to the current player
        territory->setOwner(players[playerIndex]);
        players[playerIndex]->addTerritories(territory);

        // Print assignment (for debugging or confirmation)
        std::cout << "Assigned territory " << pair.first
                  << " to player " << players[playerIndex]->getName() << std::endl;

        // Move to the next player (round-robin)
        playerIndex = (playerIndex + 1) % totalPlayers;
    }
    

    

}