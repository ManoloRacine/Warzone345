
#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <string>
#include "../Cards/Cards.h"
#include "../Player/Player.h"

class Player;
class Territory;
class Card;
enum CardType : int;

using std::vector;
using std::string;

// orders
class Order{
private:
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
  
public:
  virtual void execute() = 0;
  virtual void execute(Player* user, Player* targeted, int troops, Territory* source, Territory* target) = 0;
  virtual ~Order() = 0;
  virtual Order *clone() const = 0;
  Order();
  Order(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
  //Getters and setters for user
  Player* getUser() const;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const;
  void setSource(Territory* newSource);

  //get label
  virtual string getLabel() const = 0;
private:
  virtual std::ostream &orderCout(std::ostream &) const = 0;
  friend std::ostream &operator<<(std::ostream &, const Order &);


  
};

//order list
class OrdersList{
private:
  vector<Order*> orders{};

public:
  OrdersList() = default;
  ~OrdersList();
  OrdersList(const OrdersList &);

  OrdersList &operator=(const OrdersList &);

  void add(Order *o);
  void remove(int);
  void move(int, int);
  //vector<Order*> getList() const;
 // std::vector<Order *>* getList();
 std::vector<Order*> getList() const;
  const std::vector<Territory*>& getConnectedTerritories() const;

private:

  friend std::ostream &operator<<(std::ostream &, const OrdersList &);
};

//========================================
//Deploy Order
//========================================
class Deploy : public Order{
private:
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* player, int armies, Territory* target);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute(Player* player, int armies, Territory* target);
  void execute() override;
  ~Deploy() override;
  Deploy(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;
private:
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

//========================================
//Advance Order
//========================================
class Advance : public Order{
private:
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* player, int armies, Territory* source, Territory* target);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  void execute(Player* player, int armies, Territory* source, Territory* target);
  ~Advance() override;
  Advance(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;
private:
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

//========================================
//Airlift Order
//========================================
class Airlift : public Order{
private:
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* player, int armies, Territory* source, Territory* target);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  void execute(Player* player, int armies, Territory* source, Territory* target);
  ~Airlift() override;
  Airlift(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;
private:
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


//========================================
//Bomb Order
//========================================
class Bomb : public Order{
private:
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* player, Territory* target);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  void execute(Player* player, Territory* target);
  ~Bomb() override;
  Bomb(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;
private:
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


//========================================
//Blockade Order
//========================================
class Blockade : public Order{
private:
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* player, Territory* source);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  void execute(Player* user, Territory* source);  
  ~Blockade() override;
  Blockade(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;

private:
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


//========================================
//Negotiate Order
//========================================
class Negotiate : public Order{
private:
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* user, Player* target);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  void execute(Player* user, Player* targeted);
  ~Negotiate() override;
  Negotiate(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;
  
private:
  
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

class UserInputOrder{
public:
  static Order *create(const std::string&) ;
};

class OrdersFactory {
public:
  static Order* CreateOrder(CardType cardType);

};

#endif