package mcr.robinson;


public interface IDataSlot<T> {
	
	void receive(T msg);

}
