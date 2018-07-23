#include "stdafx.h"
#include "ConsoleRender.h"
#include "TextBlock.h"
#include "Container.h"
#include "Image.h"

using namespace AdaptiveSharedNamespace;

void RenderElements(std::vector<std::shared_ptr<BaseCardElement>> elements, std::string& consoleString)
{
	for (auto element : elements)
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
			default:
				break;
		}
	}
}

void RenderToConsole(std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> card, std::string& consoleString)
{
	auto body = card->GetBody();
	RenderElements(body, consoleString);
}
