
from mcr_robinson_python.DataPort import DataPortOutput, EventPortOutput

class HelloWorld:
    '''
    classdocs
    '''

    pout_answer = DataPortOutput()
    
    eventport_output_done = EventPortOutput()
    
    def __init__(self):
        '''
        Constructor
        '''
        self.counter = 0
        print("HelloWorld (python) initialized")
        
    def update(self):
        msg = str("Hello " + self._pin_name + " " + str(self.counter))
        self.counter += 1
        self.pout_answer(msg)
        self.eventport_output_done()
        print("HelloWorld.update: " + msg)
        
    _pin_name = ""
    def pin_name(self, name):
        print("HelloWorld.pin_name: " + name)
        self._pin_name = name

    def init(self):
        print("HelloWorld.init")
        
    def shutdown(self):
        print("HelloWorld.shutdown")