// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import * as Constants from "./constants";

import { HostContainer } from "./containers/host-container";
import { SkypeContainer } from "./containers/skype";
import { WebChatContainer } from "./containers/webchat";
import { TeamsContainer } from "./containers/teams";
import { ToastContainer } from "./containers/toast";
import { TimelineContainer } from "./containers/timeline";
import { OutlookContainer } from "./containers/outlook";
import { BotFrameworkImageContainer } from "./containers/bf-image";

import { adaptiveCardSchema } from "./adaptive-card-schema";
import { CortanaContainer } from "./containers/cortana";

var hostContainerOptions: Array<HostContainerOption> = [];
var hostContainerPicker: HTMLSelectElement;
var lastValidationErrors: Array<Adaptive.IValidationError> = [];

function getSelectedHostContainer(): HostContainer {
    return hostContainerOptions[hostContainerPicker.selectedIndex].hostContainer;
}

function setContent(element) {
    var contentContainer = document.getElementById("content");

    contentContainer.innerHTML = '';
    contentContainer.appendChild(element);
}

function renderCard(target: HTMLElement): HTMLElement {
    document.getElementById("errorContainer").hidden = true;

    let json = JSON.parse(currentCardPayload);
    let adaptiveCard = new Adaptive.AdaptiveCard();
    adaptiveCard.hostConfig = new Adaptive.HostConfig(currentConfigPayload);

    getSelectedHostContainer().setHostCapabilities(adaptiveCard.hostConfig);

    let serializationContext = new Adaptive.SerializationContext();
    
    serializationContext.onParseElement = (element: Adaptive.CardElement, source: any, context: Adaptive.SerializationContext) => {
        getSelectedHostContainer().parseElement(element, source, context);
    }

    adaptiveCard.parse(json, serializationContext);

    let validationResults = adaptiveCard.validateProperties();

    for (let failure of validationResults.failures) {
        lastValidationErrors = lastValidationErrors.concat(failure.errors);
    }

    showValidationErrors();

    return getSelectedHostContainer().render(adaptiveCard, target);
}

function tryRenderCard() {
    var contentContainer = document.getElementById("content");
    contentContainer.innerHTML = '';

    try {
        renderCard(contentContainer);
    }
    catch (ex) {
        var renderedCard = document.createElement("div");
        renderedCard.innerText = ex.message;
        contentContainer.appendChild(renderedCard);
    }

    try {
        sessionStorage.setItem("AdaptivePayload", currentCardPayload);
        history.pushState(hostContainerPicker.value, `Visualizer - ${hostContainerPicker.value}`, "index.html" + `?hostApp=${hostContainerPicker.value}`);
    }
    catch (e) {
        console.log("Unable to cache JSON payload.")
    }

    isLoaded = true;
}

function openFilePicker() {
    document.getElementById("filePicker").click();
}

function filePickerChanged(evt) {
    var filePicker = document.getElementById("filePicker") as HTMLInputElement;

    var file = filePicker.files[0];

    if (file) {
        let reader = new FileReader();

        reader.onload = function (e: ProgressEvent) {
            let downloadedPayload = (e.target as FileReader).result;

            if (typeof downloadedPayload === "string") {
                currentCardPayload = downloadedPayload;
            }

            switchToCardEditor();
        }

        reader.readAsText(file);
    }
    else {
        alert("Failed to load file");
    }
}

function loadStyleSheetAndConfig() {
    var styleSheetLinkElement = <HTMLLinkElement>document.getElementById("adaptiveCardStylesheet");

    if (styleSheetLinkElement == null) {
        styleSheetLinkElement = document.createElement("link");
        styleSheetLinkElement.id = "adaptiveCardStylesheet";

        document.getElementsByTagName("head")[0].appendChild(styleSheetLinkElement);
    }

    styleSheetLinkElement.rel = "stylesheet";
    styleSheetLinkElement.type = "text/css";

    var selectedHostContainer = getSelectedHostContainer();
    selectedHostContainer.initialize();

    styleSheetLinkElement.href = selectedHostContainer.styleSheet;

    currentConfigPayload = JSON.stringify(selectedHostContainer.getHostConfig(), null, '\t');

    if (!isCardEditor) {
        monacoEditor.setValue(currentConfigPayload);
    }
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

var currentCardPayload: string = "";
var currentConfigPayload: string = "";
var isLoaded = false;;

function hostContainerPickerChanged() {
    loadStyleSheetAndConfig();

    if (isLoaded) {
        tryRenderCard();
    }
}

function setupContainerPicker() {
    hostContainerPicker = <HTMLSelectElement>document.getElementById("hostContainerPicker");

    hostContainerOptions.push(new HostContainerOption("Bot Framework WebChat", new WebChatContainer("css/webchat.css")));
    hostContainerOptions.push(new HostContainerOption("Cortana Skills", new CortanaContainer(true, "css/cortana.css")));
    hostContainerOptions.push(new HostContainerOption("Microsoft Teams", new TeamsContainer("css/teams.css")));
    hostContainerOptions.push(new HostContainerOption("Outlook Actionable Messages", new OutlookContainer("css/outlook.css")));
    hostContainerOptions.push(new HostContainerOption("Windows Timeline", new TimelineContainer(320, 176, "css/timeline.css")));
    hostContainerOptions.push(new HostContainerOption("Bot Framework Other Channels (Image render)", new BotFrameworkImageContainer(400, "css/bf.css")));
	hostContainerOptions.push(new HostContainerOption("Skype (Preview)", new SkypeContainer(350, "css/skype.css")));
    hostContainerOptions.push(new HostContainerOption("Windows Notifications (Preview)", new ToastContainer(362, "css/toast.css")));

	// hostContainerOptions.push(//     new HostContainerOption(//         "All at once", //         new BotFrameworkImageContainer(400, "css/bf.css")));

    hostContainerPicker.addEventListener("change", hostContainerPickerChanged);

    for (var i = 0; i < hostContainerOptions.length; i++) {
        var option = document.createElement("option");
        option.value = hostContainerOptions[i].name;
        option.text = hostContainerOptions[i].name;

        hostContainerPicker.appendChild(option);
    }
}

function setContainerAppFromUrl() {
    var requestedHostApp = getParameterByName("hostApp", null);

    if (!requestedHostApp) {
        requestedHostApp = hostContainerOptions[0].name;
    }

    console.log(`Setting host app to ${requestedHostApp}`);

    hostContainerPicker.value = requestedHostApp;

    hostContainerPickerChanged();
}

function setupFilePicker() {
    document.getElementById("loadSample").onclick = () => { document.getElementById("filePicker").click(); };
    document.getElementById("filePicker").addEventListener("change", filePickerChanged);
}

function actionExecuted(action: Adaptive.Action) {
    var message: string = "Action executed\n";
    message += "    Title: " + action.title + "\n";

    if (action instanceof Adaptive.OpenUrlAction) {
        message += "    Type: OpenUrl\n";
        message += "    Url: " + (<Adaptive.OpenUrlAction>action).url + "\n";
    }
    else if (action instanceof Adaptive.SubmitAction) {
        message += "    Type: Submit";
        message += "    Data: " + JSON.stringify((<Adaptive.SubmitAction>action).data);
    }
    else if (action instanceof Adaptive.HttpAction) {
        var httpAction = <Adaptive.HttpAction>action;
        message += "    Type: Http\n";
        message += "    Url: " + httpAction.url + "\n";
        message += "    Method: " + httpAction.method + "\n";
        message += "    Headers:\n";

        for (var i = 0; i < httpAction.headers.length; i++) {
            message += "        " + httpAction.headers[i].name + ": " + httpAction.headers[i].value + "\n";
        }

        message += "    Body: " + httpAction.body + "\n";
    }
    else if (action instanceof Adaptive.ShowCardAction) {
        showPopupCard(<Adaptive.ShowCardAction>action);
        return;
    }
    else {
        message += "    Type: <unknown>";
    }

    alert(message);
}

function showPopupCard(action: Adaptive.ShowCardAction) {
    var overlayElement = document.createElement("div");
    overlayElement.id = "popupOverlay";
    overlayElement.className = "popupOverlay";
    overlayElement.tabIndex = 0;
    overlayElement.style.width = document.documentElement.scrollWidth + "px";
    overlayElement.style.height = document.documentElement.scrollHeight + "px";
    overlayElement.onclick = (e) => {
        document.body.removeChild(overlayElement);
    };

    var cardContainer = document.createElement("div");
    cardContainer.className = "popupCardContainer";
    cardContainer.onclick = (e) => { e.stopPropagation() };

    var cardContainerBounds = cardContainer.getBoundingClientRect();
    cardContainer.style.left = (window.innerWidth - cardContainerBounds.width) / 2 + "px";
    cardContainer.style.top = (window.innerHeight - cardContainerBounds.height) / 2 + "px";

    overlayElement.appendChild(cardContainer);
    document.body.appendChild(overlayElement);

    var hostContainer = getSelectedHostContainer();
    hostContainer.render(action.card, cardContainer);
}

function showValidationErrors() {
    if (lastValidationErrors.length > 0) {
        var errorContainer = document.getElementById("errorContainer");
        errorContainer.innerHTML = "";

        for (var i = 0; i < lastValidationErrors.length; i++) {
            var errorElement = document.createElement("div");
            errorElement.innerText = lastValidationErrors[i].message;

            errorContainer.appendChild(errorElement);
        }

        errorContainer.hidden = false;
    }
}

var isCardEditor = true;

function switchToCardEditor() {
    isCardEditor = true;

    document.getElementById("editCard").classList.remove("subdued");
    document.getElementById("editConfig").classList.add("subdued");

    monacoEditor.setValue(currentCardPayload);
    monacoEditor.focus();
}

function switchToConfigEditor() {
    isCardEditor = false;

    document.getElementById("editCard").classList.add("subdued");
    document.getElementById("editConfig").classList.remove("subdued");

    monacoEditor.setValue(currentConfigPayload);
    monacoEditor.focus();
}

function inlineCardExpanded(action: Adaptive.ShowCardAction, isExpanded: boolean) {
    alert("Card \"" + action.title + "\" " + (isExpanded ? "expanded" : "collapsed"));
}

function elementVisibilityChanged(element: Adaptive.CardElement) {
    alert("An element is now " + (element.isVisible ? "visible" : "invisible"));
}

declare var monacoEditor: any;

// Monaco loads asynchronously via a call to require() from index.html
// App initialization needs to happen after.
declare function loadMonacoEditor(schema: any, callback: () => void);

function monacoEditorLoaded() {
    Adaptive.AdaptiveCard.onAnchorClicked = (element: Adaptive.CardElement, anchor: HTMLAnchorElement) => {
        return getSelectedHostContainer().anchorClicked(element, anchor);
    }

    currentConfigPayload = Constants.defaultConfigPayload;

    document.getElementById("editCard").onclick = (e) => {
        switchToCardEditor();
    };

    document.getElementById("editConfig").onclick = (e) => {
        switchToConfigEditor();
    };

    Adaptive.AdaptiveCard.onExecuteAction = actionExecuted;
    // Adaptive.AdaptiveCard.onShowPopupCard = showPopupCard;

    /*
    Test additional events:

    Adaptive.AdaptiveCard.onInlineCardExpanded = inlineCardExpanded;
    Adaptive.AdaptiveCard.onElementVisibilityChanged = elementVisibilityChanged;
    */

    // Uncomment to test the onInlineCardExpanded event:
    // Adaptive.AdaptiveCard.onInlineCardExpanded = inlineCardExpanded;

    setupContainerPicker();
    setContainerAppFromUrl();
    setupFilePicker();
    loadStyleSheetAndConfig();

    // Handle Back and Forward after the Container app drop down is changed
    window.addEventListener(
        "popstate",
        function (e) {
            setContainerAppFromUrl();
        });

    monacoEditor.onDidChangeModelContent(
        function (e) {
            if (isCardEditor) {
                currentCardPayload = monacoEditor.getValue();
            }
            else {
                currentConfigPayload = monacoEditor.getValue();
            }

            tryRenderCard();
        });

    currentCardPayload = Constants.defaultPayload;

    var initialCardLaodedAsynchronously = false;
    var cardUrl = getParameterByName("card", null);

    if (cardUrl) {
        initialCardLaodedAsynchronously = true;

        var xhttp = new XMLHttpRequest();

        xhttp.onload = function () {
            if (xhttp.responseText && xhttp.responseText != "") {
                currentCardPayload = xhttp.responseText;
            }

            switchToCardEditor();
        };

        try {
            xhttp.open("GET", cardUrl, true);
            xhttp.send();
        }
        catch {
            initialCardLaodedAsynchronously = false;
        }
    }
    else {
        var cachedPayload;

        try {
            console.log("loading card from cache");
            cachedPayload = sessionStorage.getItem("AdaptivePayload");
        }
        catch {
            // Session storage is not accessible
            console.log("Unable to load card from cache");
        }

        if (cachedPayload && cachedPayload != "") {
            currentCardPayload = cachedPayload;
        }
    }

    if (!initialCardLaodedAsynchronously) {
        switchToCardEditor();
    }
}

window.onload = function() {
    loadMonacoEditor(adaptiveCardSchema, monacoEditorLoaded);
};
