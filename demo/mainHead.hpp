#ifndef SEQUENCE
#define SEQUENCE

#define ESC 41
#define MAJ 225

#include <Engine/Window.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/DirLight.hpp>
#include <Engine/OBJModel.hpp>
#include <Engine/SkyBox.hpp>
#include <Engine/Screen.hpp>
#include <SDL2/SDL_mixer.h>

extern GLboolean keyState[256];
extern Mix_Music *song;

extern engine::Window window;
extern engine::Renderer renderer;
extern engine::ShaderProgram *mainProgram;
extern engine::ShaderProgram *shadowProgram;
extern engine::ShaderProgram *skyboxProgram;

extern engine::Camera cam;
extern engine::DirLight sun;
extern engine::Model face;
extern engine::OBJModel helicopter;
extern engine::OBJModel grotor;
extern engine::OBJModel protor;
extern engine::SkyBox sky;

extern GLfloat sr, sg, sb, sa;

extern void helicopterMatrixIdentity(void);
extern void helicopterMatrixScale(GLfloat x, GLfloat y, GLfloat z);
extern void helicopterMatrixTranslate(GLfloat x, GLfloat y, GLfloat z);
extern void helicopterMatrixRotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
extern void helicopterRotateRotor(GLfloat angle);

extern void sequence(void);

#endif