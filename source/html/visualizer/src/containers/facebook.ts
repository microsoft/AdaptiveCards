import { HostContainer } from "./host-container";
import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";

export class FacebookContainer extends HostContainer {
    private _width: number;

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
        this.supportsActionBar = false;
    }

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var outerElement = document.createElement("div");
        outerElement.className = "facebookOuterContainer";
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
            colors: {
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
                    spacing: 20
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
                backgroundColor: "#FFF5F5F5",
                padding: {
                    left: 8,
                    top: 8,
                    right: 8,
                    bottom: 8
                }
            },
            container: {
                separation: {
                    spacing: 10
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
                        spacing: 10,
                    },
                    normal: {
                        spacing: 10
                    },
                    medium: {
                        spacing: 10
                    },
                    large: {
                        spacing: 10
                    },
                    extraLarge: {
                        spacing: 10
                    }
                }
            },
            image: {
                size: "medium",
                separation: {
                    spacing: 10
                }
            },
            imageSet: {
                imageSize: "medium",
                separation: {
                    spacing: 10
                }
            },
            factSet: {
                separation: {
                    spacing: 10
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
                spacing: 20
            },
            input: {
                separation: {
                    spacing: 10
                }
            },
            columnSet: {
                separation: {
                    spacing: 10
                }
            },
            column: {
                separation: {
                    spacing: 10
                }
            }
        };

    }
}