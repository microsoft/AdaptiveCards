import { HostContainer} from "./host-container";
import {
    IHostConfig,
    Size,
    TextSize,
    TextColor,
    TextWeight,
    Spacing,
    ShowCardActionMode,
    Orientation,
    ActionAlignment
} from "microsoft-adaptivecards";

export class ToastContainer extends HostContainer {
    private _width: number;

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.style.border = "#474747 1px solid";
        element.style.width = this._width + "px";
        element.style.overflow = "hidden";

        element.appendChild(renderedCard);

        return element;
    }

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
    }

    public getHostConfig(): IHostConfig {
        return {
            spacing: {
                small: 3,
                default: 8,
                medium: 20,
                large: 30,
                extraLarge: 40,
                padding: 10
            },
            separator: {
                lineThickness: 1,
                lineColor: "#EEEEEE"        
            },
            supportsInteractivity: true,
            fontFamily: "Segoe UI",
            fontSizes: {
                small: 12,
                normal: 14,
                medium: 17,
                large: 21,
                extraLarge: 26
            },
            fontWeights: {
                lighter: 200,
                normal: 400,
                bolder: 600
            },
            containerStyles: {
                default: {
                    backgroundColor: "#1F1F1F",
                    fontColors: {
                        default: {
                            normal: "#FFFFFF",
                            subtle: "#88FFFFFF"
                        },
                        accent: {
                            normal: "#2E89FC",
                            subtle: "#882E89FC" 
                        },
                        attention: {
                            normal: "#FFD800",
                            subtle: "#DDFFD800"
                        },
                        good: {
                            normal: "#00FF00",
                            subtle: "#DD00FF00"
                        },
                        warning: {
                            normal: "#FF0000",
                            subtle: "#DDFF0000"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#19FFFFFF",
                    fontColors: {
                        default: {
                            normal: "#FFFFFF",
                            subtle: "#88FFFFFF"
                        },
                        accent: {
                            normal: "#2E89FC",
                            subtle: "#882E89FC" 
                        },
                        attention: {
                            normal: "#FFD800",
                            subtle: "#DDFFD800"
                        },
                        good: {
                            normal: "#00FF00",
                            subtle: "#DD00FF00"
                        },
                        warning: {
                            normal: "#FF0000",
                            subtle: "#DDFF0000"
                        }
                    }
                }
            },
            imageSizes: {
                small: 40,
                medium: 80,
                large: 160
            },
            actions: {
                maxActions: 5,
                spacing: Spacing.Default,
                buttonSpacing: 10,
                showCard: {
                     actionMode:ShowCardActionMode.InlineEdgeToEdge,
                    inlineTopMargin: 16
                },
                actionsOrientation: Orientation.Horizontal,
                actionAlignment: ActionAlignment.Stretch
            },
            adaptiveCard: {
                allowCustomStyle: false
            },
            image: {
                size: Size.Medium,
            },
            imageSet: {
                imageSize: Size.Medium,
                maxImageHeight: 100
            },
            factSet: {
                title: {
                    color: TextColor.Default,
                    size: TextSize.Normal,
                    isSubtle: false,
                    weight: TextWeight.Bolder,
                    wrap: true,
                    maxWidth: 150,
                },
                value: {
                    color: TextColor.Default,
                    size: TextSize.Normal,
                    isSubtle: false,
                    weight: TextWeight.Normal,
                    wrap: true,
                },
                spacing: 10
            }
        };
    }
}