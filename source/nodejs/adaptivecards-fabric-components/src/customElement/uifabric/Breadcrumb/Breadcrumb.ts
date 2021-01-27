// Below is sample json
// {
//     "type": "AdaptiveCard",
//     "body": [
//         {
//             "type": "Breadcrumb",
//             "items": "[{\"text\":\"Folder 1\",\"key\":\"f4\"},{\"text\":\"Folder 2\",\"key\":\"f2\"},{\"text\":\"Folder 3\",\"key\":\"f3\"}]"
//         }
//     ],
//     "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
//     "version": "1.3"
// }

import * as AC from 'adaptivecards';
import * as ReactDOM from "react-dom";
import { getBreadCrumbElement } from './BreadcrumbElement';
import { IBreadcrumbItem, initializeIcons } from "@fluentui/react";
import { BaseTextBlock, ColorSetDefinition, EnumProperty, SubmitAction, TextColorDefinition } from 'adaptivecards';
import * as Enums from 'adaptivecards/lib/enums'
import * as Utils from 'adaptivecards/lib/utils'
initializeIcons()


export class Breadcrumb extends AC.CardElement {
  static readonly JsonTypeName = 'Breadcrumb';

  //#region Schema

  static readonly itemsProperty = new AC.StringProperty(AC.Versions.v1_2, 'items', true);
  static readonly sizeProperty = new EnumProperty(
    AC.Versions.v1_2,
    "size",
    Enums.TextSize,
    Enums.TextSize.Default);
    static readonly weightProperty = new EnumProperty(
    AC.Versions.v1_2,
    "weight",
    Enums.TextWeight,
    Enums.TextWeight.Default);
    static readonly fontTypeProperty = new EnumProperty(
    AC.Versions.v1_2,
    "fontType",
    Enums.FontType,
    Enums.FontType.Default);
    static readonly colorProperty = new EnumProperty(
    AC.Versions.v1_2,
    "color",
    Enums.TextColor,
    Enums.TextColor.Default);

  @AC.property(Breadcrumb.itemsProperty)
  get items(): string {
    return this.getValue(Breadcrumb.itemsProperty);
  }

  set items(value: string) {
    if (this.items !== value) {
      this.setValue(Breadcrumb.itemsProperty, value);

      this.updateLayout();
    }
  }

  @AC.property(Breadcrumb.sizeProperty)
  size: Enums.TextSize = Enums.TextSize.Default;

  @AC.property(Breadcrumb.weightProperty)
  weight: Enums.TextWeight = Enums.TextWeight.Default;

  @AC.property(Breadcrumb.fontTypeProperty)
    fontType?: Enums.FontType = Enums.FontType.Default;

  @AC.property(Breadcrumb.colorProperty)
    color: Enums.TextColor = Enums.TextColor.Default;


  //#endregion

  
  private _breadCrumbElement: JSX.Element;

  protected internalRender(): HTMLElement {

    this._breadCrumbElement = getBreadCrumbElement(this.items, this.getFontSize(), this.getFontWeight(), this.getColor(), this.customActionHandler.bind(this))

    const element = document.createElement("div");
    ReactDOM.render(this._breadCrumbElement, element);
    element.style.width = "100%";
    return element;
  }

  getColorDefinition(colorSet: ColorSetDefinition, color: Enums.TextColor): TextColorDefinition {
    switch (color) {
        case Enums.TextColor.Accent:
            return colorSet.accent;
        case Enums.TextColor.Dark:
            return colorSet.dark;
        case Enums.TextColor.Light:
            return colorSet.light;
        case Enums.TextColor.Good:
            return colorSet.good;
        case Enums.TextColor.Warning:
            return colorSet.warning;
        case Enums.TextColor.Attention:
            return colorSet.attention;
        default:
            return colorSet.default;
    }
}

get effectiveColor(): Enums.TextColor {
  return this.color ? this.color : Enums.TextColor.Default;
}

  getColor(): string {
    let colorDefinition = this.getColorDefinition(this.getEffectiveStyleDefinition().foregroundColors, this.effectiveColor);

    return <string>Utils.stringToCssColor(colorDefinition.default);

  }

  getFontSize(): string {
    let fontType = this.hostConfig.getFontTypeDefinition(this.fontType);

    let fontSize: number;

    switch (this.size) {
        case Enums.TextSize.Small:
            fontSize = fontType.fontSizes.small;
            break;
        case Enums.TextSize.Medium:
            fontSize = fontType.fontSizes.medium;
            break;
        case Enums.TextSize.Large:
            fontSize = fontType.fontSizes.large;
            break;
        case Enums.TextSize.ExtraLarge:
            fontSize = fontType.fontSizes.extraLarge;
            break;
        default:
            fontSize = fontType.fontSizes.default;
            break;
    }

    return fontSize + "px";
  }

  getFontWeight(): string {
    let fontType = this.hostConfig.getFontTypeDefinition(this.fontType);
    let fontWeight: number;

    switch (this.weight) {
      case Enums.TextWeight.Lighter:
          fontWeight = fontType.fontWeights.lighter;
          break;
      case Enums.TextWeight.Bolder:
          fontWeight = fontType.fontWeights.bolder;
          break;
      default:
          fontWeight = fontType.fontWeights.default;
          break;
  }

  return fontWeight.toString();
  }

  getJsonTypeName(): string {
    return Breadcrumb.JsonTypeName;
  }

  public customActionHandler(item: IBreadcrumbItem) : void {
    const submitAction = new SubmitAction();
    submitAction.data = item;
    //@ts-ignore
    return this.getRootElement().onExecuteAction(submitAction)
  }

  updateLayout(processChildren: boolean = true): void {
    super.updateLayout(processChildren);

    // if (this.renderedElement) {
    //   if (!this.items) {
    //     this._breadCrumbElement = null;
    //   } else {
    //     this._breadCrumbElement = getBreadCrumbElement(this.items, this.getFontSize(), this.getFontWeight(), this.customActionHandler.bind(this))
    //   }
    // }
  }
}