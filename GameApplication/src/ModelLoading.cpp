#include "ModelLoading.h"

void processMesh(const aiMesh *pMesh, vector<Vertex> &verts, vector<int> &indices)
{
	int texCoordIndex = 0;

	for (int f = 0; f < pMesh->mNumFaces; f++)
	{
		const aiFace * face = &pMesh->mFaces[f];
		for (int i = 0; i < face->mNumIndices; i++)
		{
			int index = face->mIndices[i];
			indices.push_back(index);
		}
	}

	for (int v = 0; v < pMesh->mNumVertices; v++)
	{
		Vertex ourV;

		aiVector3D position = pMesh->mVertices[v];

		ourV.position = vec3(position.x, position.y, position.z);

		if (pMesh->HasNormals()) {
			aiVector3D normal = pMesh->mNormals[v];
			ourV.normal = vec3(normal.x, normal.y, normal.z);
		}
		if (pMesh->HasTangentsAndBitangents())
		{
			aiVector3D binormal = pMesh->mBitangents[v];
			aiVector3D tangent = pMesh->mTangents[v];

			ourV.binormal = vec3(binormal.x, binormal.y, binormal.z);
			ourV.tangent = vec3(tangent.x, tangent.y, tangent.z);
		}
		for (int t = 0; t < pMesh->GetNumUVChannels(); t++)
		{
			if (pMesh->HasTextureCoords(t))
			{
				texCoordIndex = t;
			}
		}

		if (pMesh->HasTextureCoords(texCoordIndex))
		{
			aiVector3D texCoord = pMesh->mTextureCoords[texCoordIndex][v];
			ourV.texCoords0 = vec2(texCoord.x, texCoord.y);
		}


		verts.push_back(ourV);
	}
}

void processNode(GameObject *pParent,const aiScene * currentScene,aiNode * currentNode)
{
	GameObject *pObject = new GameObject();
	vector<int> indices;
	vector<Vertex> verts;
	for (int currentMeshID = 0; currentMeshID < currentNode->mNumMeshes; currentMeshID++)
	{
		int meshID = currentNode->mMeshes[currentMeshID];
		processMesh(currentScene->mMeshes[meshID], verts, indices);
		pObject->copyVertexData(&verts[0], verts.size(), &indices[0], indices.size());
	}
	for (int currentNodeID = 0; currentNodeID < currentNode->mNumChildren; currentNodeID++)
	{
		aiNode *pChildNode = currentNode->mChildren[currentNodeID];
		processNode(pObject, currentScene,pChildNode );
	}

	pParent->addChild(shared_ptr<GameObject>(pObject));
}

//http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
GameObject * loadModelFromFile(const string & filename)
{
	LOG(INFO,"Attempting to load model %s",filename.c_str());
	//Empty Game 
	GameObject *gameObject = new GameObject();
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	const aiScene* scene = aiImportFile(filename.c_str(), aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords | aiProcess_CalcTangentSpace);
	if (scene)
	{
		processNode(gameObject, scene, scene->mRootNode);
	}
	aiReleaseImport(scene);


	return gameObject;
}
