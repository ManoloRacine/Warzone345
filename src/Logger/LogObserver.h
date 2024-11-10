//
// Created by Ryad on 2024-11-07.
//

#ifndef LOGOBSERVER_H
#define LOGOBSERVER_H



#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <../GameEngine/GameEngine.h>

class OrdersList;
class ILogObserver;
class GameEngine;

// loggable which will be superclass of objects that need to be logged
class ILoggable {
public:
  virtual std::string stringToLog() = 0;
  virtual ~ILoggable()= default;
};

// ISubject

class ISubject {
public:
  virtual ~ISubject() = default;
  virtual void attach(ILogObserver* observer) = 0;
  virtual void detach(ILogObserver* observer) = 0;
  virtual void notify(ILoggable*) = 0;
  virtual void resetObservers() = 0;
};


//subject

class Subject : ISubject {
private:
  std::vector<ILogObserver*> observers;
public:
  Subject() = default;
  ~Subject() override = default;

  void attach(ILogObserver* observer) override;
  void detach(ILogObserver* observer) override;
  void notify(ILoggable*) override;
  void resetObservers() override;

};

//interface logObserver

class ILogObserver {
public:
  virtual ~ILogObserver() = default;
  virtual void update(ILoggable*) = 0;
};


// LogObserver which will be called when subject notifies
class LogObserver : ILogObserver {
private:
    // Object Owner
    GameEngine* game;

public:

    // Constructors
    explicit LogObserver(GameEngine*);
    ~LogObserver() override = default;
    explicit LogObserver(LogObserver*);

    void update(ILoggable*) override;

    // Stream Operator
    friend std::ostream &operator << (std::ostream &out, const LogObserver &log);

    // Assignment Operator
    LogObserver& operator=(const LogObserver &other);

};
#endif //LOGOBSERVER_H
