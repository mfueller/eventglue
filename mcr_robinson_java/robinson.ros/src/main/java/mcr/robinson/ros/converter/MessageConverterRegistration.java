package mcr.robinson.ros.converter;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface MessageConverterRegistration {
	Class<?> LocalType();
	Class<? extends org.ros.internal.message.Message> ROSType();
}
