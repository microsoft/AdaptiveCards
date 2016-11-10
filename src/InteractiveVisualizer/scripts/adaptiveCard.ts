/*
Strongly typed events from https://keestalkstech.com/2016/03/strongly-typed-event-handlers-in-typescript-part-1/
*/

enum TextContrast {
    DarkOnLight,
    LightOnDark
}

function stringToTextContrast(value: string): TextContrast {
    switch (value) {
        case "darkOnLight":
            return TextContrast.DarkOnLight;
        case "lightOnDark":
            return TextContrast.LightOnDark;
        default:
            return undefined;
    }
}

enum TextSize {
    ExtraSmall,
    Small,
    Normal,
    Large,
    ExtraLarge
}

function stringToTextSize(value: string, defaultValue: TextSize): TextSize {
    switch (value) {
        case "extraSmall":
            return TextSize.ExtraLarge;
        case "small":
            return TextSize.Small;
        case "normal":
            return TextSize.Normal;
        case "large":
            return TextSize.Large;
        case "extraLarge":
            return TextSize.ExtraLarge;
        default:
            return defaultValue;
    }
}

enum TextWeight {
    Lighter,
    Normal,
    Bolder
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

enum TextColor {
    Darker,
    Normal,
    Brighter
}

function stringToTextColor(value: string, defaultValue: TextColor): TextColor {
    switch (value) {
        case "darker":
            return TextColor.Darker;
        case "normal":
            return TextColor.Normal;
        case "brighter":
            return TextColor.Brighter;
        default:
            return defaultValue;
    }
}

enum HorizontalAlignment {
    Left,
    Center,
    Right
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

enum Size {
    Auto,
    Small,
    Medium,
    Large,
    Stretch
}

function stringToSize(value: string, defaultValue: Size): Size {
    switch (value) {
        case "auto":
            return Size.Auto;
        case "small":
            return Size.Small;
        case "medium":
            return Size.Medium;
        case "large":
            return Size.Large;
        case "stretch":
            return Size.Stretch;
        default:
            return defaultValue;
    }
}

enum PictureStyle {
    Normal,
    Person
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

enum ButtonState {
    Normal,
    Selected,
    Inactive
}

enum Spacing {
    None,
    ExtraNarrow,
    Narrow,
    Normal,
    Wide
}

function stringToSpacing(value: string, defaultValue: Spacing): Spacing {
    switch (value) {
        case "none":
            return Spacing.None;
        case "extraNarrow":
            return Spacing.ExtraNarrow;
        case "narrow":
            return Spacing.Narrow;
        case "normal":
            return Spacing.Normal;
        case "wide":
            return Spacing.Wide;
        default:
            return defaultValue;
    }
}

function getPhysicalSpacing(size: Spacing): number {
    switch (size) {
        case Spacing.ExtraNarrow:
            return 5;
        case Spacing.Narrow:
            return 10;
        case Spacing.Normal:
            return 20;
        case Spacing.Wide:
            return 30;
        default:
            return 0;
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
    private _container: Container;
    private _topSpacing: Spacing = Spacing.Normal;
    private _size: Size = Size.Auto;
    private _horizontalAlignment: HorizontalAlignment = HorizontalAlignment.Left;

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

    constructor(container: Container) {
        this._container = container;
    }

    get container(): Container {
        return this._container;
    }

    get topSpacing(): Spacing {
        return this._topSpacing;
    }

    set topSpacing(value: Spacing) {
        this._topSpacing = value;
    }

    get size(): Size {
        return this._size;
    }

    set size(value: Size) {
        this._size = value;
    }

    get horizontalAlignment(): HorizontalAlignment {
        return this._horizontalAlignment;
    }

    set horizontalAlignment(value: HorizontalAlignment) {
        this._horizontalAlignment = value;
    }

    abstract render(): HTMLElement;

    adjustLayout(element: HTMLElement) {
        if (this.size == Size.Stretch) {
            element.style.width = "100%";
        }
        else if (this.size != Size.Auto) {
            element.style.width = this.getPhysicalSize().toString() + "px";
        }

        switch (this.horizontalAlignment) {
            case HorizontalAlignment.Center:
                element.style.textAlign = "center";
                break;
            case HorizontalAlignment.Right:
                element.style.textAlign = "right";
                break;
        }
    }

    internalRender(): HTMLElement {
        let renderedElement =  this.render();

        this.adjustLayout(renderedElement);

        return renderedElement;
    }

    static getPhysicalSize(size: Size) {
        switch (size) {
            case Size.Small:
                return 100;
            case Size.Large:
                return 300;
            default:
                return 200;
        }
    }

    getPhysicalSize(): number {
        return CardElement.getPhysicalSize(this.size);
    }

    parse(json: any) {
        this._topSpacing = stringToSpacing(json["topSpacing"], Spacing.Normal);
        this._size = stringToSize(json["size"], this.size);
        this._horizontalAlignment = stringToHorizontalAlignment(json["horizontalAlignment"], this.horizontalAlignment);
    }
}

class TextBlock extends CardElement {
    textSize: TextSize = TextSize.Normal;
    textWeight: TextWeight = TextWeight.Normal;
    textColor: TextColor = TextColor.Normal;
    text: string;

    static create(
        container: Container,
        text: string,
        textSize: TextSize,
        textWeight: TextWeight,
        textColor: TextColor): TextBlock {
        let result: TextBlock = null;

        if (!isNullOrEmpty(text)) {
            result = new TextBlock(container);
            result.text = text;
            result.textSize = textSize;
            result.textWeight = textWeight;
            result.textColor = textColor;
        }

        return result;
    }

    static render(
        value: string,
        textSize: TextSize,
        textWeight: TextWeight,
        textColor: TextColor,
        textContrast: TextContrast): HTMLElement {
        if (!isNullOrEmpty(value)) {
            let element = document.createElement("div");
            let cssStyle = "text ";

            switch (textSize) {
                case TextSize.ExtraSmall:
                    cssStyle += "extraSmall ";
                    break; 
                case TextSize.Small:
                    cssStyle += "small ";
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

            switch (textColor) {
                case TextColor.Darker:
                    cssStyle += "darker ";
                    break;
                case TextColor.Brighter:
                    cssStyle += "lighter ";
                    break;
                default:
                    cssStyle += "defaultColor ";
                    break;
            }

            switch (textWeight) {
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

            cssStyle += textContrast == TextContrast.DarkOnLight ? "darkOnLight" : "lightOnDark";
            
            element.className = cssStyle;            
            element.innerHTML = processMarkdown(value);

            return element;
        }
        else {
            return null;
        }
    }

    parse(json: any) {
        super.parse(json);

        this.text = json["text"];
        this.textSize = stringToTextSize(json["textSize"], TextSize.Normal);
        this.textColor = stringToTextColor(json["textColor"], TextColor.Normal);
    }

    render(): HTMLElement {
        return TextBlock.render(
            this.text,
            this.textSize,
            this.textWeight,
            this.textColor,
            this.container.textContrast);
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
            element.style.borderWidth = "0px";
            element.style.borderSpacing = "0px";
            element.style.borderStyle = "none";
            element.style.borderCollapse = "collapse";

            let html: string = '';

            for (var i = 0; i < this._items.length; i++) {
                html += '<tr>';

                html += '    <td style="border-width: 0px; padding: 0px; border-style: none; min-width: 100px; vertical-align: top">';
                html += TextBlock.render(this._items[i].name, TextSize.Normal, TextWeight.Bolder, TextColor.Normal, this.container.textContrast).outerHTML;
                html += '    </td>';
                html += '    <td style="border-width: 0px; padding: 0px; border-style: none; vertical-align: top; padding 0px 0px 0px 10px">';
                html += TextBlock.render(this._items[i].value, TextSize.Normal, TextWeight.Lighter, TextColor.Normal, this.container.textContrast).outerHTML;
                html += '    </td>';
                html += '</tr>';
            }

            element.innerHTML = html;
        }

        return element;
    }
}

class Picture extends CardElement {
    private _style: PictureStyle = PictureStyle.Normal;
    private _url: string;

    static getPhysicalSize(size: Size): number {
        switch (size) {
            case Size.Small:
                return 40;
            case Size.Medium:
                return 80;
            default:
                return 160;
        }
    }

    getPhysicalSize(): number {
        return Picture.getPhysicalSize(this.size);
    }

    get style(): PictureStyle {
        return this._style;
    }

    set style(value: PictureStyle) {
        this._style = value;
    }

    get url(): string {
        return this._url;
    }

    set url(value: string) {
        this._url = value;
    }

    parse(json: any) {
        super.parse(json);
        
        this._url = json["url"];
        this._style = stringToPictureStyle(json["style"], PictureStyle.Normal);
    }

    render(
        marginLeft: number = 0,
        marginTop: number = 0,
        marginRight: number = 0,
        marginBottom: number = 0): HTMLElement {
        let image: HTMLImageElement = null;

        if (!isNullOrEmpty(this._url)) {
            image = document.createElement("img");

            if (this.size == Size.Auto) {
                image.style.maxWidth = "100%";
            }
            else {
                let physicalSize = Picture.getPhysicalSize(this.size);

                image.style.maxWidth = physicalSize.toString() + "px"; 
                image.style.maxHeight = physicalSize.toString() + "px";

                if (this._style == PictureStyle.Person) {
                    image.className = "inCircle";
                    image.style.borderRadius = (physicalSize / 2).toString() + "px";
                    image.style.backgroundPosition = "50% 50%";
                    image.style.backgroundRepeat = "no-repeat";
                }
            }

            image.style.marginLeft = marginLeft.toString() + "px";
            image.style.marginTop = marginTop.toString() + "px";
            image.style.marginRight = marginRight.toString() + "px";
            image.style.marginBottom = marginBottom.toString() + "px";

            image.src = this._url;
        }

        return image;
    }
}

class PictureGallery extends CardElement {
    private _items: Array<Picture> = [];
    private _pictureSize: Size = Size.Medium;

    get items(): Array<Picture> {
        return this._items;
    }

    parse(json: any) {
        super.parse(json);
        
        this._pictureSize = stringToSize(json["imageSize"], Size.Medium);

        if (json["items"] != null) {
            let pictureArray = json["items"] as Array<any>;

            for (let i = 0; i < pictureArray.length; i++) {
                let picture = new Picture(this.container);

                picture.size = this._pictureSize;
                picture.url = pictureArray[i];

                this._items.push(picture);
            }
        }
    }

    render(): HTMLElement {
        let element: HTMLElement = null;

        if (this._items.length > 0) {
            element = document.createElement("div");

            for (var i = 0; i < this._items.length; i++) {
                appendChild(element, this._items[i].render(0, 0, 10, 0));
            }
        }

        return element;
    }
}

abstract class Action {
    private _owner: CardElement;
    private _name: string;

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
        this._name = json["name"];
    }

    renderUi(container: Container, requiresTopSpacer: boolean = false): HTMLElement {
        return null;
    }

    get name() {
        return this._name;
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
    targets: Array<TargetUri> = [];

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
                    let target = new TargetUri();

                    target.parse(targetArray[i]);

                    this.targets.push(target);
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
        element.className = "textInput";
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
        selectElement.className = "multichoiceInput";

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

        if (needsTopSpacer) {
            actionCardElement.style.marginTop = "16px";
        }

        actionCardElement.style.paddingTop = container.padding == 0 ? "16px" : getPhysicalSpacing(container.padding).toString() + "px";
        actionCardElement.style.paddingBottom = actionCardElement.style.paddingTop;

        if (this._card != null) {
            appendChild(actionCardElement, this._card.render());
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
            let actionButton = new ActionButton(
                this._actions[i],
                this._actions.length == 1 ? ActionButtonStyle.PushProminent : ActionButtonStyle.PushSubdued);
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
    PushProminent,
    PushSubdued
}

class ActionButton {
    private _action: Action;
    private _style: ActionButtonStyle;
    private _baseStyleName: string;
    private _onClick: EventDispatcher<ActionButton> = new EventDispatcher<ActionButton>();
    private _element: HTMLElement = null;
    private _state: ButtonState = ButtonState.Normal;
    private _text: string;

    private click() {
        this._onClick.dispatch(this, null);
    }

    constructor(action: Action, style: ActionButtonStyle) {
        this._action = action;
        this._style = style;
        this._baseStyleName = this._style == ActionButtonStyle.Link ? "link" : "push";
        this._element = document.createElement("div");
        this._element.onclick = (e) => { this.click(); };

        if (style != ActionButtonStyle.Link) {
            this._element.onmouseenter = (e) => { this.state = ButtonState.Selected; };
            this._element.onmouseleave = (e) => { this.state = ButtonState.Normal; };
        }

        this.state = ButtonState.Normal;
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

    get state(): ButtonState {
        return this._state;
    }

    get element(): HTMLElement {
        return this._element;
    }

    set state(value: ButtonState) {
        this._state = value;

        let styleName = this._baseStyleName;

        if (this._style == ActionButtonStyle.PushProminent) {
            styleName += " prominent";
        }
        else if (this._style == ActionButtonStyle.PushSubdued) {
            styleName += " subdued";
        }

        switch (this._state) {
            case ButtonState.Selected:
                this._element.className = "button " + styleName + " selected";
                break;
            case ButtonState.Inactive:
                this._element.className = "button " + styleName + " inactive";
                break;
            default:
                this._element.className = "button " + styleName + " normal";
                break;
        }

        this._element.style.flex = "0 1 auto";
        this._element.style.textOverflow = "ellipsis";
        this._element.style.whiteSpace = "nowrap";
        this._element.style.overflow = "hidden";
    }
}

class ActionGroup extends CardElement {
    private _actionButtons: Array<ActionButton> = [];
    private _actionCardContainer: HTMLDivElement;
    private _actions: Array<Action> = [];

    private hideActionCardPane() {
        this._actionCardContainer.innerHTML = '';

        this.container.showBottomSpacer(this);
    }

    private showActionCardPane(action: Action) {
        this.container.hideBottomSpacer(this);

        this._actionCardContainer.innerHTML = '';

        appendChild(
            this._actionCardContainer,
            action.renderUi(this.container, this._actions.length > 1));
    }

    private actionClicked(actionButton: ActionButton) {
        if (!actionButton.action.hasUi) {
            for (var i = 0; i < this._actionButtons.length; i++) {
                this._actionButtons[i].state = ButtonState.Normal;
            }

            this.hideActionCardPane();

            alert("Executing action " + actionButton.text)
        }
        else {
            if (actionButton.state == ButtonState.Selected) {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    this._actionButtons[i].state = ButtonState.Normal;
                }

                this.hideActionCardPane();
            }
            else {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    if (this._actionButtons[i] !== actionButton) {
                        this._actionButtons[i].state = ButtonState.Inactive;
                    }
                }

                actionButton.state = ButtonState.Selected;

                this.showActionCardPane(actionButton.action);
            }
        }
    }

    get actions(): Array<Action> {
        return this._actions;
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

        let actionContainer = document.createElement("div");
        actionContainer.style.display = "flex";

        appendChild(element, actionContainer);

        let containerPadding = this.container.getActionCardLeftRightPadding();

        this._actionCardContainer = document.createElement("div");
        this._actionCardContainer.style.backgroundColor = "#F8F8F8";
        this._actionCardContainer.style.marginLeft = "-" + containerPadding.toString() + "px";
        this._actionCardContainer.style.marginRight = "-" + containerPadding.toString() + "px";
        this._actionCardContainer.style.paddingLeft = containerPadding.toString() + "px";
        this._actionCardContainer.style.paddingRight = containerPadding.toString() + "px";

        appendChild(element, this._actionCardContainer);

        if (this._actions.length == 1 && this._actions[0] instanceof ActionCard) {
            this.showActionCardPane(this._actions[0]);
        }
        else {
            for (let i = 0; i < this._actions.length; i++) {
                let actionButton = new ActionButton(this._actions[i], ActionButtonStyle.Link);
                actionButton.text = this._actions[i].name;

                if (i < this._actions.length - 1) {
                    actionButton.element.style.marginRight = "20px";
                }

                actionButton.onClick.subscribe(
                    (ab, args) => {
                        this.actionClicked(ab);
                    });
                
                this._actionButtons.push(actionButton);

                appendChild(actionContainer, actionButton.element);
            }
        }

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
        element.style.borderTop = "1px solid #EEEEEE";

        return element;
    }
}

class Container extends CardElement {
    private _forbiddenItemTypes: Array<string>;
    private _items: Array<CardElement> = [];
    private _element: HTMLDivElement;
    private _backgroundImageUrl: string;
    private _backgroundColor: string;
    private _padding: Spacing = Spacing.None;
    private _textContrast: TextContrast = undefined;

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

    constructor(container: Container, forbiddenItemTypes: Array<string> = null) {
        super(container);

        this._forbiddenItemTypes = forbiddenItemTypes;
    }

    get padding(): Spacing {
        return this._padding;
    }

    set padding(value: Spacing) {
        this._padding = value;
    }

    get elementCount(): number {
        return this._items.length;
    }

    get backgroundImageUrl(): string {
        return this._backgroundImageUrl;
    }

    set backgroundImageUrl(value: string) {
        this._backgroundImageUrl = value;
    }

    get backgroundColor(): string {
        return this._backgroundColor;
    }

    set backgroundColor(value: string) {
        this._backgroundColor = value;
    }

    set textContrast(value: TextContrast) {
        this._textContrast = value;
    }

    get textContrast(): TextContrast {
        if (this._textContrast != undefined) {
            return this._textContrast;
        }

        if (this.container != null) {
            return this.container.textContrast;
        }

        return TextContrast.DarkOnLight;
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
            this._element.style.paddingBottom = getPhysicalSpacing(this.padding) + "px"; 

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

        this._padding = stringToSpacing(json["padding"], Spacing.None);        
        this._backgroundImageUrl = json["backgroundImage"];
        this._backgroundColor = json["backgroundColor"];
        this._textContrast = stringToTextContrast(json["textContrast"]);

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

            if (!isNullOrEmpty(this.backgroundColor)) {
                this._element.style.backgroundColor = this.backgroundColor;
            }

            this._element.style.padding = getPhysicalSpacing(this.padding) + "px"; 

            let html: string = '';
            let previousElement: CardElement = null;

            for (var i = 0; i < this.elementCount; i++) {
                let spacing = getPhysicalSpacing(this.getElement(i).topSpacing);

                let renderedElement = this.getElement(i).internalRender();

                if (renderedElement != null) {
                    if (previousElement != null && spacing > 0) {
                        renderedElement.style.marginTop = spacing.toString() + "px";
                    }

                    appendChild(this._element, renderedElement);
                }

                previousElement = this.getElement(i);
            }

            if (!isNullOrEmpty(this._backgroundImageUrl)) {
                this._element.style.backgroundImage = 'url("' + this._backgroundImageUrl + '")';
                this._element.style.backgroundRepeat = "no-repeat";
                this._element.style.backgroundSize = "cover";
            }
        }

        return this._element;
    }

    getActionCardLeftRightPadding(): number {
        let currentSection: Container = this;
        let result: number = 0;

        while (currentSection != null && result == 0) {
            result = getPhysicalSpacing(currentSection.padding);

            currentSection = currentSection.container;
        };

        return result;
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

        this.size = stringToSize(json["size"], undefined);

        if (this.size == undefined) {
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
                    element.style.flex = "0 1 auto";
                    break;
                case Size.Stretch:
                    element.style.flex = "1 1 auto";
                    break;
                default:
                    element.style.flex = "0 0 " + CardElement.getPhysicalSize(this.size) + "px";
                    break;
            }
        }

        element.style.overflow = "hidden";
    }
}

class ColumnGroup extends CardElement {
    private _items: Array<Column> = [];
    private _columnSpacing: Spacing = Spacing.Narrow;

    get spacing(): number {
        return this._columnSpacing;
    }

    set spacing(value: number) {
        this._columnSpacing = value;
    }

    parse(json: any) {
        super.parse(json);

        this._columnSpacing = stringToSpacing(json["columnSpacing"], Spacing.Narrow);
        
        if (json["items"] != null) {
            let itemArray = json["items"] as Array<any>;

            for (let i = 0; i < itemArray.length; i++) {
                let groupItem = new Column(this.container, ["ColumnGroup", "ActionGroup"]);

                groupItem.parse(itemArray[i]);

                this._items.push(groupItem);
            }
        }
    }

    render(): HTMLElement {
        if (this._items.length > 0) {
            let element = document.createElement("div");
            element.style.display = "flex";

            let perColumnTotalSpacing = ((this._items.length - 1) * getPhysicalSpacing(this.spacing)) / this._items.length;

            for (let i = 0; i < this._items.length; i++) {
                let renderedColumn = this._items[i].internalRender();

                if (this._items.length > 1) {
                    if (i == 0) {
                        renderedColumn.style.paddingRight = perColumnTotalSpacing.toString() + "px";
                    }
                    else if (i == this._items.length - 1) {
                        renderedColumn.style.paddingLeft = perColumnTotalSpacing.toString() + "px";
                    }
                    else {
                        renderedColumn.style.paddingRight = (perColumnTotalSpacing / 2).toString() + "px";
                        renderedColumn.style.paddingLeft = (perColumnTotalSpacing / 2).toString() + "px";
                    }
                }

                appendChild(element, renderedColumn);
            }

            return element;
        }
        else {
            return null;
        }
    }
}

class AdaptiveCard {
    private _rootSection = new Container(null);
    private _width: number;
    private _height: number;

    parse(json: any) {
        this._rootSection.padding = stringToSpacing(json["padding"], Spacing.None);
        this._rootSection.backgroundImageUrl = json["backgroundImage"];
        this._rootSection.backgroundColor = json["backgroundColor"];
        this._rootSection.textContrast = stringToTextContrast(json["textContrast"]);
        this._width = <number>json["width"];
        this._height = <number>json["height"];

        if (json["sections"] != undefined) {
            let sectionArray = json["sections"] as Array<any>;

            for (var i = 0; i < sectionArray.length; i++) {
                let section = new Container(this._rootSection, [ "Section" ]);

                section.parse(sectionArray[i]);

                this._rootSection.addElement(section);
            }
        }
    }

    render(): HTMLElement {
        let element = this._rootSection.internalRender();

        if (this._width != undefined) {
            element.style.width = this._width.toString() + "px";
        }

        if (this._height != undefined) {
            element.style.height = this._height.toString() + "px";
        }

        return element;
   }
}