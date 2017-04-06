import * as Adaptive from "adaptive-cards";
import * as Constants from "./constants";

import { HostContainer } from "./containers/host-container";
import { BingContainer } from "./containers/bing";
import { LiveTileContainer } from "./containers/live-tile";
import { OutlookConnectorContainer } from "./containers/outlook-connector";
import { SkypeContainer } from "./containers/skype";
import { SpeechContainer } from "./containers/speech";
import { TeamsConnectorContainer } from "./containers/teams-connector";
import { ToastContainer } from "./containers/toast";
import { CortanaCarContainer } from "./containers/cortana-car";

import * as ace from "brace";
import "brace/mode/json";
import "brace/theme/chrome";
import * as vkbeautify from "vkbeautify";

let editor: ace.Editor;
let hostContainerOptions: Array<HostContainerOption> = [];
let hostContainerPicker: HTMLSelectElement;

function actionExecuted(action: Adaptive.Action) {
    
    var message: string = "Action executed\n";
    message += "    Title: " + action.title + "\n";

    if (action instanceof Adaptive.ActionOpenUrl) {
        message += "    Type: OpenUrl\n";
        message += "    Url: " + (<Adaptive.ActionOpenUrl>action).url + "\n";
    }
    else if (action instanceof Adaptive.ActionSubmit) {
        message += "    Type: Submit";
        message += "    Data: " + JSON.stringify((<Adaptive.ActionSubmit>action).data);
    }
    else if (action instanceof Adaptive.ActionHttp) {
        var httpAction = <Adaptive.ActionHttp>action;
        message += "    Type: Http\n";
        message += "    Url: " + httpAction.url + "\n";
        message += "    Methid: " + httpAction.method + "\n";
        message += "    Headers:\n";

        for (var i = 0; i < httpAction.headers.length; i++) {
            message += "        " + httpAction.headers[i].name + ": " + httpAction.headers[i].value + "\n";
        }

        message += "    Body: " + httpAction.body + "\n";
    }
    else {
        message += "    Type: <unknown>";
    }

    alert(message);
}

function setContent(element) {
    let contentContainer = document.getElementById("content");

    contentContainer.innerHTML = '';
    contentContainer.appendChild(element);
}

function renderCard(): HTMLElement {
    let hostContainer = hostContainerOptions[hostContainerPicker.selectedIndex].hostContainer;
    hostContainer.applyOptions();

    var jsonPayload = editor.getValue();
    var json = JSON.parse(jsonPayload);

    var cardTypeName = json["type"];

    var jsonParser = new Adaptive.JsonParser();
    var adaptiveCard = jsonParser.parse(json);

    var popupContainer = document.getElementById("popupCardContainer");

    if (Adaptive.AdaptiveCard.renderOptions.actionShowCardInPopup) {
        popupContainer.innerText = "ActionShowCard popups will appear in this box, according to container settings";
        popupContainer.hidden = false;
    }
    else {
        popupContainer.hidden = true;
    }

    document.getElementById("errorContainer").hidden = true;

    return hostContainer.render(adaptiveCard);
}

function tryRenderCard() {
    var renderedCard: HTMLElement;

    try {
        renderedCard = renderCard();
    }
    catch (ex) {
        renderedCard = document.createElement("div");
        renderedCard.innerText = ex.message;
    }

    var contentContainer = document.getElementById("content");
    contentContainer.innerHTML = '';
    contentContainer.appendChild(renderedCard);

    try {
        sessionStorage.setItem("AdaptivePayload", editor.getValue());
    }
    catch (e) {
        console.log("Unable to cache JSON payload.")
    }
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

        document.getElementsByTagName("head")[0].appendChild(styleSheetLinkElement);
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

    var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)");

    var results = regex.exec(url);

    if (results && results[2]) {
        return decodeURIComponent(results[2].replace(/\+/g, " "));
    }
    else {
        return "";
    }
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
    editor.getSession().on(
        "change",
        function (e) {
            tryRenderCard();
        });

    // Load the cached payload if the user had one
    try {
        let cachedPayload = sessionStorage.getItem("AdaptivePayload");
        var cardUrl = document.location.search.substring(1).split('card=')[1];
        if (cardUrl) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    editor.session.setValue(xhttp.responseText);
                }
            };
            xhttp.open("GET", cardUrl, true);
            xhttp.send(); 
        }
        else if (cachedPayload) {
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

    hostContainerOptions.push(
        new HostContainerOption(
            "Outlook Connector",
            new OutlookConnectorContainer("red", "css/outlookConnectorCard.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Microsoft Teams Connector",
            new TeamsConnectorContainer("css/teamsConnectorCard.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Windows Toast Notification",
            new ToastContainer(362, "css/toast.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Large Live Tile",
            new LiveTileContainer(310, 310, "css/liveTile.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Skype",
            new SkypeContainer("css/skypeCard.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Bing",
            new BingContainer(285, 150, "css/bing.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Cortana Car",
            new CortanaCarContainer("css/cortanaCar.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Speech",
            new SpeechContainer("css/bing.css")));

    if (hostContainerPicker) {
        hostContainerPicker.addEventListener(
            "change", () => {
                // update the query string
                history.pushState(hostContainerPicker.value, `Visualizer - ${hostContainerPicker.value}`, `index.html?hostApp=${hostContainerPicker.value}`);

                updateStyleSheet();
                tryRenderCard();
            });

        for (let i = 0; i < hostContainerOptions.length; i++) {
            let option = document.createElement("option");
            option.value = hostContainerOptions[i].name;
            option.text = hostContainerOptions[i].name;

            hostContainerPicker.appendChild(option);
        }
    }
}

function setContainerAppFromUrl() {
    var requestedHostApp = getParameterByName("hostApp", null);

    if (requestedHostApp) {
        console.log(`Setting host app to ${requestedHostApp}`);

        hostContainerPicker.value = requestedHostApp;
    }
}

function setupFilePicker() {
    document.getElementById("loadSample").onclick = () => { document.getElementById("filePicker").click(); };
    document.getElementById("filePicker").addEventListener("change", filePickerChanged);
}

window.onload = () => {
    Adaptive.AdaptiveCard.onExecuteAction = actionExecuted;

    Adaptive.AdaptiveCard.onShowPopupCard = (action, element) => {
        var popupContainer = document.getElementById("popupCardContainer");
        popupContainer.innerHTML = "";
        popupContainer.appendChild(action.card.render());
    }

    Adaptive.AdaptiveCard.onValidationError = (error, message) => {
        var errorContainer = document.getElementById("errorContainer");
        errorContainer.innerText = message;
        errorContainer.hidden = false;
    }

    hostContainerPicker = <HTMLSelectElement>document.getElementById("hostContainerPicker");

    setupContainerPicker();
    setContainerAppFromUrl();
    setupFilePicker();
    updateStyleSheet();
    setupEditor();

    // handle Back and Forward after the Container app drop down is changed
    window.addEventListener(
        "popstate",
        function (e) {
            setContainerAppFromUrl();
        });
};

