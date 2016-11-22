var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
var editor;
var markdownProcessor;
var hostContainerOptions = [];
var selectedHostContainerIndex = 0;
var HostContainer = (function () {
    function HostContainer(padding) {
        this._padding = Spacing.None;
        this._padding = padding;
    }
    HostContainer.prototype.initializeCard = function (card) {
        card.padding = this._padding;
    };
    return HostContainer;
}());
var LiveTileContainer = (function (_super) {
    __extends(LiveTileContainer, _super);
    function LiveTileContainer(width, height, padding) {
        _super.call(this, padding);
        this._width = width;
        this._height = height;
    }
    LiveTileContainer.prototype.initializeCard = function (card) {
        _super.prototype.initializeCard.call(this, card);
        card.textColor = LiveTileContainer.textColor;
    };
    LiveTileContainer.prototype.render = function () {
        var element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        element.style.backgroundColor = LiveTileContainer.backgroundColor;
        element.style.overflow = "hidden";
        return element;
    };
    LiveTileContainer.backgroundColor = "#0078D7";
    LiveTileContainer.textColor = TextColor.Light;
    return LiveTileContainer;
}(HostContainer));
var ConnectorContainer = (function (_super) {
    __extends(ConnectorContainer, _super);
    function ConnectorContainer(themeColor, padding) {
        _super.call(this, padding);
        this._themeColor = themeColor;
    }
    ConnectorContainer.prototype.render = function () {
        var element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";
        if (isNullOrEmpty(this._themeColor)) {
            element.style.border = "1px solid #F1F1F1";
        }
        else {
            element.style.borderLeft = "3px solid " + this._themeColor;
        }
        return element;
    };
    return ConnectorContainer;
}(HostContainer));
var SkypeCardContainer = (function (_super) {
    __extends(SkypeCardContainer, _super);
    function SkypeCardContainer() {
        _super.apply(this, arguments);
    }
    SkypeCardContainer.prototype.render = function () {
        return document.createElement("div");
    };
    return SkypeCardContainer;
}(HostContainer));
function renderCard() {
    try {
        var json = JSON.parse(editor.getValue());
        var cardTypeName = json["@type"];
        var node = document.getElementById('content');
        node.innerHTML = '';
        switch (cardTypeName) {
            case "SwiftCard":
            case "MessageCard":
                var swiftCard = new MessageCard();
                swiftCard.parse(json);
                node.appendChild(swiftCard.render());
                break;
            case "AdaptiveCard":
                var adaptiveCard = new AdaptiveCard();
                adaptiveCard.parse(json);
                var hostContainer = hostContainerOptions[selectedHostContainerIndex].hostContainer;
                hostContainer.initializeCard(adaptiveCard);
                var renderedHostContainer = hostContainer.render();
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
function openFilePicker() {
    document.getElementById("filePicker").click();
}
function filePickerChanged(evt) {
    var filePicker = document.getElementById("filePicker");
    var file = filePicker.files[0];
    if (file) {
        var reader = new FileReader();
        reader.onload = function (e) {
            editor.session.setValue(e.target.result);
        };
        reader.readAsText(file);
    }
    else {
        alert("Failed to load file");
    }
}
function hostContainerPickerChanged(evt) {
    var hostContainerPicker = document.getElementById("hostContainerPicker");
    selectedHostContainerIndex = hostContainerPicker.selectedIndex;
    renderCard();
}
function processMarkdown(text) {
    return markdownProcessor.render(text);
}
var HostContainerOption = (function () {
    function HostContainerOption(name, hostContainer) {
        this.name = name;
        this.hostContainer = hostContainer;
    }
    return HostContainerOption;
}());
window.onload = function () {
    hostContainerOptions.push(new HostContainerOption("Connector Card", new ConnectorContainer("red", Spacing.Wide)));
    hostContainerOptions.push(new HostContainerOption("Large Live Tile", new LiveTileContainer(204, 204, Spacing.Narrow)));
    hostContainerOptions.push(new HostContainerOption("Wide Live Tile", new LiveTileContainer(204, 100, Spacing.Narrow)));
    hostContainerOptions.push(new HostContainerOption("Medium Live Tile", new LiveTileContainer(100, 100, Spacing.Narrow)));
    hostContainerOptions.push(new HostContainerOption("Small Live Tile", new LiveTileContainer(48, 48, Spacing.Narrow)));
    hostContainerOptions.push(new HostContainerOption("Skype Card", new SkypeCardContainer(Spacing.None)));
    var hostContainerPicker = document.getElementById("hostContainerPicker");
    if (hostContainerPicker) {
        hostContainerPicker.addEventListener("change", hostContainerPickerChanged);
        for (var i = 0; i < hostContainerOptions.length; i++) {
            var option = document.createElement("option");
            option.text = hostContainerOptions[i].name;
            appendChild(hostContainerPicker, option);
        }
    }
    var filePicker = document.getElementById("filePicker");
    filePicker.addEventListener("change", filePickerChanged);
    renderCard();
};
//# sourceMappingURL=app.js.map