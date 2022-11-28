import loader
import numpy as np
from PIL import Image, ImageDraw
import math
import os

def render(filename, simName):
    try:
        os.mkdir("./renders/" + simName)
    except FileExistsError:
        if(input("Folder already exists,") != "y"):
            exit()
    finally:
        pass
    simData = loader.loader(filename)
<<<<<<< HEAD
    cam = camera(0, 1, 1, 2, 0, 1, 1)
    conf = config(10, "#306BAC", 0, 0, 1)
=======
    cam = camera(0, 1, 1, 2, 0, 1, 1, 1000, 1000)
    conf = config(40, "#306BAC", 20, 20, 5)
>>>>>>> 357d67df9ac6657cc9e8a3a12bbf6387bb48a920

    for i in range(len(simData)):
        print(f"Rendering frame {i}")
        renderStill(simName, i, simData[i], cam, conf)

def renderStill(simName, simId, currentVectors, cam, conf):
<<<<<<< HEAD
    im = Image.new("RGB", (1000, 1000),color="#E3E3E3")
=======
    im = Image.new("RGB", (cam.vw, cam.vh),color="#E3E3E3")
>>>>>>> 357d67df9ac6657cc9e8a3a12bbf6387bb48a920
    draw = ImageDraw.Draw(im, 'RGBA')

    for i in currentVectors:
        x,y = getPointPos(i,cam)
        if (-conf.scale < x < conf.scale) and (-conf.scale < y < conf.scale):
<<<<<<< HEAD
            xFactor = ( 500 - (conf.xMargin * 2) ) / conf.scale
            yFactor = ( 500 - (conf.yMargin * 2) ) / conf.scale
            draw.ellipse(
                [(500 + x*xFactor - (conf.circleSize / 2),500 + y*yFactor - (conf.circleSize / 2)),
                (500 + x*xFactor + (conf.circleSize / 2),500 + y*yFactor + (conf.circleSize / 2))
=======
            xFactor = ( (cam.vw/2) - (conf.xMargin * 2) ) / conf.scale
            yFactor = ( (cam.vh/2) - (conf.yMargin * 2) ) / conf.scale
            draw.ellipse(
                [((cam.vw/2) + x*xFactor - (conf.circleSize / 2),(cam.vh/2) + y*yFactor - (conf.circleSize / 2)),
                ((cam.vw/2) + x*xFactor + (conf.circleSize / 2),(cam.vh/2) + y*yFactor + (conf.circleSize / 2))
>>>>>>> 357d67df9ac6657cc9e8a3a12bbf6387bb48a920
                ],fill=conf.circleColor)
    
    draw.line([(0, 900), (1000, 900)], "#000000", 5)

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
    def __init__(self, a, b, c, d, xCamMiddle, yCamMiddle, zCamMiddle, vw, vh) -> None:
        self.a = a
        self.b = b
        self.c = c
        self.d = d
        self.xCamMiddle = xCamMiddle
        self.yCamMiddle = yCamMiddle
        self.zCamMiddle = zCamMiddle
        self.vw = vw
        self.vh = vh

class config():
    def __init__(self, circleSize, circleColor, xMargin, yMargin, scale) -> None:
        self.circleSize = circleSize
        self.circleColor = circleColor
        self.xMargin = xMargin
        self.yMargin = yMargin
        self.scale = scale