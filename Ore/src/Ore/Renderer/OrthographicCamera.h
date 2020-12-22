#pragma once
#include <glm/glm.hpp>

namespace Ore
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void setPosition(const glm::vec3& position) { p_Position = position; RecalculateViewMatrix(); }
		void setRotation(float rotation) { p_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::vec3& GetPosition() const { return p_Position; }
		float GetRotation() const { return p_Rotation; }
		
		const glm::mat4& GetProjectionMatrix() const { return p_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return p_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return p_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 p_ProjectionMatrix;
		glm::mat4 p_ViewMatrix;
		glm::mat4 p_ViewProjectionMatrix;

		glm::vec3 p_Position = { 0.0f, 0.0f, 0.0f };
		float p_Rotation = 0.0f;
	};
}