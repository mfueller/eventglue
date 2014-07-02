package mcr.robinson.ros;

import java.io.File;
import java.net.URL;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.Set;

import org.reflections.Reflections;

public class JavaPackageFinder {

	Class[] getClasses(String packagename, Class<?> interfaceClass) {
		
		Reflections reflections = new Reflections(interfaceClass);

	    Set<?> subTypes = reflections.getSubTypesOf(interfaceClass);
	    
	    return subTypes.toArray(new Class[subTypes.size()]);
	}
}
