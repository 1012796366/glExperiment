#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "customShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

float calcDist(float posX1, float posY1, float posX2, float posY2)
{
	return sqrt(pow(posX1 - posX2, 2) + pow(posY1 - posY2, 2));
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

	customShader fixStar("Shader/shader.vs", "Shader/shader.fs");
	customShader movStar("Shader/shader.vs", "Shader/shader.fs");

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
		/*
		* !!! DEPRECATED !!!
		* 3 个三角形的简单画法
		* 1, 3, 9,
		* 2, 4, 10,
		* 3, 5, 6,
		*/
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

	unsigned int VBO[2], VAO[2], EBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);

	// 绑定首个 VAO 然后导入数据
	glBindVertexArray(VAO[0]);
	// 导入的是顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);
	// 导入的是画什么顶点
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 属性指定，下同
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 绑定第二个 VAO 然后导入数据
	glBindVertexArray(VAO[1]);
	// 顶点
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);
	// 画什么顶点
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 解绑 VAO 之前，需要先解绑 VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 预先声明需要使用到的变量
	// 可以放进循环里，不放进去仅因为我个人觉得不好看
	// 如果不放进去，请记得每次循环时都要初始化变量
	glm::mat4 transFixStar;
	glm::mat4 transMovStar;
	unsigned int uniFixStar;
	unsigned int uniMovStar;

	// 会飞五角星的位置，因为是平面的运动所以不需要第三个变量去记录位置
	float posX = 0.3f;
	float posY = 0.3f;
	float dirX = 1.0f;
	float dirY = 1.0f;

	// 旋转方向
	// 2 - 顺时针
	// 1 - 逆时针
	float dirR = 1.0f;

	// 缩放大小
	// x y 轴的缩放比例均一致
	float scaleSize;

	while (!glfwWindowShouldClose(window))
	{
		scaleSize = 0.3 + 0.1 * sin(glfwGetTime());

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 开始画原地旋转
		fixStar.use();

		// 五角星原地旋转一小时.mp4 变换矩阵的设定
		// 位移旋转放缩的执行顺序从下到上，此处特化为先缩放后旋转
		// 矩阵相乘顺序和代码编写顺序从上到下
		transFixStar = glm::mat4(1.0f);
		transFixStar = glm::rotate(transFixStar, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		transFixStar = glm::scale(transFixStar, glm::vec3(scaleSize, scaleSize, 1.0f));	// 五角星太大了，缩放
		// uniform 变量修改
		uniFixStar = glGetUniformLocation(fixStar.ID, "transform");
		glUniformMatrix4fv(uniFixStar, 1, GL_FALSE, glm::value_ptr(transFixStar));
		// 画画
		glBindVertexArray(VAO[0]);
		// Deprecated
		// glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

		// 开始画移动五角星
		movStar.use();

		// 会到处飞的五角星.mp4 变换矩阵的设定
		// 位移旋转放缩的执行顺序从下到上，此处特化为先缩放后旋转，最后平移
		// 矩阵相乘顺序和代码编写顺序从上到下
		transMovStar = glm::mat4(1.0f);
		transMovStar = glm::translate(transMovStar, glm::vec3(posX, posY, 0.0f));
		transMovStar = glm::rotate(transMovStar, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, -dirR));
		transMovStar = glm::scale(transMovStar, glm::vec3(scaleSize, scaleSize, 1.0f));
		// uniform 变量修改
		uniMovStar = glGetUniformLocation(movStar.ID, "transform");
		glUniformMatrix4fv(uniMovStar, 1, GL_FALSE, glm::value_ptr(transMovStar));
		// 画画
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

		if (posX > (0.9f - scaleSize + 0.3f))
		{
			// 意味着已经达到了右边界
			dirX = -1.0f;
			posX += dirX * 0.0007f;
		}
		if (posX < (-0.9f + scaleSize - 0.3f))
		{
			// 意味着已经达到了左边界
			dirX = 1.0f;
			posX += dirX * 0.0007f;
		}
		if (posY > (0.9f - scaleSize + 0.3f))
		{
			// 上边界
			dirY = -1.0f;
			posY += dirY * 0.0009f;
		}
		if (posY < (-0.9f + scaleSize - 0.3f))
		{
			// 下边界
			dirY = 1.0f;
			posY += dirY * 0.0009f;
		}
		if (calcDist(0.0f, 0.0f, posX, posY) <= (0.2f + scaleSize - 0.3f))
		{
			dirX = -dirX;
			dirY = -dirY;
			posX += dirX * 0.0007f;
			posY += dirY * 0.0009f;
		}

		if (dirX > 0)
		{
			dirR = 1.0f;
		}
		if (dirX < 0)
		{
			dirR = -1.0f;
		}

		posX += dirX * 0.0007f;
		posY += dirY * 0.0009f;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	fixStar.unuse();
	glfwTerminate();
	return 0;
}