//
//  Renderer.h
//  Graphics
//
//  Created by Edwin Solis on 10/6/20.
//

#ifndef Renderer_h
#define Renderer_h

#include <vector>
#include "Mesh.h"
#include "Shader.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();
    
    void PushToQueue(const Mesh& mesh, const Shader& shader);
    void Draw() const;
    
private:
    std::vector<std::pair<Mesh, const Shader*>> _queue;
};

#endif /* Renderer_h */
