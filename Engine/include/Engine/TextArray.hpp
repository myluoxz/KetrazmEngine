#ifndef TEXT_ARRAY
#define TEXT_ARRAY

#include "Object.hpp"

namespace engine
{
	class Texture;
	class Buffer;
	class ShaderProgram;
	class Renderer;

	class DLLAPI TextArray : public Object
	{
	private:
		TTF_Font *_font;
		Texture *_texture;
		GLuint _idVAO;
		Buffer *_vertexBuffer;
		Buffer *_MVPMatrixBuffer;
		glm::mat4 *_mat;
		ShaderProgram *_program;
		SDL_Color _color;
	public:
		TextArray(void);
		~TextArray(void);
		void config(const GLchar *font, const GLuint &size,
			const GLubyte &r, const GLubyte &g, const GLubyte &b,
			const GLuint &x, const GLuint &y, const GLuint &w, const GLuint &h, ShaderProgram *program, Renderer *renderer);
		void write(const GLchar *text);
		void display(Renderer *renderer);
	};
}

#endif
