package mcr.robinson;

import java.util.Vector;

public class EventOutputPort {
	
	protected Vector<IEventSlot> slots = new Vector<IEventSlot>();
	
	public void emit() {
		for (IEventSlot s : slots) {
			s.receive();
		}
	}
	
	public void connect(IEventSlot slot) {
		slots.add(slot);
	}
}
