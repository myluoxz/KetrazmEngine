#include <Engine/Mesh.hpp>
#include <Engine/Texture2D.hpp>
#include <Engine/TextureCube.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/Material.hpp>

Engine::Mesh::Mesh(void)
	: _numElement(0), _material(NULL)
{
	_vertexBuffer = new Buffer;
	_indexBuffer = new Buffer;

	glGenVertexArrays(1, &_idVAO);

	memset(_tex, 0, sizeof _tex);
};

Engine::Mesh::~Mesh(void)
{
	delete _vertexBuffer;
	delete _indexBuffer;
	
	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::Mesh::setMaterial(Material *material)
{
	memset(_tex, 0, sizeof _tex);

	_material = material;

	if (_material->hasDiffuseTexture())
		_tex[0] = _material->getDiffuseTexture()->getId();

	if (_material->hasSpecularTexture())
		_tex[1] = _material->getSpecularTexture()->getId();

	if (_material->hasAmbientTexture())
		_tex[2] = _material->getAmbientTexture()->getId();

	if (_material->hasEmissiveTexture())
		_tex[3] = _material->getEmissiveTexture()->getId();

	if (_material->hasShininessTexture())
		_tex[4] = _material->getShininessTexture()->getId();

	if (_material->hasOpacityTexture())
		_tex[5] = _material->getOpacityTexture()->getId();

	if (_material->hasBumpMap())
		_tex[6] = _material->getBumpMap()->getId();

	if (_material->hasNormalMap())
		_tex[7] = _material->getNormalMap()->getId();

	if (_material->hasDisplacementMap())
		_tex[8] = _material->getDisplacementMap()->getId();

	if (_material->hasLightMap())
		_tex[9] = _material->getLightMap()->getId();
}

Engine::Material *Engine::Mesh::getMaterial(void) const
{
     return _material;
}

void Engine::Mesh::load(const GLsizei &numVertex, const Vertex *vertexArray,
	const GLsizei &numIndex, const GLuint *indexArray)
{
	_numElement = numIndex;

	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertexArray, numVertex * sizeof *vertexArray, GL_STATIC_DRAW);
	_indexBuffer->createStore(GL_ELEMENT_ARRAY_BUFFER, indexArray, numIndex * sizeof *indexArray, GL_STATIC_DRAW);

	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer->getId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(5 * sizeof(GLfloat)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(8 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void Engine::Mesh::display(void) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _tex[1]);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _tex[2]);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _tex[3]);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _tex[4]);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, _tex[5]);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, _tex[6]);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, _tex[7]);

	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, _tex[8]);

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, _tex[9]);

	glBindBufferBase(GL_UNIFORM_BUFFER, 2, _material->getMatBuffer());
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, _material->getStateBuffer());

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Engine::Mesh::display(TextureCube *cubeTexture) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _tex[1]);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _tex[2]);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _tex[3]);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _tex[4]);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, _tex[5]);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, _tex[6]);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, _tex[7]);

	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, _tex[8]);

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, _tex[9]);
	
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture->getId());

	glBindBufferBase(GL_UNIFORM_BUFFER, 2, _material->getMatBuffer());
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, _material->getStateBuffer());

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Engine::Mesh::displayShadow(void) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex[0]);

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

bool Engine::CompareMesh::operator()(const Mesh *first, const Mesh *second)
{
	if (first->_material == NULL)
		return false;
	if (first->_material->getOpacity() < second->_material->getOpacity())
		return true;
	return false;
}
