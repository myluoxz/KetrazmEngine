#ifndef GBUFFER
#define GBUFFER

#include "FrameBuffer.hpp"
#include "Renderer.hpp"

#define GBUF_NUM_TEX 3
#define GBUF_NORMAL 0
#define GBUF_MATERIAL 1
#define GBUF_DEPTH 2

namespace engine
{
	class DLLAPI GBuffer : public FrameBuffer
	{
	private:
		GLuint _idTexture[GBUF_NUM_TEX];
	public:
		GLenum colorAttachment[GBUF_NUM_TEX-1];
		GBuffer(void);
		~GBuffer(void);
		void config(const GLuint &width, const GLuint &height);
		GLuint getIdTexture(const GLuint &num) const;
		void display(Renderer *r, const GLuint &buf) const;
		void clear(void) const;
	};
}

#endif
