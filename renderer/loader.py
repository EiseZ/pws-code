import pandas as pd
import numpy as np
import math
def loader(filename):
    csv = pd.read_csv(filename, header=None)
    numpyArray = csv.to_numpy()
    return numpyArray.reshape(len(numpyArray), math.floor(len(numpyArray[0]) / 3), 3)