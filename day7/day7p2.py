from functools import cmp_to_key


file = open("input")
lines = file.readlines()
for i in range(len(lines)):
    lines[i] = lines[i].replace('A', 'Z')
    lines[i] = lines[i].replace('K', 'Y')
    lines[i] = lines[i].replace('Q', 'X')
    lines[i] = lines[i].replace('J', '*')
    lines[i] = lines[i].replace('T', 'V')


def strenght(hand: str) -> int:
    set_of_cards = []
    for card in hand:
        if card not in set_of_cards:
            set_of_cards.append(card)

    size = len(set_of_cards)
    if size == 1:
        del set_of_cards
        return 7
    elif size == 2:
        count_a = 0
        count_b = 0
        for card in hand:
            if card == set_of_cards[0]:
                count_a += 1
            elif card == set_of_cards[1]:
                count_b += 1

        if (count_a == 4 or count_b == 4):
            del set_of_cards
            return 6
        else:
            del set_of_cards
            return 5

    elif size == 3:
        count_a = 0
        count_b = 0
        count_c = 0
        for card in hand:
            if card == set_of_cards[0]:
                count_a += 1
            elif card == set_of_cards[1]:
                count_b += 1
            elif card == set_of_cards[2]:
                count_c += 1

        if (count_a == 3 or count_b == 3 or count_c == 3):
            del set_of_cards
            return 4
        else:
            del set_of_cards
            return 3
    elif size == 4:
        del set_of_cards
        return 2
    else:
        del set_of_cards
        return 1


hand_to_strength = []

for i in range(len(lines)):
    hand = lines[i].split(' ')[0]
    bid = lines[i].split(' ')[1][:-1]
    strength = strenght(lines[i].split(' ')[0])
    joker = hand.count('*')
    hand_to_strength.append([hand, strength, bid, joker])

for i in range(len(hand_to_strength)):
    hand = hand_to_strength[i][0]
    strength = hand_to_strength[i][1]
    bid = hand_to_strength[i][2]
    joker = hand_to_strength[i][3]

    if (strength == 1):
        if (joker > 0):
            hand_to_strength[i][1] = 2
    elif (strength == 2):
        if (joker > 0):
            hand_to_strength[i][1] = 4
    elif (strength == 3):
        if (joker == 2):
            hand_to_strength[i][1] = 6
        elif (joker == 1):
            hand_to_strength[i][1] = 5
    elif (strength == 4):
        if (joker > 0):
            hand_to_strength[i][1] = 6
    elif (strength == 5):
        if (joker > 0):
            hand_to_strength[i][1] = 7
    elif (strength == 6):
        if (joker > 0):
            hand_to_strength[i][1] = 7

hand_to_strength = sorted(
    hand_to_strength, key=lambda x: (x[1], x[0]))

for i in range(len(hand_to_strength)):
    hand_to_strength[i][0] = hand_to_strength[i][0].replace('Z', 'A')
    hand_to_strength[i][0] = hand_to_strength[i][0].replace('Y', 'K')
    hand_to_strength[i][0] = hand_to_strength[i][0].replace('X', 'Q')
    hand_to_strength[i][0] = hand_to_strength[i][0].replace('*', 'J')
    hand_to_strength[i][0] = hand_to_strength[i][0].replace('V', 'T')


ans = 0
for rank, (hand, strength, bid, joker) in enumerate(hand_to_strength):
    ans += (rank+1) * int(bid)
    print(rank+1, hand, strength, bid, joker)

# 249483956

print(ans)
