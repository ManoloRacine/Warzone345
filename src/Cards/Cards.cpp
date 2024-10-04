//
// Created by manol on 9/28/2024.
//

#include "Cards.h"

#include <algorithm>
#include <iostream>
using namespace std;
#include <random>

Deck::Deck() {

}

Deck::Deck(const Deck &deck) {
    cards = deck.cards;
}

Deck &Deck::operator=(const Deck &other) {
    if (this != &other) {
        cards = other.cards;
    }

    return *this;
}

//Generates an equal amount of the five different card types and shuffles them
void Deck::generateDeck() {
    std::vector<Card*> cardsToShuffle;

    //reserve the space for the final number of cards in the deck
    cardsToShuffle.reserve(50);


    for (int i = 0; i < 10; i++) {
        cardsToShuffle.push_back(new BombCard(this));
    }
    for (int i = 0; i < 10; i++) {
        cardsToShuffle.push_back(new ReinforcementCard(this));
    }
    for (int i = 0; i < 10; i++) {
        cardsToShuffle.push_back(new BlockadeCard(this));
    }
    for (int i = 0; i < 10; i++) {
        cardsToShuffle.push_back(new AirliftCard(this));
    }
    for (int i = 0; i < 10; i++) {
        cardsToShuffle.push_back(new DiplomacyCard(this));
    }

    //randomizer generation
    std::random_device rd;
    std::mt19937 gen {rd()};

    std::ranges::shuffle(cardsToShuffle, gen);

    for (Card* card : cardsToShuffle) {
        cards.push(card);
    }

}

//Draws the top card from the deck
Card *Deck::draw() {
    if (cards.empty()) {
        std::cout << "deck is empty" << std::endl;
        return nullptr;
    }
    Card* card = cards.front();
    cards.pop();
    return card;
}

//Puts back the card into at the bottom of the deck
void Deck::putIntoDeck(Card* card_to_put_back) {
    cards.push(card_to_put_back);
}

//Prints out all the cards in the deck
std::ostream& operator<<(std::ostream& os, const Deck &deck) {
    std::queue<Card*> cardsToPrint = deck.cards;
    while (!cardsToPrint.empty()) {
        Card* card = cardsToPrint.front();
        cardsToPrint.pop();
        os << card->print();
    }
    return os;
}

Hand::Hand() {

}

Hand::Hand(const Hand &hand) {
    cards = hand.cards;
}

Hand &Hand::operator=(const Hand &other) {
    if (this != &other) {
        cards = other.cards;
    }

    return *this;
}

//Plays the card, and removes it from the hand
void Hand::play(Card *cardToPlay) {
    cardToPlay->play();

    cout << cardToPlay->print() << " card played" << endl;

    auto it = std::find(cards.begin(), cards.end(),
                        cardToPlay);

    if (it != cards.end()) {
        cards.erase(it);
    }
}

//Draws a card from the deck and adds it to the hand
void Hand::draw(Deck *deck) {
    Card* card_drawn = deck->draw();

    if (card_drawn == nullptr) {
        std::cout << "no card drawn";
        return;
    }

    std::cout << *card_drawn << " card drawn" << std::endl;

    cards.push_back(card_drawn);
}

std::vector<Card *> Hand::getCards() {
    return cards;
}

//Prints out all the cards in the hand
std::ostream& operator<<(std::ostream& os, const Hand &hand) {
    for (auto const& it : hand.cards) {
        os << it->print() << std::endl;
    }
    return os;
}



Card::Card(const Card &card) {
    original_deck = card.original_deck;
}

Card &Card::operator=(const Card &other) {
    if (this != &other) {
        original_deck = other.original_deck;
    }

    return *this;
}

//Plays the card and puts it back into its original deck
void BombCard::play() {
    original_deck->putIntoDeck(this);
}

std::string BombCard::print() const{
    return "bomb";
}

//Plays the card and puts it back into its original deck
void ReinforcementCard::play() {
    original_deck->putIntoDeck(this);
}

std::string ReinforcementCard::print()  const {
    return "reinforcement";
}

//Plays the card and puts it back into its original deck
void BlockadeCard::play() {
    original_deck->putIntoDeck(this);
}

std::string BlockadeCard::print()  const {
    return "blockade";
}

//Plays the card and puts it back into its original deck
void AirliftCard::play() {
    original_deck->putIntoDeck(this);
}

std::string AirliftCard::print()  const {
    return "airlift";
}

//Plays the card and puts it back into its original deck
void DiplomacyCard::play() {
    original_deck->putIntoDeck(this);
}

std::string DiplomacyCard::print()  const {
    return "diplomacy";
}

Card::Card(Deck *deck) {
    original_deck = deck;
}

//Prints out the string given by the print() method that is overloaded by each card type
std::ostream& operator<<(std::ostream& os, const Card &card) {
    return os << card.print();
}








