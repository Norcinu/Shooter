#ifndef TEXTURED_QUAD_H
#define TEXTURED_QUAD_H

#include <string>

class TexturedQuad
{
public:
	TexturedQuad(void);
	~TexturedQuad(void);

	void Load(const std::string& filename);
	void Render(const float dt);

private:
	int x;
	int y;
	int z;
};

#endif
