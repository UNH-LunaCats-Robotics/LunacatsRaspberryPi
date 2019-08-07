from enum import Enum

class DetectedType(Enum):
    HILL = 1
    HOLE = -1
    NONE = 0