#include "pch.h"
#include "CppUnitTest.h"
#include "AdaptiveRenderContext.h"
#include "QmlTag.h"
#include "RenderedQmlAdaptiveCard.h"
#include "AdaptiveCardQmlRenderer.h"
#include "HostConfig.h"
#include "AdaptiveCardDependency.h"
#include "Formatter.h"
#include <rpc.h>
#include <windows.h>
#include <shellapi.h>
#include <mutex>
#include "Utils.h"
#include "adaptivecard_light_config.h"
#include "resource.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace RendererQml;

namespace CppUnitTestFramework
{
	HMODULE GCM()
	{
		HMODULE hModule = NULL;
		GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)GCM, &hModule);
		return hModule;
	}

	static std::string getQmlString(int fileCode)
	{
		std::string result;
		HRSRC hres = FindResource(GCM(), MAKEINTRESOURCE(fileCode), MAKEINTRESOURCE(TEXTFILE));
		HGLOBAL hData = LoadResource(GCM(), hres);
		DWORD hSize = SizeofResource(GCM(), hres);
		char* hFinal = (char*)LockResource(hData);
		result.assign(hFinal, hSize);

		return result;
	}

	static std::string GenerateQml(std::string cardQml)
	{
		std::shared_ptr<AdaptiveCards::ParseResult> mainCard = AdaptiveCards::AdaptiveCard::DeserializeFromString(cardQml, "2.0");
		std::shared_ptr<AdaptiveCardQmlRenderer> renderer_ptr;
		std::shared_ptr<AdaptiveSharedNamespace::HostConfig> hostConfig = std::make_shared<AdaptiveSharedNamespace::HostConfig>(AdaptiveSharedNamespace::HostConfig::DeserializeFromString(LightConfig::lightConfig));
		renderer_ptr = std::make_shared<AdaptiveCardQmlRenderer>(AdaptiveCardQmlRenderer(hostConfig));
		renderer_ptr = std::make_shared<AdaptiveCardQmlRenderer>(AdaptiveCardQmlRenderer(hostConfig));
		std::shared_ptr<RenderedQmlAdaptiveCard> result = renderer_ptr->RenderCard(mainCard->GetAdaptiveCard());
		const auto generatedQml = result->GetResult();
		return generatedQml->ToString();
	}

	TEST_CLASS(QmlRendererUnitTest)
	{
	public:
		TEST_METHOD(EmptyAdaptiveCard)
		{
			std::string card = R"({
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "type" : "AdaptiveCard",
                "version" : "2.0",
                "body" : []
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(EMPTY_ADAPTIVE_CARD);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}
		
		TEST_METHOD(SimpleAdaptiveCard)
		{
			std::string card = R"({
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "type" : "AdaptiveCard",
                "version" : "2.0",
                "body" : [
                    {
                        "type": "TextBlock",
                        "text" : "This card's action will show another card"
                    }
                ],
                "actions": [
                    {
                        "type": "Action.ShowCard",
                        "title" : "Action.ShowCard",
                        "card" : {
                        "type": "AdaptiveCard",
                        "body" : [
                            {
                                "type": "TextBlock",
                                "text" : "What do you think?"
                            }
                        ],
                        "actions": [
                            {
                                "type": "Action.Submit",
                                "title" : "Neat!"
                            }
                        ]
                        }
                    }
                ]
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(SIMPLE_ADAPTIVE_CARD);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(Input_Text_One)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Input.Text",
                        "id": "text1",
                        "title": "New Input.Toggle1",
                        "placeholder": "Placeholder text 1"
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(INPUT_TEXT_ONE);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(Input_Text_Multiple)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Input.Text",
                        "id": "text1",
                        "title": "New Input.Toggle1",
                        "placeholder": "Placeholder text 1"
                    },
                    {
                        "type": "Input.Text",
                        "id": "text2",
                        "title": "New Input.Toggle2",
                        "placeholder": "Placeholder text2"
                    },
                    {
                        "type": "Input.Text",
                        "id": "text3",
                        "title": "New Input.Toggle3",
                        "placeholder": "Placeholder text3"
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(INPUT_TEXT_MULTIPLE);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(Input_Text_Multiple_Separator)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Input.Text",
                        "id": "text1",
                        "title": "New Input.Toggle1",
                        "placeholder": "Placeholder text 1"
                    },
                    {
                        "type": "Input.Text",
                        "id": "text2",
                        "separator": true,
                        "title": "New Input.Toggle2",
                        "placeholder": "Placeholder text2"
                    },
                    {
                        "type": "Input.Text",
                        "id": "text3",
                        "title": "New Input.Toggle3",
                        "placeholder": "Placeholder text3"
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(INPUT_TEXT_MULTIPLE_SEPERATOR);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(CardActions)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "actions": [
                    {
                        "type": "Action.OpenUrl",
                        "id": "openurl",
                        "title": "Action.OpenUrl",
                        "url": "https://www.example.com"
                    },
                    {
                        "type": "Action.Submit",
                        "id": "submit",
                        "title": "Action.Submit",
                        "data": {
                            "a": "b"
                        }
                    },
                    {
                        "type": "Action.ShowCard",
                        "id": "showcard",
                        "title": "Action.ShowCard",
                        "card": {
                            "type": "AdaptiveCard",
                            "style": "emphasis",
                            "body": [
                                {
                                    "type": "Input.Text",
                                    "id": "a",
                                    "placeholder": "Placeholder text"
                                }
                            ],
                            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json"
                        }
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(CARD_ACTIONS);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(ColumnSet1)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "ColumnSet",
                        "columns": [
                            {
                                "type": "Column",
                                "items": [
                                    {
                                        "type": "Input.Text",
                                        "id": "t1",
                                        "title": "New Input.Toggle",
                                        "placeholder": "Placeholder text"
                                    }
                                ],
                                "width": "stretch"
                            },
                            {
                                "type": "Column",
                                "items": [
                                    {
                                        "type": "Input.Text",
                                        "id": "t2",
                                        "title": "New Input.Toggle",
                                        "placeholder": "Placeholder text"
                                    }
                                ],
                                "width": "stretch"
                            },
                            {
                                "type": "Column",
                                "items": [
                                    {
                                        "type": "Input.Text",
                                        "id": "t3",
                                        "title": "New Input.Toggle",
                                        "placeholder": "Placeholder text"
                                    }
                                ],
                                "width": "stretch"
                            }
                        ]
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(COLUMN_SET_ONE);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(TextBlock)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "TextBlock",
                        "id": "t1",
                        "text": "Next Text1"
                    },
                    {
                        "type": "TextBlock",
                        "id": "t2",
                        "spacing": "Medium",
                        "separator": true,
                        "height": "stretch",
                        "size": "Medium",
                        "weight": "Bolder",
                        "color": "Dark",
                        "text": "Text2",
                        "maxLines": 2
                    },
                    {
                        "type": "TextBlock",
                        "id": "t3",
                        "horizontalAlignment": "Right",
                        "size": "Small",
                        "weight": "Lighter",
                        "color": "Warning",
                        "text": "New TextBlock with wrap",
                        "isSubtle": true,
                        "wrap": true
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(TEXT_BLOCK);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(Containers)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Container",
                        "items": [
                            {
                                "type": "TextBlock",
                                "id": "t1",
                                "text": "New TextBlock"
                            },
                            {
                                "type": "Container",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "id": "t2",
                                        "text": "New TextBlock"
                                    }
                                ]
                            },
                            {
                                "type": "Input.Text",
                                "id": "i1",
                                "title": "New Input.Toggle",
                                "placeholder": "Placeholder text"
                            }
                        ]
                    },
                    {
                        "type": "Container",
                        "items": [
                            {
                                "type": "TextBlock",
                                "id": "t3",
                                "text": "New TextBlock"
                            },
                            {
                                "type": "Container",
                                "items": [
                                    {
                                        "type": "TextBlock",
                                        "id": "t4",
                                        "text": "New TextBlock"
                                    }
                                ]
                            }
                        ]
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(CONTAINERS);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(BackgroundImages)
		{
			std::string card = R"({
				"type": "AdaptiveCard",
				"backgroundImage": {
					"url": "https://adaptivecards.io/content/AlkiBeach.jpg"
				},
				"body": [
					{
						"type": "ColumnSet",
						"columns": [
							{
								"type": "Column",
								"backgroundImage": {
									"url": "https://adaptivecards.io/content/GoldenGardensPark.jpg"
								},
								"width": "stretch",
								"items": [
									{
										"type": "TextBlock",
										"text": "New TextBlock",
										"wrap": true
									}
								]
							}
						]
					}
				],
				"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
				"version": "1.3"
			})";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(BACKGROUND_IMAGES);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(FactSet)
		{
			std::string card = R"({
				"type": "AdaptiveCard",
				"backgroundImage": "http://www.cisco.com/logo.png",
				"body": [
					{
						"type": "FactSet",
						"id": "fs1",
						"facts": [
							{
								"title": "Fact 1",
								"value": "Value 1"
							},
							{
								"title": "Fact 2",
								"value": "Value 2"
							}
						]
					},
					{
						"type": "FactSet",
						"id": "fs2",
						"spacing": "Small",
						"separator": true,
						"height": "stretch",
						"facts": [
							{
								"title": "F1",
								"value": "V1"
							},
							{
								"title": "F2",
								"value": "V2"
							}
						]
					}
				],
				"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
				"version": "1.0"
			})";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(FACT_SET);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(ChoiceSets)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Input.ChoiceSet",
                        "id": "choice1",
                        "value": "Choice 1",
                        "placeholder": "Placeholder text",
                        "choices": [
                            {
                                "title": "Choice 1",
                                "value": "Choice 1"
                            },
                            {
                                "title": "Choice 2",
                                "value": "Choice 2"
                            },
                            {
                                "title": "Choice 3",
                                "value": "Choice 3"
                            }
                        ],
                        "style": "expanded",
                        "isMultiSelect": true
                    },
                    {
                        "type": "Input.ChoiceSet",
                        "id": "choice2",
                        "value": "Choice 1",
                        "placeholder": "Placeholder text",
                        "choices": [
                            {
                                "title": "Choice 1",
                                "value": "Choice 1"
                            },
                            {
                                "title": "Choice 2",
                                "value": "Choice 2"
                            }
                        ],
                        "style": "expanded"
                    },
                    {
                        "type": "Input.ChoiceSet",
                        "id": "Choice3",
                        "title": "Choice 3 Title",
                        "value": "Choice 2",
                        "placeholder": "Placeholder text",
                        "choices": [
                            {
                                "title": "Choice 1",
                                "value": "Choice 1"
                            },
                            {
                                "title": "Choice 2",
                                "value": "Choice 2"
                            }
                        ]
                    },
                    {
                        "type": "Input.ChoiceSet",
                        "id": "Choice4",
                        "placeholder": "Placeholder text",
                        "choices": [
                            {
                                "title": "Choice 1",
                                "value": "Choice 1"
                            },
                            {
                                "title": "Choice 2",
                                "value": "Choice 2"
                            }
                        ]
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(CHOICE_SETS);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(DateInput1)
		{
			std::string card = R"({
				"type": "AdaptiveCard",
					"body" : [
				{
					"type": "Input.Date",
						"id" : "d1",
						"title" : "tg1"
				},
				{
					"type": "Input.Date",
					"id" : "d2",
					"spacing" : "Small",
					"separator" : true,
					"title" : "tg2"
				},
				{
					"type": "Input.Date",
					"id" : "d3",
					"title" : "tg3"
				}
						],
						"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
							"version" : "1.0"
				}
			)";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(DATE_INPUT_ONE);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(ToggleInput)
		{
			std::string card = R"({
            "type": "AdaptiveCard",
            "body": [
                {
                    "type": "Input.Toggle",
                    "id": "t1",
                    "title": "New Input.Toggle",
                    "value": "false"
                },
                {
                    "type": "Input.Toggle",
                    "id": "t2",
                    "separator": true,
                    "title": "New Input.Toggle2",
                    "value": "true"
                },
                {
                    "type": "Input.Toggle",
                    "id": "t3",
                    "spacing": "Small",
                    "separator": true,
                    "title": "New Input.Toggle3",
                    "value": "customTrue",
                    "valueOn": "customTrue",
                    "valueOff": "customFalse"
                },
                {
                    "type": "Input.Toggle",
                    "id": "t4",
                    "title": "New Input.Toggle",
                    "value": "false"
                }
            ],
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.0"
        })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(TOGGLE_INPUT);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(ImageSet)
		{
			std::string card = R"({
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "type": "AdaptiveCard",
                "version": "1.0",
                "body": [
                {
                    "type": "TextBlock",
                    "text": "Here are some cool photos",
                    "size": "large"
                },
                {
                    "type": "TextBlock",
                    "text": "Sorry some of them are repeats",
                    "size": "medium",
                    "weight": "lighter"
                },
                {
                    "type": "ImageSet",
                    "imageSize": "medium",
                    "images": [
                    {
                        "type": "Image",
                        "url": "https://picsum.photos/200/200?image=100"
                    },
                    {
                        "type": "Image",
                        "url": "https://picsum.photos/300/200?image=200"
                    },
                    {
                        "type": "Image",
                        "url": "https://picsum.photos/300/200?image=301"
                    },
                    {
                        "type": "Image",
                        "url": "https://picsum.photos/200/200?image=400"
                    },
                    {
                        "type": "Image",
                        "url": "https://picsum.photos/300/200?image=500"
                    },
                    {
                        "type": "Image",
                        "url": "https://picsum.photos/200/200?image=600"
                    },
                    {
                        "type": "Image",
                        "url": "https://picsum.photos/300/200?image=700"
                    },
                    {
                        "type": "Image",
                        "url": "https://picsum.photos/300/200?image=800"
                    },
                    {
                        "type": "Image",
                        "url": "https://picsum.photos/300/200?image=900"
                    }
                    ]
                }
                ]
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(IMAGE_SET);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(Image)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Image",
                        "id": "i1",
                        "selectAction": {
                            "type": "Action.OpenUrl",
                            "id": "a1",
                            "title": "Hello",
                            "iconUrl": "https://www.cisco.com/logo.png",
                            "url": "https://www.cisco.com/"
                        },
                        "backgroundColor": "#AABBCC",
                        "url": "https://picsum.photos/300/200?image=800",
                        "width": "10px",
                        "height": "10px",
                        "altText": ""
                    },
                    {
                        "type": "Image",
                        "id": "i2",
                        "isVisible": false,
                        "horizontalAlignment": "Left",
                        "spacing": "Small",
                        "separator": true,
                        "selectAction": {
                            "type": "Action.Submit",
                            "id": "s1",
                            "title": "submit",
                            "iconUrl": "https://www.cisco.com/logo2.png",
                            "ignoreInputValidation": true,
                            "data": {
                                "h": "x"
                            }
                        },
                        "url": "https://picsum.photos/200/200?image=100",
                        "altText": ""
                    },
                    {
                        "type": "Image",
                        "id": "i3",
                        "horizontalAlignment": "Center",
                        "height": "stretch",
                        "selectAction": {
                            "type": "Action.ToggleVisibility",
                            "id": "tv1",
                            "title": "toggle",
                            "iconUrl": "https://www.cisco.com/logo3.png",
                            "style": "positive",
                            "targetElements": ["i2"]
                        },
                        "url": "https://picsum.photos/300/200?image=200",
                        "size": "Stretch",
                        "altText": "i3 alt"
                    },
                    {
                        "type": "Image",
                        "id": "i4",
                        "url": "https://picsum.photos/300/200?image=301",
                        "size": "Large",
                        "altText": ""
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(IMAGE);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(InvalidImageThrows)
		{
			std::string noUrl = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Image",
                        "id": "i1",
                        "selectAction": {
                            "type": "Action.OpenUrl",
                            "id": "a1",
                            "title": "Hello",
                            "iconUrl": "https://www.cisco.com/logo.png"
                        },
                        "backgroundColor": "#AABBCC",
                        "url": "https://picsum.photos/300/200?image=800",
                        "width": "10px",
                        "height": "10px",
                        "altText": ""
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string noTarget = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Image",
                        "id": "i3",
                        "horizontalAlignment": "Center",
                        "height": "stretch",
                        "selectAction": {
                            "type": "Action.ToggleVisibility",
                            "id": "tv1",
                            "title": "toggle",
                            "iconUrl": "https://www.cisco.com/logo3.png",
                            "style": "positive",
                            "targetElements": []
                        },
                        "url": "https://picsum.photos/300/200?image=200",
                        "size": "Stretch",
                        "altText": "i3 alt"
                    }                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";
			bool isException = false;
			try
			{
				std::shared_ptr<AdaptiveCards::ParseResult> mainCard = AdaptiveCards::AdaptiveCard::DeserializeFromString(noUrl, "2.0");
			}
			catch (const std::exception&)
			{
				isException = true;
			}
			Assert::IsTrue(isException);

			isException = false;
			try
			{
				std::shared_ptr<AdaptiveCards::ParseResult> mainCard = AdaptiveCards::AdaptiveCard::DeserializeFromString(noTarget, "2.0");
			}
			catch (const std::exception&)
			{
				isException = true;
			}
			Assert::IsTrue(isException);
		}

		TEST_METHOD(Time)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Input.Time",
                        "id": "t1",
                        "title": "Toggle1",
                        "value": "20:15",
                        "validation": {
                            "necessity": "Required",
                            "errorMessage": "e1"
                        }
                    },
                    {
                        "type": "Input.Time",
                        "id": "t2",
                        "isVisible": false,
                        "title": "Toggle2",
                        "value": "10:15"
                    },
                    {
                        "type": "Input.Time",
                        "id": "t3",
                        "spacing": "Large",
                        "separator": true,
                        "title": "Toggle3",
                        "validation": {
                            "necessity": "RequiredWithVisualCue"
                        },
                        "min": "10:00",
                        "max": "20:00"
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(TIME);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(DateInput2)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Input.Date",
                        "id": "d1",
                        "title": "Tog1",
                        "value": "",
                        "validation": {
                            "necessity": "Required"
                        }
                    },
                    {
                        "type": "Input.Date",
                        "id": "d2",
                        "isVisible": false,
                        "spacing": "Large",
                        "title": "Tog2"
                    },
                    {
                        "type": "Input.Date",
                        "id": "d3",
                        "separator": true,
                        "title": "Tog3",
                        "value": "2019-03-21",
                        "validation": {
                            "necessity": "RequiredWithVisualCue",
                            "errorMessage": "e1"
                        },
                        "min": "2000-01-01",
                        "max": "2020-12-31"
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(DATE_INPUT_TWO);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(NumberInput)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Input.Number",
                        "id": "i1",
                        "spacing": "Small",
                        "title": "tog1",
                        "value": 0,
                        "validation": {
                            "necessity": "Required"
                        },
                        "placeholder": "Placeholder text",
                        "min": 0,
                        "max": 5
                    },
                    {
                        "type": "Input.Number",
                        "id": "i2",
                        "isVisible": false,
                        "title": "tog2",
                        "value": 2,
                        "placeholder": "placeholder2",
                        "min": 1,
                        "max": 4
                    },
                    {
                        "type": "Input.Number",
                        "id": "i3",
                        "title": "tog3",
                        "value": 1,
                        "validation": {
                            "necessity": "RequiredWithVisualCue",
                            "errorMessage": "e2"
                        },
                        "placeholder": "placeholder3",
                        "min": -10,
                        "max": 10
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(NUMBER_INPUT);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(InvalidNumberThrows)
		{
			std::string numberString = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Input.Number",
                        "id": "i1",
                        "spacing": "Small",
                        "title": "tog1",
                        "value": "0",
                        "validation": {
                            "necessity": "Required"
                        },
                        "placeholder": "Placeholder text",
                        "min": "0",
                        "max": "5"
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";


			bool isException = false;
			try
			{
				std::shared_ptr<AdaptiveCards::ParseResult> mainCard = AdaptiveCards::AdaptiveCard::DeserializeFromString(numberString, "2.0");
			}
			catch (const std::exception&)
			{
				isException = true;
			}
			Assert::IsTrue(isException);
		}

		TEST_METHOD(RichTextBasic)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "RichTextBlock",
                        "id": "r1",
                        "horizontalAlignment": "Left",
                        "inlines": [
                            {
                                "type": "TextRun",
                                "text": "New RichTextBlock1"
                            },
                            {
                                "type": "TextRun",
                                "text": "New RichTextBlock2"
                            }
                        ]
                    },
                    {
                        "type": "RichTextBlock",
                        "id": "r2",
                        "isVisible": false,
                        "horizontalAlignment": "Center",
                        "spacing": "Large",
                        "separator": true,
                        "inlines": [
                            {
                                "type": "TextRun",
                                "text": "New RichTextBlock3"
                            },
                            {
                                "type": "TextRun",
                                "text": "New RichTextBlock4"
                            }
                        ]
                    },
                    {
                        "type": "RichTextBlock",
                        "id": "r3",
                        "height": "stretch",
                        "inlines": [
                            {
                                "type": "TextRun",
                                "text": "New RichTextBlock5"
                            },
                            {
                                "type": "TextRun",
                                "text": "New RichTextBlock6"
                            },
                            {
                                "type": "TextRun",
                                "text": "New RichTextBlock7"
                            }
                        ]
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(RICH_TEXT_BASIC);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(ApplyText)
		{
			std::string card = R"({
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "type": "AdaptiveCard",
              "version": "1.0",
              "body": [
                {
                  "type": "TextBlock",
                  "text": "Created {{DATE(2017-02-14T06:08:39Z, SHORT)}} {{TIME(2017-02-14T02:08:39+08:30)}} {{TIME(2017-02-14T18:08:39-08:30)}} {{DATE(2017-02-14T02:08:39+08:30, SHORT)}} {{DATE(2017-02-14T18:08:39-08:30, SHORT)}} {{DATE(2017-02-14T06:08:39Z, LONG)}} {{DATE(2017-02-14T06:08:39Z, COMPACT)}}",
                  "weight": "bolder",
                  "size": "medium"
                }]
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(APPLY_TEXT);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(JiraBot)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Container",
                        "border": true,
                        "items": [
                            {
                                "type": "ColumnSet",
                                "spacing": "Medium",
                                "separator": true,
                                "columns": [
                                    {
                                        "type": "Column",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "horizontalAlignment": "Left",
                                                "size": "Medium",
                                                "weight": "Bolder",
                                                "color": "Accent",
                                                "text": "Create issue",
                                                "wrap": true
                                            }
                                        ],
                                        "width": "stretch"
                                    }
                                ]
                            },
                            {
                                "type": "ColumnSet",
                                "horizontalAlignment": "Left",
                                "spacing": "Medium",
                                "columns": [
                                    {
                                        "type": "Column",
                                        "horizontalAlignment": "Center",
                                        "verticalContentAlignment": "Bottom",
                                        "items": [
                                            {
                                                "type": "TextBlock",
                                                "spacing": "Medium",
                                                "weight": "Bolder",
                                                "color": "Dark",
                                                "text": "Summary",
                                                "wrap": true
                                            },
                                            {
                                                "type": "Input.Text",
                                                "id": "summary",
                                                "placeholder": "Enter a summary"
                                            },
                                            {
                                                "type": "TextBlock",
                                                "horizontalAlignment": "Left",
                                                "weight": "Bolder",
                                                "color": "Dark",
                                                "text": "Project",
                                                "wrap": true
                                            },
                                            {
                                                "type": "Input.ChoiceSet",
                                                "id": "projectDropdown",
                                                "value": "WTB",
                                                "placeholder": "Select Project",
                                                "choices": [
                                                    {
                                                        "title": "webex",
                                                        "value": "WTB"
                                                    }
                                                ]
                                            },
                                            {
                                                "type": "TextBlock",
                                                "spacing": "Medium",
                                                "weight": "Bolder",
                                                "color": "Dark",
                                                "text": "Issue Type",
                                                "wrap": true
                                            },
                                            {
                                                "type": "Input.ChoiceSet",
                                                "id": "issueTypeDropdown",
                                                "value": "Story",
                                                "placeholder": "Select an Issue Type",
                                                "choices": [
                                                    {
                                                        "title": "Story",
                                                        "value": "Story"
                                                    },
                                                    {
                                                        "title": "Bug",
                                                        "value": "Bug"
                                                    },
                                                    {
                                                        "title": "Task",
                                                        "value": "Task"
                                                    }
                                                ]
                                            }
                                        ],
                                        "width": "stretch"
                                    }
                                ]
                            }
                        ]
                    }
                ],
                "actions": [
                    {
                        "type": "Action.ShowCard",
                        "title": "Details",
                        "card": {
                            "type": "AdaptiveCard",
                            "style": "emphasis",
                            "body": [
                                {
                                    "type": "TextBlock",
                                    "horizontalAlignment": "Left",
                                    "weight": "Bolder",
                                    "text": "Optional Details",
                                    "wrap": true
                                },
                                {
                                    "type": "TextBlock",
                                    "spacing": "Medium",
                                    "weight": "Bolder",
                                    "text": "Description",
                                    "wrap": true
                                },
                                {
                                    "type": "Input.Text",
                                    "id": "description",
                                    "placeholder": "Enter a description",
                                    "isMultiline": true,
                                    "style": "Email"
                                },
                                {
                                    "type": "TextBlock",
                                    "spacing": "Medium",
                                    "weight": "Bolder",
                                    "text": "Priority",
                                    "wrap": true
                                },
                                {
                                    "type": "Input.ChoiceSet",
                                    "id": "priority",
                                    "value": "low",
                                    "placeholder": "Low",
                                    "choices": [
                                        {
                                            "title": "Low",
                                            "value": "low"
                                        },
                                        {
                                            "title": "Medium",
                                            "value": "medium"
                                        },
                                        {
                                            "title": "High",
                                            "value": "high"
                                        }
                                    ]
                                },
                                {
                                    "type": "TextBlock",
                                    "spacing": "Medium",
                                    "weight": "Bolder",
                                    "text": "Assignee",
                                    "wrap": true
                                },
                                {
                                    "type": "Input.ChoiceSet",
                                    "id": "assigneeDropdown",
                                    "value": "admin",
                                    "placeholder": "Select an assignee",
                                    "choices": [
                                        {
                                            "title": "webex-teams-bots",
                                            "value": "admin"
                                        }
                                    ]
                                }
                            ],
                            "actions": [
                                {
                                    "type": "Action.Submit",
                                    "title": "Create Issue"
                                }
                            ],
                            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json"
                        }
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(JIRA_BOT);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(Concur_Approved)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "TextBlock",
                        "size": "Medium",
                        "weight": "Bolder",
                        "color": "Dark",
                        "text": "Jane Jordan's report is approved",
                        "wrap": true
                    }
                ],
                "actions": [
                    {
                        "type": "Action.Submit",
                        "id": "showNextPendingBtn1",
                        "title": "Show next pending",
                        "data": {
                            "buttonId": "showNextPendingBtn1"
                          }
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(CONCUR_APPROVED);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(Concur_1Approval)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Container",
                        "items": [
                            {
                                "type": "TextBlock",
                                "size": "Medium",
                                "weight": "Bolder",
                                "color": "Dark",
                                "text": "1 Pending approval",
                                "wrap": true
                            },
                            {
                                "type": "TextBlock",
                                "text": "Here's the last report pending your approval:",
                                "wrap": true
                            },
                            {
                                "type": "ColumnSet",
                                "horizontalAlignment": "Left",
                                "spacing": "Medium",
                                "columns": [
                                    {
                                        "type": "Column",
                                        "horizontalAlignment": "Left",
                                        "verticalContentAlignment": "Center",
                                        "width": "20px"
                                    },
                                    {
                                        "type": "Column",
                                        "items": [
                                            {
                                                "type": "ColumnSet",
                                                "columns": [
                                                    {
                                                        "type": "Column",
                                                        "items": [
                                                            {
                                                                "type": "TextBlock",
                                                                "height": "stretch",
                                                                "text": "Employee"
                                                            },
                                                            {
                                                                "type": "TextBlock",
                                                                "spacing": "Small",
                                                                "height": "stretch",
                                                                "weight": "Bolder",
                                                                "color": "Dark",
                                                                "text": "Andrew Davis"
                                                            },
                                                            {
                                                                "type": "TextBlock",
                                                                "spacing": "Medium",
                                                                "text": "Report Date"
                                                            },
                                                            {
                                                                "type": "TextBlock",
                                                                "text": "Amount due to employee"
                                                            },
                                                            {
                                                                "type": "TextBlock",
                                                                "text": "Claimed Amount"
                                                            }
                                                        ],
                                                        "width": "auto"
                                                    },
                                                    {
                                                        "type": "Column",
                                                        "items": [
                                                            {
                                                                "type": "TextBlock",
                                                                "height": "stretch",
                                                                "text": "Report Name:"
                                                            },
                                                            {
                                                                "type": "TextBlock",
                                                                "height": "stretch",
                                                                "weight": "Bolder",
                                                                "color": "Dark",
                                                                "text": "Team offsite in Seattle"
                                                            },
                                                            {
                                                                "type": "TextBlock",
                                                                "spacing": "Medium",
                                                                "text": "2019-06-09"
                                                            },
                                                            {
                                                                "type": "TextBlock",
                                                                "text": "$2039.12"
                                                            },
                                                            {
                                                                "type": "TextBlock",
                                                                "text": "$2039.12"
                                                            }
                                                        ],
                                                        "width": "auto"
                                                    }
                                                ]
                                            }
                                        ],
                                        "width": "stretch"
                                    }
                                ]
                            }
                        ]
                    }
                ],
                "actions": [
                    {
                        "type": "Action.Submit",
                        "title": "Approve",
                        "id": "lastApproveBtn",
                    "data": {
                      "buttonId": "lastApproveBtn"
                    }
                    },
                    {
                        "type": "Action.ShowCard",
                        "title": "Send back",
                        "card": {
                            "type": "AdaptiveCard",
                            "style": "emphasis",
                            "body": [
                                {
                                    "type": "Container",
                                    "items": [
                                        {
                                            "type": "ColumnSet",
                                            "horizontalAlignment": "Left",
                                            "columns": [
                                                {
                                                    "type": "Column",
                                                    "items": [
                                                        {
                                                            "type": "TextBlock",
                                                            "text": "Reason:"
                                                        }
                                                    ],
                                                    "width": "auto"
                                                },
                                                {
                                                    "type": "Column",
                                                    "items": [
                                                        {
                                                            "type": "Input.Text",
                                                            "id": "comment",
                                                            "placeholder": "Optional comment",
                                                            "isMultiline": true
                                                        }
                                                    ],
                                                    "width": "stretch"
                                                }
                                            ]
                                        }
                                    ]
                                }
                            ],
                            "actions": [
                                {
                                    "type": "Action.Submit",
                                    "title": "Submit Send Back",
                                    "id": "sendBackBtn",
                          "data": {
                            "buttonId": "sendBackBtn"
                          }
                                }
                            ],
                            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json"
                        }
                    },
                    {
                        "type": "Action.OpenUrl",
                        "title": "View in Concur",
                        "url": "https://www.concur.co.in/"
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(CONCUR_ONE_APPROVAL);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(Concur_2Approval)
		{
			std::string card = R"({
              "type": "AdaptiveCard",
              "body": [
                  {
                      "type": "Container",
                      "items": [
                          {
                              "type": "TextBlock",
                              "size": "Medium",
                              "weight": "Bolder",
                              "color": "Dark",
                              "text": "2 Pending approvals",
                              "wrap": true
                          },
                          {
                              "type": "TextBlock",
                              "text": "Here's the first report pending your approval:",
                              "wrap": true
                          },
                          {
                              "type": "ColumnSet",
                              "horizontalAlignment": "Left",
                              "spacing": "Medium",
                              "columns": [
                                  {
                                      "type": "Column",
                                      "horizontalAlignment": "Left",
                                      "verticalContentAlignment": "Center",
                                      "width": "20px"
                                  },
                                  {
                                      "type": "Column",
                                      "items": [
                                          {
                                              "type": "ColumnSet",
                                              "columns": [
                                                  {
                                                      "type": "Column",
                                                      "items": [
                                                          {
                                                              "type": "TextBlock",
                                                              "height": "stretch",
                                                              "text": "Employee"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "spacing": "Small",
                                                              "height": "stretch",
                                                              "weight": "Bolder",
                                                              "color": "Dark",
                                                              "text": "Jane Jordan"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "spacing": "Medium",
                                                              "text": "Report Date"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "text": "Amount due to employee"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "text": "Claimed Amount"
                                                          }
                                                      ],
                                                      "width": "auto"
                                                  },
                                                  {
                                                      "type": "Column",
                                                      "items": [
                                                          {
                                                              "type": "TextBlock",
                                                              "height": "stretch",
                                                              "text": "Report Name:"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "height": "stretch",
                                                              "weight": "Bolder",
                                                              "color": "Dark",
                                                              "text": "Cisco Live 2019"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "spacing": "Medium",
                                                              "text": "2019-06-09"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "text": "$1981.79"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "text": "$1981.79"
                                                          }
                                                      ],
                                                      "width": "auto"
                                                  }
                                              ]
                                          }
                                      ],
                                      "width": "stretch"
                                  }
                              ]
                          }
                      ]
                  }
              ],
              "actions": [
                  {
                      "type": "Action.Submit",
                      "title": "Approve",
                      "id": "firstApprovalCardBtn",
                  "data": {
                    "buttonId": "firstApprovalCardBtn"
                  }
                  },
                  {
                      "type": "Action.ShowCard",
                      "title": "Send back",
                      "card": {
                          "type": "AdaptiveCard",
                          "style": "emphasis",
                          "body": [
                              {
                                  "type": "Container",
                                  "items": [
                                      {
                                          "type": "ColumnSet",
                                          "horizontalAlignment": "Left",
                                          "columns": [
                                              {
                                                  "type": "Column",
                                                  "items": [
                                                      {
                                                          "type": "TextBlock",
                                                          "text": "Reason:"
                                                      }
                                                  ],
                                                  "width": "auto"
                                              },
                                              {
                                                  "type": "Column",
                                                  "items": [
                                                      {
                                                          "type": "Input.Text",
                                                          "id": "comment",
                                                          "placeholder": "Optional comment",
                                                          "isMultiline": true
                                                      }
                                                  ],
                                                  "width": "stretch"
                                              }
                                          ]
                                      }
                                  ]
                              }
                          ],
                          "actions": [
                              {
                                  "type": "Action.Submit",
                                  "title": "Submit Send Back",
                                  "id": "firstCardSendBackBtn",
                      "data": {
                          "buttonId": "firstCardSendBackBtn"
                      }
                              }
                          ],
                          "$schema": "http://adaptivecards.io/schemas/adaptive-card.json"
                      }
                  },
                  {
                      "type": "Action.OpenUrl",
                      "title": "View in Concur",
                      "url": "https://www.concur.co.in/"
                  }
              ],
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(CONCUR_TWO_APPROVAL);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(Concur_SendBackCard)
		{
			std::string card = R"({
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "TextBlock",
                        "size": "Medium",
                        "weight": "Bolder",
                        "color": "Dark",
                        "text": "Andrew Davis' report was sent back",
                        "wrap": true
                    },
                    {
                        "type": "TextBlock",
                        "spacing": "Medium",
                        "text": "No more pending approvals.",
                        "wrap": true
                    }
                ],
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(CONCUR_SEND_BACK_CARD);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(Concur_2ApprovalOnClick)
		{
			std::string card = R"({
              "type": "AdaptiveCard",
              "body": [
                  {
                      "type": "Container",
                      "items": [
                          {
                              "type": "TextBlock",
                              "size": "Medium",
                              "weight": "Bolder",
                              "color": "Dark",
                              "text": "2 Pending approvals",
                              "wrap": true
                          },
                          {
                              "type": "TextBlock",
                              "text": "Here's the first report pending your approval:",
                              "wrap": true
                          },
                          {
                              "type": "ColumnSet",
                              "horizontalAlignment": "Left",
                              "spacing": "Medium",
                              "columns": [
                                  {
                                      "type": "Column",
                                      "horizontalAlignment": "Left",
                                      "verticalContentAlignment": "Center",
                                      "width": "20px"
                                  },
                                  {
                                      "type": "Column",
                                      "items": [
                                          {
                                              "type": "ColumnSet",
                                              "columns": [
                                                  {
                                                      "type": "Column",
                                                      "items": [
                                                          {
                                                              "type": "TextBlock",
                                                              "height": "stretch",
                                                              "text": "Employee"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "spacing": "Small",
                                                              "height": "stretch",
                                                              "weight": "Bolder",
                                                              "color": "Dark",
                                                              "text": "Jane Jordan"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "spacing": "Medium",
                                                              "text": "Report Date"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "text": "Amount due to employee"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "text": "Claimed Amount"
                                                          }
                                                      ],
                                                      "width": "auto"
                                                  },
                                                  {
                                                      "type": "Column",
                                                      "items": [
                                                          {
                                                              "type": "TextBlock",
                                                              "height": "stretch",
                                                              "text": "Report Name:"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "height": "stretch",
                                                              "weight": "Bolder",
                                                              "color": "Dark",
                                                              "text": "Cisco Live 2019"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "spacing": "Medium",
                                                              "text": "2019-06-09"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "text": "$1981.79"
                                                          },
                                                          {
                                                              "type": "TextBlock",
                                                              "text": "$1981.79"
                                                          }
                                                      ],
                                                      "width": "auto"
                                                  }
                                              ]
                                          }
                                      ],
                                      "width": "stretch"
                                  }
                              ]
                          }
                      ]
                  }
              ],
              "actions": [
                  {
                      "type": "Action.Submit",
                      "title": "Approve",
                      "id": "firstApprovalCardBtn",
                  "data": {
                    "buttonId": "firstApprovalCardBtn"
                  }
                  },
                  {
                      "type": "Action.ShowCard",
                      "title": "Send back",
                      "card": {
                          "type": "AdaptiveCard",
                          "style": "emphasis",
                          "body": [
                              {
                                  "type": "Container",
                                  "items": [
                                      {
                                          "type": "ColumnSet",
                                          "horizontalAlignment": "Left",
                                          "columns": [
                                              {
                                                  "type": "Column",
                                                  "items": [
                                                      {
                                                          "type": "TextBlock",
                                                          "text": "Reason:"
                                                      }
                                                  ],
                                                  "width": "auto"
                                              },
                                              {
                                                  "type": "Column",
                                                  "items": [
                                                      {
                                                          "type": "Input.Text",
                                                          "id": "comment",
                                                          "placeholder": "Optional comment",
                                                          "isMultiline": true
                                                      }
                                                  ],
                                                  "width": "stretch"
                                              }
                                          ]
                                      }
                                  ]
                              }
                          ],
                          "actions": [
                              {
                                  "type": "Action.Submit",
                                  "title": "Submit Send Back",
                                  "id": "firstCardSendBackBtn",
                      "data": {
                          "buttonId": "firstCardSendBackBtn"
                      }
                              }
                          ],
                          "$schema": "http://adaptivecards.io/schemas/adaptive-card.json"
                      }
                  },
                  {
                      "type": "Action.OpenUrl",
                      "title": "View in Concur",
                      "url": "https://www.concur.co.in/"
                  }
              ],
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "version": "1.0"
            })";

			std::string QmlStr = GenerateQml(card);
			std::string expected = getQmlString(CONCUR_TWO_APPROVAL_ON_CLICK);
			expected.erase(std::remove(expected.begin(), expected.end(), '\r'), expected.end());
			Assert::AreEqual<std::string>(QmlStr, expected);
		}

		TEST_METHOD(GetRGBColor)
		{
			std::shared_ptr<AdaptiveCards::HostConfig> hostConfig = std::make_shared<AdaptiveCards::HostConfig>();
			AdaptiveRenderContext context = AdaptiveRenderContext(hostConfig, nullptr);
			Assert::IsTrue(context.GetRGBColor("#ffffffff") == "Qt.rgba(255, 255, 255, 1.00)");
			Assert::IsTrue(context.GetRGBColor("#7ffefdfc") == "Qt.rgba(254, 253, 252, 0.50)");
			Assert::IsTrue(context.GetRGBColor("red") == "'red'");
			Assert::IsTrue(context.GetRGBColor("#red") == "'#red'");
			Assert::IsTrue(context.GetRGBColor("#ninechar") == "'#ninechar'");
			Assert::IsTrue(context.GetRGBColor("#1f2x3y4f") == "'#1f2x3y4f'");
			Assert::IsTrue(context.GetRGBColor("var(--themeColor)") == "'var(--themeColor)'");
			Assert::IsTrue(context.GetRGBColor("var ( --themeColor ) ") == "'var ( --themeColor ) '");
			Assert::IsTrue(context.GetRGBColor("var(--themeColor, blue)") == "'var(--themeColor, blue)'");
		}

		TEST_METHOD(TryParseDouble)
		{
			double d;
			Assert::IsTrue(Utils::TryParse("1.1", d) && (d == 1.1));
			Assert::IsFalse(Utils::TryParse("", d));
			Assert::IsFalse(Utils::TryParse("xyz", d));
			Assert::IsFalse(Utils::TryParse("1.1px", d));
			Assert::IsTrue(Utils::TryParse("10", d) && (d == 10));
			Assert::IsTrue(Utils::TryParse("0", d) && (d == 0));
		}

		TEST_METHOD(ApplyTextFunctions)
		{
			//Set TZ to +530

			//Timezone translation
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{TIME(2017-02-14T02:08:39+08:30)}}", "en") == "Created 11:08 PM");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{TIME(2017-02-14T18:08:39-08:30)}}", "en") == "Created 08:08 AM");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{TIME(2017-02-14T06:08:39+06:00)}}", "en") == "Created 05:38 AM");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{TIME(2017-02-14T06:08:39-01:00)}}", "en") == "Created 12:38 PM");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{TIME(2017-02-14T06:08:39Z)}}", "en") == "Created 11:38 AM");

			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T02:08:39+08:30, SHORT)}}", "en") == "Created Mon, Feb 13, 2017");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T18:08:39-08:30, SHORT)}}", "en") == "Created Wed, Feb 15, 2017");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39+06:00, SHORT)}}", "en") == "Created Tue, Feb 14, 2017");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39-01:00, SHORT)}}", "en") == "Created Tue, Feb 14, 2017");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39Z, SHORT)}}", "en") == "Created Tue, Feb 14, 2017");

			// Multiple matches in text
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39Z, SHORT)}} Updated {{DATE(2018-03-15T07:09:35Z, SHORT)}}", "en") == "Created Tue, Feb 14, 2017 Updated Thu, Mar 15, 2018");

			// Formats
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39Z, SHORT)}}", "fr") == "Created Tue, Feb 14, 2017");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39Z, SHORT)}}", "en") == "Created Tue, Feb 14, 2017");

			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39Z, LONG)}}", "fr") == "Created Tuesday, February 14, 2017");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39Z, LONG)}}", "en") == "Created Tuesday, February 14, 2017");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39Z, COMPACT)}}", "") == "Created 2/14/2017");

			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39Z, COMPACT)}}", "fr") == "Created 2/14/2017");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{TIME(2017-02-14T06:08:39+06:00)}}", "fr") == "Created 05:38 AM");

			Assert::IsTrue(TextUtils::ApplyTextFunctions("Hello World", "") == "Hello World");

			//Invalids
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39+05:60, SHORT)}}", "en") == "Created {{DATE(2017-02-14T06:08:39+05:60, SHORT)}}");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{TIME(2017-02-14T06:08:39+05:60)}}", "en") == "Created {{TIME(2017-02-14T06:08:39+05:60)}}");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{TIME(2017-02-14T06:08:39+05:30, SHORT)}}", "en") == "Created {{TIME(2017-02-14T06:08:39+05:30, SHORT)}}");
			Assert::IsTrue(TextUtils::ApplyTextFunctions("Created {{DATE(2017-02-14T06:08:39Z+530 abc, SHORT)}}", "en") == "Created {{DATE(2017-02-14T06:08:39Z+530 abc, SHORT)}}");

		}
	};
}
