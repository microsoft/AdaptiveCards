// Below is sample json
// {
//     "type": "AdaptiveCard",
//     "body": [
//         {
//             "type": "Icon",
//             "iconName": "WindowsLogo"
//         }
//     ],
//     "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
//     "version": "1.3"
// }

import * as AC from 'adaptivecards';
import * as ReactDOM from "react-dom";
import {getIconElement} from "./IconElement"


export class Icon extends AC.CardElement {
  static readonly JsonTypeName = 'Icon';

  //#region Schema

  static readonly iconName = new AC.StringProperty(AC.Versions.v1_2, 'iconName', true);

  @AC.property(Icon.iconName)
  get iconName(): string | undefined {
    return this.getValue(Icon.iconName);
  }

  set iconName(value: string) {
    if (this.iconName !== value) {
      this.setValue(Icon.iconName, value);

      this.updateLayout();
    }
  }


  //#endregion

  private _iconElement: JSX.Element;

  protected internalRender(): HTMLElement {

    this._iconElement = getIconElement(this.iconName)

    const element = document.createElement("div");
    ReactDOM.render(this._iconElement, element);
    element.style.width = "100%";
    return element;
  }

  getJsonTypeName(): string {
    return Icon.JsonTypeName;
  }

  updateLayout(processChildren: boolean = true) {
    super.updateLayout(processChildren);

    // if (this.renderedElement) {
    //   if (!this.iconName) {
    //     this._iconElement = null;
    //   } else {
    //     this._iconElement = getIconElement(this.iconName)
    //   }
    // }
  }
}