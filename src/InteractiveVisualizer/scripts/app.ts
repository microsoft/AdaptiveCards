var editor;
var markdownProcessor;
var hostContainerOptions: Array<HostContainerOption> = [];
var selectedHostContainerIndex: number = 0;

abstract class HostContainer {
    protected _padding: Spacing = Spacing.None;

    constructor(padding: Spacing) {
        this._padding = padding;
    }

    initializeCard(card: AdaptiveCard) {
        card.padding = this._padding;
    }

    abstract render(): HTMLElement;
}

class LiveTileContainer extends HostContainer {
    static backgroundColor: string = "#0078D7";
    static textColor: TextColor = TextColor.Light;

    private _width: number;
    private _height: number;

    constructor(width: number, height: number, padding: Spacing) {
        super(padding);

        this._width = width;
        this._height = height;
    }

    initializeCard(card: AdaptiveCard) {
        super.initializeCard(card);

        card.textColor = LiveTileContainer.textColor;
    }

    render(): HTMLElement {
        let element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        element.style.backgroundColor = LiveTileContainer.backgroundColor;
        element.style.overflow = "hidden";

        return element;
    }
}

class ConnectorContainer extends HostContainer {
    private _themeColor: string;

    constructor(themeColor: string, padding: Spacing) {
        super(padding);

        this._themeColor = themeColor;
    }

    render(): HTMLElement {
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

        return element;
    }
}

class SkypeCardContainer extends HostContainer {
    render(): HTMLElement {
        return document.createElement("div");
    }
}

function renderCard() {
    try {
        let json = JSON.parse(editor.getValue());
        let cardTypeName = json["@type"];

        let node = document.getElementById('content');
        node.innerHTML = '';

        switch (cardTypeName) {
            case "SwiftCard":
            case "MessageCard":
                let swiftCard = new MessageCard();
                swiftCard.parse(json);

                node.appendChild(swiftCard.render());
                
                break;
            case "AdaptiveCard":
                let adaptiveCard = new AdaptiveCard();
                adaptiveCard.parse(json);

                let hostContainer = hostContainerOptions[selectedHostContainerIndex].hostContainer;
                hostContainer.initializeCard(adaptiveCard);

                let renderedHostContainer = hostContainer.render();
                renderedHostContainer.appendChild(adaptiveCard.render());

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

function hostContainerPickerChanged(evt) {
    let hostContainerPicker = document.getElementById("hostContainerPicker") as HTMLSelectElement;

    selectedHostContainerIndex = hostContainerPicker.selectedIndex;

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
            "Connector Card",
            new ConnectorContainer("red", Spacing.Wide)));
    hostContainerOptions.push(
        new HostContainerOption(
            "Large Live Tile",
            new LiveTileContainer(204, 204, Spacing.Narrow)));
    hostContainerOptions.push(
        new HostContainerOption(
            "Wide Live Tile",
            new LiveTileContainer(204, 100, Spacing.Narrow)));
    hostContainerOptions.push(
        new HostContainerOption(
            "Medium Live Tile",
            new LiveTileContainer(100, 100, Spacing.Narrow)));
    hostContainerOptions.push(
        new HostContainerOption(
            "Small Live Tile",
            new LiveTileContainer(48, 48, Spacing.Narrow)));
    hostContainerOptions.push(
        new HostContainerOption(
            "Skype Card",
            new SkypeCardContainer(Spacing.None)));

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

    renderCard();
};