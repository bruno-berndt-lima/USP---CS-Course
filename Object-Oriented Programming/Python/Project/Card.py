class Card:
    values = [2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K', 'A']
    suits = ['♥', '♦', '♠', '♣']

    def __init__(self, value, suit):
        self.value = value
        self.suit = suit

    def __str__(self):
        if self.value == 10:
            s = " --------\n |      | \n |  {}{} | \n |      | \n --------\n".format(self.value, self.suit)
        else:
            s = " --------\n |      | \n |  {}{}  | \n |      | \n --------\n".format(self.value, self.suit)
        return s




