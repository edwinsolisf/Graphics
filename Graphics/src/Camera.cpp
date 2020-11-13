//
//  Camera.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/6/20.
//

#include <Camera.h>
#include "constants.h"
#include "math.h"

Camera::Camera()
:_position(0.0f), _target(0.0f, 0.0f, 1.0f), _rotations(0.0f), _direction(0.0f, 0.0f, 1.0f), _right(-1.0f, 0.0f, 0.0f), _up(0.0f, 1.0f, 0.0f), _worldX(stml::posX), _worldY(stml::posY), _worldZ(stml::posZ), _view(stml::identity_mat4f)
{
    _view = stml::lookAt(_position, _up, _right);
}

Camera::Camera(const stml::vec3f& position)
:_position(position), _target(position + stml::vec3f(0.0f, 0.0f, 1.0f)), _rotations(0.0f), _worldX(stml::posX), _worldY(stml::posY), _worldZ(stml::posZ)
{
    SetCamera(_position, _target);
}

void Camera::SetCamera(const stml::vec3f& position, const stml::vec3f& target)
{
    _position = position;
    _target = target;
    
    /*
    _direction = stml::normalize(_target - _position);
    
    if(_rotations.x < stml::radians(89.0f) && _rotations.x > stml::radians(-89.0f))
        _right = stml::crossproduct(_direction, _worldY).UnitVector();
    else
        _right = stml::crossproduct(_direction, _worldX).UnitVector();
    _up = stml::crossproduct(_right, _direction).UnitVector();
    */
    
    _view = stml::lookAt(_position, _up, _right, _direction);
}

void Camera::MoveUp(float step)
{
    SetCamera(_position + (_up * step), _target + (_up * step));
}

void Camera::MoveRight(float step)
{
    SetCamera(_position + (_right * step), _target + (_right * step));
}

void Camera::MoveForward(float step)
{
    SetCamera(_position + (_direction * step), _target + (_direction * step));
}
/*
void Camera::RotatePitch(float angle)
{
    if((_rotations.x + angle) > stml::radians(89.0f))
    {
        angle = stml::radians(89.0f) - _rotations.x;
        _rotations.x = stml::radians(89.0f);
    }
    else if((_rotations.x + angle) < stml::radians(-89.0f))
    {
        angle = stml::radians(-89.0f) - _rotations.x;
        _rotations.x = stml::radians(-89.0f);
    }
    else
        _rotations.x += angle;
    
    if((_rotations.x < stml::radians(89.0f)) && (_rotations.x > stml::radians(-89.0f)))
    {
        stml::vec4f target = stml::rotate(_right, angle).Multiply(stml::vec4f(_target.x, _target.y, _target.z, 1.0f));
        SetCamera(_position, target.ToVector<3>());
    }
}
*/
/*
void Camera::RotatePitch(float angle)
{
    stml::vec4f target = stml::rotate(_right, -_rotations.x).Multiply(stml::vec4f(_direction.x, _direction.y, _direction.z, 0.0f));
    stml::vec3f dir = _target - _position;
    if((_rotations.x + angle)>= stml::radians(89.0f))
        _rotations.x = stml::radians(89.0f);
    else if((_rotations.x + angle) <= stml::radians(-89.0f))
        _rotations.x = stml::radians(-89.0f);
    else
        _rotations.x += angle;
    target = stml::rotate(_right, _rotations.x).Multiply(target).UnitVector();
    SetCamera(_position, target.ToVector<3>() * dir.Magnitude() + _position);
}

*//*
void Camera::RotatePitch(float angle)
{
    stml::vec3f target = stml::rotation(_direction, _right, -_rotations.x);
    stml::vec3f dir = _target - _position;
    if((_rotations.x + angle) > stml::radians(89.0f))
        _rotations.x = stml::radians(89.0f);
    else if((_rotations.x + angle) < stml::radians(-89.0f))
        _rotations.x = stml::radians(-89.0f);
    else
        _rotations.x += angle;
    SetCamera(_position, (stml::rotation(target, _right, _rotations.x).UnitVector() * dir.Magnitude()) + _position);
}
*/
void Camera::RotatePitch(float angle)
{
    if(((stml::angle(_worldY, _direction) - angle) > stml::radians(1.0f)) && ((stml::angle(_worldY, _direction) - angle) < stml::radians(179.0f)))
    {
        //SetCamera(_position, (stml::rotation(_direction, _right, angle) * (_target - _position).Magnitude()) + _position);
        _target = (stml::rotation(_direction, _right, angle) * (_target - _position).Magnitude()) + _position;
         _direction = stml::normalize(_target - _position);
        _up = stml::normalize(stml::crossproduct(_right, _direction));
        _view = stml::lookAt(_position, _up, _right, _direction);
    }
}

void Camera::RotateYaw(float angle)
{
    //SetCamera(_position, (stml::rotation(_direction, _up, angle) * (_target - _position).Magnitude()) + _position);
    _target = (stml::rotation(_direction, _up, angle) * (_target - _position).Magnitude()) + _position;
    _direction = stml::normalize(_target - _position);
    _right = stml::normalize(stml::crossproduct(_direction, _worldY));
    _up = stml::normalize(stml::crossproduct(_right, _direction));
    _view = stml::lookAt(_position, _up, _right, _direction);
}

void Camera::RotateRoll(float angle)
{
    _worldY = stml::rotation(_worldY, _direction, angle);
    _right = stml::normalize(stml::crossproduct(_direction, _worldY));
    _up = stml::normalize(stml::crossproduct(_right, _direction));
    _view = stml::lookAt(_position, _up, _right, _direction);
    //SetCamera(_position, _target);
}

