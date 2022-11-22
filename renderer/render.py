import loader
import numpy as np
from PIL import Image, ImageDraw
import math

def render(filename, simName):
    simData = loader.loader(filename)
    cam = camera(1, 1, 1, 3, 1, 1, 1)

def renderStill(simName, currentVectors):
    pass

def getPointPos(vec,cam):
    # Step one: de projected vector
    normalVecCam = [cam.a, cam.b, cam.c]
    normalizedNormalVector = normalize(normalVecCam)
    distCurrentVector = circleDistance(vec,cam)
    projectedPoint = [vec[0]+(normalizedNormalVector[0] * distCurrentVector), vec[1]+(normalizedNormalVector[1] * distCurrentVector), vec[2]+(normalizedNormalVector[2] * distCurrentVector)]

def normalize(vec):
    lSq = vec[0] ^ 2 + vec[1] ^ 2 + vec[2] ^ 2
    l = math.sqrt(lSq)
    return [vec[0] / l,vec[1] / l,vec[2] / l]

def circleDistance(vec, cam):
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