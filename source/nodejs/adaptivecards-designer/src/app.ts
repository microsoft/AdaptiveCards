import * as Adaptive from "adaptivecards";
import * as Constants from "./constants";
import * as Designer from "./card-designer";

var designer: Designer.CardDesigner;

function buildPropertySheet(peer: Designer.CardElementPeer) {
    var propertySheetHost = document.getElementById("propertySheetHost");
    propertySheetHost.innerHTML = "";

    var card = peer.buildPropertySheetCard();

    propertySheetHost.appendChild(card.render());
}

window.onload = () => {
    Adaptive.AdaptiveCard.elementTypeRegistry.registerType("Input.TextPropertyInput", () => { return new Designer.ObservableTextInput(); });

    var card = new Adaptive.AdaptiveCard();
    card.parse(JSON.parse(Constants.defaultPayload));

    var designer = new Designer.CardDesigner(document.getElementById("designerHost"));
    designer.selectedPeerChanged = (peer: Designer.CardElementPeer) => { buildPropertySheet(peer); };
    designer.card = card;

    document.getElementById("deleteSelected").onclick = () => {
        designer.deleteSelected();
    }

    window.addEventListener('resize', function () {
        designer.updateLayout();
    });
};