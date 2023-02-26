import pandas as pd
import numpy as np
import math
import sys
csv = pd.read_csv(sys.argv[1], header=None)
csv = csv[csv.columns[-1]]
csv = csv.to_numpy()
print(csv[-1] - csv[1])
