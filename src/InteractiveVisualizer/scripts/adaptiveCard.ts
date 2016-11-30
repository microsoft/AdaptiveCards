/*
Strongly typed events from https://keestalkstech.com/2016/03/strongly-typed-event-handlers-in-typescript-part-1/
*/
class Size {
    static Auto = new Size("auto");
    static Stretch = new Size("stretch");
    static Small = new Size("small", 100, 40);
    static Medium = new Size("medium", 200, 80);
    static Large = new Size("large", 300, 160);

    protected constructor(name: string, physicalSize: number = undefined, physicalPictureSize: number = undefined) {
        this.name = name;
        this.physicalSize = physicalSize;
        this.physicalPictureSize = physicalPictureSize;
    }

    static parse(name: string, defaultValue: Size): Size {
        for (let key in Size) {
            if (!isNullOrEmpty(Size[key].name) && Size[key].name == name) {
                return Size[key];
            }
        }

        return defaultValue;
    }

    readonly name: string;
    physicalSize: number;
    physicalPictureSize: number;
}

enum Spacing {
    None,
    Default
}

enum TextSize {
    Small,
    Normal,
    Medium,
    Large,
    ExtraLarge
}

enum TextWeight {
    Lighter,
    Normal,
    Bolder
}

enum TextColor {
    Default,
    Dark,
    Light,
    Accent
}

enum HorizontalAlignment {
    Left,
    Center,
    Right
}

enum PictureStyle {
    Normal,
    Person
}

function stringToTextSize(value: string, defaultValue: TextSize): TextSize {
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

function stringToTextWeight(value: string, defaultValue: TextWeight): TextWeight {
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

function stringToTextColor(value: string, defaultValue: TextColor): TextColor {
    switch (value) {
        case "default":
            return TextColor.Default;
        case "dark":
            return TextColor.Dark;
        case "light":
            return TextColor.Light;
        case "accent":
            return TextColor.Accent;
        default:
            return defaultValue;
    }
}

function stringToHorizontalAlignment(value: string, defaultValue: HorizontalAlignment): HorizontalAlignment {
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

function stringToPictureStyle(value: string, defaultValue: PictureStyle): PictureStyle {
    switch (value) {
        case "person":
            return PictureStyle.Person;
        case "normal":
            return PictureStyle.Normal;
        default:
            return defaultValue;
    }
}

interface IEvent<TSender> {
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

function isNullOrEmpty(value: string): boolean {
    return value === undefined || value === null || value === "";
}

function appendChild(node: Node, child: Node) {
    if (child != null && child != undefined) {
        node.appendChild(child);
    }
}

abstract class CardElement {
    static createElement(container: Container, typeName: string): CardElement {
        switch (typeName) {
            case "TextBlock":
                return new TextBlock(container);
            case "Picture":
                return new Picture(container);
            case "PictureGallery":
                return new PictureGallery(container);
            case "ActionGroup":
                return new ActionGroup(container);
            case "FactGroup":
                return new FactGroup(container);
            case "Separator":
                return new Separator(container);
            case "ColumnGroup":
                return new ColumnGroup(container);
            case "TextInput":
                return new TextInput(container);
            case "DateInput":
                return new DateInput(container);
            case "MultichoiceInput":
                return new MultichoiceInput(container);
            default:
                throw new Error("Unknown element type: " + typeName);
        }
    }

    private _container: Container;

    size: Size = Size.Auto;
    horizontalAlignment: HorizontalAlignment = HorizontalAlignment.Left;
    topSpacing: Spacing = Spacing.Default;

    constructor(container: Container) {
        this._container = container;
    }

    get container(): Container {
        return this._container;
    }

    get hideOverflow(): boolean {
        return true;
    }

    abstract render(): HTMLElement;

    removeTopSpacing(element: HTMLElement) {
        element.style.marginTop = "0px";
    }

    adjustLayout(element: HTMLElement) {
        if (this.size == Size.Stretch) {
            element.style.width = "100%";
        }
        else if (this.size != Size.Auto) {
            element.style.width = this.size.physicalSize.toString() + "px";
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
        let renderedElement =  this.render();

        if (renderedElement != null) {
            this.adjustLayout(renderedElement);
        }

        if (this.topSpacing == Spacing.None) {
            this.removeTopSpacing(renderedElement);
        }

        return renderedElement;
    }

    parse(json: any) {
        this.size = Size.parse(json["size"], this.size);
        this.horizontalAlignment = stringToHorizontalAlignment(json["horizontalAlignment"], this.horizontalAlignment);
        
        if (json["topSpacing"] === "none") {
            this.topSpacing = Spacing.None;
        }
    }
}

class TextBlock extends CardElement {
    textSize: TextSize = TextSize.Normal;
    textWeight: TextWeight = TextWeight.Normal;
    textColor: TextColor = TextColor.Default;
    text: string;
    isSubtle: boolean = false;
    wrap: boolean = true;

    parse(json: any) {
        super.parse(json);

        this.text = json["text"];
        this.textSize = stringToTextSize(json["textSize"], TextSize.Normal);
        this.textWeight = stringToTextWeight(json["textWeight"], TextWeight.Normal);
        this.textColor = stringToTextColor(json["textColor"], TextColor.Default);
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

            let firstChild = <HTMLElement>element.firstChild;
            firstChild.className = cssStyle;

            var anchors = firstChild.getElementsByTagName("a");

            for (var i = 0; i < anchors.length; i++) { 
                anchors[i].target = "_blank";
            }

            if (!this.wrap) {
                firstChild.style.whiteSpace = "nowrap";
                firstChild.style.textOverflow = "ellipsis";
            }

            return firstChild;
        }
        else {
            return null;
        }
    }

    removeTopSpacing(element: HTMLElement) {
        element.style.paddingTop = "0px";
    }
}

class Fact {
    name: string;
    value: string;

    parse(json: any) {
        this.name = json["name"];
        this.value = json["value"];
    }
}

class FactGroup extends CardElement {
    private _items: Array<Fact> = [];

    get items(): Array<Fact> {
        return this._items;
    }

    parse(json: any) {
        super.parse(json);

        if (json["items"] != null) {
            var factArray = json["items"] as Array<any>;

            for (var i = 0; i < factArray.length; i++) {
                let fact = new Fact();

                fact.parse(factArray[i]);

                this._items.push(fact);
            }
        }
    }

    render(): HTMLElement {
        let element: HTMLElement = null;

        if (this._items.length > 0) {
            element = document.createElement("table");
            element.className = "factGroup";

            let html: string = '';

            for (var i = 0; i < this._items.length; i++) {
                html += '<tr>';
                html += '    <td style="border-width: 0px; padding: 0px; border-style: none; min-width: 100px; vertical-align: top">';

                let textBlock = new TextBlock(this.container);
                textBlock.text = this._items[i].name;
                textBlock.textWeight = TextWeight.Bolder;
                textBlock.topSpacing = Spacing.None;

                html += textBlock.internalRender().outerHTML;

                html += '    </td>';
                html += '    <td style="border-width: 0px; padding: 0px; border-style: none; vertical-align: top; padding: 0px 0px 0px 10px">';

                textBlock = new TextBlock(this.container);
                textBlock.text = this._items[i].value;
                textBlock.textWeight = TextWeight.Lighter;
                textBlock.topSpacing = Spacing.None;
                
                html += textBlock.internalRender().outerHTML;

                html += '    </td>';
                html += '</tr>';
            }

            element.innerHTML = html;
        }

        return element;
    }
}

class Picture extends CardElement {
    style: PictureStyle = PictureStyle.Normal;
    url: string;

    parse(json: any) {
        super.parse(json);
        
        this.url = json["url"];
        this.style = stringToPictureStyle(json["style"], PictureStyle.Normal);
    }

    render(): HTMLElement {
        let image: HTMLImageElement = null;

        if (!isNullOrEmpty(this.url)) {
            image = document.createElement("img");
            image.className = "picture";

            if (this.size == Size.Auto) {
                image.style.maxWidth = "100%";
            }
            else {
                image.style.maxWidth = this.size.physicalPictureSize.toString() + "px"; 
                image.style.maxHeight = this.size.physicalPictureSize.toString() + "px";

                if (this.style == PictureStyle.Person) {
                    image.className = "inCircle";
                    image.style.borderRadius = (this.size.physicalPictureSize / 2).toString() + "px";
                    image.style.backgroundPosition = "50% 50%";
                    image.style.backgroundRepeat = "no-repeat";
                }
            }

            image.src = this.url;
        }

        return image;
    }
}

class PictureGallery extends CardElement {
    private _items: Array<Picture> = [];

    pictureSize: Size = Size.Medium;

    get items(): Array<Picture> {
        return this._items;
    }

    parse(json: any) {
        super.parse(json);
        
        this.pictureSize = Size.parse(json["imageSize"], Size.Medium);

        if (json["items"] != null) {
            let pictureArray = json["items"] as Array<any>;

            for (let i = 0; i < pictureArray.length; i++) {
                let picture = new Picture(this.container);

                picture.size = this.pictureSize;
                picture.url = pictureArray[i];

                this._items.push(picture);
            }
        }
    }

    render(): HTMLElement {
        let element: HTMLElement = null;

        if (this._items.length > 0) {
            element = document.createElement("div");
            element.className = "pictureGallery";

            for (var i = 0; i < this._items.length; i++) {
                let renderedPicture =  this._items[i].render();
                renderedPicture.style.margin = "0px";
                renderedPicture.style.marginRight = "10px";

                appendChild(element, renderedPicture);
            }
        }

        return element;
    }
}

abstract class Action {
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

abstract class ExternalAction extends Action {
}

class TargetUri {
    os: string;
    uri: string;

    parse(json: any) {
        this.os = json["os"];
        this.uri = json["uri"];
    }
}

class OpenUri extends ExternalAction {
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

class HttpPOST extends ExternalAction {
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

abstract class Input extends CardElement {
    id: string;
    title: string;
    value: string;

    static createInput(container: Container, typeName: string): Input {
        switch (typeName) {
            case "TextInput":
                return new TextInput(container);
            case "MultichoiceInput":
                return new MultichoiceInput(container);
            case "DateInput":
                return new DateInput(container);
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
}

class TextInput extends Input {
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
        element.placeholder = this.title;

        return element;
    }
}

class Choice {
    display: string;
    value: string;

    parse(json: any) {
        this.display = json["display"];
        this.value = json["value"];
    }
}

class MultichoiceInput extends Input {
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

class DateInput extends Input {
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

class ActionCard extends Action {
    private _allowedActionTypes: Array<string> = [ "OpenUri", "HttpPOST" ]; 
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
            this._card = new Container(this.owner.container, [ "ActionGroup" ]);
            this._card.topSpacing = Spacing.None;
            this._card.parse(json["card"]);
        }

        if (json["inputs"] != undefined) {
            let inputArray = json["inputs"] as Array<any>;

            for (let i = 0; i < inputArray.length; i++) {
                let input = Input.createInput(this.owner.container, inputArray[i]["@type"]);

                if (i == 0) {
                    input.topSpacing = Spacing.None;
                }

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

                if (i > 0) {
                    inputElement.style.marginTop = "10px";
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

enum ActionButtonStyle {
    Link,
    Push
}

enum ActionButtonState {
    Normal,
    Expanded,
    Subdued
}

class ActionButton {
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

class ActionGroup extends CardElement {
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
        this._actionCardContainer.style.marginTop = null;

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
        
        if (json["items"] != null) {
            var actionArray = json["items"] as Array<any>;

            for (var i = 0; i < actionArray.length; i++) {
                let action = Action.create(this, actionArray[i]["@type"]);

                action.parse(actionArray[i]);

                this._actions.push(action);
            }
        }
    }

    render(): HTMLElement {
        let element = document.createElement("div");
        element.className = "actionGroup";

        let buttonStrip = document.createElement("div");
        buttonStrip.className = "buttonStrip";

        if (this._actions.length == 1 && this._actions[0] instanceof ActionCard) {
            this.showActionCardPane(this._actions[0]);
        }
        else {
            for (let i = 0; i < this._actions.length; i++) {
                let buttonStripItem = document.createElement("div");
                buttonStripItem.className = "buttonStripItem";

                if (i < this._actions.length - 1) {
                    buttonStripItem.style.marginRight = "20px";
                }

                let actionButton = new ActionButton(this._actions[i], ActionButtonStyle.Link);
                actionButton.text = this._actions[i].name;

                actionButton.onClick.subscribe(
                    (ab, args) => {
                        this.actionClicked(ab);
                    });
                
                this._actionButtons.push(actionButton);

                appendChild(buttonStripItem, actionButton.element);
                appendChild(buttonStrip, buttonStripItem);
            }
        }

        appendChild(element, buttonStrip);

        this._actionCardContainer = document.createElement("div");
        this._actionCardContainer.className = "actionCardContainer";
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";

        appendChild(element, this._actionCardContainer);

        return element;
    }
}

class Separator extends CardElement {
    parse(json: any) {
        super.parse(json);
        
        // Nothing else to parse
    }

    render() {
        let element = document.createElement("div");
        element.className = "separator";

        return element;
    }
}

class Container extends CardElement {
    private _forbiddenItemTypes: Array<string>;
    private _items: Array<CardElement> = [];
    private _element: HTMLDivElement;
    private _textColor: TextColor = TextColor.Default;

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

    backgroundImageUrl: string;
    backgroundColor: string;

    constructor(container: Container, forbiddenItemTypes: Array<string> = null) {
        super(container);

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

        if (json["items"] != null) {
            let items = json["items"] as Array<any>;

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
            this._element.className = "container";

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

    getRootContainer(): Container {
        let currentContainer: Container = this;

        while (currentContainer.container != null) {
            currentContainer = currentContainer.container;
        }

        return currentContainer;
    }
}

class Column extends Container {
    private _useWeight: boolean = false;
    private _weight: number = 100;

    parse(json: any) {
        super.parse(json);

        this.size = Size.parse(json["size"], undefined);

        if (this.size === undefined) {
            this._useWeight = true;
            this._weight = Number(json["size"]);
        }
    }

    adjustLayout(element: HTMLElement) {
        if (this._useWeight) {
            element.style.flex = "1 1 " + this._weight + "%";
        }
        else {
            switch (this.size) {
                case Size.Auto:
                    element.style.flex = "0 0 auto";
                    break;
                case Size.Stretch:
                    element.style.flex = "1 1 auto";
                    break;
                default:
                    element.style.flex = "0 0 " + this.size.physicalSize + "px";
                    break;
            }
        }
    }
}

class ColumnGroup extends CardElement {
    private _items: Array<Column> = [];

    addColumn(): Column {
        let column = new Column(this.container, ["ColumnGroup", "ActionGroup"]);
        column.topSpacing = Spacing.None;

        this._items.push(column);

        return column;
    }

    parse(json: any) {
        super.parse(json);

        if (json["items"] != null) {
            let itemArray = json["items"] as Array<any>;

            for (let i = 0; i < itemArray.length; i++) {
                let column = this.addColumn();
                column.parse(itemArray[i]);
            }
        }
    }

    render(): HTMLElement {
        if (this._items.length > 0) {
            let element = document.createElement("div");
            element.className = "columnGroup";
            element.style.display = "flex";

            for (let i = 0; i < this._items.length; i++) {
                let renderedColumn = this._items[i].internalRender();

                appendChild(element, renderedColumn);

                if (this._items.length > 1 && i < this._items.length - 1) {
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
}

class AdaptiveCard {
    private _rootContainer = new Container(null);
    
    textColor: TextColor = TextColor.Dark;

    parse(json: any) {
        this._rootContainer.backgroundImageUrl = json["backgroundImage"];

        if (json["sections"] != undefined) {
            let sectionArray = json["sections"] as Array<any>;

            for (var i = 0; i < sectionArray.length; i++) {
                let section = new Container(this._rootContainer, [ "Section" ]);

                section.parse(sectionArray[i]);

                this._rootContainer.addElement(section);
            }
        }
    }

    render(): HTMLElement {
        this._rootContainer.textColor = this.textColor;

        let renderedContainer = this._rootContainer.internalRender();
        renderedContainer.className = "rootContainer";

        return renderedContainer;
   }
}