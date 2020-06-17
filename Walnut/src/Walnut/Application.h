#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Walnut/Events/ApplicationEvent.h"

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

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To de defined in CLIENT
	Application* CreateApplication();
}