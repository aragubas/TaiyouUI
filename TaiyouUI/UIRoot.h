#pragma once
#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include "Layer.h"
#include "Container.h"
#include "UIRootContext.h"
#include "Turk/Turk.h"


namespace TaiyouUI
{
	/// @brief The backbone of the entire GUI tree, manages every instance attached to it
	class UIRoot
	{
		std::vector<Layer> m_Layers;

	public:
		SDL_Point Size;
		UIRootContext Context;
		std::shared_ptr<TurkInstance> Turk;

		UIRoot(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Window> window);

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
