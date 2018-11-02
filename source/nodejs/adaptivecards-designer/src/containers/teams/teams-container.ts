import * as Adaptive from "adaptivecards";
import * as Designer from "../../adaptivecards-designer";

export abstract class BaseTeamsContainer extends Designer.HostContainer {
    public renderTo(hostElement: HTMLElement) {
        var outerFrame = document.createElement("div");
        outerFrame.className = "teams-frame";

        // Draw the hexagon bot logo
        var hexagonOuter = document.createElement("div");
        hexagonOuter.className = "teams-hexagon-outer";

        var hexagonInner = document.createElement("div");
        hexagonInner.className = "teams-hexagon-inner";

        var botLogo = document.createElement("div");
        botLogo.className = "teams-bot-logo";

        hexagonOuter.appendChild(hexagonInner);
        hexagonInner.appendChild(botLogo);

        outerFrame.appendChild(hexagonOuter);

        let innerFrame = document.createElement("div");
        innerFrame.className = "teams-inner-frame";

        this.cardHost.classList.add("teams-card");

        let botNameAndTime = document.createElement("div");
        botNameAndTime.className = "teams-botNameAndTime";
        botNameAndTime.innerText = "Test Bot    2:36 PM";

        innerFrame.appendChild(botNameAndTime);
        innerFrame.appendChild(this.cardHost);

        outerFrame.appendChild(innerFrame);

        hostElement.appendChild(outerFrame);
    }
}

export class LightTeamsContainer extends BaseTeamsContainer {
    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(
            {
                "choiceSetInputValueSeparator": ",",
                "supportsInteractivity": true,
                "fontFamily": "Segoe UI",
                "spacing": {
                    "small": 8,
                    "default": 12,
                    "medium": 16,
                    "large": 20,
                    "extraLarge": 24,
                    "padding": 16
                },
                "separator": {
                    "lineThickness": 1,
                    "lineColor": "#EEEEEE"
                },
                "fontSizes": {
                    "small": 12,
                    "default": 14,
                    "medium": 14,
                    "large": 18,
                    "extraLarge": 24
                },
                "fontWeights": {
                    "lighter": 300,
                    "default": 400,
                    "bolder": 600
                },
                "imageSizes": {
                    "small": 32,
                    "medium": 52,
                    "large": 100
                },
                "containerStyles": {
                    "default": {
                        "foregroundColors": {
                            "default": {
                                "default": "#ff252424",
                                "subtle": "#bf252424"
                            },
                            "dark": {
                                "default": "#252424",
                                "subtle": "#bf252424"
                            },
                            "light": {
                                "default": "#ffffff",
                                "subtle": "#fff3f2f1"
                            },
                            "accent": {
                                "default": "#6264a7",
                                "subtle": "#8b8cc7"
                            },
                            "good": {
                                "default": "#92c353",
                                "subtle": "#e592c353"
                            },
                            "warning": {
                                "default": "#f8d22a",
                                "subtle": "#e5f8d22a"
                            },
                            "attention": {
                                "default": "#c4314b",
                                "subtle": "#e5c4314b"
                            }
                        },
                        "backgroundColor": "#ffffff"
                    },
                    "emphasis": {
                        "foregroundColors": {
                            "default": {
                                "default": "#ff252424",
                                "subtle": "#bf252424"
                            },
                            "dark": {
                                "default": "#252424",
                                "subtle": "#bf252424"
                            },
                            "light": {
                                "default": "#ffffff",
                                "subtle": "#fff3f2f1"
                            },
                            "accent": {
                                "default": "#6264a7",
                                "subtle": "#8b8cc7"
                            },
                            "good": {
                                "default": "#92c353",
                                "subtle": "#e592c353"
                            },
                            "warning": {
                                "default": "#f8d22a",
                                "subtle": "#e5f8d22a"
                            },
                            "attention": {
                                "default": "#c4314b",
                                "subtle": "#e5c4314b"
                            }
                        },
                        "backgroundColor": "#fff9f8f7"
                    }
                },
                "actions": {
                    "maxActions": 6,
                    "spacing": "Default",
                    "buttonSpacing": 8,
                    "showCard": {
                        "actionMode": "Inline",
                        "inlineTopMargin": 16,
                        "style": "emphasis"
                    },
                    "preExpandSingleShowCardAction": false,
                    "actionsOrientation": "Horizontal",
                    "actionAlignment": "Left"
                },
                "adaptiveCard": {
                    "allowCustomStyle": false
                },
                "imageSet": {
                    "imageSize": "Medium",
                    "maxImageHeight": 100
                },
                "factSet": {
                    "title": {
                        "size": "Default",
                        "color": "Default",
                        "isSubtle": false,
                        "weight": "Bolder",
                        "warp": true
                    },
                    "value": {
                        "size": "Default",
                        "color": "Default",
                        "isSubtle": false,
                        "weight": "Default",
                        "warp": true
                    },
                    "spacing": 16
                }
            }
        );
    }
}


export class DarkTeamsContainer extends BaseTeamsContainer {
    public getBackgroundColor(): string {
        return "#201E1F";
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(
            {
                "choiceSetInputValueSeparator": ",",
                "supportsInteractivity": true,
                "fontFamily": "Segoe UI",
                "spacing": {
                    "small": 8,
                    "default": 12,
                    "medium": 16,
                    "large": 20,
                    "extraLarge": 24,
                    "padding": 16
                },
                "separator": {
                    "lineThickness": 1,
                    "lineColor": "#EEEEEE"
                },
                "fontSizes": {
                    "small": 12,
                    "default": 14,
                    "medium": 14,
                    "large": 18,
                    "extraLarge": 24
                },
                "fontWeights": {
                    "lighter": 300,
                    "default": 400,
                    "bolder": 600
                },
                "imageSizes": {
                    "small": 32,
                    "medium": 52,
                    "large": 100
                },
                "containerStyles": {
                    "default": {
                        "foregroundColors": {
                            "default": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "dark": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "light": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "accent": {
                                "default": "#ffa6a7dc",
                                "subtle": "#ff8b8cc7"
                            },
                            "good": {
                                "default": "#ff92c353",
                                "subtle": "#e592c353"
                            },
                            "warning": {
                                "default": "#fff8d22a",
                                "subtle": "#e5f8d22a"
                            },
                            "attention": {
                                "default": "#ffd74654",
                                "subtle": "#e5d74654"
                            }
                        },
                        "backgroundColor": "#ff2d2c2c"
                    },
                    "emphasis": {
                        "foregroundColors": {
                            "default": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "dark": {
                                "default": "#ffffffff",
                                "subtle": "#bfffffff"
                            },
                            "light": {
                                "default": "#ff201f1f",
                                "subtle": "#ff2d2c2c"
                            },
                            "accent": {
                                "default": "#ffa6a7dc",
                                "subtle": "#ff8b8cc7"
                            },
                            "good": {
                                "default": "#ff92c353",
                                "subtle": "#e592c353"
                            },
                            "warning": {
                                "default": "#fff8d22a",
                                "subtle": "#e5f8d22a"
                            },
                            "attention": {
                                "default": "#ffd74654",
                                "subtle": "#e5d74654"
                            }
                        },
                        "backgroundColor": "#ff292828"
                    }
                },
                "actions": {
                    "maxActions": 6,
                    "spacing": "Default",
                    "buttonSpacing": 8,
                    "showCard": {
                        "actionMode": "Inline",
                        "inlineTopMargin": 16,
                        "style": "emphasis"
                    },
                    "preExpandSingleShowCardAction": false,
                    "actionsOrientation": "Horizontal",
                    "actionAlignment": "Left"
                },
                "adaptiveCard": {
                    "allowCustomStyle": false
                },
                "imageSet": {
                    "imageSize": "Medium",
                    "maxImageHeight": 100
                },
                "factSet": {
                    "title": {
                        "size": "Default",
                        "color": "Default",
                        "isSubtle": false,
                        "weight": "Bolder",
                        "warp": true
                    },
                    "value": {
                        "size": "Default",
                        "color": "Default",
                        "isSubtle": false,
                        "weight": "Default",
                        "warp": true
                    },
                    "spacing": 16
                }
            }
        );
    }
}
