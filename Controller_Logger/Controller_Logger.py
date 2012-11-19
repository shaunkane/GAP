#python

import sys
import datetime
import time
import pygame
from SpinWheel import SpinWheel
import Controller
import EventHandler

def main():
	pygame.init()

	# Just a couple of env variables.
	size = width, height = 250, 250
	black = (0, 0, 0)

	screen = pygame.display.set_mode(size)
	background = pygame.Surface(screen.get_size())
	background = background.convert()
	background.fill(black)
	pygame.display.set_caption("Controller Logger")
	
	# Initial screen render.
	screen.blit(background, (0, 0))
	pygame.display.flip()

	# A little "progress" spinner. Let's me know things are running.
	spinWheel = SpinWheel()
	file = open('./Resources/Controller_Logger_Log.txt', 'a')

	s = "\n******************************\n\
Launching Controller_Logger...\n\
******************************\n\n"

	file.write(s)

	# Setting up my spinner and frame clock.
	allSprites = pygame.sprite.RenderPlain((spinWheel))
	clock = pygame.time.Clock()

	# Find and initialize all of the fancy plug-in devices.
	s = "Joystick Initiailization: " + str(pygame.joystick.get_count()) + " Joystick(s) Detected\n"
	print(s)
	file.write(s)
	for joys in range(0, pygame.joystick.get_count()):
		joy = pygame.joystick.Joystick(joys)
		joy.init()
		Controller.bio(joy, file)

	# Start the main render loop.
	progRunMessage(file)
	while 1:
		# Keeps rendering at 60 frames/second.
		clock.tick(60)

		# Main event listener.
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				return progRunDone(file)
			else:
			   EventHandler.handle(event, file)

		# Keep the spinner up-to-date.
		allSprites.update()

		# Keep the screen up-to-date.
		screen.blit(background, (0, 0))
		allSprites.draw(screen)
		pygame.display.flip()

def progRunMessage(file):
	s = "\n*********************\n\
Starting Main Loop...\n\
*********************\n\n"
	
	print(s)
	file.write(s)

	return 0

def progRunDone(file):
	s = "\n*********************\n\
Exiting Main Loop...\n\
*********************\n\n"
	
	print(s)
	file.write(s)

	file.close()

	return 0

if __name__ == "__main__":
	sys.exit(main())