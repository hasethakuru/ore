#include "opch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Ore
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: p_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), p_ViewMatrix(1.0f)
	{
		p_ViewProjectionMatrix = p_ProjectionMatrix * p_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(p_Rotation), glm::vec3(0, 0, 1));

		p_ViewMatrix = glm::inverse(transform);
		p_ViewProjectionMatrix = p_ProjectionMatrix * p_ViewMatrix;

	}
}