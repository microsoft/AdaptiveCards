import { HostContainer } from "./host-container";
import * as Adaptive from "adaptivecards";
import {
        Spacing,
        ShowCardActionMode,
        Orientation,
        ActionAlignment,
        Size,
        TextColor,
        TextSize,
        TextWeight,
        AdaptiveCard
    } from "adaptivecards";

export class TimelineContainer extends HostContainer {
    private _width: number;
    private _height: number;

    // constructor(width: number, height: number, styleSheet: string) {
    //     super(name, styleSheet);

    //     this._width = width;
    //     this._height = height;
    //     // this.supportsActionBar = false;
    // }

    renderTo(hostElement: HTMLElement) {
        AdaptiveCard.useAdvancedCardBottomTruncation = true;

        let cardHost = this.cardHost;

        let timelineCardChild = document.querySelector('.timeline-card > div') as HTMLElement;

        let target = document.getElementById("designerHost");
        let frame = document.createElement("div");
        frame.className = "timeline-frame";
        target.appendChild(frame);

        let cardContainer = document.createElement("div");
        cardContainer.className = "timeline-card";
        frame.appendChild(cardContainer);
        cardHost.style.height = "178px";
        cardHost.style.width = "328px";
        cardHost.style.overflow = "hidden";

        cardContainer.appendChild(cardHost);
        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig({
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
