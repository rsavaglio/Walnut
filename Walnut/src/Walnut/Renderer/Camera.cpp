#include "wnpch.h"
#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Walnut {

	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
		:m_Proj(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_View(1.0f)
	{
		m_VP = m_Proj * m_View;
	}


	void OrthoCamera::CalculateViewMatrix()
	{
		// May need optimization
		glm::mat4 transform = 
			glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

		m_View = glm::inverse(transform);
		m_VP = m_Proj * m_View;
	}

}