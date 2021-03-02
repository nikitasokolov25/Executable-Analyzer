#include "foxui.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#include <stdexcept>

//Vitoliy, it's for you
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <GLFW/glfw3.h>


#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

FoxUI::FoxUI(unsigned short winW, unsigned short winH): windowWidth(winW), windowHeight(winH)
{
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    throw std::runtime_error("[FoxUI] Could not initialize glfw");

  createWindow("Executable Analyzer");

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  
  ImGui::StyleColorsDark();
 
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL2_Init();
}

FoxUI::~FoxUI()
{
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
}

void FoxUI::runUI()
{
  newFrame();

  static bool showDemo = false;

  if (showDemo)
    ImGui::ShowDemoWindow();

  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
  if (ImGui::Begin("Exec", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
  {
    ImGui::Button("Analyze");
    ImGui::Checkbox("Show demo window", &showDemo);

    ImGui::End();
  }

  render();
}

bool FoxUI::isAlive()
{
  return !glfwWindowShouldClose(window);
}

void FoxUI::createWindow(std::string name)
{
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(windowWidth, windowHeight, name.c_str(), 0, 0);
  if (window == 0)
    throw std::runtime_error("[FoxUI] Could not create window");

  glfwMakeContextCurrent(window);

  //vsync
  glfwSwapInterval(1);
}

void FoxUI::newFrame()
{
  glfwPollEvents();

  ImGui_ImplOpenGL2_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void FoxUI::render()
{
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  ImGui::Render();
  int display_w, display_h;

  glfwGetFramebufferSize(window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

  glfwMakeContextCurrent(window);
  glfwSwapBuffers(window);
}
