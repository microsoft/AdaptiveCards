#include "stdafx.h"
#include "ConsoleRender.h"
#include "TextBlock.h"
#include "Container.h"
#include "Image.h"
#include "ColumnSet.h"

using namespace AdaptiveSharedNamespace;

void RenderElements(std::vector<std::shared_ptr<BaseCardElement>> elements, std::string& consoleString);
void RenderColumnSet(ColumnSet &set, std::string &consoleString);

void RenderElement(std::shared_ptr<BaseCardElement> element, std::string &consoleString)
{
	switch (element->GetElementType())
	{
	case CardElementType::Container:
		RenderElements(std::dynamic_pointer_cast<Container>(element)->GetItems(), consoleString);
		break;
	case CardElementType::TextBlock:
		consoleString += std::dynamic_pointer_cast<TextBlock>(element)->GetText() + "\n";
		break;
	case CardElementType::Image:
		consoleString += std::dynamic_pointer_cast<Image>(element)->GetAltText() + "\n";
		break;
	case CardElementType::Column:
		consoleString += "Column:\n"; // std::dynamic_pointer_cast<Column>(element)->
		break;
	case CardElementType::ColumnSet:
		consoleString += "ColumnSet:\n";
		RenderColumnSet(*std::dynamic_pointer_cast<ColumnSet>(element), consoleString);
		break;
	default:
		consoleString += "Unimplemented: " + AdaptiveSharedNamespace::CardElementTypeToString(element->GetElementType()) + "\n";
		break;
	}
}

void RenderElements(std::vector<std::shared_ptr<BaseCardElement>> elements, std::string& consoleString)
{
	for (auto element : elements)
	{
		RenderElement(element, consoleString);
	}
}

void RenderColumnSet(ColumnSet &set, std::string &consoleString)
{
	auto columns = set.GetColumns();
	for (auto column : columns)
	{
		consoleString += "Column:\n";
		for (auto item : column->GetItems())
		{
			RenderElement(item, consoleString);
		}
	}
}

void RenderToConsole(std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> card, std::string& consoleString)
{
	auto body = card->GetBody();
	RenderElements(body, consoleString);
}
