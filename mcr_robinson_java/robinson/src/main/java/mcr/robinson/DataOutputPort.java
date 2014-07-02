package mcr.robinson;

import java.util.Vector;


public class DataOutputPort<T> {
	
	protected Vector<IDataSlot<T>> slots = new Vector<IDataSlot<T>>();
	
	public void emit(T msg) {
		for (IDataSlot<T> s : slots) {
			s.receive(msg);
		}
	}
	
	public void connect(IDataSlot<T> slot) {
		slots.add(slot);
	}
}
