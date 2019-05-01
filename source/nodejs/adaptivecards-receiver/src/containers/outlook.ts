// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { HostContainer } from "./host-container";
import * as Adaptive from "adaptivecards";
import * as outlookConfiguration from "../../../../../samples/HostConfig/outlook-desktop.json";

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

        Adaptive.AdaptiveCard.actionTypeRegistry.unregisterType("Action.Submit");
        Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.Http", () => { return new Adaptive.HttpAction(); });

        Adaptive.AdaptiveCard.useMarkdownInRadioButtonAndCheckbox = false;
        Adaptive.AdaptiveCard.allowMarkForTextHighlighting = true;
    }

    private parsePadding(json: any): Adaptive.PaddingDefinition {
        if (json) {
            if (typeof json === "string") {
                var uniformPadding = Adaptive.getEnumValue(Adaptive.Spacing, json, Adaptive.Spacing.None);

                return new Adaptive.PaddingDefinition(
                    uniformPadding,
                    uniformPadding,
                    uniformPadding,
                    uniformPadding);
            }
            else if (typeof json === "object") {
                return new Adaptive.PaddingDefinition(
                    Adaptive.getEnumValue(Adaptive.Spacing, json["top"], Adaptive.Spacing.None),
                    Adaptive.getEnumValue(Adaptive.Spacing, json["right"], Adaptive.Spacing.None),
                    Adaptive.getEnumValue(Adaptive.Spacing, json["bottom"], Adaptive.Spacing.None),
                    Adaptive.getEnumValue(Adaptive.Spacing, json["left"], Adaptive.Spacing.None));
            }
        }

        return null;
    }

    public parseElement(element: Adaptive.CardElement, json: any) {
        if (element instanceof Adaptive.Container && json["rtl"] != undefined) {
            //element.rtl = json["rtl"];
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

    public anchorClicked(element: Adaptive.CardElement, anchor: HTMLAnchorElement): boolean {
        var regEx = /^action:([a-z0-9]+)$/ig;
        var rootCard = element.getRootElement() as Adaptive.AdaptiveCard;

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

    public setHostCapabilities(hostConfig: Adaptive.HostConfig) {
        // Uncomment to test "requires" clause
        hostConfig.hostCapabilities.capabilities = {
            helloWorld: "*",
            whatNow: new Adaptive.Version(2, 3)
        };
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(outlookConfiguration);
    }
}
