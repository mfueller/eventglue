#ifndef MESSAGECONVERTET_H_
#define MESSAGECONVERTET_H_

#include <string.h>

#include <ros/ros.h>

template <typename FROM, typename TO>
class MessageConverter {
public:
	static TO convert(FROM msg);
};

template <typename FROM, typename TO>
inline TO MessageConverter<FROM, TO>::convert(FROM msg) {
	TO msg_new;
	const char* from_type = typeid(FROM).name();
	const char* to_type = typeid(TO).name();

	std::stringstream ss;
	ss << "No Template function to convert " << from_type << " -> " << to_type << std::endl;
	ROS_ERROR(ss.str().c_str());
	return msg_new;
}

#endif
