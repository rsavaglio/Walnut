#include <Walnut.h>

#include "imgui/imgui.h"

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello!");
		ImGui::End();
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
	}

	~Sandbox() {}
};

Walnut::Application* Walnut::CreateApplication()
{
	return new Sandbox();
}