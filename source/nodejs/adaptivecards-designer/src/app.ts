import * as Adaptive from "adaptivecards";
import * as Constants from "./constants";
import * as Designer from "./card-designer";

var designer: Designer.CardDesigner;

function buildPropertySheet(peer: Designer.DesignerPeer) {
    var propertySheetHost = document.getElementById("propertySheetHost");
    propertySheetHost.innerHTML = "";

    if (peer) {
        var card = peer.buildPropertySheetCard();

        propertySheetHost.appendChild(card.render());
    }
}

function buildCommandList(peer: Designer.DesignerPeer) {
    var commandsHost = document.getElementById("commandsHost");
    commandsHost.innerHTML = "";

    if (peer) {
        var commands = peer.getCommands();

        for (var i = 0; i < commands.length; i++) {
            let button = document.createElement("button");
            button.type = "button";
            button.innerText = commands[i].name;

            let command = commands[i];

            button.onclick = () => { command.execute(); };

            commandsHost.appendChild(button);
        }
    }
}

export class ToggleVisibilityAction extends Adaptive.Action {
    targetElementIds: Array<string> = [];

    getJsonTypeName(): string {
        return "Action.ToggleVisibility";
    }

    execute() {
        if (this.targetElementIds) {
            for (var i = 0; i < this.targetElementIds.length; i++) {
                var targetElement = this.parent.getRootElement().getElementById(this.targetElementIds[i]);

                if (targetElement) {
                    targetElement.isVisible = !targetElement.isVisible;
                }
            }
        }
    }

    parse(json: any) {
        super.parse(json);

        this.targetElementIds = json["targetElements"] as Array<string>;
    }
}

window.onload = () => {
    Adaptive.AdaptiveCard.elementTypeRegistry.registerType("ActionSet", () => { return new Adaptive.ActionSet(); });
    Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.Http", () => { return new Adaptive.HttpAction(); });
    Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.ToggleVisibility", () => { return new ToggleVisibilityAction(); });

    var card = new Adaptive.AdaptiveCard();
    card.designMode = true;
    card.parse(JSON.parse(Constants.defaultPayload));

    var designer = new Designer.CardDesigner(document.getElementById("designerHost"));
    designer.onSelectedPeerChanged = (peer: Designer.CardElementPeer) => {
        buildPropertySheet(peer);
        buildCommandList(peer);
    };
    designer.card = card;

    window.addEventListener('resize', function () {
        designer.updateLayout();
    });
};