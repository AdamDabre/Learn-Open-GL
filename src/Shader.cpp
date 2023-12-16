#include "../src/shaders/Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. Reading the files to get the source code for the shaders
	std::string vertexCodeSource;
	std::string fragmentCodeSource;

	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	// ensure ifstream objects can throw exceptions:
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// opening the files
	try
	{
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// convert stream into string
		vertexCodeSource = vShaderStream.str();
		fragmentCodeSource = fShaderStream.str();
	}
	catch (std::ifstream:: failure e)
	{
		std::cout << "ERROR :: SHADER ::FILE_READ_ERROR" << std::endl;
	}
	const char* vertexCode = vertexCodeSource.c_str();
	const char* fragmentCode = fragmentCodeSource.c_str();

	// 2. Now that shaders content has been read, its time to compile them.

	unsigned int vertexInt, fragmentInt;

	int successVertex;
	char infoLogVertex[512];
	// vertex Shader
	vertexInt = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexInt, 1, &vertexCode, NULL);
	glCompileShader(vertexInt);

		// Error checking and printing any issues to the screen
	glGetShaderiv(vertexInt, GL_COMPILE_STATUS, &successVertex);
	if (!successVertex)
	{
		glGetShaderInfoLog(vertexInt, 512, NULL, infoLogVertex);
		std::cout << "ERROR :: SHADER ::VERTEX:: COMPILIATION FAILED \n" << infoLogVertex << std::endl;
	}

	int successFragment;
	char infoLogFragment[512];

	fragmentInt = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentInt, 1, &fragmentCode, NULL);
	glCompileShader(fragmentInt);

	glGetShaderiv(fragmentInt, GL_COMPILE_STATUS, &successFragment);
	if (!successFragment)
	{
		glGetShaderInfoLog(fragmentInt, 512, NULL, infoLogFragment);
		std::cout << "ERROR :: SHADER ::FRAGMENT:: COMPILIATION FAILED \n" << infoLogFragment << std::endl;
	}

	// 3. Creating the shader program by linking the two programs we made together
	// Generating this shader an ID
	this->ID = glCreateProgram();
	glAttachShader(ID, vertexInt);
	glAttachShader(ID, fragmentInt);
	glLinkProgram(ID);

	// checking if any linking errors have occured
	int successLinking;
	char infoLogLinking[512];
	glGetProgramiv(this->ID, GL_LINK_STATUS, &successLinking);

	if (!successLinking)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLogLinking);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogLinking << std::endl;
	}
	
	glDeleteShader(vertexInt);
	glDeleteShader(fragmentInt);
}

// using the program, gets called before renders
void Shader::activate()
{
	glUseProgram(ID);
}

	// setting values in the uniforms
void Shader:: setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this ->ID, name.c_str()), (int)value);
}
void Shader:: setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
void Shader:: setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}
	// Vectors
void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
}

void Shader:: setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}


void Shader:: setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader:: setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}