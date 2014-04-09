#ifndef GL_CONTEXT
#define GL_CONTEXT

#include "GL.hpp"
#include "ShaderProgram.hpp"
#include "matrix.h"

namespace engine
{
  class GLcontext
  {
  private:
    ShaderProgram *_program;
  public:
    GLfloat _biasMatrix[16];
    static GLuint width;
    static GLuint height;
    static GLfloat near;
    static GLfloat far;
    GLint camMatrixLocation;
    GLint biasLightMatrixLocation;
    GLint modelMatrixLocation;
    GLint matAmbientLocation;
    GLint matDiffuseLocation;
    GLint matSpecularLocation;
    GLint matShininessLocation;
    GLint camPositionLocation;
    GLint lightPositionLocation;
    GLint lightDirectionLocation;
    GLint lightSpotCutOffLocation;
    GLint lightAmbientLocation;
    GLint lightDiffuseLocation;
    GLint lightSpecularLocation;
    GLint textureLocation;
    GLint shadowTextureLocation;
    GLcontext(void);
    ~GLcontext(void);
    static void config(const GLuint &w, const GLuint &h, const GLfloat &n, const GLfloat &f);
    static void clear(void);
    void setShaderProgram(ShaderProgram *program);
    GLuint getProgramId(void);
  };
}


#endif
