// Below is sample json
// {
//     "type": "AdaptiveCard",
//     "body": [
//         {
//             "type": "ProgressIndicator",
//             "label": "Indicator",
//              "description": "Loading details"
//         }
//     ],
//     "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
//     "version": "1.3"
// }

import * as AC from 'adaptivecards';
import * as ReactDOM from "react-dom";
import {getProgressIndicatorElement} from "./ProgressIndicatorElement"


export class ProgressIndicator extends AC.CardElement {
  static readonly JsonTypeName = 'ProgressIndicator';

  //#region Schema

  static readonly label = new AC.StringProperty(AC.Versions.v1_2, 'label', true);
  static readonly description = new AC.StringProperty(AC.Versions.v1_2, 'description', true);

  @AC.property(ProgressIndicator.label)
  get label(): string {
    return this.getValue(ProgressIndicator.label);
  }

  set label(value: string) {
    if (this.label !== value) {
      this.setValue(ProgressIndicator.label, value);

      this.updateLayout();
    }
  }

  @AC.property(ProgressIndicator.description)
  get description(): string {
    return this.getValue(ProgressIndicator.description);
  }

  set description(value: string) {
    if (this.description !== value) {
      this.setValue(ProgressIndicator.description, value);

      this.updateLayout();
    }
  }


  //#endregion

  private _progressIndicatorElement: JSX.Element;

  protected internalRender(): HTMLElement {

    this._progressIndicatorElement = getProgressIndicatorElement(this.label, this.description)

    const element = document.createElement("div");
    ReactDOM.render(this._progressIndicatorElement, element);
    element.style.width = "100%";
    return element;
  }

  getJsonTypeName(): string {
    return ProgressIndicator.JsonTypeName;
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