#ifndef OBJECT
#define OBJECT

#include "GL.hpp"
#include "Renderer.hpp"
#include "Light.hpp"

namespace engine
{
  class Object
  {
    friend int comparObject(const void *p1, const void *p2);
  private:
    Renderer *_context;
    GLuint _idTexture;
    GLuint _idVAO;
    GLuint _idVBO[2];
    GLfloat _matAmbient[4];
    GLfloat _matDiffuse[4];
    GLfloat _matSpecular[4];
    GLfloat _matShininess[1];
    GLuint _numElement;
  public:
    Object(void);
    ~Object(void);
    void setRenderer(Renderer *context);
    void setTexture(const GLuint &id);
    void setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
    void setShininess(const GLfloat &x);
    GLfloat getTransparency(void);
    void load(const GLuint &sizeVertexArray, const GLfloat *vertexArray,
	      const GLuint &sizeIndexArray, const GLuint *indexArray);
    void display(void) const;
    void displayShadow(Light *l) const;
  };
  
  int comparObject(const void *p1, const void *p2);
  
}


#endif