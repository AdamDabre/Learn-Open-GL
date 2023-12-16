#include "Texture.h"

Texture::Texture(const char* imagePath, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = textureType;

		// Storing the meta data for the image
	int imageWidth, imageHeight, numChannels;

		// fliping the images so the appear in correct orientation
	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(imagePath, &imageWidth, &imageHeight, &numChannels, 0);
		
		// Generating an ID for a texture
	glGenTextures(1, &this->ID);

		// Assigns the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(textureType, ID);

		// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Configures the way the texture repeats (if it does at all)
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Assigns the image to the OpenGL Texture object
	glTexImage2D(textureType,0,GL_RGBA,imageWidth,imageHeight,0,format,pixelType,bytes);

		// Generate a mipmap for the image
	glGenerateMipmap(textureType);

		// Deletes the image data after we bind the data to an OpenGL Texture Object
	stbi_image_free(bytes);

		// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(textureType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint  unit)
{
		// Gets the location of the uniform
	GLuint textUni = glGetUniformLocation(shader.ID, uniform);

		// Shaders need to be activated before modifying the value of a uniform
	shader.activate();

		// setting the value of the uniform
	glUniform1i(textUni, unit);

}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}