#include "DX.cpp"
#include "CJwin.cpp"



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE phInst, LPSTR cmdLine, int cmdShow)
{
		srand(time(NULL));

		char *className = "CJwin_001_wcClass";
		WNDCLASSEX wc = {};
		MSG msg = {};

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_VREDRAW | CS_HREDRAW;
		wc.hInstance = hInst;
		wc.lpfnWndProc = WndProc;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszClassName = className;
		
		if(!RegisterClassEx(&wc))
		{
				MessageBox(0, "Register Fail", "RegisterClass failed!", 0);
				win32_states.running = false;
		}

		RECT clientRect = {0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT};
		AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, 0);

		int clientWidth = clientRect.right - clientRect.left;
		int clientHeight = clientRect.bottom - clientRect.top;

		HWND hwnd = CreateWindowEx(0,
						className,
						"CJwin_001",
						WS_OVERLAPPEDWINDOW,
						0, 0,
						clientWidth, clientHeight,
						0, 0, hInst, 0);

		ShowWindow(hwnd, SW_SHOW); 


		// ***** DIRECT3D ***** //

		InitD3D(hwnd, SCREEN_WIDTH, SCREEN_HEIGHT); 


		// CREATE AND LOAD TEXTURE
		HRESULT hr;
		hr = CreateWICTextureFromFile(device.Get(), deviceContext.Get(), boxFile, vikingTex.GetAddressOf(), vikingsrv.GetAddressOf(), maxSize);


		D3D11_TEXTURE2D_DESC vikTexDesc;
		comPtr<ID3D11Texture2D> viktex2d;
		vikingTex.As(&viktex2d);
		viktex2d->GetDesc(&vikTexDesc);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		vikingsrv->GetDesc(&srvd);

		D3D11_SAMPLER_DESC mapSamplerDesc = {};
		mapSamplerDesc.Filter =  	D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		mapSamplerDesc.AddressU =	D3D11_TEXTURE_ADDRESS_WRAP;
		mapSamplerDesc.AddressV =	D3D11_TEXTURE_ADDRESS_WRAP;
		mapSamplerDesc.AddressW =	D3D11_TEXTURE_ADDRESS_WRAP; 
		mapSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		mapSamplerDesc.MaxLOD = 	D3D11_FLOAT32_MAX;

		device->CreateSamplerState(&mapSamplerDesc, mapSampler.GetAddressOf());

		HDC dc = GetDC(hwnd);

		float acc = 0.0001;

		float moveX = 0.0f;
		float moveY = 0.0f;
		float moveZ = 0.0f;


		float width =  1.0f;
		float height = 1.0f;
		float depth =  1.0f;

		XMMATRIX rect1_m = XMLoadFloat4x4(&rect1.pos);
		
		while(win32_states.running)
		{

				while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
				}
				
				if(win32_states.keyStates[VK_RIGHT])
				{
					width += 0.01f;
					moveX += 0.01f/2.0f;

				}
				if(win32_states.keyStates[VK_LEFT])
				{
					width -= 0.01f;
					moveX -= 0.01f/2.0f;
				}
				if(win32_states.keyStates[VK_UP])
				{
					height += 0.01f;
					moveY  += 0.01f/2.0f;
				}
				if(win32_states.keyStates[VK_DOWN])
				{
					height -= 0.01f;
					moveY  -= 0.01f/2.0f;
				}	

				if(win32_states.keyStates['O'])
				{
				}	
				if(win32_states.keyStates['I'])
				{
				}	

				if(win32_states.keyStates['W'])
				{
					moveY += 0.01f;
				}	
				if(win32_states.keyStates['S'])
				{
					moveY -= 0.01f;
				}	
				if(win32_states.keyStates['A'])
				{
					moveX -= 0.01f;
				}	

				if(win32_states.keyStates['D'])
				{
					moveX += 0.01f;
				}	

				if(win32_states.leftKeyPressed)
				{
					moveX = getCursorPosX_f(hwnd);  
					moveY = getCursorPosY_f(hwnd);
				}


				rect1_m = XMMatrixTranspose(
								XMMatrixScaling(width, height, depth) *
								XMMatrixTranslation(moveX, moveY, moveZ)
						      	   );
				

				rect1.col.r = 1.0f;

				XMStoreFloat4x4(&rect1.pos, rect1_m);  

				RenderFrame();

				DwmFlush();

		}
			 ReleaseDC(hwnd, dc);


		return msg.wParam;
}

