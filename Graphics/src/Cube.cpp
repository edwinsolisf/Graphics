//
//  Cube.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/6/20.
//

#include "Cube.h"

Cube::Cube(float length, stml::vec3f position, const std::vector<Texture>& texture)
:_length(length), _position(position), _textures(texture)
{
}
/*
stml::vector<float, 40 + 20> Cube::GenVertexBuffer() const
{
    stml::vector<float, 40 + 20> out;
    //VERTEX 1
    out[0] = _position.x + _length/2.0f;
    out[1] = _position.y + _length/2.0f;
    out[2] = _position.z + _length/2.0f; 
    out[3] = 1.0f;
    out[4] = 1.0f;
    
    //VERTEX 2
    out[5] = _position.x - _length/2.0f;
    out[6] = _position.y + _length/2.0f;
    out[7] = _position.z + _length/2.0f;
    out[8] = 0.0f;
    out[9] = 1.0f;
    //3
    out[10] = _position.x - _length/2.0f;
    out[11] = _position.y - _length/2.0f;
    out[12] = _position.z + _length/2.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    //4
    out[15] = _position.x + _length/2.0f;
    out[16] = _position.y - _length/2.0f;
    out[17] = _position.z + _length/2.0f;
    out[18] = 1.0f;
    out[19] = 0.0f;
    
    out[20] = _position.x + _length/2.0f;
    out[21] = _position.y + _length/2.0f;
    out[22] = _position.z - _length/2.0f;
    out[23] = 1.0f;
    out[24] = 0.0f;
    
    out[25] = _position.x - _length/2.0f;
    out[26] = _position.y + _length/2.0f;
    out[27] = _position.z - _length/2.0f;
    out[28] = 0.0f;
    out[29] = 0.0f;
    
    out[30] = _position.x - _length/2.0f;
    out[31] = _position.y -_length/2.0f;
    out[32] = _position.z - _length/2.0f;
    out[33] = 0.0f;
    out[34] = 1.0f;
    
    out[35] = _position.x + _length/2.0f;
    out[36] = _position.y - _length/2.0f;
    out[37] = _position.z - _length/2.0f;
    out[38] = 1.0f;
    out[39] = 1.0f;
    //5
    out[40] = _position.x + _length/2.0f;
    out[41] = _position.y + _length/2.0f;
    out[42] = _position.z - _length/2.0f;
    out[43] = 0.0f;
    out[44] = 1.0f;
    
    out[45] = _position.x - _length/2.0f;
    out[46] = _position.y + _length/2.0f;
    out[47] = _position.z - _length/2.0f;
    out[48] = 1.0f;
    out[49] = 1.0f;
    
    out[50] = _position.x - _length/2.0f;
    out[51] = _position.y -_length/2.0f;
    out[52] = _position.z - _length/2.0f;
    out[53] = 1.0f;
    out[54] = 0.0f;
    
    out[55] = _position.x + _length/2.0f;
    out[56] = _position.y - _length/2.0f;
    out[57] = _position.z - _length/2.0f;
    out[58] = 0.0f;
    out[59] = 0.0f;
    return out;
}

stml::vector<unsigned int, 36> Cube::GenIndexBuffer() const
{
    stml::vector<unsigned int, 36> out;
    
    //FRONT
    out[0] = 0;
    out[1] = 1;
    out[2] = 2;
    
    out[3] = 0;
    out[4] = 2;
    out[5] = 3;
    
    //LEFT
    out[6] = 1;
    out[7] = 2;
    out[8] = 6 + 4;
    
    out[9] = 1;
    out[10] = 5 + 4;
    out[11] = 6 + 4;
    
    //BACK
    out[12] = 4;
    out[13] = 5;
    out[14] = 6;
    
    out[15] = 4;
    out[16] = 6;
    out[17] = 7;
    
    //RIGHT
    out[18] = 0;
    out[19] = 4 + 4;
    out[20] = 7 + 4;
    
    out[21] = 0;
    out[22] = 3;
    out[23] = 7 + 4;
    
    //TOP
    out[24] = 0;
    out[25] = 1;
    out[26] = 5;
    
    out[27] = 0;
    out[28] = 4;
    out[29] = 5;
    
    //BOTTOM
    out[30] = 2;
    out[31] = 6;
    out[32] = 7;
    
    out[33] = 2;
    out[34] = 3;
    out[35] = 7;
    
    return out;
}
*/

stml::matrix<float, 8 * 3, 8> Cube::GenVertexData() const
{
    stml::matrix<float, 8 * 3, 8> out;
    //VERTEX 0 - 0
    out[(0 * 3) + 0][0] = _position.x + _length/2.0f; //posx
    out[(0 * 3) + 0][1] = _position.y + _length/2.0f; //posy
    out[(0 * 3) + 0][2] = _position.z + _length/2.0f; //poz
    out[(0 * 3) + 0][3] = 0.0f; //norm x
    out[(0 * 3) + 0][4] = 0.0f; //norm y
    out[(0 * 3) + 0][5] = 1.0f; //norm z
    out[(0 * 3) + 0][6] = 1.0f; //tex x
    out[(0 * 3) + 0][7] = 1.0f; //tex y
        //ver)tex 0 - 1
    out[(0 * 3) + 1][0] = _position.x + _length/2.0f;
    out[(0 * 3) + 1][1] = _position.y + _length/2.0f;
    out[(0 * 3) + 1][2] = _position.z + _length/2.0f;
    out[(0 * 3) + 1][3] = 1.0f;
    out[(0 * 3) + 1][4] = 0.0f;
    out[(0 * 3) + 1][5] = 0.0f;
    out[(0 * 3) + 1][6] = 0.0f;
    out[(0 * 3) + 1][7] = 1.0f;
        //ver)tex 0 - 2
    out[(0 * 3) + 2][0] = _position.x + _length/2.0f;
    out[(0 * 3) + 2][1] = _position.y + _length/2.0f;
    out[(0 * 3) + 2][2] = _position.z + _length/2.0f;
    out[(0 * 3) + 2][3] = 0.0f;
    out[(0 * 3) + 2][4] = 1.0f;
    out[(0 * 3) + 2][5] = 0.0f;
    out[(0 * 3) + 2][6] = 1.0f;
    out[(0 * 3) + 2][7] = 0.0f;
    
    //VERTEX 1
    out[(1 * 3) + 0][0] = _position.x - _length/2.0f;
    out[(1 * 3) + 0][1] = _position.y + _length/2.0f;
    out[(1 * 3) + 0][2] = _position.z + _length/2.0f;
    out[(1 * 3) + 0][3] = 0.0f;
    out[(1 * 3) + 0][4] = 0.0f;
    out[(1 * 3) + 0][5] = 1.0f;
    out[(1 * 3) + 0][6] = 0.0f;
    out[(1 * 3) + 0][7] = 1.0f;
    
    out[(1 * 3) + 1][0] = _position.x - _length/2.0f;
    out[(1 * 3) + 1][1] = _position.y + _length/2.0f;
    out[(1 * 3) + 1][2] = _position.z + _length/2.0f;
    out[(1 * 3) + 1][3] = -1.0f;
    out[(1 * 3) + 1][4] = 0.0f;
    out[(1 * 3) + 1][5] = 0.0f;
    out[(1 * 3) + 1][6] = 1.0f;
    out[(1 * 3) + 1][7] = 1.0f;
    
    out[(1 * 3) + 2][0] = _position.x - _length/2.0f;
    out[(1 * 3) + 2][1] = _position.y + _length/2.0f;
    out[(1 * 3) + 2][2] = _position.z + _length/2.0f;
    out[(1 * 3) + 2][3] = 0.0f;
    out[(1 * 3) + 2][4] = 1.0f;
    out[(1 * 3) + 2][5] = 0.0f;
    out[(1 * 3) + 2][6] = 0.0f;
    out[(1 * 3) + 2][7] = 0.0f;
    
    // VERTEX 2
    out[(2 * 3) + 0][0] = _position.x - _length/2.0f;
    out[(2 * 3) + 0][1] = _position.y - _length/2.0f;
    out[(2 * 3) + 0][2] = _position.z + _length/2.0f;
    out[(2 * 3) + 0][3] = 0.0f;
    out[(2 * 3) + 0][4] = 0.0f;
    out[(2 * 3) + 0][5] = 1.0f;
    out[(2 * 3) + 0][6] = 0.0f;
    out[(2 * 3) + 0][7] = 0.0f;
    
    out[(2 * 3) + 1][0] = _position.x - _length/2.0f;
    out[(2 * 3) + 1][1] = _position.y - _length/2.0f;
    out[(2 * 3) + 1][2] = _position.z + _length/2.0f;
    out[(2 * 3) + 1][3] = -1.0f;
    out[(2 * 3) + 1][4] = 0.0f;
    out[(2 * 3) + 1][5] = 0.0f;
    out[(2 * 3) + 1][6] = 1.0f;
    out[(2 * 3) + 1][7] = 0.0f;
    
    out[(2 * 3) + 2][0] = _position.x - _length/2.0f;
    out[(2 * 3) + 2][1] = _position.y - _length/2.0f;
    out[(2 * 3) + 2][2] = _position.z + _length/2.0f;
    out[(2 * 3) + 2][3] = 0.0f;
    out[(2 * 3) + 2][4] = -1.0f;
    out[(2 * 3) + 2][5] = 0.0f;
    out[(2 * 3) + 2][6] = 0.0f;
    out[(2 * 3) + 2][7] = 1.0f;
    
    // VERTEX 3
    out[(3 * 3) + 0][0] = _position.x + _length/2.0f;
    out[(3 * 3) + 0][1] = _position.y - _length/2.0f;
    out[(3 * 3) + 0][2] = _position.z + _length/2.0f;
    out[(3 * 3) + 0][3] = 0.0f;
    out[(3 * 3) + 0][4] = 0.0f;
    out[(3 * 3) + 0][5] = 1.0f;
    out[(3 * 3) + 0][6] = 1.0f;
    out[(3 * 3) + 0][7] = 0.0f;
    
    out[(3 * 3) + 1][0] = _position.x + _length/2.0f;
    out[(3 * 3) + 1][1] = _position.y - _length/2.0f;
    out[(3 * 3) + 1][2] = _position.z + _length/2.0f;
    out[(3 * 3) + 1][3] = 1.0f;
    out[(3 * 3) + 1][4] = 0.0f;
    out[(3 * 3) + 1][5] = 0.0f;
    out[(3 * 3) + 1][6] = 0.0f;
    out[(3 * 3) + 1][7] = 0.0f;
    
    out[(3 * 3) + 2][0] = _position.x + _length/2.0f;
    out[(3 * 3) + 2][1] = _position.y - _length/2.0f;
    out[(3 * 3) + 2][2] = _position.z + _length/2.0f;
    out[(3 * 3) + 2][3] = 0.0f;
    out[(3 * 3) + 2][4] = -1.0f;
    out[(3 * 3) + 2][5] = 0.0f;
    out[(3 * 3) + 2][6] = 1.0f;
    out[(3 * 3) + 2][7] = 1.0f;
    
    // VERTEX 4
    out[(4 * 3) + 0][0] = _position.x + _length/2.0f;
    out[(4 * 3) + 0][1] = _position.y + _length/2.0f;
    out[(4 * 3) + 0][2] = _position.z - _length/2.0f;
    out[(4 * 3) + 0][3] = 0.0f;
    out[(4 * 3) + 0][4] = 0.0f;
    out[(4 * 3) + 0][5] = -1.0f;
    out[(4 * 3) + 0][6] = 0.0f;
    out[(4 * 3) + 0][7] = 1.0f;
    
    out[(4 * 3) + 1][0] = _position.x + _length/2.0f;
    out[(4 * 3) + 1][1] = _position.y + _length/2.0f;
    out[(4 * 3) + 1][2] = _position.z - _length/2.0f;
    out[(4 * 3) + 1][3] = 1.0f;
    out[(4 * 3) + 1][4] = 0.0f;
    out[(4 * 3) + 1][5] = 0.0f;
    out[(4 * 3) + 1][6] = 1.0f;
    out[(4 * 3) + 1][7] = 1.0f;
    
    out[(4 * 3) + 2][0] = _position.x + _length/2.0f;
    out[(4 * 3) + 2][1] = _position.y + _length/2.0f;
    out[(4 * 3) + 2][2] = _position.z - _length/2.0f;
    out[(4 * 3) + 2][3] = 0.0f;
    out[(4 * 3) + 2][4] = 1.0f;
    out[(4 * 3) + 2][5] = 0.0f;
    out[(4 * 3) + 2][6] = 1.0f;
    out[(4 * 3) + 2][7] = 1.0f;
    
    //VERTEX 5
    out[(5 * 3) + 0][0] = _position.x - _length/2.0f;
    out[(5 * 3) + 0][1] = _position.y + _length/2.0f;
    out[(5 * 3) + 0][2] = _position.z - _length/2.0f;
    out[(5 * 3) + 0][3] = -1.0f;
    out[(5 * 3) + 0][4] = 0.0f;
    out[(5 * 3) + 0][5] = 0.0f;
    out[(5 * 3) + 0][6] = 0.0f;
    out[(5 * 3) + 0][7] = 1.0f;
    
    out[(5 * 3) + 1][0] = _position.x - _length/2.0f;
    out[(5 * 3) + 1][1] = _position.y + _length/2.0f;
    out[(5 * 3) + 1][2] = _position.z - _length/2.0f;
    out[(5 * 3) + 1][3] = 0.0f;
    out[(5 * 3) + 1][4] = 0.0f;
    out[(5 * 3) + 1][5] = -1.0f;
    out[(5 * 3) + 1][6] = 1.0f;
    out[(5 * 3) + 1][7] = 1.0f;
    
    out[(5 * 3) + 2][0] = _position.x - _length/2.0f;
    out[(5 * 3) + 2][1] = _position.y + _length/2.0f;
    out[(5 * 3) + 2][2] = _position.z - _length/2.0f;
    out[(5 * 3) + 2][3] = 0.0f;
    out[(5 * 3) + 2][4] = 1.0f;
    out[(5 * 3) + 2][5] = 0.0f;
    out[(5 * 3) + 2][6] = 0.0f;
    out[(5 * 3) + 2][7] = 1.0f;
    
    //VERTEX 6
    out[(6 * 3) + 0][0] = _position.x - _length/2.0f;
    out[(6 * 3) + 0][1] = _position.y - _length/2.0f;
    out[(6 * 3) + 0][2] = _position.z - _length/2.0f;
    out[(6 * 3) + 0][3] = -1.0f;
    out[(6 * 3) + 0][4] = 0.0f;
    out[(6 * 3) + 0][5] = 0.0f;
    out[(6 * 3) + 0][6] = 0.0f;
    out[(6 * 3) + 0][7] = 0.0f;
    
    out[(6 * 3) + 1][0] = _position.x - _length/2.0f;
    out[(6 * 3) + 1][1] = _position.y - _length/2.0f;
    out[(6 * 3) + 1][2] = _position.z - _length/2.0f;
    out[(6 * 3) + 1][3] = 0.0f;
    out[(6 * 3) + 1][4] = 0.0f;
    out[(6 * 3) + 1][5] = -1.0f;
    out[(6 * 3) + 1][6] = 1.0f;
    out[(6 * 3) + 1][7] = 0.0f;
    
    out[(6 * 3) + 2][0] = _position.x - _length/2.0f;
    out[(6 * 3) + 2][1] = _position.y - _length/2.0f;
    out[(6 * 3) + 2][2] = _position.z - _length/2.0f;
    out[(6 * 3) + 2][3] = 0.0f;
    out[(6 * 3) + 2][4] = -1.0f;
    out[(6 * 3) + 2][5] = 0.0f;
    out[(6 * 3) + 2][6] = 0.0f;
    out[(6 * 3) + 2][7] = 0.0f;
    
    // VERTEX 7
    out[(7 * 3) + 0][0] = _position.x + _length/2.0f;
    out[(7 * 3) + 0][1] = _position.y - _length/2.0f;
    out[(7 * 3) + 0][2] = _position.z - _length/2.0f;
    out[(7 * 3) + 0][3] = 0.0f;
    out[(7 * 3) + 0][4] = 0.0f;
    out[(7 * 3) + 0][5] = -1.0f;
    out[(7 * 3) + 0][6] = 0.0f;
    out[(7 * 3) + 0][7] = 0.0f;
    
    out[(7 * 3) + 1][0] = _position.x + _length/2.0f;
    out[(7 * 3) + 1][1] = _position.y - _length/2.0f;
    out[(7 * 3) + 1][2] = _position.z - _length/2.0f;
    out[(7 * 3) + 1][3] = 1.0f;
    out[(7 * 3) + 1][4] = 0.0f;
    out[(7 * 3) + 1][5] = 0.0f;
    out[(7 * 3) + 1][6] = 1.0f;
    out[(7 * 3) + 1][7] = 0.0f;
    
    out[(7 * 3) + 2][0] = _position.x + _length/2.0f;
    out[(7 * 3) + 2][1] = _position.y - _length/2.0f;
    out[(7 * 3) + 2][2] = _position.z - _length/2.0f;
    out[(7 * 3) + 2][3] = 0.0f;
    out[(7 * 3) + 2][4] = -1.0f;
    out[(7 * 3) + 2][5] = 0.0f;
    out[(7 * 3) + 2][6] = 1.0f;
    out[(7 * 3) + 2][7] = 0.0f;
    
    return out;
}

stml::vector<unsigned int, 36> Cube::GenIndexData() const
{
    stml::vector<unsigned int, 36> out;
    
    //FRONT
    out[0]  = (0 * 3) + 0;
    out[1]  = (1 * 3) + 0;
    out[2]  = (2 * 3) + 0;
    
    out[3]  = (0 * 3) + 0;
    out[4]  = (2 * 3) + 0;
    out[5]  = (3 * 3) + 0;
    
    //LEFT
    out[6]  = (1 * 3) + 1;
    out[7]  = (2 * 3) + 1;
    out[8]  = (6 * 3) + 0;
    
    out[9]  = (1 * 3) + 1;
    out[10] = (5 * 3) + 0;
    out[11] = (6 * 3) + 0;
    
    //BACK
    out[12] = (4 * 3) + 0;
    out[13] = (5 * 3) + 1;
    out[14] = (6 * 3) + 1;
    
    out[15] = (4 * 3) + 0;
    out[16] = (6 * 3) + 1;
    out[17] = (7 * 3) + 0;
    
    //RIGHT
    out[18] = (0 * 3) + 1;
    out[19] = (3 * 3) + 1;
    out[20] = (7 * 3) + 1;
    
    out[21] = (0 * 3) + 1;
    out[22] = (4 * 3) + 1;
    out[23] = (7 * 3) + 1;
    
    //UP
    out[24] = (0 * 3) + 2;
    out[25] = (1 * 3) + 2;
    out[26] = (5 * 3) + 2;
    
    out[27] = (0 * 3) + 2;
    out[28] = (4 * 3) + 2;
    out[29] = (5 * 3) + 2;
    
    //DOWN
    out[30] = (2 * 3) + 2;
    out[31] = (3 * 3) + 2;
    out[32] = (7 * 3) + 2;
    
    out[33] = (2 * 3) + 2;
    out[34] = (6 * 3) + 2;
    out[35] = (7 * 3) + 2;
    
    return out;
}

Mesh Cube::GenMesh() const
{
    std::vector<Vertex> vertices;
    std::vector<Index> indices;
    
    vertices.reserve(24);
    indices.reserve(36);
    
    stml::matrix<float, 24, 8> vertexData = GenVertexData();
    stml::vector<unsigned int, 36> indexData = GenIndexData();
    
    for(unsigned int i = 0; i < 24; ++i)
        vertices.emplace_back(stml::vec3f(&vertexData[i][0]), stml::vec3f(&vertexData[i][3]), stml::vec2f(&vertexData[i][6]));
    for(unsigned int i = 0; i < 36; ++i)
        indices.push_back(indexData[i]);
    return Mesh(vertices, indices, _textures);
}
