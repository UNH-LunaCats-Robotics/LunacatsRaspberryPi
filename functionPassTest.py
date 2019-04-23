taskInput = ""

def terminTask():
    global taskInput
    while taskInput != "S":
        taskInput = raw_input("Input")


def performAction(action, args): 
	if taskInput != "S":
		action(args)
		return False
	return True
		

def test(stringToPrint):
    print stringToPrint
    


test("Hello")

if performAction(test,"Test Action"):
	print "Got True!"
else:
	print "Got False!"

terminTask()

if performAction(test,"Test Action 2"):
	print "Got True!"
else:
	print "Got False!"