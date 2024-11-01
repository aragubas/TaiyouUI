#include "FontDescriptor.h"

TaiyouUI::Turk::FontDescriptor::FontDescriptor() :
	Name(""), Size(0)
{
}

TaiyouUI::Turk::FontDescriptor::FontDescriptor(std::string name, int size) :
	Name(name), Size(size)
{
}

bool TaiyouUI::Turk::FontDescriptor::operator==(const FontDescriptor& object) const
{
	return object.Name == Name && object.Size == Size;
}
