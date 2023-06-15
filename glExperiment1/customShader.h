#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class customShader
{
public:
	// 程序 ID
	unsigned int ID;

	// 读取并构建着色器
	customShader(const char* vertexPath, const char* fragmentPath);
	// 使用 / 激活程序
	void use();
	// uniform 设置函数
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};