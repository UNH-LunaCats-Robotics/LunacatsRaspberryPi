import SerialMessages;


def startup():
    SerialMessages.startup()

def sendMessage(data):
    return SerialMessages.send_json(data)