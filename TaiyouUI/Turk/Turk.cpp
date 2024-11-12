#include "Turk.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <fmt/printf.h>
using namespace TaiyouUI::Turk;


Turk::Turk(SDL_Renderer* renderer, SDL_Window* window) :
	m_Renderer(renderer), m_Window(window)
{
	// Reserve 4 spots for fonts
	m_Fonts.reserve(4);

	// Check if Application Data folder exists
	std::filesystem::path path = std::filesystem::path("Application Data");
	if (!std::filesystem::exists(path))
	{
		throw std::runtime_error("Could not find Application Data, required for assets.");
	}
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

FontDescriptor TaiyouUI::Turk::Turk::GetFontDescriptor(std::string fontName, int fontSize)
{
	FontDescriptor descriptor;
	descriptor.Name = NormalizeFontName(fontName);
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

TTF_Font* Turk::Turk::m_LoadFont(const std::string &fontName, int fontSize)
{
	std::string name = NormalizeFontName(fontName);

	// Check if font exists in cache
	FontDescriptor fontDescriptor(name, fontSize);

	if (m_Fonts.contains(fontDescriptor))
	{
		std::cout << "[Warning] Turk::m_LoadFont attempt to load a font twice" << std::endl;
		return m_Fonts[fontDescriptor];
	}

	// Add font to cache
	std::filesystem::path fontPath = std::filesystem::path("Application Data") / "Fonts" / name;
	TTF_Font* newFont = TTF_OpenFont(fontPath.string().c_str(), fontSize);

	if (newFont == nullptr)
	{
		const char* error = TTF_GetError();

		std::cout << error << std::endl;

		throw std::runtime_error(error);
	}

	fmt::printf("[Debug] Turk::m_LoadFont new font loaded: name: \"%s\" size: \"%i\"\n", fontDescriptor.Name, fontDescriptor.Size);
	
	m_Fonts[fontDescriptor] = newFont;

	return newFont;
}

std::string Turk::Turk::NormalizeFontName(std::string fontName)
{
	if (fontName.ends_with(".ttf"))
	{
		return fontName;
	}
	// If font name doesn't end with .ttf
	fontName.append(".ttf");

	return fontName;
}
