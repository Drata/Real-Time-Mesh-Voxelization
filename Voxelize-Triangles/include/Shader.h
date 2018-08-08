#include "common.h"
#pragma once
#include "util.h"
#include "Vertex.h"


class Shader {
public:
	uint32_t getId() const;
	const char* getError();
	void use() const;
	void setupAttribs() const;
	int getLocation(const char* name) const;
	int getRetCode() const;
	void setInt(int loc, int val);
	void setFloat(int loc, float val);
	void setVec3(int loc, const glm::vec3& vec);
	void setVec4(int loc, const glm::vec4& vec);
	void setMatrix(int loc, const glm::mat4& mat);

	static std::shared_ptr<Shader> create(const char *vertexCode, const char * fragmentCode, const char * geometryShaderC);

protected:
	Shader(const char* vertexShaderC, const char* fragmentShaderC, const char * geometryShaderC);
	~Shader();
	static void destroy(Shader* p) {
		delete p;
	}

private:
	uint32_t id, program;
	int retCode, vposLoc;
    char errorLog[1024];
};