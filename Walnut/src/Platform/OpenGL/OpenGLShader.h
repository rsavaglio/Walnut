#pragma once

#include "Walnut/Renderer/Shader.h"
#include <string>
#include <glm/glm.hpp>

namespace Walnut {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

	private:
		uint32_t m_RendererID; // Number that identifies this object in OpenGL
	};
}