#include "Camera.h"

//用摄像机坐标和目标点坐标计算forward方向向量
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	//摄像机方向向量
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
//用欧拉角求forward方向向量
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
	//摄像机坐标、摄像机方向向量、世界向上的向量
	return glm::lookAt(Position, Position + Forward, WorldUp);
}
//更新摄像机三个方向向量
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

