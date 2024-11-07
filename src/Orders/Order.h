//
// Created by Ryad on 2024-10-03.
//

#pragma once

#include <iostream>
#include <vector>
#include "Logger/LogObserver.h"
#include "../Cards/Cards.h"

class Card;
enum CardType : int;

// orders
class Order
{
public:
  virtual std::string getLabel() const = 0;
  virtual bool validate() const = 0;
  virtual void execute() const = 0;
  virtual ~Order() = 0;
  virtual Order *clone() const = 0;

private:
  virtual std::ostream &orderCout(std::ostream &) const = 0;

  friend std::ostream &operator<<(std::ostream &, const Order &);
};

//order list
class OrdersList: public Subject, ILoggable
{
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
  std::string stringToLog() override;
  std::vector<Order *>* getList();

  static std::string castOrderType(Order *o);

private:

  friend std::ostream &operator<<(std::ostream &, const OrdersList &);
};



//advance
class Advance : public Order, Subject, ILoggable
{
public:
  std::string stringToLog() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Advance() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

//airlift
class Airlift : public Order, Subject, ILoggable
{
public:
  std::string stringToLog() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Airlift() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

//blockade
class Blockade : public Order, Subject, ILoggable
{
public:
  std::string stringToLog() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Blockade() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


// bomb
class Bomb : public Order, Subject, ILoggable
{
public:
  std::string stringToLog() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Bomb() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

//deploy
class Deploy : public Order, Subject, ILoggable
{
public:
  std::string stringToLog() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Deploy() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

class Negotiate : public Order, Subject, ILoggable
{
public:
  std::string stringToLog() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Negotiate() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

class UserInputOrder
{
public:
  static Order *create(const std::string&) ;
};

class OrdersFactory {

public:
  static Order* CreateOrder(CardType cardType);

};