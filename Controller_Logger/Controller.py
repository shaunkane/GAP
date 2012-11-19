import sys
import math
import pygame

axisMap = {
		   0:   "Left Joy",
		   1:   "Left Joy",
		   3:   "Right Joy",
		   4:   "Right Joy",
		   2:   "Trigger"}
buttonMap = {
		   0:   "A Button",
		   1:   "B Button",
		   2:   "X Button",
		   3:   "Y Button",
		   4:   "Left Bumper",
		   5:   "Right Bumper",
		   6:   "Back",
		   7:   "Start",
		   8:   "Left Joy",
		   9:   "Right Joy"}
hatMap = {}

def bio(joy, file):

	s = "All About Me\n\
------------\n\
Joystick ID: " + str(joy.get_id()) + "\n\
Joystick Name: " + str(joy.get_name()) + "\n\
------------\n\
Buttons: " + str(joy.get_numbuttons()) + "\n\
Trackballs: " + str(joy.get_numballs()) + "\n\
Hats: " + str(joy.get_numhats()) + "\n\
Axes: " + str(joy.get_numaxes()) + "\n\n"
	
	print(s)
	file.write(s)

def axisEng(event):
	eng = ""

	# The behavior of the triggers is a little funny to figure out. 
	# The two triggers seems to act like counter-balances.
	# When they're in equilibrium, the pressure reads 0%.
	if axisMap[event.axis] == "Trigger":
		pressure = int(event.value * 100)

		if pressure == 0:
			eng += "(Released) "
		elif pressure > 0:    
			eng += "Left "
		else:
			eng += "Right "
		eng += axisMap[event.axis] + " (" + str(abs(pressure)) + "%)"

	# The only other axis-based devices are the right and left joysticks.
	# Because we're doing everything event driven, there needs to be
	# a couple of gets to generate meaningful output (i.e., coordinates).
	# Basically, I cue on an event to pull an entire coordinate.
	else:
		# You have to "init" a controlled to pull coordinates off of it,
		# because those values don't get passed along to the event.
		controller = pygame.joystick.Joystick(event.joy)
		direction = 0
		magnitude = 0

		# Excuse the magic numbers. I'll think of a more elegent solution later.
		# These are the axes for the left joystick.
		if event.axis == 0 or event.axis == 1:
			axisX = controller.get_axis(0)
			axisY = controller.get_axis(1)
			magnitude = math.sqrt(math.pow(axisX, 2) + math.pow(axisY, 2)) * 100
			direction = math.degrees(math.atan2(axisY, axisX)) + 90
		# These are the axes for the right joystick.
		elif event.axis == 3 or event.axis == 4:
			axisX = controller.get_axis(4)
			axisY = controller.get_axis(3)
			magnitude = math.sqrt(math.pow(axisX, 2) + math.pow(axisY, 2)) * 100
			direction = math.degrees(math.atan2(axisY, axisX)) + 90

		if direction < 0:
			direction += 360

		eng += axisMap[event.axis] + " (" + str(int(magnitude)) + "% @ " + str(int(direction)) + "\xb0)"

	return eng

def buttonEng(event):
	eng = ""

	eng += buttonMap[event.button]

	return eng

def hatEng(event):
	eng = ""

	if event.value[1] < 0:
		eng += "Bottom "
	elif event.value[1] > 0:
		eng += "Top "

	if event.value[0] == 0:
		eng += "Center"
	elif event.value[0] < 0:
		eng += "Left"
	elif event.value[0] > 0:
		eng += "Right"
	
	return eng

