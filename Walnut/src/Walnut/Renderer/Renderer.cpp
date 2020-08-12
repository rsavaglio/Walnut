#include "wnpch.h"
#include "Renderer.h"

namespace Walnut {

	void Renderer::BeginScene()
	{
		// TODO: Take in scene parameters
		// TODO: Ensures shaders take in the correct uniforms
		// TODO: Lighting and environment data
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}