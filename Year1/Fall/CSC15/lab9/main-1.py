# Team Members: Ryan Chen, Dylan Alflen, Brandon Sabillon, Manuel Lizzarzo 
# Description: Create a dice rolling game with betting abilities

# Importing necessary classes from player.py and dice.py
from player import Player
from dice import Dice

# Defining the DiceGame class
class DiceGame:
    # Initializing the game with players and maximum turns
    def __init__(self):
        # Creating four players
        self.players = [Player('Player 1'), Player('Player 2'), Player('Player 3'), Player('Player 4')]
        # Setting the maximum number of turns in a game
        self.max_turns = 12

    # Method to play a round of the game
    def play_round(self):
        # Creating an instance of the Dice class
        dice = Dice()

        # Looping through each turn
        for turn in range(1, self.max_turns + 1):
            # Printing the current turn
            print(f"\n----- Turn {turn} -----")

            # Looping through each player in the game
            for player in self.players:
                # Asking the player whether to roll or pass
                choice = input(f"{player.get_name()}, roll (r) or pass (p)? ").lower()

                # Checking the player's choice
                if choice == 'r':
                    # Rolling the dice and updating player's balance
                    dice_value = dice.roll()
                    print(f"{player.get_name()} rolled a {dice_value}.")
                    player.update_balance(dice_value)
                    print(f"{player.get_name()}'s total: ${player.get_balance()}")
                elif choice != 'p':
                    # Handling invalid choice and continuing to the next iteration
                    print("Invalid choice. Enter 'r' to roll or 'p' to pass.")
                    continue

            # Printing the current totals for all players
            print("\nCurrent Totals:")
            for player in self.players:
                print(f"{player.get_name()}: ${player.get_balance()}")

        # Determining the winner based on the maximum balance
        winner = max(self.players, key=lambda x: x.get_balance())
        # Printing the winner and their balance
        print(f"\nGame Over! {winner.get_name()} wins with ${winner.get_balance()}.")

# Main block
if __name__ == "__main__":
    # Creating an instance of the DiceGame class and playing a round
    game = DiceGame()
    game.play_round()
