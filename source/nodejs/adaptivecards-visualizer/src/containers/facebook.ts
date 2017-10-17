import { HostContainer } from "./host-container";
import {
    AdaptiveCard,
    HostConfig,
    Size,
    TextSize,
    TextColor,
    TextWeight,
    Spacing,
    ShowCardActionMode,
    Orientation,
    ActionAlignment,
    FactTitleDefinition,
    FactTextDefinition
} from "adaptivecards";

export class FacebookContainer extends HostContainer {
    private _width: number;

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
        this.supportsActionBar = false;
    }

    protected renderContainer(adaptiveCard: AdaptiveCard, target: HTMLElement) {
        var outerElement = document.createElement("div");
        outerElement.className = "facebookOuterContainer";
        outerElement.style.width = this._width + "px";
        target.appendChild(outerElement);
        adaptiveCard.render(outerElement);
    }

    public getHostConfig(): HostConfig {
        return new HostConfig({
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
            supportsInteractivity: false,
            fontFamily: "Calibri, Candara, Segoe, 'Segoe UI', Optima, Arial, sans-serif;",
            fontSizes: {
                small: 12,
                default: 14,
                medium: 16,
                large: 19,
                extraLarge: 22
            },
            fontWeights: {
                lighter: 200,
                default: 400,
                bolder: 600
            },
            containerStyles: {
                default: {
                    backgroundColor: "#FFF5F5F5",
                    fontColors: {
                        default: {
                            normal: "#FF101010",
                            subtle: "#b2101010"
                        },
                        accent: {
                            normal: "#FF0000FF",
                            subtle: "#b20000FF"
                        },
                        good: {
                            normal: "#FF008000",
                            subtle: "#b2008000"
                        },
                        warning: {
                            normal: "#FFFFD700",
                            subtle: "#b2FFD700"
                        },
                        attention: {
                            normal: "#FF8B0000",
                            subtle: "#b28B0000"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#08000000",
                    fontColors: {
                        default: {
                            normal: "#FF101010",
                            subtle: "#b2101010"
                        },
                        accent: {
                            normal: "#FF0000FF",
                            subtle: "#b20000FF"
                        },
                        good: {
                            normal: "#FF008000",
                            subtle: "#b2008000"
                        },
                        warning: {
                            normal: "#FFFFD700",
                            subtle: "#b2FFD700"
                        },
                        attention: {
                            normal: "#FF8B0000",
                            subtle: "#b28B0000"
                        }
                    }
                }
            },
            imageSizes: {
                small: 60,
                medium: 120,
                large: 180
            },
            actions: {
                maxActions: 5,
                spacing: Spacing.Default,
                buttonSpacing: 20,
                showCard: {
                    actionMode: ShowCardActionMode.Inline,
                    inlineTopMargin: 16
                },
                actionsOrientation: Orientation.Horizontal,
                actionAlignment: ActionAlignment.Left
            },
            adaptiveCard: {
                allowCustomStyle: false
            },
            image: {
                size: Size.Medium
            },
            imageSet: {
                imageSize: Size.Medium,
                maxImageHeight: 100
            },
            factSet: {
                title: {
                    color: TextColor.Default,
                    size: TextSize.Default,
                    isSubtle: false,
                    weight: TextWeight.Bolder,
                    wrap: true,
                    maxWidth: 150,
                },
                value: {
                    color: TextColor.Default,
                    size: TextSize.Default,
                    isSubtle: false,
                    weight: TextWeight.Default,
                    wrap: true,
                },
                spacing: 20
            }
        });
    }
}