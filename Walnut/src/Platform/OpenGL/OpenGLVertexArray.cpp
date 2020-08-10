#include "wnpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Walnut {

	// Temp
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:   return GL_FLOAT;
			case ShaderDataType::Float2:  return GL_FLOAT;
			case ShaderDataType::Float3:  return GL_FLOAT;
			case ShaderDataType::Float4:  return GL_FLOAT;
			case ShaderDataType::Mat3:    return GL_FLOAT;
			case ShaderDataType::Mat4:    return GL_FLOAT;
			case ShaderDataType::Int:     return GL_INT;
			case ShaderDataType::Int2:    return GL_INT;
			case ShaderDataType::Int3:    return GL_INT;
			case ShaderDataType::Int4:    return GL_INT;
			case ShaderDataType::Bool:    return GL_BOOL;
		}
		WN_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);

	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		WN_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,											// Index to be used in shader
				element.GetComponentCount(),					// How many components in this element (vec3 has 3 componenets)
				ShaderDataTypeToOpenGLBaseType(element.Type),	// The data type
				element.Normalized,								// Should GL normalize the data for you, defaults to false
				layout.GetStride(),								// Size of element in bytes (vec3 = 3 components * 4 bytes)
				(const void*)element.Offset						// Offset to get to this element in the layout (size in bytes of all previous elements in layout)
			);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}