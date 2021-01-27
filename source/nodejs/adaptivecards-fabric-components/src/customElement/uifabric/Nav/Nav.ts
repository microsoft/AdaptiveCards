// Below is sample json
// {
//     "type": "AdaptiveCard",
//     "body": [
//         {
//             "type": "Nav",
//             "groups": "[{\"links\":[{\"name\":\"Parent link 1\",\"url\":\"http:\/\/example.com\",\"target\":\"_blank\",\"expandAriaLabel\":\"Expand Parent link 1\",\"collapseAriaLabel\":\"Collapse Parent link 1\",\"links\":[{\"name\":\"Child link 1\",\"url\":\"http:\/\/example.com\",\"target\":\"_blank\"},{\"name\":\"Child link 2\",\"url\":\"http:\/\/example.com\",\"target\":\"_blank\",\"expandAriaLabel\":\"Expand Child link 2\",\"collapseAriaLabel\":\"Collapse Child link 2\",\"links\":[{\"name\":\"3rd level link 1\",\"url\":\"http:\/\/example.com\",\"target\":\"_blank\"},{\"name\":\"3rd level link 2\",\"url\":\"http:\/\/example.com\",\"target\":\"_blank\"}]},{\"name\":\"Child link 3\",\"url\":\"http:\/\/example.com\",\"target\":\"_blank\"}]},{\"name\":\"Parent link 2\",\"url\":\"http:\/\/example.com\",\"target\":\"_blank\",\"expandAriaLabel\":\"Expand Parent link 2\",\"collapseAriaLabel\":\"Collapse Parent link 2\",\"links\":[{\"name\":\"Child link 4\",\"url\":\"http:\/\/example.com\",\"target\":\"_blank\"}]}]}]"
//         }
//     ],
//     "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
//     "version": "1.3"
// }

import * as AC from 'adaptivecards';
import * as ReactDOM from "react-dom";
import {getNavElement} from "./NavElement"


export class Nav extends AC.CardElement {
  static readonly JsonTypeName = 'Nav';

  //#region Schema

  static readonly groups = new AC.StringProperty(AC.Versions.v1_2, 'groups', true);

  @AC.property(Nav.groups)
  get groups(): string {
    return this.getValue(Nav.groups);
  }

  set groups(value: string) {
    if (this.groups !== value) {
      this.setValue(Nav.groups, value);

      this.updateLayout();
    }
  }


  //#endregion

  private _navElement: JSX.Element;

  protected internalRender(): HTMLElement {

    this._navElement = getNavElement(this.groups)

    const element = document.createElement("div");
    ReactDOM.render(this._navElement, element);
    element.style.width = "100%";
    return element;
  }

  getJsonTypeName(): string {
    return Nav.JsonTypeName;
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