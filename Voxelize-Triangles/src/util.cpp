#include "../include/util.h"

std::string readString(const std::string& filename) {
	std::ifstream istream(filename.c_str(), std::ios_base::binary);
	std::stringstream sstream;
	sstream << istream.rdbuf();
	return sstream.str();
}

bool init() {
	//Init glew
	if (glewInit()) {
		return GL_FALSE;
	}

	//Enable gl states
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);

	return GL_TRUE;
}
