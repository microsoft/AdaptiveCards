#pragma once
#include "stdafx.h"

namespace LightConfig
{
    const std::string lightConfig = R"({
    "hostCapabilities": {
        "capabilities": null
    },
    "choiceSetInputValueSeparator": ",",
    "supportsInteractivity": true,
    "fontFamily": "Segoe UI",
    "fontTypes":{
        "default":{
            "fontFamily": "Segoe UI",
            "fontSizes":{
                "small": 12,
                "default": 14,
                "medium": 16,
                "large": 20,
                "extraLarge": 24
            },
            "fontWeights":{
                "lighter":300,
                "default":400,
                "bolder":600
            }
        },
        "monospace":{
            "fontFamily":"Courier New, Courier, monospace",
            "fontSizes":{
                "small": 12,
                "default": 14,
                "medium": 16,
                "large": 20,
                "extraLarge": 24
            },
            "fontWeights":{
                "lighter":300,
                "default":400,
                "bolder":600
            }
        }
    },
    "spacing": {
        "small": 4,
        "default": 12,
        "medium": 12,
        "large": 12,
        "extraLarge": 16,
        "padding": 12
    },
    "separator": {
        "lineThickness": 1,
        "lineColor": "#EEEEEE"
    },
    "fontSizes":{
        "small": 12,
        "default": 14,
        "medium": 16,
        "large": 20,
        "extraLarge": 24
    },
    "fontWeights": {
        "lighter": 300,
        "default": 400,
        "bolder": 600
    },
    "imageSizes": {
        "small": 40,
        "medium": 80,
        "large": 160
    },
    "containerStyles": {
        "default": {
            "foregroundColors": {
                "default": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "dark": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "light": {
                    "default": "#99000000",
                    "subtle": "#80000000"
                },
                "accent": {
                    "default": "#0352A6",
                    "subtle": "#1170CF"
                },
                "good": {
                    "default": "#185E46",
                    "subtle": "#1D805F"
                },
                "warning": {
                    "default": "#7D4705",
                    "subtle": "#A85F00"
                },
                "attention": {
                    "default": "#AB0A15",
                    "subtle": "#DB1F2E"
                }
            },
            "backgroundColor": "#FFFFFF"
        },
        "emphasis": {
            "foregroundColors": {
                "default": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "dark": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "light": {
                    "default": "#99000000",
                    "subtle": "#80000000"
                },
                "accent": {
                    "default": "#0352A6",
                    "subtle": "#1170CF"
                },
                "good": {
                    "default": "#185E46",
                    "subtle": "#1D805F"
                },
                "warning": {
                    "default": "#7D4705",
                    "subtle": "#A85F00"
                },
                "attention": {
                    "default": "#AB0A15",
                    "subtle": "#DB1F2E"
                }
            },
            "backgroundColor": "#EDEDED"
        },
        "good": {
            "foregroundColors": {
                "default": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "dark": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "light": {
                    "default": "#99000000",
                    "subtle": "#80000000"
                },
                "accent": {
                    "default": "#0352A6",
                    "subtle": "#1170CF"
                },
                "good": {
                    "default": "#185E46",
                    "subtle": "#1D805F"
                },
                "warning": {
                    "default": "#7D4705",
                    "subtle": "#A85F00"
                },
                "attention": {
                    "default": "#AB0A15",
                    "subtle": "#DB1F2E"
                }
            },
            "backgroundColor": "#CEF5EB"
        },
        "accent": {
            "foregroundColors": {
                "default": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "dark": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "light": {
                    "default": "#99000000",
                    "subtle": "#80000000"
                },
                "accent": {
                    "default": "#0352A6",
                    "subtle": "#1170CF"
                },
                "good": {
                    "default": "#185E46",
                    "subtle": "#1D805F"
                },
                "warning": {
                    "default": "#7D4705",
                    "subtle": "#A85F00"
                },
                "attention": {
                    "default": "#AB0A15",
                    "subtle": "#DB1F2E"
                }
            },
            "backgroundColor": "#DBF0FF"
        },
        "warning": {
            "foregroundColors": {
                "default": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "dark": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "light": {
                    "default": "#99000000",
                    "subtle": "#80000000"
                },
                "accent": {
                    "default": "#0352A6",
                    "subtle": "#1170CF"
                },
                "good": {
                    "default": "#185E46",
                    "subtle": "#1D805F"
                },
                "warning": {
                    "default": "#7D4705",
                    "subtle": "#A85F00"
                },
                "attention": {
                    "default": "#AB0A15",
                    "subtle": "#DB1F2E"
                }
            },
            "backgroundColor": "#FFEBC2"
        },
        "attention": {
            "foregroundColors": {
                "default": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "dark": {
                    "default": "#F2000000",
                    "subtle": "#99000000"
                },
                "light": {
                    "default": "#99000000",
                    "subtle": "#80000000"
                },
                "accent": {
                    "default": "#0352A6",
                    "subtle": "#1170CF"
                },
                "good": {
                    "default": "#185E46",
                    "subtle": "#1D805F"
                },
                "warning": {
                    "default": "#7D4705",
                    "subtle": "#A85F00"
                },
                "attention": {
                    "default": "#AB0A15",
                    "subtle": "#DB1F2E"
                }
            },
            "backgroundColor": "#FFE8EA"
        }
    },
    "actions": {
        "maxActions": 5,
        "buttonSpacing": 8,
        "showCard": {
            "actionMode": "Inline",
            "inlineTopMargin": 8,
            "style": "emphasis"
        },
        "style": "emphasis",
        "preExpandSingleShowCardAction": false,
        "actionsOrientation": "Horizontal",
        "actionAlignment": "Left",
        "iconPlacement": "leftOfTitle"
    },
    "adaptiveCard": {
        "allowCustomStyle": false
    },
    "imageSet": {
        "maxImageHeight": 100
    },
    "media": {
        "allowInlinePlayback": false
    },
    "factSet": {
        "title": {
            "size": "Default",
            "color": "Default",
            "isSubtle": false,
            "weight": "Bolder",
            "wrap": true
        },
        "value": {
            "size": "Default",
            "color": "Default",
            "isSubtle": false,
            "weight": "Default",
            "wrap": true
        },
        "spacing": 10
    },
    "cssClassNamePrefix": null
})";
}
