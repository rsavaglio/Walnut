#include "wnpch.h"
#include "Application.h"

#include "Walnut/Log.h"
#include "Walnut/Input.h"


#include <Glad/glad.h>


namespace Walnut {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

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

	Application::Application()
	{
		WN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		///////////////// Graphics Stuff /////////////////

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		// Triangle Data
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};



		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"}, // This is an element
				{ShaderDataType::Float4, "a_Color"}
			};
			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
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
		
		// Index Buffer  (tells open the order to draw vertices
		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		// Shaders
		std::string vertexSrc = R"( 
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec3 v_Position;			
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"( 
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color.r = v_Color.r * v_Position.r + 0.5;
				color.g = v_Color.g * v_Position.g + 0.5;
				color.b = v_Color.b * v_Position.b + 0.5;
				color.a = 1;
			}
		)";

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{

		while (m_Running)
		{	
			////// Rendering /////

			// Clear screen
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			// Bind shader
			m_Shader->Bind();

			// Draw triangle
			//m_VertexArray->Bind();

			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}


			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();


		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}