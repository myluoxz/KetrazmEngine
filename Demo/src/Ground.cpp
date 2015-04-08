#include "Ground.hpp"

Ground::Ground(Engine::ShaderProgram *objectProgram, Engine::ShaderProgram *depthMapProgram)
{
	_texture = new Engine::Texture2D;
	_material = new Engine::Material;
	_mesh = new Engine::Mesh;
	_model = new Engine::Model(objectProgram, depthMapProgram);

	_texture->loadFromFile("../resources/textures/ornaments.jpg");
	_material->setDiffuseTexture(_texture);
	_material->setAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	_material->setDiffuse(glm::vec3(0.9f, 0.9f, 0.9f));
	_material->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	_material->setOpacity(1.0f);
	_material->setShininess(20.0f);

	Engine::Vertex vertexArray[] =
	{
		glm::vec3(-500, 0, -500), glm::vec2(0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
		glm::vec3(-500, 0, 500), glm::vec2(0, 1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
		glm::vec3(500, 0, 500), glm::vec2(1, 1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
		glm::vec3(500, 0, -500), glm::vec2(1, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
	};
	GLuint index[] = { 2, 0, 1, 0, 2, 3 };

	_mesh->setMaterial(_material);
	_mesh->load(sizeof vertexArray / sizeof(Engine::Vertex), vertexArray, sizeof index / sizeof(GLuint), index);

	_model->addMesh(_mesh);
}

Ground::~Ground(void)
{
	delete _texture;
	delete _material;
	delete _mesh;
	delete _model;
}

Engine::Model *Ground::getModel(void) const
{
	return _model;
}
