import { HostContainer} from "./host-container";
import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";

export class ToastContainer extends HostContainer {
    private _width: number;

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.style.border = "#474747 1px solid";
        element.style.width = this._width + "px";
        element.style.overflow = "hidden";

        element.appendChild(renderedCard);

        return element;
    }

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
    }

    public getHostConfiguration(): Adaptive.IHostConfiguration {
        return {
            supportedElementTypes: [
                Adaptive.Container,
                Adaptive.TextBlock,
                Adaptive.Image,
                Adaptive.ImageSet,
                Adaptive.FactSet,
                Adaptive.ColumnSet,
                Adaptive.ActionSet,
                Adaptive.TextInput,
                Adaptive.DateInput,
                Adaptive.NumberInput,
                Adaptive.ChoiceSetInput,
                Adaptive.ToggleInput            
            ],
            supportsInteractivity: true,
            strongSeparation: {
                spacing: 20,
                lineThickness: 1,
                lineColor: "#22FFFFFF"
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
                    normal: "#FFD800",
                    subtle: "#DDFFD800"
                },
                good: {
                    normal: "#00FF00",
                    subtle: "#DD00FF00"
                },
                warning: {
                    normal: "#FF0000",
                    subtle: "#DDFF0000"
                }
            },
            imageSizes: {
                small: 40,
                medium: 80,
                large: 160
            },
            actions: {
                maxActions: 5,
                supportedActionTypes: [
                    Adaptive.HttpAction,
                    Adaptive.OpenUrlAction,
                    Adaptive.SubmitAction,
                    Adaptive.ShowCardAction
                ],
                separation: {
                    spacing: 10
                },
                buttonSpacing: 10,
                stretch: true,
                showCard: {
                    actionMode: Adaptive.ShowCardActionMode.InlineEdgeToEdge,
                    inlineCardSpacing: 10,
                    backgroundColor: "#22FFFFFF",
                    padding: {
                        top: 10,
                        right: 10,
                        bottom: 10,
                        left: 10
                    }
                },
                actionsOrientation: Adaptive.Orientation.Horizontal,
                actionAlignment: Adaptive.HorizontalAlignment.Left
            },
            adaptiveCard: {
                backgroundColor: "#1F1F1F",
                padding: {
                    left: 10,
                    top: 10,
                    right: 10,
                    bottom: 10
                }
            },
            container: {
                separation: {
                    spacing: 10
                },
                normal: {
                },
                emphasis: {
                    backgroundColor: "#22FFFFFF",
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
                color: Adaptive.TextColor.Light,
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
                size: Adaptive.Size.Medium,
                separation: {
                    spacing: 10
                }
            },
            imageSet: {
                imageSize: Adaptive.Size.Medium,
                separation: {
                    spacing: 10
                }
            },
            factSet: {
                separation: {
                    spacing: 10
                },
                title: {
                    color: Adaptive.TextColor.Dark,
                    size: Adaptive.TextSize.Normal,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Bolder
                },
                value: {
                    color: Adaptive.TextColor.Dark,
                    size: Adaptive.TextSize.Normal,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Normal
                },
                spacing: 10
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