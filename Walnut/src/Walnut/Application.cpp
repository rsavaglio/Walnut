#include "wnpch.h"
#include "Application.h"

#include "Walnut/Log.h"
#include "Walnut/Input.h"

namespace Walnut {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_Camera(-1.0f, 1.0f, -1.0f, 1.0f)
	{
		WN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		///////////////// Graphics Stuff /////////////////

		//// Triangle ////
		m_VertexArray.reset(VertexArray::Create());

		// Triangle Data
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		// Vertex Buffer
		std::shared_ptr<VertexBuffer> triangleVB;
		triangleVB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"}, // This is an element
			{ShaderDataType::Float4, "a_Color"}
		};
		
		triangleVB->SetLayout(layout); // You must set the layout before adding to VA
		m_VertexArray->AddVertexBuffer(triangleVB);
		
		// Index Buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> triangleIB;
		triangleIB.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIB);

		//// Square /////
		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
		 -0.75f, -0.75f, 0.0f,
		  0.75f, -0.75f, 0.0f,
		  0.75f,  0.75f, 0.0f,
		 -0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({ 
			{ ShaderDataType::Float3, "a_Position" } 
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Shaders
		std::string vertexSrc = R"( 
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_VP;
			
			out vec3 v_Position;			
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_VP * vec4(a_Position, 1.0);
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

		// Shaders
		std::string blueVertShaderSrc = R"( 
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_VP;

			void main()
			{
				gl_Position = u_VP * vec4(a_Position, 1.0);
			}
		)";

		std::string blueFragShaderSrc = R"( 
			#version 330 core
			
			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(Shader::Create(blueVertShaderSrc, blueFragShaderSrc));
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
			//////////// Rendering ///////////

			RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_BlueShader->Bind();
			m_BlueShader->UploadUniformMat4("m_VP", m_Camera.GetVP());
			Renderer::Submit(m_SquareVA);

			m_Shader->Bind();
			m_Shader->UploadUniformMat4("m_VP", m_Camera.GetVP());
			Renderer::Submit(m_VertexArray);
			Renderer::EndScene();

			//////////////////////////////////

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