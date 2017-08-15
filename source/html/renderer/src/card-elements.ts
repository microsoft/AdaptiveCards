import * as Enums from "./enums";
import * as Utils from "./utils";
import * as HostConfig from "./host-config";
import * as TextFormatters from "./text-formatters";

function invokeSetParent(obj: any, parent: CardElement) {
    // This is not super pretty, but it the closest emulation of
    // "internal" in TypeScript.
    obj["setParent"](parent);
}

function invokeSetCollection(action: Action, collection: ActionCollection) {
    action["setCollection"](collection);
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
        case "padding":
            return hostConfig.spacing.padding;
        default:
            return 0;
    }
}

function getEffectivePadding(padding: Enums.Padding): number {
    switch (padding) {
        case "default":
            return hostConfig.spacing.padding;
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

function getContainerStyleDefinition(containerStyle: Enums.ContainerStyle) {
    switch (containerStyle) {
        case "emphasis":
            return hostConfig.containerStyles.emphasis;
        default:
            return hostConfig.containerStyles.default;
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
    private _isVisibile: boolean = true;
    private _renderedElement: HTMLElement = null;
    private _separatorElement: HTMLElement = null;

    private updateRenderedElementVisibility() {
        if (this._renderedElement) {
            this._renderedElement.style.visibility = this._isVisibile ? null : "collapse";
        }

        if (this._separatorElement) {
            this._separatorElement.style.visibility = this._isVisibile ? null : "collapse";
        }
    }

    protected internalGetNonZeroPadding(padding: HostConfig.IPaddingDefinition) {
        if (padding.top == "none") {
            padding.top = this.internalPadding.top;
        }

        if (padding.right == "none") {
            padding.right = this.internalPadding.right;
        }

        if (padding.bottom == "none") {
            padding.bottom = this.internalPadding.bottom;
        }

        if (padding.left == "none") {
            padding.left = this.internalPadding.left;
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

    protected internalRenderSeparator(): HTMLElement {
        return Utils.renderSeparation(
            {
                spacing: getEffectiveSpacing(this.spacing),
                lineThickness: this.separator ? hostConfig.separator.lineThickness : null,
                lineColor: this.separator ? hostConfig.separator.lineColor : null
            },
            "vertical");        
    }

    protected get allowCustomPadding(): boolean {
        return true;
    }

    protected get defaultPadding(): HostConfig.IPaddingDefinition {
        return { top: "none", right: "none", bottom: "none", left: "none" };
    }

    protected get internalPadding(): HostConfig.IPaddingDefinition {
        return (this._internalPadding && this.allowCustomPadding) ? this._internalPadding : this.defaultPadding;
    }

    protected set internalPadding(value: HostConfig.IPaddingDefinition) {
        this._internalPadding = value;
    }

    protected get separatorOrientation(): Enums.Orientation {
        return "horizontal";
    }

    id: string;
    speak: string;
    horizontalAlignment: Enums.HorizontalAlignment = "left";
    spacing: Enums.Spacing = "default";
    separator: boolean = false;
    height: "auto" | "stretch" = "auto";

    abstract getJsonTypeName(): string;
    abstract renderSpeech(): string;

    getNonZeroPadding(): HostConfig.IPaddingDefinition {
        var padding: HostConfig.IPaddingDefinition = {
            top: "none",
            right: "none",
            bottom: "none",
            left: "none"
        };

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
        raiseParseElementEvent(this, json);

        this.id = json["id"];
        this.speak = json["speak"];
        this.horizontalAlignment = Utils.getValueOrDefault<Enums.HorizontalAlignment>(json["horizontalAlignment"], "left");

        this.spacing = Utils.getValueOrDefault<Enums.Spacing>(json["spacing"], "default");
        this.separator = json["separator"];

        var jsonSeparation = json["separation"];

        if (jsonSeparation !== undefined) {
            if (jsonSeparation === "none") {
                this.spacing = "none";
                this.separator = false;
            }
            else if (jsonSeparation === "strong") {
                this.spacing = "large";
                this.separator = true;
            }
            else if (jsonSeparation === "default") {
                this.spacing = "default";
                this.separator = false;
            }

            raiseParseError(
                {
                    error: Enums.ValidationError.Deprecated,
                    message: "The \"separation\" property is deprecated and will be removed. Use the \"spacing\" and \"separator\" properties instead."
                });
        }

        var jsonHeight = json["height"];

        if (jsonHeight === "auto" || jsonHeight === "stretch") {
            this.height = jsonHeight;
        }
    }

    validate(): Array<IValidationError> {
        return [];
    }

    render(): HTMLElement {
        this._renderedElement = this.internalRender();
        this._separatorElement = this.internalRenderSeparator();

        if (this._renderedElement) {
            this._renderedElement.style.boxSizing = "border-box";

            this.adjustRenderedElementSize(this._renderedElement);
        }

        this.updateLayout(false);
        this.updateRenderedElementVisibility();

        return this._renderedElement;
    }

    updateLayout(processChildren: boolean = true) {
        // Does nothing in base implementation
    }

    isAtTheVeryTop(): boolean {
        return this.parent ? this.parent.isFirstElement(this) && this.parent.isAtTheVeryTop() : true;
    }

    isFirstElement(element: CardElement): boolean {
        return true;
    }

    isAtTheVeryBottom(): boolean {
        return this.parent ? this.parent.isLastElement(this) && this.parent.isAtTheVeryBottom() : true;
    }

    isLastElement(element: CardElement): boolean {
        return true;
    }

    isAtTheVeryLeft(): boolean {
        return this.parent ? this.parent.isLeftMostElement(this) && this.parent.isAtTheVeryLeft() : true;
    }

    isLeftMostElement(element: CardElement): boolean {
        return true;
    }

    isAtTheVeryRight(): boolean {
        return this.parent ? this.parent.isRightMostElement(this) && this.parent.isAtTheVeryRight() : true;
    }

    isRightMostElement(element: CardElement): boolean {
        return true;
    }

    canContentBleed(): boolean {
        return this.parent ? this.parent.canContentBleed() : true;
    }

    getRootElement(): CardElement {
        var rootElement: CardElement = this;

        while (rootElement.parent) {
            rootElement = rootElement.parent;
        }

        return rootElement;
    }

    getParentContainer(): Container {
        var currentElement: CardElement = this.parent;

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

    getElementById(id: string): CardElement {
        return this.id === id ? this : null;
    }

    getActionById(id: string): Action {
        return null;
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

    get isVisible(): boolean {
        return this._isVisibile;
    }

    set isVisible(value: boolean) {
        if (this._isVisibile != value) {
            this._isVisibile = value;

            this.updateRenderedElementVisibility();

            if (this._renderedElement) {
                raiseElementVisibilityChangedEvent(this);
            }
        }
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;        
    }

    get separatorElement(): HTMLElement {
        return this._separatorElement;
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
            var styleDefinition = getContainerStyleDefinition(parentContainer ? parentContainer.style : "default");

            var actualTextColor = this.color ? this.color : hostConfig.textBlock.color;
            var colorDefinition: HostConfig.ITextColorDefinition;

            switch (actualTextColor) {
                case "dark":
                    colorDefinition = styleDefinition.fontColors.dark;
                    break;
                case "light":
                    colorDefinition = styleDefinition.fontColors.light;
                    break;
                case "accent":
                    colorDefinition = styleDefinition.fontColors.accent;
                    break;
                case "good":
                    colorDefinition = styleDefinition.fontColors.good;
                    break;
                case "warning":
                    colorDefinition = styleDefinition.fontColors.warning;
                    break;
                case "attention":
                    colorDefinition = styleDefinition.fontColors.attention;
                    break;
                default:
                    colorDefinition = styleDefinition.fontColors.dark;
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

            if (this.pixelWidth || this.pixelHeight) {
                if (this.pixelWidth) {
                    imageElement.style.width = this.pixelWidth + "px";
                }

                if (this.pixelHeight) {
                    imageElement.style.height = this.pixelHeight + "px";
                }
            }
            else {
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
    selectAction: Action;
    pixelWidth?: number = null;
    pixelHeight?: number = null;

    getJsonTypeName(): string {
        return "Image";
    }

    getActionById(id: string) {
        var result = super.getActionById(id);

        if (!result && this.selectAction) {
            result = this.selectAction.getActionById(id);
        }

        return result;
    }

    parse(json: any) {
        super.parse(json);

        this.url = json["url"];
        this.style = Utils.getValueOrDefault<Enums.ImageStyle>(json["style"], this.style);
        this.size = Utils.getValueOrDefault<Enums.Size>(json["size"], this.size);

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            this.selectAction = Action.createAction(selectActionJson);
            invokeSetParent(this.selectAction, this);
        }

        if (json["pixelWidth"] && typeof json["pixelWidth"] === "number") {
            this.pixelWidth = json["pixelWidth"];
        }

        if (json["pixelHeight"] && typeof json["pixelHeight"] === "number") {
            this.pixelHeight = json["pixelHeight"];
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
    private _style: Enums.ActionStyle = "link";
    private _element: HTMLButtonElement = null;
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
        this._element.type = "button";
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
    private _actionCollection: ActionCollection = null; // hold the reference to its action collection

    protected setParent(value: CardElement) {
        this._parent = value;
    }

    abstract getJsonTypeName(): string;

    execute() {
        raiseExecuteActionEvent(this);
    }

    private setCollection(actionCollection: ActionCollection) {
        this._actionCollection = actionCollection;
    }

    // Expand the action card pane with a inline status card
    // Null status will clear the status bar
    setStatus(status: any) {
        if (this._actionCollection == null) {
            return;
        }

        if (status) {
            let statusCard = new InlineAdaptiveCard();
            statusCard.parse(status);
            this._actionCollection.showStatusCard(statusCard);
        }
        else {
            this._actionCollection.hideStatusCard();
        }
    }

    validate(): Array<IValidationError> {
        return [];
    }

    prepare(inputs: Array<Input>) {
        // Do nothing in base implementation
    };

    parse(json: any) {
        this.id = json["id"];
        this.title = json["title"];
    }

    getAllInputs(): Array<Input> {
        return [];
    }

    getActionById(id: string): Action {
        if (this.id == id) {
            return this;
        }
    }

    id: string;
    title: string;

    get parent(): CardElement {
        return this._parent;
    }
}

export class SubmitAction extends Action {
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

export class OpenUrlAction extends Action {
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

export class HttpAction extends Action {
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

    getActionById(id: string): Action {
        var result = super.getActionById(id);

        if (!result) {
            result = this.card.getActionById(id);
        }

        return result;
    }
}

class ActionCollection {
    private _owner: CardElement;
    private _actionButtons: Array<ActionButton> = [];
    private _actionCardContainer: HTMLDivElement;
    private _expandedAction: ShowCardAction = null;
    private _renderedActionCount: number = 0;
    private _statusCard: HTMLElement = null;
    private _actionCard: HTMLElement = null;

    showStatusCard(status: AdaptiveCard) {
        this._statusCard = status.render();

        this.refreshContainer();
    }

    hideStatusCard() {
        this._statusCard = null;

        this.refreshContainer();
    }

    private refreshContainer() {
        this._actionCardContainer.innerHTML = "";

        if (this._actionCard === null && this._statusCard === null) {
            this._actionCardContainer.style.padding = "0px";
            this._actionCardContainer.style.marginTop = "0px";

            if (this.onHideActionCardPane) {
                this.onHideActionCardPane();
            }

            return;
        }

        if (this.onShowActionCardPane) {
            this.onShowActionCardPane(null);
        }

        this._actionCardContainer.style.marginTop = this._renderedActionCount > 0 ? hostConfig.actions.showCard.inlineTopMargin + "px" : "0px";

        var padding = paddingToSpacingDefinition(this._owner.getNonZeroPadding());

        if (hostConfig.actions.showCard.actionMode == "inlineEdgeToEdge") {
            if (this._actionCard !== null) {
                this._actionCard.style.paddingLeft = padding.left + "px";
                this._actionCard.style.paddingRight = padding.right + "px";

                this._actionCard.style.marginLeft = "-" + padding.left + "px";
                this._actionCard.style.marginRight = "-" + padding.right + "px";

                Utils.appendChild(this._actionCardContainer, this._actionCard);
            }

            if (this._statusCard !== null) {
                this._statusCard.style.paddingLeft = padding.left + "px";
                this._statusCard.style.paddingRight = padding.right + "px";

                this._statusCard.style.marginLeft = "-" + padding.left + "px";
                this._statusCard.style.marginRight = "-" + padding.right + "px";

                Utils.appendChild(this._actionCardContainer, this._statusCard);
            }
        }
    }

    private hideActionCard() {
        if (this._expandedAction) {
            raiseInlineCardExpandedEvent(this._expandedAction, false);
        }

        this._expandedAction = null;
        this._actionCard = null;

        this.refreshContainer();
    }

    private showActionCard(action: ShowCardAction) {
        if (action.card == null) return;

        var renderedCard = action.card.render();

        this._actionCard = renderedCard;
        this._expandedAction = action;

        this.refreshContainer();
        raiseInlineCardExpandedEvent(action, true);
    }

    private actionClicked(actionButton: ActionButton) {
        if (!(actionButton.action instanceof ShowCardAction)) {
            for (var i = 0; i < this._actionButtons.length; i++) {
                this._actionButtons[i].state = ActionButtonState.Normal;
            }

            this.hideActionCard();

            actionButton.action.execute();
        }
        else {
            this.hideStatusCard();

            if (hostConfig.actions.showCard.actionMode == "popup") {
                actionButton.action.execute();
            }
            else if (actionButton.action === this._expandedAction) {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    this._actionButtons[i].state = ActionButtonState.Normal;
                }

                this.hideActionCard();
            }
            else {
                for (var i = 0; i < this._actionButtons.length; i++) {
                    if (this._actionButtons[i] !== actionButton) {
                        this._actionButtons[i].state = ActionButtonState.Subdued;
                    }
                }

                actionButton.state = ActionButtonState.Expanded;

                this.showActionCard(actionButton.action);
            }
        }
    }

    items: Array<Action> = [];
    actionStyle: Enums.ActionStyle = "link";
    onHideActionCardPane: () => void = null;
    onShowActionCardPane: (action: ShowCardAction) => void = null;

    constructor(owner: CardElement) {
        this._owner = owner;
    }

    getActionById(id: string): Action {
        var result: Action = null;

        for (var i = 0; i < this.items.length; i++) {
            result = this.items[i].getActionById(id);

            if (result) {
                break;
            }
        }

        return result;
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
            this.showActionCard(<ShowCardAction>this.items[0]);
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
            invokeSetCollection(action, this);
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

    actionStyle: Enums.ActionStyle = "link";

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

        this.actionStyle = Utils.getValueOrDefault<Enums.ActionStyle>(json["actionStyle"], this.actionStyle);

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
    private _style?: Enums.ContainerStyle = null;

    protected showBottomSpacer(requestingElement: CardElement) {
        if ((!requestingElement || this.isLastElement(requestingElement)) && hostConfig.actions.showCard.actionMode == "inlineEdgeToEdge") {
            this.renderedElement.style.paddingBottom = paddingToSpacingDefinition(this.internalPadding).bottom + "px";

            super.showBottomSpacer(this);
        }
    }

    protected hideBottomSpacer(requestingElement: CardElement) {
        if ((!requestingElement || this.isLastElement(requestingElement)) && hostConfig.actions.showCard.actionMode == "inlineEdgeToEdge") {
            this.renderedElement.style.paddingBottom = "0px";

            super.hideBottomSpacer(this);
        }
    }

    protected applyPadding() {
        if (this.hasBackground) {
            var physicalMargin: HostConfig.ISpacingDefinition = { top: 0, right: 0, bottom: 0, left: 0 };
            var physicalPadding: HostConfig.ISpacingDefinition = { top: 0, right: 0, bottom: 0, left: 0 };

            var useAutoPadding = AdaptiveCard.useAutoPadding && (this.parent ? this.parent.canContentBleed() : false);

            if (useAutoPadding) {
                var effectivePadding = this.getNonZeroPadding();
                var effectiveMargin: HostConfig.IPaddingDefinition = {
                    top: effectivePadding.top,
                    right: effectivePadding.right,
                    bottom: effectivePadding.bottom,
                    left: effectivePadding.left,
                };

                if (!this.isAtTheVeryTop()) {
                    effectivePadding.top = "none";
                    effectiveMargin.top = "none";
                }

                if (!this.isAtTheVeryBottom()) {
                    effectivePadding.bottom = "none";
                    effectiveMargin.bottom = "none";
                }

                if (!this.isAtTheVeryLeft()) {
                    effectivePadding.left = "none";
                    effectiveMargin.left = "none";
                }

                if (!this.isAtTheVeryRight()) {
                    effectivePadding.right = "none";
                    effectiveMargin.right = "none";
                }

                if (effectivePadding.left != "none" || effectivePadding.right != "none") {
                    if (effectivePadding.left == "none") {
                        effectivePadding.left = effectivePadding.right;
                    }

                    if (effectivePadding.right == "none") {
                        effectivePadding.right = effectivePadding.left;
                    }
                }

                if (effectivePadding.top != "none" || effectivePadding.bottom != "none") {
                    if (effectivePadding.top == "none") {
                        effectivePadding.top = effectivePadding.bottom;
                    }

                    if (effectivePadding.bottom == "none") {
                        effectivePadding.bottom = effectivePadding.top;
                    }
                }

                if (effectivePadding.top != "none" || effectivePadding.right != "none" || effectivePadding.bottom != "none" || effectivePadding.left != "none") {
                    if (effectivePadding.top == "none") {
                        effectivePadding.top = "default";
                    }

                    if (effectivePadding.right == "none") {
                        effectivePadding.right = "default";
                    }

                    if (effectivePadding.bottom == "none") {
                        effectivePadding.bottom = "default";
                    }

                    if (effectivePadding.left == "none") {
                        effectivePadding.left = "default";
                    }
                }

                if (effectivePadding.top == "none" && effectivePadding.right == "none" && effectivePadding.bottom == "none" && effectivePadding.left == "none") {
                    effectivePadding.top = "default";
                    effectivePadding.right = "default";
                    effectivePadding.bottom = "default";
                    effectivePadding.left = "default";
                }

                physicalMargin = paddingToSpacingDefinition(effectiveMargin);
                physicalPadding = paddingToSpacingDefinition(effectivePadding);
            }
            else {
                physicalPadding = paddingToSpacingDefinition({ top: "default", right: "default", bottom: "default", left: "default" });
            }

            if (this.renderedElement) {
                this.renderedElement.style.marginTop = "-" + physicalMargin.top + "px";
                this.renderedElement.style.marginRight = "-" + physicalMargin.right + "px";
                this.renderedElement.style.marginBottom = "-" + physicalMargin.bottom + "px";
                this.renderedElement.style.marginLeft = "-" + physicalMargin.left + "px";

                this.renderedElement.style.paddingTop = physicalPadding.top + "px";
                this.renderedElement.style.paddingRight = physicalPadding.right + "px";
                this.renderedElement.style.paddingBottom = physicalPadding.bottom + "px";
                this.renderedElement.style.paddingLeft = physicalPadding.left + "px";
            }

            if (this.separatorElement) {
                if (this.separatorOrientation == "horizontal") {
                    this.separatorElement.style.marginLeft = "-" + physicalMargin.left + "px";
                    this.separatorElement.style.marginRight = "-" + physicalMargin.right + "px";
                }
                else {
                    this.separatorElement.style.marginTop = "-" + physicalMargin.top + "px";
                    this.separatorElement.style.marginBottom = "-" + physicalMargin.bottom + "px";
                }
            }
        }
    }

    protected internalRender(): HTMLElement {
        var element = document.createElement("div");
        element.className = "ac-container";
        element.style.display = "flex";
        element.style.flexDirection = "column";

        if (this.backgroundImage) {
            this.backgroundImage.apply(element);
        }

        var styleDefinition = getContainerStyleDefinition(this.style);

        if (!Utils.isNullOrEmpty(styleDefinition.backgroundColor)) {
            element.style.backgroundColor = Utils.stringToCssColor(styleDefinition.backgroundColor);
        }

        if (this.selectAction) {
            element.classList.add("ac-selectable");
        }

        element.onclick = (e) => {
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
                    if (renderedElementCount > 0 && this._items[i].separatorElement) {
                        this._items[i].separatorElement.style.flex = "0 0 auto";

                        Utils.appendChild(element, this._items[i].separatorElement);
                    }

                    Utils.appendChild(element, renderedElement);

                    renderedElementCount++;
                }
            }
        }

        return element;
    }

    protected get hasBackground(): boolean {
        var parentContainer = this.getParentContainer();

        return this.backgroundImage != undefined || (parentContainer ? parentContainer.style != this.style : false);
    }

    protected get defaultStyle(): Enums.ContainerStyle {
        return "default";
    }

    protected get allowCustomStyle(): boolean {
        return true;
    }

    selectAction: Action;
    backgroundImage: BackgroundImage;

    get style(): Enums.ContainerStyle {
        if (this.allowCustomStyle) {
            return this._style ? this._style : this.defaultStyle;
        }
        else {
            return this.defaultStyle;
        }
    }

    getJsonTypeName(): string {
        return "Container";
    }

    isFirstElement(element: CardElement): boolean {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].isVisible) {
                return this._items[i] == element;
            }
        }

        return false;
    }

    isLastElement(element: CardElement): boolean {
        for (var i = this._items.length - 1; i >= 0; i --) {
            if (this._items[i].isVisible) {
                return this._items[i] == element;
            }
        }

        return false;
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

        var jsonBackgroundImage = json["backgroundImage"];

        if (jsonBackgroundImage) {
            this.backgroundImage = new BackgroundImage();

            if (typeof jsonBackgroundImage === "string") {
                this.backgroundImage.url = jsonBackgroundImage;
                this.backgroundImage.mode = "stretch";
            }
            else if (typeof jsonBackgroundImage === "object") {
                this.backgroundImage = new BackgroundImage();
                this.backgroundImage.parse(json["backgroundImage"]);
            }
        }

        this._style = Utils.getValueOrDefault<Enums.ContainerStyle>(json["style"], null);

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
            this.selectAction = Action.createAction(selectActionJson);
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

    canContentBleed(): boolean {
        return this.hasBackground ? false : super.canContentBleed();
    }

    getAllInputs(): Array<Input> {
        var result: Array<Input> = [];

        for (var i = 0; i < this._items.length; i++) {
            var item: CardElement = this._items[i];

            result = result.concat(item.getAllInputs());
        }

        return result;
    }

    getElementById(id: string): CardElement {
        var result: CardElement = super.getElementById(id);

        if (!result) {
            for (var i = 0; i < this._items.length; i++) {
                result = this._items[i].getElementById(id);

                if (result) {
                    break;
                }
            }
        }

        return result;
    }

    getActionById(id: string): Action {
        var result: Action = super.getActionById(id);

        if (!result) {
            if (this.selectAction) {
                result = this.selectAction.getActionById(id);
            }

            if (!result) {
                for (var i = 0; i < this._items.length; i++) {
                    result = this._items[i].getActionById(id);

                    if (result) {
                        break;
                    }
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

    updateLayout(processChildren: boolean = true) {
        this.applyPadding();

        if (processChildren) {
            for (var i = 0; i < this._items.length; i++) {
                this._items[i].updateLayout();
            }
        }
    }
}

export class Column extends Container {
    private _computedWeight: number = 0;

    protected internalRenderSeparator(): HTMLElement {
        return Utils.renderSeparation(
            {
                spacing: getEffectiveSpacing(this.spacing),
                lineThickness: this.separator ? hostConfig.separator.lineThickness : null,
                lineColor: this.separator ? hostConfig.separator.lineColor : null
            },
            "horizontal");        
    }

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

    protected get separatorOrientation(): Enums.Orientation {
        return "vertical";
    }

    width: number | "auto" | "stretch" = "auto";

    getJsonTypeName(): string {
        return "Column";
    }

    parse(json: any) {
        super.parse(json);

        var jsonWidth = json["width"];

        if (jsonWidth === undefined) {
            jsonWidth = json["size"];

            if (jsonWidth !== undefined) {
                raiseParseError(
                    {
                        error: Enums.ValidationError.Deprecated,
                        message: "The \"Column.size\" property is deprecated and will be removed. Use the \"Column.width\" property instead."
                    });
            }
        }

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
            element.className = "ac-columnSet";
            element.style.display = "flex";

            if (this.selectAction) {
                element.classList.add("ac-selectable");
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
                    if (renderedColumnCount > 0 && this._columns[i].separatorElement) {
                        this._columns[i].separatorElement.style.flex = "0 0 auto";

                        Utils.appendChild(element, this._columns[i].separatorElement);
                    }

                    Utils.appendChild(element, renderedColumn);

                    renderedColumnCount++;
                }
            }

            return renderedColumnCount > 0 ? element : null;
        }
        else {
            return null;
        }
    }

    selectAction: Action;

    getJsonTypeName(): string {
        return "ColumnSet";
    }

    parse(json: any) {
        super.parse(json);

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            this.selectAction = Action.createAction(selectActionJson);
            invokeSetParent(this.selectAction, this);
        }

        if (json["columns"] != null) {
            let jsonColumns = json["columns"] as Array<any>;

            for (let i = 0; i < jsonColumns.length; i++) {
                var column = new Column();

                column.parse(jsonColumns[i]);

                this.addColumn(column);
            }
        }
    }

    updateLayout(processChildren: boolean = true) {
        if (processChildren) {
            for (var i = 0; i < this._columns.length; i++) {
                this._columns[i].updateLayout();
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

    isLeftMostElement(element: CardElement): boolean {
        return this._columns.indexOf(<Column>element) == 0;
    }

    isRightMostElement(element: CardElement): boolean {
        return this._columns.indexOf(<Column>element) == this._columns.length - 1;
    }

    getAllInputs(): Array<Input> {
        var result: Array<Input> = [];

        for (var i = 0; i < this._columns.length; i++) {
            result = result.concat(this._columns[i].getAllInputs());
        }

        return result;
    }

    getElementById(id: string): CardElement {
        var result: CardElement = super.getElementById(id);

        if (!result) {
            for (var i = 0; i < this._columns.length; i++) {
                result = this._columns[i].getElementById(id);

                if (result) {
                    break;
                }
            }
        }

        return result;
    }

    getActionById(id: string): Action {
        var result: Action = null;

        for (var i = 0; i < this._columns.length; i++) {
            result = this._columns[i].getActionById(id);

            if (result) {
                break;
            }
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

function raiseExecuteActionEvent(action: Action) {
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

function raiseElementVisibilityChangedEvent(element: CardElement) {
    element.getRootElement().updateLayout();

    if (AdaptiveCard.onElementVisibilityChanged != null) {
        AdaptiveCard.onElementVisibilityChanged(element);
    }
}

function raiseParseElementEvent(element: CardElement, json: any) {
    if (AdaptiveCard.onParseElement != null) {
        AdaptiveCard.onParseElement(element, json);
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
        var element = super.internalRender();

        this._actionCollection.actionStyle = this.actionStyle;

        var renderedActions = this._actionCollection.render();

        if (renderedActions) {
            Utils.appendChild(element, Utils.renderSeparation(
                {
                    spacing: getEffectiveSpacing(hostConfig.actions.spacing),
                    lineThickness: null,
                    lineColor: null
                },
                "vertical"));
            Utils.appendChild(element, renderedActions);
        }

        return element.children.length > 0 ? element : null;
    }

    actionStyle: Enums.ActionStyle = "link";

    constructor() {
        super();

        this._actionCollection = new ActionCollection(this);
        this._actionCollection.onHideActionCardPane = () => { this.showBottomSpacer(null) };
        this._actionCollection.onShowActionCardPane = (action: ShowCardAction) => { this.hideBottomSpacer(null) };
    }

    getActionById(id: string): Action {
        var result: Action = this._actionCollection.getActionById(id);

        return result ? result : super.getActionById(id);
    }

    parse(json: any, itemsCollectionPropertyName: string = "items") {
        super.parse(json, itemsCollectionPropertyName);

        this.actionStyle = Utils.getValueOrDefault<Enums.ActionStyle>(json["actionStyle"], this.actionStyle);

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

    isLastElement(element: CardElement): boolean {
        return super.isLastElement(element) && this._actionCollection.items.length == 0;
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

    static useAutoPadding: boolean = false;

    static elementTypeRegistry = new TypeRegistry<CardElement>();
    static actionTypeRegistry = new TypeRegistry<Action>();

    static onExecuteAction: (action: Action) => void = null;
    static onElementVisibilityChanged: (element: CardElement) => void = null;
    static onInlineCardExpanded: (action: ShowCardAction, isExpanded: boolean) => void = null;
    static onParseElement: (element: CardElement, json: any) => void = null;
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

    protected applyPadding() {
        var effectivePadding = paddingToSpacingDefinition(this.internalPadding);

        this.renderedElement.style.paddingTop = effectivePadding.top + "px";
        this.renderedElement.style.paddingRight = effectivePadding.right + "px";
        this.renderedElement.style.paddingBottom = effectivePadding.bottom + "px";
        this.renderedElement.style.paddingLeft = effectivePadding.left + "px";
    }

    protected get defaultPadding(): HostConfig.IPaddingDefinition {
        return { top: "default", right: "default", bottom: "default", left: "default" };
    }

    protected get allowCustomPadding(): boolean {
        return false;
    }

    protected get allowCustomStyle() {
        return hostConfig.adaptiveCard.allowCustomStyle;
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
        return { top: "default", right: "default", bottom: "default", left: "default" };
    }

    protected get defaultStyle(): Enums.ContainerStyle {
        return hostConfig.actions.showCard.style ? hostConfig.actions.showCard.style : "emphasis";
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
        extraLarge: 40,
        padding: 20
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
    containerStyles: {
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
            inlineTopMargin: 16
        },
        actionsOrientation: "horizontal",
        actionAlignment: "left"
    },
    adaptiveCard: {
        allowCustomStyle: false
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