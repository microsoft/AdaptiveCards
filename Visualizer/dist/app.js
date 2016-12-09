"use strict";
var __extends = (this && this.__extends) || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
};
var adaptiveCard_1 = require("./adaptiveCard");
var constants_1 = require("./constants");
var ace = require("brace");
require("brace/mode/json");
require("brace/theme/chrome");
var editor;
var hostContainerOptions = [];
var hostContainerPicker;
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
        adaptiveCard_1.ActionGroup.buttonStyle = adaptiveCard_1.ActionButtonStyle.Push;
        var renderedCard = card.render();
        renderedCard.style.height = "100%";
        adaptiveCard_1.appendChild(element, renderedCard);
        return element;
    };
    LiveTileContainer.backgroundColor = "#0078D7";
    LiveTileContainer.textColor = adaptiveCard_1.TextColor.Light;
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
        adaptiveCard_1.ActionGroup.buttonStyle = adaptiveCard_1.ActionButtonStyle.Push;
        var renderedCard = card.render();
        adaptiveCard_1.appendChild(element, renderedCard);
        return element;
    };
    ToastContainer.backgroundColor = "#1F1F1F";
    ToastContainer.textColor = adaptiveCard_1.TextColor.Light;
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
        if (adaptiveCard_1.isNullOrEmpty(this._themeColor)) {
            element.style.border = "1px solid #F1F1F1";
        }
        else {
            element.style.borderLeft = "3px solid " + this._themeColor;
        }
        adaptiveCard_1.ActionGroup.buttonStyle = adaptiveCard_1.ActionButtonStyle.Link;
        var renderedCard = card.render();
        adaptiveCard_1.appendChild(element, renderedCard);
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
        adaptiveCard_1.ActionGroup.buttonStyle = adaptiveCard_1.ActionButtonStyle.Link;
        var renderedCard = card.render();
        adaptiveCard_1.appendChild(element, renderedCard);
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
        element.className = "skypeContainer";
        // Draw the hexagon bot logo
        var botElement = document.createElement("div");
        botElement.className = "hexagon";
        var botElementIn1 = document.createElement("div");
        botElementIn1.className = "hexagon-in1";
        botElement.appendChild(botElementIn1);
        var botElementIn2 = document.createElement("div");
        botElementIn2.className = "hexagon-in2";
        botElementIn1.appendChild(botElementIn2);
        adaptiveCard_1.ActionGroup.buttonStyle = adaptiveCard_1.ActionButtonStyle.Push;
        var renderedCard = card.render();
        adaptiveCard_1.appendChild(element, botElement);
        adaptiveCard_1.appendChild(element, renderedCard);
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
                var adaptiveCard = new adaptiveCard_1.AdaptiveCard();
                adaptiveCard.parse(json);
                var hostContainer = hostContainerOptions[hostContainerPicker.selectedIndex].hostContainer;
                var renderedHostContainer = hostContainer.render(adaptiveCard);
                node.appendChild(renderedHostContainer);
                try {
                    sessionStorage.setItem("AdaptivePayload", editor.getValue());
                }
                catch (e2) {
                    console.log("Unable to cache payload");
                }
                break;
            default:
                if (adaptiveCard_1.isNullOrEmpty(cardTypeName)) {
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
        adaptiveCard_1.appendChild(headElement, styleSheetLinkElement);
    }
    styleSheetLinkElement.rel = "stylesheet";
    styleSheetLinkElement.type = "text/css";
    styleSheetLinkElement.href = hostContainerOptions[hostContainerPicker.selectedIndex].hostContainer.styleSheet;
}
function getParameterByName(name, url) {
    if (!url) {
        url = window.location.href;
    }
    name = name.replace(/[\[\]]/g, "\\$&");
    var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"), results = regex.exec(url);
    if (!results)
        return null;
    if (!results[2])
        return '';
    return decodeURIComponent(results[2].replace(/\+/g, " "));
}
var HostContainerOption = (function () {
    function HostContainerOption(name, hostContainer) {
        this.name = name;
        this.hostContainer = hostContainer;
    }
    return HostContainerOption;
}());
function setupEditor() {
    editor = ace.edit("editor");
    editor.setTheme("ace/theme/chrome");
    editor.setOptions({
        "showPrintMargin": false,
        "displayIndentGuides": false,
        "showFoldWidgets": true,
        "highlightSelectedWord": false,
        "fontSize": "14px",
    });
    editor.getSession().setMode("ace/mode/json");
    editor.getSession().on("change", function (e) { renderCard(); });
    // Load the cached payload if the user had one
    try {
        var cachedPayload = sessionStorage.getItem("AdaptivePayload");
        if (cachedPayload) {
            editor.session.setValue(cachedPayload);
        }
        else {
            editor.session.setValue(constants_1.defaultPayload);
        }
    }
    catch (e) {
        editor.session.setValue(constants_1.defaultPayload);
    }
}
function setupContainerPicker() {
    hostContainerOptions.push(new HostContainerOption("Outlook Connector Card", new OutlookConnectorContainer("red", "./css/outlookConnectorCard.css")));
    hostContainerOptions.push(new HostContainerOption("Teams Connector Card", new TeamsConnectorContainer("./css/teamsConnectorCard.css")));
    hostContainerOptions.push(new HostContainerOption("Toast", new ToastContainer(362, "./css/toast.css")));
    hostContainerOptions.push(new HostContainerOption("Large Live Tile", new LiveTileContainer(310, 310, "./css/liveTile.css")));
    /*
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
    */
    hostContainerOptions.push(new HostContainerOption("Skype Card", new SkypeCardContainer("./css/skypeCard.css")));
    if (hostContainerPicker) {
        hostContainerPicker.addEventListener("change", function () {
            // update the query string
            history.pushState(hostContainerPicker.value, "Visualizer - " + hostContainerPicker.value, "index.html?hostApp=" + hostContainerPicker.value);
            renderSelectedHostApp();
        });
        for (var i = 0; i < hostContainerOptions.length; i++) {
            var option = document.createElement("option");
            option.value = hostContainerOptions[i].name;
            option.text = hostContainerOptions[i].name;
            hostContainerPicker.appendChild(option);
        }
    }
    setContainerAppFromUrl();
}
function setContainerAppFromUrl() {
    var requestedHostApp = getParameterByName("hostApp", null);
    if (requestedHostApp) {
        console.log("Setting host app to " + requestedHostApp);
        hostContainerPicker.value = requestedHostApp;
    }
    renderSelectedHostApp();
}
function renderSelectedHostApp() {
    updateStyleSheet();
    renderCard();
}
function setupFilePicker() {
    document.getElementById("loadSample").onclick = function () { document.getElementById("filePicker").click(); };
    document.getElementById("filePicker").addEventListener("change", filePickerChanged);
}
window.onload = function () {
    hostContainerPicker = document.getElementById("hostContainerPicker");
    setupEditor();
    setupContainerPicker();
    setupFilePicker();
    updateStyleSheet();
    renderCard();
    // handle Back and Forward after the Container app drop down is changed
    window.addEventListener('popstate', function (e) {
        setContainerAppFromUrl();
    });
};
//# sourceMappingURL=app.js.map