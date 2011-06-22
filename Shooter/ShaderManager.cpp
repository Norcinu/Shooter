#include "ShaderManager.h"
#include <iostream>

ShaderManager::ShaderManager(void) :
	vertex_shader(nullptr),
	pixel_shader(nullptr),
	layout(nullptr),
	matrix_buffer(nullptr)
{
}


ShaderManager::~ShaderManager(void)
{
}

bool ShaderManager::InitialiseShader(const std::string& vs_filename, const std::string& ps_filename, 
		ID3D11Device *device, HWND wnd)
{
	HRESULT result;
	ID3D10Blob *error_message = 0;
	ID3D10Blob *vsh_buffer = 0;
	ID3D10Blob *psh_buffer = 0;
	D3D11_INPUT_ELEMENT_DESC polygon_layout[2];
	unsigned int num_elements;
	D3D11_BUFFER_DESC matrix_buffer_desc;

	result = D3DX11CompileFromFile(vs_filename.c_str(), NULL, NULL, "ColorVertexShader", "vs_5_0", 
		D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vsh_buffer, &error_message, NULL);

	if (FAILED(result))
	{
		if (error_message)
		{
			char* compileErrors;
			unsigned long bufferSize, i;
			//ofstream fout;


			// Get a pointer to the error message text buffer.
			compileErrors = (char*)(error_message->GetBufferPointer());

			// Get the length of the message.
			bufferSize = error_message->GetBufferSize();

			// Open a file to write the error message to.
			//fout.open("shader-error.txt");

			// Write out the error message.
			//for(i=0; i<bufferSize; i++)
			//{
			//	fout << compileErrors[i];
			//}

			//// Close the file.
			//fout.close();

			// Release the error message.
			error_message->Release();
			error_message = 0;

			// Pop a message up on the screen to notify the user to check the text file for compile errors.
			MessageBox(wnd, "Error compiling shader.  Check shader-error.txt for message.", vs_filename.c_str(), MB_OK);
		}
		else
		{
			MessageBox(wnd, vs_filename.c_str(), "Missing Shader File", MB_OK);
		}
		
	}
	return true;
}

void ShaderManager::Render(ID3D11DeviceContext* context, int c, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)
{
}