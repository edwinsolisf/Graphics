//
//  Application.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#include "Application.h"
#include "Window.h"

Application::Application()
{
    
}

void Application::Setup()
{
    const int width = 800;
    const int height = 600;
    const char* title = "OPENGL";
    
    _window = new Window(width, height, title);
    _isRunning = true;
}

void Application::Process()
{
    _isRunning = !_window->ShouldClose();
}

void Application::Render()
{
    _window->Render();
}

void Application::Close()
{
    _window->Close();
}

Application::~Application()
{
    delete _window;
}
