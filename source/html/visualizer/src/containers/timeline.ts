import { HostContainer } from "./host-container";
import * as Adaptive from "microsoft-adaptivecards";

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

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        // element.style.backgroundColor = TimelineContainer.backgroundColor;
        element.style.overflow = "hidden";

        renderedCard.style.height = "100%";

        element.appendChild(renderedCard);

        return element;
    }

    public getHostConfig(): Adaptive.IHostConfig {
        return {
            spacing: {
                small: 3,
                default: 8,
                medium: 20,
                large: 30,
                extraLarge: 40
            },
            separator: {
                lineThickness: 1,
                lineColor: "#EEEEEE"        
            },
            supportsInteractivity: false,
            fontFamily: "Segoe UI",
            fontSizes: {
                small: 12,
                normal: 13,
                medium: 20,
                large: 24,
                extraLarge: 26
            },
            fontWeights: {
                lighter: 200,
                normal: 400,
                bolder: 600
            },
            colors: {
                dark: {
                    "normal": "#333333",
                    "subtle": "#EE333333"
                },
                light: {
                    "normal": "#FFFFFF",
                    "subtle": "#9C9E9F"
                },
                accent: {
                    "normal": "#2E89FC",
                    "subtle": "#882E89FC"
                },
                attention: {
                    "normal": "#FF0000",
                    "subtle": "#DDFF0000"
                },
                good: {
                    "normal": "#00FF00",
                    "subtle": "#DD00FF00"
                },
                warning: {
                    "normal": "#FFD800",
                    "subtle": "#DDFFD800"
                }
            },
            imageSizes: {
                small: 40,
                medium: 80,
                large: 120
            },
            actions: {
                maxActions: 5,
                spacing: "default",
                buttonSpacing: 20,
                showCard: {
                    actionMode: "inlineEdgeToEdge",
                    inlineTopMargin: 16,
                    backgroundColor: "#08000000",
                    padding: {
                        top: 16,
                        right: 16,
                        bottom: 16,
                        left: 16
                    }
                },
                actionsOrientation: "horizontal",
                actionAlignment: "left"
            },
            adaptiveCard: {
                backgroundColor: "#535454",
                padding: {
                    left: 16,
                    top: 22,
                    right: 16,
                    bottom: 24
                }
            },
            container: {
                normal: {
                },
                emphasis: {
                    backgroundColor: "#EEEEEE",
                    borderColor: "#AAAAAA",
                    borderThickness: {
                        top: 1,
                        right: 1,
                        bottom: 1,
                        left: 1
                    },
                    padding: {
                        top: 10,
                        right: 10,
                        bottom: 10,
                        left: 10
                    }
                }
            },
            textBlock: {
                color: "light"
            },
            image: {
                size: "medium"
            },
            imageSet: {
                imageSize: "medium",
                maxImageHeight: 100
            },
            factSet: {
                title: {
                    color: "light",
                    size: "normal",
                    isSubtle: true,
                    weight: "bolder",
                    wrap: false,
                    maxWidth: 150,
                },
                value: {
                    color: "light",
                    size: "normal",
                    isSubtle: true,
                    weight: "normal",
                    wrap: true,
                },
                spacing: 10
            }
        };
    }
}