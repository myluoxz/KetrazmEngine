#include <Engine/Screen.hpp>

engine::Screen::Screen()
{
	_program = NULL;
}

engine::Screen::~Screen()
{
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::Screen::config(ShaderProgram *program)
{
	GLfloat vertex[] = {
		-1, -1,
		0, 0,
		
		1, -1,
		1, 0,
		
		-1,  1,
		0, 1,
		
		1,  1,
		1, 1
	};
	
	_program = program;
	_colorLocation = glGetUniformLocation(_program->getId(), "color");
	_materialTextureLocation = glGetUniformLocation(_program->getId(), "materialTexture");
	
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
  
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	glGenBuffers(1, &_idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertex, vertex, GL_STATIC_DRAW);
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(2*sizeof(GLfloat)));

	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::Screen::display(GBuffer *gbuf, const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a)
{
	if(_program==NULL)
	{
		std::cerr << "Can't diplay Screen without initialisation" << std::endl;
		return;
	}
  
	glDepthMask(GL_FALSE);
	glUseProgram(_program->getId());
	glBindVertexArray(_idVAO);

	glUniform4f(_colorLocation, r, g, b, a);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_MATERIAL));
	glUniform1i(_materialTextureLocation, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
	glBindVertexArray(0);
	glUseProgram(0);
	glDepthMask(GL_TRUE);
}
