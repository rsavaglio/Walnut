#include "wnpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Walnut {

	VertexArray* VertexArray::Create()
	{
		// Decide here which API we're using
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();

		}

		WN_CORE_ASSERT(false, "VertexArray not created, unknown RendererAPI!");
		return nullptr;
	}
}