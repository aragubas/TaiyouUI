#pragma once
#include <functional>
#include <string>
#include "FontDescriptor.h"

namespace TaiyouUI::Turk
{
	struct FontDescriptorHasher
	{
		std::size_t operator()(const FontDescriptor& key) const
		{
			return ((std::hash<std::string>()(key.Name)
				^ (std::hash<int>()(key.Size) << 1)) >> 1);
		}
	};
}

