#include <Engine/Graphics/TextArray.hpp>

Engine::Graphics::TextArray::TextArray(const std::shared_ptr<ShaderProgram> &program)
	: _font(nullptr), _program(program)
{
	_texture = std::make_shared<Texture2D>();
	_vertexBuffer = std::make_shared<Buffer>();

	_vertexBuffer->createStore(GL_ARRAY_BUFFER, nullptr, 64, GL_STATIC_DRAW);

	glUseProgram(_program->getId());
	glUniform1i(glGetUniformLocation(_program->getId(), "textTexture"), 0);

	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

Engine::Graphics::TextArray::~TextArray(void)
{
	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::Graphics::TextArray::setFont(const GLchar *font, GLuint size, GLubyte r, GLubyte g, GLubyte b)
{
	if (_font) TTF_CloseFont(_font);
	_font = TTF_OpenFont(font, size);
	if (_font == nullptr)
	{
		throw std::runtime_error(std::string("Error while loading fontFile: " + std::string(font)));
	}

	_color.r = b;
	_color.g = g;
	_color.b = r;
	_color.a = 0;
}

void Engine::Graphics::TextArray::writeScreen(GLuint x, GLuint y, GLuint w, GLuint h, const GLchar *text)
{
	SDL_Surface *t;

	t = TTF_RenderText_Blended(_font, &text[0], _color);
	_texture->loadFromSDL_Surface(t);
	SDL_FreeSurface(t);

	GLfloat vertexArray[] =
	{
		static_cast<GLfloat>(x), static_cast<GLfloat>(y),
		0, 0,
		static_cast<GLfloat>(x) + w, static_cast<GLfloat>(y),
		1, 0,
		static_cast<GLfloat>(x), static_cast<GLfloat>(y) + h,
		0, 1,
		static_cast<GLfloat>(x) + w, static_cast<GLfloat>(y) + h,
		1, 1,
	};
	_vertexBuffer->updateStoreSub(vertexArray);
}

void Engine::Graphics::TextArray::writeScreen(const GLchar *text) const
{
	SDL_Surface *t;

	t = TTF_RenderText_Blended(_font, &text[0], _color);
	_texture->loadFromSDL_Surface(t);
	SDL_FreeSurface(t);
}

void Engine::Graphics::TextArray::display(const std::shared_ptr<CBuffer> &cbuf) const
{
	cbuf->setTransparentState();

	glUseProgram(_program->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
