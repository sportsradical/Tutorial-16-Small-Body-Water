////////////////////////////////////////////////////////////////////////////////
// Filename: skyplaneclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYPLANECLASS_H_
#define _SKYPLANECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: SkyPlaneClass
////////////////////////////////////////////////////////////////////////////////
class SkyPlaneClass
{
private:
	struct SkyPlaneType
	{
		float x, y, z;
		float tu, tv;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	SkyPlaneClass();
	SkyPlaneClass(const SkyPlaneClass& other);
	~SkyPlaneClass();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, 
					char* cloudTextureFilename, char* perturbTextureFilename);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);
	void Frame();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetCloudTexture();
	ID3D11ShaderResourceView* GetPerturbTexture();
	
	float GetScale();
	float GetBrightness();
	float GetTranslation();

private:
	bool InitializeSkyPlane(int skyPlaneResolution, float skyPlaneWidth, float skyPlaneTop, float skyPlaneBottom, int textureRepeat);
	void ShutdownSkyPlane();

	bool InitializeBuffers(ID3D11Device* device, int skyPlaneResolution);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

	bool LoadTextures(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename1, char* textureFilename2);
	void ReleaseTextures();

private:
	SkyPlaneType* m_skyPlane;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	TextureClass *m_CloudTexture, *m_PerturbTexture;
	float m_scale, m_brightness, m_translation;
};

#endif