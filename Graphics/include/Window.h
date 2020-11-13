//
//  Window.h
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#ifndef Window_h
#define Window_h

#include "Opengl.h"
#include "vector.h"
class Window
{
public:
    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();
    
    void Run();
    void Render();
    void BackgroundColor(const stml::vec4f& color) const;
    void Close() const;
    void Frame();
    
    bool NewFrame() const { return _new; }
    bool ShouldClose() const { return glfwWindowShouldClose(_glfwWindow); }
private:
    unsigned int _width, _height;
    const char* _title;
    bool _new;
    GLFWwindow* _glfwWindow;
};

#endif /* Window_h */
