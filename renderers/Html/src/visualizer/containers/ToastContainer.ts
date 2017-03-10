import { HostContainer} from "./HostContainer";
import * as Adaptive from "../../Adaptive";
import * as Utils from "../../Utils";

export class ToastContainer extends HostContainer {
    static backgroundColor: string = "#1F1F1F";
    static textColor: Adaptive.TextColor = Adaptive.TextColor.Light;

    private _width: number;

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
    }

    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.actionShowCardInPopup = false;
        Adaptive.AdaptiveCard.renderOptions.defaultActionButtonStyle = Adaptive.ActionButtonStyle.Push;
        Adaptive.AdaptiveCard.renderOptions.defaultTextColor = Adaptive.TextColor.Light;
    }

    render(card: Adaptive.AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.border = "#474747 1px solid";
        element.style.width = this._width + "px";
        element.style.backgroundColor = ToastContainer.backgroundColor;
        element.style.overflow = "hidden";
        

        // TODO: Bring this back once the Toast schema is ready

        // if (card.title != undefined || card.description1 != undefined) {
        //     let headerElement = document.createElement("div");
        //     headerElement.className = "headerContainer";

        //     let html: string = '';
        //     html += '<div style="flex: 0 0 auto; margin-right: 10px;">';
        //     html += '  <img class="image autoSize" style="overflow: hidden; margin-top: 0px;" src="./assets/appicon.png"/>';
        //     html += '</div>';

        //     html += '<div style="flex: 1 1 100%">';

        //     if (card.title != undefined) {
        //         html += '  <div class="text defaultSize lightColor">' + card.title + '</div>';
        //     }

        //     if (card.description1 != undefined) {
        //         html += '  <div class="text defaultSize lightColor `sub`tle">' + card.description1 + '</div>';
        //     }

        //     if (card.description2 != undefined) {
        //         html += '  <div class="text small lightColor subtle">' + card.description2 + '</div>';
        //     }

        //     html += '</div>';

        //     headerElement.innerHTML = html;

        //     appendChild(element, headerElement);
        // }

        card.root.textColor = ToastContainer.textColor;

        let renderedCard = card.render();

        Utils.appendChild(element, renderedCard);
        let hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, super.render(card));
        return hostDiv;
    }
}