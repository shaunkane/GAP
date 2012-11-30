import sys
import datetime
import pygame
import Controller

def handle(event, file):
    switch = {
            pygame.ACTIVEEVENT:       pActiveEvent,
            pygame.KEYDOWN:           pKeyDown,
            pygame.KEYUP:             pKeyUp,
            pygame.MOUSEMOTION:       pMouseMotion,
            pygame.MOUSEBUTTONUP:     pMouseButtonUp,
            pygame.MOUSEBUTTONDOWN:   pMouseButtonDown,
            pygame.JOYAXISMOTION:     pJoyAxisMotion,
            pygame.JOYBALLMOTION:     pJoyBallMotion,
            pygame.JOYHATMOTION:      pJoyHatMotion,
            pygame.JOYBUTTONUP:       pJoyButtonUp,
            pygame.JOYBUTTONDOWN:     pJoyButtonDown,
            pygame.VIDEORESIZE:       pVideoResize,
            pygame.VIDEOEXPOSE:       pVideoExpose,
            pygame.USEREVENT:         pUserEvent}
    if event.type in switch:
        switch[event.type](event, file)
    else:
        pDefault(event, file)

def pDefault(event, file):
    s = str(datetime.datetime.now()) + ",\
UNKOWNEVENT\
," + str(event.type) + "\n"

    print(s)
    file.write(s)

def pActiveEvent(event, file):
    s = str(datetime.datetime.now()) + ",\
ACTIVEEVENT\
," + str(event.gain) + "\
," + str(event.state) + "\n"

    print(s)
    file.write(s)

def pKeyDown(event, file):
    s = str(datetime.datetime.now()) + ",\
KEYDOWN\
," + str(event.unicode) + "\
," + str(event.key) + "\
," + str(event.mod) + "\n"
    
    print(s)
    file.write(s)

def pKeyUp(event, file):
    s = str(datetime.datetime.now()) + ",\
KEYUP\
," + str(event.key) + "\
," + str(event.mod) + "\n"
    
    print(s)
    file.write(s)

def pMouseMotion(event, file):
    s = str(datetime.datetime.now()) + ",\
MOUSEMOTION\
," + str(event.pos) + "\
," + str(event.rel) + "\
," + str(event.buttons) + "\n"

    print(s)
    file.write(s)

def pMouseButtonUp(event, file):
    s = str(datetime.datetime.now()) + ",\
MOUSEBUTTONUP\
," + str(event.pos) + "\
," + str(event.button) + "\n"

    print(s)
    file.write(s)

def pMouseButtonDown(event, file):
    s = str(datetime.datetime.now()) + ",\
MOUSEBUTTONDOWN\
," + str(event.pos) + "\
," + str(event.button) + "\n"

    print(s)
    file.write(s)

def pJoyAxisMotion(event, file):
    s = str(datetime.datetime.now()) + ",\
JOYAXISMOTION\
," + str(event.joy) + "\
," + str(event.axis) + "\
," + str(event.value) + "\
," + str(Controller.axisEng(event)) + "\n"

    print(s)
    file.write(s)

def pJoyBallMotion(event, file):
    s = str(datetime.datetime.now()) + ",\
JOYBALLMOTION\
," + str(event.joy) + "\
," + str(event.ball) + "\
," + str(event.rel) + "\n"

    print(s)
    file.write(s)

def pJoyHatMotion(event, file):
    s = str(datetime.datetime.now()) + ",\
JOYHATMOTION\
," + str(Controller.hatEng(event)) + "\
," + str(event.hat) + "\
," + str(event.value) + "\
," + str(event.joy) + "\n"
    
    print(s)
    file.write(s)

def pJoyButtonUp(event, file):
    s = str(datetime.datetime.now()) + ",\
JOYBUTTONUP\
," + str(Controller.buttonEng(event)) + "\
," + str(event.button) + "\
," + str(event.joy) + "\n"

    print(s)
    file.write(s)

def pJoyButtonDown(event, file):
    s = str(datetime.datetime.now()) + ",\
JOYBUTTONDOWN\
," + str(Controller.buttonEng(event)) + "\
," + str(event.button) + "\
," + str(event.joy) + "\n"

    print(s)
    file.write(s)

def pVideoResize(event, file):
    s = str(datetime.datetime.now()) + ",\
VIDEORESIZE\
," + str(event.size) + "\
," + str(event.w) + "\
," + str(event.h) + "\n"
    
    print(s)
    file.write(s)

def pVideoExpose(event, file):
    s = str(datetime.datetime.now()) + ",\
VIDEOEXPOSE" + "\n"
    
    print(s)
    file.write(s)

def pUserEvent(event, file):
    s = str(datetime.datetime.now()) + ",\
USEREVENT\
," + event.code + "\n"
    
    print(s)
    file.write(s)
