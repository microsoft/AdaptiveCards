import * as Utils from "./Utils";

import * as Adaptive from "./Adaptive";
import * as Constants from "./Constants";

import { BingContainer } from "./containers/BingContainer";
import { HostContainer } from "./containers/HostContainer";
import { ConnectorContainer } from "./containers/ConnectorContainer";
import { LiveTileContainer } from "./containers/LiveTileContainer";
import { OutlookConnectorContainer } from "./containers/OutlookConnectorContainer";
import { SkypeContainer } from "./containers/SkypeContainer";
import { SpeechContainer } from "./containers/SpeechContainer";
import { TeamsConnectorContainer } from "./containers/TeamsConnectorContainer";
import { ToastContainer } from "./containers/ToastContainer";

import * as ace from "brace";
import "brace/mode/json";
import "brace/theme/chrome";
import * as vkbeautify from "vkbeautify";

let editor: ace.Editor;
let hostContainerOptions: Array<HostContainerOption> = [];
let hostContainerPicker: HTMLSelectElement;

function renderCard() {

    let jsonText = editor.getValue();
    try {
        let json = JSON.parse(jsonText);
        let cardTypeName = json["@type"];

        let node = document.getElementById('content');
        node.innerHTML = '';

        switch (cardTypeName) {
            case "AdaptiveCard":
                let adaptiveCard = new Adaptive.AdaptiveCard();
                adaptiveCard.parse(json);

                let hostContainer = hostContainerOptions[hostContainerPicker.selectedIndex].hostContainer;
                let renderedHostContainer = hostContainer.render(adaptiveCard);

                Utils.appendChild(node, renderedHostContainer);

                try {
                    sessionStorage.setItem("AdaptivePayload", editor.getValue());
                }
                catch (e2) {
                    console.log("Unable to cache payload")
                }

                break;
            default:
                if (Utils.isNullOrEmpty(cardTypeName)) {
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
    let filePicker = document.getElementById("filePicker") as HTMLInputElement;

    let file = filePicker.files[0];

    if (file) {
        let reader = new FileReader();

        reader.onload = function (e: ProgressEvent) {
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
        // TODO: Is this a bug? Won't previous style sheets stick around then?
        let headElement = document.getElementsByTagName("head")[0];
        Utils.appendChild(headElement, styleSheetLinkElement);
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
    var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
        results = regex.exec(url);
    if (!results) return null;
    if (!results[2]) return '';
    return decodeURIComponent(results[2].replace(/\+/g, " "));
}

class HostContainerOption {
    readonly name: string;
    readonly hostContainer: HostContainer;

    constructor(name: string, hostContainer: HostContainer) {
        this.name = name;
        this.hostContainer = hostContainer;
    }
}

function setupEditor() {
    editor = ace.edit("editor");
    editor.setTheme("ace/theme/chrome");
    editor.setOptions(
        {
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
        let cachedPayload = sessionStorage.getItem("AdaptivePayload");
        if (cachedPayload) {
            editor.session.setValue(cachedPayload);
        }
        else {
            // editor.session.setValue(Constants.defaultPayload);
        }
    }
    catch (e) {
        // editor.session.setValue(Constants.defaultPayload);
    }

}

function setupContainerPicker() {

    hostContainerOptions.push(
        new HostContainerOption(
            "Outlook Connector",
            new OutlookConnectorContainer("red", "./css/outlookConnectorCard.css")));
    hostContainerOptions.push(
        new HostContainerOption(
            "Microsoft Teams Connector",
            new TeamsConnectorContainer("./css/teamsConnectorCard.css")));
    hostContainerOptions.push(
        new HostContainerOption(
            "Windows Toast Notification",
            new ToastContainer(362, "./css/toast.css")));
    hostContainerOptions.push(
        new HostContainerOption(
            "Large Live Tile",
            new LiveTileContainer(310, 310, "./css/liveTile.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Skype",
            new SkypeContainer("./css/skypeCard.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Bing",
            new BingContainer(285, 150, "./css/bing.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Speech",
            new SpeechContainer("./css/bing.css")));

    if (hostContainerPicker) {
        hostContainerPicker.addEventListener("change", () => {
            // update the query string
            history.pushState(hostContainerPicker.value, `Visualizer - ${hostContainerPicker.value}`, `index.html?hostApp=${hostContainerPicker.value}`);

            renderSelectedHostApp();
        });

        for (let i = 0; i < hostContainerOptions.length; i++) {
            let option = document.createElement("option");
            option.value = hostContainerOptions[i].name;
            option.text = hostContainerOptions[i].name;

            Utils.appendChild(hostContainerPicker, option);
        }
    }

    setContainerAppFromUrl();
}

function setContainerAppFromUrl() {
    let requestedHostApp = getParameterByName("hostApp", null);
    if (requestedHostApp) {
        console.log(`Setting host app to ${requestedHostApp}`);
        hostContainerPicker.value = requestedHostApp;
    }

    renderSelectedHostApp();
}

function renderSelectedHostApp() {
    updateStyleSheet();
    renderCard();
}

function setupFilePicker() {
    document.getElementById("loadSample").onclick = () => { document.getElementById("filePicker").click(); };
    document.getElementById("filePicker").addEventListener("change", filePickerChanged);
}

window.onload = () => {
    hostContainerPicker = <HTMLSelectElement>document.getElementById("hostContainerPicker");

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

