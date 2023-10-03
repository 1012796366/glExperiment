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

	// ��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "�������ڴ���" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ��ʼ�� GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "��ʼ�� GLAD ʧ��" << std::endl;
		return -1;
	}

	customShader fixStar("Shader/shader.vs", "Shader/shader.fs");
	customShader movStar("Shader/shader.vs", "Shader/shader.fs");

	// ����
	// ��ɫ
	float R = 0.5f;
	float r = 0.2f;
	float verticles[] = {
		// ԭ�� ( 0 )
		0.0f, 0.0f, 0.0f,
		0.8f, 0.0f, 0.0f,
		// A �� ( 1 )
		0.0f,    R, 1.0f,
		0.8f, 0.0f, 0.0f,
		// B �� ( 2 )
		GetPointCos(R, 18),  GetPointSin(R, 18), 1.0f,
		0.8f, 0.0f, 0.0f,
		// C �� ( 3 )
		GetPointCos(R, 54), -GetPointSin(R, 54), 1.0f,
		0.8f, 0.0f, 0.0f,
		// D �� ( 4 )
	   -GetPointCos(R, 54), -GetPointSin(R, 54), 1.0f,
		0.8f, 0.0f, 0.0f,
		// E �� ( 5 )
	   -GetPointCos(R, 18),  GetPointSin(R, 18), 1.0f,
		0.8f, 0.0f, 0.0f,
		// a �� ( 6 )
		GetPointCos(r, 54),  GetPointSin(r, 54), 1.0f,
		0.8f, 0.0f, 0.0f,
		// b �� ( 7 )
		GetPointCos(r, 18), -GetPointSin(r, 18), 1.0f,
		0.8f, 0.0f, 0.0f,
		// c �� ( 8 )
		0.0f,   -r, 1.0f,
		0.8f, 0.0f, 0.0f,
		// d �� ( 9 )
	   -GetPointCos(r, 18), -GetPointSin(r, 18), 1.0f,
		0.8f, 0.0f, 0.0f,
		// e �� ( 10 )
		-GetPointCos(r, 54), GetPointSin(r, 54), 1.0f,
		0.8f, 0.0f, 0.0f,
	};

	unsigned int indices[] = {
		/*
		* !!! DEPRECATED !!!
		* 3 �������εļ򵥻���
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

	// ���׸� VAO Ȼ��������
	glBindVertexArray(VAO[0]);
	// ������Ƕ�������
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);
	// ������ǻ�ʲô����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// ����ָ������ͬ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// �󶨵ڶ��� VAO Ȼ��������
	glBindVertexArray(VAO[1]);
	// ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);
	// ��ʲô����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ��� VAO ֮ǰ����Ҫ�Ƚ�� VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Ԥ��������Ҫʹ�õ��ı���
	// ���ԷŽ�ѭ������Ž�ȥ����Ϊ�Ҹ��˾��ò��ÿ�
	// ������Ž�ȥ����ǵ�ÿ��ѭ��ʱ��Ҫ��ʼ������
	glm::mat4 transFixStar;
	glm::mat4 transMovStar;
	unsigned int uniFixStar;
	unsigned int uniMovStar;

	// �������ǵ�λ�ã���Ϊ��ƽ����˶����Բ���Ҫ����������ȥ��¼λ��
	float posX = 0.3f;
	float posY = 0.3f;
	float dirX = 1.0f;
	float dirY = 1.0f;

	// ��ת����
	// 2 - ˳ʱ��
	// 1 - ��ʱ��
	float dirR = 1.0f;

	// ���Ŵ�С
	// x y ������ű�����һ��
	float scaleSize;

	while (!glfwWindowShouldClose(window))
	{
		scaleSize = 0.3 + 0.1 * sin(glfwGetTime());

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ��ʼ��ԭ����ת
		fixStar.use();

		// �����ԭ����תһСʱ.mp4 �任������趨
		// λ����ת������ִ��˳����µ��ϣ��˴��ػ�Ϊ�����ź���ת
		// �������˳��ʹ����д˳����ϵ���
		transFixStar = glm::mat4(1.0f);
		transFixStar = glm::rotate(transFixStar, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		transFixStar = glm::scale(transFixStar, glm::vec3(scaleSize, scaleSize, 1.0f));	// �����̫���ˣ�����
		// uniform �����޸�
		uniFixStar = glGetUniformLocation(fixStar.ID, "transform");
		glUniformMatrix4fv(uniFixStar, 1, GL_FALSE, glm::value_ptr(transFixStar));
		// ����
		glBindVertexArray(VAO[0]);
		// Deprecated
		// glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

		// ��ʼ���ƶ������
		movStar.use();

		// �ᵽ���ɵ������.mp4 �任������趨
		// λ����ת������ִ��˳����µ��ϣ��˴��ػ�Ϊ�����ź���ת�����ƽ��
		// �������˳��ʹ����д˳����ϵ���
		transMovStar = glm::mat4(1.0f);
		transMovStar = glm::translate(transMovStar, glm::vec3(posX, posY, 0.0f));
		transMovStar = glm::rotate(transMovStar, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, -dirR));
		transMovStar = glm::scale(transMovStar, glm::vec3(scaleSize, scaleSize, 1.0f));
		// uniform �����޸�
		uniMovStar = glGetUniformLocation(movStar.ID, "transform");
		glUniformMatrix4fv(uniMovStar, 1, GL_FALSE, glm::value_ptr(transMovStar));
		// ����
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

		if (posX > (0.9f - scaleSize + 0.3f))
		{
			// ��ζ���Ѿ��ﵽ���ұ߽�
			dirX = -1.0f;
			posX += dirX * 0.0007f;
		}
		if (posX < (-0.9f + scaleSize - 0.3f))
		{
			// ��ζ���Ѿ��ﵽ����߽�
			dirX = 1.0f;
			posX += dirX * 0.0007f;
		}
		if (posY > (0.9f - scaleSize + 0.3f))
		{
			// �ϱ߽�
			dirY = -1.0f;
			posY += dirY * 0.0009f;
		}
		if (posY < (-0.9f + scaleSize - 0.3f))
		{
			// �±߽�
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