# Documentation for file protocol
## A single timeframe
To denote objects in a text file the following structure will be used:
```
    X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3
```
The stucture follows the csv file format and can continue for any number of objects.

## Multiple timeframes
Multiple timeframes shall also follow the csv file format. Each line in the file shall be a new timeframe.

## Example
Example file:
```
    2,3,5,1,1,2,3,4,3
    2,3,5,0,1,1,3,3,3
    1,1,1,0,0,0,2,2,2
```
In this example the first timeframe has three vectors, (2, 3, 4), (1, 1, 2) and (3, 4, 3). The next timeframe the vectors change to be, (2, 3, 5), (0, 1, 1) and (3, 3, 3). In the end the vectors will be (1, 1, 1), (0, 0, 0,) and (2, 2, 2).