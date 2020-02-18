// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfig from "../../hostConfigs/outlook-desktop.json";

export class OutlookContainer extends HostContainer {
    constructor(name: string, styleSheet: string) {
        super(name, styleSheet);

        this.actionsRegistry.unregister("Action.Submit");
        this.actionsRegistry.register("Action.Http", Adaptive.HttpAction);
    }

    public renderTo(hostElement: HTMLElement) {
        hostElement.classList.add("outlook-frame");
        hostElement.appendChild(this.cardHost);
    }

    public initialize() {
        super.initialize();

        Adaptive.GlobalSettings.useMarkdownInRadioButtonAndCheckbox = false;
    }

    private parsePadding(source: any): Adaptive.PaddingDefinition {
        if (source) {
            if (typeof source === "string") {
                var uniformPadding = Adaptive.parseEnum(Adaptive.Spacing, source, Adaptive.Spacing.None);

                return new Adaptive.PaddingDefinition(
                    uniformPadding,
                    uniformPadding,
                    uniformPadding,
                    uniformPadding);
            }
            else if (typeof source === "object") {
                return new Adaptive.PaddingDefinition(
                    Adaptive.parseEnum(Adaptive.Spacing, source["top"], Adaptive.Spacing.None),
                    Adaptive.parseEnum(Adaptive.Spacing, source["right"], Adaptive.Spacing.None),
                    Adaptive.parseEnum(Adaptive.Spacing, source["bottom"], Adaptive.Spacing.None),
                    Adaptive.parseEnum(Adaptive.Spacing, source["left"], Adaptive.Spacing.None));
            }
        }

        return null;
    }

    public parseElement(element: Adaptive.CardElement, source: any, context: Adaptive.SerializationContext) {
        if (element instanceof Adaptive.Container && typeof source["rtl"] === "boolean") {
            element.rtl = source["rtl"];
        }

        if (element instanceof Adaptive.AdaptiveCard) {
            var card = <Adaptive.AdaptiveCard>element;
            var actionArray: Array<Adaptive.Action> = [];

            card["resources"] = { actions: actionArray };

            if (typeof source["resources"] === "object") {
                var actionResources = source["resources"]["actions"] as Array<any>;

                for (var i = 0; i < actionResources.length; i++) {
                    let action = this.actionsRegistry.createInstance(actionResources[i]["type"], context.targetVersion);

                    if (action) {
                        action.parse(actionResources[i], context);
                        action.setParent(card);

                        actionArray.push(action);
                    }
                }
            }
        }

        if (element instanceof Adaptive.Image) {
            (<Adaptive.Image>element).backgroundColor = source["backgroundColor"];
        }

        if (element instanceof Adaptive.Container) {
            var padding = this.parsePadding(source["padding"]);

            if (padding) {
                (<Adaptive.Container>element).padding = padding;
            }
        }

        if (element instanceof Adaptive.ColumnSet) {
            var padding = this.parsePadding(source["padding"]);

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

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfig);
    }
}
