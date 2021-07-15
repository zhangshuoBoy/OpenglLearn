#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	//摄像机坐标、目标坐标、世界向上的向量
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	glm::vec3 Position;
	//摄像机的方向
	glm::vec3 Forward;
	glm::vec3 Right;
	//摄像机的上方向
	glm::vec3 Up;
	//世界的上方向
	glm::vec3 WorldUp;
	//两个欧拉角
	float Pitch;
	float Yaw;
	float SenseX = 0.001f;
	float SenseY = 0.001f;
	//前后移动步伐
	float speedZ = 0;
	float speedX = 0;
	float speedY = 0;
	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float deltaX, float deltaY);
	void UpdateCameraPos();
private:
	void UpdateCameraVectors();

};

