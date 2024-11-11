//
// Created by manol on 9/21/2024.
//
// FSM pattern referenced from https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/
#include <algorithm> // For std::shuffle
#include <random>    // For std::random_device and std::mt19937
#include "GameEngine.h"
#include <iostream>
#include "../Map/Map.h"
#include "../Player/Player.h"
#include <filesystem>

using namespace std;

State GameState::getState() {
    return state;
}

GameState::GameState(State state) : state(state) {}

StartState::StartState() : GameState(Start) {}
MapLoadedState::MapLoadedState() : GameState(MapLoaded) {}
MapValidatedState::MapValidatedState() : GameState(MapValidated) {}
PlayersAddedState::PlayersAddedState() : GameState(PlayersAdded) {}
AssignReinforcementState::AssignReinforcementState() : GameState(AssignReinforcement) {}
IssueOrdersState::IssueOrdersState() : GameState(IssueOrders) {}
ExecuteOrdersState::ExecuteOrdersState() : GameState(ExecuteOrders) {}
WinState::WinState() : GameState(Win) {}

//Changes current game engine state based on input
void StartState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "loadmap") {
        gameEngine->setState(MapLoadedState::getInstance());
    }
    else {
        throw stateInput;
    }
}

string StartState::getName() {
    return "start state";
}

//returns a singleton representing this state
GameState& StartState::getInstance() {
    static StartState instance;
    instance.state = Start;
    return instance;
}

//Changes current game engine state based on input
void MapLoadedState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "loadmap") {
        gameEngine->setState(MapLoadedState::getInstance());
    }
    else if (stateInput == "validatemap") {
        gameEngine->setState(MapValidatedState::getInstance());
    }
    else {
        throw stateInput;
    }
}

string MapLoadedState::getName() {
    return "map loaded state";
}

//returns a singleton representing this state
GameState& MapLoadedState::getInstance() {
    static MapLoadedState instance;
    return instance;
}


//Changes current game engine state based on input
void MapValidatedState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "addplayer") {
        gameEngine->setState(PlayersAddedState::getInstance());
    }
    else {
        throw stateInput;
    }
}

//returns a singleton representing this state
GameState & MapValidatedState::getInstance() {
    static MapValidatedState instance;
    return instance;
}

string MapValidatedState::getName() {
    return "map validated state";
}


//Changes current game engine state based on input
void PlayersAddedState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "addplayer") {
        gameEngine->setState(PlayersAddedState::getInstance());
    }
    else if (stateInput == "gamestart") {
        gameEngine->setState(AssignReinforcementState::getInstance());
    }
    else {
        throw stateInput;
    }
}

//returns a singleton representing this state
GameState & PlayersAddedState::getInstance() {
    static PlayersAddedState instance;
    return instance;
}

string PlayersAddedState::getName() {
    return "players added state";
}


//Changes current game engine state based on input
void AssignReinforcementState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "issueorder") {
        gameEngine->setState(IssueOrdersState::getInstance());
    }
    else {
        throw stateInput;
    }
}

//returns a singleton representing this state
GameState & AssignReinforcementState::getInstance() {
    static AssignReinforcementState instance;
    return instance;
}

string AssignReinforcementState::getName() {
    return "assign reinforcement";
}


//Changes current game engine state based on input
void IssueOrdersState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "issueorder") {
        gameEngine->setState(IssueOrdersState::getInstance());
    }
    else if (stateInput == "endissueorders") {
        gameEngine->setState(ExecuteOrdersState::getInstance());
    }
    else {
        throw stateInput;
    }
}

//returns a singleton representing this state
GameState & IssueOrdersState::getInstance() {
    static IssueOrdersState instance;
    return instance;
}

string IssueOrdersState::getName() {
    return "issue orders";
}


//Changes current game engine state based on input
void ExecuteOrdersState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "execorder") {
        gameEngine->setState(ExecuteOrdersState::getInstance());
    }
    else if (stateInput == "endexecorders") {
        gameEngine->setState(AssignReinforcementState::getInstance());
    }
    else if (stateInput == "win") {
        gameEngine->setState(WinState::getInstance());
    }
    else {
        throw stateInput;
    }
}

//returns a singleton representing this state
GameState & ExecuteOrdersState::getInstance() {
    static ExecuteOrdersState instance;
    return instance;
}

string ExecuteOrdersState::getName() {
    return "execute orders";
}


//Changes current game engine state based on input
void WinState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "play") {
        gameEngine->setState(StartState::getInstance());
    }
    else if (stateInput == "end") {
        exit(0);
    }
    else {
        throw stateInput;
    }
}

//returns a singleton representing this state
GameState & WinState::getInstance() {
    static WinState instance;
    return instance;
}

string WinState::getName() {
    return "win";
}



GameEngine::GameEngine() {
    gameEngineState = &StartState::getInstance();
}

GameState* GameEngine::getCurrentState() const {
    return gameEngineState;
}

void GameEngine::changeState(string stateInput) {
    gameEngineState->changeState(this, stateInput);
}

void GameEngine::setState(GameState &newState) {
    gameEngineState = &newState;
}

GameEngine::GameEngine(const GameEngine &gameEngine) {
    gameEngineState = gameEngine.gameEngineState;
}

GameEngine & GameEngine::operator=(const GameEngine &other) {
    if (this != &other) {
        gameEngineState = other.gameEngineState;
    }

    return *this;
}

std::ostream & operator<<(std::ostream &os, const GameEngine &gameEngine) {
    os << gameEngine.getCurrentState()->getName();
    return os;
}

// --------------------------- A2-PART2 -----------------------------------------

void GameEngine::startupPhase() {
    CommandProcessor commandProcessor; // Create CommandProcessor instance
    std::cout << "Starting game setup. Enter commands:" << std::endl;
    bool isMapLoaded = false;
    bool isMapValid = false;
    bool enoughPlayers = false;

    int playerCount = 0;

    MapLoader mapLoader;
    Map loadedMap;


    // Define the path to the maps directory
    const std::string mapDirectory = "../res/maps/";
    printAllMaps(mapDirectory);

    while (true) {
        Command* command = commandProcessor.getCommand(this);
        std::cout << "getCommand(): " << command->getCommand() << std::endl; // Output the command


        if (command->getType() == Quit) {
            std::cout << "Exiting the game." << std::endl;
            break;
        }

        // Handle LoadMap command
        if (command->getType() == LoadMap) {
            std::string fullCommand = command->getCommand(); // Get the full command
            std::size_t spacePos = fullCommand.find(' '); // Find the position of the first space

            if (spacePos != std::string::npos) {
                std::string filename = fullCommand.substr(spacePos + 1); // Extract the filename after the first space
                std::string selectedMap = mapDirectory + filename; // Construct the full path
                std::cout << "Loading map from: " << selectedMap << std::endl;

                if (isMapLoaded) { cout << "Map Already Loaded." << endl;
                } else {
                    // Load map logic
                    try {
                        mapLoader.loadMap(loadedMap,selectedMap);
                        std::cout << "Map loaded successfully!" << std::endl;
                        isMapLoaded = true;
                        //Set gameMap to loaded map
                        gameMap = new Map(loadedMap);
                        cout << "Current State: " << *this << endl;

                    } catch (const std::exception& e) {
                        std::cerr << "Error loading map: " << e.what() << std::endl;
                    }
                }
            } else {
                std::cerr << "Error: No filename provided for LoadMap command." << std::endl;
            }
        } else if (command->getType() == ValidateMap) {
            std::cout << "Validating map..." << std::endl;
            if (isMapLoaded) {
                bool result = loadedMap.validate(); // Call the validate method
                isMapValid = result;
                std::cout << (result ? "Map is valid." : "Map is invalid.") << std::endl;
                cout << "Current State: " << *this << endl;
            } else {
                std::cout << "No map loaded. Please load a map first." << std::endl;
            }
        } else if (command->getType() == AddPlayer) {
            std::cout << "Adding player..." << std::endl;
            std::string fullCommand = command->getCommand(); // Get the full command
            std::size_t spacePos = fullCommand.find(' '); // Find the position of the first space

            if (spacePos != std::string::npos) {
                std::string playername = fullCommand.substr(spacePos + 1); // Extract the player name after the first space
                if (playerCount < 6) {  // Enforce max player count (6)
                    Player* player = new Player(playername); // Use extracted player name
                    playerList.push_back(player); //Add player pointer to vector
                    playerCount++;
                    if (playerCount > 1) {
                        enoughPlayers = true;
                    }
                    std::cout << "Player " << playername << " added successfully." << std::endl;
                    std::cout << "Player Count: " << playerCount << std::endl;
                } else {
                    std::cout << "Couldn't add player, already at max player count (6)." << std::endl;
                }
            } else {
                std::cerr << "Error: No player name provided for AddPlayer command." << std::endl;
            }
        } else if (command->getType() == GameStart) {
            if (isMapLoaded && isMapValid && enoughPlayers ) {
                std::cout << "Preparing Game..." << std::endl;
                // a) Assign all territories
                assignTerritoriesToPlayers(loadedMap,playerList);
                // b) Determine order of play
                determineOrderOfPlay(playerList);
                // c) Give all player 50 reinforcement units to start
                setReinforcementPools(playerList);
                // d) let each player draw 2 initial cards
                draw2cards(playerList);
                cout << "Game Set Up Succesfull..." << endl;
                cout << "Starting Game..." << endl;
                cout << "Current State: " << *this << endl;

            } else if(!isMapLoaded) {
                cout << "Can't proceed: Map not loaded" << endl;
            }else if(!isMapValid) {
                cout << "Can't proceed: Map not validated" << endl;
            }else if (!enoughPlayers) {
                cout << "Can't proceed: Not enough players" << endl;
            }
        } else if (command->getType() == Invalid) {
            std::cout << "Invalid command!" << std::endl;
        }
    }
}


// Function to assign territories in a round-robin fashion
void GameEngine::assignTerritoriesToPlayers(Map& map, vector<Player*>& players) {

    int playerIndex = 0;
    int totalPlayers = players.size();
//make a for loop that alternates between the players
    // Traverse mapData and assign each territory to a player in round-robin fashion
    for (auto& pair : map.getMapData()) {
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

// Randomly shuffle player list to determine order of play
void GameEngine::determineOrderOfPlay(std::vector<Player*>& players) {
    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    cout << "Shuffling player order..." << endl;

    // Shuffle the players vector to randomize the order
    std::shuffle(players.begin(), players.end(), g);
}
// Give all player 50 reinforcement units to start
void GameEngine::setReinforcementPools(std::vector<Player*>& players) {

    cout << "Adding reinforcements..." << endl;

    for(const auto& player : players) {
        player->setReinforcements(50);
    }
}

//let each player draw 2 initial cards from the deck using the deck’s draw() method
void GameEngine::draw2cards(std::vector<Player*>& players) {

    this->gameDeck = new Deck();
    gameDeck->generateDeck();

    cout<< "CURRENT GAME DECK: " << *gameDeck << endl;

    for(const auto& player : players) {
        cout << player->getName() << " Draws two cards..." << endl;
        player->getHand()->draw(gameDeck);
        player->getHand()->draw(gameDeck);

    }

}


void GameEngine::printAllMaps(const std::string& mapDirectory) {
    std::filesystem::path dir(mapDirectory);

    // Check if the directory exists
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        std::cerr << "Directory does not exist: " << mapDirectory << std::endl;
        return;
    }

    std::cout << "Available maps in directory '" << mapDirectory << "':" << std::endl;

    std::vector<std::string> mapFiles; // Vector to store map filenames

    // Iterate through the directory
    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_regular_file()) { // Check if the entry is a regular file
            mapFiles.push_back(entry.path().filename().string()); // Store the file name
        }
    }

    // Print map filenames as a CSV
    if (!mapFiles.empty()) {
        std::cout << "Maps: ";
        for (size_t i = 0; i < mapFiles.size(); ++i) {
            std::cout << mapFiles[i];
            if (i < mapFiles.size() - 1) {
                std::cout << ", "; // Add a comma for all but the last element
            }
        }
        std::cout << std::endl; // New line after printing all maps
    } else {
        std::cout << "No maps found in directory." << std::endl;
    }
}

//----------------A2-PART3-Griffin-Sin-Chan---------------//


void GameEngine::mainGameLoop() {
    GameEngine game;
    CommandProcessor commandProcessor;
    MapLoader mapLoader;
    Map loadedMap;
    mapLoader.loadMap(loadedMap,"../res/maps/smallAfrica.txt");
    cout << "loadingMap: usa.txt..." << endl;
    game.gameMap = new Map(loadedMap);
    bool result = loadedMap.validate();
    cout << "Map validation is: " << result << endl;
    Player* player1 = new Player("bob");
    game.playerList.push_back(player1);
    cout << "adding player bob" << endl;
    Player* player2 = new Player("sam");
    game.playerList.push_back(player2);
    cout << "adding player sam" << endl;
    cout << "Assigning territories" << endl;
    game.assignTerritoriesToPlayers(loadedMap, game.playerList);
    cout << "Setting Reinforcement pools" << endl;
    //game.setReinforcementPools(game.playerList); gamestart up give 50 troops
    game.draw2cards(game.playerList);
    cout << *player1 << endl;
   // cout << *player2 << endl;
    
    bool play = true;
     while (play) {
        setState(AssignReinforcementState::getInstance());
        game.resetPlayerStatuses(playerList, gameDeck);
        game.reinforcementPhase(loadedMap, game.playerList);
        
        setState(IssueOrdersState::getInstance());
        game.issueOrdersPhase(loadedMap, game.playerList);

        setState(ExecuteOrdersState::getInstance());
        game.orderExecutionPhase(game.playerList);
        

        if (game.playerList.size() <= 1) {
            setState(WinState::getInstance());
            cout << game.playerList[0]->getName() << " wins the game"<< endl;
            play = false;
        }
     }
}
void GameEngine::reinforcementPhase(Map& map, std::vector<Player*>& players) {

    vector<Continent*> continents = map.getContinents();
    
    //Distribute normal number of troops to all players
    cout << "Adding reinforcements..." << endl;
    for(const auto& player : players) {
        //# of territories owned divided by 3, rounded down
        int numTroops = ((player->getTerritories().size())/3);
        player->setReinforcements(numTroops + player->getReinforcements());


        //set minimal troops for player if less than 3
        if (numTroops < 3) {
        player->setReinforcements(2 + player->getReinforcements());
        }
        cout << player->getName() <<" recieves " << player->getReinforcements() << " troops." << endl;
    }


    //Check for continent bonus
    //loop throuh all continents
    for(int i = 0; i < continents.size(); i++) {
        //player ptr to track the current owner of the territory
        //bool to say if the territories are owned by the same player
        Player* tempOwnerPtr = nullptr;
        bool sameOwner = false;
        //loop through all the territories of the current continent
        for (int j = 0; j < continents[i]->getTerritories().size(); j++) {
            //On the first iteration nullptr is changed to the current territories owner
            if (tempOwnerPtr == nullptr) {
                tempOwnerPtr = continents[i]->getTerritories()[j]->getOwner();
            }
            //Check to see if the previous territories owner is the same as the current territories owner
            if (tempOwnerPtr != continents[i]->getTerritories()[j]->getOwner()) {
                //if not true they are not the same owner and break out of the loop
                sameOwner = false;
                break;
            }
            else {
                //the previous owner was the same as the current
                //the loop goes through all of the continents territories
                sameOwner = true;
            }
        }
        //if all territories share the same owner give the continent bonus
        if (sameOwner) {
            //total troops = current troops + continent bonus
            int totalTroops = (tempOwnerPtr->getReinforcements() + continents[i]->getBonus());
            tempOwnerPtr->setReinforcements(totalTroops);
            cout << tempOwnerPtr->getName() <<" recieves a bonus of " << continents[i]->getBonus()<< " troops." <<endl;
        }
    }
}


void GameEngine::issueOrdersPhase(Map& map, std::vector<Player*>& players) {
    
    //Vector storing number players with turn status
    int numPlayers = players.size();
    //create vector with size equal to num players and set true
    vector<bool> playerNotDoneTurn(numPlayers, true);
    vector<bool> playerDoneDeploying(numPlayers, false);
    bool playersIssuingOrders = true;
    bool validOrder = false;
    string choice;
    int numArmies;
    string sourceTerritory;
    string targetTerritory;
    string opposingPlayerName;

    cout<<"Issuing Orders" << endl;
    //While orders are still being issued
    while(playersIssuingOrders) {
        //looping until player puts in a valid order
        //rotate through each player
        for(int i = 0; i < numPlayers; i++) {
            //if player not done issuing orders let them issue order
            if (playerNotDoneTurn[i]) { 
                validOrder = false;
                //loop until current player gives a valid order
                while (!validOrder) {
                    numArmies = 0;
                    // ask user for their order
                    cout << players[i]->getName() << " enter an order: " << endl;
                    // let user put in order
                    cin >> choice;
                    choice = toLower(choice);

                    if (players[i]->getReinforcements() == 0) {
                        playerDoneDeploying[i] = true;
                    }

                    //for user to choose deploy
                    if (!playerDoneDeploying[i]) {
                        if(choice != "deploy") {
                            
                            cout<< "Must deploy all troops First" << endl;
                            i--;
                            break;
                        }
                    }

                    // using user input create a new order
                    
                    //========================================
                    //Deploy Order
                    //========================================
                    if (choice == "deploy"){
                        cout << "Enter number of troops to move:" << endl;
                        cin >> numArmies;
                        if (cin.fail()) {
                            numArmies = 0;
                            cin.clear();
                        }
                        int playerTroops = (players[i]->getReinforcements());

                        if(playerTroops-numArmies < 0) {
                            cout << "Number entered goes beyond the reinforcement pool" << endl;
                            cout << playerTroops << " troops remaining" << endl;
                            i--;
                            break;
                        } 
                            
                        players[i]->setReinforcements(playerTroops-numArmies);
                        cout << "Enter name of target territory:" << endl;
                        getline(cin >> ws, targetTerritory);

                        // the player issuing the order is also the one being affcted by the order, which is why the same player is passed twice
                        // the rest of the inputs are inputted by the user, number of troops to transfer, source territory is unnecessary...null, target territory owned
                        Deploy *deployOrder = new Deploy(players[i], nullptr, numArmies, nullptr, getTerritoryByName(map, targetTerritory));
                        // pass the order onto the current players order list place order inside of the function
                        players[i]->issueOrder(deployOrder);
                        validOrder = true;
                        
                    } 
                    //========================================
                    //Advance Order
                    //========================================
                    else if (choice == "advance") {
                        cout << "Enter number of troops to move:" << endl;
                        cin >> numArmies;
                        if (cin.fail()) {
                            numArmies = 0;
                            cin.clear();
                        }
                        cout << "Enter name of source territory:" << endl;
                        getline(cin >> ws, sourceTerritory);
                        cout << "Enter name of target territory:" << endl;
                        getline(cin >> ws, targetTerritory);


                        // Pass in the current player and the player being attacked
                        // getTerritoryByName(map, targetTerritory)->getOwner()... it gets the owner of the territory being attacked or defended
                        // the rest of the inputs are inputted by the user, number of troops to transfer, from which territory to destination
                        Advance *advanceOrder = new Advance(players[i], nullptr, numArmies, getTerritoryByName(map, sourceTerritory), getTerritoryByName(map, targetTerritory));
                        // pass the order onto the current players order list place order inside of the function
                        players[i]->issueOrder(advanceOrder);
                        validOrder = true;
                    }
                    
                    //========================================
                    //Airlift Order
                    //========================================
                    else if (choice == "airlift") {
                        cout << "Enter number of troops to move:" << endl;
                        cin >> numArmies;
                        if (cin.fail()) {
                            numArmies = 0;
                            cin.clear();
                        }
                        cout << "Enter name of source territory:" << endl;
                        getline(cin >> ws, sourceTerritory);
                        cout << "Enter name of target territory:" << endl;
                        getline(cin >> ws, targetTerritory);


                        // the player issuing the order is also the one being affcted by the order, which is why the same player is passed twice
                        // the rest of the inputs are inputted by the user, number of troops to transfer, from which territory to destination
                        Airlift *airliftOrder = new Airlift(players[i], players[i], numArmies, getTerritoryByName(map, sourceTerritory), getTerritoryByName(map, targetTerritory));
                        // pass the order onto the current players order list place order inside of the function
                        players[i]->issueOrder(airliftOrder);
                        validOrder = true;


                    }
                    //========================================
                    //Bomb Order
                    //========================================
                    else if (choice == "bomb") {
                        cout << "Enter name of target territory:" << endl;
                        getline(cin >> ws, targetTerritory);


                        // the player issuing the order is also the one being affcted by the order, which is way the same player is passed twice
                        // the rest of the inputs are inputted by the user, number of troops to transfer, from which territory to destination
                        Bomb *bombOrder = new Bomb(players[i], players[i], 0, nullptr, getTerritoryByName(map, targetTerritory));
                        // pass the order onto the current players order list place order inside of the function
                        players[i]->issueOrder(bombOrder);
                        validOrder = true;


                    }
                    //========================================
                    //Blockade Order
                    //========================================
                    else if (choice == "blockade") {
                        
                        cout << "Enter name of target territory:" << endl;
                        getline(cin >> ws, targetTerritory);


                        // the player issuing the order is also the one being affcted by the order, which is way the same player is passed twice
                        // the rest of the inputs are inputted by the user, number of troops to transfer, source territory and targte territory are the same
                        Blockade *blockadeOrder = new Blockade(players[i], players[i], 0, getTerritoryByName(map, targetTerritory), getTerritoryByName(map, targetTerritory));
                        // pass the order onto the current players order list place order inside of the function
                        players[i]->issueOrder(blockadeOrder);
                        validOrder = true;


                    }
                    //========================================
                    //Negotiate Order
                    //========================================
                    else if (choice == "negotiate") {
                        cout << "Enter name of player to negotiate with:" << endl;
                        cin >> opposingPlayerName;


                        //negotiate only needs current player and opposing player of choosing
                        Negotiate *negotiateOrder = new Negotiate(players[i], getPlayerByName(players, opposingPlayerName), 0, nullptr, nullptr);
                        // pass the order onto the current players order list place order inside of the function
                        players[i]->issueOrder(negotiateOrder);
                        validOrder = true;

                    }
                    else if (choice == "done") {
                        // player is now done issuing orders
                        playerNotDoneTurn[i] = false;
                        validOrder = true;
                    }

                    bool allPlayersDone = true;
                    // Check if all players are done
                    for (int j = 0; j < numPlayers; j++) {
                        if (playerNotDoneTurn[j]) {
                            allPlayersDone = false;
                            break;
                        }
                    }
                    if (allPlayersDone) {
                        playersIssuingOrders = false;
                    }
                }
            }
        }
    }
}


void GameEngine::orderExecutionPhase(std::vector<Player*>& players) {
    vector<bool> playerNotDoneExecuting(players.size(), true);
    bool execute = true;  
    //First loop through all players orderlist search for deploy orders
    for (int i = 0; i < players.size(); i++) {
        int orderListSize = players[i]->getOrdersList()->getList().size();
        for (int j = 0; j < orderListSize; j++) {
            
            //if the order list size is 0 no orders left skip
            if (orderListSize == 0) {
                playerNotDoneExecuting[i] = false;
                break;
            }

                string order = toLower(players[i]->getOrdersList()->getList()[j]->getLabel());
            if (order == "deploy") {
                cout<<"\n--------------------------  Deploying  --------------------------"<<endl;
                players[i]->getOrdersList()->getList()[j]->validate();
                
                //validate internally calls the excute method if conditions satisfied
                //regardeless of validation remove the deploy order
                players[i]->getOrdersList()->remove(j);
                //move back one index because remove shifted the vector
                j--;
                //track the decreased size to prevent out of bounds
                orderListSize--;

            }
        }   
    }

    //issue round robin players orders

    while(execute) {
        for (int i = 0; i < players.size(); i++) {
            //firstly check if player has any territories
            if (players[i]->getTerritories().empty() || players[i]->getTerritories()[0] == nullptr) {
                //remove the player at the specified index from the vector of player
                players.erase(players.begin()+i);
                break;
            }
            else if(playerNotDoneExecuting[i] == true) {
                if (players[i]->getOrdersList()->getList().size() == 0) {
                    playerNotDoneExecuting[i] = false;  
                } 
                else {
                    //get label to compare with order name later
                    string orderType = toLower(players[i]->getOrdersList()->getList()[0]->getLabel());
                    if (orderType == "advance") {
                        cout<<"\n--------------------------  Advance  --------------------------"<<endl;
                        //validate run excute internally
                        players[i]->getOrdersList()->getList()[0]->validate();

                        //remove the order from the list, pop first element
                        players[i]->getOrdersList()->remove(0);

                        cout<<"inside advance at the end" << endl;
                    }
                    else if (orderType == "airlift") {
                        cout<<"\n--------------------------  Airlift --------------------------"<<endl;
                        players[i]->getOrdersList()->getList()[0]->validate();
                        players[i]->getOrdersList()->remove(0);
                    }
                    else if (orderType == "bomb") {
                        cout<<"\n--------------------------  Bomb  --------------------------"<<endl;
                        players[i]->getOrdersList()->getList()[0]->validate();
                        players[i]->getOrdersList()->remove(0);
                    }
                    else if (orderType == "blockade") {
                        cout<<"\n--------------------------  Blockade  --------------------------"<<endl;
                        players[i]->getOrdersList()->getList()[0]->validate();
                        players[i]->getOrdersList()->remove(0);
                    }
                    else if (orderType == "negotiate") {
                        cout<<"\n--------------------------  Deploying  --------------------------"<<endl;
                        players[i]->getOrdersList()->getList()[0]->validate();
                        players[i]->getOrdersList()->remove(0);
                    }
                }
            }
            bool allPlayersDone = true;
            // Check if all players are done
            for (int j = 0; j < players.size(); j++) {
                if (playerNotDoneExecuting[j] == true) {
                    allPlayersDone = false;
                    break;
                }
            }
            if (allPlayersDone) {
                execute = false;
            }
        }
    }
}


// Function to convert a string to lowercase
string GameEngine::toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return lowerStr;
}

Territory* GameEngine::getTerritoryByName(Map& map, string targetName) {
    //Iterate through the map data
    for (auto& pair : map.getMapData()) {
        //refence second data in pair iterator which is a territory ptr
        Territory* territory = pair.second;

        //if target name matches current iterations name, return the territory ptr
        if(toLower(targetName) == toLower(territory->getName())) {
            return territory;
        }
    }
    //never found return null
    return(nullptr);
}


Player* GameEngine::getPlayerByName(vector<Player*>& players, string targetPlayer) {
        //iterate through all players
        for (auto& player: players) {
       
        //if target player name found in the player list return the player ptr
        if(toLower(targetPlayer) == toLower(player->getName())) {
            return player;
        }
    }
    //never found return null
    return(nullptr);
}

void GameEngine::resetPlayerStatuses(vector<Player*>& players, Deck* deck) {
    for (int i; i < players.size(); i++) {
        //reset concquered territory status
        if (players[i]->getConqueredATerritory() == true) {
            players[i]->getHand()->draw(deck);
            players[i]->setConqueredATerritory(false);
        }
        //initialize some empty vectors
        vector<Territory*>  emptyToAttack = {};
        vector<Territory*>  emptyToDefend = {};
        //set territoies to attack and to defend to empty vectors
        players[i]->setTerritoriesToAttack(emptyToAttack);
        players[i]->setTerritoriesToDefend(emptyToDefend);
        //resets player negotiations
        players[i]->clearNegotiations();
        players[i]->getOrdersList()->getList().clear();
   
    }
}

