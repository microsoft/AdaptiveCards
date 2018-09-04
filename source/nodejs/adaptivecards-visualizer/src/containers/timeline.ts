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
} from "adaptivecards";

export class TimelineContainer extends HostContainer {
    // static backgroundColor: string = "#0078D7";

    private _width: number;
    private _height: number;

    constructor(width: number, height: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
        this._height = height;
        this.supportsActionBar = false;
    }

    protected renderContainer(adaptiveCard: AdaptiveCard, target: HTMLElement): HTMLElement {
        AdaptiveCard.useAdvancedCardBottomTruncation = true;

        var wrapper = document.createElement("div");
        wrapper.className = "timeline-frame";
        target.appendChild(wrapper);

        var cardContainer = document.createElement("div");
        cardContainer.className = "timeline-card"; 
        wrapper.appendChild(cardContainer);

        // Style must be set in code for fixed-height clipping to work
        var clippingDiv = document.createElement("div");
        clippingDiv.style.height = this._height + "px";
        clippingDiv.style.width = this._width + "px";
        clippingDiv.style.overflow = "hidden";
        cardContainer.appendChild(clippingDiv);

        var renderedCard = adaptiveCard.render();
        renderedCard.style.height = "100%";
        clippingDiv.appendChild(renderedCard);
        adaptiveCard.updateLayout();
        
        return wrapper;
    }

    public getHostConfig(): HostConfig {
        return new HostConfig({
            spacing: {
                small: 4,
                default: 12,
                medium: 20,
                large: 30,
                extraLarge: 40,
                padding: 15
            },
            separator: {
                lineThickness: 1,
                lineColor: "#EEEEEE"
            },
            supportsInteractivity: false,
            fontFamily: "Segoe UI",
            fontSizes: {
                small: 12,
                default: 14,
                medium: 20,
                large: 20,
                extraLarge: 26
            },
            fontWeights: {
                lighter: 200,
                default: 400,
                bolder: 700
            },
            containerStyles: {
                default: {
                    backgroundColor: "#535454",
                    foregroundColors: {
                        default: {
                            "default": "#FFFFFF",
                            "subtle": "#9C9E9F"
                        },
                        accent: {
                            "default": "#2E89FC",
                            "subtle": "#882E89FC"
                        },
                        attention: {
                            "default": "#FF0000",
                            "subtle": "#DDFF0000"
                        },
                        good: {
                            "default": "#00FF00",
                            "subtle": "#DD00FF00"
                        },
                        warning: {
                            "default": "#FFD800",
                            "subtle": "#DDFFD800"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#33000000",
                    foregroundColors: {
                        default: {
                            "default": "#FFFFFF",
                            "subtle": "#9C9E9F"
                        },
                        accent: {
                            "default": "#2E89FC",
                            "subtle": "#882E89FC"
                        },
                        attention: {
                            "default": "#FF0000",
                            "subtle": "#DDFF0000"
                        },
                        good: {
                            "default": "#00FF00",
                            "subtle": "#DD00FF00"
                        },
                        warning: {
                            "default": "#FFD800",
                            "subtle": "#DDFFD800"
                        }
                    }
                }
            },
            imageSizes: {
                small: 40,
                medium: 80,
                large: 120
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
                    wrap: false,
                    maxWidth: 150,
                },
                value: {
                    color: TextColor.Default,
                    size: TextSize.Default,
                    isSubtle: false,
                    weight: TextWeight.Default,
                    wrap: true,
                },
                spacing: 10
            }
        });
    }
}
