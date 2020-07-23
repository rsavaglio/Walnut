#include "wnpch.h"

#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Walnut{
	
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);

		}

		WN_CORE_ASSERT(false, "Shader not created, unknown RendererAPI!");
		return nullptr;
	}



}