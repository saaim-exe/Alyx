#include "Model.h"



void Model::Draw(Shader& shader)
{
	for (size_t i = 0; i < m_meshes.size(); ++i)
	{
		m_meshes[i].Draw(shader); 
	}
}

void Model::Load(const std::string& path)
{

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals); 

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl; 
		return; 
	}

	const size_t slash = path.find_last_of("/\\"); 
	directory = (slash == std::string::npos) ? "" : path.substr(0, slash); 

	processNode(scene->mRootNode, scene); 
} 

void Model::processNode(aiNode* node, const aiScene* scene) {
	

	// process all node meshes 
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
		m_meshes.push_back(processMesh(mesh, scene)); 
	}

	// process any children meshes 
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene); 
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// process vertices (position, normas, tex coords) 

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{

		glm::vec3 vector{ mesh->mVertices[i].x,mesh->mVertices[i].y, mesh->mVertices[i].z };

		glm::vec3 n_vector{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

		glm::vec2 t_vector{ 0.0f, 0.0f }; // default   

		if (mesh->mTextureCoords[0])
		{
			t_vector.x = mesh->mTextureCoords[0][i].x;
			t_vector.y = mesh->mTextureCoords[0][i].y;
		}

		Vertex vertex{
			.position = vector,
			.normal = n_vector,
			.uv = t_vector
		};

		vertices.push_back(vertex);
	}


	// process indices 

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace	face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.emplace_back(face.mIndices[j]);
		}
	}


	// process material 

	if (mesh->mMaterialIndex >= 0)
	{

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.begin(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.begin(), specularMaps.begin(), specularMaps.end());

	}

	return Mesh(vertices, indices, textures);
}



std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {


	std::vector<Texture> textures;

	for (size_t i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false; 

		for (size_t j = 0; j < m_textures_loaded.size(); j++)
		{
			if (std::strcmp(m_textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.emplace_back(m_textures_loaded[j]); 
				skip = true; 
				break; 
			}
		}

		if (!skip)
		{
			Texture texture{
			.id = loadTexture(str.C_Str()), // NOTE: load texture implentation may be wrong for parsing .obj files  ,
			.type = typeName,
			.path = str.C_Str(),
			};

			textures.emplace_back(texture);
			m_textures_loaded.emplace_back(texture); 
		}

		
	}
	return textures;
}




