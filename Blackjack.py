""" Blackjack.py - Blackjack game program write in python
* @version python3.6
* @author Junjie Wu at SMU
* @sid  47503174
"""

import random


# Create a Card class
class Card:
    def __init__(self, suit, rank):
        self.suit = suit
        self.rank = rank

    def display(self):
        print(self.suit + ": " + self.rank + "  ", end="")


# Create Deck class to represent the whole 52 cards
class Deck:
    suits = ("Spades", "Heats", "Clubs", "Diamonds")
    ranks = ("A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K")

    def __init__(self):
        self.deck = []
        for suit in Deck.suits:
            for rank in Deck.ranks:
                self.deck.append(Card(suit, rank))

    #  Call the random.shuffle to shuffle the deck
    def shuffle(self):
        random.shuffle(self.deck)

    def deal(self):
        card = self.deck.pop()
        return card


# Create Role class to represent the dealer and player
class Role:
    def __init__(self):
        self.cards = []
        self.points = 0
        # "A" counts 1 or 11 points
        self.magic = False

    def add_card(self, card):
        self.cards.append(card)
        if card.rank == "A":
            self.magic = True
            self.points += 1
        elif card.rank == "J":
            self.points += 10
        elif card.rank == "Q":
            self.points += 10
        elif card.rank == "K":
            self.points += 10
        else:
            self.points += int(card.rank)

    def point_calc(self):
        if self.magic is True and self.points <= 11:
            return self.points + 10
        else:
            return self.points

    # The second parameter indicate dealer or player
    def show(self, dealer=True):
        # The dealer has one card downward
        if dealer is True:
            for index in range(1, len(self.cards)):
                self.cards[index].display()
        else:
            for index in range(0, len(self.cards)):
                self.cards[index].display()


# Initialize dealer, player and deck
def game_setup():
    deal_alternate = False
    dealer = Role()
    player = Role()
    deck = Deck()
    deck.shuffle()

    # Deal the deal two cards and then two cards to player, or alternatively deal
    if not deal_alternate:
        dealer.add_card(deck.deal())
        dealer.add_card(deck.deal())
        player.add_card(deck.deal())
        player.add_card(deck.deal())
    else:
        for i in range(2):
            dealer.add_card(deck.deal())
            player.add_card(deck.deal())
            dealer.add_card(deck.deal())
            player.add_card(deck.deal())

    # Beginning, dealer shows only one card, player shows two cards
    print("Dealer's hand: ", end="")
    dealer.show(True)
    print("")
    print("Player's hand: ", end="")
    player.show(False)
    print("Total points: " + str(player.point_calc()))
    if dealer.point_calc() == 21:
        print("Dealer got a Blackjack, dealer wins!")
        replay()
    if player.point_calc() == 21:
        print("Player got a Blackjack, player wins!")
        replay()

    # player has choice to hit or stand from keyboard
    print("Press 'H' to hit or 'S' to stand...")
    key = input().lower()
    while key != 'h' and key != 's':
        print("Wrong key, please press 'H' or 'S'")
        key = input().lower()
    if key == 'h':
        hit(dealer, player, deck)
    else:
        stand(dealer, player, deck)


# Add one card to player's hand
def hit(dealer, player, deck):
    player.add_card(deck.deal())
    game_continue(dealer, player, deck, True)


# Player chose to stand, dealer add cards until points up to 17
def stand(dealer, player, deck):
    while dealer.point_calc() < 17:
        dealer.add_card(deck.deal())
    game_continue(dealer, player, deck, False)


# Compare the points of dealer and player
def game_continue(dealer, player, deck, flag):
    # flag == False means player chosen stand option
    if flag is False:
        print("Dealer's hand: ", end="")
        # show dealer's cards including hidden card
        dealer.show(False)
        print("Total points: " + str(dealer.point_calc()))
        print("Player's hand: ", end="")
        player.show(False)
        print("Total points: " + str(player.point_calc()))
        # As player chosen stand, player is impossible to  bust at this time
        if dealer.point_calc() > 21:
            print("Dealer busted, player wins!")
        elif dealer.point_calc() == 21:
            print("Dealer got a Blackjack, Dealer wins!")
        elif dealer.point_calc() > player.point_calc():
            print("Dealer has more points, Dealer wins!")
        elif dealer.point_calc() == player.point_calc():
            print("Tied up")
        else:
            print("Player has more points, player wins!")
        # This round is over
        replay()

    # else flag == True means player chosen hit
    else:
        print("")
        print("Dealer's hand: ", end="")
        dealer.show(True)
        print("")
        print("Player's hand: ", end="")
        player.show(False)
        print("Total points: " + str(player.point_calc()))
        # Player chosen hit, dealer is impossible to bust at this time
        if player.point_calc() > 21:
            print("Player busted, Dealer wins!")
            replay()
        elif player.point_calc() == 21:
            print("Player got a Blackjack, you win!")
            replay()
        # Player's points are less than 21, play has further choice
        else:
            print("Press 'h' to hit or 's' to stand")
            key = input().lower()
            while key != 'h' and key != 's':
                print("Wrong key, please press 'H' or 'S'")
                key = input().lower()
            if key == 'h':
                hit(dealer, player, deck)
            else:
                stand(dealer, player, deck)


# replay the game or exit the game
def replay():
    print("Press 'R' to replay or 'Q' to exit")
    key = input().lower()
    while key != 'r' and key != 'q':
        print("Wrong key, please press 'R' or 'Q'")
        key = input().lower()
    if key == 'r':
        game_start()
    else:
        game_exit()


# Exit the game
def game_exit():
    print("Thanks for playing Blackjack Game!")
    exit()


# Run the game
def game_start():
    print("Welcome to the Blackjack Game!")
    print("Press 'Q' to quit or any other key to continue.....")
    key = input().lower()
    if key == 'q':
        game_exit()
    else:
        game_setup()


if __name__ == "__main__":
    game_start()


