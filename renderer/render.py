import loader
import numpy as np
from PIL import Image, ImageDraw
import math
import os

def render(filename, simName):
    os.mkdir("./renders/" + simName)
    simData = loader.loader(filename)
    cam = camera(0, 1, 1, 2, 0, 1, 1)
    conf = config(40, "#306BAC", 20, 20, 5)

    for i in range(len(simData)):
        renderStill(simName, i, simData[i], cam, conf)

def renderStill(simName, simId, currentVectors, cam, conf):
    im = Image.new("RGB", (1920, 1080),color="#E3E3E3")
    draw = ImageDraw.Draw(im, 'RGBA')

    for i in currentVectors:
        x,y = getPointPos(i,cam)
        if (-conf.scale < x < conf.scale) and (-conf.scale < y < conf.scale):
            xFactor = ( 960 - (conf.xMargin * 2) ) / conf.scale
            yFactor = ( 540 - (conf.yMargin * 2) ) / conf.scale
            draw.ellipse(
                [(960 + x*xFactor - (conf.circleSize / 2),540 + y*yFactor - (conf.circleSize / 2)),
                (960 + x*xFactor + (conf.circleSize / 2),540 + y*yFactor + (conf.circleSize / 2))
                ],fill=conf.circleColor)

    file_name = "renders/" + simName + "/" + str(simId) + '.png'
    im.save(file_name)

def getPointPos(vec,cam):
    # Step one: de projected vector
    normalVecCam = [cam.a, cam.b, cam.c]
    normalizedNormalVector = normalize(normalVecCam)
    distCurrentVector = circleDistance(vec,cam)
    projectedPoint = [vec[0]+(normalizedNormalVector[0] * distCurrentVector), vec[1]+(normalizedNormalVector[1] * distCurrentVector), vec[2]+(normalizedNormalVector[2] * distCurrentVector)]

    # Step two: position on plane
    localProjectedPoint = [projectedPoint[0]- cam.xCamMiddle, projectedPoint[1]- cam.yCamMiddle, projectedPoint[2]- cam.zCamMiddle]
    transformedPoint = [localProjectedPoint[0], math.sqrt( (localProjectedPoint[1]*localProjectedPoint[1]) + (localProjectedPoint[2]*localProjectedPoint[2]) )]

    return transformedPoint

def normalize(vec):
    lSq = (vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2])
    l = math.sqrt(lSq)
    return [vec[0] / l,vec[1] / l,vec[2] / l]

def circleDistance(vec, cam):
    x = vec[0]
    y = vec[1]
    z = vec[2]

    return abs((cam.a * x) + (cam.b * y) + (cam.c * z) - cam.d) / math.sqrt((cam.a*cam.a) + (cam.b*cam.b) + (cam.c*cam.c))

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

class config():
    def __init__(self, circleSize, circleColor, xMargin, yMargin, scale) -> None:
        self.circleSize = circleSize
        self.circleColor = circleColor
        self.xMargin = xMargin
        self.yMargin = yMargin
        self.scale = scale