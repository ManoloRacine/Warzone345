//
// Created by manol on 9/21/2024.
//
// FSM pattern referenced from https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/

#include "GameEngine.h"
#include <iostream>
#include "../Map/Map.h"
#include "../Player/Player.h"
#include <filesystem>
using namespace std;

State GameState::getState() {
    return state;
}


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

    while (true) {
        Command* command = commandProcessor.getCommand(this);
        std::cout << "getCommand(): " << command->getCommand() << std::endl; // Output the command

        if (command->getType() == Quit) {
            std::cout << "Exiting the game." << std::endl;
            delete command; // Clean up command
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

                // Load map logic
                try {
                    mapLoader.loadMap(loadedMap,selectedMap);
                    std::cout << "Map loaded successfully!" << std::endl;
                    //cout << loadedMap;
                    isMapLoaded = true;
                } catch (const std::exception& e) {
                    std::cerr << "Error loading map: " << e.what() << std::endl;
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
                std::cout << "Starting the game..." << std::endl;
                assignTerritoriesToPlayers(loadedMap,playerList);

            } else if(!isMapLoaded) {
                cout << "Map not loaded" << endl;
            }else if(!isMapValid) {
                cout << "Map not validated" << endl;
            }else if (!enoughPlayers) {
                cout << "Not enough players" << endl;
            }
            // Start game logic here
        } else if (command->getType() == Invalid) {
            std::cout << "Invalid command!" << std::endl;
        }
        // Clean up command
        delete command;
    }
}


// Function to assign territories in a round-robin fashion
void GameEngine::assignTerritoriesToPlayers(Map& map, vector<Player*>& players) {

    int playerIndex = 0;
    int totalPlayers = players.size();

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
