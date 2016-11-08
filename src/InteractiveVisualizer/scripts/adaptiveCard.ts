/*
Strongly typed events from https://keestalkstech.com/2016/03/strongly-typed-event-handlers-in-typescript-part-1/
*/
 
enum TextStyle {
    Default,
    CardSummary,
    CardTitle,
    CardText,
    SectionTitle,
    SectionText,
    ActivityTitle,
    ActivitySubtitle,
    ActivityText,
    FactName,
    FactValue
}

function stringToTextStyle(value: string, defaultValue: TextStyle): TextStyle {
    switch (value) {
        case "defaultTextStyle":
            return TextStyle.Default;
        case "cardSummary":
            return TextStyle.CardSummary;
        case "cardTitle":
            return TextStyle.CardTitle;
        case "cardText":
            return TextStyle.CardText; 
        case "sectionTitle":
            return TextStyle.SectionTitle;
        case "sectionText":
            return TextStyle.SectionText;
        case "activityTitle":
            return TextStyle.ActivityTitle;
        case "activitySubtitle":
            return TextStyle.ActivitySubtitle;
        case "activityText":
            return TextStyle.ActivityText;
        case "factName":
            return TextStyle.FactName;
        case "factValue":
            return TextStyle.FactValue;
        default:
            return defaultValue;
    }
}

function textStyleToCssClassName(style: TextStyle): string {
    switch (style) {
        case TextStyle.CardSummary:
            return "cardSummary";
        case TextStyle.CardTitle:
            return "cardTitle";
        case TextStyle.CardText:
            return "cardText";
        case TextStyle.SectionTitle:
            return "sectionTitle";
        case TextStyle.SectionText:
            return "sectionText";
        case TextStyle.ActivityTitle:
            return "activityTitle";
        case TextStyle.ActivitySubtitle:
            return "activitySubtitle";
        case TextStyle.ActivityText:
            return "activityText";
        case TextStyle.FactName:
            return "factName";
        case TextStyle.FactValue:
            return "factValue";
        default:
            return "defaultTextStyle";
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

enum SectionStyle {
    Normal,
    Card,
    Emphasis
}

function stringToSectionStyle(value: string, defaultValue: SectionStyle): SectionStyle {
    switch (value) {
        case "normal":
            return SectionStyle.Normal;
        case "emphasis":
            return SectionStyle.Emphasis;
        default:
            return defaultValue;
    }
}

enum Spacing {
    None,
    Narrow,
    Normal,
    Wide
}

function stringToSpacing(value: string, defaultValue: Spacing): Spacing {
    switch (value) {
        case "none":
            return Spacing.None;
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
            case "FlexBox":
                return new FlexBox(container);
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

    abstract render(): HTMLElement;

    adjustPhysicalSize(element: HTMLElement) {
        if (this.size == Size.Stretch) {
            element.style.width = "100%";
        }
        else if (this.size != Size.Auto) {
            element.style.width = this.getPhysicalSize().toString() + "px";
        }
    }

    internalRender(): HTMLElement {
        let renderedElement =  this.render();

        this.adjustPhysicalSize(renderedElement);

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
    }

    getSpacingAfterThis(): number {
        return 20;
    }
}

class TextBlock extends CardElement {
    style: TextStyle = TextStyle.Default;
    text: string;

    static create(container: Container, text: string, style: TextStyle): TextBlock {
        let result: TextBlock = null;

        if (!isNullOrEmpty(text)) {
            result = new TextBlock(container);
            result.style = style;
            result.text = text;
        }

        return result;
    }

    static render(value: string, style: TextStyle): HTMLElement {
        if (!isNullOrEmpty(value)) {
            var element = document.createElement("div");
            element.className = textStyleToCssClassName(style);
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
        this.style = stringToTextStyle(json["style"], TextStyle.Default);
    }

    render(): HTMLElement {
        return TextBlock.render(this.text, this.style);
    }

    getSpacingAfterThis(): number {
        if (this.style == TextStyle.SectionTitle) {
            return 10;
        }
        else {
            return super.getSpacingAfterThis();
        }
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
            element.className = "factsTable";

            let html: string = '';

            for (var i = 0; i < this._items.length; i++) {
                html += '<tr>';
                html += '    <td class="factNameCell">';
                html += TextBlock.render(this._items[i].name, TextStyle.FactName).outerHTML;
                html += '    </td>';
                html += '    <td class="factValueCell">';
                html += TextBlock.render(this._items[i].value, TextStyle.FactValue).outerHTML;
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

        if (json["type"] == "ViewAction") {
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
    private _card: ActionCardContainer; 

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
            this._card = new ActionCardContainer(this.owner.container, [ "ActionGroup" ]);
            this._card.parse(json["card"]);
        }

        if (json["inputs"] != undefined) {
            let inputArray = json["inputs"] as Array<any>;

            for (let i = 0; i < inputArray.length; i++) {
                let input = Input.createInput(this.owner.container, inputArray[i]["type"]);

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
                    if (actionJson["type"] === this._allowedActionTypes[j]) {
                        typeIsAllowed = true;
                        break;
                    }
                }

                if (typeIsAllowed) {
                    let action = Action.create(this.owner, actionJson["type"]);

                    action.parse(actionJson);

                    this._actions.push(action);
                }
            }
        }
    }

    private actionClicked(actionButton: ActionButton) {
        alert('Now executing "' + actionButton.text + '"');
    }

    renderUi(container: Section, needsTopSpacer: boolean = false): HTMLElement {
        let actionCardElement = document.createElement("div");

        if (needsTopSpacer) {
            actionCardElement.style.marginTop = "16px";
        }

        let topBottomPadding = container.getActionCardTopBottomPadding();

        actionCardElement.style.paddingTop = topBottomPadding.toString() + "px";
        actionCardElement.style.paddingBottom = topBottomPadding.toString() + "px";

        if (this._card != null) {
            appendChild(actionCardElement, this._card.render());
        }
        else {
            for (let i = 0; i < this._inputs.length; i++) {
                let inputElement = this._inputs[i].internalRender();

                if (i > 0) {
                    let spacer = document.createElement("div");
                    spacer.style.height = "10px";

                    appendChild(actionCardElement, spacer);
                }

                appendChild(actionCardElement, inputElement);
            }
        }

        let buttonsContainer = document.createElement("div");
        buttonsContainer.className = "pushButtonsContainer";
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
            
            appendChild(buttonsContainer, actionButton.element);

            if (i < this._actions.length - 1) {
                let spacer = document.createElement("div");
                spacer.style.width = "16px";

                appendChild(buttonsContainer, spacer);
            }
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
            styleName += "Prominent";
        }
        else if (this._style == ActionButtonStyle.PushSubdued) {
            styleName += "Subdued";
        }

        switch (this._state) {
            case ButtonState.Selected:
                this._element.className = "button " + styleName + "Selected actionItem";
                break;
            case ButtonState.Inactive:
                this._element.className = "button " + styleName + "Inactive actionItem";
                break;
            default:
                this._element.className = "button " + styleName + "Normal actionItem";
                break;
        }
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
                let action = Action.create(this, actionArray[i]["type"]);

                action.parse(actionArray[i]);

                this._actions.push(action);
            }
        }
    }

    render(): HTMLElement {
        let element = document.createElement("div");

        let actionContainer = document.createElement("div");
        actionContainer.className = "linkButtonsContainer";

        appendChild(element, actionContainer);

        let containerPadding = this.container.getActionCardLeftRightPadding();

        this._actionCardContainer = document.createElement("div");
        this._actionCardContainer.style.backgroundColor = this.container.getActionCardBackgroundColor();
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

        element.className = "horizontalSeparator";

        return element;
    }
}

abstract class Container extends CardElement {
    private _forbiddenItemTypes: Array<string>;
    private _items: Array<CardElement> = [];
    private _bottomSpacer: HTMLElement;
    private _padding: number = 0;
    private _backgroundImageUrl;
    private _useMargins = false;

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

    get padding(): number {
        return this._padding;
    }

    set padding(value: number) {
        this._padding = value;
    }

    get elementCount(): number {
        return this._items.length;
    }

    get useMargins(): boolean {
        return this._useMargins;
    }

    set useMargins(value: boolean) {
        this._useMargins = value;
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
            this._bottomSpacer.style.height = this.padding.toString() + "px";

            if (this.container != null) {
                this.container.showBottomSpacer(this);
            }
        }
    }

    hideBottomSpacer(requestingElement: CardElement) {
        if (this.isLastElement(requestingElement)) {
            this._bottomSpacer.style.height = "0px";

            if (this.container != null) {
                this.container.hideBottomSpacer(this);
            }
        }
    }

    parse(json: any) {
        super.parse(json);
        
        this._backgroundImageUrl = json["backgroundImage"];

        if (json["items"] != null) {
            let items = json["items"] as Array<any>;

            for (let i = 0; i < items.length; i++) {
                let elementType = items[i]["type"];

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
        this._bottomSpacer = document.createElement("div");
        this._bottomSpacer.style.height = this.padding.toString() + "px";

        let element: HTMLElement = null;

        if (this.elementCount > 0) {
            element = document.createElement("div");
            element.style.paddingLeft = this._padding.toString() + "px";
            element.style.paddingTop = this._padding.toString() + "px";
            element.style.paddingRight = this._padding.toString() + "px";

            let html: string = '';
            let previousElement: CardElement = null;
            let spaceUsingMargins: boolean = this.getRootContainer().useMargins; 

            for (var i = 0; i < this.elementCount; i++) {
                let spacing: Number = 0;

                if (!spaceUsingMargins) {
                    spacing = previousElement != null ? previousElement.getSpacingAfterThis() : 0;
                }
                else {
                    spacing = getPhysicalSpacing(this.getElement(i).topSpacing);
                }

                let renderedElement = this.getElement(i).internalRender();

                if (renderedElement != null) {
                    if (previousElement != null && spacing > 0) {
                        let spacer = document.createElement("div");
                        spacer.style.height = spacing.toString() + "px";

                        appendChild(element, spacer);
                    }

                    appendChild(element, renderedElement);
                }

                previousElement = this.getElement(i);
            }

            if (!isNullOrEmpty(this._backgroundImageUrl)) {
                element.style.backgroundImage = "url(" + this._backgroundImageUrl + ")";
                element.style.backgroundRepeat = "no-repeat";
                element.style.backgroundSize = "cover";
            }

            appendChild(element, this._bottomSpacer);
        }

        return element;
    }

    getActionCardLeftRightPadding(): number {
        let currentSection: Container = this;
        let result: number = 0;

        while (currentSection != null && result == 0) {
            result = currentSection.padding;

            currentSection = currentSection.container;
        };

        return result;
    }

    getActionCardTopBottomPadding(): number {
        return 16;
    }

    getActionCardBackgroundColor(): string {
        return "transparent";
    }

    getRootContainer(): Container {
        let currentContainer: Container = this;

        while (currentContainer.container != null) {
            currentContainer = currentContainer.container;
        }

        return currentContainer;
    }
}

class Section extends Container {
    private _style: SectionStyle;
    private _themeColor: string;

    get style(): SectionStyle {
        return this._style;
    }

    set style(value: SectionStyle) {
        this._style = value;

        switch (this._style) {
            case SectionStyle.Emphasis:
                this.padding = 10;
                break;
            case SectionStyle.Card:
                this.padding = 20;
                break;
            default:
                this.padding = 0;
                break;
        }
    }

    get themeColor(): string {
        return this._themeColor;
    }

    set themeColor(value: string) {
        this._themeColor = value;
    }

    getActionCardTopBottomPadding(): number {
        switch (this.style) {
            case SectionStyle.Emphasis:
                return this.padding;
            default:
                return 16;
        }
    }

    getActionCardBackgroundColor(): string {
        switch (this.style) {
            case SectionStyle.Emphasis:
                return "#EAEAEA";
            default:
                return "#F8F8F8";
        }
    }

    parse(json: any) {
        super.parse(json);

        this.style = stringToSectionStyle(json["style"], SectionStyle.Normal); 
    }

    render(): HTMLElement {
        let element = super.render();

        if (element != null) {
            switch (this.style) {
                case SectionStyle.Emphasis:
                    element.className = "emphasizedSection";
                    break;
                case SectionStyle.Card:
                    if (isNullOrEmpty(this._themeColor)) {
                        element.className = "cardRootSimple";
                    }
                    else {
                        element.className = "cardRootWithTheme";
                        element.style.borderLeftColor = "#" + this._themeColor;
                    }
                    break;
            }
        }

        return element;
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

    adjustPhysicalSize(element: HTMLElement) {
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
    }
}

class FlexBox extends CardElement {
    private _items: Array<Column> = [];
    private _spacing: Spacing = Spacing.Narrow;

    get spacing(): number {
        return this._spacing;
    }

    set spacing(value: number) {
        this._spacing = value;
    }

    parse(json: any) {
        super.parse(json);

        this._spacing = stringToSpacing(json["spacing"], Spacing.Narrow);
        
        if (json["items"] != null) {
            let itemArray = json["items"] as Array<any>;

            for (let i = 0; i < itemArray.length; i++) {
                let groupItem = new Column(this.container, ["FlexBox", "ActionGroup"]);

                groupItem.parse(itemArray[i]);

                this._items.push(groupItem);
            }
        }
    }

    render(): HTMLElement {
        let element = document.createElement("div");
        element.className = "groupContainer";

        for (let i = 0; i < this._items.length; i++) {
            let renderedGroup = this._items[i].internalRender();

            if (i < this._items.length - 1) {
                renderedGroup.style.marginRight = getPhysicalSpacing(this.spacing).toString() + "px";
            }

            appendChild(element, renderedGroup);
        }

        return element;
    }
}

class ActionCardContainer extends Container {
}

class AdaptiveCard {
    private _rootSection = new Section(null);

    parse(json: any) {
        this._rootSection.useMargins = true;
        this._rootSection.style = SectionStyle.Card;

        if (json["sections"] != undefined) {
            let sectionArray = json["sections"] as Array<any>;

            for (var i = 0; i < sectionArray.length; i++) {
                let section = new Section(this._rootSection, [ "Section" ]);

                section.parse(sectionArray[i]);

                this._rootSection.addElement(section);
            }
        }
    }

    render(): HTMLElement {
        return this._rootSection.internalRender();
    }
}