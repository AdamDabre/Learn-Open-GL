#pragma once
#include<glad/glad.h>
#include "stb_image.h"

#include "../shaders/Shader.hpp"

class Texture
{
public:
		// The unique ID for the Texture
	GLuint ID;
		// The type the texture is 
	GLenum type;
		// The constructor for the clas
	Texture(const char* imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};
