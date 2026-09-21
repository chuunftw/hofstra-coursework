class MyCircleClass:
  def __init__(self, radius):
    self.radius = radius
  def getDiameter(self):
    return self.radius * 2
  def getArea(self):
    return 3.14 * self.radius**2
  def getCircumference(self):
    return self.radius * 2 * 3.14