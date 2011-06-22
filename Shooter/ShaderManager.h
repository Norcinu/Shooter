#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>
#include <d3d11.h>
#include <D3DX10math.h> // port this to use the xna math.
#include <D3DX11async.h>

class ShaderManager
{
public:
	ShaderManager(void);
	~ShaderManager(void);

	bool Initialise(ID3D11Device* device, HWND wnd);
	void Render(ID3D11DeviceContext* context, int, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection);
	
private:
	struct MatrixBufferType_t
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	bool InitialiseShader(const std::string& vs_filename, const std::string& ps_filename, 
		ID3D11Device *device, HWND wnd);
	void RenderShader(ID3D11DeviceContext* context, int);

private:
	ID3D11VertexShader* vertex_shader;
	ID3D11PixelShader* pixel_shader;
	ID3D11InputLayout* layout;
	ID3D11Buffer* matrix_buffer;
};

#endif
