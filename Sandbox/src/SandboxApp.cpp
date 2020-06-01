#include <Walnut.h>


class Sandbox : public Walnut::Application
{
public: 
	Sandbox() {}

	~Sandbox() {}
};

Walnut::Application* Walnut::CreateApplication()
{
	return new Sandbox();
}