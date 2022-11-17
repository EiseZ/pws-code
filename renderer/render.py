import loader
import numpy as np
from PIL import Image, ImageDraw
import math

def render(filename, simName):
    simData = loader.loader(filename)
    cam = camera(1, 1, 1, 3, 1, 1, 1)

def renderStill(simName, currentVectors):
    pass

def circleSize(vec, cam):
    x = vec[0]
    y = vec[1]
    z = vec[2]

    return math.abs((cam.a * x) + (cam.b * y) + (cam.c * z) - cam.d) / math.sqrt((cam.a*cam.a) + (cam.b*cam.b) + (cam.c*cam.c))

def circlePos(vec, cam):
    pass

class camera():
    def __init__(self, a, b, c, d, xCamMiddle, yCamMiddle, zCamMiddle) -> None:
        self.a = a
        self.b = b
        self.c = c
        self.d = d
        self.xCamMiddle = xCamMiddle
        self.yCamMiddle = yCamMiddle
        self.zCamMiddle = zCamMiddle