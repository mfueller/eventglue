package helloworld;

import helloworld.HelloWorldImpl;
import helloworld.IHelloWorld;
import mcr.robinson.ComponentContainer;
import mcr.robinson.ComponentContainer.Mode;
import mcr.robinson.DataInputSlot;
import mcr.robinson.EventInputSlot;
import mcr.robinson.PortUtils;
import mcr.robinson.adapter.Data2EventSlot;
import mcr.robinson.ros.PortUtilsROS;
import mcr.robinson.ros.PortWireingROS;

import org.ros.concurrent.CancellableLoop;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;

//Method method = scope.getClass().getMethod(methodName, getParameterClasses(parameters));
//return method.invoke(scope, parameters);

public class Main extends AbstractNodeMain {

	@Override
	public void onStart(ConnectedNode connectedNode) {

		IHelloWorld hw = new HelloWorldImpl();

		final ComponentContainer cc = new ComponentContainer(IHelloWorld.class, hw);
		// cc.setMode(Mode.CYCLIC);
		cc.setMode(Mode.ON_EVENT);

		PortUtilsROS rosutils = new PortUtilsROS(connectedNode);
		
		// for automatic connection generation
		// PortWireingROS hw_wiring = new PortWireingROS(IHelloWorld.class, hw, util);
		// hw_wiring.connectAllPorts();
		
		// or manual
		rosutils.EventOutputPortROS("event_name", "different_event")
				.connect(new EventInputSlot(hw, "event_in", "name"));

		hw.event_out_done.connect(rosutils.EventInputPortROS("event_out", "done"));

		hw.pout_answer.connect(rosutils.DataInputPortROS("pout_answer", String.class));

		rosutils.DataOutputPortROS("pin_name", String.class).connect(new DataInputSlot(hw, "name"));

		// could be wired automatically
		PortWireingROS cc_wiring = new PortWireingROS(ComponentContainer.class, cc, rosutils);
		cc_wiring.connectAllPorts();
		// or manually
		// util.EventOutputPortROS("event_in",
		// "e_start").connect(this.eventSlot(cc, "event_in", "e_start"));

		rosutils.DataOutputPortROS("pin_name", String.class).connect(
				new Data2EventSlot(new EventInputSlot(cc, "event_in", "update")));

		connectedNode.executeCancellableLoop(new CancellableLoop() {
			@Override
			protected void loop() throws InterruptedException {
				cc.update_cycle();

				Thread.sleep(100);
			}
		});
	}

	@Override
	public GraphName getDefaultNodeName() {
		return GraphName.of("Main");
	}
}
