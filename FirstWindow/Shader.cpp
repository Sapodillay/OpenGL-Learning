#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) 
{

	//assign texture type to type
	type = texType;

	//declare image metadata
	int widthImg, heightImg, numColCh;
	//Flip image as OpenGL works from bottom to top with textures
	stbi_set_flip_vertically_on_load(true);

	//load image into unsigned char array and store image metadata
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);


	//Generate texture
	glGenTextures(1, &ID);
	//Assign texture to a texture unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);


	//Configures the settings we want for the texture
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Assigns the image to the OpenGL texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	//delete the unused bytes and free the texture
	stbi_image_free(bytes);
	glBindTexture(texType, 0);


}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(tex0Uni, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}