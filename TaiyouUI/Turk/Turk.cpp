#include "Turk.h"
#include <string>
#include <filesystem>
#include <iostream>
using namespace TaiyouUI::Turk;


Turk::Turk(SDL_Renderer* renderer, SDL_Window* window) :
	m_Renderer(renderer), m_Window(window)
{
	// Reserve 4 spots fo
	m_Fonts.reserve(4);
}

Turk::Turk::~Turk()
{
	std::cout << "Turk::~Turk() Releasing all resources" << std::endl;
	// Release all font resources
	for (auto& [key, value] : m_Fonts)
	{
		TTF_CloseFont(value);
	}
}

FontDescriptor TaiyouUI::Turk::Turk::GetFontDescriptor(const char* fontName, int fontSize)
{
	FontDescriptor descriptor;
	descriptor.Name = fontName;
	descriptor.Size = fontSize;
	
	// Check if font resource already exists
	if (m_Fonts.contains(descriptor))
		return descriptor;
	

	m_LoadFont(fontName, fontSize);

	return descriptor;
}

TTF_Font* Turk::GetFont(FontDescriptor fontDescriptor)
{
	// Check if font exists in cache
	if (m_Fonts.contains(fontDescriptor))
		return m_Fonts[fontDescriptor];

	return m_LoadFont(fontDescriptor.Name, fontDescriptor.Size);
}

TTF_Font* Turk::Turk::m_LoadFont(const char* fontName, int fontSize)
{
	// Normalize fontName
	const char* finalFontName;
	std::string fontNameAsString = std::string(fontName);

	if (fontNameAsString.ends_with(".ttf"))
	{
		// Remove .ttf from the end of name
		fontNameAsString = fontNameAsString.replace(fontNameAsString.find_last_of(".ttf", 4), 4, "");
	}
	fontNameAsString.append(".ttf");
	finalFontName = fontNameAsString.c_str();


	// Check if font exists in cache
	FontDescriptor fontDescriptor(finalFontName, fontSize);

	if (m_Fonts.contains(fontDescriptor))
	{
		std::cout << "[Warning] Turk::m_LoadFont called when font is already loaded" << std::endl;
		return m_Fonts[fontDescriptor];
	}

	// Add font to cache
	std::filesystem::path fontPath = std::filesystem::path("Application Data") / "Fonts" / finalFontName;
	TTF_Font* newFont = TTF_OpenFont(fontPath.string().c_str(), fontSize);

	if (newFont == nullptr)
	{
		const char* error = TTF_GetError();

		std::cout << error << std::endl;

		throw std::runtime_error(error);
	}

	m_Fonts[fontDescriptor] = newFont;
}
