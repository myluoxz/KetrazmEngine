#ifndef MOVABLE_CAMERA
#define MOVABLE_CAMERA

#include "Camera.hpp"

namespace engine
{
	class DLLAPI MovableCamera : public Camera
	{
	protected:
		GLfloat _speed;
		GLfloat _atheta;
		GLfloat _aphi;
		glm::vec3 *_vforward;
		glm::vec3 *_vleft;
	public:
		MovableCamera(void);
		~MovableCamera(void);
		void setInitialAngle(const GLfloat &t, const GLfloat &p);
		void setSpeed(const GLfloat &v);
		glm::vec3 getForward(void) const;
		glm::vec3 getLeft(void) const;
		void mouseMove(const GLint &xrel, const GLint &yrel);
		virtual void keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r) = 0;
	};
}

#endif