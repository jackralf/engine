#pragma once

#include "../defines.h"

#ifdef _WIN32
#include <stdlib.h>
#include <libs/OpenGL/GLEW/include/GL/glew.h>
#else
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <iostream>
#include <fstream>
#include "../EventLoop.h"
#include "../AssetManaging/Resource.h"
#endif

namespace star
{
	// Attribute index.
	enum
	{
		ATTRIB_VERTEX,
		ATTRIB_TEXTUREPOSITON,
		NUM_ATTRIBUTES
	};

	class Shader {
	public:
		Shader(){}
		Shader(tstring vsFile, tstring fsFile);
		~Shader();

		bool Init(tstring vsFile, tstring fsFile);

		void Bind();
		void Unbind();

		GLuint id();

	private:

		char* TextFileReading(tstring fileName);
		bool CompileShader(GLuint* shader, GLenum type, tstring file);

		GLuint mShaderID;;
		GLuint mVertexShader;
		GLuint mFragmentShader;

	};

}