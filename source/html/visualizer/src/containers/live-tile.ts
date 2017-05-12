import { HostContainer} from "./host-container";
import * as Adaptive from "microsoft-adaptivecards";
import * as Utils from "../utils";

export class LiveTileContainer extends HostContainer {
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
        // element.style.backgroundColor = LiveTileContainer.backgroundColor;
        element.style.overflow = "hidden";

        renderedCard.style.height = "100%";

        element.appendChild(renderedCard);

        return element;
    }

    public getHostConfig(): Adaptive.IHostConfig {
        return {
            supportsInteractivity: false,
            strongSeparation: {
                spacing: 5,
                lineThickness: 1,
                lineColor: "#EEEEEE"
            },
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
            colors: {
                dark: {
                    normal: "#333333",
                    subtle: "#EE333333"
                },
                light: {
                    normal: "#FFFFFF",
                    subtle: "#88FFFFFF"
                },
                accent: {
                    normal: "#00c2ff",
                    subtle: "#8800c2ff" 
                },
                attention: {
                    normal: "#ffa700",
                    subtle: "#DDffa700"
                },
                good: {
                    normal: "#00FF00",
                    subtle: "#DD00FF00"
                },
                warning: {
                    normal: "#FFD800",
                    subtle: "#DDFFD800"
                }
            },
            imageSizes: {
                small: 40,
                medium: 80,
                large: 120
            },
            actions: {
                maxActions: 5,
                separation: {
                    spacing: 0
                },
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
                backgroundColor: "#0078D7",
                padding: {
                    left: 10,
                    top: 10,
                    right: 10,
                    bottom: 10
                }
            },
            container: {
                separation: {
                    spacing: 0
                },
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
                color: "light",
                separations: {
                    small: {
                        spacing: 0,
                    },
                    normal: {
                        spacing: 0
                    },
                    medium: {
                        spacing: 0
                    },
                    large: {
                        spacing: 0
                    },
                    extraLarge: {
                        spacing: 0
                    }
                }
            },
            image: {
                size: "medium",
                separation: {
                    spacing: 0
                }
            },
            imageSet: {
                imageSize: "medium",
                separation: {
                    spacing: 0
                }
            },
            factSet: {
                separation: {
                    spacing: 0
                },
                title: {
                    color: "light",
                    size: "normal",
                    isSubtle: false,
                    weight: "bolder",
                    wrap: true,
                    maxWidth: 150,
                },
                value: {
                    color: "light",
                    size: "normal",
                    isSubtle: false,
                    weight: "normal",
                    wrap: true,
                },
                spacing: 10
            },
            input: {
                separation: {
                    spacing: 0
                }
            },
            columnSet: {
                separation: {
                    spacing: 0
                }
            },
            column: {
                separation: {
                    spacing: 0
                }
            }
        };
    }
}