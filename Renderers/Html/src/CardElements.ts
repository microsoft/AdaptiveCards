import * as Enums from "./Enumerations";
import * as Eventing from "./Eventing";
import * as Utils from "./Utils";
import * as TextFormatters from "./TextFormatters";

export abstract class CardElement {
    private _container: Container;

    speak: string;
    horizontalAlignment: Enums.HorizontalAlignment = Enums.HorizontalAlignment.Left;

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
            element.className += " stretch";
        }

        switch (this.horizontalAlignment) {
            case Enums.HorizontalAlignment.Center:
                element.style.textAlign = "center";
                break;
            case Enums.HorizontalAlignment.Right:
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
}

export class TextBlock extends CardElement {
    static TypeName: string = "TextBlock";
    
    textSize: Enums.TextSize = Enums.TextSize.Normal;
    textWeight: Enums.TextWeight = Enums.TextWeight.Normal;
    textColor: Enums.TextColor = Enums.TextColor.Default;
    text: string;
    isSubtle: boolean = false;
    wrap: boolean = true;
    startParagraph: boolean = true;

    render(): HTMLElement {
        if (!Utils.isNullOrEmpty(this.text)) {
            let element = document.createElement("div");

            let cssStyle = "text ";

            if (this.startParagraph) {
                cssStyle += "startParagraph ";
            }
            
            switch (this.textSize) {
                case Enums.TextSize.Small:
                    cssStyle += "small ";
                    break;
                case Enums.TextSize.Medium:
                    cssStyle += "medium ";
                    break;
                case Enums.TextSize.Large:
                    cssStyle += "large ";
                    break;
                case Enums.TextSize.ExtraLarge:
                    cssStyle += "extraLarge ";
                    break;
                default:
                    cssStyle += "defaultSize ";
                    break;
            }

            let actualTextColor = this.textColor == Enums.TextColor.Default ? this.container.textColor : this.textColor;

            switch (actualTextColor) {
                case Enums.TextColor.Dark:
                    cssStyle += "darkColor ";
                    break;
                case Enums.TextColor.Light:
                    cssStyle += "lightColor ";
                    break;
                case Enums.TextColor.Accent:
                    cssStyle += "accentColor ";
                    break;
                case Enums.TextColor.Good:
                    cssStyle += "goodColor ";
                    break;
                case Enums.TextColor.Warning:
                    cssStyle += "warningColor ";
                    break;
                case Enums.TextColor.Attention:
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
                case Enums.TextWeight.Lighter:
                    cssStyle += "lighter ";
                    break;
                case Enums.TextWeight.Bolder:
                    cssStyle += "bolder ";
                    break;
                default:
                    cssStyle += "defaultWeight ";
                    break;
            }

            var formattedText = TextFormatters.formatText(this.text);

            element.innerHTML = Utils.processMarkdown(formattedText);
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

    renderSpeech(): string {
        if (this.speak != null) {
            return this.speak + '\n';
        }

        return '<s>' + this.name + ' ' + this.value + '</s>\n';
    }
}

export class FactSet extends CardElement {
    static TypeName: string = "FactSet";

    private _facts: Array<Fact> = [];

    get facts(): Array<Fact> {
        return this._facts;
    }

    render(): HTMLElement {
        let element: HTMLElement = null;

        if (this._facts.length > 0) {
            element = document.createElement("table");
            element.className = "factGroup";

            let html: string = '';

            for (var i = 0; i < this._facts.length; i++) {
                html += '<tr>';
                html += '    <td class="factName">';

                let textBlock = new TextBlock(this.container);
                textBlock.text = this._facts[i].name;
                textBlock.textWeight = Enums.TextWeight.Bolder;
                textBlock.startParagraph = false;

                let renderedText = textBlock.internalRender();

                if (renderedText != null) {
                    html += renderedText.outerHTML;
                }

                html += '    </td>';
                html += '    <td class="factValue">';

                textBlock = new TextBlock(this.container);
                textBlock.text = this._facts[i].value;
                textBlock.textWeight = Enums.TextWeight.Lighter;
                textBlock.startParagraph = false;

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
        if (this.speak != null) {
            return this.speak + '\n';
        }

        // render each fact 
        let speak = null;

        if (this._facts.length > 0) {
            speak = '';

            for (var i = 0; i < this._facts.length; i++) {
                let speech = this._facts[i].renderSpeech();

                if (speech) {
                    speak += speech;
                }
            }
        }

        return '<p>' + speak + '\n</p>\n';
    }

    get useDefaultSizing(): boolean {
        return false;
    }
}

export class Image extends CardElement {
    static TypeName: string = "Image";
    
    style: Enums.ImageStyle = Enums.ImageStyle.Normal;
    url: string;
    size: Enums.Size = Enums.Size.Medium;
    selectAction: ActionExternal;

    get useDefaultSizing() {
        return false;
    }

    render(): HTMLElement {
        let imageElement: HTMLImageElement = null;

        if (!Utils.isNullOrEmpty(this.url)) {
            imageElement = document.createElement("img");

            let cssStyle = "image";

            switch (this.size) {
                case Enums.Size.Auto:
                    cssStyle += " autoSize";
                    break;
                case Enums.Size.Stretch:
                    cssStyle += " stretch";
                    break;
                case Enums.Size.Small:
                    cssStyle += " small";
                    break;
                case Enums.Size.Large:
                    cssStyle += " large";
                    break;
                default:
                    cssStyle += " medium";
                    break;
            }

            if (this.style == Enums.ImageStyle.Person) {
                cssStyle += " person";
            }

            imageElement.className = cssStyle;

            imageElement.src = this.url;
        }

        return imageElement;
    }

    renderSpeech(): string {
        if (this.speak != null) {
            return this.speak + '\n';
        }

        return null;
    }
}

export class ImageSet extends CardElement {
    static TypeName: string = "ImageSet";

    private _images: Array<Image> = [];

    imageSize: Enums.Size = Enums.Size.Medium;

    get images(): Array<Image> {
        return this._images;
    }

    render(): HTMLElement {
        let element: HTMLElement = null;

        if (this._images.length > 0) {
            element = document.createElement("div");
            element.className = "imageGallery";

            for (var i = 0; i < this._images.length; i++) {
                let renderedImage = this._images[i].internalRender();
                renderedImage.style.margin = "0px";
                renderedImage.style.marginRight = "10px";

                Utils.appendChild(element, renderedImage);
            }
        }

        return element;
    }

    renderSpeech(): string {
        if (this.speak != null) {
            return this.speak;
        }

        var speak = null;

        if (this._images.length > 0) {
            speak = '';

            for (var i = 0; i < this._images.length; i++) {
                speak += this._images[i].renderSpeech();
            }
        }

        return speak;
    }
}

export abstract class Input extends CardElement {
    id: string;
    title: string;
    defaultValue: string;

    abstract get value(): string;

    renderSpeech(): string {
        if (this.speak != null) {
            return this.speak;
        }

        if (this.title) {
            return '<s>' + this.title + '</s>\n';
        }

        return null;
    }
}

export class InputText extends Input {
    static TypeName: string = "Input.Text";

    private _textareaElement: HTMLTextAreaElement;

    maxLength: number;
    isMultiline: boolean;
    placeholder: string;

    constructor(container: Container) {
        super(container);
    }

    get value(): string {
        return this._textareaElement.textContent;
    }

    render(): HTMLElement {
        this._textareaElement = document.createElement("textarea");
        this._textareaElement.className = "input textInput";

        if (this.isMultiline) {
            this._textareaElement.className += " multiline";
        }

        this._textareaElement.placeholder = this.placeholder;

        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._textareaElement.textContent = this.defaultValue;
        }

        return this._textareaElement;
    }
}

export class InputToggle extends Input {
    static TypeName: string = "Input.Toggle";

    private _checkboxInputElement: HTMLInputElement;

    title: string;
    valueOn: string;
    valueOff: string;

    get value(): string {
        return this._checkboxInputElement.checked ? this.valueOn : this.valueOff;
    }

    render(): HTMLElement {
        let element = document.createElement("div");
        element.className = "input";

        this._checkboxInputElement = document.createElement("input");
        this._checkboxInputElement.className = "toggleInput";
        this._checkboxInputElement.type = "checkbox";

        if (this.defaultValue == this.valueOn) {
            this._checkboxInputElement.checked = true;
        }

        var label = new TextBlock(this.container);
        label.text = this.title;

        var labelElement = label.render();
        labelElement.className += " toggleLabel";

        var compoundInput = document.createElement("div");

        Utils.appendChild(element, this._checkboxInputElement);
        Utils.appendChild(element, labelElement);

        return element;
    }
}

export class Choice {
    display: string;
    value: string;
}

export class InputChoiceSet extends Input {
    static TypeName: string = "Input.ChoiceSet";

    private _selectElement: HTMLSelectElement;
    private _toggleInputs: Array<HTMLInputElement>;

    choices: Array<Choice> = [];
    isCompact: boolean;
    isMultiSelect: boolean;
    placeholder: string;

    constructor(container: Container) {
        super(container);
    }

    get value(): string {
        return "";
    }

    render(): HTMLElement {
        if (!this.isMultiSelect) {
            if (this.isCompact) {
                // Render as a combo box
                this._selectElement = document.createElement("select");
                this._selectElement.className = "input multichoiceInput";

                var option = document.createElement("option");
                option.selected = true;
                option.disabled = true;
                option.hidden = true;
                option.text = this.placeholder;

                Utils.appendChild(this._selectElement, option);

                for (var i = 0; i < this.choices.length; i++) {
                    var option = document.createElement("option");
                    option.value = this.choices[i].value;
                    option.text = this.choices[i].display;

                    Utils.appendChild(this._selectElement, option);
                }

                return this._selectElement;
            }
            else {
                // Render as a series of radio buttons
                var element = document.createElement("div");
                element.className = "input";

                this._toggleInputs = [];

                for (var i = 0; i < this.choices.length; i++) {
                    var radioInput = document.createElement("input");
                    radioInput.className = "toggleInput";
                    radioInput.type = "radio";
                    radioInput.name = this.id;
                    radioInput.value = this.choices[i].value;

                    if (this.defaultValue == this.choices[i].value) {
                        radioInput.checked = true;
                    }

                    this._toggleInputs.push(radioInput);

                    var label = new TextBlock(this.container);
                    label.text = this.choices[i].display;

                    var labelElement = label.render();
                    labelElement.className += " toggleLabel";

                    var compoundInput = document.createElement("div");

                    Utils.appendChild(compoundInput, radioInput);
                    Utils.appendChild(compoundInput, labelElement);

                    Utils.appendChild(element, compoundInput);
                }

                return element;
            }
        }
        else {
            // Render as a list of toggle inputs
            var element = document.createElement("div");
            element.className = "input";

            this._toggleInputs = [];

            for (var i = 0; i < this.choices.length; i++) {
                var checkboxInput = document.createElement("input");
                checkboxInput.className = "toggleInput";
                checkboxInput.type = "checkbox";
                checkboxInput.value = this.choices[i].value;

                // TODO: handle default value

                this._toggleInputs.push(checkboxInput);

                var label = new TextBlock(this.container);
                label.text = this.choices[i].display;

                var labelElement = label.render();
                labelElement.className += " toggleLabel";

                var compoundInput = document.createElement("div");

                Utils.appendChild(compoundInput, checkboxInput);
                Utils.appendChild(compoundInput, labelElement);

                Utils.appendChild(element, compoundInput);
            }

            return element;
        }
    }
}

export class InputNumber extends Input {
    static TypeName: string = "Input.Number";

    private _numberInputElement: HTMLInputElement;

    min: string;
    max: string;

    constructor(container: Container) {
        super(container);
    }

    get value(): string {
        return this._numberInputElement.value;
    }

    render(): HTMLElement {
        this._numberInputElement = document.createElement("input");
        this._numberInputElement.type = "number";
        this._numberInputElement.className = "input number";
        this._numberInputElement.min = this.min;
        this._numberInputElement.max = this.max;

        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._numberInputElement.value = this.defaultValue;
        }

        return this._numberInputElement;
    }
}

export class InputDate extends Input {
    static TypeName: string = "Input.Date";

    private _dateInputElement: HTMLInputElement;

    constructor(container: Container) {
        super(container);
    }

    get value(): string {
        return this._dateInputElement.value;
    }

    render(): HTMLElement {
        this._dateInputElement = document.createElement("input");
        this._dateInputElement.type = "date";
        this._dateInputElement.className = "input date";

        return this._dateInputElement;
    }
}

export class InputTime extends Input {
    static TypeName: string = "Input.Time";

    private _timeInputElement: HTMLInputElement;

    constructor(container: Container) {
        super(container);
    }

    get value(): string {
        return this._timeInputElement.value;
    }

    render(): HTMLElement {
        this._timeInputElement = document.createElement("input");
        this._timeInputElement.type = "time";
        this._timeInputElement.className = "input time";

        return this._timeInputElement;
    }
}

export class ActionButton {
    private _action: Action;
    private _style: Enums.ActionButtonStyle;
    private _onClick: Eventing.EventDispatcher<ActionButton, any> = new Eventing.EventDispatcher<ActionButton, any>();
    private _element: HTMLElement = null;
    private _state: Enums.ActionButtonState = Enums.ActionButtonState.Normal;
    private _text: string;

    private click() {
        this._onClick.dispatch(this, null);
    }

    private updateCssStyle() {
        let cssStyle = this._style == Enums.ActionButtonStyle.Link ? "linkButton " : "pushButton ";

        switch (this._state) {
            case Enums.ActionButtonState.Expanded:
                cssStyle += " expanded";
                break;
            case Enums.ActionButtonState.Subdued:
                cssStyle += " subdued";
                break;
        }

        this._element.className = cssStyle;
    }

    constructor(action: Action, style: Enums.ActionButtonStyle) {
        this._action = action;
        this._style = style;
        this._element = document.createElement("div");
        this._element.onclick = (e) => { this.click(); };

        this.updateCssStyle();
    }

    get action() {
        return this._action;
    }

    get onClick(): Eventing.IEvent<ActionButton, any> {
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

    get state(): Enums.ActionButtonState {
        return this._state;
    }

    set state(value: Enums.ActionButtonState) {
        this._state = value;

        this.updateCssStyle();
    }
}

export abstract class Action {
    name: string;

    abstract execute();

    parse(json: any) {
        this.name = json["title"];
    }

    renderUi(): HTMLElement {
        return null;
    }

    get hasUi(): boolean {
        return false;
    }
}

export abstract class ActionExternal extends Action {
    private _onExecute: Eventing.EventDispatcher<ActionExternal, any> = new Eventing.EventDispatcher<ActionExternal, any>();

    execute() {
        this._onExecute.dispatch(this, null);
    }

    get onExecute(): Eventing.IEvent<ActionExternal, any> {
        return this._onExecute;
    }
}

export class ActionSubmit extends ActionExternal {
    static TypeName: string = "Action.Submit";
}

export class ActionOpenUrl extends ActionExternal {
    static TypeName: string = "Action.OpenUrl";

    url: string;
}

export class HttpHeader {
    name: string;
    value: string;
}

export class ActionHttp extends ActionExternal {
    static TypeName: string = "Action.Http";
    
    private _headers: Array<HttpHeader> = [];

    url: string;
    method: string;
    body: string;

    get headers(): Array<HttpHeader> {
        return this._headers;
    }
}

export class ActionShowCard extends Action {
    static TypeName: string = "Action.ShowCard";

    card: Container;
    name: string;

    /*
    private actionClicked(actionButton: ActionButton) {
        alert('Now executing "' + actionButton.text + '"');
    }
    */

    execute() {
        // TODO
    }

    get hasUi(): boolean {
        return true;
    }

    renderUi(): HTMLElement {
        var renderedCard = this.card.internalRender();
        renderedCard.style.marginTop = "0px";

        return renderedCard;
    }
}

export class ActionCollection {
    private _container: Container;
    private _actionButtons: Array<ActionButton> = [];
    private _actionCardContainer: HTMLDivElement;
    private _items: Array<Action> = [];
    private _expandedAction: Action = null;

    private hideActionCardPane() {
        this._actionCardContainer.innerHTML = '';
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";

        this._container.showBottomSpacer();
    }

    private showActionCardPane(action: Action) {
        this._container.hideBottomSpacer();

        this._actionCardContainer.innerHTML = '';
        this._actionCardContainer.style.padding = null;
        this._actionCardContainer.style.marginTop = this._items.length > 1 ? null : "0px";

        Utils.appendChild(this._actionCardContainer, action.renderUi());
    }

    private actionClicked(actionButton: ActionButton) {
        if (!actionButton.action.hasUi) {
            for (var i = 0; i < this._actionButtons.length; i++) {
                this._actionButtons[i].state = Enums.ActionButtonState.Normal;
            }

            this.hideActionCardPane();

            actionButton.action.execute();
        }
        else {
            if (AdaptiveCard.options.actionShowCardInPopup) {
                AdaptiveCard.showPopupCard(<ActionShowCard>actionButton.action, actionButton.action.renderUi());
            }
            else if (actionButton.action === this._expandedAction) {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    this._actionButtons[i].state = Enums.ActionButtonState.Normal;
                }

                this._expandedAction = null;

                this.hideActionCardPane();
            }
            else {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    if (this._actionButtons[i] !== actionButton) {
                        this._actionButtons[i].state = Enums.ActionButtonState.Subdued;
                    }
                }

                actionButton.state = Enums.ActionButtonState.Expanded;

                this._expandedAction = actionButton.action;

                this.showActionCardPane(actionButton.action);
            }
        }
    }

    constructor(container: Container) {
        this._container = container;
    }

    get container(): Container {
        return this._container;
    }

    get items(): Array<Action> {
        return this._items;
    }

    get hideOverflow(): boolean {
        return false;
    }

    render(): HTMLElement {
        let element = document.createElement("div");
        element.className = "actionGroup";

        let buttonStrip = document.createElement("div");
        buttonStrip.className = "buttonStrip";

        this._actionCardContainer = document.createElement("div");
        this._actionCardContainer.className = "actionCardContainer";
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";

        if (this._items.length == 1 && this._items[0] instanceof ActionShowCard) {
            this.showActionCardPane(this._items[0]);
        }
        else {
            for (let i = 0; i < this._items.length; i++) {
                let buttonStripItem = document.createElement("div");
                buttonStripItem.className = "buttonStripItem";

                let actionButton = new ActionButton(this._items[i], this._container.actionButtonStyle);
                actionButton.text = this._items[i].name;

                actionButton.onClick.subscribe(
                    (ab, args) => {
                        this.actionClicked(ab);
                    });

                this._actionButtons.push(actionButton);

                if (i < this._items.length - 1) {
                    buttonStripItem.className += " buttonStripItemSpacer";
                }

                Utils.appendChild(buttonStripItem, actionButton.element);
                Utils.appendChild(buttonStrip, buttonStripItem);
            }
        }

        Utils.appendChild(element, buttonStrip);

        Utils.appendChild(element, this._actionCardContainer);

        return element;
    }
}

export class Container extends CardElement {
    static TypeName: string = "Container";
    static defaultActionButtonStyle: Enums.ActionButtonStyle = Enums.ActionButtonStyle.Push;

    private _items: Array<CardElement> = [];
    private _element: HTMLDivElement;
    private _textColor: Enums.TextColor = Enums.TextColor.Default;
    private _itemsCollectionPropertyName: string;

    protected get cssClassName(): string {
        return "container";
    }

    backgroundImageUrl: string;
    backgroundColor: string;
    actionButtonStyle: Enums.ActionButtonStyle = Container.defaultActionButtonStyle;
    actions: ActionCollection;
    selectAction: ActionExternal;
    isGroupStart: boolean;

    constructor(
        container: Container,
        itemsCollectionPropertyName: string = "items") {
        super(container);

        this._itemsCollectionPropertyName = itemsCollectionPropertyName;
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

    get textColor(): Enums.TextColor {
        if (this.container == null) {
            return this._textColor == Enums.TextColor.Default ? Enums.TextColor.Dark : this._textColor;
        }

        if (this._textColor == Enums.TextColor.Default) {
            return this.container.textColor;
        }

        return this._textColor;
    }

    set textColor(value: Enums.TextColor) {
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

    showBottomSpacer(requestingElement: CardElement = null) {
        if (requestingElement == null || this.isLastElement(requestingElement)) {
            this._element.style.paddingBottom = null;

            if (this.container != null) {
                this.container.showBottomSpacer(this);
            }
        }
    }

    hideBottomSpacer(requestingElement: CardElement = null) {
        if (requestingElement == null || this.isLastElement(requestingElement)) {
            this._element.style.paddingBottom = "0px";

            if (this.container != null) {
                this.container.hideBottomSpacer(this);
            }
        }
    }

    render(): HTMLElement {
        if (this.elementCount > 0) {
            this._element = document.createElement("div");
            this._element.className = this.cssClassName;

            if (this.isGroupStart) {
                this._element.className += " startGroup";
            }

            if (!Utils.isNullOrEmpty(this.backgroundColor)) {
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

                    Utils.appendChild(this._element, renderedElement);
                }

                previousElement = this.getElement(i);
            }

            if (!Utils.isNullOrEmpty(this.backgroundImageUrl)) {
                this._element.style.backgroundImage = 'url("' + this.backgroundImageUrl + '")';
                this._element.style.backgroundRepeat = "no-repeat";
                this._element.style.backgroundSize = "cover";
            }

            if (this.actions != null) {
                Utils.appendChild(this._element, this.actions.render());
            }
        }

        return this._element;
    }

    renderSpeech(): string {
        if (this.speak != null) {
            return this.speak;
        }

        // render each item
        let speak = null;

        if (this._items.length > 0) {
            speak = '';

            for (var i = 0; i < this._items.length; i++) {
                var result = this._items[i].renderSpeech();

                if (result) {
                    speak += result;
                }
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
    weight: number = 100;

    protected get cssClassName(): string {
        return "column";
    }

    adjustLayout(element: HTMLElement) {
        if (this.weight > 0) {
            element.style.flex = "1 1 " + this.weight + "%";
        }
        else if (this.weight == 0) {
            element.style.flex = "0 0 auto";
        }
        else {
            element.style.flex = "1 1 auto";
        }
    }
}

export class ColumnSet extends CardElement {
    static TypeName: string = "ColumnSet";

    private _columns: Array<Column> = [];

    get columns(): Array<Column> {
        return this._columns;
    }

    render(): HTMLElement {
        if (this._columns.length > 0) {
            var element = document.createElement("div");
            element.className = "columnGroup";
            element.style.display = "flex";

            for (let i = 0; i < this._columns.length; i++) {
                var renderedColumn = this._columns[i].internalRender();

                Utils.appendChild(element, renderedColumn);

                if (this._columns.length > 1 && i < this._columns.length - 1) {
                    var spacer = document.createElement("div");
                    spacer.className = "columnSpacer";
                    spacer.style.flex = "0 0 auto";

                    if (this._columns[i + 1].isGroupStart) {
                        spacer.className += " startGroup";

                        var separator = document.createElement("div");
                        separator.className = "columnSeparator";

                        Utils.appendChild(spacer, separator);
                    }

                    Utils.appendChild(element, spacer);
                }
            }

            return element;
        }
        else {
            return null;
        }
    }

    renderSpeech(): string {
        if (this.speak != null) {
            return this.speak;
        }

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

export interface IAdaptiveCardOptions {
    actionShowCardInPopup: boolean;
}

export class AdaptiveCard {
    private static _options: IAdaptiveCardOptions;

    static onShowPopupCard: (action: ActionShowCard, renderedCard: HTMLElement) => void = null;

    static showPopupCard(action: ActionShowCard, renderedCard: HTMLElement) {
        if (AdaptiveCard.onShowPopupCard != null) {
            AdaptiveCard.onShowPopupCard(action, renderedCard);
        }
    }

    static options: IAdaptiveCardOptions = {
        actionShowCardInPopup: false
    };

    private _onExecuteAction: Eventing.EventDispatcher<ActionExternal, any> = new Eventing.EventDispatcher<ActionExternal, any>();

    allInputs: Array<Input> = [];
    root = new Container(null, "body");

    get onExecuteAction(): Eventing.IEvent<ActionExternal, any> {
        return this._onExecuteAction;
    }

    executeAction(action: ActionExternal) {
        this._onExecuteAction.dispatch(action, null);
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