#include "../lib/glew/glew.h"
#include "shader.h"
#include "vertex.h"

std::string Shader::m_error;

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader) : m_program(0) {
	m_error = "";
	int retCode = GL_FALSE;
	char errorLog[1024];

	// create vertex shader
	uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderC = vertexShader.c_str();
	glShaderSource(vs, 1, &vertexShaderC, nullptr);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(vs, sizeof(errorLog), nullptr, errorLog);
		m_error = errorLog;
		glDeleteShader(vs);
		return;
	}

	// create fragment shader
	uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderC = fragmentShader.c_str();
	glShaderSource(fs, 1, &fragmentShaderC, nullptr);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(fs, sizeof(errorLog), nullptr, errorLog);
		m_error = errorLog;
		glDeleteShader(vs);
		glDeleteShader(fs);
		return;
	}
	
	// create geometry shader
	uint32_t gs = glCreateShader(GL_GEOMETRY_SHADER);
	const char* geometryShaderC = geometryShader.c_str();
	glShaderSource(fs, 1, &geometryShaderC, nullptr);
	glCompileShader(gs);
	glGetShaderiv(gs, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(gs, sizeof(errorLog), nullptr, errorLog);
		m_error = errorLog;
		glDeleteShader(vs);
		glDeleteShader(fs);
		glDeleteShader(gs);
	}
	
	// create program
	m_program = glCreateProgram();
	glAttachShader(m_program, vs);
	glAttachShader(m_program, fs);
	glLinkProgram(m_program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glGetProgramiv(m_program, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetProgramInfoLog(m_program, sizeof(errorLog), nullptr, errorLog);
		m_error = errorLog;
		return;
	}

	// get attrib locations
	m_vposLoc = glGetAttribLocation(m_program, "vpos");
	m_vTexLoc = glGetAttribLocation(m_program, "vtex");
	m_vNormLoc = glGetAttribLocation(m_program, "vnormal");
	m_vboneIndicesLoc = glGetAttribLocation(m_program, "vboneIndices");
	m_vboneWeightLoc = glGetAttribLocation(m_program, "vboneWeights");
}

Shader::~Shader() {
	if ( m_program != 0 ) glDeleteProgram(m_program);
}

std::shared_ptr<Shader> Shader::create(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader) {
	std::shared_ptr<Shader> p(new Shader(vertexShader, fragmentShader), [](Shader* p) { delete p; });
	if (m_error != "") p = nullptr;
	return p;
}

void Shader::use() const {
	glUseProgram(m_program);
}

void Shader::setupAttribs() const {
	if (m_vposLoc != -1) {
		glEnableVertexAttribArray(m_vposLoc);
		glVertexAttribPointer(m_vposLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	}
	if (m_vTexLoc != -1) {
		glEnableVertexAttribArray(m_vTexLoc);
		glVertexAttribPointer(m_vTexLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texture)));
	}
	if (m_vNormLoc != -1) {
		glEnableVertexAttribArray(m_vNormLoc);
		glVertexAttribPointer(m_vNormLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	}
	if (m_vboneIndicesLoc != -1) {
		glEnableVertexAttribArray(m_vboneIndicesLoc);
		glVertexAttribPointer(m_vboneIndicesLoc, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, bonesIndex)));
	}
	if (m_vboneWeightLoc != -1) {
		glEnableVertexAttribArray(m_vboneWeightLoc);
		glVertexAttribPointer(m_vboneWeightLoc, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, bonesWeight)));
	}
}

int Shader::getLocation(const char* name) const {
	return glGetUniformLocation(m_program, name);
}

void Shader::setInt(int loc, int val) {
	if ( loc != -1 ) glUniform1i(loc, val);
}

void Shader::setFloat(int loc, float val) {
	if (loc >= 0) glUniform1f(loc, val);
}

void Shader::setVec3(int loc, const glm::vec3& vec) {
	if (loc >= 0) glUniform3fv(loc, 1, glm::value_ptr(vec));
}

void Shader::setVec4(int loc, const glm::vec4& vec) {
	if (loc >= 0) glUniform4fv(loc, 1, glm::value_ptr(vec));
}

void Shader::setMatrix(int loc, const glm::mat4& matrix) {
	if (loc >= 0) glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix));
}
