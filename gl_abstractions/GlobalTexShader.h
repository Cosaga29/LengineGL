#pragma once

#include "Shader.hpp"
#include "Texture.hpp"


#ifndef DEFAULT_FRAG_TEXT_SHADER
#define DEFAULT_FRAG_TEXT_SHADER "shaders/default/default_frag_texture.shader"
#endif

#ifndef DEFAULT_VERT_TEXT_SHADER
#define DEFAULT_VERT_TEXT_SHADER "shaders/default/default_vert_texture.shader"
#endif


class GlobalTexShader : public Shader
{
public:
	GlobalTexShader() :
		Shader(DEFAULT_FRAG_TEXT_SHADER, DEFAULT_VERT_TEXT_SHADER) {}
};

