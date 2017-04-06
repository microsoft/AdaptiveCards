import * as Enums from "./enums";
import * as Utils from "./utils";
import * as TextFormatters from "./text-formatter";

function invokeSetContainer(obj: any, container: Container) {
    obj["setContainer"](container);
}

export abstract class CardElement {
    private _container: Container = null;

    private getRootElement(): CardElement {
        if (!this._container) {
            return this;
        }

        return this._container.getRootElement();
    }

    protected setContainer(value: Container) {
        this._container = value;
    }

    protected get hideOverflow(): boolean {
        return true;
    }

    protected get useDefaultSizing(): boolean {
        return true;
    }

    protected removeTopSpacing(element: HTMLElement) {
        element.className += " removeTopSpacing";
    }

    protected adjustAlignment(element: HTMLElement) {
        switch (this.horizontalAlignment) {
            case Enums.HorizontalAlignment.Center:
                element.style.textAlign = "center";
                break;
            case Enums.HorizontalAlignment.Right:
                element.style.textAlign = "right";
                break;
        }
    }

    protected adjustLayout(element: HTMLElement) {
        if (this.useDefaultSizing) {
            element.className += " stretch";
        }

        this.adjustAlignment(element);

        if (this.separation != Enums.Separation.Default) {
            this.removeTopSpacing(element);
        }

        if (this.hideOverflow) {
            element.style.overflow = "hidden";
        }
    }

    protected abstract internalRender(): HTMLElement;

    speak: string;
    horizontalAlignment: Enums.HorizontalAlignment = Enums.HorizontalAlignment.Left;
    separation: Enums.Separation;

    abstract renderSpeech(): string;

    render(/* container: Container = null */): HTMLElement {
        // this._container = container;

        let renderedElement = this.internalRender();

        if (renderedElement != null) {
            this.adjustLayout(renderedElement);
        }

        return renderedElement;
    }

    getRootContainer(): Container {
        var rootElement = this.getRootElement();

        if (rootElement instanceof Container) {
            return <Container>rootElement;
        }
        else {
            return null;
        }
    }

    get container(): Container {
        return this._container;
    }
}

export class TextBlock extends CardElement {
    static TypeName: string = "TextBlock";

    size: Enums.TextSize = Enums.TextSize.Normal;
    weight: Enums.TextWeight = Enums.TextWeight.Normal;
    color?: Enums.TextColor;
    text: string;
    isSubtle: boolean = false;
    wrap: boolean = true;
    maxLines: number;

    protected internalRender(): HTMLElement {
        if (!Utils.isNullOrEmpty(this.text)) {
            let element = document.createElement("div");

            let cssStyle = "text ";

            switch (this.size) {
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

            /// let actualTextColor = this.color ? this.color : (container.textColor ? container.textColor : AdaptiveCard.renderOptions.defaultTextColor);
            let actualTextColor = this.color ? this.color : this.container.textColor;

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

            switch (this.weight) {
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
}

class InternalTextBlock extends TextBlock {
    get useDefaultSizing(): boolean {
        return false;
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

    protected get useDefaultSizing(): boolean {
        return false;
    }

    protected internalRender(): HTMLElement {
        let element: HTMLElement = null;

        if (this.facts.length > 0) {
            element = document.createElement("table");
            element.className = "factGroup";

            let html: string = '';

            for (var i = 0; i < this.facts.length; i++) {
                html += '<tr>';
                html += '    <td class="factName">';

                let textBlock = new InternalTextBlock();
                textBlock.text = this.facts[i].name;
                textBlock.weight = Enums.TextWeight.Bolder;
                textBlock.separation = Enums.Separation.None;

                invokeSetContainer(textBlock, this.container);

                let renderedText = textBlock.render(); // this.container);

                if (renderedText != null) {
                    html += renderedText.outerHTML;
                }

                html += '    </td>';
                html += '    <td class="factValue">';

                textBlock = new InternalTextBlock();
                textBlock.text = this.facts[i].value;
                textBlock.weight = Enums.TextWeight.Lighter;
                textBlock.separation = Enums.Separation.None;

                invokeSetContainer(textBlock, this.container);

                renderedText = textBlock.render(); // this.container);

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

    facts: Array<Fact> = [];

    renderSpeech(): string {
        if (this.speak != null) {
            return this.speak + '\n';
        }

        // render each fact 
        let speak = null;

        if (this.facts.length > 0) {
            speak = '';

            for (var i = 0; i < this.facts.length; i++) {
                let speech = this.facts[i].renderSpeech();

                if (speech) {
                    speak += speech;
                }
            }
        }

        return '<p>' + speak + '\n</p>\n';
    }
}

export class Image extends CardElement {
    static TypeName: string = "Image";

    protected get useDefaultSizing() {
        return false;
    }

    protected adjustAlignment(element: HTMLElement) {
        switch (this.horizontalAlignment) {
            case Enums.HorizontalAlignment.Center:
                element.style.marginLeft = "auto";
                element.style.marginRight = "auto";

                break;
            case Enums.HorizontalAlignment.Right:
                element.style.marginLeft = "auto";

                break;
        }
    }

    protected internalRender(): HTMLElement {
        let imageElement: HTMLImageElement = null;

        if (!Utils.isNullOrEmpty(this.url)) {
            imageElement = document.createElement("img");
            imageElement.style.display = "block";
            imageElement.onclick = (e) => {
                if (this.selectAction != null) {
                    raiseExecuteActionEvent(this.container, this.selectAction);
                    e.cancelBubble = true;
                }
            }

            let cssStyle = "image";

            if (this.selectAction != null) {
                cssStyle += " selectable";
            }

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

    style: Enums.ImageStyle = Enums.ImageStyle.Normal;
    url: string;
    size: Enums.Size = Enums.Size.Medium;
    selectAction: ActionExternal;

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

    protected internalRender(): HTMLElement {
        let element: HTMLElement = null;

        if (this._images.length > 0) {
            element = document.createElement("div");
            element.className = "imageGallery";

            for (var i = 0; i < this._images.length; i++) {
                let renderedImage = this._images[i].render(); // this.container);
                renderedImage.style.margin = "0px";
                renderedImage.style.marginRight = "10px";

                Utils.appendChild(element, renderedImage);
            }
        }

        return element;
    }

    imageSize: Enums.Size = Enums.Size.Medium;

    addImage(image: Image) {
        if (!image.container) {
            this._images.push(image);

            invokeSetContainer(image, this.container);
        }
        else {
            throw new Error("This image already belongs to another ImageSet");
        }
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

export abstract class Input extends CardElement implements Utils.IInput {
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

export class TextInput extends Input {
    static TypeName: string = "Input.Text";

    private _textareaElement: HTMLTextAreaElement;

    protected internalRender(): HTMLElement {
        this._textareaElement = document.createElement("textarea");
        this._textareaElement.className = "input textInput";

        if (this.isMultiline) {
            this._textareaElement.className += " multiline";
        }

        if (!Utils.isNullOrEmpty(this.placeholder)) {
            this._textareaElement.placeholder = this.placeholder;
        }

        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._textareaElement.textContent = this.defaultValue;
        }

        if (this.maxLength > 0) {
            this._textareaElement.maxLength = this.maxLength;
        }

        return this._textareaElement;
    }

    maxLength: number;
    isMultiline: boolean;
    placeholder: string;

    get value(): string {
        return this._textareaElement ? this._textareaElement.textContent : null;
    }
}

export class ToggleInput extends Input {
    static TypeName: string = "Input.Toggle";

    private _checkboxInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement {
        var element = document.createElement("div");
        element.className = "input";

        this._checkboxInputElement = document.createElement("input");
        this._checkboxInputElement.className = "toggleInput";
        this._checkboxInputElement.type = "checkbox";

        if (this.defaultValue == this.valueOn) {
            this._checkboxInputElement.checked = true;
        }

        var label = new InternalTextBlock();
        label.text = this.title;

        invokeSetContainer(label, this.container);

        var labelElement = label.render(); // this.container);
        labelElement.className += " toggleLabel";

        var compoundInput = document.createElement("div");

        Utils.appendChild(element, this._checkboxInputElement);
        Utils.appendChild(element, labelElement);

        return element;
    }

    title: string;
    valueOn: string;
    valueOff: string;

    get value(): string {
        if (this._checkboxInputElement) {
            return this._checkboxInputElement.checked ? this.valueOn : this.valueOff;
        }
        else {
            return null;
        }
    }
}

export class Choice {
    title: string;
    value: string;
}

export class ChoiceSetInput extends Input {
    static TypeName: string = "Input.ChoiceSet";

    private _selectElement: HTMLSelectElement;
    private _toggleInputs: Array<HTMLInputElement>;

    protected internalRender(): HTMLElement {
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
                    option.text = this.choices[i].title;

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

                    this._toggleInputs.push(radioInput);

                    var label = new InternalTextBlock();
                    label.text = this.choices[i].title;

                    invokeSetContainer(label, this.container);

                    var labelElement = label.render(); // this.container);
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

                this._toggleInputs.push(checkboxInput);

                var label = new InternalTextBlock();
                label.text = this.choices[i].title;

                invokeSetContainer(label, this.container);

                var labelElement = label.render(); // this.container);
                labelElement.className += " toggleLabel";

                var compoundInput = document.createElement("div");

                Utils.appendChild(compoundInput, checkboxInput);
                Utils.appendChild(compoundInput, labelElement);

                Utils.appendChild(element, compoundInput);
            }

            return element;
        }
    }

    choices: Array<Choice> = [];
    isCompact: boolean;
    isMultiSelect: boolean;
    placeholder: string;

    get value(): string {
        if (!this.isMultiSelect) {
            if (this.isCompact) {
                return this._selectElement ? this._selectElement.value : null;
            }
            else {
                if (this._toggleInputs.length == 0) {
                    return null;
                }

                for (var i = 0; i < this._toggleInputs.length; i++) {
                    if (this._toggleInputs[i].checked) {
                        return this._toggleInputs[i].value;
                    }
                }

                return null;
            }
        }
        else {
            if (this._toggleInputs.length == 0) {
                return null;
            }
            
            var result: string = "";

            for (var i = 0; i < this._toggleInputs.length; i++) {
                if (this._toggleInputs[i].checked) {
                    if (result != "") {
                        result += ";";
                    }

                    result += this._toggleInputs[i].value;
                }
            }

            return result == "" ? null : result;
        }
    }
}

export class NumberInput extends Input {
    static TypeName: string = "Input.Number";

    private _numberInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement {
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

    min: string;
    max: string;

    get value(): string {
        return this._numberInputElement ? this._numberInputElement.value : null;
    }
}

export class DateInput extends Input {
    static TypeName: string = "Input.Date";

    private _dateInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement {
        this._dateInputElement = document.createElement("input");
        this._dateInputElement.type = "date";
        this._dateInputElement.className = "input date";

        return this._dateInputElement;
    }

    get value(): string {
        return this._dateInputElement ? this._dateInputElement.value : null;
    }
}

export class TimeInput extends Input {
    static TypeName: string = "Input.Time";

    private _timeInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement {
        this._timeInputElement = document.createElement("input");
        this._timeInputElement.type = "time";
        this._timeInputElement.className = "input time";

        return this._timeInputElement;
    }

    get value(): string {
        return this._timeInputElement ? this._timeInputElement.value : null;
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
    private _element: HTMLElement = null;
    private _state: ActionButtonState = ActionButtonState.Normal;
    private _text: string;

    private click() {
        if (this.onClick != null) {
            this.onClick(this);
        }
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

    onClick: (actionButton: ActionButton) => void = null;

    get action() {
        return this._action;
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

export abstract class Action {
    private _container: Container = null;

    protected setContainer(value: Container) {
        this._container = value;
    }

    prepare(inputs: Array<Input>) {
        // Do nothing in base implementation
    };

    title: string;

    get container(): Container {
        return this._container;
    }
}

export abstract class ActionExternal extends Action {
}

export class ActionSubmit extends ActionExternal {
    static TypeName: string = "Action.Submit";

    private _isPrepared: boolean = false;
    private _originalData: Object;
    private _processedData: Object;

    prepare(inputs: Array<Input>) {
        if (this._originalData) {
            this._processedData = JSON.parse(JSON.stringify(this._originalData));
        }
        else {
            this._processedData = { };
        }

        for (var i = 0; i < inputs.length; i++) {
            var inputValue = inputs[i].value;

            if (inputValue != null) {
                this._processedData[inputs[i].id] = inputs[i].value;
            }
        }

        this._isPrepared = true;
    }

    get data(): Object {
        return this._isPrepared ? this._processedData : this._originalData;
    }

    set data(value: Object) {
        this._originalData = value;
        this._isPrepared = false;
    }
}

export class ActionOpenUrl extends ActionExternal {
    static TypeName: string = "Action.OpenUrl";

    url: string;
}

export class HttpHeader {
    private _value = new Utils.StringWithSubstitutions();

    name: string;

    get value(): string {
        return this._value.get();
    }

    set value(newValue: string) {
        this._value.set(newValue);
    }
}

export class ActionHttp extends ActionExternal {
    static TypeName: string = "Action.Http";

    private _url = new Utils.StringWithSubstitutions();
    private _headers: Array<HttpHeader> = [];
    private _body = new Utils.StringWithSubstitutions();

    method: string;

    prepare(inputs: Array<Input>) {
        Utils.substituteInputValues(this, inputs);
    };

    get url(): string {
        return this._url.get();
    }

    set url(value: string) {
        this._url.set(value);
    }

    get body(): string {
        return this._body.get();
    }

    set body(value: string) {
        this._body.set(value);
    }

    get headers(): Array<HttpHeader> {
        return this._headers;
    }
}

export class ActionShowCard extends Action {
    static TypeName: string = "Action.ShowCard";

    protected setContainer(value: Container) {
        super.setContainer(value);

        invokeSetContainer(this.card, value);
    }

    readonly card: ActionShowCardContainer;

    title: string;

    constructor() {
        super();

        this.card = new ActionShowCardContainer();
    }
}

export class ActionCollection {
    private _container: Container;
    private _forbiddenActionTypes: Array<any>;
    private _actionButtons: Array<ActionButton> = [];
    private _actionCardContainer: HTMLDivElement;
    private _expandedAction: Action = null;

    private hideActionCardPane() {
        this._actionCardContainer.innerHTML = '';
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";

        if (this.onHideActionCardPane) {
            this.onHideActionCardPane();
        }
    }

    private showActionCardPane(action: ActionShowCard) {
        if (this.onShowActionCardPane) {
            this.onShowActionCardPane(action);
        }

        this._actionCardContainer.innerHTML = '';

        var padding = Utils.getActualPadding(this._actionCardContainer);

        this._actionCardContainer.style.padding = null;
        this._actionCardContainer.style.paddingLeft = padding.left + "px";
        this._actionCardContainer.style.paddingRight = padding.right + "px";

        this._actionCardContainer.style.marginTop = this.items.length > 1 ? null : "0px";
        this._actionCardContainer.style.marginLeft = "-" + padding.left + "px";
        this._actionCardContainer.style.marginRight = "-" + padding.right + "px";

        Utils.appendChild(this._actionCardContainer, action.card.render()); // this._container));
    }

    private actionClicked(actionButton: ActionButton) {
        if (!(actionButton.action instanceof ActionShowCard)) {
            for (var i = 0; i < this._actionButtons.length; i++) {
                this._actionButtons[i].state = ActionButtonState.Normal;
            }

            this.hideActionCardPane();

            raiseExecuteActionEvent(this._container, <ActionExternal>actionButton.action);
        }
        else {
            if (AdaptiveCard.renderOptions.actionShowCardInPopup) {
                var actionShowCard = <ActionShowCard>actionButton.action;

                raiseShowPopupCardEvent(this._container, actionShowCard, actionShowCard.card.render()); // this._container));
            }
            else if (actionButton.action === this._expandedAction) {
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

    /*
    private checkActionTypeIsAllowed(action: Action): boolean {
        var className = Utils.getClassNameFromInstance(action);
        var typeIsForbidden = false;

        if (this._forbiddenActionTypes) {
            for (var i = 0; i < this._forbiddenActionTypes.length; i++) {
                if (className === Utils.getClassNameFromConstructor(this._forbiddenActionTypes[i])) {
                    typeIsForbidden = true;
                    break;
                }
            }
        }

        if (!typeIsForbidden) {
            for (var i = 0; i < AdaptiveCard.renderOptions.supportedActionTypes.length; i++) {
                if (className === Utils.getClassNameFromConstructor(AdaptiveCard.renderOptions.supportedActionTypes[i])) {
                    return true;
                }
            }
        }

        raiseValidationErrorEvent(
            Enums.ValidationError.ActionTypeNotAllowed,
            "Actions of type " + className + " are not allowed.");

        return false;
    }
    */

    constructor(container: Container, forbiddenActionTypes?: Array<any>) {
        this._container = container;
        this._forbiddenActionTypes = forbiddenActionTypes;
    }
    
    items: Array<Action> = [];
    onHideActionCardPane: () => void = null;
    onShowActionCardPane: (action: ActionShowCard) => void = null;

    render(): HTMLElement {
        /*
        if (this._container.container != null && !AdaptiveCard.renderOptions.supportsNestedActions) {
            AdaptiveCard.raiseRenderError(
                Enums.RenderError.NestedActionNotAllowed,
                "Nested actions are not allowed.");

            return null;
        }
        */

        if (AdaptiveCard.renderOptions.maxActions != null && AdaptiveCard.renderOptions.maxActions < this.items.length) {
            raiseValidationErrorEvent(
                Enums.ValidationError.TooManyActions,
                "There are " + this.items.length.toString() + " in the actions collection, but only " + AdaptiveCard.renderOptions.maxActions.toString() + " are allowed.");

            return null;
        }

        let element = document.createElement("div");
        element.className = "actionGroup";

        let buttonStrip = document.createElement("div");
        buttonStrip.className = "buttonStrip";

        this._actionCardContainer = document.createElement("div");
        this._actionCardContainer.className = "actionCardContainer";
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";

        var renderedActions: number = 0;

        if (this.items.length == 1 && this.items[0] instanceof ActionShowCard) {
            // if (this.checkActionTypeIsAllowed(this.items[0])) {
                this.showActionCardPane(<ActionShowCard>this.items[0]);

                renderedActions++;
            // }
        }
        else {
            var actionButtonStyle = ActionButtonStyle.Push;

            for (var i = 0; i < this.items.length; i++) {
                if (this.items[i] instanceof ActionShowCard) {
                    actionButtonStyle = ActionButtonStyle.Link;
                    break;
                }
            }

            for (var i = 0; i < this.items.length; i++) {
                // if (this.checkActionTypeIsAllowed(this.items[i])) {
                    let buttonStripItem = document.createElement("div");
                    buttonStripItem.className = "buttonStripItem";

                    // let actionButton = new ActionButton(this.items[i], this._container.actionButtonStyle);
                    let actionButton = new ActionButton(this.items[i], actionButtonStyle);
                    actionButton.text = this.items[i].title;

                    actionButton.onClick = (ab) => { this.actionClicked(ab); };

                    this._actionButtons.push(actionButton);

                    if (i < this.items.length - 1) {
                        buttonStripItem.className += " buttonStripItemSpacer";
                    }

                    Utils.appendChild(buttonStripItem, actionButton.element);
                    Utils.appendChild(buttonStrip, buttonStripItem);

                    renderedActions++;
                // }
            }

            Utils.appendChild(element, buttonStrip);
        }

        Utils.appendChild(element, this._actionCardContainer);

        return renderedActions > 0 ? element : null;
    }
}

export class Container extends CardElement {
    static TypeName: string = "Container";

    private showBottomSpacer(requestingElement: CardElement = null) {
        if (requestingElement == null || this.isLastItem(requestingElement)) {
            if (this.container) {
                this.container.showBottomSpacer(this);
            }

            this._element.style.paddingBottom = null;
        }
    }

    private hideBottomSpacer(requestingElement: CardElement = null) {
        if (requestingElement == null || this.isLastItem(requestingElement)) {
            if (this.container) {
                this.container.hideBottomSpacer(this);
            }

            this._element.style.paddingBottom = "0px";
        }
    }

    private checkElementTypeIsAllowed(element: CardElement) {
        var className = Utils.getClassNameFromInstance(element);
        var typeIsForbidden = false;
        var forbiddenElementTypes = this.getForbiddenElementTypes();

        if (forbiddenElementTypes) {
            for (var i = 0; i < forbiddenElementTypes.length; i++) {
                if (className === Utils.getClassNameFromConstructor(forbiddenElementTypes[i])) {
                    typeIsForbidden = true;
                    break;
                }
            }
        }

        if (!typeIsForbidden) {
            for (var i = 0; i < AdaptiveCard.renderOptions.supportedElementTypes.length; i++) {
                if (className === Utils.getClassNameFromConstructor(AdaptiveCard.renderOptions.supportedElementTypes[i])) {
                    return true;
                }
            }
        }

        raiseValidationErrorEvent(
            Enums.ValidationError.ElementTypeNotAllowed,
            "Elements of type " + className + " are not allowed in this container.");

        return false;
    }
    
    private checkActionTypeIsAllowed(action: Action): boolean {
        var className = Utils.getClassNameFromInstance(action);
        var typeIsForbidden = false;
        var forbiddenActionTypes = this.getForbiddenActionTypes();

        if (forbiddenActionTypes) {
            for (var i = 0; i < forbiddenActionTypes.length; i++) {
                if (className === Utils.getClassNameFromConstructor(forbiddenActionTypes[i])) {
                    typeIsForbidden = true;
                    break;
                }
            }
        }

        if (!typeIsForbidden) {
            for (var i = 0; i < AdaptiveCard.renderOptions.supportedActionTypes.length; i++) {
                if (className === Utils.getClassNameFromConstructor(AdaptiveCard.renderOptions.supportedActionTypes[i])) {
                    return true;
                }
            }
        }

        raiseValidationErrorEvent(
            Enums.ValidationError.ActionTypeNotAllowed,
            "Actions of type " + className + " are not allowed in this container.");

        return false;
    }

    private _items: Array<CardElement> = [];
    private _hasBottomPadding?: boolean;

    protected _actionCollection: ActionCollection;
    protected _element: HTMLDivElement;

    protected isLastItem(element: CardElement): boolean {
        return this._items.indexOf(element) == (this._items.length - 1);
    }

    protected getForbiddenElementTypes(): Array<any> {
        return null;
    }

    protected getForbiddenActionTypes(): Array<any> {
        return null;
    }

    protected internalRender(): HTMLElement {
        this._element = document.createElement("div");
        this._element.className = this.cssClassName;
        this._element.onclick = (e) => {
            if (this.selectAction != null) {
                raiseExecuteActionEvent(this.container, this.selectAction);
                e.cancelBubble = true;
            }
        }

        if (!Utils.isNullOrEmpty(this.backgroundColor)) {
            this._element.style.backgroundColor = this.backgroundColor;
        }

        if (this._items.length > 0) {
            var renderedElementCount: number = 0;

            for (var i = 0; i < this._items.length; i++) {
                // if (Container.checkElementTypeIsAllowed(this._items[i])) {
                    var renderedElement = this._items[i].render(); // this);

                    if (renderedElement != null) {
                        if (renderedElementCount == 0) {
                            this.removeTopSpacing(renderedElement);
                        }
                        else {
                            if (this._items[i].separation == Enums.Separation.Strong) {
                                var separator = document.createElement("div");
                                separator.className = "separator";

                                Utils.appendChild(this._element, separator);
                            }
                        }

                        Utils.appendChild(this._element, renderedElement);

                        renderedElementCount++;
                    }
                // }
            }
        }

        var renderedActions = this._actionCollection.render();

        Utils.appendChild(this._element, renderedActions);

        if (renderedElementCount > 0 || renderedActions != null) {
            if (!Utils.isNullOrEmpty(this.backgroundImageUrl)) {
                this._element.style.backgroundImage = 'url("' + this.backgroundImageUrl + '")';
                this._element.style.backgroundRepeat = "no-repeat";
                this._element.style.backgroundSize = "cover";
            }

            return this._element;
        }
        else {
            return null;
        }
    }

    protected get hideOverflow() {
        return false;
    }

    protected get cssClassName(): string {
        var className = "container";

        if (this.selectAction != null) {
            className += " selectable";
        }

        return className;
    }

    backgroundImageUrl: string;
    backgroundColor: string;
    // actionButtonStyle: Enums.ActionButtonStyle = AdaptiveCard.renderOptions.defaultActionButtonStyle;
    selectAction: ActionExternal;

    constructor() {
        super();

        this._actionCollection = new ActionCollection(this, this.getForbiddenActionTypes());
        this._actionCollection.onHideActionCardPane = () => { this.showBottomSpacer() };
        this._actionCollection.onShowActionCardPane = (action: ActionShowCard) => { this.hideBottomSpacer() };
    }

    private _textColor?: Enums.TextColor;

    get textColor(): Enums.TextColor {
        if (!this._textColor) {
            if (this.container) {
                return this.container.textColor;
            }
            else {
                return AdaptiveCard.renderOptions.defaultTextColor;
            }
        }
        else {
            return this._textColor;
        }
    }

    set textColor(value: Enums.TextColor) {
        this._textColor = value;
    }

    addItem(item: CardElement) {
        if (this.checkElementTypeIsAllowed(item)) {
            if (!item.container) {
                this._items.push(item);

                invokeSetContainer(item, this);
            }
            else {
                throw new Error("The element already belongs to another container.")
            }
        }
    }

    addAction(action: Action) {
        var isNested = this.container || this instanceof ActionShowCardContainer;
        var addAction = true;

        if (isNested && !AdaptiveCard.renderOptions.supportsNestedActions) {
            raiseValidationErrorEvent(
                Enums.ValidationError.NestedActionNotAllowed,
                "Nested actions are not allowed.");

            addAction = false;
        }

        if (addAction) {
            addAction = this.checkActionTypeIsAllowed(action);
        }

        if (addAction) {
            this._actionCollection.items.push(action);

            invokeSetContainer(action, this);
        }
    }

    getAllInputs(): Array<Input> {
        var result: Array<Input> = [];

        for (var i = 0; i < this._items.length; i++) {
            var item: CardElement = this._items[i];

            if (item instanceof Input) {
                result.push(<Input>item);
            }

            if (item instanceof Container) {
                result = result.concat((<Container>item).getAllInputs());
            }
        }

        for (var i = 0; i < this._actionCollection.items.length; i++) {
            var action = this._actionCollection.items[i];

            if (action instanceof ActionShowCard) {
                var actionShowCard = <ActionShowCard>action;

                if (actionShowCard.card) {
                    result = result.concat(actionShowCard.card.getAllInputs());
                }
            }
        }

        return result;
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
}

export class ActionShowCardContainer extends Container {
    protected getForbiddenActionTypes(): Array<any> {
        return [ ActionShowCard ];
    }

    protected get cssClassName(): string {
        return "";
    }
}

export class Column extends Container {
    weight: number = 100;

    protected get cssClassName(): string {
        var className = "column";

        if (this.selectAction != null) {
            className += " selectable";
        }

        return className;
    }

    protected adjustLayout(element: HTMLElement) {
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

    protected internalRender(): HTMLElement {
        if (this._columns.length > 0) {
            var element = document.createElement("div");
            element.className = "columnGroup";
            element.style.display = "flex";

            var renderedColumnCount: number = 0;

            for (let i = 0; i < this._columns.length; i++) {
                var renderedColumn = this._columns[i].render(); // this.container);

                if (renderedColumn != null) {
                    Utils.appendChild(element, renderedColumn);

                    if (this._columns.length > 1 && i < this._columns.length - 1 && this._columns[i + 1].separation != Enums.Separation.None) {
                        var separator = document.createElement("div");
                        separator.style.flex = "0 0 auto";

                        switch (this._columns[i + 1].separation) {
                            case Enums.Separation.Default:
                                separator.className = "defaultColumnSeparator";
                                break;
                            case Enums.Separation.Strong:
                                separator.className = "strongColumnSeparator";
                                break;
                        }

                        Utils.appendChild(element, separator);
                    }

                    renderedColumnCount++;
                }
            }

            return renderedColumnCount > 0 ? element : null;
        }
        else {
            return null;
        }
    }

    addColumn(column: Column) {
        if (!column.container) {
            this._columns.push(column);
            invokeSetContainer(column, this.container);
        }
        else {
            throw new Error("This column already belongs to another ColumnSet.");
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

export interface IVersion {
    major: number;
    minor: number;
}

export interface IRenderOptions {
    actionShowCardInPopup: boolean;
    // defaultActionButtonStyle: Enums.ActionButtonStyle;
    defaultTextColor: Enums.TextColor;
    defaultSeparation: Enums.Separation;
    supportedElementTypes: any[];
    supportedActionTypes: any[];
    supportsNestedActions: boolean;
    maxActions?: number;
}

function raiseExecuteActionEvent(container: Container, action: ActionExternal) {
    if (AdaptiveCard.onExecuteAction != null) {
        action.prepare(container.getRootContainer().getAllInputs());

        AdaptiveCard.onExecuteAction(action);
    }
}

function raiseShowPopupCardEvent(container: Container, action: ActionShowCard, renderedCard: HTMLElement) {
    if (AdaptiveCard.onShowPopupCard != null) {
        AdaptiveCard.onShowPopupCard(action, renderedCard);
    }
}

function raiseValidationErrorEvent(error: Enums.ValidationError, data: string) {
    if (AdaptiveCard.onValidationError != null) {
        AdaptiveCard.onValidationError(error, data);
    }
}

export class AdaptiveCard {
    private static currentVersion: IVersion = { major: 1, minor: 0 };

    static onExecuteAction: (action: ActionExternal) => void = null;
    static onShowPopupCard: (action: ActionShowCard, renderedCard: HTMLElement) => void = null;
    static onValidationError: (error: Enums.ValidationError, message: string) => void = null;

    static renderOptions: IRenderOptions = {
        actionShowCardInPopup: false,
        // defaultActionButtonStyle: Enums.ActionButtonStyle.Push,
        defaultTextColor: Enums.TextColor.Dark,
        defaultSeparation: Enums.Separation.Default,
        supportedElementTypes: [
            Container,
            TextBlock,
            Image,
            ImageSet,
            FactSet,
            ColumnSet,
            TextInput,
            DateInput,
            NumberInput,
            ChoiceSetInput,
            ToggleInput
        ],
        supportedActionTypes: [
            ActionHttp,
            ActionOpenUrl,
            ActionSubmit,
            ActionShowCard
        ],
        supportsNestedActions: true
    };

    readonly root: Container = new Container();

    minVersion: IVersion = { major: 1, minor: 0 };
    fallbackText: string;

    render(): HTMLElement {
        var unsupportedVersion: boolean =
            (AdaptiveCard.currentVersion.major < this.minVersion.major) ||
            (AdaptiveCard.currentVersion.major == this.minVersion.major && AdaptiveCard.currentVersion.minor < this.minVersion.minor);

        var renderedCard: HTMLElement;

        if (unsupportedVersion) {
            renderedCard = document.createElement("div");
            renderedCard.innerHTML = this.fallbackText ? this.fallbackText : "The version of this card is not supported.";
        }
        else {
            renderedCard = this.root.render();
            renderedCard.className = "rootContainer";
        }

        return renderedCard;
    }

    renderSpeech(): string {
        return this.root.renderSpeech();
    }
}