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
        TextWeight
    } from "adaptivecards";

export class ToastContainer extends HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("toast-card");

        let frame = document.createElement("div");
        frame.className = "toast-frame";
        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig({
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
                default: 14,
                medium: 17,
                large: 21,
                extraLarge: 26
            },
            fontWeights: {
                lighter: 200,
                default: 400,
                bolder: 600
            },
            containerStyles: {
                default: {
                    backgroundColor: "#1F1F1F",
                    foregroundColors: {
                        default: {
                            default: "#FFFFFF",
                            subtle: "#88FFFFFF"
                        },
                        accent: {
                            default: "#2E89FC",
                            subtle: "#882E89FC"
                        },
                        attention: {
                            default: "#FF0000",
                            subtle: "#DDFF0000"
                        },
                        good: {
                            default: "#00FF00",
                            subtle: "#DD00FF00"
                        },
                        warning: {
                            default: "#FFD800",
                            subtle: "#DDFFD800"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#19FFFFFF",
                    foregroundColors: {
                        default: {
                            default: "#FFFFFF",
                            subtle: "#88FFFFFF"
                        },
                        accent: {
                            default: "#2E89FC",
                            subtle: "#882E89FC"
                        },
                        attention: {
                            default: "#FFD800",
                            subtle: "#DDFFD800"
                        },
                        good: {
                            default: "#00FF00",
                            subtle: "#DD00FF00"
                        },
                        warning: {
                            default: "#FF0000",
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
                    actionMode: ShowCardActionMode.Inline,
                    inlineTopMargin: 16
                },
                actionsOrientation: Orientation.Horizontal,
                actionAlignment: ActionAlignment.Stretch
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
                spacing: 10
            }
        });
    }
}
