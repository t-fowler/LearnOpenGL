#pragma once
#include <exception>
#include <iostream>
#include <string>

#include <GLFW/glfw3.h>

class ConstructorException : public std::exception
{
private:
public:
	virtual const char* what() const throw();
};

class Display
{
private:
	GLFWwindow* window;
public:
	Display(int width, int height, std::string title);
	~Display();

	int shouldClose();
	void createContext(GLFWframebuffersizefun framebuffer_size_callback);

	inline GLFWwindow* getWindow() const { return window; };
};

