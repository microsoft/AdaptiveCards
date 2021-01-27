// Below is sample json
// {
//     "type": "AdaptiveCard",
//     "body": [
//         {
//             "type": "Persona",
//             "personaProps": "{\"imageUrl\":\"https:\/\/static2.sharepointonline.com\/files\/fabric\/office-ui-fabric-react-assets\/persona-female.png\",\"imageInitials\":\"AL\",\"text\":\"Annie Lindqvist\",\"secondaryText\":\"Software Engineer\",\"tertiaryText\":\"In a meeting\",\"optionalText\":\"Available at 4:00pm\",\"size\": \"size120\", \"presence\": \"online\"}"
//         }
//     ],
//     "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
//     "version": "1.3"
// }

import * as AC from 'adaptivecards';
import * as ReactDOM from "react-dom";
import {getPersonaElement} from "./PersonaElement"


export class Persona extends AC.CardElement {
  static readonly JsonTypeName = 'Persona';

  //#region Schema

  static readonly personaProps = new AC.StringProperty(AC.Versions.v1_2, 'personaProps', true);

  @AC.property(Persona.personaProps)
  get personaProps(): string {
    return this.getValue(Persona.personaProps);
  }

  set personaProps(value: string) {
    if (this.personaProps !== value) {
      this.setValue(Persona.personaProps, value);

      this.updateLayout();
    }
  }


  //#endregion

  private _personaElement: JSX.Element;

  protected internalRender(): HTMLElement {

    this._personaElement = getPersonaElement(this.personaProps)

    const element = document.createElement("div");
    ReactDOM.render(this._personaElement, element);
    element.style.width = "100%";
    return element;
  }

  getJsonTypeName(): string {
    return Persona.JsonTypeName;
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