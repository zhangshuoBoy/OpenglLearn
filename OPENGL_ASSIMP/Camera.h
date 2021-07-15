#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	//��������ꡢĿ�����ꡢ�������ϵ�����
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	glm::vec3 Position;
	//������ķ���
	glm::vec3 Forward;
	glm::vec3 Right;
	//��������Ϸ���
	glm::vec3 Up;
	//������Ϸ���
	glm::vec3 WorldUp;
	//����ŷ����
	float Pitch;
	float Yaw;
	float SenseX = 0.001f;
	float SenseY = 0.001f;
	//ǰ���ƶ�����
	float speedZ = 0;
	float speedX = 0;
	float speedY = 0;
	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float deltaX, float deltaY);
	void UpdateCameraPos();
private:
	void UpdateCameraVectors();

};

