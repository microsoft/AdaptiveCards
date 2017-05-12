import { HostContainer } from "./host-container";
import * as Adaptive from "microsoft-adaptivecards";
import * as Utils from "../utils";

export class KikContainer extends HostContainer {
    private _width: number;

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
        this.supportsActionBar = false;
    }

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var outerElement = document.createElement("div");
        outerElement.className = "kikOuterContainer";
        outerElement.style.width = this._width + "px";
        outerElement.appendChild(renderedCard);
        return outerElement;
    }

    public getHostConfig(): Adaptive.IHostConfig {
        return {
            supportsInteractivity: false,
            strongSeparation: {
                spacing: 20,
                lineThickness: 1,
                lineColor: "#FF707070"
            },
            fontFamily: "Calibri, Candara, Segoe, 'Segoe UI', Optima, Arial, sans-serif;",
            fontSizes: {
                small: 12,
                normal: 14,
                medium: 16,
                large: 19,
                extraLarge: 22
            },
            fontWeights: {
                lighter: 200,
                normal: 400,
                bolder: 600
            },
            colors:{
//                default: {
//                    normal: "#FF000000",
//                    subtle: "#b2000000"
//                },
                accent: {
                    normal: "#FF0000FF",
                    subtle: "#b20000FF"
                },
                dark: {
                    normal: "#FF101010",
                    subtle: "#b2101010"
                },
                light: {
                    normal: "#FFFFFFFF",
                    subtle: "#b2FFFFFF"
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
            },
            imageSizes: {
                small: 60,
                medium: 120,
                large: 180
            },
            actions: {
                maxActions: 5,
                separation: {
                    spacing: 8
                },
                buttonSpacing: 10,
                showCard: {
                    actionMode: "inlineEdgeToEdge",
                    inlineTopMargin: 16,
                    backgroundColor: "#08000000",
                    padding: {
                        top: 8,
                        right: 8,
                        bottom: 8,
                        left: 8
                    }
                },
                actionsOrientation: "horizontal",
                actionAlignment: "left"
            },
            adaptiveCard: {
                backgroundColor: "#FFFFFF",
                padding: {
                    left: 8,
                    top: 8,
                    right: 8,
                    bottom: 8
                }
            },
            container: {
                separation: {
                    spacing: 8
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
                        spacing: 8,
                    },
                    normal: {
                        spacing: 8
                    },
                    medium: {
                        spacing: 8
                    },
                    large: {
                        spacing: 8
                    },
                    extraLarge: {
                        spacing: 8
                    }
                }
            },
            image: {
                size: "medium",
                separation: {
                    spacing: 8
                }
            },
            imageSet: {
                imageSize: "medium",
                separation: {
                    spacing: 8
                }
            },
            factSet: {
                separation: {
                    spacing: 8
                },
                title: {
                    color: "dark",
                    size: "normal",
                    isSubtle: false,
                    weight: "bolder",
                    wrap: true,
                    maxWidth: 150
                },
                value: {
                    color: "dark",
                    size: "normal",
                    isSubtle: false,
                    weight: "normal",
                    wrap: true
                },
                spacing: 10
            },
            input: {
                separation: {
                    spacing: 8
                }
            },
            columnSet: {
                separation: {
                    spacing: 8
                }
            },
            column: {
                separation: {
                    spacing: 8
                }
            }
        };
    }
}