class Player:
  def __init__(self, name):
      self.name = name
      self.balance = 100
#Allows for a set of different players whos names can be changed by the user
  def get_name(self):
      return self.name
#Returns the current balance of the player at any given time
  def get_balance(self):
      return self.balance
#Updates balance of player at time of post-roll
  def update_balance(self, amount):
      self.balance += amount

