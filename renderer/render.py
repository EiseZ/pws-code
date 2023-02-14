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
    conf = config(20,"#306BAC", 315, 120, 1)

    for i in range(len(simData)):
        renderStill(simName, i, simData[i], math.floor(3150/2), 1200, conf)

def renderStill(simName, simId, currentVectors, width, height, conf):
    im = Image.new("RGB", ((width + conf.xMargin), (height+conf.yMargin)),color="#E3E3E3")
    draw = ImageDraw.Draw(im, 'RGBA')
    for i in currentVectors:
        x = (i[0]/2) * 10000 + (width/2) + (conf.xMargin/2)
        y = height - ((i[1]/2) * 10000) + (conf.yMargin/2)

        draw.ellipse(
            [(x-(conf.circleSize / 2),y-(conf.circleSize/2)), (x+(conf.circleSize/2),y+(conf.circleSize/2))]
            ,fill=conf.circleColor)

    file_name = "renders/" + simName + "/" + str(simId) + '.png'
    im.save(file_name)

class config():
    def __init__(self, circleSize, circleColor, xMargin, yMargin, scale) -> None:
        self.circleSize = circleSize
        self.circleColor = circleColor
        self.xMargin = xMargin
        self.yMargin = yMargin
        self.scale = scale
