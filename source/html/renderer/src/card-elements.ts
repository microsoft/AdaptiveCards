import * as Enums from "./enums";
import * as Utils from "./utils";
import * as HostConfig from "./host-config";
import * as TextFormatters from "./text-formatters";

function invokeSetParent(obj: any, parent: CardElement) {
    // This is not super pretty, but it the closest emulation of
    // "internal" in TypeScript.
    obj["setParent"](parent);
}

function isActionAllowed(action: Action, forbiddenActionTypes: Array<string>): boolean {
    if (forbiddenActionTypes) {
        for (var i = 0; i < forbiddenActionTypes.length; i++) {
            if (action.getJsonTypeName() === forbiddenActionTypes[i]) {
                return false;
            }
        }
    }

    return true;
}

function isElementAllowed(element: CardElement, forbiddenElementTypes: Array<string>) {
    if (!hostConfig.supportsInteractivity && element.isInteractive) {
        return false;
    }

    if (forbiddenElementTypes) {
        for (var i = 0; i < forbiddenElementTypes.length; i++) {
            if (element.getJsonTypeName() === forbiddenElementTypes[i]) {
                return false;
            }
        }
    }

    return true;
}

function getEffectiveSpacing(spacing: Enums.Spacing): number {
    switch (spacing) {
        case "small":
            return hostConfig.spacing.small;
        case "default":
            return hostConfig.spacing.default;
        case "medium":
            return hostConfig.spacing.medium;
        case "large":
            return hostConfig.spacing.large;
        case "extraLarge":
            return hostConfig.spacing.extraLarge;
        default:
            return 0;
    }
}

function getEffectivePadding(padding: Enums.Padding): number {
    switch (padding) {
        case "small":
            return hostConfig.padding.small;
        case "default":
            return hostConfig.padding.default;
        case "large":
            return hostConfig.padding.large;
        default:
            return 0;
    }
}

function paddingToSpacingDefinition(padding: HostConfig.IPaddingDefinition): HostConfig.ISpacingDefinition {
    return {
        top: getEffectivePadding(padding.top),
        right: getEffectivePadding(padding.right),
        bottom: getEffectivePadding(padding.bottom),
        left: getEffectivePadding(padding.left)
    }
}

function getColorPaletteDefinition(colorPalette: Enums.ColorPalette) {
    switch (colorPalette) {
        case "emphasis":
            return hostConfig.colorPalettes.emphasis;
        default:
            return hostConfig.colorPalettes.default;
    }
}

export interface IValidationError {
    error: Enums.ValidationError,
    message: string;
}

export abstract class CardElement {
    static createElementInstance(typeName: string): CardElement {
        var element = AdaptiveCard.elementTypeRegistry.createInstance(typeName);

        if (!element) {
            raiseParseError(
                {
                    error: Enums.ValidationError.UnknownElementType,
                    message: "Unknown element type: " + typeName
                });
        }

        return element;
    }

    private _internalPadding: HostConfig.IPaddingDefinition = null;
    private _parent: CardElement = null;

    protected internalGetNonZeroPadding(padding: HostConfig.ISpacingDefinition) {
        var actualPadding = paddingToSpacingDefinition(this.internalPadding);

        if (padding.top == 0) {
            padding.top = actualPadding.top;
        }

        if (padding.right == 0) {
            padding.right = actualPadding.right;
        }

        if (padding.bottom == 0) {
            padding.bottom = actualPadding.bottom;
        }

        if (padding.left == 0) {
            padding.left = actualPadding.left;
        }

        if (this.parent) {
            this.parent.internalGetNonZeroPadding(padding);
        }
    }

    protected adjustRenderedElementSize(renderedElement: HTMLElement) {
        if (this.height === "auto") {
            renderedElement.style.flex = "0 1 auto";
        }
        else {
            renderedElement.style.flex = "1 1 100%";
        }        
    }

    protected showBottomSpacer(requestingElement: CardElement) {
        if (this.parent) {
            this.parent.showBottomSpacer(this);
        }
    }

    protected hideBottomSpacer(requestingElement: CardElement) {
        if (this.parent) {
            this.parent.hideBottomSpacer(this);
        }
    }

    protected setParent(value: CardElement) {
        this._parent = value;
    }

    protected get useDefaultSizing(): boolean {
        return true;
    }

    protected abstract internalRender(): HTMLElement;

    protected get allowCustomPadding(): boolean {
        return true;
    }

    protected get defaultPadding(): HostConfig.IPaddingDefinition {
        return HostConfig.NoPadding;
    }

    protected get internalPadding(): HostConfig.IPaddingDefinition {
        return (this._internalPadding && this.allowCustomPadding) ? this._internalPadding : this.defaultPadding;
    }

    protected set internalPadding(value: HostConfig.IPaddingDefinition) {
        this._internalPadding = value;
    }

    speak: string;
    horizontalAlignment: Enums.HorizontalAlignment = "left";
    spacing: Enums.Spacing = "default";
    separator: boolean = false;
    height: "auto" | "stretch" = "auto";

    abstract getJsonTypeName(): string;
    abstract renderSpeech(): string;

    getNonZeroPadding(): HostConfig.ISpacingDefinition {
        var padding: HostConfig.ISpacingDefinition = { top: 0, right: 0, bottom: 0, left: 0 };

        this.internalGetNonZeroPadding(padding);

        return padding;
    }

    getForbiddenElementTypes(): Array<string> {
        return null;
    }

    getForbiddenActionTypes(): Array<any> {
        return null;
    }

    parse(json: any) {
        this.speak = json["speak"];
        this.horizontalAlignment = Utils.getValueOrDefault<Enums.HorizontalAlignment>(json["horizontalAlignment"], "left");
        this.spacing = Utils.getValueOrDefault<Enums.Spacing>(json["spacing"], "default");
        this.separator = json["separator"];

        var jsonHeight = json["height"];

        if (jsonHeight === "auto" || jsonHeight === "stretch") {
            this.height = jsonHeight;
        }
    }

    validate(): Array<IValidationError> {
        return [];
    }

    render(): HTMLElement {
        let renderedElement = this.internalRender();

        if (renderedElement) {
            renderedElement.style.boxSizing = "border-box";

            this.adjustRenderedElementSize(renderedElement);
        }

        return renderedElement;
    }

    isLastItem(item: CardElement): boolean {
        return this.parent ? this.parent.isLastItem(item) : true;
    }

    getRootElement(): CardElement {
        var rootElement: CardElement = this;

        while (rootElement.parent) {
            rootElement = rootElement.parent;
        }

        return rootElement;
    }

    getParentContainer(): Container {
        var currentElement: CardElement = this;

        while (currentElement) {
            if (currentElement instanceof Container) {
                return <Container>currentElement;
            }

            currentElement = currentElement.parent;
        }

        return null;
    }

    getAllInputs(): Array<Input> {
        return [];
    }

    get isInteractive(): boolean {
        return false;
    }

    get isStandalone(): boolean {
        return true;
    }

    get parent(): CardElement {
        return this._parent;
    }
}

export class TextBlock extends CardElement {
    size: Enums.TextSize = "normal";
    weight: Enums.TextWeight = "normal";
    color?: Enums.TextColor;
    text: string;
    isSubtle: boolean = false;
    wrap: boolean = false;
    maxLines: number;

    protected internalRender(): HTMLElement {
        if (!Utils.isNullOrEmpty(this.text)) {
            var element = document.createElement("div");

            if (hostConfig.fontFamily) {
                element.style.fontFamily = hostConfig.fontFamily;
            }

            switch (this.horizontalAlignment) {
                case "center":
                    element.style.textAlign = "center";
                    break;
                case "right":
                    element.style.textAlign = "right";
                    break;
                default:
                    element.style.textAlign = "left";
                    break;
            }

            var cssStyle = "text ";
            var fontSize: number;

            switch (this.size) {
                case "small":
                    fontSize = hostConfig.fontSizes.small;
                    break;
                case "medium":
                    fontSize = hostConfig.fontSizes.medium;
                    break;
                case "large":
                    fontSize = hostConfig.fontSizes.large;
                    break;
                case "extraLarge":
                    fontSize = hostConfig.fontSizes.extraLarge;
                    break;
                default:
                    fontSize = hostConfig.fontSizes.normal;
                    break;
            }

            // Looks like 1.33 is the magic number to compute line-height
            // from font size.
            var computedLineHeight = fontSize * 1.33;

            element.style.fontSize = fontSize + "px";
            element.style.lineHeight = computedLineHeight + "px";

            var parentContainer = this.getParentContainer();
            var colorPaletteDefinition = getColorPaletteDefinition(parentContainer ? parentContainer.colorPalette : "default");

            var actualTextColor = this.color ? this.color : hostConfig.textBlock.color;
            var colorDefinition: HostConfig.ITextColorDefinition;

            switch (actualTextColor) {
                case "dark":
                    colorDefinition = colorPaletteDefinition.fontColors.dark;
                    break;
                case "light":
                    colorDefinition = colorPaletteDefinition.fontColors.light;
                    break;
                case "accent":
                    colorDefinition = colorPaletteDefinition.fontColors.accent;
                    break;
                case "good":
                    colorDefinition = colorPaletteDefinition.fontColors.good;
                    break;
                case "warning":
                    colorDefinition = colorPaletteDefinition.fontColors.warning;
                    break;
                case "attention":
                    colorDefinition = colorPaletteDefinition.fontColors.attention;
                    break;
                default:
                    colorDefinition = colorPaletteDefinition.fontColors.dark;
                    break;
            }

            element.style.color = Utils.stringToCssColor(this.isSubtle ? colorDefinition.subtle : colorDefinition.normal);

            var fontWeight: number;

            switch (this.weight) {
                case "lighter":
                    fontWeight = hostConfig.fontWeights.lighter;
                    break;
                case "bolder":
                    fontWeight = hostConfig.fontWeights.bolder;
                    break;
                default:
                    fontWeight = hostConfig.fontWeights.normal;
                    break;
            }

            element.style.fontWeight = fontWeight.toString();

            var formattedText = TextFormatters.formatText(this.text);

            element.innerHTML = Utils.processMarkdown(formattedText);

            if (element.firstElementChild instanceof HTMLElement) {
                var firstElementChild = <HTMLElement>element.firstElementChild;
                firstElementChild.style.marginTop = "0px";
                firstElementChild.style.width = "100%";

                if (!this.wrap) {
                    firstElementChild.style.overflow = "hidden";
                    firstElementChild.style.textOverflow = "ellipsis";
                }
            }

            if (element.lastElementChild instanceof HTMLElement) {
                (<HTMLElement>element.lastElementChild).style.marginBottom = "0px";
            }

            var anchors = element.getElementsByTagName("a");

            for (var i = 0; i < anchors.length; i++) {
                anchors[i].target = "_blank";
            }

            if (this.wrap) {
                element.style.wordWrap = "break-word";

                if (this.maxLines > 0) {
                    element.style.maxHeight = (computedLineHeight * this.maxLines) + "px";
                    element.style.overflow = "hidden";
                }
            }
            else {
                element.style.whiteSpace = "nowrap";
            }

            return element;
        }
        else {
            return null;
        }
    }

    parse(json: any) {
        super.parse(json);

        this.text = json["text"];
        this.size = Utils.getValueOrDefault<Enums.TextSize>(json["size"], "normal");
        this.weight = Utils.getValueOrDefault<Enums.TextWeight>(json["weight"], "normal");
        this.color = Utils.getValueOrDefault<Enums.TextColor>(json["color"], hostConfig.textBlock.color);
        this.isSubtle = json["isSubtle"];
        this.wrap = json["wrap"] === undefined ? false : json["wrap"];
        this.maxLines = json["maxLines"];
    }

    getJsonTypeName(): string {
        return "TextBlock";
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';

        if (this.text)
            return '<s>' + this.text + '</s>\n';

        return null;
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
    protected get useDefaultSizing(): boolean {
        return false;
    }

    protected internalRender(): HTMLElement {
        let element: HTMLElement = null;

        if (this.facts.length > 0) {
            element = document.createElement("table");
            element.style.borderWidth = "0px";
            element.style.borderSpacing = "0px";
            element.style.borderStyle = "none";
            element.style.borderCollapse = "collapse";
            element.style.display = "block";
            element.style.overflow = "hidden";

            for (var i = 0; i < this.facts.length; i++) {
                var trElement = document.createElement("tr");

                if (i > 0) {
                    trElement.style.marginTop = hostConfig.factSet.spacing + "px";
                }

                var tdElement = document.createElement("td");
                tdElement.style.padding = "0";

                if (hostConfig.factSet.title.maxWidth) {
                    tdElement.style.maxWidth = hostConfig.factSet.title.maxWidth + "px";
                }

                tdElement.style.verticalAlign = "top";

                let textBlock = new TextBlock();
                textBlock.text = this.facts[i].name;
                textBlock.size = hostConfig.factSet.title.size;
                textBlock.color = hostConfig.factSet.title.color;
                textBlock.isSubtle = hostConfig.factSet.title.isSubtle;
                textBlock.weight = hostConfig.factSet.title.weight;
                textBlock.wrap = hostConfig.factSet.title.wrap;
                textBlock.spacing = "none";

                Utils.appendChild(tdElement, textBlock.render());
                Utils.appendChild(trElement, tdElement);

                tdElement = document.createElement("td");
                tdElement.style.padding = "0px 0px 0px 10px";
                tdElement.style.verticalAlign = "top";

                textBlock = new TextBlock();
                textBlock.text = this.facts[i].value;
                textBlock.size = hostConfig.factSet.value.size;
                textBlock.color = hostConfig.factSet.value.color;
                textBlock.isSubtle = hostConfig.factSet.value.isSubtle;
                textBlock.weight = hostConfig.factSet.value.weight;
                textBlock.wrap = hostConfig.factSet.value.wrap;
                textBlock.spacing = "none";

                Utils.appendChild(tdElement, textBlock.render());
                Utils.appendChild(trElement, tdElement);
                Utils.appendChild(element, trElement);
            }
        }

        return element;
    }

    facts: Array<Fact> = [];

    getJsonTypeName(): string {
        return "FactSet";
    }

    parse(json: any) {
        super.parse(json);

        if (json["facts"] != null) {
            var jsonFacts = json["facts"] as Array<any>;

            for (var i = 0; i < jsonFacts.length; i++) {
                let fact = new Fact();

                fact.name = jsonFacts[i]["title"];
                fact.value = jsonFacts[i]["value"];
                fact.speak = jsonFacts[i]["speak"];

                this.facts.push(fact);
            }
        }
    }

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
    protected get useDefaultSizing() {
        return false;
    }

    protected internalRender(): HTMLElement {
        var element: HTMLElement = null;

        if (!Utils.isNullOrEmpty(this.url)) {
            element = document.createElement("div");
            element.classList.add("ac-image");
            element.style.display = "flex";
            element.style.alignItems = "flex-start";

            if (this.selectAction != null) {
                element.classList.add("ac-selectable");
            }

            element.onclick = (e) => {
                if (this.selectAction) {
                    this.selectAction.execute();
                    e.cancelBubble = true;
                }
            }

            switch (this.horizontalAlignment) {
                case "center":
                    element.style.justifyContent = "center";
                    break;
                case "right":
                    element.style.justifyContent = "flex-end";
                    break;
                default:
                    element.style.justifyContent = "flex-start";
                    break;
            }

            var imageElement = document.createElement("img");
            imageElement.style.maxHeight = "100%";
            imageElement.style.minWidth = "0";

            switch (this.size) {
                case "stretch":
                    imageElement.style.width = "100%";
                    imageElement.style.maxHeight = "500px";
                    break;
                case "auto":
                    imageElement.style.maxWidth = "100%";
                    imageElement.style.maxHeight = "500px";
                    break;
                case "small":
                    imageElement.style.maxWidth = hostConfig.imageSizes.small + "px";
                    break;
                case "large":
                    imageElement.style.maxWidth = hostConfig.imageSizes.large + "px";
                    break;
                case "medium":
                    imageElement.style.maxWidth = hostConfig.imageSizes.medium + "px";
                    break;
            }

            if (this.style == "person") {
                imageElement.style.borderRadius = "50%";
                imageElement.style.backgroundPosition = "50% 50%";
                imageElement.style.backgroundRepeat = "no-repeat";
            }

            imageElement.src = this.url;

            element.appendChild(imageElement);
        }

        return element;
    }

    style: Enums.ImageStyle = "normal";
    url: string;
    size: Enums.Size = "auto";
    selectAction: ExternalAction;

    getJsonTypeName(): string {
        return "Image";
    }

    parse(json: any) {
        super.parse(json);

        this.url = json["url"];
        this.style = Utils.getValueOrDefault<Enums.ImageStyle>(json["style"], this.style);
        this.size = Utils.getValueOrDefault<Enums.Size>(json["size"], this.size);

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            this.selectAction = <ExternalAction>Action.createAction(selectActionJson);
            invokeSetParent(this.selectAction, this);
        }
    }

    renderSpeech(): string {
        if (this.speak != null) {
            return this.speak + '\n';
        }

        return null;
    }
}

export class ImageSet extends CardElement {
    private _images: Array<Image> = [];

    protected internalRender(): HTMLElement {
        let element: HTMLElement = null;

        if (this._images.length > 0) {
            element = document.createElement("div");
            element.style.display = "flex";
            element.style.flexWrap = "wrap";

            for (var i = 0; i < this._images.length; i++) {
                let renderedImage = this._images[i].render();

                renderedImage.style.display = "inline-flex";
                renderedImage.style.margin = "0px";
                renderedImage.style.marginRight = "10px";
                renderedImage.style.maxHeight = hostConfig.imageSet.maxImageHeight + "px";

                Utils.appendChild(element, renderedImage);
            }
        }

        return element;
    }

    imageSize: Enums.Size = "medium";

    getJsonTypeName(): string {
        return "ImageSet";
    }

    parse(json: any) {
        super.parse(json);

        this.imageSize = Utils.getValueOrDefault<Enums.Size>(json["imageSize"], "medium");

        if (json["images"] != null) {
            let jsonImages = json["images"] as Array<any>;

            for (let i = 0; i < jsonImages.length; i++) {
                var image = new Image();
                image.parse(jsonImages[i]);
                image.size = this.imageSize;

                this.addImage(image);
            }
        }
    }

    addImage(image: Image) {
        if (!image.parent) {
            this._images.push(image);

            invokeSetParent(image, this);
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

    validate(): Array<IValidationError> {
        if (!this.id) {
            return [{ error: Enums.ValidationError.PropertyCantBeNull, message: "All inputs must have a unique Id" }];
        }
        else {
            return [];
        }
    }

    parse(json: any) {
        super.parse(json);

        this.id = json["id"];
        this.defaultValue = json["value"];
    }

    renderSpeech(): string {
        if (this.speak != null) {
            return this.speak;
        }

        if (this.title) {
            return '<s>' + this.title + '</s>\n';
        }

        return null;
    }

    getAllInputs(): Array<Input> {
        return [this];
    }

    get isInteractive(): boolean {
        return true;
    }
}

export class TextInput extends Input {
    private _textareaElement: HTMLTextAreaElement;
    private _inputElement: HTMLInputElement;

    protected internalRender(): HTMLElement {
        if (this.isMultiline) {
            this._textareaElement = document.createElement("textarea");
            this._textareaElement.className = "ac-input ac-textInput ac-multiline";
            this._textareaElement.style.width = "100%";

            if (!Utils.isNullOrEmpty(this.placeholder)) {
                this._textareaElement.placeholder = this.placeholder;
            }

            if (!Utils.isNullOrEmpty(this.defaultValue)) {
                this._textareaElement.value = this.defaultValue;
            }

            if (this.maxLength > 0) {
                this._textareaElement.maxLength = this.maxLength;
            }

            return this._textareaElement;
        }
        else {
            this._inputElement = document.createElement("input");
            this._inputElement.type = "text";
            this._inputElement.className = "ac-input ac-textInput";
            this._inputElement.style.width = "100%";

            if (!Utils.isNullOrEmpty(this.placeholder)) {
                this._inputElement.placeholder = this.placeholder;
            }

            if (!Utils.isNullOrEmpty(this.defaultValue)) {
                this._inputElement.value = this.defaultValue;
            }

            if (this.maxLength > 0) {
                this._inputElement.maxLength = this.maxLength;
            }

            return this._inputElement;
        }
    }

    maxLength: number;
    isMultiline: boolean;
    placeholder: string;

    getJsonTypeName(): string {
        return "Input.Text";
    }

    parse(json: any) {
        super.parse(json);

        this.maxLength = json["maxLength"];
        this.isMultiline = json["isMultiline"];
        this.placeholder = json["placeholder"];
    }

    get value(): string {
        if (this.isMultiline) {
            return this._textareaElement ? this._textareaElement.value : null;
        }
        else {
            return this._inputElement ? this._inputElement.value : null;
        }
    }
}

export class ToggleInput extends Input {
    private _checkboxInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement {
        var element = document.createElement("div");
        element.className = "ac-input";
        element.style.width = "100%";

        this._checkboxInputElement = document.createElement("input");
        this._checkboxInputElement.type = "checkbox";
        this._checkboxInputElement.style.display = "inline-block";
        this._checkboxInputElement.style.verticalAlign = "middle";
        this._checkboxInputElement.style.margin = "0";

        if (this.defaultValue == this.valueOn) {
            this._checkboxInputElement.checked = true;
        }

        var label = new TextBlock();
        label.text = this.title;

        var labelElement = label.render();
        labelElement.style.display = "inline-block";
        labelElement.style.marginLeft = "6px";
        labelElement.style.verticalAlign = "middle";

        var compoundInput = document.createElement("div");

        Utils.appendChild(element, this._checkboxInputElement);
        Utils.appendChild(element, labelElement);

        return element;
    }

    title: string;
    valueOn: string;
    valueOff: string;

    getJsonTypeName(): string {
        return "Input.Toggle";
    }

    parse(json: any) {
        super.parse(json);

        this.title = json["title"];
        this.valueOn = json["valueOn"];
        this.valueOff = json["valueOff"];
    }

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
    private _selectElement: HTMLSelectElement;
    private _toggleInputs: Array<HTMLInputElement>;

    protected internalRender(): HTMLElement {
        if (!this.isMultiSelect) {
            if (this.isCompact) {
                // Render as a combo box
                this._selectElement = document.createElement("select");
                this._selectElement.className = "ac-input ac-multichoiceInput";
                this._selectElement.style.width = "100%";

                var option = document.createElement("option");
                option.selected = true;
                option.disabled = true;
                option.hidden = true;

                if (this.placeholder) {
                    option.text = this.placeholder;
                }

                Utils.appendChild(this._selectElement, option);

                for (var i = 0; i < this.choices.length; i++) {
                    var option = document.createElement("option");
                    option.value = this.choices[i].value;
                    option.text = this.choices[i].title;

                    if (this.choices[i].value == this.defaultValue) {
                        option.selected = true;
                    }

                    Utils.appendChild(this._selectElement, option);
                }

                return this._selectElement;
            }
            else {
                // Render as a series of radio buttons
                var element = document.createElement("div");
                element.className = "ac-input";
                element.style.width = "100%";

                this._toggleInputs = [];

                for (var i = 0; i < this.choices.length; i++) {
                    var radioInput = document.createElement("input");
                    radioInput.type = "radio";
                    radioInput.style.margin = "0";
                    radioInput.style.display = "inline-block";
                    radioInput.style.verticalAlign = "middle";
                    radioInput.name = this.id;
                    radioInput.value = this.choices[i].value;

                    if (this.choices[i].value == this.defaultValue) {
                        radioInput.checked = true;
                    }

                    this._toggleInputs.push(radioInput);

                    var label = new TextBlock();
                    label.text = this.choices[i].title;

                    var labelElement = label.render();
                    labelElement.style.display = "inline-block";
                    labelElement.style.marginLeft = "6px";
                    labelElement.style.verticalAlign = "middle";

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
            var defaultValues = this.defaultValue ? this.defaultValue.split(",") : null;

            var element = document.createElement("div");
            element.className = "ac-input";
            element.style.width = "100%";

            this._toggleInputs = [];

            for (var i = 0; i < this.choices.length; i++) {
                var checkboxInput = document.createElement("input");
                checkboxInput.type = "checkbox";
                checkboxInput.style.margin = "0";
                checkboxInput.style.display = "inline-block";
                checkboxInput.style.verticalAlign = "middle";
                checkboxInput.value = this.choices[i].value;

                if (defaultValues) {
                    if (defaultValues.indexOf(this.choices[i].value) >= 0) {
                        checkboxInput.checked = true;
                    }
                }

                this._toggleInputs.push(checkboxInput);

                var label = new TextBlock();
                label.text = this.choices[i].title;

                var labelElement = label.render();
                labelElement.style.display = "inline-block";
                labelElement.style.marginLeft = "6px";
                labelElement.style.verticalAlign = "middle";

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

    getJsonTypeName(): string {
        return "Input.ChoiceSet";
    }

    validate(): Array<IValidationError> {
        var result: Array<IValidationError> = [];

        if (this.choices.length == 0) {
            result = [{ error: Enums.ValidationError.CollectionCantBeEmpty, message: "An Input.ChoiceSet must have at least one choice defined." }];
        }

        for (var i = 0; i < this.choices.length; i++) {
            if (!this.choices[i].title || !this.choices[i].value) {
                result = result.concat([{ error: Enums.ValidationError.PropertyCantBeNull, message: "All choices in an Input.ChoiceSet must have their title and value properties set." }])
                break;
            }
        }

        return result;
    }

    parse(json: any) {
        super.parse(json);

        this.isCompact = !(json["style"] === "expanded");
        this.isMultiSelect = json["isMultiSelect"];
        this.placeholder = json["placeholder"];

        if (json["choices"] != undefined) {
            var choiceArray = json["choices"] as Array<any>;

            for (var i = 0; i < choiceArray.length; i++) {
                var choice = new Choice();

                choice.title = choiceArray[i]["title"];
                choice.value = choiceArray[i]["value"];

                this.choices.push(choice);
            }
        }
    }

    get value(): string {
        if (!this.isMultiSelect) {
            if (this.isCompact) {
                return this._selectElement ? this._selectElement.value : null;
            }
            else {
                if (!this._toggleInputs || this._toggleInputs.length == 0) {
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
            if (!this._toggleInputs || this._toggleInputs.length == 0) {
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
    private _numberInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement {
        this._numberInputElement = document.createElement("input");
        this._numberInputElement.type = "number";
        this._numberInputElement.className = "ac-input ac-numberInput";
        this._numberInputElement.min = this.min;
        this._numberInputElement.max = this.max;
        this._numberInputElement.style.width = "100%";

        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._numberInputElement.value = this.defaultValue;
        }

        return this._numberInputElement;
    }

    min: string;
    max: string;

    getJsonTypeName(): string {
        return "Input.Number";
    }

    parse(json: any) {
        super.parse(json);

        this.min = json["min"];
        this.max = json["max"];
    }

    get value(): string {
        return this._numberInputElement ? this._numberInputElement.value : null;
    }
}

export class DateInput extends Input {
    private _dateInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement {
        this._dateInputElement = document.createElement("input");
        this._dateInputElement.type = "date";
        this._dateInputElement.className = "ac-input ac-dateInput";
        this._dateInputElement.style.width = "100%";

        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._dateInputElement.value = this.defaultValue;
        }

        return this._dateInputElement;
    }

    getJsonTypeName(): string {
        return "Input.Date";
    }

    get value(): string {
        return this._dateInputElement ? this._dateInputElement.value : null;
    }
}

export class TimeInput extends Input {
    private _timeInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement {
        this._timeInputElement = document.createElement("input");
        this._timeInputElement.type = "time";
        this._timeInputElement.className = "ac-input ac-timeInput";
        this._timeInputElement.style.width = "100%";

        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._timeInputElement.value = this.defaultValue;
        }

        return this._timeInputElement;
    }

    getJsonTypeName(): string {
        return "Input.Time";
    }

    get value(): string {
        return this._timeInputElement ? this._timeInputElement.value : null;
    }
}

enum ActionButtonState {
    Normal,
    Expanded,
    Subdued
}

class ActionButton {
    private _action: Action;
    private _style: Enums.ActionStyle = "button";
    private _element: HTMLElement = null;
    private _state: ActionButtonState = ActionButtonState.Normal;
    private _text: string;

    private click() {
        if (this.onClick != null) {
            this.onClick(this);
        }
    }

    private updateCssStyle() {
        this._element.className = this._style == "link" ? "ac-linkButton" : "ac-pushButton";

        if (this._action instanceof ShowCardAction) {
            this._element.classList.add("expandable");
        }

        switch (this._state) {
            case ActionButtonState.Expanded:
                this._element.classList.add("expanded");
                break;
            case ActionButtonState.Subdued:
                this._element.classList.add("subdued");
                break;
        }
    }

    constructor(action: Action, style: Enums.ActionStyle) {
        this._action = action;
        this._style = style;

        this._element = document.createElement("button");
        this._element.style.overflow = "hidden";
        this._element.style.whiteSpace = "nowrap";
        this._element.style.textOverflow = "ellipsis";
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
    static createAction(json: any): Action {
        var actionType = json["type"];

        var result = AdaptiveCard.actionTypeRegistry.createInstance(actionType);

        if (result) {
            result.parse(json);
        }
        else {
            raiseParseError(
                {
                    error: Enums.ValidationError.UnknownActionType,
                    message: "Unknown action type: " + actionType
                });
        }

        return result;
    }

    private _parent: CardElement = null;

    protected setParent(value: CardElement) {
        this._parent = value;
    }

    abstract getJsonTypeName(): string;
    abstract execute();

    validate(): Array<IValidationError> {
        return [];
    }

    prepare(inputs: Array<Input>) {
        // Do nothing in base implementation
    };

    parse(json: any) {
        this.title = json["title"];
    }

    getAllInputs(): Array<Input> {
        return [];
    }

    title: string;

    get parent(): CardElement {
        return this._parent;
    }
}

export abstract class ExternalAction extends Action {
    execute() {
        raiseExecuteActionEvent(this);
    }
}

export class SubmitAction extends ExternalAction {
    private _isPrepared: boolean = false;
    private _originalData: Object;
    private _processedData: Object;

    getJsonTypeName(): string {
        return "Action.Submit";
    }

    prepare(inputs: Array<Input>) {
        if (this._originalData) {
            this._processedData = JSON.parse(JSON.stringify(this._originalData));
        }
        else {
            this._processedData = {};
        }

        for (var i = 0; i < inputs.length; i++) {
            var inputValue = inputs[i].value;

            if (inputValue != null) {
                this._processedData[inputs[i].id] = inputs[i].value;
            }
        }

        this._isPrepared = true;
    }

    parse(json: any) {
        super.parse(json);

        this.data = json["data"];
    }

    get data(): Object {
        return this._isPrepared ? this._processedData : this._originalData;
    }

    set data(value: Object) {
        this._originalData = value;
        this._isPrepared = false;
    }
}

export class OpenUrlAction extends ExternalAction {
    url: string;

    getJsonTypeName(): string {
        return "Action.OpenUrl";
    }

    validate(): Array<IValidationError> {
        if (!this.url) {
            return [{ error: Enums.ValidationError.PropertyCantBeNull, message: "An Action.OpenUrl must have its url property set." }];
        }
        else {
            return [];
        }
    }

    parse(json: any) {
        super.parse(json);

        this.url = json["url"];
    }
}

export class HttpHeader {
    private _value = new Utils.StringWithSubstitutions();

    name: string;

    prepare(inputs: Array<Input>) {
        this._value.substituteInputValues(inputs);
    }

    get value(): string {
        return this._value.get();
    }

    set value(newValue: string) {
        this._value.set(newValue);
    }
}

export class HttpAction extends ExternalAction {
    private _url = new Utils.StringWithSubstitutions();
    private _body = new Utils.StringWithSubstitutions();
    private _headers: Array<HttpHeader> = [];

    method: string;

    getJsonTypeName(): string {
        return "Action.Http";
    }

    validate(): Array<IValidationError> {
        var result: Array<IValidationError> = [];

        if (!this.url) {
            result = [{ error: Enums.ValidationError.PropertyCantBeNull, message: "An Action.Http must have its url property set." }];
        }

        if (this.headers.length > 0) {
            for (var i = 0; i < this.headers.length; i++) {
                if (!this.headers[i].name || !this.headers[i].value) {
                    result = result.concat([{ error: Enums.ValidationError.PropertyCantBeNull, message: "All headers of an Action.Http must have their name and value properties set." }]);
                    break;
                }
            }
        }

        return result;
    }

    prepare(inputs: Array<Input>) {
        this._url.substituteInputValues(inputs);
        this._body.substituteInputValues(inputs);

        for (var i = 0; i < this._headers.length; i++) {
            this._headers[i].prepare(inputs);
        }
    };

    parse(json: any) {
        super.parse(json);

        this.url = json["url"];
        this.method = json["method"];
        this.body = json["body"];

        if (json["headers"] != null) {
            var jsonHeaders = json["headers"] as Array<any>;

            for (var i = 0; i < jsonHeaders.length; i++) {
                let httpHeader = new HttpHeader();

                httpHeader.name = jsonHeaders[i]["name"];
                httpHeader.value = jsonHeaders[i]["value"];

                this.headers.push(httpHeader);
            }
        }
    }

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

export class ShowCardAction extends Action {
    protected setParent(value: CardElement) {
        super.setParent(value);

        invokeSetParent(this.card, value);
    }

    readonly card: AdaptiveCard = new InlineAdaptiveCard();

    title: string;

    execute() {
        raiseShowPopupCardEvent(this);
    }

    getJsonTypeName(): string {
        return "Action.ShowCard";
    }

    validate(): Array<IValidationError> {
        return this.card.validate();
    }

    parse(json: any) {
        super.parse(json);

        this.card.parse(json["card"]);
    }

    getAllInputs(): Array<Input> {
        return this.card.getAllInputs();
    }
}

class ActionCollection {
    private _owner: CardElement;
    private _actionButtons: Array<ActionButton> = [];
    private _actionCardContainer: HTMLDivElement;
    private _expandedAction: ShowCardAction = null;
    private _renderedActionCount: number = 0;

    private hideActionCardPane() {
        this._actionCardContainer.innerHTML = '';
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";

        if (this.onHideActionCardPane) {
            this.onHideActionCardPane();
        }

        if (this._expandedAction) {
            raiseInlineCardExpandedEvent(this._expandedAction, false);
        }

        this._expandedAction = null;
    }

    private showActionCardPane(action: ShowCardAction) {
        if (this.onShowActionCardPane) {
            this.onShowActionCardPane(action);
        }

        var renderedCard = action.card.render();

        this._actionCardContainer.innerHTML = '';
        this._actionCardContainer.style.marginTop = this._renderedActionCount > 0 ? hostConfig.actions.showCard.inlineTopMargin + "px" : "0px";

        if (hostConfig.actions.showCard.actionMode == "inlineEdgeToEdge") {
            var padding = this._owner.getNonZeroPadding();

            renderedCard.style.paddingLeft = padding.left + "px";
            renderedCard.style.paddingRight = padding.right + "px";
            
            renderedCard.style.marginLeft = "-" + padding.left + "px";
            renderedCard.style.marginRight = "-" + padding.right + "px";
        }

        Utils.appendChild(this._actionCardContainer, renderedCard);

        raiseInlineCardExpandedEvent(action, true);

        this._expandedAction = action;
    }

    private actionClicked(actionButton: ActionButton) {
        if (!(actionButton.action instanceof ShowCardAction)) {
            for (var i = 0; i < this._actionButtons.length; i++) {
                this._actionButtons[i].state = ActionButtonState.Normal;
            }

            this.hideActionCardPane();

            actionButton.action.execute();
        }
        else {
            if (hostConfig.actions.showCard.actionMode == "popup") {
                actionButton.action.execute();
            }
            else if (actionButton.action === this._expandedAction) {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    this._actionButtons[i].state = ActionButtonState.Normal;
                }

                this.hideActionCardPane();
            }
            else {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    if (this._actionButtons[i] !== actionButton) {
                        this._actionButtons[i].state = ActionButtonState.Subdued;
                    }
                }

                actionButton.state = ActionButtonState.Expanded;

                this.showActionCardPane(actionButton.action);
            }
        }
    }

    items: Array<Action> = [];
    actionStyle: Enums.ActionStyle = "button";
    onHideActionCardPane: () => void = null;
    onShowActionCardPane: (action: ShowCardAction) => void = null;

    constructor(owner: CardElement) {
        this._owner = owner;
    }

    validate(): Array<IValidationError> {
        var result: Array<IValidationError> = [];

        if (hostConfig.actions.maxActions && this.items.length > hostConfig.actions.maxActions) {
            result.push(
                {
                    error: Enums.ValidationError.TooManyActions,
                    message: "A maximum of " + hostConfig.actions.maxActions + " actions are allowed."
                });
        }

        if (this.items.length > 0 && !hostConfig.supportsInteractivity) {
            result.push(
                {
                    error: Enums.ValidationError.InteractivityNotAllowed,
                    message: "Interactivity is not allowed."
                });
        }

        for (var i = 0; i < this.items.length; i++) {
            if (!isActionAllowed(this.items[i], this._owner.getForbiddenActionTypes())) {
                result.push(
                    {
                        error: Enums.ValidationError.ActionTypeNotAllowed,
                        message: "Actions of type " + this.items[i].getJsonTypeName() + " are not allowe."
                    });
            }

        }

        for (var i = 0; i < this.items.length; i++) {
            result = result.concat(this.items[i].validate());
        }

        return result;
    }

    render(): HTMLElement {
        if (!hostConfig.supportsInteractivity) {
            return null;
        }

        var element = document.createElement("div");

        this._actionCardContainer = document.createElement("div");

        this._renderedActionCount = 0;

        var maxActions = hostConfig.actions.maxActions ? Math.min(hostConfig.actions.maxActions, this.items.length) : this.items.length;

        var forbiddenActionTypes = this._owner.getForbiddenActionTypes();

        if (hostConfig.actions.preExpandSingleShowCardAction && maxActions == 1 && this.items[0] instanceof ShowCardAction && isActionAllowed(this.items[i], forbiddenActionTypes)) {
            this.showActionCardPane(<ShowCardAction>this.items[0]);
            this._renderedActionCount = 1;
        }
        else {
            var buttonStrip = document.createElement("div");
            buttonStrip.style.display = "flex";

            if (hostConfig.actions.actionsOrientation == "horizontal") {
                buttonStrip.style.flexDirection = "row";

                switch (hostConfig.actions.actionAlignment) {
                    case "center":
                        buttonStrip.style.justifyContent = "center";
                        break;
                    case "right":
                        buttonStrip.style.justifyContent = "flex-end";
                        break;
                    default:
                        buttonStrip.style.justifyContent = "flex-start";
                        break;
                }
            }
            else {
                buttonStrip.style.flexDirection = "column";

                switch (hostConfig.actions.actionAlignment) {
                    case "center":
                        buttonStrip.style.alignItems = "center";
                        break;
                    case "right":
                        buttonStrip.style.alignItems = "flex-end";
                        break;
                    case "stretch":
                        buttonStrip.style.alignItems = "stretch";
                        break;
                    default:
                        buttonStrip.style.alignItems = "flex-start";
                        break;
                }
            }

            for (var i = 0; i < maxActions; i++) {
                if (isActionAllowed(this.items[i], forbiddenActionTypes)) {
                    var actionButton = new ActionButton(this.items[i], this.actionStyle);
                    actionButton.element.style.overflow = "hidden";
                    actionButton.element.style.overflow = "table-cell";
                    actionButton.element.style.flex = hostConfig.actions.actionAlignment == "stretch" ? "0 1 100%" : "0 1 auto";
                    actionButton.text = this.items[i].title;
                    actionButton.onClick = (ab) => { this.actionClicked(ab); };

                    this._actionButtons.push(actionButton);

                    buttonStrip.appendChild(actionButton.element);

                    if (i < this.items.length - 1 && hostConfig.actions.buttonSpacing > 0) {
                        var spacer = document.createElement("div");

                        if (hostConfig.actions.actionsOrientation == "horizontal") {
                            spacer.style.flex = "0 0 auto";
                            spacer.style.width = hostConfig.actions.buttonSpacing + "px";
                        }
                        else {
                            spacer.style.height = hostConfig.actions.buttonSpacing + "px";
                        }

                        Utils.appendChild(buttonStrip, spacer);
                    }

                    this._renderedActionCount++;
                }
            }

            var buttonStripContainer = document.createElement("div");
            buttonStripContainer.style.overflow = "hidden";
            buttonStripContainer.appendChild(buttonStrip);

            Utils.appendChild(element, buttonStripContainer);
        }

        Utils.appendChild(element, this._actionCardContainer);

        return this._renderedActionCount > 0 ? element : null;
    }

    addAction(action: Action) {
        if (!action.parent) {
            this.items.push(action);

            invokeSetParent(action, this._owner);
        }
        else {
            throw new Error("The action already belongs to another element.")
        }
    }

    clear() {
        this.items = [];
    }

    getAllInputs(): Array<Input> {
        var result: Array<Input> = [];

        for (var i = 0; i < this.items.length; i++) {
            var action = this.items[i];

            result = result.concat(action.getAllInputs());
        }

        return result;
    }
}

export class ActionSet extends CardElement {
    private _actionCollection: ActionCollection;

    protected internalRender(): HTMLElement {
        this._actionCollection.actionStyle = this.actionStyle;
        
        return this._actionCollection.render();
    }

    actionStyle: Enums.ActionStyle = "button";

    constructor() {
        super();

        this._actionCollection = new ActionCollection(this);
        this._actionCollection.onHideActionCardPane = () => { this.showBottomSpacer(this); };
        this._actionCollection.onShowActionCardPane = (action: ShowCardAction) => { this.hideBottomSpacer(this); };
    }

    getJsonTypeName(): string {
        return "ActionSet";
    }

    validate(): Array<IValidationError> {
        return this._actionCollection.validate();
    }

    parse(json: any, itemsCollectionPropertyName: string = "items") {
        super.parse(json);

        this.actionStyle = Utils.getValueOrDefault<Enums.ActionStyle>(json["actionStyle"], "button");

        if (json["actions"] != undefined) {
            var jsonActions = json["actions"] as Array<any>;

            for (var i = 0; i < jsonActions.length; i++) {
                this.addAction(Action.createAction(jsonActions[i]));
            }
        }
    }

    addAction(action: Action) {
        if (action != null) {
            this._actionCollection.addAction(action);
        }
    }

    getAllInputs(): Array<Input> {
        return this._actionCollection.getAllInputs();
    }

    renderSpeech(): string {
        // TODO: What's the right thing to do here?
        return "";
    }

    get isInteractive(): boolean {
        return true;
    }
}

export class BackgroundImage {
    url: string;
    mode: Enums.BackgroundImageMode = "stretch";
    horizontalAlignment: Enums.HorizontalAlignment = "left";
    verticalAlignment: Enums.VerticalAlignment = "top";

    parse(json: any) {
        this.url = json["url"];
        this.mode = Utils.getValueOrDefault<Enums.BackgroundImageMode>(json["mode"], this.mode);
        this.horizontalAlignment = Utils.getValueOrDefault<Enums.HorizontalAlignment>(json["horizontalAlignment"], this.horizontalAlignment);
        this.verticalAlignment = Utils.getValueOrDefault<Enums.VerticalAlignment>(json["verticalAlignment"], this.verticalAlignment);
    }

    apply(element: HTMLElement) {
        if (this.url) {
            element.style.backgroundImage = "url('" + this.url + "')";

            switch (this.mode) {
                case "repeat":
                    element.style.backgroundRepeat = "repeat";
                    break;
                case "repeatHorizontally":
                    element.style.backgroundRepeat = "repeat-x";
                    break;
                case "repeatVertically":
                    element.style.backgroundRepeat = "repeat-y";
                    break;
                case "stretch":
                default:
                    element.style.backgroundRepeat = "no-repeat";
                    element.style.backgroundSize = "cover";
                    break;
            }

            switch (this.horizontalAlignment) {
                case "center":
                    element.style.backgroundPositionX = "center";
                    break;
                case "right":
                    element.style.backgroundPositionX = "right";
                    break;
            }

            switch (this.verticalAlignment) {
                case "center":
                    element.style.backgroundPositionY = "center";
                    break;
                case "bottom":
                    element.style.backgroundPositionY = "bottom";
                    break;
            }
        }
    }
}

export class Container extends CardElement {
    private _items: Array<CardElement> = [];
    private _colorPalette?: Enums.ColorPalette = null;

    protected showBottomSpacer(requestingElement: CardElement) {
        if ((!requestingElement || this.isLastItem(requestingElement)) && hostConfig.actions.showCard.actionMode == "inlineEdgeToEdge") {
            this._element.style.paddingBottom = paddingToSpacingDefinition(this.internalPadding).bottom + "px";

            super.showBottomSpacer(this);
        }
    }

    protected hideBottomSpacer(requestingElement: CardElement) {
        if ((!requestingElement || this.isLastItem(requestingElement)) && hostConfig.actions.showCard.actionMode == "inlineEdgeToEdge") {
            this._element.style.paddingBottom = "0px";

            super.hideBottomSpacer(this);
        }
    }

    protected internalRender(): HTMLElement {
        this._element = document.createElement("div");
        this._element.className = "ac-container";
        this._element.style.display = "flex";
        this._element.style.flexDirection = "column";

        if (this.backgroundImage) {
            this.backgroundImage.apply(this._element);
        }

        var colorPaletteDefinition = getColorPaletteDefinition(this.colorPalette);

        if (!Utils.isNullOrEmpty(colorPaletteDefinition.backgroundColor)) {
            this._element.style.backgroundColor = Utils.stringToCssColor(colorPaletteDefinition.backgroundColor);
        }

        if (this.selectAction) {
            this._element.classList.add("ac-selectable");
        }

        var effectivePadding = paddingToSpacingDefinition(this.internalPadding);

        this._element.style.paddingTop = effectivePadding.top + "px";
        this._element.style.paddingRight = effectivePadding.right + "px";
        this._element.style.paddingBottom = effectivePadding.bottom + "px";
        this._element.style.paddingLeft = effectivePadding.left + "px";

        this._element.onclick = (e) => {
            if (this.selectAction != null) {
                this.selectAction.execute();
                e.cancelBubble = true;
            }
        }

        if (this._items.length > 0) {
            var renderedElementCount: number = 0;

            for (var i = 0; i < this._items.length; i++) {
                var renderedElement = isElementAllowed(this._items[i], this.getForbiddenElementTypes()) ? this._items[i].render() : null;

                if (renderedElement) {
                    if (renderedElementCount > 0) {
                        var separator = Utils.renderSeparation(
                            {
                                spacing: getEffectiveSpacing(this._items[i].spacing),
                                lineThickness: this._items[i].separator ? hostConfig.separator.lineThickness : null,
                                lineColor: this._items[i].separator ? hostConfig.separator.lineColor : null
                            },
                            "vertical");

                        if (separator) {
                            separator.style.flex = "0 0 auto";
                        }

                        Utils.appendChild(this._element, separator);
                    }

                    Utils.appendChild(this._element, renderedElement);

                    renderedElementCount++;
                }
            }
        }

        return this._element;
    }

    protected get defaultColorPalette(): Enums.ColorPalette {
        return "default";
    }

    protected get allowCustomColorPalette(): boolean {
        return true;
    }

    protected _element: HTMLDivElement;

    selectAction: ExternalAction;
    backgroundImage: BackgroundImage;

    get colorPalette(): Enums.ColorPalette {
        if (this.allowCustomColorPalette) {
            return this._colorPalette ? this._colorPalette : this.defaultColorPalette;
        }
        else {
            return this.defaultColorPalette;
        }
    }

    get padding(): HostConfig.IPaddingDefinition {
        return this.internalPadding;
    }

    set padding(value: HostConfig.IPaddingDefinition) {
        this.internalPadding = value;
    }

    getJsonTypeName(): string {
        return "Container";
    }

    isLastItem(item: CardElement): boolean {
        return this._items.indexOf(item) == (this._items.length - 1);
    }

    validate(): Array<IValidationError> {
        var result: Array<IValidationError> = [];

        for (var i = 0; i < this._items.length; i++) {
            if (!hostConfig.supportsInteractivity && this._items[i].isInteractive) {
                result.push(
                    {
                        error: Enums.ValidationError.InteractivityNotAllowed,
                        message: "Interactivity is not allowed."
                    });
            }

            if (!isElementAllowed(this._items[i], this.getForbiddenElementTypes())) {
                result.push(
                    {
                        error: Enums.ValidationError.InteractivityNotAllowed,
                        message: "Elements of type " + this._items[i].getJsonTypeName() + " are not allowed in this container."
                    });
            }

            result = result.concat(this._items[i].validate());
        }

        return result;
    }

    parse(json: any, itemsCollectionPropertyName: string = "items") {
        super.parse(json);

        if (json["backgroundImage"]) {
            this.backgroundImage = new BackgroundImage();
            this.backgroundImage.parse(json["backgroundImage"]);
        }

        this._colorPalette = Utils.getValueOrDefault<Enums.ColorPalette>(json["colorPalette"], null);

        var jsonPadding = json["padding"];

        if (jsonPadding) {
            if (typeof jsonPadding === "string") {
                var spacing = Utils.getValueOrDefault<Enums.Padding>(jsonPadding, "none");

                this.padding = {
                    top: spacing,
                    right: spacing,
                    bottom: spacing,
                    left: spacing
                };
            }
            else {
                this.padding = {
                    top: Utils.getValueOrDefault<Enums.Padding>(jsonPadding["top"], "none"),
                    right: Utils.getValueOrDefault<Enums.Padding>(jsonPadding["right"], "none"),
                    bottom: Utils.getValueOrDefault<Enums.Padding>(jsonPadding["bottom"], "none"),
                    left: Utils.getValueOrDefault<Enums.Padding>(jsonPadding["left"], "none")
                };
            }
        }

        if (json[itemsCollectionPropertyName] != null) {
            var items = json[itemsCollectionPropertyName] as Array<any>;

            for (var i = 0; i < items.length; i++) {
                var elementType = items[i]["type"];

                var element = CardElement.createElementInstance(elementType);

                this.addItem(element);

                element.parse(items[i]);
            }
        }

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            this.selectAction = <ExternalAction>Action.createAction(selectActionJson);
            invokeSetParent(this.selectAction, this);
        }
    }

    addItem(item: CardElement) {
        if (!item.parent) {
            if (item.isStandalone) {
                this._items.push(item);

                invokeSetParent(item, this);
            }
            else {
                throw new Error("Elements of type " + item.getJsonTypeName() + " cannot be used as standalone elements.");
            }
        }
        else {
            throw new Error("The element already belongs to another container.")
        }
    }

    clear() {
        this._items = [];
    }

    getAllInputs(): Array<Input> {
        var result: Array<Input> = [];

        for (var i = 0; i < this._items.length; i++) {
            var item: CardElement = this._items[i];

            result = result.concat(item.getAllInputs());
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

export class Column extends Container {
    private _computedWeight: number = 0;

    protected adjustRenderedElementSize(renderedElement: HTMLElement) {
        renderedElement.style.minWidth = "0";

        if (typeof this.width === "number") {
            renderedElement.style.flex = "1 1 " + (this._computedWeight > 0 ? this._computedWeight : this.width) + "%";
        }
        else if (this.width === "auto") {
            renderedElement.style.flex = "0 1 auto";
        }
        else {
            renderedElement.style.flex = "1 1 auto";
        }
    }

    protected internalGetNonZeroPadding(padding: HostConfig.ISpacingDefinition) {
        // Action.ShowCard should not bleed outside a Column's boundaries
        // So we stop retrieving paddings here.
    }

    width: number | "auto" | "stretch" = "auto";

    getJsonTypeName(): string {
        return "Column";
    }

    parse(json: any) {
        super.parse(json);

        var jsonWidth = json["width"];
        var invalidWidth = false;

        if (typeof jsonWidth === "number") {
            if (jsonWidth <= 0) {
                invalidWidth = true;
            }
        }
        else if (typeof jsonWidth === "string") {
            if (jsonWidth != "auto" && jsonWidth != "stretch") {
                var sizeAsNumber = parseInt(jsonWidth);

                if (!isNaN(sizeAsNumber)) {
                    jsonWidth = sizeAsNumber;
                }
                else {
                    invalidWidth = true;
                }
            }
        }
        else if (jsonWidth) {
            invalidWidth = true;
        }

        if (invalidWidth) {
            raiseParseError(
                {
                    error: Enums.ValidationError.InvalidPropertyValue,
                    message: "Invalid column width: " + jsonWidth
                });
        }
        else {
            this.width = jsonWidth;
        }
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class ColumnSet extends CardElement {
    private _columns: Array<Column> = [];

    protected internalRender(): HTMLElement {
        if (this._columns.length > 0) {
            var element = document.createElement("div");
            element.style.display = "flex";
            element.style.overflow = "hidden";

            switch (this.horizontalAlignment) {
                case "center":
                    element.style.justifyContent = "center";
                    break;
                case "right":
                    element.style.justifyContent = "flex-end";
                    break;
                default:
                    element.style.justifyContent = "flex-start";
                    break;
            }

            var totalWeight: number = 0;

            for (let i = 0; i < this._columns.length; i++) {
                if (typeof this._columns[i].width === "number") {
                    totalWeight += <number>this._columns[i].width;
                }
            }

            var renderedColumnCount: number = 0;

            for (let i = 0; i < this._columns.length; i++) {
                if (typeof this._columns[i].width === "number" && totalWeight > 0) {
                    var computedWeight = 100 / totalWeight * <number>this._columns[i].width;

                    // Best way to emulate "internal" access I know of
                    this._columns[i]["_computedWeight"] = computedWeight;
                }

                var renderedColumn = this._columns[i].render();

                if (renderedColumn) {
                    Utils.appendChild(element, renderedColumn);

                    if (this._columns.length > 1 && i < this._columns.length - 1) {
                        var separator = Utils.renderSeparation(
                            {
                                spacing: getEffectiveSpacing(this._columns[i + 1].spacing),
                                lineThickness: this._columns[i + 1].separator ? hostConfig.separator.lineThickness : null,
                                lineColor: this._columns[i + 1].separator ? hostConfig.separator.lineColor : null
                            },
                            "horizontal");

                        if (separator) {
                            separator.style.flex = "0 0 auto";

                            Utils.appendChild(element, separator);
                        }
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

    getJsonTypeName(): string {
        return "ColumnSet";
    }

    parse(json: any) {
        super.parse(json);

        if (json["columns"] != null) {
            let jsonColumns = json["columns"] as Array<any>;

            for (let i = 0; i < jsonColumns.length; i++) {
                var column = new Column();

                column.parse(jsonColumns[i]);

                this.addColumn(column);
            }
        }
    }

    addColumn(column: Column) {
        if (!column.parent) {
            this._columns.push(column);

            invokeSetParent(column, this);
        }
        else {
            throw new Error("This column already belongs to another ColumnSet.");
        }
    }

    getAllInputs(): Array<Input> {
        var result: Array<Input> = [];

        for (var i = 0; i < this._columns.length; i++) {
            result = result.concat(this._columns[i].getAllInputs());
        }

        return result;
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

function raiseExecuteActionEvent(action: ExternalAction) {
    if (AdaptiveCard.onExecuteAction != null) {
        action.prepare(action.parent.getRootElement().getAllInputs());

        AdaptiveCard.onExecuteAction(action);
    }
}

function raiseInlineCardExpandedEvent(action: ShowCardAction, isExpanded: boolean) {
    if (AdaptiveCard.onInlineCardExpanded != null) {
        AdaptiveCard.onInlineCardExpanded(action, isExpanded);
    }
}

function raiseShowPopupCardEvent(action: ShowCardAction) {
    if (AdaptiveCard.onShowPopupCard != null) {
        AdaptiveCard.onShowPopupCard(action);
    }
}

function raiseParseError(error: IValidationError) {
    if (AdaptiveCard.onParseError != null) {
        AdaptiveCard.onParseError(error);
    }
}

interface ITypeRegistration<T> {
    typeName: string,
    createInstance: () => T;
}

export class TypeRegistry<T> {
    private _items: Array<ITypeRegistration<T>> = [];

    private findTypeRegistration(typeName: string): ITypeRegistration<T> {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].typeName === typeName) {
                return this._items[i];
            }
        }

        return null;
    }

    clear() {
        this._items = [];
    }

    registerType(typeName: string, createInstance: () => T) {
        var registrationInfo = this.findTypeRegistration(typeName);

        if (registrationInfo != null) {
            registrationInfo.createInstance = createInstance;
        }
        else {
            registrationInfo = {
                typeName: typeName,
                createInstance: createInstance
            }

            this._items.push(registrationInfo);
        }
    }

    unregisterType(typeName: string) {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].typeName === typeName) {
                this._items.splice(i, 1);

                return;
            }
        }
    }

    createInstance(typeName: string): T {
        var registrationInfo = this.findTypeRegistration(typeName);

        return registrationInfo ? registrationInfo.createInstance() : null;
    }
}

export abstract class ContainerWithActions extends Container {
    private _actionCollection: ActionCollection;

    protected internalRender(): HTMLElement {
        super.internalRender();

        this._actionCollection.actionStyle = this.actionStyle;

        var renderedActions = this._actionCollection.render();

        if (renderedActions) {
            Utils.appendChild(this._element, Utils.renderSeparation(
                {
                    spacing: getEffectiveSpacing(hostConfig.actions.spacing),
                    lineThickness: null,
                    lineColor: null                    
                },
                "vertical"));
            Utils.appendChild(this._element, renderedActions);
        }

        return this._element.children.length > 0 ? this._element : null;
    }

    actionStyle: Enums.ActionStyle = "button";

    constructor() {
        super();

        this._actionCollection = new ActionCollection(this);
        this._actionCollection.onHideActionCardPane = () => { this.showBottomSpacer(null) };
        this._actionCollection.onShowActionCardPane = (action: ShowCardAction) => { this.hideBottomSpacer(null) };
    }

    parse(json: any, itemsCollectionPropertyName: string = "items") {
        super.parse(json, itemsCollectionPropertyName);

        this.actionStyle = Utils.getValueOrDefault<Enums.ActionStyle>(json["actionStyle"], "button");

        if (json["actions"] != undefined) {
            var jsonActions = json["actions"] as Array<any>;

            for (var i = 0; i < jsonActions.length; i++) {
                var action = Action.createAction(jsonActions[i]);

                if (action != null) {
                    this.addAction(action);
                }
            }
        }
    }

    isLastItem(item: CardElement): boolean {
        return super.isLastItem(item) && this._actionCollection.items.length == 0;
    }

    addAction(action: Action) {
        this._actionCollection.addAction(action);
    }

    clear() {
        super.clear();

        this._actionCollection.clear();
    }

    getAllInputs(): Array<Input> {
        return super.getAllInputs().concat(this._actionCollection.getAllInputs());
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class AdaptiveCard extends ContainerWithActions {
    private static currentVersion: IVersion = { major: 1, minor: 0 };

    static elementTypeRegistry = new TypeRegistry<CardElement>();
    static actionTypeRegistry = new TypeRegistry<Action>();

    static onExecuteAction: (action: ExternalAction) => void = null;
    static onShowPopupCard: (action: ShowCardAction) => void = null;
    static onInlineCardExpanded: (action: ShowCardAction, isExpanded: boolean) => void = null;
    static onParseError: (error: IValidationError) => void = null;

    static initialize() {
        AdaptiveCard.elementTypeRegistry.clear();

        AdaptiveCard.elementTypeRegistry.registerType("Container", () => { return new Container(); });
        AdaptiveCard.elementTypeRegistry.registerType("TextBlock", () => { return new TextBlock(); });
        AdaptiveCard.elementTypeRegistry.registerType("Image", () => { return new Image(); });
        AdaptiveCard.elementTypeRegistry.registerType("ImageSet", () => { return new ImageSet(); });
        AdaptiveCard.elementTypeRegistry.registerType("FactSet", () => { return new FactSet(); });
        AdaptiveCard.elementTypeRegistry.registerType("ColumnSet", () => { return new ColumnSet(); });
        AdaptiveCard.elementTypeRegistry.registerType("ActionSet", () => { return new ActionSet(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.Text", () => { return new TextInput(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.Date", () => { return new DateInput(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.Time", () => { return new TimeInput(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.Number", () => { return new NumberInput(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.ChoiceSet", () => { return new ChoiceSetInput(); });
        AdaptiveCard.elementTypeRegistry.registerType("Input.Toggle", () => { return new ToggleInput(); });

        AdaptiveCard.actionTypeRegistry.clear();

        AdaptiveCard.actionTypeRegistry.registerType("Action.Http", () => { return new HttpAction(); });
        AdaptiveCard.actionTypeRegistry.registerType("Action.OpenUrl", () => { return new OpenUrlAction(); });
        AdaptiveCard.actionTypeRegistry.registerType("Action.Submit", () => { return new SubmitAction(); });
        AdaptiveCard.actionTypeRegistry.registerType("Action.ShowCard", () => { return new ShowCardAction(); });
    }

    private isVersionSupported(): boolean {
        var unsupportedVersion: boolean =
            (AdaptiveCard.currentVersion.major < this.minVersion.major) ||
            (AdaptiveCard.currentVersion.major == this.minVersion.major && AdaptiveCard.currentVersion.minor < this.minVersion.minor);

        return !unsupportedVersion;
    }

    private _cardTypeName: string;

    protected get defaultPadding(): HostConfig.IPaddingDefinition {
        return hostConfig.adaptiveCard.padding;
    }

    protected get allowCustomPadding(): boolean {
        return hostConfig.adaptiveCard.allowCustomPadding;
    }

    protected get allowCustomColorPalette() {
        return hostConfig.adaptiveCard.allowCustomColorPalette;
    }

    minVersion: IVersion = { major: 1, minor: 0 };
    fallbackText: string;

    getJsonTypeName(): string {
        return "AdaptiveCard";
    }

    validate(): Array<IValidationError> {
        var result: Array<IValidationError> = [];

        if (this._cardTypeName != "AdaptiveCard") {
            result.push(
                {
                    error: Enums.ValidationError.MissingCardType,
                    message: "Invalid or missing card type. Make sure the card's type property is set to \"AdaptiveCard\"."
                });
        }

        if (!this.isVersionSupported()) {
            result.push(
                {
                    error: Enums.ValidationError.UnsupportedCardVersion,
                    message: "The specified card version is not supported."
                });
        }

        return result.concat(super.validate());
    }

    parse(json: any) {
        this._cardTypeName = json["type"];

        var minVersion = json["minVersion"];
        var regEx = /(\d+).(\d+)/gi;
        var matches = regEx.exec(minVersion);

        if (matches != null && matches.length == 3) {
            this.minVersion.major = parseInt(matches[1]);
            this.minVersion.minor = parseInt(matches[2]);
        }

        this.fallbackText = json["fallbackText"];

        super.parse(json, "body");
    }

    render(): HTMLElement {
        var renderedCard: HTMLElement;

        if (!this.isVersionSupported()) {
            renderedCard = document.createElement("div");
            renderedCard.innerHTML = this.fallbackText ? this.fallbackText : "The specified card version is not supported.";

            return renderedCard;
        }
        else {
            return super.render();
        }
    }
}

// This calls acts as a static constructor (see https://github.com/Microsoft/TypeScript/issues/265)
AdaptiveCard.initialize();

class InlineAdaptiveCard extends AdaptiveCard {
    protected get defaultPadding(): HostConfig.IPaddingDefinition {
        return hostConfig.actions.showCard.padding;
    }

    protected get defaultColorPalette(): Enums.ColorPalette {
        return "emphasis";
    }

    getForbiddenActionTypes(): Array<any> {
        return [ShowCardAction];
    }
}

var defaultHostConfig: HostConfig.IHostConfig = {
    supportsInteractivity: true,
    spacing: {
        small: 3,
        default: 8,
        medium: 20,
        large: 30,
        extraLarge: 40
    },
    padding: {
        small: 10,
        default: 20,
        large: 30
    },
    separator: {
        lineThickness: 1,
        lineColor: "#EEEEEE"        
    },
    fontFamily: "Segoe UI",
    fontSizes: {
        small: 8,
        normal: 10,
        medium: 12,
        large: 14,
        extraLarge: 16
    },
    fontWeights: {
        lighter: 200,
        normal: 400,
        bolder: 600
    },
    colorPalettes: {
        default: {
            fontColors: {
                dark: { normal: "#0000FF", subtle: "#222222" },
                light: { normal: "#FFFFFF", subtle: "#DDDDDD" },
                accent: { normal: "#0000FF", subtle: "#0000DD" },
                attention: { normal: "#FF6600", subtle: "#DD4400" },
                good: { normal: "#00FF00", subtle: "#00DD00" },
                warning: { normal: "#FF0000", subtle: "#DD0000" }
            }
        },
        emphasis: {
            backgroundColor: "#EEEEEE",
            fontColors: {
                dark: { normal: "#0000FF", subtle: "#222222" },
                light: { normal: "#FFFFFF", subtle: "#DDDDDD" },
                accent: { normal: "#0000FF", subtle: "#0000DD" },
                attention: { normal: "#FF6600", subtle: "#DD4400" },
                good: { normal: "#00FF00", subtle: "#00DD00" },
                warning: { normal: "#FF0000", subtle: "#DD0000" }
            }
        }
    },
    imageSizes: {
        small: 40,
        medium: 80,
        large: 160
    },
    actions: {
        maxActions: 5,
        spacing: "default",
        buttonSpacing: 20,
        showCard: {
            actionMode: "inlineEdgeToEdge",
            inlineTopMargin: 16,
            padding: {
                top: "default",
                right: "default",
                bottom: "default",
                left: "default"
            }
        },
        actionsOrientation: "horizontal",
        actionAlignment: "left"
    },
    adaptiveCard: {
        padding: {
            left: "default",
            top: "default",
            right: "default",
            bottom: "default"
        },
        allowCustomPadding: false,
        allowCustomColorPalette: false
    },
    textBlock: {
        color: "dark"
    },
    image: {
        size: "medium"
    },
    imageSet: {
        imageSize: "medium",
        maxImageHeight: 100
    },
    factSet: {
        title: {
            color: "dark",
            size: "normal",
            isSubtle: false,
            weight: "bolder",
            wrap: true,
            maxWidth: 150
        },
        value: {
            color: "dark",
            size: "normal",
            isSubtle: false,
            weight: "normal",
            wrap: true
        },
        spacing: 10
    }
}

var hostConfig = defaultHostConfig;

export function setHostConfig(configuration: HostConfig.IHostConfig) {
    hostConfig = configuration;
}

export function resetHostConfig() {
    hostConfig = defaultHostConfig;
}