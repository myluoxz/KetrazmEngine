#ifndef OBJECT
#define OBJECT

#include "GLHead.hpp"

namespace engine
{;
	class DLLAPI Object
	{
	protected:
		static GLint _memState;
	public:
		Object(void);
		virtual ~Object(void);
		void *operator new(size_t sz);
		void *operator new[](size_t sz);
		void operator delete(void *p);
		void operator delete[](void *p);
		static GLint getMemoryState(void);
		static void saveMemoryInfo(const GLchar *filename);
	};
}

#endif
