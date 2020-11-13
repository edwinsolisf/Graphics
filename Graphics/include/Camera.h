//
//  Camera.h
//  Graphics
//
//  Created by Edwin Solis on 10/6/20.
//

#ifndef Camera_h
#define Camera_h

#include "matrix.h"
#include "vector.h"
#include "matrix_transform.h"

class Camera
{
public:
    Camera();
    Camera(const stml::vec3f& position);
    
    void SetCamera(const stml::vec3f& position, const stml::vec3f& target);
    
    void MoveUp(float step);
    void MoveRight(float step);
    void MoveForward(float step);
    void RotatePitch(float angle);
    void RotateYaw(float angle);
    void RotateRoll(float angle);
    
    inline const stml::vec3f& GetCameraPosition() const { return _position; }
    inline const stml::vec3f& GetCameraTarget() const { return _target; }
    inline const stml::vec3f& GetCameraRotations() const { return _rotations; }
    inline const stml::vec3f& GetCameraDirection() const { return _direction; }
    inline const stml::vec3f& GetCameraRight() const { return _right; }
    inline const stml::vec3f& GetCameraUp() const { return _up; }
    inline const stml::mat4f& GetCameraView() const { return _view; }
    
private:
    stml::vec3f _position;
    stml::vec3f _target;
    stml::vec3f _rotations;
    
    stml::vec3f _direction;
    stml::vec3f _right;
    stml::vec3f _up; 
    
    stml::vec3f _worldX;
    stml::vec3f _worldY;
    stml::vec3f _worldZ;
    
    stml::mat4f _view;
};

#endif /* Camera_h */
