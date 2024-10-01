//
// Created by manol on 9/28/2024.
//

#include "Cards.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace std;
#include <random>

void BombCard::play() {
    original_deck->putIntoDeck(this);
}

std::string BombCard::print() const{
    return "bomb";
}


void ReinforcementCard::play() {
    original_deck->putIntoDeck(this);
}

std::string ReinforcementCard::print()  const {
    return "reinforcement";
}

void BlockadeCard::play() {
    original_deck->putIntoDeck(this);
}

std::string BlockadeCard::print()  const {
    return "blockade";
}

void AirliftCard::play() {
    original_deck->putIntoDeck(this);
}

std::string AirliftCard::print()  const {
    return "airlift";
}

void DiplomacyCard::play() {
    original_deck->putIntoDeck(this);
}

std::string DiplomacyCard::print()  const {
    return "diplomacy";
}


Card::Card(Deck *deck) {
    original_deck = deck;
}

void Hand::play(Card *cardToPlay) {
    cardToPlay->play();

    cout << cardToPlay->print() << " card played" << endl;

    auto it = std::find(cards.begin(), cards.end(),
                        cardToPlay);

    if (it != cards.end()) {
        cards.erase(it);
    }
}

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


Card *Deck::draw() {
    if (cards.empty()) {
        std::cout << "deck is empty" << std::endl;
        return nullptr;
    }
    Card* card = cards.front();
    cards.pop();
    return card;
}

void Deck::putIntoDeck(Card* card_to_put_back) {
    cards.push(card_to_put_back);
}

void Deck::generateDeck() {
    std::vector<Card*> cardsToShuffle;
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

    std::random_device rd;
    std::mt19937 gen {rd()};

    std::ranges::shuffle(cardsToShuffle, gen);

    for (Card* card : cardsToShuffle) {
        cards.push(card);
    }

}

std::ostream& operator<<(std::ostream& os, const Card &card) {
    return os << card.print();
}





