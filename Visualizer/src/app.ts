var editor;
var markdownProcessor;
var hostContainerOptions: Array<HostContainerOption> = [];
var selectedHostContainerIndex: number = 0;

abstract class HostContainer {
    constructor(styleSheet: string) {
        this.styleSheet = styleSheet;
    }

    abstract render(card: AdaptiveCard): HTMLElement;

    readonly styleSheet: string;
}

class LiveTileContainer extends HostContainer {
    static backgroundColor: string = "#0078D7";
    static textColor: TextColor = TextColor.Light;

    private _width: number;
    private _height: number;

    constructor(width: number, height: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
        this._height = height;
    }

    render(card: AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        element.style.backgroundColor = LiveTileContainer.backgroundColor;
        element.style.overflow = "hidden";

        card.textColor = LiveTileContainer.textColor;

        ActionGroup.buttonStyle = ActionButtonStyle.Push;

        let renderedCard = card.render();
        renderedCard.style.height = "100%";

        appendChild(element, renderedCard);

        return element;
    }
}

class ToastContainer extends HostContainer {
    static backgroundColor: string = "#1F1F1F";
    static textColor: TextColor = TextColor.Light;

    private _width: number;

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
    }

    render(card: AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.border = "#474747 1px solid";
        element.style.width = this._width + "px";
        element.style.backgroundColor = ToastContainer.backgroundColor;
        element.style.overflow = "hidden";

        card.textColor = LiveTileContainer.textColor;

        ActionGroup.buttonStyle = ActionButtonStyle.Push;

        let renderedCard = card.render();

        appendChild(element, renderedCard);

        return element;
    }
}

class OutlookConnectorContainer extends HostContainer {
    private _themeColor: string;

    constructor(themeColor: string, styleSheet: string) {
        super(styleSheet);

        this._themeColor = themeColor;
    }

    render(card: AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";

        if (isNullOrEmpty(this._themeColor)) {
            element.style.border = "1px solid #F1F1F1"
        }
        else {
            element.style.borderLeft = "3px solid " + this._themeColor;
        }

        ActionGroup.buttonStyle = ActionButtonStyle.Link;

        let renderedCard = card.render();

        appendChild(element, renderedCard);

        return element;
    }
}

class TeamsConnectorContainer extends HostContainer {
    render(card: AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";
        element.style.border = "1px solid #F1F1F1"

        ActionGroup.buttonStyle = ActionButtonStyle.Link;

        let renderedCard = card.render();

        appendChild(element, renderedCard);

        return element;
    }
}

class SkypeCardContainer extends HostContainer {
    render(card: AdaptiveCard): HTMLElement {
        let element = document.createElement("div");

        ActionGroup.buttonStyle = ActionButtonStyle.Push;

        let renderedCard = card.render();

        appendChild(element, renderedCard);

        return element;
    }
}

function renderCard() {
    try {
        let json = JSON.parse(editor.getValue());
        let cardTypeName = json["@type"];

        let node = document.getElementById('content');
        node.innerHTML = '';

        switch (cardTypeName) {
            case "AdaptiveCard":
                let adaptiveCard = new AdaptiveCard();
                adaptiveCard.parse(json);

                let hostContainer = hostContainerOptions[selectedHostContainerIndex].hostContainer;
                let renderedHostContainer = hostContainer.render(adaptiveCard);

                node.appendChild(renderedHostContainer);

                break;
            default:
                if (isNullOrEmpty(cardTypeName)) {
                    throw new Error("The card's type must be specified.");
                }
                else {
                    throw new Error("Unknown card type: " + cardTypeName);
                }
        }
    }
    catch (e) {
        document.getElementById('content').innerHTML = "Error: " + e.toString();
    }
}

function textareaChange() {
    renderCard();
}

function openFilePicker(){
    document.getElementById("filePicker").click();
}

function filePickerChanged(evt) {
    let filePicker = document.getElementById("filePicker") as HTMLInputElement;

    let file = filePicker.files[0]; 

    if (file) {
        let reader = new FileReader();

        reader.onload = function(e: ProgressEvent) {
            editor.session.setValue((e.target as FileReader).result);
        }

        reader.readAsText(file);
    }
    else { 
        alert("Failed to load file");
    }
}

function updateStyleSheet() {
    let styleSheetLinkElement = <HTMLLinkElement>document.getElementById("adaptiveCardStylesheet");

    if (styleSheetLinkElement == null) {
        styleSheetLinkElement = document.createElement("link");
        styleSheetLinkElement.id = "adaptiveCardStylesheet";

        let headElement = document.getElementsByTagName("head")[0];
        appendChild(headElement, styleSheetLinkElement);
    }

    styleSheetLinkElement.rel = "stylesheet";
    styleSheetLinkElement.type = "text/css";
    styleSheetLinkElement.href = hostContainerOptions[selectedHostContainerIndex].hostContainer.styleSheet;
}

function hostContainerPickerChanged(evt) {
    let hostContainerPicker = document.getElementById("hostContainerPicker") as HTMLSelectElement;

    selectedHostContainerIndex = hostContainerPicker.selectedIndex;

    updateStyleSheet();

    renderCard();
}

function processMarkdown(text: string): any {
    return markdownProcessor.render(text);
}

class HostContainerOption {
    readonly name: string;
    readonly hostContainer: HostContainer;

    constructor(name: string, hostContainer: HostContainer) {
        this.name = name;
        this.hostContainer = hostContainer;
    }
}

window.onload = () => {
    hostContainerOptions.push(
        new HostContainerOption(
            "Outlook Connector Card",
            new OutlookConnectorContainer("red", "./css/outlookConnectorCard.css")));
    hostContainerOptions.push(
        new HostContainerOption(
            "Teams Connector Card",
            new TeamsConnectorContainer("./css/teamsConnectorCard.css")));
    hostContainerOptions.push(
        new HostContainerOption(
            "Toast",
            new ToastContainer(362, "./css/toast.css")));
    hostContainerOptions.push(
        new HostContainerOption(
            "Large Live Tile",
            new LiveTileContainer(204, 204, "./css/liveTile.css")));
    hostContainerOptions.push(
        new HostContainerOption(
            "Wide Live Tile",
            new LiveTileContainer(204, 100, "./css/liveTile.css")));
    hostContainerOptions.push(
        new HostContainerOption(
            "Medium Live Tile",
            new LiveTileContainer(100, 100, "./css/liveTile.css")));
    hostContainerOptions.push(
        new HostContainerOption(
            "Small Live Tile",
            new LiveTileContainer(48, 48, "./css/liveTile.css")));
    hostContainerOptions.push(
        new HostContainerOption(
            "Skype Card",
            new SkypeCardContainer("./css/skypeCard.css")));

    let hostContainerPicker = <HTMLSelectElement>document.getElementById("hostContainerPicker");

    if (hostContainerPicker) {
        hostContainerPicker.addEventListener("change", hostContainerPickerChanged);

        for (let i = 0; i < hostContainerOptions.length; i++) {
            let option = document.createElement("option");
            option.text = hostContainerOptions[i].name;

            appendChild(hostContainerPicker, option);
        }
    }

    let filePicker = document.getElementById("filePicker");
    filePicker.addEventListener("change", filePickerChanged);

    updateStyleSheet();

    renderCard();
};