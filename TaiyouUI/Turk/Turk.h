#pragma once
#include <unordered_map>
#include <SDL3_ttf/SDL_ttf.h>
#include "FontDescriptor.h"
#include "FontDescriptorHasher.h"
#include <string>
#include <memory>
using namespace TaiyouUI::Turk;

namespace TaiyouUI
{
	/// <summary>
	/// TaiyouUI Resource Keeper
	/// </summary>
	class TurkInstance
	{
	public:
		TurkInstance(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Window> window);
		~TurkInstance();

		/// <summary>
		/// Creates the font resource (if necessary) and returns the descriptor
		/// </summary>
		/// <param name="fontName"></param>
		/// <param name="fontSize"></param>
		/// <returns></returns>
		FontDescriptor GetFontDescriptor(std::string fontName, int fontSize);
		/// <summary>
		/// Returns precached font (if exists)
		/// </summary>
		/// <param name="fontDescriptor"></param>
		/// <returns></returns>
		TTF_Font* GetFont(FontDescriptor fontDescriptor);

		// Logging Utilities
		void LogWarning(const std::string& message);

	private:
		std::shared_ptr<SDL_Renderer> m_Renderer;
		std::shared_ptr<SDL_Window> m_Window;

		std::unordered_map<FontDescriptor, TTF_Font*, FontDescriptorHasher> m_Fonts;

		TTF_Font* m_LoadFont(const std::string &fontName, int fontSize);
		std::string NormalizeFontName(std::string fontName);
	};
}