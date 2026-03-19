import random
from Card import Card

class Deck:
    def __init__(self):
        self.cards = []
        self.create_deck()
        self.shuffle_deck()

    def create_deck(self):
        self.cards = [Card(value, suit) for value in Card.values for suit in Card.suits]  

    def shuffle_deck(self):
        random.shuffle(self.cards)

    def draw_card(self):
        return self.cards.pop()

    def __str__(self):
        s = ""
        for card in self.cards:
            s += str(card)
        
        return s


