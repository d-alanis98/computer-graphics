import numpy

class FHDRaster:

    def __init__(self):
        self.data = None
        self.initData()
    
    def initData(self):
        self.data = numpy.zeros((1920, 1080, 3))

    def write(self):
        print(self.data)
    
    def drawLine(self, x1, y1, x2, y2):
        print('Drawing line from (%d, %d) to (%d, %d)' % (x1, y1, x2, y2))
