#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Walnut/Events/ApplicationEvent.h"

#include "Walnut/ImGui/ImGuiLayer.h"

#include "Walnut/Renderer/Shader.h"

namespace Walnut {

	class WALNUT_API Application
	{
	public:
		Application();
		virtual ~Application(); // This class is sub-classes by applications

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() {return *s_Instance;}

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		// Temp graphics stuff
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

	private:
		static Application* s_Instance;
	};

	// To de defined in CLIENT
	Application* CreateApplication();
}