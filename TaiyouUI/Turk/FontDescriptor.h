#pragma once
#include <string>

namespace TaiyouUI::Turk
{
	struct FontDescriptor
	{
		std::string Name;
		int Size;

		FontDescriptor();
		FontDescriptor(std::string name, int size);

		bool operator ==(const FontDescriptor& object) const;
	};
}

