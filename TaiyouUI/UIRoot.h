#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Layer.h"
#include "Container.h"

/// @brief Controls input flow, manages rendering and activation/de-activation of the UI Layer Stack
class UIRoot
{
	std::vector<Layer *> m_Layers;

public:
	UIRoot();

	/// @brief Adds the layer into the internal layer stack and return the Layer index
	/// @param layer Layer pointer (do no free this pointer, as it's managed by UIRoot)
	/// @return
	Layer *CreateLayer(Container *container);

	/// @brief Deletes the layer from the internal layer stack
	/// @param index ID of the layer to remove
	void RemoveLayer(unsigned int id);

	void Update(double deltaTime);
	void Draw(SDL_Renderer *renderer, double deltaTime);
	void EventUpdate(SDL_Event event);
};
