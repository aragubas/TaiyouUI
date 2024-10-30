#pragma once

namespace TaiyouUI::Turk
{
	struct FontDescriptor
	{
		const char* Name;
		int Size;

		FontDescriptor();
		FontDescriptor(const char* name, int size);

		bool operator ==(const FontDescriptor& object) const;
	};
}

