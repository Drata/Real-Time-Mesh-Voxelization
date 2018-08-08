#pragma once

#include "common.h"

class Shader {
public:
	static std::shared_ptr<Shader> create(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);

	// Devuelve el identificador de OpenGL del programa
	uint32_t getId() const { return m_program; }

	// Obtiene el mensaje de error generado al compilar o enlazar
	static const std::string& getError() { return m_error; }

	// Activa el uso de este programa
	void use() const;

	// Activa la escritura de las variables attribute, y especifica su formato
	void setupAttribs() const;

	// Obtiene la localización de una variable uniform
	int getLocation(const char* name) const;

	// Da valor a una variable uniform
	void setInt(int loc, int val);
	void setFloat(int loc, float val);
	void setVec3(int loc, const glm::vec3& vec);
	void setVec4(int loc, const glm::vec4& vec);
	void setMatrix(int loc, const glm::mat4& matrix);
protected:
	Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
	~Shader();
private:
	uint32_t			m_program;
	static std::string	m_error;
	int					m_vposLoc;
	int					m_vTexLoc;
	int					m_vNormLoc;
};