#include "wnpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Walnut {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}