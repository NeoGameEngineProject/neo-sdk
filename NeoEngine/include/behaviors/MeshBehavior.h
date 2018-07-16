#ifndef NEO_MESHBEHAVIOR_H
#define NEO_MESHBEHAVIOR_H

#include "Behavior.h"

#include <vector>
#include <Vector3.h>
#include <Vector2.h>
#include <Image.h>
#include <Array.h>

namespace Neo 
{

struct AABB
{
	Vector3 min, max;
};

struct MeshVertex
{
	Vector3 position, normal;
};

class Texture;
struct Material
{
	// TODO Blend mode
	float opacity = 1;
	float shininess = 32;
	float customValue;
	Vector3 diffuse = Vector3(1, 1, 1);
	Vector3 specular = Vector3(1, 1, 1);
	Vector3 emit;
	Vector3 customColor;
	Texture* textures[4] {nullptr, nullptr, nullptr, nullptr};
};

class SubMesh
{
public:
	SubMesh() {}
	SubMesh(SubMesh&& b):
		m_indices(std::move(b.m_indices)),
		m_meshVertices(std::move(b.m_meshVertices)),
		m_textureChannels(std::move(b.m_textureChannels)),
		m_material(b.m_material) {}
	
	SubMesh(const SubMesh& b):
		m_indices(b.m_indices),
		m_meshVertices(b.m_meshVertices),
		m_textureChannels(b.m_textureChannels),
		m_material(b.m_material) {}
	
	std::vector<MeshVertex>& getVertices() { return m_meshVertices; }
	std::vector<unsigned int>& getIndices() { return m_indices; }
	std::vector<Array<Vector2>>& getTextureChannels() { return m_textureChannels; }
	
	void set(size_t numVertices,
		Vector3* vertices,
		Vector3* normals,
		size_t numIndices,
		unsigned int* indices);
	
	const Material& getMaterial() const { return m_material; }
	void setMaterial(Material& material) { m_material = material; }
	
	AABB calculateBoundingBox();
	
private:
	std::vector<unsigned int> m_indices;
	std::vector<MeshVertex> m_meshVertices;
	std::vector<Array<Vector2>> m_textureChannels;
	
	Material m_material;
};

class MeshBehavior : public Neo::Behavior
{
	std::vector<SubMesh> m_submeshes;
	AABB m_boundingBox;
	
public:
	MeshBehavior() {}
	MeshBehavior(MeshBehavior&& b) { *this = std::move(b); }
		
	MeshBehavior(MeshBehavior& b):
		m_submeshes(b.m_submeshes) {}
	
	const char* getName() const override { return "Mesh"; }
	std::vector<SubMesh>& getSubMeshes() { return m_submeshes; }
	
	MeshBehavior& operator= (MeshBehavior&& b)
	{
		if(this != &b)
		{
			m_submeshes = std::move(b.m_submeshes);
		}
		
		return *this;
	}
	
	void updateBoundingBox();
	AABB getBoundingBox() const { return m_boundingBox; }
};

}

#endif // NEO_MESHBEHAVIOR_H
