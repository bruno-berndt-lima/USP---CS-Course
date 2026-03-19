from Deck import Deck

class Player:
    def __init__(self):
        self.credit = 200
        self.hand = []

    def draw(self, deck):
        self.hand.append(deck.draw_card())
        return self 

    def new_draw(self, deck, how_many, which_ones):
        for i in range(how_many):
            self.hand[which_ones[i] - 1] = deck.draw_card()
        return self

    def show_hand(self):
        s = ""
        str_res = ""
        for card in self.hand:
            s += str(card)
        str1 = s.split("\n")
        
        for i in range(5):
            str_res += str1[i] + "\t" + str1[i + 5] + "\t" + str1[i + 10]\
             + "\t" + str1[i + 15] + "\t" + str1[i + 20] + "\n"
        print(" 1\t\t 2\t\t 3\t\t 4\t\t 5")
        print(str_res)
        



