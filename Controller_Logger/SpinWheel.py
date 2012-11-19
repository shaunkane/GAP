import sys
import pygame

class SpinWheel(pygame.sprite.Sprite):
	# The little 'progress' spin wheel that spins during program execution.

	def __init__(self):
		pygame.sprite.Sprite.__init__(self)
		screen = pygame.display.get_surface()

		self.image, self.rect = loadImage("./Resources/Images/ring.png", -1)
		self.area = screen.get_rect()
		self.image = pygame.transform.scale(self.image, (int(self.area.width / 2), int(self.area.height / 2)))
		self.original = self.image
		self.rect.center = (self.area.width / 2), (self.area.height / 2)

		self.angle = 0
		self.spinspeed = -15

	def update(self):
		self._spin()

	def _spin(self):
		center = self.rect.center
		self.angle = self.angle + self.spinspeed

		if self.angle >= 360:
			self.angle = 0
			self.image = self.original
		else:
			self.image = pygame.transform.rotate(self.original, self.angle)

		self.rect = self.image.get_rect()
		self.rect.center = center

def loadImage(name, colorKey=None):
	try:
		image = pygame.image.load(name)
	except pygame.error as variable:
		sys.stderr.write("Error: Cannot load image - [", name, "].\n")
		raise SystemExit
	
	image = image.convert()

	return image, image.get_rect()