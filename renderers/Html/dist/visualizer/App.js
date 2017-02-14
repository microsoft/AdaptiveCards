"use strict";
var Adaptive = require("../Adaptive");
var Constants = require("./Constants");
var BingContainer_1 = require("./containers/BingContainer");
var LiveTileContainer_1 = require("./containers/LiveTileContainer");
var OutlookConnectorContainer_1 = require("./containers/OutlookConnectorContainer");
var SkypeContainer_1 = require("./containers/SkypeContainer");
var SpeechContainer_1 = require("./containers/SpeechContainer");
var TeamsConnectorContainer_1 = require("./containers/TeamsConnectorContainer");
var ToastContainer_1 = require("./containers/ToastContainer");
var CortanaCarContainer_1 = require("./containers/CortanaCarContainer");
var ace = require("brace");
require("brace/mode/json");
require("brace/theme/chrome");
var editor;
var hostContainerOptions = [];
var hostContainerPicker;
function renderCard() {
    var jsonText = editor.getValue();
    try {
        var json = JSON.parse(jsonText);
        var cardTypeName = json["@type"];
        var node = document.getElementById('content');
        node.innerHTML = '';
        switch (cardTypeName) {
            case "AdaptiveCard":
                var adaptiveCard = new Adaptive.AdaptiveCard();
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
                // TODO: Fix this
                //if (isNullOrEmpty(cardTypeName)) {
                if (!false) {
                    throw new Error("The card's type must be specified.");
                }
                else {
                    throw new Error("Unknown card type: " + cardTypeName);
                }
        }
    }
    catch (e) {
        document.getElementById('content').innerHTML = "Error: " + e.toString();
        console.log(e.toString() + '\n' + jsonText);
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
        // TODO: Is this a bug? Won't previous style sheets stick around then?
        var headElement = document.getElementsByTagName("head")[0];
        headElement.appendChild(styleSheetLinkElement);
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
            editor.session.setValue(Constants.defaultPayload);
        }
    }
    catch (e) {
        editor.session.setValue(Constants.defaultPayload);
    }
}
function setupContainerPicker() {
    hostContainerOptions.push(new HostContainerOption("Outlook Connector", new OutlookConnectorContainer_1.OutlookConnectorContainer("red", "./../../css/outlookConnectorCard.css")));
    hostContainerOptions.push(new HostContainerOption("Microsoft Teams Connector", new TeamsConnectorContainer_1.TeamsConnectorContainer("./../../css/teamsConnectorCard.css")));
    hostContainerOptions.push(new HostContainerOption("Windows Toast Notification", new ToastContainer_1.ToastContainer(362, "./../../css/toast.css")));
    hostContainerOptions.push(new HostContainerOption("Large Live Tile", new LiveTileContainer_1.LiveTileContainer(310, 310, "./../../css/liveTile.css")));
    hostContainerOptions.push(new HostContainerOption("Skype", new SkypeContainer_1.SkypeContainer("./../../css/skypeCard.css")));
    hostContainerOptions.push(new HostContainerOption("Bing", new BingContainer_1.BingContainer(285, 150, "./../../css/bing.css")));
    hostContainerOptions.push(new HostContainerOption("Cortana Car", new CortanaCarContainer_1.CortanaCarContainer("./../../css/cortanaCar.css")));
    hostContainerOptions.push(new HostContainerOption("Speech", new SpeechContainer_1.SpeechContainer("./../../css/bing.css")));
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
//# sourceMappingURL=App.js.map