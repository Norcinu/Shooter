#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <d3d11.h>

class Visualisation
{
public:
	Visualisation(void);
	~Visualisation(void);

	bool Initialise(HWND wnd, const int h, const int w);
	void BeginScene();
	void EndScene();

	ID3D11Device* GetDevice() const { return d3d_device; }

private:
	DXGI_SWAP_CHAIN_DESC swap_chain_desc;
	IDXGISwapChain* swap_chain;
	ID3D11Device* d3d_device;
	ID3D11DeviceContext* device_context;
	ID3D11RenderTargetView* render_target_view;
	ID3D11Texture2D* depth_Stencil_buffer;
	ID3D11DepthStencilState* depth_stencil_state;
	ID3D11DepthStencilView* depth_stencil_view;
	ID3D11RasterizerState* raster_state;

	int screen_width;
	int screen_height;
};

#endif
