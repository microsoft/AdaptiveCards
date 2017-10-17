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

export class GroupMeContainer extends HostContainer {
    private _width: number;

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
        this.supportsActionBar = false;
    }

    protected renderContainer(adaptiveCard: AdaptiveCard, target: HTMLElement) {
        var outerElement = document.createElement("div");
        outerElement.className = "groupmeOuterContainer";
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
            fontFamily: "'Segoe UI', Frutiger, 'Frutiger Linotype', 'Dejavu Sans', 'Helvetica Neue', Arial, sans-serif",
            fontSizes: {
                small: 13,
                default: 15,
                medium: 17,
                large: 20,
                extraLarge: 23
            },
            fontWeights: {
                lighter: 200,
                default: 400,
                bolder: 600
            },
            containerStyles: {
                default: {
                    backgroundColor: "#F7F7F7",
                    fontColors: {
                        default: {
                            normal: "#333333",
                            subtle: "#EE333333",
                        },
                        accent: {
                            normal: "#2E89FC",
                            subtle: "#882E89FC",
                        },
                        attention: {
                            normal: "#FF0000",
                            subtle: "#DDFF0000"
                        },
                        good: {
                            normal: "#54a254",
                            subtle: "#DD54a254",
                        },
                        warning: {
                            normal: "#c3ab23",
                            subtle: "#DDc3ab23",
                        },
                    },
                },
                emphasis: {
                    backgroundColor: "#08000000",
                    fontColors: {
                        default: {
                            normal: "#333333",
                            subtle: "#EE333333"
                        },
                        accent: {
                            normal: "#2E89FC",
                            subtle: "#882E89FC"
                        },
                        attention: {
                            normal: "#FF0000",
                            subtle: "#DDFF0000"
                        },
                        good: {
                            normal: "#54a254",
                            subtle: "#DD54a254"
                        },
                        warning: {
                            normal: "#c3ab23",
                            subtle: "#DDc3ab23"
                        },
                    },
                },
            },
            imageSizes: {
                small: 60,
                medium: 120,
                large: 180,
            },
            actions: {
                maxActions: 5,
                spacing: Spacing.Default,
                buttonSpacing: 20,
                showCard: {
                    actionMode: ShowCardActionMode.Inline,
                    inlineTopMargin: 16,
                },
                actionsOrientation: Orientation.Horizontal,
                actionAlignment: ActionAlignment.Left,
            },
            adaptiveCard: {
                allowCustomStyle: false,
            },
            image: {
                size: Size.Medium,
            },
            imageSet: {
                imageSize: Size.Medium,
                maxImageHeight: 100,
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
                spacing: 10,
            },
        });
    }
}