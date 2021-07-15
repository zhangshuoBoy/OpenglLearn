#include "Camera.h"

//������������Ŀ����������forward��������
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	//�������������
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
//��ŷ������forward��������
Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
glm::mat4 Camera::GetViewMatrix()
{
	//��������ꡢ����������������������ϵ�����
	return glm::lookAt(Position, Position + Forward, WorldUp);
}
//���������������������
void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch -= deltaY * SenseX;
	Yaw -= deltaX * SenseY;
	UpdateCameraVectors();
}
void Camera::UpdateCameraPos()
{
	Position += Forward * speedZ*0.1f + Up * speedY*0.1f + Right * speedX*0.1f;
	//Position += glm::vec3(-speedX*0.01f,0,-speedZ*0.01f);
}

