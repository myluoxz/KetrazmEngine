#include <Engine/TextArray.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/Renderer.hpp>

engine::TextArray::TextArray(void)
	: _idTexture(0), _idVAO(0), _idVBO(0), _font(NULL)
{
	_mat = new glm::mat4;
}

engine::TextArray::~TextArray(void)
{
	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
	if (glIsVertexArray(_idVAO)) glDeleteVertexArrays(1, &_idVAO);
	if (glIsBuffer(_idVBO)) glDeleteBuffers(1, &_idVBO);
	if (_font) TTF_CloseFont(_font);
	delete _mat;
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::TextArray::config(const GLchar *font, const GLuint &size,
	const GLubyte &r, const GLubyte &g, const GLubyte &b,
	const GLuint &x, const GLuint &y, const GLuint &w, const GLuint &h, ShaderProgram *program, Renderer *renderer)
{
	SDL_Surface *t;

	if (glIsTexture(_idTexture)) glDeleteTextures(1, &_idTexture);
	if (glIsVertexArray(_idVAO)) glDeleteVertexArrays(1, &_idVAO);
	if (glIsBuffer(_idVBO)) glDeleteBuffers(1, &_idVBO);
	if (_font) TTF_CloseFont(_font);
	
	_color.r = r;
	_color.g = g;
	_color.b = b;
	_color.a = 0;
	
	_font = TTF_OpenFont(font, size);
	if(_font == NULL)
	{
		std::cerr << "Error while loading fontFile: " << font << std::endl;
		exit(1);
	}
	t = TTF_RenderText_Blended(_font, " ", _color);
	if(t == NULL)
	{
		std::cerr << "Error while creating RenderText" << std::endl;
		exit(1);
	}
	loadTextureFromSDL_Surface(t, &_idTexture);
	SDL_FreeSurface(t);
	
	GLfloat vertexArray[] = {
		(GLfloat)x, (GLfloat)y,
		0, 0,

		(GLfloat)x+w, (GLfloat)y,
		1, 0,

		(GLfloat)x, (GLfloat)y+h,
		0, 1,

		(GLfloat)x+w, (GLfloat)y+h,
		1, 1,
	};

	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
  
	glGenBuffers(1, &_idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertexArray, vertexArray, GL_STATIC_DRAW);
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
  
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(2*sizeof(GLfloat)));
	
	glBindVertexArray(0);

	_program = program;
	_MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
	_textureLocation = glGetUniformLocation(_program->getId(), "textTex");

	*_mat = glm::ortho(0.0f, (GLfloat)renderer->getWidth(), 0.0f, (GLfloat)renderer->getHeight(), -1.0f, 1.0f);
}

#undef BUFFER_OFFSET

void engine::TextArray::write(const GLchar *text)
{
	SDL_Surface *t;
	
	t = TTF_RenderText_Blended(_font, &text[0], _color);
	if(t == NULL)
	{
		std::cerr << "Error while creating RenderText" << std::endl;
		exit(1);
	}
	
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
	loadTextureFromSDL_Surface(t, &_idTexture);
	
	SDL_FreeSurface(t);
}

void engine::TextArray::display(Renderer *renderer)
{
	renderer->setState();

	glUseProgram(_program->getId());
	
	glUniformMatrix4fv(_MVPLocation, 1, GL_FALSE, glm::value_ptr(*_mat));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glUniform1i(_textureLocation, 0);

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	glUseProgram(0);
}