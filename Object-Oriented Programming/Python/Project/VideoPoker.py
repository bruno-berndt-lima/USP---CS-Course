from Player import Player
from Deck import Deck
import Score

p1 = Player()
bet = -1 
rodada = 1

while p1.credit > 0:
    print("--------------------- Rodada {} ---------------------".format(rodada))
    print("Saldo: {}".format(p1.credit))
    print("Digite quanto quer apostar: ", end="")
    bet = int(input())
    
    if bet < 0 or bet > p1.credit:
        print("Valor de aposta inválido.")
        break
    elif bet == 0:
        break
    p1.credit = p1.credit - bet
    
    deck = Deck()
    for i in range(5):
        p1.draw(deck)

    p1.show_hand()
    
    for i in range(2):
        print("Digite as cartas a serem trocadas, separadas por espaço, caso não queira digite ENTER")
        cards = input()
        if cards != "":
            cards_nums = list(map(int, cards.split(" ")))
            p1.new_draw(deck, len(cards_nums), cards_nums)
            p1.show_hand()
        else:
            break
    
    comb, prize = Score.computate_score(p1.hand) 
    print("{}. Ganhou {} créditos nessa rodada.".format(comb, prize * bet))

    p1.credit = p1.credit + prize * bet
    p1.hand = []

    rodada += 1
