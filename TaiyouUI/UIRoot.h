#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "Layer.h"
#include "Container.h"

/// @brief Controls input flow, manages rendering and activation/de-activation of the UI Layer Stack
class UIRoot
{
	std::vector<Layer *> m_Layers;

public:
	SDL_Point Size;

	UIRoot();

	/// @brief Adds the layer into the internal layer stack and returns the layer pointer
	/// @param container Container pointer
	/// @return
	Layer *CreateLayer(Container *container);

	/// @brief Deletes the layer from the internal layer stack
	/// @param index ID of the layer to remove
	void RemoveLayer(unsigned int id);

	void Update(double deltaTime);
	void Draw(SDL_Renderer *renderer, double deltaTime);
	void EventUpdate(SDL_Event event);
};
