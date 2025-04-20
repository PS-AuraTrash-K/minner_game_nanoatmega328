//
// Created by tarshpatar on 20.04.25.
//
#pragma once
#include "abstractMapElement.h"

template <class Type>
class SingleMapElement : public AbstractMapElement<Type> {
    public:
      SingleMapElement() : AbstractMapElement<Type>() {}
      void run();
};

template <class Type>
void SingleMapElement<Type>::run() {
    for (int x = 0; x < CAM_SIZE_X; x++)
    {
        for (int y = 0; y < CAM_SIZE_Y; y++)
        {
            this->checkMatrix(x, y);
        }
    }
}