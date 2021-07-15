#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"

#pragma region Model Data
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

#pragma region Camera Declare
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion
#pragma region Light Declare
LightPoint lightP0 = LightPoint(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(glm::radians(45.0f), 0, 0), glm::vec3(0.5f, 0.5f, 0.5f));
LightPoint lightP1 = LightPoint(glm::vec3(0.0f, 2.0f, 1.0f), glm::vec3(glm::radians(45.0f), 0, 0), glm::vec3(1.0f, 1.0f, 0));
LightPoint lightP2 = LightPoint(glm::vec3(3.0f, -1.0f, 2.0f), glm::vec3(glm::radians(45.0f), 0, 0));
LightPoint lightP3 = LightPoint(glm::vec3(4.0f, 1.0f, -21.0f), glm::vec3(glm::radians(45.0f), 0, 0));
LightSpot lightS = LightSpot(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(glm::radians(90.0f), 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
//LightSpot light = LightSpot(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(glm::radians(90.0f), 0, 0));
LightDirectional light = LightDirectional(glm::vec3(1.0f, 1.0f, 5.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), glm::radians(45.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
#pragma endregion
#pragma region Input Declare
//前一次的x坐标和y坐标
float lastX;
float lastY;
//首次进入
bool firstMouse = true;
//控制按键
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = -1.0f;
	}
	else
	{
		camera.speedZ = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedX = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedX = 1.0f;
	}
	else
	{
		camera.speedX = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.speedY = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.speedY = -1.0f;
	}
	else
	{
		camera.speedY = 0;
	}
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse == true)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	//上次的移动差值，移动的快值就大
	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;

	lastX = xPos;
	lastY = yPos;

	//更新摄像机的三个方向向量
	camera.ProcessMouseMovement(deltaX, deltaY);
}
#pragma endregion
unsigned int LoadImageToGpu(const char* filename, GLuint internalFormat, GLenum format, int textrueSlot)
{
	GLuint TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textrueSlot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load image fail1");
	}
	stbi_image_free(data);
	return TexBuffer;
}
int main()
{
#pragma region Open a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//设置核心模式
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 800, "test", NULL, NULL);
	if (window == NULL)
	{
		printf("failed");
		glfwTerminate();
		return -1;
	}
	//联系上下文
	glfwMakeContextCurrent(window);
	//关闭鼠标游标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//获得当前鼠标位置
	glfwSetCursorPosCallback(window, mouse_callback);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("failed");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 800);
	glEnable(GL_DEPTH_TEST);

#pragma endregion
#pragma region Init Shader Program
	Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
#pragma endregion
#pragma region Init Material
	Material *myMaterial = new Material(myShader,
		LoadImageToGpu("container2 .png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
		LoadImageToGpu("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f);
#pragma endregion
#pragma region Init and Load Models to VAO,VBO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//写入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(4);
#pragma endregion

#pragma region Init Load Textures
	//GLuint TexBufferA;
	//TexBufferA = LoadImageToGpu("wall.jpg", GL_RGB, GL_RGB, 0);
	//GLuint TexBufferB;
	//TexBufferB = LoadImageToGpu("awesomeface.png", GL_RGBA, GL_RGBA, 2);
#pragma endregion

#pragma region Prepare MVP matrices
	//定义变换矩阵,
	//组合时先缩放再旋转后位移（列主序）
	//写的时候先平移再旋转后缩放
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	//投影矩阵
	glm::mat4 projMat;
	//投影矩阵一般不变
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
#pragma endregion
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//清屏
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		viewMat = camera.GetViewMatrix();
		for (int i = 0; i < 10; i++)
		{
			//Set Model matrix
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);

			//Set View Projection Matrices here if you want


			//Set Material ->Shader Program
			myShader->use();

			//Set Material->Textures
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D, myMaterial->specular);

			//Set Material ->Uniform
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 2);
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);


			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.pos"), light.position.x, light.position.y, light.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.dirToLight"), light.direction.x, light.direction.y, light.direction.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.color"), light.color.x, light.color.y, light.color.z);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.pos"), lightP0.position.x, lightP0.position.y, lightP0.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.dirToLight"), lightP0.direction.x, lightP0.direction.y, lightP0.direction.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.color"), lightP0.color.x, lightP0.color.y, lightP0.color.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.quadratic"), lightP0.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.pos"), lightP1.position.x, lightP1.position.y, lightP1.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.dirToLight"), lightP1.direction.x, lightP1.direction.y, lightP1.direction.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.color"), lightP1.color.x, lightP1.color.y, lightP1.color.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.quadratic"), lightP1.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.pos"), lightP2.position.x, lightP2.position.y, lightP2.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.dirToLight"), lightP2.direction.x, lightP2.direction.y, lightP2.direction.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.color"), lightP2.color.x, lightP2.color.y, lightP2.color.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.constant"), lightP2.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.linear"), lightP2.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.quadratic"), lightP2.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.pos"), lightP3.position.x, lightP3.position.y, lightP3.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.dirToLight"), lightP3.direction.x, lightP3.direction.y, lightP3.direction.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.color"), lightP3.color.x, lightP3.color.y, lightP3.color.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.constant"), lightP3.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.linear"), lightP3.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.quadratic"), lightP3.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.pos"), lightS.position.x, lightS.position.y, lightS.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.color"), lightS.color.x, lightS.color.y, lightS.color.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.quadratic"), lightS.quadratic);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOutter"), lightS.cosPhyOutter);

			//glUniform1f(glGetUniformLocation(myShader->ID,"lightS.cosPhyInner"),light.cosPhyInner);
			//glUniform1f(glGetUniformLocation(myShader->ID,"lightS.cosPhyOutter"),light.cosPhyOutter);
			//glUniform1f(glGetUniformLocation(myShader->ID,"lightP.constant"),light.constant);
			//glUniform1f(glGetUniformLocation(myShader->ID,"lightP.linear"),light.linear);
			//glUniform1f(glGetUniformLocation(myShader->ID,"lightP.quadratic"),light.quadratic);


			myMaterial->shader->setUniform3f("material.ambient", myMaterial->ambient);
			myMaterial->shader->setUniformli("material.diffuse", Shader::DIFFUSE);
			myMaterial->shader->setUniformli("material.specular", Shader::SPECULAR);
			//myMaterial->shader->setUniform3f("material.specular",myMaterial->specular);
			myMaterial->shader->setUniform1f("material.shininess", myMaterial->shininess);


			//Set Model
			glBindVertexArray(VAO);
			//Drawcall
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//Clean Up prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();
		camera.UpdateCameraPos();
	}
	//Exit Program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}