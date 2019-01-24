#include "TextureContainer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image\stb_image.h"

#include "GameConstants\GameConstants.h"

TextureContainer::TextureContainer()
{
	stbi_set_flip_vertically_on_load(true);

    int textureCount = GameConstants::TextureData.GetTextureCount();
    int fontCount = GameConstants::FontData.FontCount();
    m_TextureHandles.reserve(textureCount + fontCount);

    for (int i = 0; i < textureCount; ++i)
    {
        GLuint texture = LoadTexture(GameConstants::TextureData.GetTextureDataWithID(i).Path(), i, GL_RGBA);
        m_TextureHandles.emplace_back(texture);
    }

    for (int i = 0; i < fontCount; ++i) 
    {
        const FontData& fontData = GameConstants::FontData.GetFontDataWithName(static_cast<FontName>(i));
        std::string path = "Resources/Textures/Fonts/" + fontData.GetFontName() + ".png";
        GLuint texture = LoadTexture(path, textureCount + i, GL_RED);
    }
}

TextureContainer::~TextureContainer()
{
    glDeleteTextures(m_TextureHandles.size(), m_TextureHandles.data());
}

GLuint TextureContainer::LoadTexture(const std::string& path, int textureIndex, int textureFormat)
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data == nullptr)
	{
		printf("stb_image: Could not load image '%s'\n", path.c_str());
	}

    int imageFormat = nrChannels == 3 ? GL_RGB : GL_RGBA;
 	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	
	stbi_image_free(data);

    return texture;
}
