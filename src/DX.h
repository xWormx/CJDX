#define comPtr Microsoft::WRL::ComPtr

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>
#include "..\WICTexture\pch.h"
#include "..\WICTexture\WICTextureLoader.h"
#include "..\WICTexture\DirectXHelpers.h"
#include "..\WICTexture\PlatformHelpers.h"
#include "..\WICTexture\WICTextureLoader.cpp"

comPtr<ID3D11Device> device;
comPtr<ID3D11DeviceContext> deviceContext;
comPtr<ID3D11RenderTargetView> renderTarget;
comPtr<ID3D11Texture2D> backBuffer;
comPtr<IDXGISwapChain> swapChain;

comPtr<ID3DBlob> vShaderCode;
comPtr<ID3DBlob> pShaderCode;
comPtr<ID3DBlob> vShaderErrorCode;
comPtr<ID3DBlob> pShaderErrorCode;

comPtr<ID3D11InputLayout> inpuLayout;
comPtr<ID3D11VertexShader> vertexShader;
comPtr<ID3D11PixelShader> pixelShader;

comPtr<ID3D11Resource> vikingTex;
comPtr<ID3D11ShaderResourceView> vikingsrv;
comPtr<ID3D11SamplerState> mapSampler;

D3D11_BUFFER_DESC VBdesc = {};
D3D11_SUBRESOURCE_DATA vbSubResData = {};
comPtr<ID3D11Buffer> VBuffer;

D3D11_BUFFER_DESC IBdesc = {};
D3D11_SUBRESOURCE_DATA ibSubResData = {};
comPtr<ID3D11Buffer> IBuffer;

D3D11_BUFFER_DESC CBdesc = {};
D3D11_SUBRESOURCE_DATA cbSubResData = {};
comPtr<ID3D11Buffer> CBuffer;

size_t maxSize = 0;
const wchar_t *vikingFile = L"..\\assets\\viking-test.png";
const wchar_t *boxFile = L"..\\assets\\box-test.png";

using namespace DirectX;

struct CJColor4f
{
	float r;
	float g;
	float b;
	float a;
};
struct Vertex 
{
	XMFLOAT3 pos;
	CJColor4f col;
};		


struct ConstBuff
{

	XMFLOAT4X4 pos;
	CJColor4f col;
};

ConstBuff constBuff;

struct CJRectangle
{
	XMFLOAT4X4 pos; 
	CJColor4f col;
};

CJRectangle rect1 = 
{
	XMFLOAT4X4 { 1.0f, 0.0f, 0.0f, 0.0f,
		     0.0f, 1.0f, 0.0f, 0.0f,
		     0.0f, 0.0f, 1.0f, 0.0f,
		     0.0f, 0.0f, 0.0f, 1.0f },
}; 

// VERTEX BUFFER SETUP
Vertex vertices[] = 
{
	{ XMFLOAT3(-0.5f, -0.5f, 1.0f),  	1.0f, 0.0f, 0.0f, 1.0f},
	{ XMFLOAT3(-0.5f,  0.5f, 1.0f),  	0.0f, 1.0f, 0.0f, 1.0f},
	{ XMFLOAT3( 0.5f,  0.5f, 1.0f),  	0.0f, 0.0f, 1.0f, 1.0f},
	{ XMFLOAT3( 0.5f, -0.5f, 1.0f),  	0.0f, 0.0f, 0.0f, 1.0f}
};


// INDEX BUFFER SETUP
unsigned int indices[] =
{
	0, 1, 2,
	2, 3, 0,
 };


void CreateVertexBuffer(ID3D11Device *device, Vertex *vertices, UINT sizeVertice);
void CreateIndexBuffer(ID3D11Device *device, unsigned int *indices, UINT sizeIndices);
void CreateConstantBuffer(ID3D11Device *device, int byteWidth, ConstBuff *srcConstBuff);


void InitD3D(HWND hwnd, int SCREEN_WIDTH, int CREEN_HEIGHT);
void CompileShader(wchar_t* fileName, char* shaderEntry, char* shaderVersion, ID3DBlob **shaderCode);
void DrawIndexedConstantBuffer(ConstBuff *constBuff, unsigned int indexCount);
void DrawIndexedConstantBuffer(CJRectangle *rect, unsigned int indexCount);
void RenderFrame();


