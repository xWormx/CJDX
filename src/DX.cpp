#include "DX.h"

void CreateVertexBuffer(Vertex *vertices, UINT sizeVertices)
{
	VBdesc.Usage = D3D11_USAGE_DYNAMIC;
	VBdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VBdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	VBdesc.MiscFlags = 0;
	VBdesc.ByteWidth = sizeVertices;
	VBdesc.StructureByteStride = sizeof(Vertex);

	vbSubResData.pSysMem = vertices;

	HRESULT hra = device->CreateBuffer(&VBdesc, &vbSubResData, &VBuffer);
}

void CreateIndexBuffer(unsigned int *indices, UINT sizeIndices)
{
	IBdesc.Usage = D3D11_USAGE_DYNAMIC;
	IBdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	IBdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	IBdesc.MiscFlags = 0;
	IBdesc.ByteWidth = sizeIndices;
	IBdesc.StructureByteStride = sizeof(int);

	ibSubResData.pSysMem = indices;

	HRESULT hra = device->CreateBuffer(&IBdesc, &ibSubResData, &IBuffer);
}

void CreateConstantBuffer(int byteWidth, ConstBuff *srcConstBuff)
{
	CBdesc.Usage = D3D11_USAGE_DEFAULT;
	CBdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CBdesc.CPUAccessFlags = 0;
	CBdesc.MiscFlags = 0;
	CBdesc.ByteWidth = byteWidth;
	CBdesc.StructureByteStride = 0;

	cbSubResData.pSysMem =  srcConstBuff;

	HRESULT hr = device->CreateBuffer(&CBdesc, &cbSubResData, &CBuffer);
}


void CompileShader(wchar_t* fileName, char* shaderEntry, char* shaderVersion, ID3DBlob **shaderCode)
{
	ID3DBlob *errorMsg;
	D3DCompileFromFile(fileName, 0, 0, shaderEntry, shaderVersion, 0, 0, shaderCode, &errorMsg);

	if(errorMsg)
	{
		char *error = (char*)errorMsg->GetBufferPointer();
		MessageBox(0, error, "Shader Compilation Fail", MB_OK);
	}
}

void InitD3D(HWND hwnd, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	// SETUP SWAPCHAIN DEVICE AND RENDERTARGET
	DXGI_SWAP_CHAIN_DESC sdDesc = {};
	sdDesc.BufferDesc.Width = SCREEN_WIDTH; 
	sdDesc.BufferDesc.Height = SCREEN_HEIGHT;
	sdDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sdDesc.BufferDesc.RefreshRate.Numerator = 60;
	sdDesc.BufferDesc.RefreshRate.Denominator = 1;
	sdDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sdDesc.BufferCount = 1;
	sdDesc.SampleDesc.Count = 1;
	sdDesc.SampleDesc.Quality = 0;
	sdDesc.OutputWindow = hwnd;
	sdDesc.Windowed = TRUE;


	HRESULT hr = {};
	hr = D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0,
						D3D11_SDK_VERSION, &sdDesc, &swapChain,
						&device, 0, &deviceContext);
	
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)backBuffer.GetAddressOf());
	device->CreateRenderTargetView(backBuffer.Get(), 0, renderTarget.GetAddressOf());
	deviceContext->OMSetRenderTargets(1, renderTarget.GetAddressOf(), 0);

	// CREATE VIEWPORT
	D3D11_VIEWPORT pViewPort = {};

	pViewPort.TopLeftX = 0;
	pViewPort.TopLeftY = 0;
	pViewPort.Width = SCREEN_WIDTH;
	pViewPort.Height = SCREEN_HEIGHT;

	deviceContext->RSSetViewports(1, &pViewPort);

	// COMPILE SHADERS
	CompileShader(L"shader.fx", "VS_Main", "vs_5_0", vShaderCode.GetAddressOf());
	CompileShader(L"shader.fx", "PS_Main", "ps_5_0", pShaderCode.GetAddressOf());

	D3D11_INPUT_ELEMENT_DESC ieDesc[] = 
	{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// CREATE SHADERS AND INPUT LAYOUT
	hr = device->CreateVertexShader(vShaderCode->GetBufferPointer(), vShaderCode->GetBufferSize(), 0, vertexShader.GetAddressOf());
	hr = device->CreatePixelShader(pShaderCode->GetBufferPointer(), pShaderCode->GetBufferSize(), 0, pixelShader.GetAddressOf());
	hr = device->CreateInputLayout(ieDesc, ARRAYSIZE(ieDesc), vShaderCode->GetBufferPointer(), vShaderCode->GetBufferSize(), inpuLayout.GetAddressOf());


	// CREATE VERTEX, INDEX, CONSTANT BUFFERS
	CreateVertexBuffer(vertices, sizeof(vertices));
	CreateIndexBuffer(indices, sizeof(indices));
	CreateConstantBuffer(80, &constBuff);

	const unsigned int stride = sizeof(Vertex);
	const unsigned int offset = 0u;

	// BIND THE BUFFERS
	deviceContext->IASetVertexBuffers(0, 1, VBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetIndexBuffer(IBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	deviceContext->VSSetConstantBuffers(0, 1, CBuffer.GetAddressOf());

}

void DrawIndexedConstantBuffer(ConstBuff *cbuffSrc, unsigned int indexCount)
{
	// BIND/UPDATE CONST BUFFER, SET SHADERRESOURCE AND SAMPLER 
	deviceContext->UpdateSubresource(CBuffer.Get(), 0, 0, cbuffSrc, 0, 0);
	deviceContext->PSSetShaderResources(0, 1, vikingsrv.GetAddressOf());
	deviceContext->PSSetSamplers(0, 1, mapSampler.GetAddressOf());
	deviceContext->DrawIndexed(indexCount, 0, 0);

}

void DrawIndexedRect(CJRectangle *rect, unsigned int indexCount)
{
	// BIND/UPDATE CONST BUFFER, SET SHADERRESOURCE AND SAMPLER 
	deviceContext->UpdateSubresource(CBuffer.Get(), 0, 0, rect, 0, 0);
	deviceContext->PSSetShaderResources(0, 1, vikingsrv.GetAddressOf());
	deviceContext->PSSetSamplers(0, 1, mapSampler.GetAddressOf());
	deviceContext->DrawIndexed(indexCount, 0, 0);

}
void RenderFrame()
{
	float Color4[4] = { 0.0f, 0.0f, 0.3f, 1.0f };
	deviceContext->ClearRenderTargetView(renderTarget.Get(), Color4);

	// BIND INPUTLAYOUT, SHADERS, TOPOLOGY
	deviceContext->IASetInputLayout(inpuLayout.Get());
	deviceContext->PSSetShader(pixelShader.Get(), 0, 0);
	deviceContext->VSSetShader(vertexShader.Get(), 0, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DrawIndexedRect(&rect1, 6);

	swapChain->Present(0, 0);
}
