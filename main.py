import argparse
# Algorithms
from DDA import DDA
from Bresenham import Bresenham
from NaiveSolution import NaiveSolution

# Initiate the args parser
parser = argparse.ArgumentParser()
# Verbose
parser.add_argument('-v', '--verbose', help='Verbose mode', action='store_true')
# ALGORITHMS
# Naive solution algorithm
parser.add_argument('-n', '--naive', help='Use naive solution algorithm', action='store_true')
# DDA algorithm
parser.add_argument('-d', '--dda', help='Use DDA algorithm', action='store_true')
# Bresenham algorithm
parser.add_argument('-b', '--bresenham', help='Use Bresenham algorithm', action='store_true')
# POINTS 
parser.add_argument('-x', '--x1', help='X coordinate of the first point')
parser.add_argument('-y', '--y1', help='Y coordinate of the first point')
parser.add_argument('-X', '--x2', help='X coordinate of the second point')
parser.add_argument('-Y', '--y2', help='Y coordinate of the second point')


# Read arguments from the command line
args = parser.parse_args()

#The algorithm to use
algorithm = None

#Points
x1 = x2 = y1 = y2 = 0

# FUNCTIONS

'''
This function only prints the message if verbose mode was specified as argument.
'''
def printVerbose(message):
    if(args.verbose):
        print(message)

'''
This function defines the algorithm to be used, acoording to the supplied algorithm as argument.
'''
def setAlgorithmToUse():
    global algorithm
    if args.bresenham:
        algorithm = Bresenham()
        printVerbose('Using Bresenham algorithm')
        return
    if args.dda:
        algorithm = DDA()
        printVerbose('Using dda algoritm')
        return
    if args.naive:
        algorithm = NaiveSolution()
        printVerbose('Using naive solution algoritm')
        return
    print('[ERROR]: An algorithm must be supplied')
    exit(1)

def getLinePoints():
    global x1, y1, x2, y2
    x1 = args.x1
    y1 = args.y1
    x2 = args.x2
    y2 = args.y2


def main():
    setAlgorithmToUse()
    getLinePoints()
    for j in range (1080):
        algorithm.setPixel(0, j, 255, 243, 210) 
    algorithm.write()
    # algorithm.drawLine(x1, y1, x2, y2)


if __name__ == '__main__':
    main()











