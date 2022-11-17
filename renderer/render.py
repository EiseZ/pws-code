import loader
import numpy as np
from PIL import Image, ImageDraw

def render(filename, simName):
    simData = loader.loader(filename)

def renderStill(simName, currentVectors):
    pass

def circleSize(vec, cam):
    pass

def circlePos(vec, cam):
    pass

class camera():
    def __init__(self, a, b, c, d) -> None:
        self.a = a
        self.b = b
        self.c = c
        self.d = d