package mcr.robinson.adapter;

import mcr.robinson.IDataSlot;
import mcr.robinson.IEventSlot;

public class Data2EventSlot<T> implements IDataSlot<T> {
	
	IEventSlot slot;
	public Data2EventSlot(IEventSlot slot) {
		this.slot = slot;
	}
	
	@Override
	public void receive(T msg) {
		this.slot.receive();
	}
	
}
