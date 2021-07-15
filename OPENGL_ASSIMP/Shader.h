#pragma once
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
	Shader();
	~Shader();
	Shader(const char * vertexPath, const char * fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;//ShaderProgramµÄID
	enum Slot
	{
		DIFFUSE,
		SPECULAR
	};
	void setUniform3f(const char* paraNameString, glm::vec3 param);
	void setUniform1f(const char* paraNameString, float param);
	void setUniformli(const char* paraNameString, int slot);
	void use();
private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

