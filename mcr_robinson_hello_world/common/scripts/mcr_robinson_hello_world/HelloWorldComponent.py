
from mcr_robinson_python.DataPort import PortOutput

class HelloWorld:
    '''
    classdocs
    '''

    pout_string = PortOutput()
    
    
    def __init__(self):
        '''
        Constructor
        '''
        print("HelloWorldComponent (python) initialized")
        
    def update(self):
        msg = str("Hello " + self._pin_name)
        self.pout_string(msg)
        print("UPDATE called: " + msg)
        
    _pin_name = ""
    def pin_name(self, name):
        print("pin_name: " + name)
        self._pin_name = name
        
    def pin_test(self, test):
        print("pin_test: " + str(test.name) + "-" + str(test.year))
        self._test = test
