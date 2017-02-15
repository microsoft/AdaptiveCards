import markdownIt = require("markdown-it");
let markdownProcessor = new markdownIt();

export function processMarkdown(text: string): any {
    return markdownProcessor.render(text);
}

/*
Strongly typed events from https://keestalkstech.com/2016/03/strongly-typed-event-handlers-in-typescript-part-1/
*/
export enum Size {
    Auto,
    Stretch,
    Small,
    Medium,
    Large
}

export enum TextSize {
    Small,
    Normal,
    Medium,
    Large,
    ExtraLarge
}

export enum TextWeight {
    Lighter,
    Normal,
    Bolder
}

export enum TextColor {
    Default,
    Dark,
    Light,
    Accent,
    Good,
    Warning,
    Attention
}

export enum HorizontalAlignment {
    Left,
    Center,
    Right
}

export enum ImageStyle {
    Normal,
    Person
}

export function stringToSize(value: string, defaultValue: Size): Size {
    switch (value) {
        case "auto":
            return Size.Auto;
        case "stretch":
            return Size.Stretch;
        case "small":
            return Size.Small;
        case "medium":
            return Size.Medium;
        case "large":
            return Size.Large;
        default:
            return defaultValue;
    }
}

export function stringToTextSize(value: string, defaultValue: TextSize): TextSize {
    switch (value) {
        case "small":
            return TextSize.Small;
        case "normal":
            return TextSize.Normal;
        case "medium":
            return TextSize.Medium;
        case "large":
            return TextSize.Large;
        case "extraLarge":
            return TextSize.ExtraLarge;
        default:
            return defaultValue;
    }
}

export function stringToTextWeight(value: string, defaultValue: TextWeight): TextWeight {
    switch (value) {
        case "lighter":
            return TextWeight.Lighter;
        case "normal":
            return TextWeight.Normal;
        case "bolder":
            return TextWeight.Bolder;
        default:
            return defaultValue;
    }
}

export function stringToTextColor(value: string, defaultValue: TextColor): TextColor {
    switch (value) {
        case "default":
            return TextColor.Default;
        case "dark":
            return TextColor.Dark;
        case "light":
            return TextColor.Light;
        case "accent":
            return TextColor.Accent;
        case "good":
            return TextColor.Good;
        case "warning":
            return TextColor.Warning;
        case "attention":
            return TextColor.Attention;
        default:
            return defaultValue;
    }
}

export function stringToHorizontalAlignment(value: string, defaultValue: HorizontalAlignment): HorizontalAlignment {
    switch (value) {
        case "left":
            return HorizontalAlignment.Left;
        case "center":
            return HorizontalAlignment.Center;
        case "right":
            return HorizontalAlignment.Right;
        default:
            return defaultValue;
    }
}

export function stringToImageStyle(value: string, defaultValue: ImageStyle): ImageStyle {
    switch (value) {
        case "person":
            return ImageStyle.Person;
        case "normal":
            return ImageStyle.Normal;
        default:
            return defaultValue;
    }
}

export interface IEvent<TSender> {
    subscribe(fn: (sender: TSender, args: any) => void): void;
    unsubscribe(fn: (sender: TSender, args: any) => void): void;
}

class EventDispatcher<TSender> implements IEvent<TSender> {
    private _subscriptions: Array<(sender: TSender, args: any) => void> = new Array<(sender: TSender, args: any) => void>();

    subscribe(fn: (sender: TSender, args: any) => void): void {
        if (fn) {
            this._subscriptions.push(fn);
        }
    }

    unsubscribe(fn: (sender: TSender, args: any) => void): void {
        let i = this._subscriptions.indexOf(fn);
        if (i > -1) {
            this._subscriptions.splice(i, 1);
        }
    }

    dispatch(sender: TSender, args: any): void {
        for (let handler of this._subscriptions) {
            handler(sender, args);
        }
    }
}

export function isNullOrEmpty(value: string): boolean {
    return value === undefined || value === null || value === "";
}

export function appendChild(node: Node, child: Node) {
    if (child != null && child != undefined) {
        node.appendChild(child);
    }
}

export abstract class CardElement {
    static createElement(container: Container, typeName: string): CardElement {
        switch (typeName) {
            case "Container":
                return new Container(container);
            case "TextBlock":
                return new TextBlock(container);
            case "Image":
                return new Image(container);
            case "ImageSet":
                return new ImageSet(container);
            case "ActionSet":
                return new ActionSet(container);
            case "FactSet":
                return new FactSet(container);
            case "Separator":
                return new Separator(container);
            case "ColumnSet":
                return new ColumnSet(container);
            case "TextInput":
                return new TextInput(container);
            case "DateInput":
                return new DateInput(container);
            case "ChoiceInput":
                return new MultichoiceInput(container);
            case "ToggleInput":
                return new ToggleInput(container);
            default:
                throw new Error("Unknown element type: " + typeName);
        }
    }

    private _container: Container;

    speak: string;
    size: Size = Size.Auto;
    horizontalAlignment: HorizontalAlignment = HorizontalAlignment.Left;

    constructor(container: Container) {
        this._container = container;
    }

    get container(): Container {
        return this._container;
    }

    get hideOverflow(): boolean {
        return true;
    }

    get useDefaultSizing(): boolean {
        return true;
    }

    abstract render(): HTMLElement;

    abstract renderSpeech(): string;

    removeTopSpacing(element: HTMLElement) {
        element.style.marginTop = "0px";
    }

    adjustLayout(element: HTMLElement) {
        if (this.useDefaultSizing) {
            switch (this.size) {
                case Size.Stretch:
                    element.className += " stretch";
                    break;
                case Size.Small:
                    element.className += " smallSize";
                    break;
                case Size.Medium:
                    element.className += " mediumSize";
                    break;
                case Size.Large:
                    element.className += " largeSize";
                    break;
            }
        }

        switch (this.horizontalAlignment) {
            case HorizontalAlignment.Center:
                element.style.textAlign = "center";
                break;
            case HorizontalAlignment.Right:
                element.style.textAlign = "right";
                break;
        }

        if (this.hideOverflow) {
            element.style.overflow = "hidden";
        }
    }

    internalRender(): HTMLElement {
        let renderedElement = this.render();

        if (renderedElement != null) {
            this.adjustLayout(renderedElement);
        }

        return renderedElement;
    }

    parse(json: any) {
        this.speak = json["speak"];
        this.size = stringToSize(json["size"], this.size);
        this.horizontalAlignment = stringToHorizontalAlignment(json["horizontalAlignment"], this.horizontalAlignment);
    }
}

export class TextBlock extends CardElement {
    textSize: TextSize = TextSize.Normal;
    textWeight: TextWeight = TextWeight.Normal;
    textColor: TextColor = TextColor.Default;
    text: string;
    isSubtle: boolean = false;
    wrap: boolean = true;

    parse(json: any) {
        super.parse(json);

        this.text = json["text"];
        this.textSize = stringToTextSize(json["size"], TextSize.Normal);
        this.textWeight = stringToTextWeight(json["weight"], TextWeight.Normal);
        this.textColor = stringToTextColor(json["color"], TextColor.Default);
        this.isSubtle = json["isSubtle"];
        this.wrap = json["wrap"];
    }

    render(): HTMLElement {
        if (!isNullOrEmpty(this.text)) {
            let element = document.createElement("div");

            let cssStyle = "text ";

            switch (this.textSize) {
                case TextSize.Small:
                    cssStyle += "small ";
                    break;
                case TextSize.Medium:
                    cssStyle += "medium ";
                    break;
                case TextSize.Large:
                    cssStyle += "large ";
                    break;
                case TextSize.ExtraLarge:
                    cssStyle += "extraLarge ";
                    break;
                default:
                    cssStyle += "defaultSize ";
                    break;
            }

            let actualTextColor = this.textColor == TextColor.Default ? this.container.textColor : this.textColor;

            switch (actualTextColor) {
                case TextColor.Dark:
                    cssStyle += "darkColor ";
                    break;
                case TextColor.Light:
                    cssStyle += "lightColor ";
                    break;
                case TextColor.Accent:
                    cssStyle += "accentColor ";
                    break;
                case TextColor.Good:
                    cssStyle += "goodColor ";
                    break;
                case TextColor.Warning:
                    cssStyle += "warningColor ";
                    break;
                case TextColor.Attention:
                    cssStyle += "attentionColor ";
                    break;
                default:
                    cssStyle += "defaultColor ";
                    break;
            }

            if (this.isSubtle) {
                cssStyle += "subtle ";
            }

            switch (this.textWeight) {
                case TextWeight.Lighter:
                    cssStyle += "lighter ";
                    break;
                case TextWeight.Bolder:
                    cssStyle += "bolder ";
                    break;
                default:
                    cssStyle += "defaultWeight ";
                    break;
            }

            element.innerHTML = processMarkdown(this.text);
            element.className = cssStyle;

            if (element.firstElementChild instanceof (HTMLElement)) {
                (<HTMLElement>element.firstElementChild).style.marginTop = "0px";
            }

            if (element.lastElementChild instanceof (HTMLElement)) {
                (<HTMLElement>element.lastElementChild).style.marginBottom = "0px";
            }

            var anchors = element.getElementsByTagName("a");

            for (var i = 0; i < anchors.length; i++) {
                anchors[i].target = "_blank";
            }

            if (!this.wrap) {
                element.style.whiteSpace = "nowrap";
                element.style.textOverflow = "ellipsis";
            }

            return element;
        }
        else {
            return null;
        }
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';

        if (this.text)
            return '<s>' + this.text + '</s>\n';
        return null;
    }

    removeTopSpacing(element: HTMLElement) {
        element.style.paddingTop = "0px";
    }
}

export class Fact {
    name: string;
    value: string;
    speak: string;

    parse(json: any) {
        this.name = json["name"];
        this.value = json["value"];
        this.speak = json["speak"];
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';
        return '<s>' + this.name + ' ' + this.value + '</s>\n';
    }
}

export class FactSet extends CardElement {
    private _facts: Array<Fact> = [];

    get facts(): Array<Fact> {
        return this._facts;
    }

    parse(json: any) {
        super.parse(json);

        if (json["facts"] != null) {
            var factArray = json["facts"] as Array<any>;

            for (var i = 0; i < factArray.length; i++) {
                let fact = new Fact();

                fact.parse(factArray[i]);

                this._facts.push(fact);
            }
        }
    }

    render(): HTMLElement {
        let element: HTMLElement = null;

        if (this._facts.length > 0) {
            element = document.createElement("table");
            element.className = "factSet";

            let html: string = '';

            for (var i = 0; i < this._facts.length; i++) {
                html += '<tr>';
                html += '    <td class="factName">';

                let textBlock = new TextBlock(this.container);
                textBlock.text = this._facts[i].name;
                textBlock.textWeight = TextWeight.Bolder;

                let renderedText = textBlock.internalRender();

                if (renderedText != null) {
                    html += renderedText.outerHTML;
                }

                html += '    </td>';
                html += '    <td class="factValue">';

                textBlock = new TextBlock(this.container);
                textBlock.text = this._facts[i].value;
                textBlock.textWeight = TextWeight.Lighter;

                renderedText = textBlock.internalRender();

                if (renderedText != null) {
                    html += renderedText.outerHTML;
                }

                html += '    </td>';
                html += '</tr>';
            }

            element.innerHTML = html;
        }

        return element;
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';

        // render each fact 
        let speak = null;
        if (this._facts.length > 0) {
            speak = '';
            for (var i = 0; i < this._facts.length; i++) {
                let speech = this._facts[i].renderSpeech();
                if (speech)
                    speak += speech;
            }
        }
        return '<p>' + speak + '\n</p>\n';
    }

}

export class Image extends CardElement {
    style: ImageStyle = ImageStyle.Normal;
    url: string;

    get useDefaultSizing() {
        return false;
    }

    parse(json: any) {
        super.parse(json);

        this.url = json["url"];
        if (json["size"])
            this.size = json["size"];
            
        this.style = stringToImageStyle(json["style"], ImageStyle.Normal);
    }

    render(): HTMLElement {
        let imageElement: HTMLImageElement = null;

        if (!isNullOrEmpty(this.url)) {
            imageElement = document.createElement("img");

            let cssStyle = "image";

            switch (this.size) {
                case Size.Auto:
                    cssStyle += " autoSize";
                    break;
                case Size.Stretch:
                    cssStyle += " stretch";
                    break;
                case Size.Small:
                    cssStyle += " small";
                    break;
                case Size.Large:
                    cssStyle += " large";
                    break;
                default:
                    cssStyle += " medium";
                    break;
            }

            if (this.style == ImageStyle.Person) {
                cssStyle += " person";
            }

            imageElement.className = cssStyle;

            imageElement.src = this.url;
        }

        return imageElement;
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';
        return null;
    }
}

export class ImageSet extends CardElement {
    private _images: Array<Image> = [];
    imageSize: Size = Size.Medium;

    get images(): Array<Image> {
        return this._images;
    }

    parse(json: any) {
        super.parse(json);

        this.imageSize = stringToSize(json["size"], Size.Medium);

        if (json["images"] != null) {
            let imageArray = json["images"] as Array<any>;

            for (let i = 0; i < imageArray.length; i++) {
                let image = new Image(this.container);
                image.size = this.imageSize;
                image.parse(imageArray[i]);
                this._images.push(image);
            }
        }
    }

    render(): HTMLElement {
        let element: HTMLElement = null;

        if (this._images.length > 0) {
            element = document.createElement("div");
            element.className = "imageSet";

            for (var i = 0; i < this._images.length; i++) {
                let renderedImage = this._images[i].internalRender();
                renderedImage.style.margin = "0px";
                renderedImage.style.marginRight = "10px";

                appendChild(element, renderedImage);
            }
        }

        return element;
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak;

        let speak = null;
        if (this._images.length > 0) {
            speak = '';
            for (var i = 0; i < this._images.length; i++) {
                speak += this._images[i].renderSpeech();
            }
        }

        return speak;
    }
}

export abstract class Action {
    private _owner: CardElement;

    name: string;

    static create(owner: CardElement, typeName: string): Action {
        switch (typeName) {
            case "OpenUri":
            case "ViewAction":
                return new OpenUri(owner);
            case "HttpPOST":
                return new HttpPOST(owner);
            case "ActionCard":
                return new ActionCard(owner);
            default:
                throw new Error("Unknown action type: " + typeName);
        }
    }

    get owner(): CardElement {
        return this._owner;
    }

    constructor(owner: CardElement) {
        this._owner = owner;
    }

    parse(json: any) {
        this.name = json["name"];
    }

    renderUi(container: Container, requiresTopSpacer: boolean = false): HTMLElement {
        return null;
    }

    get hasUi(): boolean {
        return false;
    }
}

export abstract class ExternalAction extends Action {
}

export class TargetUri {
    os: string;
    uri: string;

    parse(json: any) {
        this.os = json["os"];
        this.uri = json["uri"];
    }
}

export class OpenUri extends ExternalAction {
    private _targets: Array<TargetUri> = [];

    addTarget(): TargetUri {
        let targetUri = new TargetUri();

        this._targets.push(targetUri);

        return targetUri;
    }

    parse(json: any) {
        super.parse(json);

        if (json["@type"] == "ViewAction") {
            let target = new TargetUri();

            target.uri = (json["target"] as Array<any>)[0];
        }
        else {
            if (json["targets"] != undefined) {
                let targetArray = json["targets"] as Array<any>;

                for (let i = 0; i < targetArray.length; i++) {
                    let target = this.addTarget();
                    target.parse(targetArray[i]);
                }
            }
        }
    }
}

export class HttpPOST extends ExternalAction {
    target: string;
    body: string;
    bodyContentType: string;
    successMessage: string;
    errorMessage: string;

    parse(json: any) {
        super.parse(json);

        this.target = json["target"];
        this.body = json["body"];
        this.bodyContentType = json["bodyContentType"];
        this.successMessage = json["successMessage"];
        this.errorMessage = json["errorMessage"];
    }
}

export abstract class Input extends CardElement {
    id: string;
    title: string;
    value: string;

    static createInput(container: Container, typeName: string): Input {
        switch (typeName) {
            case "TextInput":
                return new TextInput(container);
            case "ChoiceInput":
                return new MultichoiceInput(container);
            case "DateInput":
                return new DateInput(container);
            case "ToggleInput":
                return new ToggleInput(container);
            default:
                throw new Error("Unknown input type: " + typeName);
        }
    }

    parse(json: any) {
        super.parse(json);

        this.id = json["id"];
        this.title = json["title"];
        this.value = json["value"];
    }

    abstract render(): HTMLElement;

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak;

        if (this.title)
            return '<s>' + this.title + '</s>\n';
        return null;
    }
}

export class TextInput extends Input {
    maxLength: number;
    isMultiline: boolean;

    constructor(container: Container) {
        super(container);

        this.size = Size.Stretch;
    }

    parse(json: any) {
        super.parse(json);

        this.maxLength = json["maxLength"];
        this.isMultiline = json["isMultiline"];
    }

    render(): HTMLElement {
        let element = document.createElement("textarea");
        element.className = "input textInput";

        if (this.isMultiline) {
            element.className += " multiline";
        }

        element.placeholder = this.title;

        return element;
    }
}

export class Choice {
    display: string;
    value: string;

    parse(json: any) {
        this.display = json["display"];
        this.value = json["value"];
    }
}

export class ToggleInput extends Input {
    render(): HTMLElement {
        let element = document.createElement("div");
        element.innerHTML = '<input type="checkbox" class="input toggleInput"></input><div class="toggleInputLabel">' + this.title + '</div>';

        return element;
    }
}

export class MultichoiceInput extends Input {
    private _choices: Array<Choice> = [];

    constructor(container: Container) {
        super(container);

        this.size = Size.Medium;
    }

    parse(json: any) {
        super.parse(json);

        if (json["choices"] != undefined) {
            let choiceArray = json["choices"] as Array<any>;

            for (let i = 0; i < choiceArray.length; i++) {
                let choice = new Choice();

                choice.parse(choiceArray[i]);

                this._choices.push(choice);
            }
        }
    }

    render(): HTMLElement {
        let selectElement = document.createElement("select");
        selectElement.className = "input multichoiceInput";

        for (let i = 0; i < this._choices.length; i++) {
            let option = document.createElement("option");
            option.value = this._choices[i].value;
            option.text = this._choices[i].display;

            appendChild(selectElement, option);
        }

        return selectElement;
    }
}

export class DateInput extends Input {
    includeTime: boolean;

    constructor(container: Container) {
        super(container);

        this.size = Size.Medium;
    }

    parse(json: any) {
        super.parse(json);

        this.includeTime = json["includeTime"];
    }

    render(): HTMLElement {
        let container = document.createElement("div");
        container.className = "input";
        container.style.display = "flex";

        let datePicker = document.createElement("input");
        datePicker.type = "date";
        datePicker.className = "dateInput";

        appendChild(container, datePicker);

        if (this.includeTime) {
            datePicker.style.flex = "1 1 67%";

            let timePicker = document.createElement("input");
            timePicker.type = "time";
            timePicker.className = "timeInput";
            timePicker.style.flex = "1 1 33%";

            appendChild(container, timePicker);
        }
        else {
            datePicker.style.flex = "1 1 100%";
        }

        return container;
    }
}

export class ActionCard extends Action {
    private _allowedActionTypes: Array<string> = ["OpenUri", "HttpPOST"];
    private _inputs: Array<Input> = [];
    private _actions: Array<ExternalAction> = [];
    private _card: Container;

    name: string;

    get hasUi(): boolean {
        return true;
    }

    get inputs(): Array<Input> {
        return this._inputs;
    }

    get actions(): Array<Action> {
        return this._actions;
    }

    parse(json: any) {
        super.parse(json);

        if (json["card"] != undefined) {
            this._card = new Container(this.owner.container, ["ActionSet"]);
            this._card.parse(json["card"]);
        }

        if (json["inputs"] != undefined) {
            let inputArray = json["inputs"] as Array<any>;

            for (let i = 0; i < inputArray.length; i++) {
                let input = Input.createInput(this.owner.container, inputArray[i]["@type"]);

                input.parse(inputArray[i]);

                this._inputs.push(input);
            }
        }

        if (json["actions"] != undefined) {
            let actionArray = json["actions"] as Array<any>;

            for (let i = 0; i < actionArray.length; i++) {
                let actionJson = actionArray[i];
                let typeIsAllowed: boolean = false;

                for (let j = 0; j < this._allowedActionTypes.length; j++) {
                    if (actionJson["@type"] === this._allowedActionTypes[j]) {
                        typeIsAllowed = true;
                        break;
                    }
                }

                if (typeIsAllowed) {
                    let action = Action.create(this.owner, actionJson["@type"]);

                    action.parse(actionJson);

                    this._actions.push(action);
                }
            }
        }
    }

    private actionClicked(actionButton: ActionButton) {
        alert('Now executing "' + actionButton.text + '"');
    }

    renderUi(container: Container, needsTopSpacer: boolean = false): HTMLElement {
        let actionCardElement = document.createElement("div");

        if (this._card != null) {
            appendChild(actionCardElement, this._card.internalRender());
        }
        else {
            for (let i = 0; i < this._inputs.length; i++) {
                let inputElement = this._inputs[i].internalRender();

                if (i == 0) {
                    this._inputs[i].removeTopSpacing(inputElement);
                }

                appendChild(actionCardElement, inputElement);
            }
        }

        let buttonsContainer = document.createElement("div");
        buttonsContainer.style.display = "flex";
        buttonsContainer.style.marginTop = "16px";

        for (let i = 0; i < this._actions.length; i++) {
            let actionButton = new ActionButton(this._actions[i], ActionButtonStyle.Push);
            actionButton.text = this._actions[i].name;

            actionButton.onClick.subscribe(
                (ab, args) => {
                    this.actionClicked(ab);
                });

            if (this._actions.length > 1 && i < this._actions.length - 1) {
                actionButton.element.style.marginRight = "16px";
            }

            appendChild(buttonsContainer, actionButton.element);
        }

        appendChild(actionCardElement, buttonsContainer);

        return actionCardElement;
    }
}

export enum ActionButtonStyle {
    Link,
    Push
}

export enum ActionButtonState {
    Normal,
    Expanded,
    Subdued
}

export class ActionButton {
    private _action: Action;
    private _style: ActionButtonStyle;
    private _onClick: EventDispatcher<ActionButton> = new EventDispatcher<ActionButton>();
    private _element: HTMLElement = null;
    private _state: ActionButtonState = ActionButtonState.Normal;
    private _text: string;

    private click() {
        this._onClick.dispatch(this, null);
    }

    private updateCssStyle() {
        let cssStyle = this._style == ActionButtonStyle.Link ? "linkButton " : "pushButton ";

        switch (this._state) {
            case ActionButtonState.Expanded:
                cssStyle += " expanded";
                break;
            case ActionButtonState.Subdued:
                cssStyle += " subdued";
                break;
        }

        this._element.className = cssStyle;
    }

    constructor(action: Action, style: ActionButtonStyle) {
        this._action = action;
        this._style = style;
        this._element = document.createElement("div");
        this._element.onclick = (e) => { this.click(); };

        this.updateCssStyle();
    }

    get action() {
        return this._action;
    }

    get onClick(): IEvent<ActionButton> {
        return this._onClick;
    }

    get text(): string {
        return this._text;
    }

    set text(value: string) {
        this._text = value;
        this._element.innerText = this._text;
    }

    get element(): HTMLElement {
        return this._element;
    }

    get state(): ActionButtonState {
        return this._state;
    }

    set state(value: ActionButtonState) {
        this._state = value;

        this.updateCssStyle();
    }
}

export class ActionSet extends CardElement {
    static buttonStyle: ActionButtonStyle = ActionButtonStyle.Push;

    private _actionButtons: Array<ActionButton> = [];
    private _actionCardContainer: HTMLDivElement;
    private _actions: Array<Action> = [];
    private _expandedAction: Action = null;

    private hideActionCardPane() {
        this._actionCardContainer.innerHTML = '';
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";

        this.container.showBottomSpacer(this);
    }

    private showActionCardPane(action: Action) {
        this.container.hideBottomSpacer(this);

        this._actionCardContainer.innerHTML = '';
        this._actionCardContainer.style.padding = null;
        this._actionCardContainer.style.marginTop = this._actions.length > 1 ? null : "0px";

        appendChild(
            this._actionCardContainer,
            action.renderUi(this.container, this._actions.length > 1));
    }

    private actionClicked(actionButton: ActionButton) {
        if (!actionButton.action.hasUi) {
            for (var i = 0; i < this._actionButtons.length; i++) {
                this._actionButtons[i].state = ActionButtonState.Normal;
            }

            this.hideActionCardPane();

            alert("Executing action " + actionButton.text)
        }
        else {
            if (actionButton.action === this._expandedAction) {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    this._actionButtons[i].state = ActionButtonState.Normal;
                }

                this._expandedAction = null;

                this.hideActionCardPane();
            }
            else {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    if (this._actionButtons[i] !== actionButton) {
                        this._actionButtons[i].state = ActionButtonState.Subdued;
                    }
                }

                actionButton.state = ActionButtonState.Expanded;

                this._expandedAction = actionButton.action;

                this.showActionCardPane(actionButton.action);
            }
        }
    }

    get actions(): Array<Action> {
        return this._actions;
    }

    get hideOverflow(): boolean {
        return false;
    }

    parse(json: any) {
        super.parse(json);

        if (json["actions"] != null) {
            var actionArray = json["actions"] as Array<any>;

            for (var i = 0; i < actionArray.length; i++) {
                let action = Action.create(this, actionArray[i]["@type"]);

                action.parse(actionArray[i]);

                this._actions.push(action);
            }
        }
    }

    render(): HTMLElement {
        let element = document.createElement("div");
        element.className = "actionSet";

        let buttonStrip = document.createElement("div");
        buttonStrip.className = "buttonStrip";

        this._actionCardContainer = document.createElement("div");
        this._actionCardContainer.className = "actionCardContainer";
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";

        if (this._actions.length == 1 && this._actions[0] instanceof ActionCard) {
            this.showActionCardPane(this._actions[0]);
        }
        else {
            for (let i = 0; i < this._actions.length; i++) {
                let buttonStripItem = document.createElement("div");
                buttonStripItem.className = "buttonStripItem";

                let actionButton = new ActionButton(this._actions[i], ActionSet.buttonStyle);
                actionButton.text = this._actions[i].name;

                actionButton.onClick.subscribe(
                    (ab, args) => {
                        this.actionClicked(ab);
                    });

                this._actionButtons.push(actionButton);

                if (i < this._actions.length - 1) {
                    buttonStripItem.className += " buttonStripItemSpacer";
                }

                appendChild(buttonStripItem, actionButton.element);
                appendChild(buttonStrip, buttonStripItem);
            }
        }

        appendChild(element, buttonStrip);

        appendChild(element, this._actionCardContainer);

        return element;
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';

        // // render each fact 
        // let speak = null;
        // if (this._actionButtons.length > 0) {
        //     speak = '';
        //     for (var i = 0; i < this._actionButtons.length; i++) {
        //         let speech = this._actionButtons[i].renderSpeech();
        //         if (speech)
        //             speak += speech;
        //     }
        // }
        // return '<p>' + speak + '\n</p>\n';
        return null;
    }
}

export class Separator extends CardElement {
    parse(json: any) {
        super.parse(json);

        // Nothing else to parse
    }

    render() {
        let element = document.createElement("div");
        element.className = "separator";

        return element;
    }

    renderSpeech(): string {
        return null;
    }

}

export class Container extends CardElement {
    private _forbiddenItemTypes: Array<string>;
    private _items: Array<CardElement> = [];
    private _element: HTMLDivElement;
    private _textColor: TextColor = TextColor.Default;
    private _itemsCollectionPropertyName: string;

    private isAllowedItemType(elementType: string) {
        if (this._forbiddenItemTypes == null) {
            return true;
        }

        for (let i = 0; i < this._forbiddenItemTypes.length; i++) {
            if (elementType == this._forbiddenItemTypes[i]) {
                return false;
            }
        }

        if (this.container != null) {
            return this.container.isAllowedItemType(elementType);
        }
        else {
            return true;
        }
    }

    protected get cssClassName(): string {
        return "container";
    }

    backgroundImageUrl: string;
    backgroundColor: string;

    constructor(
        container: Container,
        forbiddenItemTypes: Array<string> = null,
        itemsCollectionPropertyName: string = "items") {
        super(container);

        this._itemsCollectionPropertyName = itemsCollectionPropertyName;
        this._forbiddenItemTypes = forbiddenItemTypes;
    }

    get items(): Array<CardElement> {
        return this._items;
    }

    get elementCount(): number {
        return this._items.length;
    }

    get hideOverflow() {
        return false;
    }

    get textColor(): TextColor {
        if (this.container == null) {
            return this._textColor == TextColor.Default ? TextColor.Dark : this._textColor;
        }

        if (this._textColor == TextColor.Default) {
            return this.container.textColor;
        }

        return this._textColor;
    }

    set textColor(value: TextColor) {
        this._textColor = value;
    }

    addElement(element: CardElement) {
        if (element != null) {
            this._items.push(element);
        }
    }

    isLastElement(element: CardElement): boolean {
        return this._items.indexOf(element) == this.elementCount - 1;
    }

    getElement(index: number): CardElement {
        return this._items[index];
    }

    showBottomSpacer(requestingElement: CardElement) {
        if (this.isLastElement(requestingElement)) {
            this._element.style.paddingBottom = null;

            if (this.container != null) {
                this.container.showBottomSpacer(this);
            }
        }
    }

    hideBottomSpacer(requestingElement: CardElement) {
        if (this.isLastElement(requestingElement)) {
            this._element.style.paddingBottom = "0px";

            if (this.container != null) {
                this.container.hideBottomSpacer(this);
            }
        }
    }

    parse(json: any) {
        super.parse(json);

        this.backgroundImageUrl = json["backgroundImage"];
        this.backgroundColor = json["backgroundColor"];

        this._textColor = stringToTextColor(json["textColor"], TextColor.Default);

        if (json[this._itemsCollectionPropertyName] != null) {
            let items = json[this._itemsCollectionPropertyName] as Array<any>;

            for (let i = 0; i < items.length; i++) {
                let elementType = items[i]["@type"];

                if (this.isAllowedItemType(elementType)) {
                    let element = CardElement.createElement(this, elementType);

                    element.parse(items[i]);

                    this.addElement(element);
                }
                else {
                    throw new Error("Elements of type " + elementType + " are not allowed in this container.");
                }
            }
        }
    }

    render(): HTMLElement {
        if (this.elementCount > 0) {
            this._element = document.createElement("div");
            this._element.className = this.cssClassName;

            if (!isNullOrEmpty(this.backgroundColor)) {
                this._element.style.backgroundColor = this.backgroundColor;
            }

            let html: string = '';
            let previousElement: CardElement = null;

            for (var i = 0; i < this.elementCount; i++) {
                let renderedElement = this.getElement(i).internalRender();

                if (renderedElement != null) {
                    if (previousElement == null) {
                        this.getElement(i).removeTopSpacing(renderedElement);
                    }

                    appendChild(this._element, renderedElement);
                }

                previousElement = this.getElement(i);
            }

            if (!isNullOrEmpty(this.backgroundImageUrl)) {
                this._element.style.backgroundImage = 'url("' + this.backgroundImageUrl + '")';
                this._element.style.backgroundRepeat = "no-repeat";
                this._element.style.backgroundSize = "cover";
            }
        }

        return this._element;
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak;

        // render each item
        let speak = null;
        if (this._items.length > 0) {
            speak = '';
            for (var i = 0; i < this._items.length; i++) {
                var result = this._items[i].renderSpeech();
                if (result)
                    speak += result;
            }
        }
        return speak;
    }

    getRootContainer(): Container {
        let currentContainer: Container = this;

        while (currentContainer.container != null) {
            currentContainer = currentContainer.container;
        }

        return currentContainer;
    }
}

export class Column extends Container {
    private get useWeight(): boolean {
        return this.size === undefined;
    }

    weight: number = 100;

    protected get cssClassName(): string {
        return "column";
    }

    parse(json: any) {
        super.parse(json);

        this.size = stringToSize(json["size"], undefined);

        if (this.size === undefined) {
            this.weight = Number(json["size"]);
        }
    }

    adjustLayout(element: HTMLElement) {
        if (this.useWeight) {
            element.style.flex = "1 1 " + this.weight + "%";
        }
        else {
            switch (this.size) {
                case Size.Stretch:
                    element.style.flex = "1 1 auto";
                    break;
                default: // Default to Auto
                    element.style.flex = "0 0 auto";
                    break;
            }
        }
    }
}

export class ColumnSet extends CardElement {
    private _columns: Array<Column> = [];

    addColumn(): Column {
        let column = new Column(this.container, ["ActionSet"]);

        this._columns.push(column);

        return column;
    }

    parse(json: any) {
        super.parse(json);

        if (json["columns"] != null) {
            let itemArray = json["columns"] as Array<any>;

            for (let i = 0; i < itemArray.length; i++) {
                let column = this.addColumn();
                column.parse(itemArray[i]);
            }
        }
    }

    render(): HTMLElement {
        if (this._columns.length > 0) {
            let element = document.createElement("div");
            element.className = "columnSet";
            element.style.display = "flex";

            for (let i = 0; i < this._columns.length; i++) {
                let renderedColumn = this._columns[i].internalRender();

                appendChild(element, renderedColumn);

                if (this._columns.length > 1 && i < this._columns.length - 1) {
                    let spacer = document.createElement("div");
                    spacer.className = "columnSpacer";
                    spacer.style.flex = "0 0 auto";

                    appendChild(element, spacer);
                }
            }

            return element;
        }
        else {
            return null;
        }
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak;

        // render each item
        let speak = '';
        if (this._columns.length > 0) {
            for (var i = 0; i < this._columns.length; i++) {
                speak += this._columns[i].renderSpeech();
            }
        }
        return speak;
    }

}

export class AdaptiveCard {
    root = new Container(null, null, "body");
    title: string;
    description1: string;
    description2: string;

    parse(json: any) {
        this.title = json["title"];
        this.description1 = json["description1"];
        this.description2 = json["description2"];

        this.root.parse(json);
    }

    render(): HTMLElement {
        let renderedContainer = this.root.internalRender();
        renderedContainer.className = "rootContainer";

        return renderedContainer;
    }

    renderSpeech(): string {
        return this.root.renderSpeech();
    }
}