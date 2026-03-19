from Player import Player
from Deck import Deck
import Score


def computate_score(hand):
    if check_royal_straight_flush(hand):
        return "Royal Straight Flush", 200
    elif check_straight_flush(hand):
        return "Straight Flush", 100
    elif check_four_of_a_kind(hand):
        return "Quadra", 50
    elif check_fullhand(hand):
        return "Full Hand", 20
    elif check_flush(hand):
        return "Flush", 10
    elif check_straight(hand):
        return "Straight", 5
    elif check_three_of_a_kind(hand):
        return "Trinca", 2
    elif check_two_pairs(hand):
        return "Dois pares", 1  
    else:
        return "Não fez nenhuma combinação", 0

def check_two_pairs(hand):
    hand_values = [card.value for card in hand]
    val_count = {card: hand_values.count(card) for card in hand_values}
    pair_count = sum(1 for val in val_count.values() if val == 2)
    return pair_count == 2

def check_three_of_a_kind(hand):
    hand_values = [card.value for card in hand]
    val_count = {card: hand_values.count(card) for card in hand_values}
    return 3 in val_count.values()

def check_straight(hand):
    hand_values = [card.value for card in hand]
    swap_char_occur_and_sort(hand_values)

    return (hand_values[0] + 1 == hand_values[1]  
        and hand_values[1] + 1 == hand_values[2] 
        and hand_values[2] + 1 == hand_values[3] 
        and hand_values[3] + 1 == hand_values[4])

def check_flush(hand):
    hand_suits = [card.suit for card in hand]
    suit_count = {card: hand_suits.count(card) for card in hand_suits}
    return 5 in suit_count.values()

def check_fullhand(hand):
    hand_values = [card.value for card in hand]
    swap_char_occur_and_sort(hand_values)

    return (hand_values[0] == hand_values[1] and hand_values[1] == hand_values[2]
        and hand_values[3] == hand_values[4]) or (hand_values[0] == hand_values[1]
        and hand_values[2] == hand_values[3] and hand_values[3] == hand_values[4])

def check_four_of_a_kind(hand):
    hand_values = [card.value for card in hand]
    val_count = {card: hand_values.count(card) for card in hand_values}
    return 4 in val_count.values()

def check_straight_flush(hand):
    return check_straight(hand) and check_flush(hand)

def check_royal_straight_flush(hand):   
    hand_values = [card.value for card in hand]
    swap_char_occur_and_sort(hand_values)

    return check_straight_flush(hand) and hand[0].value == 10

def char_to_int(c):
    if c == 'J':
        c = 11
    elif c == 'Q':
        c = 12
    elif c == 'K':
        c = 13   
    elif c == 'A':
        c = 14

    return c

def swap_char_occur_and_sort(hand_values):
    for i, val in enumerate(hand_values):
        if(not isinstance(val, int)):
            int_val = char_to_int(val)
            hand_values[i] = int_val

    hand_values.sort()
