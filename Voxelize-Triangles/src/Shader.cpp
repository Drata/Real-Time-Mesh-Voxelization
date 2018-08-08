#include "../include/Shader.h"

Shader::Shader(const char * vertexShaderC, const char * fragmentShaderC, const char * geometryShaderC)
{
	uint32_t vs, fs, gs;

	retCode = GL_FALSE;
	
	//Create vertex shader
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShaderC, nullptr);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &retCode);

	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(vs, sizeof(errorLog), nullptr, errorLog);
		return;
	}

	//Create geometry shader
	gs = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(gs, 1, &geometryShaderC, nullptr);
	glCompileShader(gs);
	glGetShaderiv(gs, GL_COMPILE_STATUS, &retCode);

	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(gs, sizeof(errorLog), nullptr, errorLog);
		return;
	}

	//Create fragment shader
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentShaderC, nullptr);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &retCode);

	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(fs, sizeof(errorLog), nullptr, errorLog);
		return;
	}

	//Create program
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glAttachShader(program, gs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &retCode);

	if (retCode == GL_FALSE) {
		glGetProgramInfoLog(program, sizeof(errorLog), nullptr, errorLog);
		return;
	}

	//Delete shaders
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(gs);

	//Setup attribute vars
	vposLoc = glGetAttribLocation(program, "vpos");
}

uint32_t Shader::getId() const
{
	return id;
}

const char * Shader::getError()
{
	return errorLog;
}

void Shader::use() const
{
	//Use program
	glUseProgram(program);
}

void Shader::setupAttribs() const
{
	glEnableVertexAttribArray(vposLoc);
	glVertexAttribPointer(vposLoc, 3, GL_FLOAT, false, sizeof(Vertex), 0);
}
int Shader::getLocation(const char * name) const
{
	return glGetUniformLocation(program, name);
}

int Shader::getRetCode() const
{
	return retCode;
}

void Shader::setInt(int loc, int val)
{
	glUniform1i(loc, val);
}

void Shader::setFloat(int loc, float val)
{
	glUniform1f(loc, val);
}

void Shader::setVec3(int loc, const glm::vec3 & vec)
{
	glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::setVec4(int loc, const glm::vec4 & vec)
{
	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMatrix(int loc, const glm::mat4 & mat)
{
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

std::shared_ptr<Shader> Shader::create(const char * vertexCode, const char * fragmentCode, const char * geometryShaderC)
{
	std::shared_ptr<Shader> sh(new Shader(vertexCode, fragmentCode, geometryShaderC), destroy);
	
	if (sh->getRetCode() != 1) {
		sh = nullptr;
	}

	return sh;
}

Shader::~Shader()
{
	glDeleteProgram(id);
}
