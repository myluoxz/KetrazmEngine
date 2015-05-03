#include "Skeleton.hpp"

Engine::Skeleton::Skeleton(void)
{
	name = "";
	parent = NULL;
}

Engine::Skeleton::Skeleton(const std::string &name)
{
	this->name = name;
}

Engine::Skeleton::~Skeleton(void)
{
	for (std::vector<Skeleton *>::iterator it = children.begin(); it != children.end(); it++)
		release_ptr(*it);
}

Engine::Skeleton *Engine::Skeleton::searchByName(const std::string &name)
{
	if (this->name == name)
		return this;

	for (std::vector<Skeleton *>::iterator it = children.begin(); it != children.end(); it++)
	{
		Skeleton *tmp_skeleton = (*it)->searchByName(name);
		if (tmp_skeleton != NULL) return tmp_skeleton;
	}

	return NULL;
}