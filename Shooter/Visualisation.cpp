#include "Visualisation.h"

D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;

Visualisation::Visualisation(void) :
	d3d_device(NULL),
	swap_chain(NULL),
	device_context(NULL),
	render_target_view(NULL),
	depth_Stencil_buffer(NULL),
	depth_stencil_state(NULL),
	depth_stencil_view(NULL),
	raster_state(NULL)
{
}

Visualisation::~Visualisation(void)
{
	if (device_context)
		device_context->ClearState();
	if (render_target_view)
		render_target_view->Release();
	if (swap_chain)
		swap_chain->Release();
	if (device_context)
		device_context->Release();
	if (d3d_device)
		d3d_device->Release();
}

bool Visualisation::Initialise(HWND wnd, const int h, const int w)
{
	screen_height = h;
	screen_width = w;

	HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( wnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.BufferDesc.Width = screen_width;
	swap_chain_desc.BufferDesc.Height = screen_height;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = wnd;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.Windowed = TRUE;

	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        g_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &swap_chain_desc, &swap_chain, &d3d_device, &g_featureLevel, &device_context );
        if( SUCCEEDED( hr ) )
            break;
    }

    if( FAILED( hr ) )
        return false;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = NULL;
    hr = swap_chain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
    if( FAILED( hr ) )
        return false;

    hr = d3d_device->CreateRenderTargetView( pBackBuffer, NULL, &render_target_view );
    pBackBuffer->Release();
    if( FAILED( hr ) )
        return false;

    device_context->OMSetRenderTargets( 1, &render_target_view, NULL );

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)screen_width;
    vp.Height = (FLOAT)screen_height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    device_context->RSSetViewports( 1, &vp );
	
	return true;
}

void Visualisation::BeginScene()
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
    device_context->ClearRenderTargetView( render_target_view, ClearColor );
}

void Visualisation::EndScene()
{
	swap_chain->Present(0, 0);
}
