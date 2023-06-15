#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class customShader
{
public:
	// ���� ID
	unsigned int ID;

	// ��ȡ��������ɫ��
	customShader(const char* vertexPath, const char* fragmentPath);
	// ʹ�� / �������
	void use();
	void unuse();
	// uniform ���ú���
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};