#pragma once
#include "Container.h"

/// @brief A UI Layer, which represents a Layer with UI contents to be rendered by UIRoot
class Layer
{
public:
    /// @brief Assigned by UIRoot, unique ID for the layer
    unsigned int Id;

    /// @brief Pointer to the Root container for this layer
    Container *RootContainer;

    Layer(unsigned int id);
    ~Layer();
};