// Copyright (C) Microsoft Corporation. All rights reserved.
import * as AC from 'adaptivecards';

const sampleHostConfig = new AC.HostConfig({
    "spacing": {
        "small": 3,
        "default": 8,
        "medium": 20,
        "large": 30,
        "extraLarge": 40,
        "padding": 10
    },
    "separator": {
        "lineThickness": 1,
        "lineColor": "#EEEEEE"
    },
    "supportsInteractivity": true,
    "fontTypes": {
        "default": {
            "fontFamily": "'Lucida Sans', serif",
            "fontSizes": {
                "small": 12,
                "default": 14,
                "medium": 17,
                "large": 21,
                "extraLarge": 26
            },
            "fontWeights": {
                "lighter": 200,
                "default": 400,
                "bolder": 600
            }
        },
        "monospace": {
            "fontFamily": "Consolas, 'Lucida Console', 'Courier New', Courier, monospace",
            "fontSizes": {
                "small": 12,
                "default": 14,
                "medium": 17,
                "large": 21,
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
            "backgroundColor": "#444471",
            "foregroundColors": {
                "default": {
                    "default": "#EAEAF2",
                    "subtle": "#C2C2DA"
                },
                "accent": {
                    "default": "#F4FF20",
                    "subtle": "#A4CECE"
                },
                "attention": {
                    "default": "#FF5959",
                    "subtle": "#C80000"
                },
                "good": {
                    "default": "#1FFE2B",
                    "subtle": "#00D80C"
                },
                "light": {
                    "default": "#FFF",
                    "subtle": "#DDD"
                },
                "warning": {
                    "default": "#EF8C05",
                    "subtle": "#DE8205"
                }
            }
        },
        "emphasis": {
            "backgroundColor": "#7474AB",
            "foregroundColors": {
                "default": {
                    "default": "#E2E2ED",
                    "subtle": "#6f6f6f"
                },
                "accent": {
                    "default": "#EBFC1B",
                    "subtle": "#881F6BF1"
                },
                "attention": {
                    "default": "#E31B13",
                    "subtle": "#DDE31B13"
                },
                "good": {
                    "default": "#7FFF00",
                    "subtle": "#DD0D860A"
                },
                "warning": {
                    "default": "#FF0C0C",
                    "subtle": "#DDBD5400"
                },
                "light": {
                    "default": "#C3C3C3",
                    "subtle": "#DD737373"
                }
            }
        },
        "accent": {
            "backgroundColor": "#D7E7FA",
            "foregroundColors": {
                "default": {
                    "default": "#333333",
                    "subtle": "#EE333333"
                },
                "dark": {
                    "default": "#000000",
                    "subtle": "#66000000"
                },
                "light": {
                    "default": "#646464",
                    "subtle": "#33646464"
                },
                "accent": {
                    "default": "#145FDD",
                    "subtle": "#88145FDD"
                },
                "attention": {
                    "default": "#C42C07",
                    "subtle": "#DDC42C07"
                },
                "good": {
                    "default": "#0B7814",
                    "subtle": "#DD0B7814"
                },
                "warning": {
                    "default": "#935A10",
                    "subtle": "#DD935A10"
                }
            }
        },
        "good": {
            "backgroundColor": "#CCFFCC",
            "foregroundColors": {
                "default": {
                    "default": "#333333",
                    "subtle": "#EE333333"
                },
                "dark": {
                    "default": "#000000",
                    "subtle": "#66000000"
                },
                "light": {
                    "default": "#6E6E6E",
                    "subtle": "#336E6E6E"
                },
                "accent": {
                    "default": "#2168E4",
                    "subtle": "#882168E4"
                },
                "attention": {
                    "default": "#CC3300",
                    "subtle": "#DDCC3300"
                },
                "good": {
                    "default": "#0F8109",
                    "subtle": "#DD0F8109"
                },
                "warning": {
                    "default": "#9A630D",
                    "subtle": "#DD9A630D"
                }
            }
        },
        "attention": {
            "backgroundColor": "#FFC5B2",
            "foregroundColors": {
                "default": {
                    "default": "#333333",
                    "subtle": "#EE333333"
                },
                "dark": {
                    "default": "#000000",
                    "subtle": "#66000000"
                },
                "light": {
                    "default": "#5A5A5A",
                    "subtle": "#335A5A5A"
                },
                "accent": {
                    "default": "#0854C5",
                    "subtle": "#880854C5"
                },
                "attention": {
                    "default": "#A92E0E",
                    "subtle": "#DDA92E0E"
                },
                "good": {
                    "default": "#256824",
                    "subtle": "#DD256824"
                },
                "warning": {
                    "default": "#775502",
                    "subtle": "#DD775502"
                }
            }
        },
        "warning": {
            "backgroundColor": "#FFE2B2",
            "foregroundColors": {
                "default": {
                    "default": "#333333",
                    "subtle": "#EE333333"
                },
                "dark": {
                    "default": "#000000",
                    "subtle": "#66000000"
                },
                "light": {
                    "default": "#646464",
                    "subtle": "#33646464"
                },
                "accent": {
                    "default": "#0F60DC",
                    "subtle": "#880F60DC"
                },
                "attention": {
                    "default": "#BF3505",
                    "subtle": "#DDBF3505"
                },
                "good": {
                    "default": "#207725",
                    "subtle": "#DD207725"
                },
                "warning": {
                    "default": "#866107",
                    "subtle": "#DD866107"
                }
            }
        }
    },
    "imageSizes": {
        "small": 60,
        "medium": 100,
        "large": 200
    },
    "actions": {
        "maxActions": 100,
        "spacing": "default",
        "buttonSpacing": 8,
        "showCard": {
            "actionMode": "inline",
            "inlineTopMargin": 8
        },
        "actionsOrientation": "horizontal",
        "actionAlignment": "left"
    },
    "adaptiveCard": {
        "allowCustomStyle": false
    },
    "imageSet": {
        "imageSize": "medium",
        "maxImageHeight": 200
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
    }
});

export { sampleHostConfig };
