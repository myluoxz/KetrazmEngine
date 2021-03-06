#include <Engine/Graphics/Texture/TextureCube.hpp>

Engine::Graphics::TextureCube::TextureCube(void)
{
}

Engine::Graphics::TextureCube::~TextureCube(void)
{
}

Engine::Graphics::TextureType Engine::Graphics::TextureCube::getType(void) const
{
	return TEXTURE_CUBE_TYPE;
}

void Engine::Graphics::TextureCube::loadFromFiles(
	const GLchar *posx, const GLchar *negx,
	const GLchar *posy, const GLchar *negy,
	const GLchar *posz, const GLchar *negz)
{
	const GLchar *tex[] = { posx, negx, posy, negy, posz, negz };
	SDL_Surface *image[6];
	image[0] = IMG_Load(tex[0]);
	image[1] = IMG_Load(tex[1]);
	image[2] = IMG_Load(tex[2]);
	image[3] = IMG_Load(tex[3]);
	image[4] = IMG_Load(tex[4]);
	image[5] = IMG_Load(tex[5]);

	GLenum cube_map_target[] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
	glGenTextures(1, &_idTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _idTexture);

	for (int i = 0; i < 6; i++)
	{
		if (image[i] == NULL)
		{
			throw std::exception(std::string("Error while loading image: " + std::string(tex[i]) + "\n" + IMG_GetError()).c_str());
		}

		switch (image[i]->format->format)
		{
		case 386930691:
			glTexImage2D(cube_map_target[i], 0, GL_RGB8, image[i]->w, image[i]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i]->pixels);
			break;
		case 390076419:
			glTexImage2D(cube_map_target[i], 0, GL_RGB8, image[i]->w, image[i]->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image[i]->pixels);
			break;
		case 376840196:
			glTexImage2D(cube_map_target[i], 0, GL_RGBA8, image[i]->w, image[i]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[i]->pixels);
			break;
		case 372645892:
			glTexImage2D(cube_map_target[i], 0, GL_RGBA8, image[i]->w, image[i]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[i]->pixels);
			break;
		default:
			std::cerr << "Format " << image[i]->format->format << " unknown" << std::endl;
			break;
		}
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SDL_FreeSurface(image[i]);
	}
}