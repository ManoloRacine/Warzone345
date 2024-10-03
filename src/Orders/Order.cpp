#include <stdexcept>

#include "Order.h"

//order

Order::~Order() = default;
std::ostream &operator<<(std::ostream &stream, const Order &o) { return o.orderCout(stream); }

//order list

OrdersList::~OrdersList(){ for(auto order: orders){ delete order; } }

OrdersList::OrdersList(const OrdersList &oldList)
{
  unsigned listLength = oldList.orders.size();
  orders = std::vector<Order *>(listLength);
  for (unsigned o = 0; o < listLength; o++) { orders[o] = oldList.orders[o]->clone(); }
}

void OrdersList::add(Order *o)
{
  if(o){ orders.push_back(o); } else { throw std::runtime_error("NULL value inserted in List"); }
}


void OrdersList::remove(int pos)
{
  unsigned listLength = orders.size();
  if (listLength == 0){
    throw std::runtime_error("order list empty");
  }
  else if (pos >= listLength || pos < 0) {
    throw std::runtime_error("try again, invalid entry");
  }
  else
  {
    delete orders[pos];
    orders.erase(orders.begin() + pos);
  }
}

void OrdersList::move(int pos1, int pos2)
{
  unsigned listLength = orders.size();
  if (listLength == 0){
    std::cout << "order list empty" << std::endl;
  }
  else if (listLength == 1)
  {
    throw std::runtime_error("only 1 order in the list");
  }
  else if (pos1 >= listLength || pos2 >= listLength || pos1 < 0 || pos2 < 0)
  {
    throw std::runtime_error("0 or 1 valid positon, try again");
  }
  else
  {
    Order *temp = orders[pos1];
    orders[pos1] = orders[pos2];
    orders[pos2] = temp;
  }
}

void OrdersList::execute()
{
  unsigned listLength = orders.size();
  if (listLength == 0){
    throw std::runtime_error("empty list");
  }
  else
  {
    for(auto order : orders){
      order->execute();
      delete order;
    }
    orders.clear();
  }
}


OrdersList &OrdersList::operator=(const OrdersList &copyList)
{
  // let go of left hand side memory and deep copy to right hand side
  // checks if we're self assigning
  if (&copyList == this){
    return *this;
  }

  unsigned initialListLength = orders.size();
  unsigned copyListLength = copyList.orders.size();

  for (int o = 0; o < initialListLength; o++) { delete orders[o]; }

  // Grab memory same size as the right hand side vector
  orders = std::vector<Order *>(copyListLength);


  for (int i = 0; i < copyListLength; i++) {
    // clone copied element to left hand side
    orders[i] = copyList.orders[i]->clone();
  }

  return *this;
}

// print out the order list
std::ostream &operator<<(std::ostream &stream, const OrdersList &ol)
{
  unsigned listLength = ol.orders.size();

  for (unsigned l = 0; l < listLength; l++)
  {
    stream << l + 1 << " --> " << ol.orders[l]->getLabel() << " // ";
  }
  stream << "\n";
  return stream;
}

std::vector<Order *> *OrdersList::getList() {
  return &this->orders;
}




//advance





std::ostream &Advance::orderCout(std::ostream &output) const { return output << "-> Advance order."; }

std::string Advance::getLabel() const { return label; }

Advance::~Advance() = default;

const std::string Advance::label = "Advance";

bool Advance::validate() const
{
  std::cout << "-> Advance order validation check" << std::endl;
  return true;
}

void Advance::execute() const
{
  if (validate()) { std::cout << "Advance execution." << std::endl; }
}

Order *Advance::clone() const { return new Advance(*this); }







//airlift



const std::string Airlift::label = "Airlift";

Airlift::~Airlift() = default;

std::string Airlift::getLabel() const { return label; }

std::ostream &Airlift::orderCout(std::ostream &output) const { return output << "-> Airlift order."; }

bool Airlift::validate() const
{
  std::cout << "-> Airlift order validation check" << std::endl;
  return true;
}

void Airlift::execute() const
{
  if (validate()) { std::cout << "Airlift execution." << std::endl; }
}

Order *Airlift::clone() const { return new Airlift(*this); }







//blockade

const std::string Blockade::label = "Blockade";

Blockade::~Blockade() = default;

std::string Blockade::getLabel() const { return label; }

std::ostream &Blockade::orderCout(std::ostream &output) const { return output << "-> Blockade order."; }

bool Blockade::validate() const
{
  std::cout << "-> Blockade order validation check" << std::endl;
  return true;
}

void Blockade::execute() const
{
  if (validate()) { std::cout << "Blockade execution." << std::endl; }
}

Order *Blockade::clone() const { return new Blockade(*this); }

//bomb

const std::string Bomb::label = "Bomb";

Bomb::~Bomb() = default;

std::string Bomb::getLabel() const { return label; }

std::ostream &Bomb::orderCout(std::ostream &output) const { return output << "-> Bomb order."; }

bool Bomb::validate() const
{
  std::cout << "-> Bomb order validation check" << std::endl;
  return true;
}

void Bomb::execute() const
{
  if (validate()) { std::cout << "Bomb execution." << std::endl; }
}

Order *Bomb::clone() const { return new Bomb(*this); }

//deploy


const std::string Deploy::label = "Deploy";

Deploy::~Deploy() = default;

std::string Deploy::getLabel() const { return label; }

std::ostream &Deploy::orderCout(std::ostream &output) const { return output << "-> Deploy order."; }

bool Deploy::validate() const
{
  std::cout << "-> Deploy order validation check" << std::endl;
  return true;
}

void Deploy::execute() const
{
  if (validate()) { std::cout << "Deploy execution." << std::endl; }
}

Order *Deploy::clone() const { return new Deploy(*this); }




// negotiate

const std::string Negotiate::label = "Negotiate";

Negotiate::~Negotiate() = default;

std::string Negotiate::getLabel() const { return label; }

bool Negotiate::validate() const
{
  std::cout << "-> Negotiate order validation check" << std::endl;
  return true;
}

void Negotiate::execute() const
{
  if (validate()) { std::cout << "Negotiate execution." << std::endl; }
}


Order *Negotiate::clone() const { return new Negotiate(*this); }

std::ostream &Negotiate::orderCout(std::ostream &ostream) const {
  return ostream << "-> Negotiate order.";
}




// user input


Order* UserInputOrder::create(const std::string& orderType)
{
  if (orderType == "Deploy") { return new Deploy; }
  else if (orderType == "Advance") { return new Advance; }
  else if (orderType == "Bomb") { return new Bomb(); }
  else if (orderType == "Blockade") { return new Blockade(); }
  else if (orderType == "Airlift") { return new Airlift(); }
  else if (orderType == "Negotiate") { return new Negotiate(); }
  else { throw std::runtime_error("invalid OrderType: " + orderType ); }
}


