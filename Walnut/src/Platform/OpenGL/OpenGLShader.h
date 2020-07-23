#pragma once

#include "Walnut/Renderer/Shader.h"
#include <string>

namespace Walnut {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_RendererID; // Number that identifies this object in OpenGL
	};
}