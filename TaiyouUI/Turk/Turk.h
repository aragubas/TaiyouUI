#pragma once
#include <unordered_map>
#include <SDL2/SDL_ttf.h>
#include "FontDescriptor.h"
#include "FontDescriptorHasher.h"


namespace TaiyouUI::Turk
{
	/// <summary>
	/// TaiyouUI Resource Keeper
	/// </summary>
	class Turk
	{
	public:
		Turk(SDL_Renderer* renderer, SDL_Window* window);
		~Turk();

		/// <summary>
		/// Creates the font resource (if necessary) and returns the descriptor
		/// </summary>
		/// <param name="fontName"></param>
		/// <param name="fontSize"></param>
		/// <returns></returns>
		FontDescriptor GetFontDescriptor(const char* fontName, int fontSize);
		/// <summary>
		/// Returns precached font (if exists)
		/// </summary>
		/// <param name="fontDescriptor"></param>
		/// <returns></returns>
		TTF_Font* GetFont(FontDescriptor fontDescriptor);

	private:
		SDL_Renderer* m_Renderer;
		SDL_Window* m_Window;

		std::unordered_map<FontDescriptor, TTF_Font*, FontDescriptorHasher> m_Fonts;

		TTF_Font* m_LoadFont(const char* fontName, int fontSize);
	};
}