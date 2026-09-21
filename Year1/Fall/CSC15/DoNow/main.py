from MyCircleClass import MyCircleClass
import random
r= random.randint(1,9)
circle_1 = MyCircleClass(r)
circle_1_dia = circle_1.getDiameter()
circle_1_area = circle_1.getArea()
circle_1_cum = circle_1.getCircumference()

print("The radius ", circle_1.radius)
print("The diameter = ", circle_1_dia)
print("The area is = ",circle_1_area)
print("The circumference = ", circle_1_cum)