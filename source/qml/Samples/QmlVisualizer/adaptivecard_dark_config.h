#pragma once
#include "stdafx.h"

namespace DarkConfig
{
const std::string darkConfig = R"({
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
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "dark": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "light": {
                    "default": "#B2FFFFFF",
                    "subtle": "#99FFFFFF"
                },
                "accent": {
                    "default": "#64B4FA",
                    "subtle": "#96D0FF"
                },
                "good": {
                    "default": "#3CC29A",
                    "subtle": "#68DEBD"
                },
                "warning": {
                    "default": "#F2990A",
                    "subtle": "#FFBE4F"
                },
                "attention": {
                    "default": "#FC8B98",
                    "subtle": "#FFB8C1"
                }
            },
            "backgroundColor": "#1A1A1A"
        },
        "emphasis": {
            "foregroundColors": {
                "default": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "dark": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "light": {
                    "default": "#B2FFFFFF",
                    "subtle": "#99FFFFFF"
                },
                "accent": {
                    "default": "#64B4FA",
                    "subtle": "#96D0FF"
                },
                "good": {
                    "default": "#3CC29A",
                    "subtle": "#68DEBD"
                },
                "warning": {
                    "default": "#F2990A",
                    "subtle": "#FFBE4F"
                },
                "attention": {
                    "default": "#FC8B98",
                    "subtle": "#FFB8C1"
                }
            },
            "backgroundColor": "#3B3B3B"
        },
        "good": {
            "foregroundColors": {
                "default": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "dark": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "light": {
                    "default": "#B2FFFFFF",
                    "subtle": "#99FFFFFF"
                },
                "accent": {
                    "default": "#64B4FA",
                    "subtle": "#96D0FF"
                },
                "good": {
                    "default": "#3CC29A",
                    "subtle": "#68DEBD"
                },
                "warning": {
                    "default": "#F2990A",
                    "subtle": "#FFBE4F"
                },
                "attention": {
                    "default": "#FC8B98",
                    "subtle": "#FFB8C1"
                }
            },
            "backgroundColor": "#134231"
        },
        "accent": {
            "foregroundColors": {
                "default": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "dark": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "light": {
                    "default": "#B2FFFFFF",
                    "subtle": "#99FFFFFF"
                },
                "accent": {
                    "default": "#64B4FA",
                    "subtle": "#96D0FF"
                },
                "good": {
                    "default": "#3CC29A",
                    "subtle": "#68DEBD"
                },
                "warning": {
                    "default": "#F2990A",
                    "subtle": "#FFBE4F"
                },
                "attention": {
                    "default": "#FC8B98",
                    "subtle": "#FFB8C1"
                }
            },
            "backgroundColor": "#063A75"
        },
        "warning": {
            "foregroundColors": {
                "default": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "dark": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "light": {
                    "default": "#B2FFFFFF",
                    "subtle": "#99FFFFFF"
                },
                "accent": {
                    "default": "#64B4FA",
                    "subtle": "#96D0FF"
                },
                "good": {
                    "default": "#3CC29A",
                    "subtle": "#68DEBD"
                },
                "warning": {
                    "default": "#F2990A",
                    "subtle": "#FFBE4F"
                },
                "attention": {
                    "default": "#FC8B98",
                    "subtle": "#FFB8C1"
                }
            },
            "backgroundColor": "#57330A"
        },
        "attention": {
            "foregroundColors": {
                "default": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "dark": {
                    "default": "#F2FFFFFF",
                    "subtle": "#B2FFFFFF"
                },
                "light": {
                    "default": "#B2FFFFFF",
                    "subtle": "#99FFFFFF"
                },
                "accent": {
                    "default": "#64B4FA",
                    "subtle": "#96D0FF"
                },
                "good": {
                    "default": "#3CC29A",
                    "subtle": "#68DEBD"
                },
                "warning": {
                    "default": "#F2990A",
                    "subtle": "#FFBE4F"
                },
                "attention": {
                    "default": "#FC8B98",
                    "subtle": "#FFB8C1"
                }
            },
            "backgroundColor": "#780D13"
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
