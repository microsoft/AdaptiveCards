import * as Adaptive from "adaptivecards";
import * as Constants from "./constants";

import { HostContainer } from "./containers/host-container";
import { LiveTileContainer } from "./containers/live-tile";
import { SkypeContainer } from "./containers/skype";
import { WebChatContainer } from "./containers/webchat";
import { TeamsContainer } from "./containers/teams";
import { ToastContainer } from "./containers/toast";
import { GroupMeContainer } from "./containers/groupme";
import { TelegramContainer } from "./containers/telegram";
import { SMSContainer } from "./containers/sms";
import { SlackContainer } from "./containers/slack";
import { KikContainer } from "./containers/kik";
import { FacebookContainer } from "./containers/facebook";
import { BingContainer } from "./containers/bing";
import { TimelineContainer } from "./containers/timeline";
import { OutlookContainer } from "./containers/outlook";

import * as ace from "brace";
import "brace/mode/json";
import "brace/theme/chrome";
import * as vkbeautify from "vkbeautify";

var editor: ace.Editor;
var hostContainerOptions: Array<HostContainerOption> = [];
var hostContainerPicker: HTMLSelectElement;
var lastValidationErrors: Array<Adaptive.IValidationError> = [];

function setContent(element) {
    var contentContainer = document.getElementById("content");

    contentContainer.innerHTML = '';
    contentContainer.appendChild(element);
}

function renderCard(): HTMLElement {
    document.getElementById("errorContainer").hidden = true;
    lastValidationErrors = [];

    var hostContainer = hostContainerOptions[hostContainerPicker.selectedIndex].hostContainer;

    var json = JSON.parse(currentCardPayload);

    var adaptiveCard = new Adaptive.AdaptiveCard();

    
    adaptiveCard.hostConfig = Adaptive.HostConfig.parse(currentConfigPayload);
   
    
    adaptiveCard.parse(json);
    
    lastValidationErrors = lastValidationErrors.concat(adaptiveCard.validate());

    showValidationErrors();

    return hostContainer.render(adaptiveCard.render(), adaptiveCard.renderSpeech());
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
        sessionStorage.setItem("AdaptivePayload", currentCardPayload);
    }
    catch (e) {
        console.log("Unable to cache JSON payload.")
    }
}

function openFilePicker() {
    document.getElementById("filePicker").click();
}

function setEditorText(text: string) {
    editor.session.setValue(text);
}

function filePickerChanged(evt) {
    var filePicker = document.getElementById("filePicker") as HTMLInputElement;

    var file = filePicker.files[0];

    if (file) {
        let reader = new FileReader();

        reader.onload = function (e: ProgressEvent) {
            currentCardPayload = (e.target as FileReader).result;
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

    var selectedHostContainer = hostContainerOptions[hostContainerPicker.selectedIndex].hostContainer;

    styleSheetLinkElement.href = selectedHostContainer.styleSheet;

    currentConfigPayload = JSON.stringify(selectedHostContainer.getHostConfig(), null, '\t');

    if (!isCardEditor) {
        setEditorText(currentConfigPayload);
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

function setupEditor() {
    editor = ace.edit("editor");
    editor.setTheme("ace/theme/chrome");
    editor.setOptions(
        {
            showPrintMargin: false,
            displayIndentGuides: false,
            showFoldWidgets: true,
            highlightSelectedWord: false,
            fontSize: "14px"
        });
    editor.getSession().setMode("ace/mode/json");
    editor.getSession().on(
        "change",
        function (e) {
            if (isCardEditor) {
                currentCardPayload = editor.getValue();
            }
            else {
                currentConfigPayload = editor.getValue();
            }

            tryRenderCard();
        });

    // Load the cached payload if the user had one
    try {
        var cachedPayload = sessionStorage.getItem("AdaptivePayload");
        var cardUrl = document.location.search.substring(1).split('card=')[1];

        if (cardUrl) {
            currentCardPayload = "";
            var xhttp = new XMLHttpRequest();
            xhttp.onload = function () {
                currentCardPayload = xhttp.responseText;
                setEditorText(currentCardPayload);
            };

            xhttp.open("GET", cardUrl, true);
            xhttp.send();
        }
        else if (cachedPayload) {
            currentCardPayload = cachedPayload;
        }
        else {
            currentCardPayload = Constants.defaultPayload;
        }
    }
    catch (e) {
        currentCardPayload = Constants.defaultPayload;
    }
}

function setupContainerPicker() {

    hostContainerOptions.push(
        new HostContainerOption(
            "Microsoft Teams",
            new TeamsContainer("css/teams.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Microsoft Outlook Actionable Messages",
            new OutlookContainer("css/outlook.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Windows Toast Notification",
            new ToastContainer(362, "css/toast.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Windows Timeline",
            new TimelineContainer(320, 180, "css/timeline.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Windows Live Tile",
            new LiveTileContainer(310, 310, "css/liveTile.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Skype",
            new SkypeContainer(350, "css/skype.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "WebChat (Bot Framework)",
            new WebChatContainer("css/webchat.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Bing (Bot Framework)",
            new BingContainer(368, "css/skype.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Kik (Bot Framework)",
            new KikContainer(400, "css/kik.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Slack (Bot Framework)",
            new SlackContainer(500, "css/slack.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Facebook (Bot Framework)",
            new FacebookContainer(450, "css/facebook.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "SMS (Bot Framework)",
            new SMSContainer(400, "css/sms.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "Telegram (Bot Framework)",
            new TelegramContainer(400, "css/telegram.css")));

    hostContainerOptions.push(
        new HostContainerOption(
            "GroupMe (Bot Framework)",
            new GroupMeContainer(450, "css/groupme.css")));

    if (hostContainerPicker) {
        hostContainerPicker.addEventListener(
            "change", () => {
                // Update the query string
                var htmlFileName = location.pathname.indexOf("dev.html") >= 0 ? "dev.html" : "index.html";

                history.pushState(hostContainerPicker.value, `Visualizer - ${hostContainerPicker.value}`, htmlFileName + `?hostApp=${hostContainerPicker.value}`);

                loadStyleSheetAndConfig();
                tryRenderCard();
            });

        for (var i = 0; i < hostContainerOptions.length; i++) {
            var option = document.createElement("option");
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
    }
    else {
        message += "    Type: <unknown>";
    }

    // Uncomment to test the action's setStatus method:
    /*
    action.setStatus(
        {
            "type": "AdaptiveCard",
            "body": [
                {
                    "type": "TextBlock",
                    "text": "Working on it...",
                    "weight": "normal",
                    "size": "small"
                }
            ]
        });

    window.setTimeout(actionCompletedCallback, 2000, action);
    */
    
    alert(message);
}

function actionCompletedCallback(action: Adaptive.Action) {
    action.setStatus(
        {
            "type": "AdaptiveCard",
            "body": [
                {
                    "type": "TextBlock",
                    "text": "Success!",
                    "weight": "normal",
                    "size": "small"
                }
            ]
        });
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

    var hostContainer = hostContainerOptions[hostContainerPicker.selectedIndex].hostContainer;

    cardContainer.appendChild(hostContainer.render(action.card.render(), action.card.renderSpeech()));

    overlayElement.appendChild(cardContainer);

    document.body.appendChild(overlayElement);

    var cardContainerBounds = cardContainer.getBoundingClientRect();
    cardContainer.style.left = (window.innerWidth - cardContainerBounds.width) / 2 + "px";
    cardContainer.style.top = (window.innerHeight - cardContainerBounds.height) / 2 + "px";
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

    setEditorText(currentCardPayload);
    editor.focus();
}

function switchToConfigEditor() {
    isCardEditor = false;

    document.getElementById("editCard").classList.add("subdued");
    document.getElementById("editConfig").classList.remove("subdued");

    setEditorText(currentConfigPayload);
    editor.focus();
}

function inlineCardExpanded(action: Adaptive.ShowCardAction, isExpanded: boolean) {
    alert("Card \"" + action.title + "\" " + (isExpanded ? "expanded" : "collapsed"));
}

function elementVisibilityChanged(element: Adaptive.CardElement) {
    alert("An element is now " + (element.isVisible ? "visible" : "invisible"));
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

        this.targetElementIds = json["targetElementIds"] as Array<string>;
    }
}

var betaFeaturesEnabled: boolean = false;

window.onload = () => {
    betaFeaturesEnabled = location.search.indexOf("beta=true") >= 0;

    if (betaFeaturesEnabled) {
        Adaptive.AdaptiveCard.useAutoPadding = true;

        Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.ToggleVisibility", () => { return new ToggleVisibilityAction(); });
        
        Adaptive.AdaptiveCard.onParseElement = (element: Adaptive.CardElement, json: any) => {
            if (typeof json["isVisible"] === "boolean") {
                element.isVisible = json["isVisible"];
            }        
        }

        Adaptive.AdaptiveCard.onAnchorClicked = (anchor: HTMLAnchorElement) => {
            if (anchor.href.startsWith("executeaction:")) {
                alert("Executing inline action...");

                return true;
            }
            else {
                return false;
            }
        }
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

    Adaptive.AdaptiveCard.onParseError = (error: Adaptive.IValidationError) => {
        lastValidationErrors.push(error);
    }

    hostContainerPicker = <HTMLSelectElement>document.getElementById("hostContainerPicker");

    setupContainerPicker();
    setContainerAppFromUrl();
    setupFilePicker();
    loadStyleSheetAndConfig();
    setupEditor();

    switchToCardEditor();

    // Handle Back and Forward after the Container app drop down is changed
    window.addEventListener(
        "popstate",
        function (e) {
            setContainerAppFromUrl();
        });
};