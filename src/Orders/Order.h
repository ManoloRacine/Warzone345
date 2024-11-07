
#pragma once

#include <iostream>
#include <vector>
#include "../Cards/Cards.h"
#include "../Player/Player.h"

class Card;
enum CardType : int;

// orders
class Order{
public:
  virtual std::string getLabel() const = 0;
  virtual void execute() = 0;
  virtual void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) = 0;
  virtual ~Order() = 0;
  virtual Order *clone() const = 0;

private:
  virtual std::ostream &orderCout(std::ostream &) const = 0;

  friend std::ostream &operator<<(std::ostream &, const Order &);
};

//order list
class OrdersList{
private:
  std::vector<Order *> orders{};

public:
  OrdersList() = default;
  ~OrdersList();
  OrdersList(const OrdersList &);

  OrdersList &operator=(const OrdersList &);

  void add(Order *o);
  void remove(int);
  void move(int, int);
  void execute();

  std::vector<Order *>* getList();

private:

  friend std::ostream &operator<<(std::ostream &, const OrdersList &);
};

//========================================
//Deploy Order
//========================================
class Deploy : public Order{
public:
  std::string getLabel() const override;
  bool validate(Player* player, int armies, Territory* target);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute(Player* player, int armies, Territory* target);
  void execute() override;
  ~Deploy() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

//========================================
//Advance Order
//========================================
class Advance : public Order{
public:
  std::string getLabel() const override;
  bool validate(Player* player, int armies, Territory* source, Territory* target);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  void execute(Player* player, int armies, Territory* source, Territory* target);
  ~Advance() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

//========================================
//Airlift Order
//========================================
class Airlift : public Order{
public:
  std::string getLabel() const override;
  bool validate(Player* player, int armies, Territory* source, Territory* target);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  ~Airlift() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

//========================================
//Blockade Order
//========================================
class Blockade : public Order{
public:
  std::string getLabel() const override;
  bool validate(Player* player, Territory* source);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  ~Blockade() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


//========================================
//Bomb Order
//========================================
class Bomb : public Order{
public:
  std::string getLabel() const override;
  bool validate(Player* player, Territory* target);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  ~Bomb() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


//========================================
//Negociate Order
//========================================
class Negotiate : public Order{
public:
  std::string getLabel() const override;
  bool validate(Player* user, Player* target);
  void execute(Player* user, Player* targeted, int armies, Territory* source, Territory* target) override;
  void execute() override;
  ~Negotiate() override;

private:
  const static std::string label;
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