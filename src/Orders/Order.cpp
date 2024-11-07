
#include <stdexcept>

#include "Order.h"


//order

Order::~Order() = default;
std::ostream &operator<<(std::ostream &stream, const Order &o) { return o.orderCout(stream); }

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

void OrdersList::execute(){
  unsigned listLength = orders.size();
  if (listLength == 0){
    throw std::runtime_error("empty list");
  }
  else{
    for(auto order : orders){
      order->execute();
      delete order;
    }
    orders.clear();
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
const std::string Deploy::label = "Deploy";
Deploy::~Deploy() = default;
std::string Deploy::getLabel() const { return label; }

std::ostream &Deploy::orderCout(std::ostream &output) const {
  return output << "Deploy order";
}

//Validate method for deploy
bool Deploy::validate(Player* player, int armies, Territory* target){
  if(player->getReinforcements() >= armies && find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end()){
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

//Validate method for Advance
bool Advance::validate(Player* player, int armies, Territory* source, Territory* target){
  if(find(player->getTerritories().begin(), player->getTerritories().end(), target) != player->getTerritories().end() && find(source->getConnectedTerritories().begin(), source->getConnectedTerritories().end(), target) != source->getConnectedTerritories().end() && armies <= source->getArmies()){
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
//Helper Fnction for execute
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
const std::string Airlift::label = "Airlift";
Airlift::~Airlift() = default;

std::string Airlift::getLabel() const { return label; }

std::ostream &Airlift::orderCout(std::ostream &output) const { return output << "Airlift order"; }

bool Airlift::validate(Player* player, int armies, Territory* source, Territory* target) {
  std::cout << "Validatin of Airlift order" << std::endl;
  return true;
}

void Airlift::execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target){
  std::cout << "Airlift execution" << std::endl;
}

void Airlift::execute(){

}

void Airlift::execute(){
  cout << "Please Pass parameters in the form (Player* player, int armies, Territory* source, Territory* target)" << endl;
}

Order *Airlift::clone() const { return new Airlift(*this); }


//========================================
//Blockade Order
//========================================
const std::string Blockade::label = "Blockade";

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
