//
// Created by manol on 9/28/2024.
//

#ifndef CARDS_H
#define CARDS_H
#include <ostream>
#include <queue>


class Hand;
class Deck;

class Card {
public:
    virtual void play() = 0;
    Card(Deck* deck);
    Card(const Card& card);
    Card& operator=(const Card& card);
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    virtual std::string print() const = 0;
    Deck* originalDeck;
};

class BombCard : public Card {
public:
    void play() override;
    BombCard(Deck* deck) : Card(deck) {};
    BombCard(const BombCard& bombCard);
    BombCard& operator=(const BombCard& bombCard);
    std::string print() const;
};

class ReinforcementCard : public Card {
public:
    void play() override;
    ReinforcementCard(Deck* deck) : Card(deck) {};
    ReinforcementCard(const ReinforcementCard& reinforcementCard);
    ReinforcementCard& operator=(const ReinforcementCard& reinforcementCard);
    std::string print() const;
};

class BlockadeCard : public Card {
public:
    void play() override;
    BlockadeCard(Deck* deck) : Card(deck) {};
    BlockadeCard(const BlockadeCard& blockadeCard);
    BlockadeCard& operator=(const BlockadeCard& blockadeCard);
    std::string print() const;
};

class AirliftCard : public Card {
public:
    void play() override;
    AirliftCard(Deck* deck) : Card(deck) {};
    AirliftCard(const AirliftCard& airliftCard);
    AirliftCard& operator=(const AirliftCard& airliftCard);
    std::string print() const;
};

class DiplomacyCard : public Card {
public:
    void play() override;
    DiplomacyCard(Deck* deck) : Card(deck) {};
    DiplomacyCard(const DiplomacyCard& diplomacyCard);
    DiplomacyCard& operator=(const DiplomacyCard& diplomacyCard);
    std::string print() const;
};

class Deck {
    public:
    Card* draw();
    void generateDeck();
    Deck();
    Deck(const Deck& deck);
    Deck& operator=(const Deck& deck);
    friend std::ostream& operator<<(std::ostream& os, const Deck& deck);
    void putIntoDeck(Card* cardToPutBack);
    void resetDeck();
    ~Deck();
private:
    std::queue<Card*> cards;

};

class Hand {
    public:
    void play(Card* cardToPlay);
    void draw(Deck* deck);
    Hand();
    Hand(const Hand& hand);
    Hand& operator=(const Hand& hand);
    friend std::ostream& operator<<(std::ostream& os, const Hand& hand);
    std::vector<Card*> getCards();
    std::vector<Card*> cards;
    ~Hand();
    void returnCards();
};

std::ostream& operator<<(std::ostream& os, const Card& card);
std::ostream& operator<<(std::ostream& os, const Hand& hand);
std::ostream& operator<<(std::ostream& os, const Deck& deck);





#endif //CARDS_H
