// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;

// Sample Test App for AdaptiveCards.Template project which is a C#/WinRT component
int main()
{
    init_apartment();

    hstring input{
        L"{\"type\": \"AdaptiveCard\",\"body\": [{\"type\": \"TextBlock\",\"text\": \"Hello, ${hi}!\"}]}"};

    AdaptiveCards::Template::AdaptiveCardTemplate adaptiveCardTemplate{ input };

	constexpr auto hostConfigJson_dark =
		LR"({
	  "spacing": {
		"small": 4,
		"default": 8,
		"medium": 20,
		"large": 30,
		"extraLarge": 40,
		"padding": 8
	  },
	  "separator": {
		"lineThickness": 0,
		"lineColor": "#C8FFFFFF"
	  },
	  "supportsInteractivity": true,
	  "fontTypes": {
		"default": {
		  "fontFamily": "'Segoe UI', 'Roboto', 'Oxygen', 'Ubuntu', 'Cantarell', 'Fira Sans', 'Droid Sans', 'Helvetica Neue', sans-serif",
		  "fontSizes": {
			"small": 12,
			"default": 12,
			"medium": 14,
			"large": 20,
			"extraLarge": 26
		  },
		  "fontWeights": {
			"lighter": 200,
			"default": 400,
			"bolder": 600
		  }
		},
		"monospace": {
		  "fontFamily": "'Courier New', Courier, monospace",
		  "fontSizes": {
			"small": 12,
			"default": 12,
			"medium": 14,
			"large": 18,
			"extraLarge": 26
		  },
		  "fontWeights": {
			"lighter": 200,
			"default": 400,
			"bolder": 600
		  }
		}
	  },
	  "containerStyles": {
		"default": {
		  "backgroundColor": "#00000000",
		  "borderColor": "#00000000",
		  "foregroundColors": {
			"default": {
			  "default": "#FFFFFF",
			  "subtle": "#C8FFFFFF"
			},
			"accent": {
			  "default": "#0063B1",
			  "subtle": "#880063B1"
			},
			"attention": {
			  "default": "#FF0000",
			  "subtle": "#DDFF0000"
			},
			"good": {
			  "default": "#54a254",
			  "subtle": "#DD54a254"
			},
			"warning": {
			  "default": "#c3ab23",
			  "subtle": "#DDc3ab23"
			}
		  }
		},
		"emphasis": {
		  "backgroundColor": "#09FFFFFF",
		  "borderColor": "#09FFFFFF",
		  "foregroundColors": {
			"default": {
			  "default": "#FFFFFF",
			  "subtle": "#C8FFFFFF"
			},
			"accent": {
			  "default": "#2E89FC",
			  "subtle": "#882E89FC"
			},
			"attention": {
			  "default": "#FF0000",
			  "subtle": "#DDFF0000"
			},
			"good": {
			  "default": "#54a254",
			  "subtle": "#DD54a254"
			},
			"warning": {
			  "default": "#c3ab23",
			  "subtle": "#DDc3ab23"
			}
		  }
		}
	  },
	  "imageSizes": {
		"small": 24,
		"medium": 36,
		"large": 48
	  },
	  "actions": {
		"maxActions": 5,
		"spacing": "default",
		"buttonSpacing": 8,
		"showCard": {
		  "actionMode": "inline",
		  "inlineTopMargin": 8
		},
		"actionsOrientation": "horizontal",
		"actionAlignment": "stretch"
	  },
	  "adaptiveCard": {
		"allowCustomStyle": false
	  },
	  "imageSet": {
		"imageSize": "medium",
		"maxImageHeight": 100
	  },
	  "factSet": {
		"title": {
		  "color": "default",
		  "size": "default",
		  "isSubtle": false,
		  "weight": "bolder",
		  "wrap": true,
		  "maxWidth": 150
		},
		"value": {
		  "color": "default",
		  "size": "default",
		  "isSubtle": false,
		  "weight": "default",
		  "wrap": true
		},
		"spacing": 8
	  },
	  "textStyles": {
		"heading": {
		  "size": "large",
		  "weight": "bolder",
		  "color": "default",
		  "isSubtle": false,
		  "fontType": "default"
		},
		"columnHeader": {
		  "size": "medium",
		  "weight": "bolder",
		  "color": "default",
		  "isSubtle": false,
		  "fontType": "default"
		}
	  }
	})";

    hstring data{ L"{\"hi\": \"world\"}" };

    auto result = adaptiveCardTemplate.Expand(data, hostConfigJson_dark);

    std::cout << "Expanded: " << to_string(result) << std::endl;

    return 0;
};
