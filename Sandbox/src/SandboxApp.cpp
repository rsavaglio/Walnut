#include <Walnut.h>

class ExampleLayer : public Walnut::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		// Testing input polling
		if (Walnut::Input::IsKeyPressed(WN_KEY_TAB))
			WN_TRACE("Tab key is pressed!");
	}

	void OnEvent(Walnut::Event& event) override
	{
		// Testing keyboard input as chars
		if (event.GetEventType() == Walnut::EventType::KeyPressed)
		{
			Walnut::KeyPressedEvent& e = (Walnut::KeyPressedEvent&)event;
			WN_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};



class Sandbox : public Walnut::Application
{
public: 
	Sandbox() 
	{
		WN_INFO("Sandbox application created!");
		PushLayer(new ExampleLayer());
		PushOverlay(new Walnut::ImGuiLayer());
	}

	~Sandbox() {}
};

Walnut::Application* Walnut::CreateApplication()
{
	return new Sandbox();
}