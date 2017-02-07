import { HostContainer} from "./HostContainer";
import * as Adaptive from "../../Adaptive";

export abstract class ConnectorContainer extends HostContainer {
    renderHeader(card: Adaptive.AdaptiveCard): HTMLElement {
        let headerElement: HTMLElement = null;
        // if (card.title != undefined || card.description1 != undefined) {
        //     headerElement = document.createElement("div");
        //     headerElement.className = "headerContainer";

        //     let html = '<div>';
        //     let spaceNeeded = false;

        //     if (card.title != undefined) {
        //         html += '  <div class="text medium bolder defaultColor">' + card.title + '</div>';

        //         spaceNeeded = true;
        //     }

        //     if (card.description1 != undefined) {
        //         html += '  <div class="text defaultSize defaultColor"';

        //         if (spaceNeeded) {
        //             html += ' style="padding-top: 16px;"';
        //         }

        //         html += '>' + card.description1 + '</div>';
        //     }

        //     if (card.description2 != undefined) {
        //         html += '  <div class="text defaultSize defaultColor subtle">' + card.description2 + '</div>';
        //     }

        //     html += '</div>';

        //     headerElement.innerHTML = html;
        // }

        return headerElement;
    }
}