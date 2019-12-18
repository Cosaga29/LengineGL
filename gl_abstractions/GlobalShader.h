#pragma once

#include "Shader.hpp"

#ifndef DEFAULT_FRAG_SHADER
#define DEFAULT_FRAG_SHADER "shaders/default/default_frag.shader"
#endif

#ifndef DEFAULT_VERT_SHADER
#define DEFAULT_VERT_SHADER "shaders/default/default_vert.shader"
#endif


class GlobalShader : public Shader
{
public:
	GlobalShader() :
		Shader(DEFAULT_FRAG_SHADER, DEFAULT_VERT_SHADER) {}
};