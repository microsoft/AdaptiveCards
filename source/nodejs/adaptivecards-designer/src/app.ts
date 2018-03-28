import * as Adaptive from "adaptivecards";
import * as Constants from "./constants";
import * as Designer from "./card-designer";

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

class PaletteItem extends Designer.DraggableElement {
    protected internalRender(): HTMLElement {
        var element = document.createElement("div");
        element.classList.add("acd-palette-item");
        element.innerText = this.typeRegistration.typeName;

        return element;
    }

    readonly typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>;

    constructor(typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>) {
        super();

        this.typeRegistration = typeRegistration;
    }

    cloneElement(): HTMLElement {
        return this.internalRender();
    }
}

var designer: Designer.CardDesigner;
var draggedPaletteItem: PaletteItem;
var draggedElement: HTMLElement;
var currentMousePosition: Designer.IPoint;

window.onload = () => {
    Adaptive.AdaptiveCard.elementTypeRegistry.registerType("ActionSet", () => { return new Adaptive.ActionSet(); });
    Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.Http", () => { return new Adaptive.HttpAction(); });
    Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.ToggleVisibility", () => { return new ToggleVisibilityAction(); });

    for (var i = 0; i < Adaptive.AdaptiveCard.elementTypeRegistry.getItemCount(); i++) {
        var paletteItem = new PaletteItem(Adaptive.AdaptiveCard.elementTypeRegistry.getItemAt(i));
        paletteItem.render();
        paletteItem.onStartDrag = (sender: PaletteItem) => {
            document.getElementById("paletteStatus").innerText = "Start drag: " + sender.typeRegistration.typeName;

            draggedPaletteItem = sender;

            draggedElement = sender.cloneElement();
            draggedElement.style.position = "absolute";
            draggedElement.style.left = currentMousePosition.x + "px";
            draggedElement.style.top = currentMousePosition.y + "px";

            document.body.appendChild(draggedElement);
        }

        paletteItem.onEndDrag = (sender: PaletteItem) => {
            document.getElementById("paletteStatus").innerText = "End drag";

            draggedElement.remove();
            draggedPaletteItem = null;
        }
    
        document.getElementById("toolPalette").appendChild(paletteItem.renderedElement);
    }

    var card = new Adaptive.AdaptiveCard();
    card.designMode = true;
    card.parse(JSON.parse(Constants.defaultPayload));

    var designer = new Designer.CardDesigner(document.getElementById("designerHost"));
    designer.onSelectedPeerChanged = (peer: Designer.CardElementPeer) => {
        buildPropertySheet(peer);
        buildCommandList(peer);
    };
    designer.card = card;

    window.addEventListener('resize',
        () => {
            designer.updateLayout();
        });

    window.addEventListener('mousemove',
        (e: MouseEvent) => {
            currentMousePosition = { x: e.x, y: e.y };

            if (draggedElement) {
                draggedElement.style.left = currentMousePosition.x + "px";
                draggedElement.style.top = currentMousePosition.y + "px";
            }
        });
};