#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Util.h"
#include "Texture.h"
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


using namespace TextureProcessing; 
using namespace Util; 


struct Model {

	void Load(const std::string& path); 

	// U NEED TO FIX THESE (aiNode and aiMesh are not type names ?? -> library issue ) 
	// UPDATE : ALL I HAD TO DO WAS MOVE THE HEADER FILES? AM I STUPID LMAOOO? 

	void processNode(aiNode *node, const aiScene* scene);
	Mesh processMesh(aiMesh *mesh, const aiScene* scene); 
	void Draw(Shader& shader); 

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
;
	std::vector<Texture> m_textures_loaded; 
	std::vector<Mesh> m_meshes; 
	std::string directory;

};
