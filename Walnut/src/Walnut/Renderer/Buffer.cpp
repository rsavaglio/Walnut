#include "wnpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#if WN_PLATFORM_WINDOWS
//Example: Include direct3D
#endif

namespace Walnut {


	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		// Decide here which API we're using
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
			
			#if WN_PLATFORM_WINDOWS
			//Exapmle: Other case for direct3D
			#endif
		}

		WN_CORE_ASSERT(false, "VertexBuffer not created, unknown RendererAPI!");
		return nullptr;

	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}
		

		WN_CORE_ASSERT(false, "Index Buffer not created, unknown RendererAPI!");
		return nullptr;
	}

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}


		WN_CORE_ASSERT(false, "Vertex Array not created, unknown RendererAPI!");
		return nullptr;
	}

}