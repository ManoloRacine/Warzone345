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


class ILogObserver; // added forward declaration



// loggable interface
class ILoggable {
public:
  virtual std::string stringToLog() = 0;
  virtual ~ILoggable()= default;
};



// the subject which notifies - interface
class ISubject {
public:
  virtual ~ISubject() = default;
  virtual void attach(ILogObserver* observer) = 0;
  virtual void detach(ILogObserver* observer) = 0;
  virtual void notify(ILoggable*) = 0;
};



// the subject which notifies - extended
class Subject : ISubject {
private:
  std::vector<ILogObserver*> observers;
public:
  Subject() = default;
  ~Subject() override = default;

  void attach(ILogObserver* observer) override;
  void detach(ILogObserver* observer) override;
  void notify(ILoggable*) override;

  void resetObservers();
};



// observer which is notified
class ILogObserver {
public:
  virtual ~ILogObserver() = default;
  virtual void update(ILoggable*) = 0;
};



//observer
class LogObserver : ILogObserver {
private:
    // Object Owner
    GameEngine* game;
public:
    explicit LogObserver(GameEngine*);
    explicit LogObserver(LogObserver*);
    void update(ILoggable*) override;
    ~LogObserver() override = default;

    LogObserver &operator=(const LogObserver &other);
};
#endif //LOGOBSERVER_H
