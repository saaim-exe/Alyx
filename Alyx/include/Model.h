#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <vector>
#include <string>

//#include <assimp/include/Importer.hpp>
//#include <assimp/include/scene.h>
//#include <assimp/include/postprocess.h>
//


struct Model {

	void Load(const std::string& path); 

	// U NEED TO FIX THESE (aiNode and aiMesh are not type names ?? -> library issue ) 


	//void processNode(aiNode *node, const aiScene* scene);
	//void processMesh(aiMesh )
	void Draw(Shader& shader); 
	


	std::vector<Mesh> meshes; 
	std::string directory;









};
