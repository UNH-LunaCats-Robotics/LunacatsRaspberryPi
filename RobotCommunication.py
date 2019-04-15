from SerialMessages import *

################################################################
#
# These are integers that tell the robot which type of command you're going to run
# This list must also be on the arduino code, and it must be the same
#
################################################################

Forward = 0
Back = 1
Left = 2
Right = 3
Stop = 4

################################################################
#
# These are Json formats for commands to send to the robot
#
################################################################


def single_command(cmd):
    return {"c": cmd}


def drive_command(cmd, power, timing):
    """Creates a json string for a drive command, this shouldn't be called outside of this function"""
    if timing == 0:

        return {
            "c": str(cmd),
            "p": int(power)
        }
    else:
        return {
            "c": str(cmd),
            "p": int(power),
            "t": int(timing)
        }


################################################################
#
# These are functions that will send commands to the arduino
#
################################################################

def forward(power, timing=0):
    """This will make the robot drive forward, up to a certain amount of time, (0 means forever)"""
    return send_json(drive_command(Forward, power, timing))


def back(power, timing=0):
    """This will make the robot drive back, up to a certain amount of time, (0 means forever)"""
    return send_json(drive_command(Back, power, timing))


def left(power, timing=0):
    """This will make the robot drive left, up to a certain amount of time, (0 means forever)"""
    return send_json(drive_command(Left, power, timing))


def right(power, timing=0):
    """This will make the robot drive right, up to a certain amount of time, (0 means forever)"""
    return send_json(drive_command(Right, power, timing))


def stop():
    """This will stop the robot"""
    return send_json(single_command(Stop))


def test():
    print("Hello!")
