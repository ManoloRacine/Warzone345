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
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    virtual std::string print() const = 0;
protected:
    Deck* original_deck;
};

class BombCard : public Card {
public:
    void play() override;
    BombCard(Deck* deck) : Card(deck) {};
    std::string print() const;
};

class ReinforcementCard : public Card {
public:
    void play() override;
    ReinforcementCard(Deck* deck) : Card(deck) {};
    std::string print() const;
};

class BlockadeCard : public Card {
public:
    void play() override;
    BlockadeCard(Deck* deck) : Card(deck) {};
    std::string print() const;
};

class AirliftCard : public Card {
public:
    void play() override;
    AirliftCard(Deck* deck) : Card(deck) {};
    std::string print() const;
};

class DiplomacyCard : public Card {
public:
    void play() override;
    DiplomacyCard(Deck* deck) : Card(deck) {};
    std::string print() const;
};

class Deck {
    public:
    Card* draw();
    void generateDeck();
    void putIntoDeck(Card* card_to_put_back);
private:
    std::queue<Card*> cards;
};

class Hand {
    public:
    void play(Card* cardToPlay);
    void draw(Deck* deck);
    std::vector<Card*> getCards();
    private:
    std::vector<Card*> cards;
};

std::ostream& operator<<(std::ostream& os, const Card& card);



#endif //CARDS_H
