////////////////////////////////////////////////////////////////////////////////
// Filename: terrainclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>
using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: TerrainClass
////////////////////////////////////////////////////////////////////////////////
class TerrainClass
{
private:
	struct HeightMapType 
	{ 
		float x, y, z;
		float nx, ny, nz;
		float r, g, b;
	};

	struct VectorType 
	{ 
		float x, y, z;
	};

	struct ModelType 
	{ 
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
		float r, g, b;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT3 binormal;
		XMFLOAT4 color;
	};
	
public:
	TerrainClass();
	TerrainClass(const TerrainClass& other);
	~TerrainClass();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* heightMapFilename, char* colorMapFilename, float flattenAmount, char* colorTextureFilename,
		char* normalTextureFilename);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetColorTexture();
	ID3D11ShaderResourceView* GetNormalTexture();

private:
	bool LoadHeightMap(char* filename);
	bool LoadColorMap(char* filename);
	void ReduceHeightMap(float value);
	bool CalculateNormals();
	bool BuildModel();
	void CalculateModelVectors();
	void CalculateTangentBinormal(TempVertexType vertex1, TempVertexType vertex2, TempVertexType vertex3,
									VectorType& tangent, VectorType& binormal);
	
	bool InitializeBuffers(ID3D11Device* device);

	bool LoadTextures(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* colorTexturefilename, char* normalTextureFilename);

	void ReleaseHeightMap();
	void ReleaseModel();
	void ReleaseBuffers();
	void ReleaseTextures();

	void RenderBuffers(ID3D11DeviceContext* deviceContext);

private:
	int m_terrainWidth, m_terrainHeight, m_vertexCount, m_indexCount;
	HeightMapType* m_heightMap;
	ModelType* m_model;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	TextureClass *m_ColorTexture, *m_NormalTexture;
};

#endif