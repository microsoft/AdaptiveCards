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

        this.targetElementIds = json["targetElements"] as Array<string>;
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

        Adaptive.AdaptiveCard.useMarkdownInRadioButtonAndCheckbox = false;
    }

    private parsePadding(json: any): Adaptive.PaddingDefinition {
        if (json) {
            if (typeof json === "string") {
                var uniformPadding = Adaptive.getEnumValueOrDefault(Adaptive.Spacing, json, Adaptive.Spacing.None);

                return new Adaptive.PaddingDefinition(
                    uniformPadding,
                    uniformPadding,
                    uniformPadding,
                    uniformPadding);
            }
            else if (typeof json === "object") {
                return new Adaptive.PaddingDefinition(
                    Adaptive.getEnumValueOrDefault(Adaptive.Spacing, json["top"], Adaptive.Spacing.None),
                    Adaptive.getEnumValueOrDefault(Adaptive.Spacing, json["right"], Adaptive.Spacing.None),
                    Adaptive.getEnumValueOrDefault(Adaptive.Spacing, json["bottom"], Adaptive.Spacing.None),
                    Adaptive.getEnumValueOrDefault(Adaptive.Spacing, json["left"], Adaptive.Spacing.None));
            }
        }

        return null;
    }

    public parseElement(element: Adaptive.CardElement, json: any) {
        if (typeof json["isVisible"] === "boolean") {
            element.isVisible = json["isVisible"];
        }

        if (element instanceof Adaptive.AdaptiveCard) {
            var card = <Adaptive.AdaptiveCard>element;
            var actionArray: Array<Adaptive.Action> = [];

            card["resources"] = { actions: actionArray };

            if (typeof json["resources"] === "object") {
                var actionResources = json["resources"]["actions"] as Array<any>;

                for (var i = 0; i < actionResources.length; i++) {
                    let action = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionResources[i]["type"]);

                    if (action) {
                        action.parse(actionResources[i]);
                        action.setParent(card);

                        actionArray.push(action);
                    }
                }
            }
        }

        if (element instanceof Adaptive.Image) {
            (<Adaptive.Image>element).backgroundColor = json["backgroundColor"];
        }

        if (element instanceof Adaptive.Column) {
            (<Adaptive.Column>element).pixelWidth = json["pixelWidth"];
        }

        if (element instanceof Adaptive.Container) {
            var padding = this.parsePadding(json["padding"]);

            if (padding) {
                (<Adaptive.Container>element).padding = padding;
            }
        }

        if (element instanceof Adaptive.ColumnSet) {
            var padding = this.parsePadding(json["padding"]);

            if (padding) {
                (<Adaptive.ColumnSet>element).padding = padding;
            }
        }
    }

    public anchorClicked(rootCard: Adaptive.AdaptiveCard, anchor: HTMLAnchorElement): boolean {
        var regEx = /^action:([a-z0-9]+)$/ig;

        var matches = regEx.exec(anchor.href);
        
        if (matches) {
            var actionId = matches[1];

            if (rootCard) {
                var actionArray = rootCard["resources"]["actions"] as Array<Adaptive.Action>;

                for (var i = 0; i < actionArray.length; i++) {
                    if (actionArray[i].id == actionId) {
                        actionArray[i].execute();

                        return true;
                    }
                }
            }
        }

        return false;
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig({
            preExpandSingleShowCardAction: true,
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
                allowCustomStyle: true
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