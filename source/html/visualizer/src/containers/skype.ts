import { HostContainer } from "./host-container";
import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";

export class SkypeContainer extends HostContainer {
    private _width: number;

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.className = "skypeContainer";

        // Draw the hexagon bot logo
        var botElement = document.createElement("div");
        botElement.className = "hexagon";

        var botElementIn1 = document.createElement("div");
        botElementIn1.className = "hexagon-in1";
        botElement.appendChild(botElementIn1);

        var botElementIn2 = document.createElement("div");
        botElementIn2.className = "hexagon-in2";
        botElementIn1.appendChild(botElementIn2);

        element.appendChild(botElement);

        renderedCard.style.width = this._width + "px";

        element.appendChild(renderedCard);

        return element;
    }

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
    }

    public getHostConfig(): Adaptive.IHostConfig {
        return {
            supportsInteractivity: true,
            strongSeparation: {
                spacing: 20,
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
                }
            },
            imageSizes: {
                small: 40,
                medium: 80,
                large: 160
            },
            actions: {
                maxActions: 5,
                separation: {
                    spacing: 20
                },
                buttonSpacing: 10,
                showCard: {
                    actionMode: "popup",
                    inlineTopMargin: 16,
                    backgroundColor: "#AEEAEAEA",
                    padding: {
                        top: 16,
                        right: 16,
                        bottom: 16,
                        left: 16
                    }
                },
                actionsOrientation: "vertical",
                actionAlignment: "stretch"
            },
            adaptiveCard: {
                backgroundColor: "#AEEAEAEA",
                padding: {
                    left: 10,
                    top: 10,
                    right: 10,
                    bottom: 10
                }
            },
            container: {
                separation: {
                    spacing: 5
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
                color: "dark",
                separations: {
                    small: {
                        spacing: 5,
                    },
                    normal: {
                        spacing: 5
                    },
                    medium: {
                        spacing: 5
                    },
                    large: {
                        spacing: 5
                    },
                    extraLarge: {
                        spacing: 5
                    }
                }
            },
            image: {
                size: "medium",
                separation: {
                    spacing: 5
                }
            },
            imageSet: {
                imageSize: "medium",
                separation: {
                    spacing: 5
                }
            },
            factSet: {
                separation: {
                    spacing: 5
                },
                title: {
                    color: "dark",
                    size: "normal",
                    isSubtle: false,
                    weight: "bolder",
                    wrap: true,
                    maxWidth: 150,
                },
                value: {
                    color: "dark",
                    size: "normal",
                    isSubtle: false,
                    weight: "normal",
                    wrap: true,
                },
                spacing: 5
            },
            input: {
                separation: {
                    spacing: 5
                }
            },
            columnSet: {
                separation: {
                    spacing: 5
                }
            },
            column: {
                separation: {
                    spacing: 5
                }
            }
        };
    }
}