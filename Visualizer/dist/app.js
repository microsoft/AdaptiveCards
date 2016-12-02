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
    function HostContainer(styleSheet) {
        this.styleSheet = styleSheet;
    }
    return HostContainer;
}());
var LiveTileContainer = (function (_super) {
    __extends(LiveTileContainer, _super);
    function LiveTileContainer(width, height, styleSheet) {
        _super.call(this, styleSheet);
        this._width = width;
        this._height = height;
    }
    LiveTileContainer.prototype.render = function (card) {
        var element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        element.style.backgroundColor = LiveTileContainer.backgroundColor;
        element.style.overflow = "hidden";
        card.textColor = LiveTileContainer.textColor;
        ActionGroup.buttonStyle = ActionButtonStyle.Push;
        var renderedCard = card.render();
        renderedCard.style.height = "100%";
        appendChild(element, renderedCard);
        return element;
    };
    LiveTileContainer.backgroundColor = "#0078D7";
    LiveTileContainer.textColor = TextColor.Light;
    return LiveTileContainer;
}(HostContainer));
var ToastContainer = (function (_super) {
    __extends(ToastContainer, _super);
    function ToastContainer(width, styleSheet) {
        _super.call(this, styleSheet);
        this._width = width;
    }
    ToastContainer.prototype.render = function (card) {
        var element = document.createElement("div");
        element.style.border = "#474747 1px solid";
        element.style.width = this._width + "px";
        element.style.backgroundColor = ToastContainer.backgroundColor;
        element.style.overflow = "hidden";
        card.textColor = LiveTileContainer.textColor;
        ActionGroup.buttonStyle = ActionButtonStyle.Push;
        var renderedCard = card.render();
        appendChild(element, renderedCard);
        return element;
    };
    ToastContainer.backgroundColor = "#1F1F1F";
    ToastContainer.textColor = TextColor.Light;
    return ToastContainer;
}(HostContainer));
var OutlookConnectorContainer = (function (_super) {
    __extends(OutlookConnectorContainer, _super);
    function OutlookConnectorContainer(themeColor, styleSheet) {
        _super.call(this, styleSheet);
        this._themeColor = themeColor;
    }
    OutlookConnectorContainer.prototype.render = function (card) {
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
        ActionGroup.buttonStyle = ActionButtonStyle.Link;
        var renderedCard = card.render();
        appendChild(element, renderedCard);
        return element;
    };
    return OutlookConnectorContainer;
}(HostContainer));
var TeamsConnectorContainer = (function (_super) {
    __extends(TeamsConnectorContainer, _super);
    function TeamsConnectorContainer() {
        _super.apply(this, arguments);
    }
    TeamsConnectorContainer.prototype.render = function (card) {
        var element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";
        element.style.border = "1px solid #F1F1F1";
        ActionGroup.buttonStyle = ActionButtonStyle.Link;
        var renderedCard = card.render();
        appendChild(element, renderedCard);
        return element;
    };
    return TeamsConnectorContainer;
}(HostContainer));
var SkypeCardContainer = (function (_super) {
    __extends(SkypeCardContainer, _super);
    function SkypeCardContainer() {
        _super.apply(this, arguments);
    }
    SkypeCardContainer.prototype.render = function (card) {
        var element = document.createElement("div");
        ActionGroup.buttonStyle = ActionButtonStyle.Push;
        var renderedCard = card.render();
        appendChild(element, renderedCard);
        return element;
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
            case "AdaptiveCard":
                var adaptiveCard = new AdaptiveCard();
                adaptiveCard.parse(json);
                var hostContainer = hostContainerOptions[selectedHostContainerIndex].hostContainer;
                var renderedHostContainer = hostContainer.render(adaptiveCard);
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
function updateStyleSheet() {
    var styleSheetLinkElement = document.getElementById("adaptiveCardStylesheet");
    if (styleSheetLinkElement == null) {
        styleSheetLinkElement = document.createElement("link");
        styleSheetLinkElement.id = "adaptiveCardStylesheet";
        var headElement = document.getElementsByTagName("head")[0];
        appendChild(headElement, styleSheetLinkElement);
    }
    styleSheetLinkElement.rel = "stylesheet";
    styleSheetLinkElement.type = "text/css";
    styleSheetLinkElement.href = hostContainerOptions[selectedHostContainerIndex].hostContainer.styleSheet;
}
function hostContainerPickerChanged(evt) {
    var hostContainerPicker = document.getElementById("hostContainerPicker");
    selectedHostContainerIndex = hostContainerPicker.selectedIndex;
    updateStyleSheet();
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
    hostContainerOptions.push(new HostContainerOption("Outlook Connector Card", new OutlookConnectorContainer("red", "./css/outlookConnectorCard.css")));
    hostContainerOptions.push(new HostContainerOption("Teams Connector Card", new TeamsConnectorContainer("./css/teamsConnectorCard.css")));
    hostContainerOptions.push(new HostContainerOption("Toast", new ToastContainer(362, "./css/toast.css")));
    hostContainerOptions.push(new HostContainerOption("Large Live Tile", new LiveTileContainer(204, 204, "./css/liveTile.css")));
    hostContainerOptions.push(new HostContainerOption("Wide Live Tile", new LiveTileContainer(204, 100, "./css/liveTile.css")));
    hostContainerOptions.push(new HostContainerOption("Medium Live Tile", new LiveTileContainer(100, 100, "./css/liveTile.css")));
    hostContainerOptions.push(new HostContainerOption("Small Live Tile", new LiveTileContainer(48, 48, "./css/liveTile.css")));
    hostContainerOptions.push(new HostContainerOption("Skype Card", new SkypeCardContainer("./css/skypeCard.css")));
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
    updateStyleSheet();
    renderCard();
};
//# sourceMappingURL=app.js.map