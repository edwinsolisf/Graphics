//
//  Application.h
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#ifndef Application_h
#define Application_h
#include "Window.h"

class Application
{
public:
    Application();
    virtual ~Application();
    
    virtual void Setup();
    virtual void Process();
    virtual void Render();
    virtual void Close();
    
    inline bool IsRunning() const { return _isRunning; }
    
private:
    bool _isRunning;
    Window* _window;
};
#endif /* Application_h */
