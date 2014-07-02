package helloworld;


public class HelloWorldImpl extends IHelloWorld {

	
	String name;
	
	int counter = 0;
	
	public void pin_name(String name) {
		System.out.println("HelloWorld:pin_name: " + name);
		this.name = name;
	}
	
	public void event_in_hello() {
		System.out.println("HelloWorld:event_in_hello");
	}
	
	public void update() {
		System.out.println("HelloWorld:update");
		
		this.pout_answer.emit("Hello " + this.name + " - " + counter++);
		
		this.event_out_done.emit();
	}
	
	public void init() {
		System.out.println("HelloWorld:init");
	}
	
	public void shutdown() {
		System.out.println("HelloWorld:shutdown");
	}
	
}
