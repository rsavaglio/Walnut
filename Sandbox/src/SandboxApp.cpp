#include <Walnut.h>

class ExampleLayer : public Walnut::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//WN_INFO("ExampleLayer::Update");
	}

	void OnEvent(Walnut::Event& event) override
	{
		WN_TRACE("{0}", event);
	}
};



class Sandbox : public Walnut::Application
{
public: 
	Sandbox() 
	{
		WN_TRACE("Help");
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Walnut::Application* Walnut::CreateApplication()
{
	return new Sandbox();
}