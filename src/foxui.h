#pragma once
#include <string>

extern void glfw_error_callback(int error, const char* description);

struct GLFWwindow;

class FoxUI
{
public:
  FoxUI(unsigned short, unsigned short);
  ~FoxUI();

  void runUI();

  bool isAlive();
private:
  void createWindow(std::string name);
  void newFrame();
  void render();

  const unsigned short windowWidth, windowHeight;

  GLFWwindow* window;
};