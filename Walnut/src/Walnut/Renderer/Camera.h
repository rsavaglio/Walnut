#pragma once

#include <glm/glm.hpp>

namespace Walnut {

	class OrthoCamera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) {m_Position = position;  CalculateViewMatrix();}

		const float GetRotation() const { return m_Rotation; }
		void SetRotation(const float rotation) { m_Rotation = rotation; CalculateViewMatrix();}

		const glm::mat4& GetProjMatrix() const { return m_Proj; }
		const glm::mat4& GetViewMatrix() const { return m_View; }
		const glm::mat4& GetVP() const { return m_VP; }

	private:
		void CalculateViewMatrix();

	private:
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_VP;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};

}