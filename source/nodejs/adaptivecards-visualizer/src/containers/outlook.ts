import { HostContainer } from "./host-container";
import * as Adaptive from "adaptivecards";

export class ToggleVisibilityAction extends Adaptive.Action {
    targetElementIds: Array<string> = [];

    getJsonTypeName(): string {
        return "Action.ToggleVisibility";
    }

    execute() {
        if (this.targetElementIds) {
            for (var i = 0; i < this.targetElementIds.length; i++) {
                var targetElement = this.parent.getRootElement().getElementById(this.targetElementIds[i]);

                if (targetElement) {
                    targetElement.isVisible = !targetElement.isVisible;
                }
            }
        }
    }

    parse(json: any) {
        super.parse(json);

        this.targetElementIds = json["targetElementIds"] as Array<string>;
    }
}

export class OutlookContainer extends HostContainer {
    protected renderContainer(adaptiveCard: Adaptive.AdaptiveCard, target: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";
        element.style.border = "1px solid #F1F1F1"
        target.appendChild(element);

        adaptiveCard.render(element);

        return element;
    }

    public initialize() {
        super.initialize();

        Adaptive.AdaptiveCard.elementTypeRegistry.registerType("ActionSet", () => { return new Adaptive.ActionSet(); });

        Adaptive.AdaptiveCard.actionTypeRegistry.unregisterType("Action.Submit");
        Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.Http", () => { return new Adaptive.HttpAction(); });
        Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.ToggleVisibility", () => { return new ToggleVisibilityAction(); });

        Adaptive.AdaptiveCard.preExpandSingleShowCardAction = true;
        Adaptive.AdaptiveCard.useMarkdownInRadioButtonAndCheckbox = false;
    }

    public parseElement(element: Adaptive.CardElement, json: any) {
        if (typeof json["isVisible"] === "boolean") {
            element.isVisible = json["isVisible"];
        }

        if (element instanceof Adaptive.Image) {
            (<Adaptive.Image>element).backgroundColor = json["backgroundColor"];
        }

        if (element instanceof Adaptive.Column) {
            (<Adaptive.Column>element).pixelWidth = json["pixelWidth"];
        }

        if (element instanceof Adaptive.Container) {
            var container = <Adaptive.Container>element;

            container.bleed = json["bleed"];

            var jsonPadding = json["padding"];

            if (jsonPadding) {
                if (typeof jsonPadding === "string") {
                    var uniformPadding = Adaptive.getEnumValueOrDefault(Adaptive.Spacing, jsonPadding, Adaptive.Spacing.None);
    
                    container.padding = new Adaptive.PaddingDefinition(
                        uniformPadding,
                        uniformPadding,
                        uniformPadding,
                        uniformPadding);
                }
                else if (typeof jsonPadding === "object") {
                    container.padding = new Adaptive.PaddingDefinition(
                        Adaptive.getEnumValueOrDefault(Adaptive.Spacing, jsonPadding["top"], Adaptive.Spacing.None),
                        Adaptive.getEnumValueOrDefault(Adaptive.Spacing, jsonPadding["right"], Adaptive.Spacing.None),
                        Adaptive.getEnumValueOrDefault(Adaptive.Spacing, jsonPadding["bottom"], Adaptive.Spacing.None),
                        Adaptive.getEnumValueOrDefault(Adaptive.Spacing, jsonPadding["left"], Adaptive.Spacing.None));
                }
            }    
        }
    }

    public anchorClicked(anchor: HTMLAnchorElement): boolean {
        if (anchor.href.toLowerCase().startsWith("action:")) {
            alert("Executing inline action...");

            return true;
        }
        else {
            return false;
        }
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig({
            supportsInteractivity: true,
            fontFamily: "Segoe UI",
            spacing: {
                small: 10,
                default: 20,
                medium: 30,
                large: 40,
                extraLarge: 50,
                padding: 20
            },
            separator: {
                lineThickness: 1,
                lineColor: "#EEEEEE"
            },
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
            imageSizes: {
                small: 40,
                medium: 80,
                large: 160
            },
            containerStyles: {
                default: {
                    backgroundColor: "#FFFFFF",
                    foregroundColors: {
                        default: {
                            default: "#333333",
                            subtle: "#EE333333"
                        },
                        accent: {
                            default: "#2E89FC",
                            subtle: "#882E89FC"
                        },
                        attention: {
                            default: "#cc3300",
                            subtle: "#DDcc3300"
                        },
                        good: {
                            default: "#54a254",
                            subtle: "#DD54a254"
                        },
                        warning: {
                            default: "#e69500",
                            subtle: "#DDe69500"
                        }
                    }
                },
                emphasis: {
                    backgroundColor: "#08000000",
                    foregroundColors: {
                        default: {
                            default: "#333333",
                            subtle: "#EE333333"
                        },
                        accent: {
                            default: "#2E89FC",
                            subtle: "#882E89FC"
                        },
                        attention: {
                            default: "#cc3300",
                            subtle: "#DDcc3300"
                        },
                        good: {
                            default: "#54a254",
                            subtle: "#DD54a254"
                        },
                        warning: {
                            default: "#e69500",
                            subtle: "#DDe69500"
                        }
                    }
                }
            },
            actions: {
                maxActions: 5,
                spacing: Adaptive.Spacing.Default,
                buttonSpacing: 10,
                showCard: {
                    actionMode: Adaptive.ShowCardActionMode.Inline,
                    inlineTopMargin: 16
                },
                actionsOrientation: Adaptive.Orientation.Horizontal,
                actionAlignment: Adaptive.ActionAlignment.Left
            },
            adaptiveCard: {
                allowCustomStyle: false
            },
            imageSet: {
                imageSize: Adaptive.Size.Medium,
                maxImageHeight: 100
            },
            factSet: {
                title: {
                    color: Adaptive.TextColor.Default,
                    size: Adaptive.TextSize.Default,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Bolder,
                    wrap: true,
                    maxWidth: 150,
                },
                value: {
                    color: Adaptive.TextColor.Default,
                    size: Adaptive.TextSize.Default,
                    isSubtle: false,
                    weight: Adaptive.TextWeight.Default,
                    wrap: true,
                },
                spacing: 10
            }
        });
    }
}