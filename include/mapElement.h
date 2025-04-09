//
// Created by tarshpatar on 07.04.25.
//

#pragma once
#include "camera.h"
#include "mapElement.h"
#include "variables.h"
#include <avr/pgmspace.h>

template <class Type>
class MapElement {
  private:
    Type *_data;
    void (*_func)(int x, int y){};
    Camera *_cam { };
   public:
    MapElement() = default;
    MapElement<Type>& setCamera(Camera *_cam);
    MapElement<Type>& setData(const Type *data);
    MapElement<Type>& setFunction(void (*func)(int x, int y));

    void checkMatrix(int x, int y);

    void runMatrix();
};


template <class Type>
MapElement<Type>& MapElement<Type>::setCamera(Camera* _cam)
{
    this->_cam = _cam;
    return *this;
}

template <class Type>
MapElement<Type>& MapElement<Type>::setData(const Type *data)
{
    this->_data = data;
    return *this;
}

template <class Type>
MapElement<Type>& MapElement<Type>::setFunction(void (*func)(int x, int y))
{
    this->_func = func;
    return *this;
}

template <class Type>
void MapElement<Type>::checkMatrix(int x, int y)
{
    if (pgm_read_dword(&_data[y + _cam->y]) >> (31 - (x + _cam->x)) & 1) {
        _func(x, y);
    }
}

template <class Type>
void MapElement<Type>::runMatrix()
{


    for (int x = 0; x < CAM_SIZE_X; x++)
    {
        for (int y = 0; y < CAM_SIZE_Y; y++)
        {
            this->checkMatrix(x, y);
        }
    }




}