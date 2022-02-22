// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfig from "../../hostConfigs/federated-search.json";

export class FederatedSearchContainer extends HostContainer {
  constructor(name: string, styleSheet: string) {
    super(name, styleSheet);

    this.actionsRegistry.unregister("Action.Submit");
    this.elementsRegistry.unregister("Input.Text");
    this.elementsRegistry.unregister("Input.Date");
    this.elementsRegistry.unregister("Input.Time");
    this.elementsRegistry.unregister("Input.Toggle");
    this.elementsRegistry.unregister("Input.ChoiceSet");
    this.elementsRegistry.unregister("Input.Number");
    this.actionsRegistry.register("Action.Http", Adaptive.HttpAction);
    this.cardHost.classList.add("fedsearch-card");
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
        const uniformPadding = Adaptive.parseEnum(Adaptive.Spacing, source, Adaptive.Spacing.None);

        return new Adaptive.PaddingDefinition(
          uniformPadding,
          uniformPadding,
          uniformPadding,
          uniformPadding
        );
      } else if (typeof source === "object") {
        return new Adaptive.PaddingDefinition(
          Adaptive.parseEnum(Adaptive.Spacing, source["top"], Adaptive.Spacing.None),
          Adaptive.parseEnum(Adaptive.Spacing, source["right"], Adaptive.Spacing.None),
          Adaptive.parseEnum(Adaptive.Spacing, source["bottom"], Adaptive.Spacing.None),
          Adaptive.parseEnum(Adaptive.Spacing, source["left"], Adaptive.Spacing.None)
        );
      }
    }

    return null;
  }

  public parseElement(
    element: Adaptive.CardElement,
    source: any,
    context: Adaptive.SerializationContext
  ) {
    if (element instanceof Adaptive.Container && typeof source["rtl"] === "boolean") {
      element.rtl = source["rtl"];
    }

    if (element instanceof Adaptive.AdaptiveCard) {
      const card = element;
      const actionArray: Array<Adaptive.Action> = [];

      card["resources"] = { actions: actionArray };

      if (typeof source["resources"] === "object") {
        const actionResources = source["resources"]["actions"] as Array<any>;

        actionResources.forEach((action) => {
          this.actionsRegistry.createInstance(actionResources["type"], context.targetVersion);

          if (action) {
            action.parse(actionResources, context);
            action.setParent(card);

            actionArray.push(action);
          }
        });
      }
    }

    if (element instanceof Adaptive.Image) {
      element.backgroundColor = source["backgroundColor"];
    }

    if (element instanceof Adaptive.Container) {
      const padding = this.parsePadding(source["padding"]);

      if (padding) {
        element.padding = padding;
      }
    }

    if (element instanceof Adaptive.ColumnSet) {
      const padding = this.parsePadding(source["padding"]);

      if (padding) {
        element.padding = padding;
      }
    }
  }

  public anchorClicked(element: Adaptive.CardElement, anchor: HTMLAnchorElement): boolean {
    const regEx = /^action:([a-z0-9]+)$/gi;
    const rootCard = element.getRootElement() as Adaptive.AdaptiveCard;
    const matches = regEx.exec(anchor.href);

    if (matches) {
      const actionId = matches[1];

      if (rootCard) {
        const actionArray = rootCard["resources"]["actions"] as Array<Adaptive.Action>;

        actionArray.forEach((_, i) => {
          if (actionArray[i].id === actionId) {
            actionArray[i].execute();

            return true;
          }
        });
      }
    }

    return false;
  }

  public getHostConfig(): Adaptive.HostConfig {
    return new Adaptive.HostConfig(hostConfig);
  }

  get targetVersion(): Adaptive.Version {
    return Adaptive.Versions.v1_4;
  }
}
