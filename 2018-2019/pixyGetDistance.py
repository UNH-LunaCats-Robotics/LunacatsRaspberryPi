pixelsWidth = 400
pixelsHeight = 300
boxWidth = 0.1  # Measurment in meters
boxHeight = 0.3 # Measurment in meters

widthOfObject  = 80
heightOfObject = 50



#Formula = FocalLengthWidth = (pixels * knowdistanceininches) / widthOfObject
#Distance = (widthOfObject * FocalLengthWidth) / pixelsWidth
#focal length and distance for height is calculated the same way replacing width with height values

def getFocalLength(data,KnownDistance):
    global pixelsWidth,pixelsHeight,boxWidth,boxHeight,widthOfObject,heightOfObject,FocalLengthWidth,FocalLengthHeight
    FocalLengthWidth =  (data["W"]   * KnownDistance) / widthOfObject
    FocalLengthHeight = (data["H"]   * KnownDistance) / heightOfObject

def getDistance(data):
    global pixelsWidth,pixelsHeight,boxWidth,boxHeight,widthOfObject,heightOfObject,FocalLengthWidth,FocalLengthHeight
    focalWidthMeasure  =  (widthOfObject * FocalLengthWidth) / data["W"]
    focalHeightMeasure =  (heightOfObject * FocalLengthHeight) / data["H"]
    return (focalWidthMeasure + focalHeightMeasure)/2


if __name__ == "__main__":
    data = {"H":6,"W":14,"Y":56,"X":135,"S":1}
    getFocalLength(data,3)

    data = {"H":6,"W":28,"Y":112,"X":135,"S":1}
    print(str(getDistance(data)))