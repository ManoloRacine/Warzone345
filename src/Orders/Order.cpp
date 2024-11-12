
#include <stdexcept>
#include <algorithm>
#include "Order.h"
#include "../GameEngine/GameEngine.h"
using namespace std;

//Constructor, Destructor and << override
Order::Order(){}
Order::~Order() = default;
std::ostream &operator<<(std::ostream &stream, const Order &o) { return o.orderCout(stream); }



//Parameterized constructor for common attributes
    Order::Order(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
        : user(user), targeted(targeted), troops(troops), source(source), target(target){}



//order list

OrdersList::OrdersList(GameEngine *gameEngine) : game(gameEngine){
  Subject::attach((ILogObserver*)game->logObserver);
}


OrdersList::~OrdersList(){ for(auto order: orders){ delete order; } }

OrdersList::OrdersList(const OrdersList &oldList){
  unsigned listLength = oldList.orders.size();
  orders = std::vector<Order *>(listLength);
  this->game = oldList.game;
  for (unsigned o = 0; o < listLength; o++) {
    orders[o] = oldList.orders[o]->clone();
  }
  // subscribe new object to subscribers
  Subject::attach((ILogObserver*)game->logObserver);
}

void OrdersList::add(Order *o){
  if(o){
    orders.push_back(o);
  } else {
    throw std::runtime_error("NULL value inserted in the list");
  }
  Subject::notify(this); // log that order is added
}


void OrdersList::remove(int pos){
  unsigned listLength = orders.size();
  if (listLength == 0){
    throw std::runtime_error("order list empty");
  }
  else if (pos >= listLength || pos < 0) {
    throw std::runtime_error("please try again, invalid entry");
  }
  else{
    delete orders[pos];
    orders.erase(orders.begin() + pos);
  }
}

void OrdersList::move(int pos1, int pos2){
  unsigned listLength = orders.size();
  if (listLength == 0){
    std::cout << "order list empty" << std::endl;
  }
  else if (listLength == 1){
    throw std::runtime_error("only 1 order in the list");
  }
  else if (pos1 >= listLength || pos2 >= listLength || pos1 < 0 || pos2 < 0){
    throw std::runtime_error("0 or 1 valid positon, please try again");
  }
  else{
    Order *temp = orders[pos1];
    orders[pos1] = orders[pos2];
    orders[pos2] = temp;
  }
}


//to copy list object
OrdersList &OrdersList::operator=(const OrdersList &copyList){
  if (&copyList == this){
    return *this;
  }

  unsigned initialListLength = orders.size();
  unsigned copyListLength = copyList.orders.size();

  for (int o = 0; o < initialListLength; o++) { 
    delete orders[o]; 
  }
  orders = std::vector<Order *>(copyListLength);


  for (int i = 0; i < copyListLength; i++) {
    orders[i] = copyList.orders[i]->clone();
  }

  return *this;
}



std::vector<Order*> OrdersList::getList() const {
    return orders;
}

//========================================
//Deploy Order
//========================================
Deploy::~Deploy() = default;
ostream &Deploy::orderCout(ostream &output) const {
  return output << "Deploy order";
}
//constructor
Deploy::Deploy(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

Deploy::Deploy(GameEngine* game, Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : game(game), user(user), targeted(targeted), troops(troops), source(source), target(target){Subject::attach((ILogObserver*)game->logObserver);}

//Getters and setters for user
Player* Deploy::getUser() const{
  return user;
}

void Deploy::setUser(Player* newUser){
  user = newUser;
}

//Getters and setters for targeted
Player* Deploy::getTargeted() const{
  return targeted;
}

void Deploy::setTargeted(Player* newTargeted){
  targeted = newTargeted;
}

//Getters and setters for Troops
int Deploy::getTroops() const{
  return troops;
}

void Deploy::setTroops(int newTroops){
  troops = newTroops;
}

//Getters and setters for target
Territory* Deploy::getTarget() const{
  return target;
}

void Deploy::setTarget(Territory* newTarget){
  target = newTarget;
}

//Getters and setters for source
Territory* Deploy::getSource() const{
  return source;
}

void Deploy::setSource(Territory* newSource){
  source = newSource;
}

  //get label
  string Deploy::getLabel() const {
  return "deploy";
  }

//Validate method for deploy
bool Deploy::validate(Player* player, int armies, Territory* target){
  if(find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end()){
      cout << "Deployment Valid" << endl;
      execute(player, armies, target);
      return true;
 }
  else
    cout << "Order Invalid" << endl;
    return false;
    
}

  bool Deploy::validate(){
  Player* player = getUser();
  int armies = getTroops();
  Territory* target = getTarget();

  // Null checks to prevent dereferencing nullptrs
  if (!player || !target) {
    std::cout << "Deploy Order Invalid: Null pointers detected." << std::endl;
    return false;
  }

  if(find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end()){
      cout << "Deployment Valid" << endl;
      execute(player, armies, target);
      return true;
 }
  else
    cout << "Order Invalid" << endl;
    return false; 
}
//Overriden execute function that performs the execution
void Deploy::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target){
    target->setArmies(target->getArmies()+armies);
    user->toDefend(target);
    cout << "Troops deployed" << endl;
    Subject::notify(this);
}
//Helper method for execute method
void Deploy::execute(Player* player, int armies, Territory* target){
  execute(player, player, armies, target, target);
}
//Overriden execute function
void Deploy::execute(){
  cout << "Please Pass parameters in the form (Player* player, int armies, Territory* target)" << endl;
}

Order *Deploy::clone() const {
  return new Deploy(*this);
}

//========================================
//Advance Order
//========================================
std::ostream &Advance::orderCout(std::ostream &output) const { return output << "Advance order"; }
Advance::~Advance() = default;

Advance::Advance(GameEngine* game,Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : game(game), user(user), targeted(targeted), troops(troops), source(source), target(target){Subject::attach((ILogObserver*)game->logObserver);}


Advance::Advance(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

    //Getters and setters for user
Player* Advance::getUser() const{
  return user;
}

void Advance::setUser(Player* newUser){
  user = newUser;
}

//Getters and setters for targeted
Player* Advance::getTargeted() const{
  return targeted;
}

void Advance::setTargeted(Player* newTargeted){
  targeted = newTargeted;
}

//Getters and setters for Troops
int Advance::getTroops() const{
  return troops;
}

void Advance::setTroops(int newTroops){
  troops = newTroops;
}

//Getters and setters for target
Territory* Advance::getTarget() const{
  return target;
}

void Advance::setTarget(Territory* newTarget){
  target = newTarget;
}

//Getters and setters for source
Territory* Advance::getSource() const{
  return source;
}

void Advance::setSource(Territory* newSource){
  source = newSource;
}

//get label
string Advance::getLabel() const{
return "advance";
}


//Validate method for Advance
bool Advance::validate(Player* player, int armies, Territory* source, Territory* target){
  if(find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end() 
  && find(source->getConnectedTerritories().begin(), source->getConnectedTerritories().end(), target) != source->getConnectedTerritories().end() 
  && armies <= source->getArmies() 
  && !player->isNegotiatedWith(target->getOwner())){
    cout << "Advance Order is Valid" << endl;
    execute(player, armies, source, target);
    return true;
  }
  else
    cout << "Advance Order Invalid" << endl;
    return false;
}

//validate for advance using getters
bool Advance::validate(){
  Player* player = getUser();
  int armies = getTroops();
  Territory* source = getSource();
  Territory* target = getTarget();

  // Null checks to prevent dereferencing nullptrs
  if (!player || !source || !target) {
    std::cout << "Advance Order Invalid: Null pointers detected." << std::endl;
    return false;
  }

  if(find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end() 
  && find(source->getConnectedTerritories().begin(), source->getConnectedTerritories().end(), target) != source->getConnectedTerritories().end() 
  && armies <= source->getArmies() 
  && !player->isNegotiatedWith(target->getOwner())){
    cout << "Advance Order is Valid" << endl;
    execute(player, armies, source, target);
    return true;
  }
  else
    cout << "Advance Order Invalid" << endl;
    return false;
}
//Overriden execute function that performs the execution
void Advance::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target){
    if(user == targeted){
      source->setArmies(source->getArmies()-armies);
      target->setArmies(target->getArmies()+armies);
      user->toDefend(target);
      cout << target->getName() << " Now has " << target->getArmies() << " occupying it" << endl;
      
    }
    else if(user != targeted){
      user->toAttack(target);
      int attackingUnits = armies;
      int defendingUnits = target->getArmies();
      int attackingLosses = 0;
      int defendingLosses = 0;

       for (int i = 0; i < attackingUnits; ++i) {
         if (rand() % 100 < 60) {
            defendingLosses++;
         }
        }
      for (int j = 0; j < defendingUnits; ++j) {
         if (rand() % 100 < 70) {
            attackingLosses++;
          }
      }

      if(source->getArmies()-attackingLosses >= 0){
        source->setArmies(source->getArmies()-attackingLosses);
      }
      else{
        source->setArmies(0);
      }
      if(target->getArmies()-defendingLosses >= 0){
        target->setArmies(target->getArmies()-defendingLosses);
      }
      else{
        target->setArmies(0);
      }

      if(target->getArmies() == 0){
        target->getOwner()->removeTerritories(target);
        target->setOwner(user);
        user->addTerritories(target);
        user->setConqueredATerritory(true);

        target->setArmies(attackingUnits-attackingLosses);
        source->setArmies(source->getArmies()-(attackingUnits-attackingLosses));
        cout << "Territory " << target->getName() << " conquered by " << user->getName() << endl;
      }
      else{
        cout << "Attack Failed " << target->getName() << " remains in " << source->getName() << "'s possession." << endl;
      }

    }
    Subject::notify(this);
}

//Helper Function for execute
void Advance::execute(Player* player, int armies, Territory* source, Territory* target){
  execute(player, target->getOwner(), armies, source, target);
}
//Overrriden Execute
void Advance::execute(){
  cout << "Please Pass parameters in the form (Player* player, int armies, Territory* source, Territory* target)" << endl;
}

Order *Advance::clone() const { return new Advance(*this); }


//========================================
//Airlift Order
//========================================
Airlift::~Airlift() = default;

//constructor
Airlift::Airlift(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

Airlift::Airlift(GameEngine *gameEng, Player *user, Player *targeted, int troops, Territory *source,
  Territory *target): game(gameEng), user(user), targeted(targeted), troops(troops), source(source), target(target){
  Subject::attach((ILogObserver*)game->logObserver);
}

    //Getters and setters for user
Player* Airlift::getUser() const{
  return user;
}

void Airlift::setUser(Player* newUser){
  user = newUser;
}

//Getters and setters for targeted
Player* Airlift::getTargeted() const{
  return targeted;
}

void Airlift::setTargeted(Player* newTargeted){
  targeted = newTargeted;
}

//Getters and setters for Troops
int Airlift::getTroops() const{
  return troops;
}

void Airlift::setTroops(int newTroops){
  troops = newTroops;
}

//Getters and setters for target
Territory* Airlift::getTarget() const{
  return target;
}

void Airlift::setTarget(Territory* newTarget){
  target = newTarget;
}

//Getters and setters for source
Territory* Airlift::getSource() const{
  return source;
}

void Airlift::setSource(Territory* newSource){
  source = newSource;
}

//get label
string Airlift::getLabel() const{
  return "airlift";
}

ostream &Airlift::orderCout(ostream &output) const { return output << "Airlift order"; }
//validation for airlift
bool Airlift::validate(Player* player, int armies, Territory* source, Territory* target) {
  if(source->getOwner()->getName() == target->getOwner()->getName()
    && armies <= source->getArmies()
    && hasCard("airlift", player)){
      cout << "AirLift Order Validated" << endl;
      execute(player, armies, source, target);
      return true;
  }
  else{
    cout << "Airlift order Invalid" << endl;
    return false;
  }
  
}
//validation using getters
bool Airlift::validate() {
  Player* player = getUser();
  int armies = getTroops();
  Territory* source = getSource();
  Territory* target = getTarget();

  // Null checks to prevent dereferencing nullptrs
  if (!player || !source || !target) {
    std::cout << "Airlift Order Invalid: Null pointers detected." << std::endl;
    return false;
  }

  if(source->getOwner() == target->getOwner()
    && armies <= source->getArmies()
    && hasCard("airlift", player)){
      cout << "AirLift Order Validated" << endl;
      execute(player, armies, source, target);
      return true;
  }
  else{
    cout << "Airlift order Invalid" << endl;
    return false;
  }
  
}
//execution of the airlift order
void Airlift::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target){
  user->toDefend(target);
  source->setArmies(source->getArmies()-armies);
  target->setArmies(target->getArmies()+armies);
  Subject::notify(this);
  cout << armies <<" Troops have successfully been Airlifted from " << source->getName() << " to " << target->getName() << endl;
}
//Helper function for execute
void Airlift::execute(Player* player, int armies, Territory* source, Territory* target){
  execute(player, player, armies, source, target);
}
//Overrriden Execute
void Airlift::execute(){
  cout << "Please Pass parameters in the form (Player* player, int armies, Territory* source, Territory* target)" << endl;
}

Order *Airlift::clone() const { return new Airlift(*this); }


//========================================
//Bomb Order
//========================================

// constructor for bomb
Bomb::Bomb(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

Bomb::Bomb(GameEngine* gameEng, Player* user, Player* targeted, int troops, Territory* source, Territory* target)
  : game(gameEng), user(user), targeted(targeted), troops(troops), source(source), target(target) {Subject::attach((ILogObserver*)game->logObserver);}

//destructor for bomb
Bomb::~Bomb() = default;

std::ostream &Bomb::orderCout(std::ostream &output) const { return output << "Bomb order"; }

//Getters and setters for user
Player* Bomb::getUser() const{
  return user;
}

void Bomb::setUser(Player* newUser){
  user = newUser;
}

//Getters and setters for targeted
Player* Bomb::getTargeted() const{
  return targeted;
}

void Bomb::setTargeted(Player* newTargeted){
  targeted = newTargeted;
}

//Getters and setters for Troops
int Bomb::getTroops() const{
  return troops;
}

void Bomb::setTroops(int newTroops){
  troops = newTroops;
}

//Getters and setters for target
Territory* Bomb::getTarget() const{
  return target;
}

void Bomb::setTarget(Territory* newTarget){
  target = newTarget;
}

//Getters and setters for source
Territory* Bomb::getSource() const{
  return source;
}

void Bomb::setSource(Territory* newSource){
  source = newSource;
}

//get label
string Bomb::getLabel() const{
  return "bomb";
}

//validation for bomb
bool Bomb::validate(Player* user, Territory* target){
  bool adjacent = false;
  for(int i = 0; i < target->getConnectedTerritories().size(); i++){
    if(target->getConnectedTerritories()[i]->getOwner() == user){
      adjacent = true;
    }
  }

  if(adjacent 
  && find(user->getTerritories().begin(), user->getTerritories().end(), target) != user->getTerritories().end() 
  && !user->isNegotiatedWith(target->getOwner())
  && hasCard("bomb", user) ){
    cout << "Bomb order Valid" << endl;
    execute(user, target);
    return true;
  }
  cout << "Bomb invalid" << endl;
return false;
}

//validation for bomb
bool Bomb::validate(){
  Player* player = getUser();
  Territory* target = getTarget();

  // Null checks to prevent dereferencing nullptrs
  if (!player || !target) {
    std::cout << "Bomb Order Invalid: Null pointers detected." << std::endl;
    return false;
  }
  
  bool adjacent = false;
  for(int i = 0; i < target->getConnectedTerritories().size(); i++){
    if(target->getConnectedTerritories()[i]->getOwner() == user){
      adjacent = true;
    }
  }

  if(adjacent 
  && find(user->getTerritories().begin(), user->getTerritories().end(), target) != user->getTerritories().end() 
  && !user->isNegotiatedWith(target->getOwner())
  && hasCard("bomb", user) ){
    cout << "Bomb order Valid" << endl;
    execute(user, target);
    return true;
  }
  cout << "Bomb invalid" << endl;
return false;
}
//execution of the Bomb order
void Bomb::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target){
  target->setArmies(target->getArmies()/2);
  cout << target->getName() << " has been bombed by " << user->getName() << ". It now has " << target->getArmies() << " troops remaining" << endl;
  Subject::notify(this);
}

//helper function for bomb order
void Bomb::execute(Player* user, Territory* target){
  execute(user, nullptr, 0, nullptr, target);
}

//overridden execute
void Bomb::execute(){
  cout << "Please Pass parameters in the form (Player* user, Territory* target)" << endl;
}

Order *Bomb::clone() const { return new Bomb(*this); }


//========================================
//Blockade Order
//========================================

//Constructor
Blockade::Blockade(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

Blockade::Blockade(GameEngine* gameEng, Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : game(gameEng), user(user), targeted(targeted), troops(troops), source(source), target(target){Subject::attach((ILogObserver*)game->logObserver);}



//destructor
Blockade::~Blockade() = default;

//Getters and setters for user
Player* Blockade::getUser() const{
  return user;
}

void Blockade::setUser(Player* newUser){
  user = newUser;
}

//Getters and setters for targeted
Player* Blockade::getTargeted() const{
  return targeted;
}

void Blockade::setTargeted(Player* newTargeted){
  targeted = newTargeted;
}

//Getters and setters for Troops
int Blockade::getTroops() const{
  return troops;
}

void Blockade::setTroops(int newTroops){
  troops = newTroops;
}

//Getters and setters for target
Territory* Blockade::getTarget() const{
  return target;
}

void Blockade::setTarget(Territory* newTarget){
  target = newTarget;
}

//Getters and setters for source
Territory* Blockade::getSource() const{
  return source;
}

void Blockade::setSource(Territory* newSource){
  source = newSource;
}

//get label
string Blockade::getLabel() const{
  return "blockade";
}


std::ostream &Blockade::orderCout(std::ostream &output) const { return output << "Blockade order"; }

//validate Blockade order
bool Blockade::validate(Player* player, Territory* source){
  if(find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end() 
  && hasCard("blockade", player)){
    cout << "Blockade Validated" << endl;
    execute(player, source);
    return true;
  }
  cout << "Blockade invalid" << endl;
  return false;
}

//validate Blockade order
bool Blockade::validate(){
  Player* player = getUser();
  Territory* source = getSource();

  // Null checks to prevent dereferencing nullptrs
  if (!player || !source) {
    std::cout << "Blockade Order Invalid: Null pointers detected." << std::endl;
    return false;
  }
  
  if(find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end() 
  && hasCard("blockade", player)){
    cout << "Blockade Validated" << endl;
    execute(player, source);
    return true;
  }
  cout << "Blockade invalid" << endl;
  return false;
}

//creation of the neutral player
static Player* neutral = new Player("neutral");


//execute the blockade function
void Blockade::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) {
  source->getOwner()->removeTerritories(source);
  source->setArmies(source->getArmies()*2);
  source->setOwner(neutral);
  neutral->addTerritories(source);
  Subject::notify(this);
  cout << "Blockade has been made on " << source->getName() << " with " << source->getArmies() << " troops." << endl;
}

//helper function for execute
void Blockade::execute(Player* user, Territory* source){
  execute(user, nullptr, 0, source, nullptr);
}

//overridden execute
void Blockade::execute(){
  cout << "Please Pass parameters in the form (Player* user, Territory* source)" << endl;
}

Order *Blockade::clone() const { return new Blockade(*this); }


//========================================
//Negotiate Order
//========================================

//constructor
Negotiate::Negotiate(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

Negotiate::Negotiate(GameEngine *gameEng, Player *user, Player *targeted, int troops, Territory *source,
  Territory *target): game(gameEng), user(user), targeted(targeted), troops(troops), source(source), target(target){
  Subject::attach((ILogObserver*)game->logObserver);
}
  
//destructor
Negotiate::~Negotiate() = default;

//Getters and setters for user
Player* Negotiate::getUser() const{
  return user;
}

void Negotiate::setUser(Player* newUser){
  user = newUser;
}

//Getters and setters for targeted
Player* Negotiate::getTargeted() const{
  return targeted;
}

void Negotiate::setTargeted(Player* newTargeted){
  targeted = newTargeted;
}

//Getters and setters for Troops
int Negotiate::getTroops() const{
  return troops;
}

void Negotiate::setTroops(int newTroops){
  troops = newTroops;
}

//Getters and setters for target
Territory* Negotiate::getTarget() const{
  return target;
}

void Negotiate::setTarget(Territory* newTarget){
  target = newTarget;
}

//Getters and setters for source
Territory* Negotiate::getSource() const{
  return source;
}

void Negotiate::setSource(Territory* newSource){
  source = newSource;
}

//get label
string Negotiate::getLabel() const{
  return "negotiate";
}
//Validation for Negotiate
bool Negotiate::validate(Player* user, Player* targeted){
  if (user != targeted 
  && hasCard("diplomacy", user)){
    cout << "Negotiation valid" << endl;
    execute(user, targeted);
    return true;
  }
  cout << "Negotiation invalid" << endl;
  return false;
}


bool Negotiate::validate(){
  Player* user = getUser();
  Player* targeted = getTargeted();

  // Null checks to prevent dereferencing nullptrs
  if (!user || !targeted) {
    std::cout << "Advance Order Invalid: Null pointers detected." << std::endl;
    return false;
  }
  
  if (user->getName() != targeted->getName()
   &&hasCard("diplomacy", user)){
    cout << "Negotiation valid" << endl;
    execute(user, targeted);
    return true;
  }
  cout << "Negotiation invalid" << endl;
  return false;
}
//execution functionality for Negotiate
void Negotiate::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target){
  user->addNegotiateEffect(targeted);
  targeted->addNegotiateEffect(user);
  cout << "Negotiate Order executed: " << user->getName()  << " and " << targeted->getName() << " cannot attack each other this turn." << endl;
  Subject::notify(this);
}
//helper function for execute
void Negotiate::execute(Player* user, Player* targeted){
  execute(user, targeted, 0, nullptr, nullptr);
}

//overridden execute
void Negotiate::execute(){
  cout << "Please Pass parameters in the form (Player* user, Player* targeted)" << endl;
}


Order *Negotiate::clone() const { return new Negotiate(*this); }

std::ostream &Negotiate::orderCout(std::ostream &ostream) const {
  return ostream << "-> Negotiate order.";
}


// i want string label to each type of order A2 P5
std::string OrdersList::castOrderType(Order * o){
  if(auto advance = dynamic_cast<Advance*>(o)){
    return advance->getLabel();
  }
  else if(auto airlift = dynamic_cast<Airlift*>(o)){
    return airlift->getLabel();
  }
  else if(auto blockade = dynamic_cast<Blockade*>(o)){
    return blockade->getLabel();
  }
  else if(auto bomb = dynamic_cast<Bomb*>(o)){
    return bomb->getLabel();
  }
  else if(auto deploy = dynamic_cast<Deploy*>(o)){
    return deploy->getLabel();
  }
  else if(auto negotiate = dynamic_cast<Negotiate*>(o)){
    return negotiate->getLabel();
  }
  throw std::runtime_error("OrderList::Error Order is null");
}

// STRING TO LOG FUNCTIONS TO BE CALLED WHEN LOGGING

std::string OrdersList::stringToLog() {
  Order &o = *orders.back();
  std::string orderType = o.getLabel();

  std::stringstream stream;
  stream << "ORDER LIST: ";
  stream << "Order List Added ";
  stream << orderType;
  return stream.str();
}
std::string Deploy::stringToLog() {
  std::stringstream stream;
  stream << "ORDER: ";
  stream << "Order Executed ";
  stream << *this;
  return stream.str();
}

std::string Bomb::stringToLog() {
  std::stringstream stream;
  stream << "ORDER: ";
  stream << "Order Executed ";
  stream << *this;
  return stream.str();
}
std::string Advance::stringToLog() {
  std::stringstream stream;
  stream << "ORDER: ";
  stream << "Order Executed ";
  stream << *this;
  return stream.str();
}
std::string Blockade::stringToLog() {
  std::stringstream stream;
  stream << "ORDER: ";
  stream << "Order Executed ";
  stream << *this;
  return stream.str();
}
std::string Airlift::stringToLog() {
  std::stringstream stream;
  stream << "ORDER: ";
  stream << "Order Executed ";
  stream << *this;
  return stream.str();
}
std::string Negotiate::stringToLog() {
  std::stringstream stream;
  stream << "ORDER: ";
  stream << "Order Executed ";
  stream << *this;
  return stream.str();
}

/*
// user input
Order* UserInputOrder::create(const std::string& orderType){
  if (orderType == "Deploy") { return new Deploy; }
  else if (orderType == "Advance") { return new Advance; }
  else if (orderType == "Bomb") { return new Bomb(); }
  else if (orderType == "Blockade") { return new Blockade(); }
  else if (orderType == "Airlift") { return new Airlift(); }
  else if (orderType == "Negotiate") { return new Negotiate(); }
  else { throw std::runtime_error("invalid OrderType: " + orderType ); }
}
*/
