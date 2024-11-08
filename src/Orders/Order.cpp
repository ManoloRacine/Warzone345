
#include <stdexcept>
#include <algorithm>
#include "Order.h"


//Constructor, Destructor and << override
Order::Order(){}
Order::~Order() = default;
std::ostream &operator<<(std::ostream &stream, const Order &o) { return o.orderCout(stream); }

//Getters and setters for user
Player* Order::getUser() const{
  return user;
}

void Order::setUser(Player* newUser){
  user = newUser;
}

//Getters and setters for targeted
Player* Order::getTargeted() const{
  return targeted;
}

void Order::setTargeted(Player* newTargeted){
  targeted = newTargeted;
}

//Getters and setters for Troops
int Order::getTroops() const{
  return troops;
}

void Order::setTroops(int newTroops){
  troops = newTroops;
}

//Getters and setters for target
Territory* Order::getTarget() const{
  return target;
}

void Order::setTarget(Territory* newTarget){
  target = newTarget;
}

//Getters and setters for source
Territory* Order::getSource() const{
  return source;
}

void Order::setSource(Territory* newSource){
  source = newSource;
}


//order list

OrdersList::~OrdersList(){ for(auto order: orders){ delete order; } }

OrdersList::OrdersList(const OrdersList &oldList){
  unsigned listLength = oldList.orders.size();
  orders = std::vector<Order *>(listLength);
  for (unsigned o = 0; o < listLength; o++) {
    orders[o] = oldList.orders[o]->clone();
  }
}

void OrdersList::add(Order *o){
  if(o){
    orders.push_back(o);
  } else {
    throw std::runtime_error("NULL value inserted in the list");
  }
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

// print out the order list
std::ostream &operator<<(std::ostream &stream, const OrdersList &ol){
  unsigned listLength = ol.orders.size();

  for (unsigned l = 0; l < listLength; l++){
    stream << l + 1 << " - " << ol.orders[l]->getLabel() << " | ";
  }
  stream << "\n";
  return stream;
}

std::vector<Order *> *OrdersList::getList() {
  return &this->orders;
}


//========================================
//Deploy Order
//========================================
const string Deploy::label = "Deploy";
Deploy::~Deploy() = default;
string Deploy::getLabel() const { return label; }
ostream &Deploy::orderCout(ostream &output) const {
  return output << "Deploy order";
}
//constructor
Deploy::Deploy(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

//Validate method for deploy
bool Deploy::validate(Player* player, int armies, Territory* target){
  if(player->getReinforcements() >= armies 
  && find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end()){
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
    user->setReinforcements(user->getReinforcements()-armies);
    target->setArmies(target->getArmies()+armies);
    user->toDefend(target);
    cout << "Troops deployed" << endl;
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
std::string Advance::getLabel() const { return label; }
Advance::~Advance() = default;
const std::string Advance::label = "Advance";

Advance::Advance(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

//Validate method for Advance
bool Advance::validate(Player* player, int armies, Territory* source, Territory* target){
  if(find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end() && find(source->getConnectedTerritories().begin(), source->getConnectedTerritories().end(), target) != source->getConnectedTerritories().end() && armies <= source->getArmies()){
    cout << "Order is Valid" << endl;
    execute(player, armies, source, target);
  }
  else
    cout << "Order Invalid" << endl;
    return false;
}
//Overriden execute function that performs the execution
void Advance::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target){
    if(user == targeted){
      user->toDefend(target);
      source->setArmies(source->getArmies()-armies);
      target->setArmies(target->getArmies()+armies);
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
        target->setOwner(user);
        targeted->removeTerritories(target);
        user->addTerritories(target);

        target->setArmies(attackingUnits-attackingLosses);
        source->setArmies(source->getArmies()-(attackingUnits-attackingLosses));
        cout << "Territory " << target->getName() << " conquered by " << user->getName() << endl;
      }
      else{
        cout << "Attack Failed " << target->getName() << " remains in " << user->getName() << "'s possession." << endl;
      }

    }
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
const string Airlift::label = "Airlift";
Airlift::~Airlift() = default;

string Airlift::getLabel() const { return label; }
//constructor
Airlift::Airlift(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

ostream &Airlift::orderCout(ostream &output) const { return output << "Airlift order"; }
//validation for airlift
bool Airlift::validate(Player* player, int armies, Territory* source, Territory* target) {
  if(find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end() 
    && find(player->getTerritories().begin(), player->getTerritories().end(), source) != player->getTerritories().end()
    && armies <= source->getArmies()
    && hasCard("airlift", player)){
      cout << "AirLift Order Validated" << endl;
      execute(player, armies, source, target);
      return true;
  }
  else{
    cout << "Airlift order Invalid" << endl;
  }
  
}
//execution of the airlift order
void Airlift::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target){
  user->toDefend(target);
  source->setArmies(source->getArmies()-armies);
  target->setArmies(target->getArmies()+armies);

  cout << "Troops have successfully been Airlifted from " << source->getName() << " to " << target->getName() << endl;
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
//Blockade Order
//========================================
const std::string Blockade::label = "Blockade";

Blockade::Blockade(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

Blockade::~Blockade() = default;

std::string Blockade::getLabel() const { return label; }

std::ostream &Blockade::orderCout(std::ostream &output) const { return output << "Blockade order"; }

bool Blockade::validate(Player* player, Territory* source){
  std::cout << "validation of Blockade order" << std::endl;
  return true;
}

void Blockade::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) {
  std::cout << "Blockade execution" << std::endl;
}

Order *Blockade::clone() const { return new Blockade(*this); }


//========================================
//Bomb Order
//========================================
const std::string Bomb::label = "Bomb";

Bomb::Bomb(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

Bomb::~Bomb() = default;

std::string Bomb::getLabel() const { return label; }

std::ostream &Bomb::orderCout(std::ostream &output) const { return output << "Bomb order"; }

bool Bomb::validate(Player* player, Territory* target){
  std::cout << "Validation of Bomb order" << std::endl;
  return true;
}

void Bomb::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target){
  std::cout << "Bomb execution" << std::endl;
}

Order *Bomb::clone() const { return new Bomb(*this); }


//========================================
//Negociate Order
//========================================
const std::string Negotiate::label = "Negotiate";

Negotiate::Negotiate(Player* user, Player* targeted, int troops, Territory* source, Territory* target)
    : user(user), targeted(targeted), troops(troops), source(source), target(target){}

Negotiate::~Negotiate() = default;

std::string Negotiate::getLabel() const { return label; }

bool Negotiate::validate(Player* user, Player* target){
  std::cout << "Validatiom of negotiate order" << std::endl;
  return true;
}

void Negotiate::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target){
  std::cout << "Negotiate execution." << std::endl;
}


Order *Negotiate::clone() const { return new Negotiate(*this); }

std::ostream &Negotiate::orderCout(std::ostream &ostream) const {
  return ostream << "-> Negotiate order.";
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