#include <Engine/FreeCam.hpp>

engine::FreeCam::FreeCam(void)
{
}

engine::FreeCam::FreeCam(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	_pcamera->x = x;
	_pcamera->y = y;
	_pcamera->z = z;
}

engine::FreeCam::~FreeCam(void)
{
}

void engine::FreeCam::keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r)
{
	if(f)
		*_pcamera += *_vforward * _speed;
	if(b)
		*_pcamera -= *_vforward * _speed;
	if(l)
		*_pcamera += *_vleft * _speed;
	if(r)
		*_pcamera -= *_vleft * _speed;
  
	*_ptarget = *_pcamera + *_vforward;
}
