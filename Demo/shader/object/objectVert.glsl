#version 440

layout(binding = 0) uniform MVPMatrixBuffer
{
	mat4 MVP;
};

layout(binding = 1) uniform normalMatrixBuffer
{
	mat4 normalMatrix;
};

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out VertexData
{
	vec2 texCoord;
	mat3 TBN;
} VertOut;

void main(void)
{
	gl_Position =  MVP * vec4(vertex, 1.0);

	vec3 N = mat3(normalMatrix) * normal;
	vec3 T = mat3(normalMatrix) * tangent;
	vec3 B = cross(N, T);

	VertOut.texCoord = texCoord;
	VertOut.TBN = mat3(T, B, N);
}
