// Below is sample json
// {
//     "type": "AdaptiveCard",
//     "body": [
//         {
//             "type": "Spinner",
//             "size": "medium"
//         }
//     ],
//     "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
//     "version": "1.3"
// }

import * as AC from 'adaptivecards';
import * as ReactDOM from "react-dom";
import {getSpinnerElement} from "./SpinnerElement"


export class Spinner extends AC.CardElement {
  static readonly JsonTypeName = 'Spinner';

  //#region Schema

  static readonly size = new AC.StringProperty(AC.Versions.v1_2, 'size', true);

  @AC.property(Spinner.size)
  get size(): string {
    return this.getValue(Spinner.size);
  }

  set size(value: string) {
    if (this.size !== value) {
      this.setValue(Spinner.size, value);

      this.updateLayout();
    }
  }


  //#endregion

  private _spinnerElement: JSX.Element;

  protected internalRender(): HTMLElement {

    this._spinnerElement = getSpinnerElement(this.size)

    const element = document.createElement("div");
    ReactDOM.render(this._spinnerElement, element);
    element.style.width = "100%";
    return element;
  }

  getJsonTypeName(): string {
    return Spinner.JsonTypeName;
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