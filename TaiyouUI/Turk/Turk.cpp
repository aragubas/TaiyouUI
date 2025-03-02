#include "Turk.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <fmt/printf.h>
using namespace TaiyouUI;

TurkInstance::TurkInstance(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Window> window) :
	m_Renderer(renderer), 
	m_Window(window),
	m_Fonts(std::unordered_map<FontDescriptor, TTF_Font*, FontDescriptorHasher>())
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

TurkInstance::~TurkInstance()
{
	std::cout << "Turk::~Turk() Releasing all resources" << std::endl;
	// Release all font resources
	for (auto& [key, value] : m_Fonts)
	{
		TTF_CloseFont(value);
	}
}

FontDescriptor TurkInstance::GetFontDescriptor(std::string fontName, int fontSize)
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

TTF_Font* TurkInstance::GetFont(FontDescriptor fontDescriptor)
{
	// Check if font exists in cache
	if (m_Fonts.contains(fontDescriptor))
		return m_Fonts[fontDescriptor];

	return m_LoadFont(fontDescriptor.Name, fontDescriptor.Size);
}

TTF_Font* TurkInstance::m_LoadFont(const std::string &fontName, int fontSize)
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
		const char* error = SDL_GetError();

		std::cout << error << std::endl;

		throw std::runtime_error(error);
	}

#ifndef NDEBUG
	fmt::printf("[Debug] Turk::m_LoadFont new font loaded: name: \"%s\" size: \"%i\"\n", fontDescriptor.Name, fontDescriptor.Size);
#endif

	m_Fonts[fontDescriptor] = newFont;

	return newFont;
}

std::string TurkInstance::NormalizeFontName(std::string fontName)
{
	if (fontName.ends_with(".ttf"))
	{
		return fontName;
	}
	// If font name doesn't end with .ttf
	fontName.append(".ttf");

	return fontName;
}

void TurkInstance::LogWarning(const std::string& message)
{
	fmt::printf("[Turk::LogWarning] %s\n", message);
}