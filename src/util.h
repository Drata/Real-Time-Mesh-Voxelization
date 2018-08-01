#pragma once

#include <fstream>
#include <sstream>
#include <string>

inline std::string readString(const char* filename) {
	std::ifstream f(filename, std::ios_base::binary);
	std::stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}