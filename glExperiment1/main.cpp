#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "customShader.h"
#define PI 3.1416

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

float GetPointCos(float R, int angle) {
	return float(R * cos(angle * PI / 180));
}
float GetPointSin(float R, int angle) {
	return float(R * sin(angle * PI / 180));
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "创建窗口错误" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 初始化 GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "初始化 GLAD 失败" << std::endl;
		return -1;
	}

	customShader ourShader("D:/repo/glExperiment/glExperiment1/Shader/shader.vs", "D:/repo/glExperiment/glExperiment1/Shader/shader.fs");

	// 坐标
	// 颜色
	float R = 0.5f;
	float r = 0.2f;
	float verticles[] = {
		// 原点 ( 0 )
		0.0f, 0.0f, 0.0f,
		0.8f, 0.0f, 0.0f,
		// A 点 ( 1 )
		0.0f,    R, 1.0f,
		0.8f, 0.0f, 0.0f,
		// B 点 ( 2 )
		GetPointCos(R, 18),  GetPointSin(R, 18), 1.0f,
		0.8f, 0.0f, 0.0f,
		// C 点 ( 3 )
		GetPointCos(R, 54), -GetPointSin(R, 54), 1.0f,
		0.8f, 0.0f, 0.0f,
		// D 点 ( 4 )
	   -GetPointCos(R, 54), -GetPointSin(R, 54), 1.0f,
		0.8f, 0.0f, 0.0f,
		// E 点 ( 5 )
	   -GetPointCos(R, 18),  GetPointSin(R, 18), 1.0f,
		0.8f, 0.0f, 0.0f,
		// a 点 ( 6 )
		GetPointCos(r, 54),  GetPointSin(r, 54), 1.0f,
		0.8f, 0.0f, 0.0f,
		// b 点 ( 7 )
		GetPointCos(r, 18), -GetPointSin(r, 18), 1.0f,
		0.8f, 0.0f, 0.0f,
		// c 点 ( 8 )
		0.0f,   -r, 1.0f,
		0.8f, 0.0f, 0.0f,
		// d 点 ( 9 )
	   -GetPointCos(r, 18), -GetPointSin(r, 18), 1.0f,
		0.8f, 0.0f, 0.0f,
		// e 点 ( 10 )
		-GetPointCos(r, 54), GetPointSin(r, 54), 1.0f,
		0.8f, 0.0f, 0.0f,
	};

	unsigned int indices[] = {
		0, 1, 6,
		0, 6, 2,
		0, 2, 7,
		0, 7, 3,
		0, 3, 8,
		0, 8, 4,
		0, 4, 9,
		0, 9, 5,
		0, 5, 10,
		0, 10, 1
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}