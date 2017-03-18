// ObjectModelTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AdaptiveCard.h"
#include "TextBlock.h"
#include <memory>
#include <iostream>

using namespace std;
using namespace AdaptiveCards;
int main()
{
    TextBlock textBlock(make_shared<Container>(), HorizontalAlignment::Center, Size::Auto, L"This is my adaptive card speech!!", L"This is the textblock's text", TextSize::Normal, TextWeight::Normal, true, true);
    wcout << "The text is: " << textBlock.GetText() << endl;
    return 0;
}

