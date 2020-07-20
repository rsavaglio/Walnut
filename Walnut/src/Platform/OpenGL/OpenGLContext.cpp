#include "wnpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Walnut {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		WN_CORE_ASSERT(windowHandle, "Window Handle is null!")
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WN_CORE_ASSERT(status, "Failed to initialize Glad!");

		WN_CORE_INFO("OpenGL Info:");
		WN_CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
		WN_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
		WN_CORE_INFO("    Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}