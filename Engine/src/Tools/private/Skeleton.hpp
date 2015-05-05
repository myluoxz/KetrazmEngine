#ifndef SKELETON_HEADER
#define SKELETON_HEADER

#include <Engine/Object.hpp>

namespace Engine
{
	struct Skeleton : public Object
	{
		std::string name;
		glm::mat4 matrix;

		Skeleton *parent;
		std::vector<Skeleton *> children;

		Skeleton(void);
		Skeleton(const std::string &name);
		~Skeleton(void);

		Skeleton *searchByName(const std::string &name);
	};

	struct Bone : public Object
	{
		glm::mat4 offsetMatrix;
		Skeleton *ptr_in_skeleton;
	};
}

#endif