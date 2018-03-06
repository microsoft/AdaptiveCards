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

export class CortanaContainer extends HostContainer {

    private _renderFrame: boolean;

    constructor(renderFrame: boolean, styleSheet: string) {
        super(styleSheet);

        this._renderFrame = renderFrame;
    }

    protected renderContainer(adaptiveCard: AdaptiveCard, target: HTMLElement): HTMLElement {

        var wrapper = document.createElement("div");
        wrapper.style.width = "342px";
        
        var cardContainer = document.createElement("div");

        if (this._renderFrame) {
            wrapper.className = "cortanaFrame";            
            cardContainer.className = "cardWrapper";
        }
 
        adaptiveCard.render(cardContainer);

        wrapper.appendChild(cardContainer);
        target.appendChild(wrapper);

        return cardContainer;
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
                lineColor: "#FF999999"
            },
            supportsInteractivity: true,
            fontFamily: "Segoe UI",
            fontSizes: {
                small: 13,
                default: 15,
                medium: 18,
                large: 20,
                extraLarge: 24
            },
            fontWeights: {
                lighter: 200,
                default: 400,
                bolder: 600
            },
            containerStyles: {
                default: {
                    backgroundColor: "#000000",
                    foregroundColors: {
                        default: {
                            default: "#FFFFFFFF",
                            subtle: "#99FFFFFF"
                        },
                        accent: {
                            default: "#FF2E89FC",
                            subtle: "#CC2E89FC"
                        },
                        dark: {
                            default: "#FF999999",
                            subtle: "#99999999"
                        },
                        light: {
                            default: "#FFFFFFFF",
                            subtle: "#99FFFFFF"
                        },
                        attention: {
                            default: "#CCFF0000",
                            subtle: "#99FF0000"
                        },
                        good: {
                            default: "#CC00FF00",
                            subtle: "#9900FF00"
                        },
                        warning: {
                            default: "#CCFF9800",
                            subtle: "#99FF9800"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#33FFFFFF",
                    foregroundColors: {
                        default: {
                            default: "#FFFFFFFF",
                            subtle: "#99FFFFFF"
                        },
                        accent: {
                            default: "#FF2E89FC",
                            subtle: "#CC2E89FC"
                        },
                        dark: {
                            default: "#FF999999",
                            subtle: "#99999999"
                        },
                        light: {
                            default: "#FFFFFFFF",
                            subtle: "#99FFFFFF"
                        },
                        attention: {
                            default: "#CCFF0000",
                            subtle: "#99FF0000"
                        },
                        good: {
                            default: "#CC00FF00",
                            subtle: "#9900FF00"
                        },
                        warning: {
                            default: "#CCFF9800",
                            subtle: "#99FF9800"
                        }
                    }
                }
            },
            imageSizes: {
                small: 40,
                medium: 68,
                large: 320
            },
            actions: {
                maxActions: 5,
                spacing: Spacing.Default,
                buttonSpacing: 5,
                showCard: {
                    actionMode: ShowCardActionMode.Inline,
                    inlineTopMargin: 20
                },
                actionsOrientation: Orientation.Horizontal,
                actionAlignment: ActionAlignment.Stretch
            },
            adaptiveCard: {
                allowCustomStyle: false
            },
            imageSet: {
                imageSize: Size.Small,
                maxImageHeight: 100
            },
            factSet: {
                title: {
                    color: TextColor.Default,
                    size: TextSize.Default,
                    isSubtle: false,
                    weight: TextWeight.Bolder,
                    wrap: true
                },
                value: {
                    color: TextColor.Default,
                    size: TextSize.Default,
                    isSubtle: false,
                    weight: TextWeight.Default,
                    wrap: true,
                },
                spacing: 12
            }
        });
    }
}
