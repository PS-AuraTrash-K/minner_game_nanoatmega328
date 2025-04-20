//
// Created by tarshpatar on 07.04.25.
//

#pragma once
#include "camera.h"
#include "variables.h"
#include <avr/pgmspace.h>
#include "GameBoy.h"

template <class Type>
class AbstractMapElement {
  private:
    const Type *_data;
    void (*_func)(GameBoy *gb, int x, int y){};
    Camera *_cam { };
    GameBoy *_gb { };
   public:
    AbstractMapElement() = default;
    AbstractMapElement& setCamera(Camera *_cam);
    AbstractMapElement& setGameBoy(GameBoy *_gb);
    AbstractMapElement& setData(const Type *data);
    AbstractMapElement& setFunction(void (*func)(GameBoy *gb, int x, int y));

    bool checkMatrix(int size, int x, int y, void (*func)(GameBoy* gb, int x, int y));
    bool checkMatrix(int x, int y);

    virtual void run() {}
};


template <class Type>
AbstractMapElement<Type>& AbstractMapElement<Type>::setCamera(Camera* _cam)
{
    this->_cam = _cam;
    return *this;
}

template <class Type>
AbstractMapElement<Type>& AbstractMapElement<Type>::setGameBoy(GameBoy* _gb)
{
    this->_gb = _gb;
    return *this;
}

template <class Type>
AbstractMapElement<Type>& AbstractMapElement<Type>::setData(const Type *data)
{
    this->_data = data;
    return *this;
}

template <class Type>
AbstractMapElement<Type>& AbstractMapElement<Type>::setFunction(void (*func)(GameBoy *gb, int x, int y))
{
    this->_func = func;
    return *this;
}

template <class Type>
bool AbstractMapElement<Type>::checkMatrix(int size, int x, int y, void (*func)(GameBoy *gb, int x, int y))
{
    if (pgm_read_dword(&_data[y + _cam->y]) >> ((size - 1) - (x + _cam->x)) & 1) {
        func(_gb, x, y);
        return true;
    }
    return false;
}

template <class Type>
bool AbstractMapElement<Type>::checkMatrix(int x,  int y)
{
     return this->checkMatrix(32, x, y, _func);
}