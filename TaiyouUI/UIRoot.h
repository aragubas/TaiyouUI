#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "Layer.h"
#include "Container.h"
#include "UIRootContext.h"
#include "Turk/Turk.h"


namespace TaiyouUI
{
	/// @brief Holds an instance of Turk, Manages input flow, rendering and activation/de-activation of UI Layers
	class UIRoot
	{
		std::vector<Layer> m_Layers;

	public:
		SDL_Point Size;
		UIRootContext Context;
		Turk::Turk Turk;

		UIRoot(SDL_Renderer *renderer, SDL_Window *window);

		/// @brief Adds the layer into the internal layer stack and returns the layer pointer
		/// @param container Container pointer
		/// @return
		uint CreateLayer(Container *container);

		/// @brief Deletes the layer from the internal layer stack
		/// @param id ID of the layer to remove
		void RemoveLayer(unsigned int id);

		/// @brief Deletes every layer in the Layer stack
		void ClearLayers();

		void Update(double deltaTime);
		void Draw(SDL_Renderer *renderer, double deltaTime);
		void EventUpdate(SDL_Event &event);
	};
}
