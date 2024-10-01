//
// Created by manol on 9/28/2024.
//

#include "CardsDriver.h"
#include "Cards.h"

void testCards() {
    Deck *deck = new Deck();
    deck->generateDeck();
    Hand *hand = new Hand();
    hand->draw(deck);
    hand->draw(deck);
    hand->draw(deck);
    hand->draw(deck);
    hand->play(hand->getCards().front());
    hand->play(hand->getCards().front());
    hand->play(hand->getCards().front());
    hand->play(hand->getCards().front());
}