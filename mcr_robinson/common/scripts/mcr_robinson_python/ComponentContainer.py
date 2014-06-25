
from mcr_robinson_python.DataPort import DataPortOutput

class State:
    IDLE = 0
    ACTIVE = 1

class Mode:
    ON_UPDATE = 0
    CYCLIC = 1
        
class ComponentContainer:

    
    state = State.IDLE
    init = False
    mode = Mode.ON_UPDATE
    
    updateEvent = DataPortOutput();
    initEvent = DataPortOutput();
    shutdownEvent = DataPortOutput();
    
    def __init__(self, component):
        self.component = component
        
        self.updateEvent.connect(component.update)
        self.initEvent.connect(component.init)
        self.shutdownEvent.connect(component.shutdown)
    
    def __del(self):
        self.shutdownEvent()
        
    def eventport_input_start(self):
        print("ComponentContainer::eventport_input_start")
        
        self.state = State.ACTIVE
        
        if (self.init == False):
            self.initEvent()
            self.init = True
            
    def eventport_input_stop(self):
        print("ComponentContainer::eventport_input_stop")
        
        self.state = State.IDLE

    def update(self):
        if (self.state == State.ACTIVE):
            self.updateEvent()

    def update_on_data(self):
        if (self.mode == Mode.ON_UPDATE):
            self.update()


    def update_cycle(self):
        if (self.mode == Mode.CYCLIC):
            self.update()
