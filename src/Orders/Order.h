
#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <string>
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "Logger/LogObserver.h"

class Player;
class GameEngine;
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
  virtual bool validate() = 0;
  virtual ~Order() = 0;
  virtual Order *clone() const = 0;
  Order();
  Order(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
  //Getters and setters for user
  virtual Player* getUser() const = 0;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  virtual Player* getTargeted() const = 0;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  virtual int getTroops() const = 0;
  void setTroops(int newTroops);

  //Getters and setters for target
  virtual Territory* getTarget() const = 0;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  virtual Territory* getSource() const = 0;
  void setSource(Territory* newSource);

  //get label
  virtual string getLabel() const = 0;
private:
  virtual std::ostream &orderCout(std::ostream &) const = 0;
  friend std::ostream &operator<<(std::ostream &, const Order &);


  
};

//order list
class OrdersList: public Subject, ILoggable{
private:
  vector<Order*> orders{};
  GameEngine* game = nullptr;
public:
  OrdersList() = default;
  explicit OrdersList(GameEngine* gameEngine);
  ~OrdersList();
  OrdersList(const OrdersList &);

  OrdersList &operator=(const OrdersList &);

  // logging order list
  static std::string castOrderType(Order * o);
  std::string stringToLog() override;

  void add(Order *o);
  void remove(int);
  void move(int, int);
  std::vector<Order*> getList() const;
  const std::vector<Territory*>& getConnectedTerritories() const;

private:

  friend std::ostream &operator<<(std::ostream &, const OrdersList &);
};

//========================================
//Deploy Order
//========================================
class Deploy  : public Order, Subject, ILoggable{
private:
  GameEngine* game = nullptr;
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
  string label;
public:
  bool validate(Player* player, int armies, Territory* target);
  bool validate() override;
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute(Player* player, int armies, Territory* target);
  void execute() override;
  std::string stringToLog() override;
  ~Deploy() override;
  Deploy(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
  Deploy(GameEngine* gameEng, Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const override;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const override;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const override;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const override;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const override;
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
class Advance : public Order, Subject, ILoggable{
private:
  GameEngine* game = nullptr;
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* player, int armies, Territory* source, Territory* target);
  bool validate() override;
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  void execute(Player* player, int armies, Territory* source, Territory* target);
  std::string stringToLog() override;
  ~Advance() override;
  Advance(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
  Advance(GameEngine* gameEng, Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const override;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const override;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const override;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const override;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const override;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;
private:
  string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

//========================================
//Airlift Order
//========================================
class Airlift : public Order, Subject, ILoggable{
private:
  GameEngine* game = nullptr;
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* player, int armies, Territory* source, Territory* target);
  bool validate() override;
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  void execute(Player* player, int armies, Territory* source, Territory* target);
  std::string stringToLog() override;
  ~Airlift() override;
  Airlift(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
  Airlift(GameEngine* gameEng, Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const override;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const override;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const override;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const override;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const override;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;
private:
  string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


//========================================
//Bomb Order
//========================================
class Bomb : public Order, Subject, ILoggable{
private:
  GameEngine* game = nullptr;
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* player, Territory* target);
  bool validate() override;
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  void execute(Player* player, Territory* target);
  std::string stringToLog() override;
  ~Bomb() override;
  Bomb(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
  Bomb(GameEngine* gameEng, Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const override;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const override;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const override;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const override;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const override;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;
private:
  string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


//========================================
//Blockade Order
//========================================
class Blockade : public Order, Subject, ILoggable{
private:
  GameEngine* game = nullptr;
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* player, Territory* source);
  bool validate() override;
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  Blockade(GameEngine* gameEng, Player* user, Player* targeted, int troops, Territory* source, Territory* target);
  void execute(Player* user, Territory* source);  
  ~Blockade() override;
  Blockade(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const override;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const override;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const override;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const override;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const override;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;

private:
  string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


//========================================
//Negotiate Order
//========================================
class Negotiate : public Order, Subject, ILoggable{
private:
  GameEngine* game = nullptr;
  Player* user;
  Player* targeted;
  int troops;
  Territory* target;
  Territory* source;
public:
  bool validate(Player* user, Player* target);
  bool validate() override;
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  void execute(Player* user, Player* targeted);
  std::string stringToLog() override;

  Negotiate(GameEngine* gameEng, Player* user, Player* targeted, int troops, Territory* source, Territory* target);
  ~Negotiate() override;
  Negotiate(Player* user, Player* targeted, int troops, Territory* source, Territory* target);
   //Getters and setters for user
  Player* getUser() const override;
  void setUser(Player* newUser);

  //Getters and setters for targeted
  Player* getTargeted() const override;
  void setTargeted(Player* newTargeted);

  //Getters and setters for Troops
  int getTroops() const override;
  void setTroops(int newTroops);

  //Getters and setters for target
  Territory* getTarget() const override;
  void setTarget(Territory* newTarget);

  //Getters and setters for source
  Territory* getSource() const override;
  void setSource(Territory* newSource);

  //get label
  string getLabel() const override;
  
private:
  string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

class UserInputOrder{
public:
  static Order *create(const std::string&) ;
};

#endif