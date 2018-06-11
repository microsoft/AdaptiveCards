import * as Enums from "./enums";
import * as Utils from "./utils";
import * as HostConfig from "./host-config";
import * as TextFormatters from "./text-formatters";

function invokeSetCollection(action: Action, collection: ActionCollection) {
    if (action) {
        // Closest emulation of "internal" in TypeScript.
        action["setCollection"](collection);
    }
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

export function createActionInstance(json: any): Action {
    var actionType = json["type"];

    var result = AdaptiveCard.actionTypeRegistry.createInstance(actionType);

    if (!result) {
        raiseParseError(
            {
                error: Enums.ValidationError.UnknownActionType,
                message: "Unknown action type: " + actionType
            });
    }

    return result;
}

export class SpacingDefinition {
    left: number = 0;
    top: number = 0;
    right: number = 0;
    bottom: number = 0;

    constructor(top: number = 0,
                right: number = 0,
                bottom: number = 0,
                left: number = 0) {
        this.top = top;
        this.right = right;
        this.bottom = bottom;
        this.left = left;
    }
}

export class PaddingDefinition {
    top: Enums.Spacing = Enums.Spacing.None;
    right: Enums.Spacing = Enums.Spacing.None;
    bottom: Enums.Spacing = Enums.Spacing.None;
    left: Enums.Spacing = Enums.Spacing.None;

    constructor(top: Enums.Spacing = Enums.Spacing.None,
                right: Enums.Spacing = Enums.Spacing.None,
                bottom: Enums.Spacing = Enums.Spacing.None,
                left: Enums.Spacing = Enums.Spacing.None) {
        this.top = top;
        this.right = right;
        this.bottom = bottom;
        this.left = left;
    }

    toSpacingDefinition(hostConfig: HostConfig.HostConfig): SpacingDefinition {
        return new SpacingDefinition(
            hostConfig.getEffectiveSpacing(this.top),
            hostConfig.getEffectiveSpacing(this.right),
            hostConfig.getEffectiveSpacing(this.bottom),
            hostConfig.getEffectiveSpacing(this.left));
    }
}

export interface IValidationError {
    error: Enums.ValidationError,
    message: string;
}

export class SizeAndUnit {
    physicalSize: number;
    unit: Enums.SizeUnit;

    static parse(input: any): SizeAndUnit {
        let result = new SizeAndUnit(0, Enums.SizeUnit.Weight);

        let regExp = /^([0-9]+)(px|\*)?$/g;
        let matches = regExp.exec(input);
    
        if (matches && matches.length >= 2) {
            result.physicalSize = parseInt(matches[1]);
    
            if (matches.length == 3) {
                if (matches[2] == "px") {
                    result.unit = Enums.SizeUnit.Pixel;
                }
            }
    
            return result;
        }
    
        throw new Error("Invalid size: " + input);
    }

    constructor(physicalSize: number, unit: Enums.SizeUnit) {
        this.physicalSize = physicalSize;
        this.unit = unit;
    }
}

export abstract class CardElement {
    private _lang: string = undefined;
    private _hostConfig?: HostConfig.HostConfig = null;
    private _internalPadding: PaddingDefinition = null;
    private _parent: CardElement = null;
    private _renderedElement: HTMLElement = null;
    private _separatorElement: HTMLElement = null;
    private _rootCard: AdaptiveCard;
    private _isVisible: boolean = true;
    private _truncatedDueToOverflow: boolean = false;
    private _defaultRenderedElementDisplayMode: string = null;
    private _padding: PaddingDefinition = null;

    private internalRenderSeparator(): HTMLElement {
        return Utils.renderSeparation(
            {
                spacing: this.hostConfig.getEffectiveSpacing(this.spacing),
                lineThickness: this.separator ? this.hostConfig.separator.lineThickness : null,
                lineColor: this.separator ? this.hostConfig.separator.lineColor : null
            },
            this.separatorOrientation);
    }

    private updateRenderedElementVisibility() {
        if (this._renderedElement) {
            this._renderedElement.style.display = this._isVisible ? this._defaultRenderedElementDisplayMode : "none";
        }

        if (this._separatorElement) {
            if (this.parent && this.parent.isFirstElement(this)) {
                this._separatorElement.style.display = "none";                
            }
            else {
                this._separatorElement.style.display = this._isVisible ? this._defaultRenderedElementDisplayMode : "none";
            }
        }
    }

    private hideElementDueToOverflow() {
        if (this._renderedElement && this._isVisible) {
            this._renderedElement.style.visibility = 'hidden';
            this._isVisible = false;
            raiseElementVisibilityChangedEvent(this, false);
        }
    }

    private showElementHiddenDueToOverflow() {
        if (this._renderedElement && !this._isVisible) {
            this._renderedElement.style.visibility = null;
            this._isVisible = true;
            raiseElementVisibilityChangedEvent(this, false);
        }
    }

    // Marked private to emulate internal access
    private handleOverflow(maxHeight: number) {
        if (this.isVisible || this.isHiddenDueToOverflow()) {
            var handled = this.truncateOverflow(maxHeight);

            // Even if we were unable to truncate the element to fit this time,
            // it still could have been previously truncated
            this._truncatedDueToOverflow = handled || this._truncatedDueToOverflow;

            if (!handled) {
                this.hideElementDueToOverflow();
            }
            else if (handled && !this._isVisible) {
                this.showElementHiddenDueToOverflow();
            }
        }
    }

    // Marked private to emulate internal access
    private resetOverflow(): boolean {
        var sizeChanged = false;

        if (this._truncatedDueToOverflow) {
            this.undoOverflowTruncation();
            this._truncatedDueToOverflow = false;
            sizeChanged = true;
        }

        if (this.isHiddenDueToOverflow) {
            this.showElementHiddenDueToOverflow();
        }

        return sizeChanged;
    }

    protected createPlaceholderElement(): HTMLElement {
        var element = document.createElement("div");
        element.style.border = "1px dashed #DDDDDD";
        element.style.padding = "4px";
        element.style.minHeight = "32px";
        element.style.fontSize = "10px";
        element.innerText = "Empty " + this.getJsonTypeName();

        return element;
    }

    protected internalGetNonZeroPadding(padding: PaddingDefinition,
                                        processTop: boolean = true,
                                        processRight: boolean = true,
                                        processBottom: boolean = true,
                                        processLeft: boolean = true) {
        if (processTop) {
            if (padding.top == Enums.Spacing.None) {
                padding.top = this.internalPadding.top;
            }
        }

        if (processRight) {
            if (padding.right == Enums.Spacing.None) {
                padding.right = this.internalPadding.right;
            }
        }

        if (processBottom) {
            if (padding.bottom == Enums.Spacing.None) {
                padding.bottom = this.internalPadding.bottom;
            }
        }

        if (processLeft) {
            if (padding.left == Enums.Spacing.None) {
                padding.left = this.internalPadding.left;
            }
        }

        if (this.parent) {
            this.parent.internalGetNonZeroPadding(
                padding,
                processTop && this.isAtTheVeryTop(),
                processRight && this.isAtTheVeryRight(),
                processBottom && this.isAtTheVeryBottom(),
                processLeft && this.isAtTheVeryLeft());
        }
    }

    protected adjustRenderedElementSize(renderedElement: HTMLElement) {
        if (this.height === "auto") {
            renderedElement.style.flex = "0 0 auto";
        }
        else {
            renderedElement.style.flex = "1 1 100%";
        }
    }

    protected abstract internalRender(): HTMLElement;

    /*
     * Called when this element overflows the bottom of the card.
     * maxHeight will be the amount of space still available on the card (0 if
     * the element is fully off the card).
     */
    protected truncateOverflow(maxHeight: number): boolean {
        // Child implementations should return true if the element handled
        // the truncation request such that its content fits within maxHeight,
        // false if the element should fall back to being hidden
        return false;
    }

    /*
     * This should reverse any changes performed in truncateOverflow().
     */
    protected undoOverflowTruncation() { }

    protected isDesignMode(): boolean {
        var rootElement = this.getRootElement();
            
        return rootElement instanceof AdaptiveCard && rootElement.designMode;
    }

    protected get useDefaultSizing(): boolean {
        return true;
    }

    protected get allowCustomPadding(): boolean {
        return true;
    }

    protected get defaultPadding(): PaddingDefinition {
        return new PaddingDefinition();
    }

    protected get internalPadding(): PaddingDefinition {
        if (this._padding) {
            return this._padding;
        }
        else {
            return (this._internalPadding && this.allowCustomPadding) ? this._internalPadding : this.defaultPadding;
        }
    }

    protected set internalPadding(value: PaddingDefinition) {
        this._internalPadding = value;
    }

    protected get separatorOrientation(): Enums.Orientation {
        return Enums.Orientation.Horizontal;
    }

    protected getPadding(): PaddingDefinition {
        return this._padding;
    }

    protected setPadding(value: PaddingDefinition) {
        this._padding = value;

        if (this._padding) {
            AdaptiveCard.useAutomaticContainerBleeding = false;
        }
    }

    id: string;
    speak: string;
    horizontalAlignment?: Enums.HorizontalAlignment = null;
    spacing: Enums.Spacing = Enums.Spacing.Default;
    separator: boolean = false;
    height: "auto" | "stretch" = "auto";

    abstract getJsonTypeName(): string;
    abstract renderSpeech(): string;

    toJSON() {
        let result = {};

        Utils.setProperty(result, "type", this.getJsonTypeName());
        Utils.setProperty(result, "id", this.id);
        Utils.setEnumProperty(Enums.HorizontalAlignment, result, "horizontalAlignment", this.horizontalAlignment);
        Utils.setEnumProperty(Enums.Spacing, result, "spacing", this.spacing, Enums.Spacing.Default);
        Utils.setProperty(result, "separator", this.separator, false);
        Utils.setProperty(result, "height", this.height, "auto");

        return result;
    }

    setParent(value: CardElement) {
        this._parent = value;
    }

    getNonZeroPadding(): PaddingDefinition {
        var padding: PaddingDefinition = new PaddingDefinition();

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
        this.horizontalAlignment = Utils.getEnumValueOrDefault(Enums.HorizontalAlignment, json["horizontalAlignment"], null);

        this.spacing = Utils.getEnumValueOrDefault(Enums.Spacing, json["spacing"], Enums.Spacing.Default);
        this.separator = json["separator"];

        var jsonSeparation = json["separation"];

        if (jsonSeparation !== undefined) {
            if (jsonSeparation === "none") {
                this.spacing = Enums.Spacing.None;
                this.separator = false;
            }
            else if (jsonSeparation === "strong") {
                this.spacing = Enums.Spacing.Large;
                this.separator = true;
            }
            else if (jsonSeparation === "default") {
                this.spacing = Enums.Spacing.Default;
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

    getActionCount(): number {
        return 0;
    }

    getActionAt(index: number): Action {
        throw new Error("Index out of range.");
    }

    validate(): Array<IValidationError> {
        return [];
    }

    remove(): boolean {
        if (this.parent && this.parent instanceof CardElementContainer) {
            return this.parent.removeItem(this);
        }

        return false;
    }

    render(): HTMLElement {
        this._renderedElement = this.internalRender();
        this._separatorElement = this.internalRenderSeparator();

        if (this._renderedElement) {
            this._renderedElement.style.boxSizing = "border-box";
            this._defaultRenderedElementDisplayMode = this._renderedElement.style.display;

            this.adjustRenderedElementSize(this._renderedElement);
            this.updateLayout(false);
        }
        else if (this.isDesignMode()) {
            this._renderedElement = this.createPlaceholderElement();
        }

        return this._renderedElement;
    }

    updateLayout(processChildren: boolean = true) {
        this.updateRenderedElementVisibility();
    }

    isRendered(): boolean {
        return this._renderedElement && this._renderedElement.offsetHeight > 0;
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

    isBleeding(): boolean {
        return false;
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

    isHiddenDueToOverflow(): boolean {
        return this._renderedElement && this._renderedElement.style.visibility == 'hidden';
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

    get lang(): string {
        if (this._lang) {
            return this._lang;
        }
        else {
            if (this.parent) {
                return this.parent.lang;
            }
            else {
                return undefined;
            }
        }
    }

    set lang(value: string) {
        if (value && value != "") {
            var regEx = /^[a-z]{2,3}$/ig;

            var matches = regEx.exec(value);

            if (!matches) {
                throw new Error("Invalid language identifier: " + value);
            }
        }

        this._lang = value;
    }

    get hostConfig(): HostConfig.HostConfig {
        if (this._hostConfig) {
            return this._hostConfig;
        }
        else {
            if (this.parent) {
                return this.parent.hostConfig;
            }
            else {
                return defaultHostConfig;
            }
        }
    }

    set hostConfig(value: HostConfig.HostConfig) {
        this._hostConfig = value;
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
        return this._isVisible;
    }

    get hasVisibleSeparator(): boolean {
        var parentContainer = this.getParentContainer();

        if (parentContainer) {
            return this.separatorElement && !parentContainer.isFirstElement(this);
        }
        else {
            return false;
        }
    }

    set isVisible(value: boolean) {
        // If the element is going to be hidden, reset any changes that were due
        // to overflow truncation (this ensures that if the element is later
        // un-hidden it has the right content)
        if (AdaptiveCard.useAdvancedCardBottomTruncation && !value) {
            this.undoOverflowTruncation();
        }

        if (this._isVisible != value) {
            this._isVisible = value;

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
    private _computedLineHeight: number;
    private _originalInnerHtml: string;
    private _text: string;
    private _processedText: string = null;

    private restoreOriginalContent() {
        var maxHeight = this.maxLines
            ? (this._computedLineHeight * this.maxLines) + 'px'
            : null;

        this.renderedElement.style.maxHeight = maxHeight;
        this.renderedElement.innerHTML = this._originalInnerHtml;
    }

    private truncateIfSupported(maxHeight: number): boolean {
        // For now, only truncate TextBlocks that contain just a single
        // paragraph -- since the maxLines calculation doesn't take into
        // account Markdown lists
        var children = this.renderedElement.children;
        var isTextOnly = !children.length;

        var truncationSupported = isTextOnly || children.length == 1
            && (<HTMLElement>children[0]).tagName.toLowerCase() == 'p';

        if (truncationSupported) {
            var element = isTextOnly
                ? this.renderedElement
                : <HTMLElement>children[0];

            Utils.truncate(element, maxHeight, this._computedLineHeight);
            return true;
        }

        return false;
    }

    protected internalRender(): HTMLElement {
        if (!Utils.isNullOrEmpty(this.text)) {
            var element = document.createElement("div");
            element.style.overflow = "hidden";

            if (this.hostConfig.fontFamily) {
                element.style.fontFamily = this.hostConfig.fontFamily;
            }

            switch (this.horizontalAlignment) {
                case Enums.HorizontalAlignment.Center:
                    element.style.textAlign = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.style.textAlign = "right";
                    break;
                default:
                    element.style.textAlign = "left";
                    break;
            }

            var cssStyle = "text ";
            var fontSize: number;

            switch (this.size) {
                case Enums.TextSize.Small:
                    fontSize = this.hostConfig.fontSizes.small;
                    break;
                case Enums.TextSize.Medium:
                    fontSize = this.hostConfig.fontSizes.medium;
                    break;
                case Enums.TextSize.Large:
                    fontSize = this.hostConfig.fontSizes.large;
                    break;
                case Enums.TextSize.ExtraLarge:
                    fontSize = this.hostConfig.fontSizes.extraLarge;
                    break;
                default:
                    fontSize = this.hostConfig.fontSizes.default;
                    break;
            }

            if (this.hostConfig.lineHeights) {
                switch (this.size) {
                    case Enums.TextSize.Small:
                        this._computedLineHeight = this.hostConfig.lineHeights.small;
                        break;
                    case Enums.TextSize.Medium:
                        this._computedLineHeight = this.hostConfig.lineHeights.medium;
                        break;
                    case Enums.TextSize.Large:
                        this._computedLineHeight = this.hostConfig.lineHeights.large;
                        break;
                    case Enums.TextSize.ExtraLarge:
                        this._computedLineHeight = this.hostConfig.lineHeights.extraLarge;
                        break;
                    default:
                        this._computedLineHeight = this.hostConfig.lineHeights.default;
                        break;    
                }
            }
            else {
                // Looks like 1.33 is the magic number to compute line-height
                // from font size.
                this._computedLineHeight = fontSize * 1.33;                
            }

            element.style.fontSize = fontSize + "px";
            element.style.lineHeight = this._computedLineHeight + "px";

            var parentContainer = this.getParentContainer();
            var styleDefinition = this.hostConfig.containerStyles.getStyleByName(parentContainer ? parentContainer.style : Enums.ContainerStyle.Default, this.hostConfig.containerStyles.default);

            var actualTextColor = this.color ? this.color : Enums.TextColor.Default;
            var colorDefinition: HostConfig.TextColorDefinition;

            switch (actualTextColor) {
                case Enums.TextColor.Accent:
                    colorDefinition = styleDefinition.foregroundColors.accent;
                    break;
                case Enums.TextColor.Dark:
                    colorDefinition = styleDefinition.foregroundColors.dark;
                    break;
                case Enums.TextColor.Light:
                    colorDefinition = styleDefinition.foregroundColors.light;
                    break;
                case Enums.TextColor.Good:
                    colorDefinition = styleDefinition.foregroundColors.good;
                    break;
                case Enums.TextColor.Warning:
                    colorDefinition = styleDefinition.foregroundColors.warning;
                    break;
                case Enums.TextColor.Attention:
                    colorDefinition = styleDefinition.foregroundColors.attention;
                    break;
                default:
                    colorDefinition = styleDefinition.foregroundColors.default;
                    break;
            }

            element.style.color = Utils.stringToCssColor(this.isSubtle ? colorDefinition.subtle : colorDefinition.default);

            var fontWeight: number;

            switch (this.weight) {
                case Enums.TextWeight.Lighter:
                    fontWeight = this.hostConfig.fontWeights.lighter;
                    break;
                case Enums.TextWeight.Bolder:
                    fontWeight = this.hostConfig.fontWeights.bolder;
                    break;
                default:
                    fontWeight = this.hostConfig.fontWeights.default;
                    break;
            }

            element.style.fontWeight = fontWeight.toString();

            if (!this._processedText) {
                var formattedText = TextFormatters.formatText(this.lang, this.text);

                this._processedText = this.useMarkdown ? AdaptiveCard.processMarkdown(formattedText) : formattedText;
            }

            element.innerHTML = this._processedText;

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
                var anchor = <HTMLAnchorElement>anchors[i];
                anchor.classList.add(this.hostConfig.makeCssClassName("ac-anchor"));
                anchor.target = "_blank";
                anchor.onclick = (e) => {
                    if (raiseAnchorClickedEvent(this, e.target as HTMLAnchorElement)) {
                        e.preventDefault();
                    }
                }
            }

            if (this.wrap) {
                element.style.wordWrap = "break-word";

                if (this.maxLines > 0) {
                    element.style.maxHeight = (this._computedLineHeight * this.maxLines) + "px";
                    element.style.overflow = "hidden";
                }
            }
            else {
                element.style.whiteSpace = "nowrap";
                element.style.textOverflow = "ellipsis";
            }

            if (AdaptiveCard.useAdvancedTextBlockTruncation
                || AdaptiveCard.useAdvancedCardBottomTruncation) {
                this._originalInnerHtml = element.innerHTML;
            }

            return element;
        }
        else {
            return null;
        }
    }

    protected truncateOverflow(maxHeight: number): boolean {
        if (maxHeight >= this._computedLineHeight) {
            return this.truncateIfSupported(maxHeight);
        }

        return false;
    }

    protected undoOverflowTruncation() {
        this.restoreOriginalContent();

        if (AdaptiveCard.useAdvancedTextBlockTruncation && this.maxLines) {
            var maxHeight = this._computedLineHeight * this.maxLines;
            this.truncateIfSupported(maxHeight);
        }
    }

    size: Enums.TextSize = Enums.TextSize.Default;
    weight: Enums.TextWeight = Enums.TextWeight.Default;
    color: Enums.TextColor = Enums.TextColor.Default;
    isSubtle: boolean = false;
    wrap: boolean = false;
    maxLines: number;
    useMarkdown: boolean = true;

    toJSON() {
        let result = super.toJSON();

        Utils.setEnumProperty(Enums.TextSize, result, "size", this.size, Enums.TextSize.Default);
        Utils.setEnumProperty(Enums.TextWeight, result, "weight", this.weight, Enums.TextWeight.Default);
        Utils.setEnumProperty(Enums.TextColor, result, "color", this.color, Enums.TextColor.Default);
        Utils.setProperty(result, "text", this.text);
        Utils.setProperty(result, "isSubtle", this.isSubtle, false);
        Utils.setProperty(result, "wrap", this.wrap, false);
        Utils.setProperty(result, "maxLines", this.maxLines, 0);

        return result;
    }

    parse(json: any) {
        super.parse(json);

        this.text = json["text"];

        var sizeString = json["size"];

        if (sizeString && typeof sizeString === "string" && sizeString.toLowerCase() === "normal") {
            this.size = Enums.TextSize.Default;

            raiseParseError(
                {
                    error: Enums.ValidationError.Deprecated,
                    message: "The TextBlock.size value \"normal\" is deprecated and will be removed. Use \"default\" instead."
                });
        }
        else {
            this.size = Utils.getEnumValueOrDefault(Enums.TextSize, sizeString, this.size);
        }

        var weightString = json["weight"];

        if (weightString && typeof weightString === "string" && weightString.toLowerCase() === "normal") {
            this.weight = Enums.TextWeight.Default;

            raiseParseError(
                {
                    error: Enums.ValidationError.Deprecated,
                    message: "The TextBlock.weight value \"normal\" is deprecated and will be removed. Use \"default\" instead."
                });
        }
        else {
            this.weight = Utils.getEnumValueOrDefault(Enums.TextWeight, weightString, this.weight);
        }

        this.color = Utils.getEnumValueOrDefault(Enums.TextColor, json["color"], this.color);
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

    updateLayout(processChildren: boolean = false) {
        super.updateLayout(processChildren);

        if (AdaptiveCard.useAdvancedTextBlockTruncation && this.maxLines && this.isRendered()) {
            // Reset the element's innerHTML in case the available room for
            // content has increased
            this.restoreOriginalContent();
            var maxHeight = this._computedLineHeight * this.maxLines;
            this.truncateIfSupported(maxHeight);
        }
    }

    get text(): string {
        return this._text;
    }

    set text(value: string) {
        if (this._text != value) {
            this._text = value;

            this._processedText = null;
        }
    }
}

export class Fact {
    name: string;
    value: string;
    speak: string;

    constructor(name: string = undefined, value: string = undefined) {
        this.name = name;
        this.value = value;
    }

    toJSON() {
        return { title: this.name, value: this.value };
    }

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
                    trElement.style.marginTop = this.hostConfig.factSet.spacing + "px";
                }

                var tdElement = document.createElement("td");
                tdElement.style.padding = "0";

                if (this.hostConfig.factSet.title.maxWidth) {
                    tdElement.style.maxWidth = this.hostConfig.factSet.title.maxWidth + "px";
                }

                tdElement.style.verticalAlign = "top";

                var textBlock = new TextBlock();
                textBlock.hostConfig = this.hostConfig;
                textBlock.text = Utils.isNullOrEmpty(this.facts[i].name) ? "Title" : this.facts[i].name;
                textBlock.size = this.hostConfig.factSet.title.size;
                textBlock.color = this.hostConfig.factSet.title.color;
                textBlock.isSubtle = this.hostConfig.factSet.title.isSubtle;
                textBlock.weight = this.hostConfig.factSet.title.weight;
                textBlock.wrap = this.hostConfig.factSet.title.wrap;
                textBlock.spacing = Enums.Spacing.None;

                Utils.appendChild(tdElement, textBlock.render());
                Utils.appendChild(trElement, tdElement);

                tdElement = document.createElement("td");
                tdElement.style.padding = "0px 0px 0px 10px";
                tdElement.style.verticalAlign = "top";

                textBlock = new TextBlock();
                textBlock.hostConfig = this.hostConfig;
                textBlock.text = Utils.isNullOrEmpty(this.facts[i].value) ? "Value" : this.facts[i].value;
                textBlock.size = this.hostConfig.factSet.value.size;
                textBlock.color = this.hostConfig.factSet.value.color;
                textBlock.isSubtle = this.hostConfig.factSet.value.isSubtle;
                textBlock.weight = this.hostConfig.factSet.value.weight;
                textBlock.wrap = this.hostConfig.factSet.value.wrap;
                textBlock.spacing = Enums.Spacing.None;

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

    toJSON() {
        let result = super.toJSON();

        let facts = []

        for (let fact of this.facts) {
            facts.push(fact.toJSON());
        }

        Utils.setProperty(result, "facts", facts);

        return result;
    }

    parse(json: any) {
        super.parse(json);

        this.facts = [];

        if (json["facts"] != null) {
            var jsonFacts = json["facts"] as Array<any>;
            this.facts = [];
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
    private _selectAction: Action;

    private parseDimension(name: string, value: any): number {
        if (value) {
            if (typeof value === "string") {
                try {
                    let size = Utils.SizeAndUnit.parse(value);

                    if (size.unit == Enums.SizeUnit.Pixel) {
                        return size.physicalSize;
                    }
                }
                catch {
                    // Ignore error
                }
            }

            raiseParseError(
                {
                    error: Enums.ValidationError.InvalidPropertyValue,
                    message: "Invalid image " + name + ": " + value
                });    
        }

        return 0;
    }

    private applySize(element: HTMLElement) {
        if (this.pixelWidth || this.pixelHeight) {
            if (this.pixelWidth) {
                element.style.width = this.pixelWidth + "px";
            }

            if (this.pixelHeight) {
                element.style.height = this.pixelHeight + "px";
            }
        }
        else {
            switch (this.size) {
                case Enums.Size.Stretch:
                    element.style.width = "100%";
                    break;
                case Enums.Size.Auto:
                    element.style.maxWidth = "100%";
                    break;
                case Enums.Size.Small:
                    element.style.width = this.hostConfig.imageSizes.small + "px";
                    break;
                case Enums.Size.Large:
                    element.style.width = this.hostConfig.imageSizes.large + "px";
                    break;
                case Enums.Size.Medium:
                    element.style.width = this.hostConfig.imageSizes.medium + "px";
                    break;
            }
        }    
    }

    protected get useDefaultSizing() {
        return false;
    }

    protected internalRender(): HTMLElement {
        var element: HTMLElement = null;

        if (!Utils.isNullOrEmpty(this.url)) {
            element = document.createElement("div");
            element.style.display = "flex";
            element.style.alignItems = "flex-start";

            element.onkeypress = (e) => {
                if (this.selectAction) {
                    if (e.keyCode == 13 || e.keyCode == 32) { // enter or space pressed
                        this.selectAction.execute();
                    }
                }
            }

            element.onclick = (e) => {
                if (this.selectAction) {
                    this.selectAction.execute();
                    e.cancelBubble = true;
                }
            }

            switch (this.horizontalAlignment) {
                case Enums.HorizontalAlignment.Center:
                    element.style.justifyContent = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.style.justifyContent = "flex-end";
                    break;
                default:
                    element.style.justifyContent = "flex-start";
                    break;
            }

            // Cache hostConfig to avoid walking the parent hierarchy multiple times
            let hostConfig = this.hostConfig;

            let imageElement = document.createElement("img");
            imageElement.onload = (e: Event) => {
                raiseImageLoadedEvent(this);
            }
            imageElement.onerror = (e: Event) => {
                let card = this.getRootElement() as AdaptiveCard;

                this.renderedElement.innerHTML = "";

                if (card && card.designMode) {
                    let errorElement = document.createElement("div");
                    errorElement.style.display = "flex";
                    errorElement.style.alignItems = "center";
                    errorElement.style.justifyContent = "center";
                    errorElement.style.backgroundColor = "#EEEEEE";
                    errorElement.style.color = "black";
                    errorElement.innerText = ":-(";
                    errorElement.style.padding = "10px";

                    this.applySize(errorElement);

                    this.renderedElement.appendChild(errorElement);
                }

                raiseImageLoadedEvent(this);
            }
            imageElement.style.maxHeight = "100%";
            imageElement.style.minWidth = "0";
            imageElement.classList.add(hostConfig.makeCssClassName("ac-image"));

            if (this.selectAction != null && hostConfig.supportsInteractivity) {
                imageElement.tabIndex = 0
                imageElement.setAttribute("role", "button");
                imageElement.setAttribute("aria-label", this.selectAction.title);
                imageElement.classList.add(hostConfig.makeCssClassName("ac-selectable"));
            }

            this.applySize(imageElement);

            if (this.style === Enums.ImageStyle.Person) {
                imageElement.style.borderRadius = "50%";
                imageElement.style.backgroundPosition = "50% 50%";
                imageElement.style.backgroundRepeat = "no-repeat";
            }

            if (!Utils.isNullOrEmpty(this.backgroundColor)) {
                imageElement.style.backgroundColor = Utils.stringToCssColor(this.backgroundColor);
            }

            imageElement.src = this.url;
            imageElement.alt = this.altText;

            element.appendChild(imageElement);
        }

        return element;
    }

    style: Enums.ImageStyle = Enums.ImageStyle.Default;
    backgroundColor: string;
    url: string;
    size: Enums.Size = Enums.Size.Auto;
    width: Utils.SizeAndUnit;
    pixelWidth?: number = null;
    pixelHeight?: number = null;
    altText: string = "";

    toJSON() {
        let result = super.toJSON();

        if (this._selectAction) {
            Utils.setProperty(result, "selectAction", this._selectAction.toJSON());
        }

        Utils.setEnumProperty(Enums.ImageStyle, result, "style", this.style, Enums.ImageStyle.Default);
        Utils.setProperty(result, "backgroundColor", this.backgroundColor);
        Utils.setProperty(result, "url", this.url);
        Utils.setEnumProperty(Enums.Size, result, "size", this.size, Enums.Size.Auto);

        if (this.pixelWidth) {
            Utils.setProperty(result, "width", this.pixelWidth + "px");
        }

        if (this.pixelHeight) {
            Utils.setProperty(result, "height", this.pixelHeight + "px");
        }

        Utils.setProperty(result, "altText", this.altText);

        return result;
    }

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

        var styleString = json["style"];

        if (styleString && typeof styleString === "string" && styleString.toLowerCase() === "normal") {
            this.style = Enums.ImageStyle.Default;

            raiseParseError(
                {
                    error: Enums.ValidationError.Deprecated,
                    message: "The Image.style value \"normal\" is deprecated and will be removed. Use \"default\" instead."
                });
        }
        else {
            this.style = Utils.getEnumValueOrDefault(Enums.ImageStyle, styleString, this.style);
        }

        this.size = Utils.getEnumValueOrDefault(Enums.Size, json["size"], this.size);
        this.altText = json["altText"];

        // pixelWidth and pixelHeight are only parsed for backwards compatibility.
        // Payloads should use the width and height proerties instead.
        if (json["pixelWidth"] && typeof json["pixelWidth"] === "number") {
            this.pixelWidth = json["pixelWidth"];

            raiseParseError(
                {
                    error: Enums.ValidationError.Deprecated,
                    message: "The pixelWidth property is deprecated and will be removed. Use the width property instead."
                });
        }

        if (json["pixelHeight"] && typeof json["pixelHeight"] === "number") {
            this.pixelHeight = json["pixelHeight"];

            raiseParseError(
                {
                    error: Enums.ValidationError.Deprecated,
                    message: "The pixelHeight property is deprecated and will be removed. Use the height property instead."
                });
        }

        let size = this.parseDimension("width", json["width"]);

        if (size > 0) {
            this.pixelWidth = size;
        }

        size = this.parseDimension("height", json["height"]);

        if (size > 0) {
            this.pixelHeight = size;
        }

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            this.selectAction = createActionInstance(selectActionJson);

            if (this.selectAction) {
                this.selectAction.setParent(this);
                this.selectAction.parse(selectActionJson);
            }
        }
    }

    renderSpeech(): string {
        if (this.speak != null) {
            return this.speak + '\n';
        }

        return null;
    }

    get selectAction(): Action {
        return this._selectAction;
    }

    set selectAction(value: Action) {
        this._selectAction = value;

        if (this._selectAction) {
            this._selectAction.setParent(this);
        }
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
                renderedImage.style.maxHeight = this.hostConfig.imageSet.maxImageHeight + "px";

                Utils.appendChild(element, renderedImage);
            }
        }

        return element;
    }

    imageSize: Enums.Size = Enums.Size.Medium;

    getJsonTypeName(): string {
        return "ImageSet";
    }

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "imageSize", this.imageSize, Enums.Size.Medium);

        if (this._images.length > 0) {
            let images = [];

            for (let image of this._images) {
                images.push(image.toJSON());
            }

            Utils.setProperty(result, "images", images);
        }

        return result;
    }

    parse(json: any) {
        super.parse(json);

        this.imageSize = Utils.getEnumValueOrDefault(Enums.Size, json["imageSize"], Enums.Size.Medium);

        if (json["images"] != null) {
            let jsonImages = json["images"] as Array<any>;
            this._images = [];
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

            image.setParent(this);
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
    protected valueChanged() {
        if (this.onValueChanged) {
            this.onValueChanged(this);
        }
    }

    abstract get value(): string;

    onValueChanged: (sender: Input) => void;

    title: string;
    defaultValue: string;

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "title", this.title);
        Utils.setProperty(result, "value", this.renderedElement ? this.value : this.defaultValue);

        return result;
    }

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
            this._textareaElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-textInput", "ac-multiline");
            this._textareaElement.style.width = "100%";
            this._textareaElement.tabIndex = 0;

            if (!Utils.isNullOrEmpty(this.placeholder)) {
                this._textareaElement.placeholder = this.placeholder;
                this._textareaElement.setAttribute("aria-label", this.placeholder)
            }

            if (!Utils.isNullOrEmpty(this.defaultValue)) {
                this._textareaElement.value = this.defaultValue;
            }

            if (this.maxLength > 0) {
                this._textareaElement.maxLength = this.maxLength;
            }

            this._textareaElement.oninput = () => { this.valueChanged(); }

            return this._textareaElement;
        }
        else {
            this._inputElement = document.createElement("input");
            this._inputElement.type = Enums.InputTextStyle[this.style].toLowerCase();
            this._inputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-textInput");
            this._inputElement.style.width = "100%";
            this._inputElement.tabIndex = 0;

            if (!Utils.isNullOrEmpty(this.placeholder)) {
                this._inputElement.placeholder = this.placeholder;
                this._inputElement.setAttribute("aria-label", this.placeholder)
            }

            if (!Utils.isNullOrEmpty(this.defaultValue)) {
                this._inputElement.value = this.defaultValue;
            }

            if (this.maxLength > 0) {
                this._inputElement.maxLength = this.maxLength;
            }

            this._inputElement.oninput = () => { this.valueChanged(); }

            return this._inputElement;
        }
    }

    maxLength: number;
    isMultiline: boolean;
    placeholder: string;
    style: Enums.InputTextStyle = Enums.InputTextStyle.Text;

    getJsonTypeName(): string {
        return "Input.Text";
    }

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "placeholder", this.placeholder);
        Utils.setProperty(result, "maxLength", this.maxLength, 0);
        Utils.setProperty(result, "isMultiline", this.isMultiline, false);
        Utils.setProperty(result, "style", this.style, Enums.InputTextStyle.Text);

        return result;
    }

    parse(json: any) {
        super.parse(json);

        this.maxLength = json["maxLength"];
        this.isMultiline = json["isMultiline"];
        this.placeholder = json["placeholder"];
        this.style =  Utils.getEnumValueOrDefault(Enums.InputTextStyle, json["style"], this.style);
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
        element.className = this.hostConfig.makeCssClassName("ac-input");
        element.style.width = "100%";
        element.style.display = "flex";

        this._checkboxInputElement = document.createElement("input");
        this._checkboxInputElement.type = "checkbox";
        this._checkboxInputElement.style.display = "inline-block";
        this._checkboxInputElement.style.verticalAlign = "middle";
        this._checkboxInputElement.style.margin = "0";
        this._checkboxInputElement.style.flex = "0 0 auto";
        this._checkboxInputElement.setAttribute("aria-label", this.title);
        this._checkboxInputElement.tabIndex = 0;

        if (this.defaultValue == this.valueOn) {
            this._checkboxInputElement.checked = true;
        }

        this._checkboxInputElement.onchange = () => { this.valueChanged(); }

        var label = new TextBlock();
        label.hostConfig = this.hostConfig;
        label.text = Utils.isNullOrEmpty(this.title) ? this.getJsonTypeName() : this.title;
        label.useMarkdown = AdaptiveCard.useMarkdownInRadioButtonAndCheckbox;

        var labelElement = label.render();
        labelElement.style.display = "inline-block";
        labelElement.style.marginLeft = "6px";
        labelElement.style.verticalAlign = "middle";

        var compoundInput = document.createElement("div");

        Utils.appendChild(element, this._checkboxInputElement);
        Utils.appendChild(element, labelElement);

        return element;
    }

    valueOn: string = "true";
    valueOff: string = "false";

    getJsonTypeName(): string {
        return "Input.Toggle";
    }

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "valueOn", this.valueOn, "true");
        Utils.setProperty(result, "valueOff", this.valueOff, "false");

        return result;
    }

    parse(json: any) {
        super.parse(json);

        this.title = json["title"];

        this.valueOn = Utils.getValueOrDefault<string>(json["valueOn"], this.valueOn);
        this.valueOff = Utils.getValueOrDefault<string>(json["valueOff"], this.valueOff);
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

    constructor(title: string = undefined, value: string = undefined) {
        this.title = title;
        this.value = value;
    }

    toJSON() {
        return { title: this.title, value: this.value };
    }
}

export class ChoiceSetInput extends Input {
    private _selectElement: HTMLSelectElement;
    private _toggleInputs: Array<HTMLInputElement>;

    protected internalRender(): HTMLElement {
        if (!this.isMultiSelect) {
            if (this.isCompact) {
                // Render as a combo box
                this._selectElement = document.createElement("select");
                this._selectElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-multichoiceInput");
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
                    option.setAttribute("aria-label", this.choices[i].title);

                    if (this.choices[i].value == this.defaultValue) {
                        option.selected = true;
                    }

                    Utils.appendChild(this._selectElement, option);
                }

                this._selectElement.onchange = () => { this.valueChanged(); }

                return this._selectElement;
            }
            else {
                // Render as a series of radio buttons
                var element = document.createElement("div");
                element.className = this.hostConfig.makeCssClassName("ac-input");
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
                    radioInput.style.flex = "0 0 auto";
                    radioInput.setAttribute("aria-label", this.choices[i].title);

                    if (this.choices[i].value == this.defaultValue) {
                        radioInput.checked = true;
                    }

                    radioInput.onchange = () => { this.valueChanged(); }

                    this._toggleInputs.push(radioInput);

                    var label = new TextBlock();
                    label.hostConfig = this.hostConfig;
                    label.text = Utils.isNullOrEmpty(this.choices[i].title) ? "Choice " + i : this.choices[i].title;
                    label.useMarkdown = AdaptiveCard.useMarkdownInRadioButtonAndCheckbox;

                    var labelElement = label.render();
                    labelElement.style.display = "inline-block";
                    labelElement.style.marginLeft = "6px";
                    labelElement.style.verticalAlign = "middle";

                    var compoundInput = document.createElement("div");
                    compoundInput.style.display = "flex";

                    Utils.appendChild(compoundInput, radioInput);
                    Utils.appendChild(compoundInput, labelElement);

                    Utils.appendChild(element, compoundInput);
                }

                return element;
            }
        }
        else {
            // Render as a list of toggle inputs
            var defaultValues = this.defaultValue ? this.defaultValue.split(this.hostConfig.choiceSetInputValueSeparator) : null;

            var element = document.createElement("div");
            element.className = this.hostConfig.makeCssClassName("ac-input");
            element.style.width = "100%";

            this._toggleInputs = [];

            for (var i = 0; i < this.choices.length; i++) {
                var checkboxInput = document.createElement("input");
                checkboxInput.type = "checkbox";
                checkboxInput.style.margin = "0";
                checkboxInput.style.display = "inline-block";
                checkboxInput.style.verticalAlign = "middle";
                checkboxInput.value = this.choices[i].value;
                checkboxInput.style.flex = "0 0 auto";
                checkboxInput.setAttribute("aria-label", this.choices[i].title);

                if (defaultValues) {
                    if (defaultValues.indexOf(this.choices[i].value) >= 0) {
                        checkboxInput.checked = true;
                    }
                }

                checkboxInput.onchange = () => { this.valueChanged(); }

                this._toggleInputs.push(checkboxInput);

                var label = new TextBlock();
                label.hostConfig = this.hostConfig;
                label.text = Utils.isNullOrEmpty(this.choices[i].title) ? "Choice " + i : this.choices[i].title;
                label.useMarkdown = AdaptiveCard.useMarkdownInRadioButtonAndCheckbox;

                var labelElement = label.render();
                labelElement.style.display = "inline-block";
                labelElement.style.marginLeft = "6px";
                labelElement.style.verticalAlign = "middle";

                var compoundInput = document.createElement("div");
                compoundInput.style.display = "flex";

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

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "placeholder", this.placeholder);

        if (this.choices.length > 0) {
            var choices = [];

            for (let choice of this.choices) {
                choices.push(choice.toJSON());
            }

            Utils.setProperty(result, "choices", choices);
        }

        Utils.setProperty(result, "isCompact", this.isCompact, false);
        Utils.setProperty(result, "isMultiSelect", this.isMultiSelect, false);

        return result;
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

        this.choices = [];

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
                        result += this.hostConfig.choiceSetInputValueSeparator;
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
        this._numberInputElement.setAttribute("type", "number");
        this._numberInputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-numberInput");
        this._numberInputElement.setAttribute("min", this.min);
        this._numberInputElement.setAttribute("max", this.max);
        this._numberInputElement.style.width = "100%";
        this._numberInputElement.tabIndex = 0;

        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._numberInputElement.value = this.defaultValue;
        }

        if (!Utils.isNullOrEmpty(this.placeholder)) {
            this._numberInputElement.placeholder = this.placeholder;
            this._numberInputElement.setAttribute("aria-label", this.placeholder);
        }

        this._numberInputElement.oninput = () => { this.valueChanged(); }

        return this._numberInputElement;
    }

    min: string;
    max: string;
    placeholder: string;

    getJsonTypeName(): string {
        return "Input.Number";
    }

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "placeholder", this.placeholder);
        Utils.setProperty(result, "min", this.min);
        Utils.setProperty(result, "max", this.max);

        return result;
    }

    parse(json: any) {
        super.parse(json);

        this.placeholder = json["placeholder"];
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
        this._dateInputElement.setAttribute("type", "date");
        this._dateInputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-dateInput");
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
        this._timeInputElement.setAttribute("type", "time");
        this._timeInputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-timeInput");
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
    private _element: HTMLButtonElement = null;
    private _state: ActionButtonState = ActionButtonState.Normal;

    private updateCssStyle() {
        let hostConfig = this.action.parent.hostConfig;

        this.action.renderedElement.classList.remove(hostConfig.makeCssClassName("expanded"));
        this.action.renderedElement.classList.remove(hostConfig.makeCssClassName("subdued"));

        switch (this._state) {
            case ActionButtonState.Expanded:
                this.action.renderedElement.classList.add(hostConfig.makeCssClassName("expanded"));
                break;
            case ActionButtonState.Subdued:
                this.action.renderedElement.classList.add(hostConfig.makeCssClassName("subdued"));
                break;
        }

        if (this.action.isPrimary) {
            this.action.renderedElement.classList.add(hostConfig.makeCssClassName("primary"));
        }

    }

    readonly action: Action;

    constructor(action: Action) {
        this.action = action;

        this.action.render();
        this.action.renderedElement.onclick = (e) => { this.click(); };

        this.updateCssStyle();
    }

    onClick: (actionButton: ActionButton) => void = null;

    click() {
        if (this.onClick != null) {
            this.onClick(this);
        }
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
    private _parent: CardElement = null;
    private _actionCollection: ActionCollection = null; // hold the reference to its action collection
    private _renderedElement: HTMLElement = null;

    private setCollection(actionCollection: ActionCollection) {
        this._actionCollection = actionCollection;
    }

    protected addCssClasses(element: HTMLElement) {
        // Do nothing in base implementation
    }

    abstract getJsonTypeName(): string;

    id: string;
    title: string;
    iconUrl: string;
    isPrimary: boolean;

    toJSON() {
        let result = {};

        Utils.setProperty(result, "type", this.getJsonTypeName());
        Utils.setProperty(result, "id", this.id);
        Utils.setProperty(result, "title", this.title);
        Utils.setProperty(result, "iconUrl", this.iconUrl);

        return result;
    }

    render() {
        // Cache hostConfig for perf
        let hostConfig = this.parent.hostConfig;

        var buttonElement = document.createElement("button");
        buttonElement.className = hostConfig.makeCssClassName("ac-pushButton");

        this.addCssClasses(buttonElement);

        buttonElement.setAttribute("aria-label", this.title);
        buttonElement.type = "button";
        buttonElement.style.display = "flex";
        buttonElement.style.alignItems = "center";
        buttonElement.style.justifyContent = "center";

        let hasTitle = !Utils.isNullOrEmpty(this.title);

        if (Utils.isNullOrEmpty(this.iconUrl)) {
            buttonElement.classList.add("noIcon");
            buttonElement.style.overflow = "hidden";
            buttonElement.style.whiteSpace = "nowrap";
            buttonElement.style.textOverflow = "ellipsis";

            if (hasTitle) {
                buttonElement.innerText = this.title;
            }
        }
        else {
            let iconElement = document.createElement("div");
            iconElement.style.width = hostConfig.actions.iconSize + "px";
            iconElement.style.height = hostConfig.actions.iconSize + "px";;
            iconElement.style.backgroundImage = "url('" + this.iconUrl + "')";
            iconElement.style.backgroundPositionX = "center";
            iconElement.style.backgroundPositionY = "center";
            iconElement.style.backgroundRepeat = "no-repeat";
            iconElement.style.backgroundSize = "contain";

            let titleElement = document.createElement("div");

            if (hasTitle) {
                titleElement.innerText = this.title;
            }

            if (hostConfig.actions.iconPlacement == Enums.ActionIconPlacement.AboveTitle) {
                buttonElement.classList.add("iconAbove");
                buttonElement.style.flexDirection = "column";

                if (hasTitle) {
                    iconElement.style.marginBottom = "4px";
                }
            }
            else {
                buttonElement.classList.add("iconLeft");
                
                if (hasTitle) {
                    iconElement.style.marginRight = "4px";
                }
            }

            buttonElement.appendChild(iconElement);
            buttonElement.appendChild(titleElement);
        }

        this._renderedElement = buttonElement;
    }

    setParent(value: CardElement) {
        this._parent = value;
    }

    execute() {
        raiseExecuteActionEvent(this);
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
        raiseParseActionEvent(this, json);
	    
        this.id = json["id"];
        this.title = json["title"];
        this.iconUrl = json["iconUrl"];
    }

    remove(): boolean {
        if (this._actionCollection) {
            return this._actionCollection.removeAction(this);
        }

        return false;
    }

    getAllInputs(): Array<Input> {
        return [];
    }

    getActionById(id: string): Action {
        if (this.id == id) {
            return this;
        }
    }

    get parent(): CardElement {
        return this._parent;
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;
    }
}

export class SubmitAction extends Action {
    private _isPrepared: boolean = false;
    private _originalData: Object;
    private _processedData: Object;

    getJsonTypeName(): string {
        return "Action.Submit";
    }

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "data", this._originalData);

        return result;
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

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "url", this.url);

        return result;
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

    toJSON() {
        return { name: this.name, value: this._value.getOriginal() };
    }

    prepare(inputs: Array<Input>) {
        this._value.substituteInputValues(inputs, Utils.ContentTypes.applicationXWwwFormUrlencoded);
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

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "method", this.method);
        Utils.setProperty(result, "url", this._url.getOriginal());
        Utils.setProperty(result, "body", this._body.getOriginal());

        if (this._headers.length > 0) {
            let headers = [];

            for (let header of this._headers) {
                headers.push(header.toJSON());
            }

            Utils.setProperty(result, "headers", headers);
        }

        return result;
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
        this._url.substituteInputValues(inputs, Utils.ContentTypes.applicationXWwwFormUrlencoded);

        let contentType = Utils.ContentTypes.applicationJson;

        for (var i = 0; i < this._headers.length; i++) {
            this._headers[i].prepare(inputs);

            if (this._headers[i].name && this._headers[i].name.toLowerCase() == "content-type") {
                contentType = this._headers[i].value;
            }
        }

        this._body.substituteInputValues(inputs, contentType);
    };

    parse(json: any) {
        super.parse(json);

        this.url = json["url"];
        this.method = json["method"];
        this.body = json["body"];

        this._headers = [];

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
    protected addCssClasses(element: HTMLElement) {
        super.addCssClasses(element);

        element.classList.add(this.parent.hostConfig.makeCssClassName("expandable"));
    }

    readonly card: AdaptiveCard = new InlineAdaptiveCard();

    getJsonTypeName(): string {
        return "Action.ShowCard";
    }

    toJSON() {
        let result = super.toJSON();

        if (this.card) {
            Utils.setProperty(result, "card", this.card.toJSON());
        }

        return result;
    }

    validate(): Array<IValidationError> {
        return this.card.validate();
    }

    parse(json: any) {
        super.parse(json);

        this.card.parse(json["card"]);
    }

    setParent(value: CardElement) {
        super.setParent(value);

        this.card.setParent(value);
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
    private _actionCardContainer: HTMLDivElement;
    private _expandedAction: ShowCardAction = null;
    private _renderedActionCount: number = 0;
    private _statusCard: HTMLElement = null;
    private _actionCard: HTMLElement = null;

    private isActionCardContainerVisible(): boolean {
        return this._actionCardContainer.children.length > 0;
    }

    private refreshContainer() {
        this._actionCardContainer.innerHTML = "";

        if (this._actionCard === null && this._statusCard === null) {
            this._actionCardContainer.style.padding = "0px";
            this._actionCardContainer.style.marginTop = "0px";

            return;
        }

        this._actionCardContainer.style.marginTop = this._renderedActionCount > 0 ? this._owner.hostConfig.actions.showCard.inlineTopMargin + "px" : "0px";

        var padding = this._owner.getNonZeroPadding().toSpacingDefinition(this._owner.hostConfig);

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

    private layoutChanged() {
        this._owner.getRootElement().updateLayout();
    }

    private hideActionCard() {
        var previouslyExpandedAction = this._expandedAction;

        this._expandedAction = null;
        this._actionCard = null;

        this.refreshContainer();

        if (previouslyExpandedAction) {
            this.layoutChanged();

            raiseInlineCardExpandedEvent(previouslyExpandedAction, false);
        }
    }

    private showActionCard(action: ShowCardAction, suppressStyle: boolean = false, raiseEvent: boolean = true) {
        if (action.card == null) {
            return;
        }

        (<InlineAdaptiveCard>action.card).suppressStyle = suppressStyle;

        var renderedCard = action.card.render();

        this._actionCard = renderedCard;
        this._expandedAction = action;

        this.refreshContainer();

        if (raiseEvent) {
            this.layoutChanged();

            raiseInlineCardExpandedEvent(action, true);
        }
    }

    private collapseExpandedAction() {
        for (var i = 0; i < this.buttons.length; i++) {
            this.buttons[i].state = ActionButtonState.Normal;
        }

        this.hideActionCard();
    }

    private expandShowCardAction(action: ShowCardAction, raiseEvent: boolean) {
        for (var i = 0; i < this.buttons.length; i++) {
            if (this.buttons[i].action !== action) {
                this.buttons[i].state = ActionButtonState.Subdued;
            }
            else {
                this.buttons[i].state = ActionButtonState.Expanded;
            }
        }

        this.showActionCard(
            action,
            !(this._owner.isAtTheVeryLeft() && this._owner.isAtTheVeryRight()),
            raiseEvent);
    }

    private actionClicked(actionButton: ActionButton) {
        if (!(actionButton.action instanceof ShowCardAction)) {
            for (var i = 0; i < this.buttons.length; i++) {
                this.buttons[i].state = ActionButtonState.Normal;
            }

            this.hideStatusCard();
            this.hideActionCard();

            actionButton.action.execute();
        }
        else {
            this.hideStatusCard();

            if (this._owner.hostConfig.actions.showCard.actionMode === Enums.ShowCardActionMode.Popup) {
                actionButton.action.execute();
            }
            else if (actionButton.action === this._expandedAction) {
                this.collapseExpandedAction();
            }
            else {
                this.expandShowCardAction(actionButton.action, true);
            }
        }
    }

    items: Array<Action> = [];
    buttons: Array<ActionButton> = [];

    constructor(owner: CardElement) {
        this._owner = owner;
    }

    toJSON() {
        if (this.items.length > 0) {
            let result = [];

            for (let action of this.items) {
                result.push(action.toJSON());
            }

            return result;
        }
        else {
            return null;
        }
    }

    showStatusCard(status: AdaptiveCard) {
        status.setParent(this._owner);

        this._statusCard = status.render();

        this.refreshContainer();
    }

    hideStatusCard() {
        this._statusCard = null;

        this.refreshContainer();
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

        if (this._owner.hostConfig.actions.maxActions && this.items.length > this._owner.hostConfig.actions.maxActions) {
            result.push(
                {
                    error: Enums.ValidationError.TooManyActions,
                    message: "A maximum of " + this._owner.hostConfig.actions.maxActions + " actions are allowed."
                });
        }

        if (this.items.length > 0 && !this._owner.hostConfig.supportsInteractivity) {
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

    render(orientation: Enums.Orientation, isDesignMode: boolean): HTMLElement {
        if (!this._owner.hostConfig.supportsInteractivity) {
            return null;
        }

        var element = document.createElement("div");

        this._actionCardContainer = document.createElement("div");

        this._renderedActionCount = 0;

        var maxActions = this._owner.hostConfig.actions.maxActions ? Math.min(this._owner.hostConfig.actions.maxActions, this.items.length) : this.items.length;

        var forbiddenActionTypes = this._owner.getForbiddenActionTypes();

        if (this._owner.hostConfig.actions.preExpandSingleShowCardAction && maxActions == 1 && this.items[0] instanceof ShowCardAction && isActionAllowed(this.items[i], forbiddenActionTypes)) {
            this.showActionCard(<ShowCardAction>this.items[0], true);
            this._renderedActionCount = 1;
        }
        else {
            var buttonStrip = document.createElement("div");
            buttonStrip.className = this._owner.hostConfig.makeCssClassName("ac-actionSet");
            buttonStrip.style.display = "flex";

            if (orientation == Enums.Orientation.Horizontal) {
                buttonStrip.style.flexDirection = "row";

                if (this._owner.horizontalAlignment && this._owner.hostConfig.actions.actionAlignment != Enums.ActionAlignment.Stretch) {
                    switch (this._owner.horizontalAlignment) {
                        case Enums.HorizontalAlignment.Center:
                            buttonStrip.style.justifyContent = "center";
                            break;
                        case Enums.HorizontalAlignment.Right:
                            buttonStrip.style.justifyContent = "flex-end";
                            break;
                        default:
                            buttonStrip.style.justifyContent = "flex-start";
                            break;
                    }
                }
                else {
                    switch (this._owner.hostConfig.actions.actionAlignment) {
                        case Enums.ActionAlignment.Center:
                            buttonStrip.style.justifyContent = "center";
                            break;
                        case Enums.ActionAlignment.Right:
                            buttonStrip.style.justifyContent = "flex-end";
                            break;
                        default:
                            buttonStrip.style.justifyContent = "flex-start";
                            break;
                    }
                }
            }
            else {
                buttonStrip.style.flexDirection = "column";

                if (this._owner.horizontalAlignment && this._owner.hostConfig.actions.actionAlignment != Enums.ActionAlignment.Stretch) {
                    switch (this._owner.horizontalAlignment) {
                        case Enums.HorizontalAlignment.Center:
                            buttonStrip.style.alignItems = "center";
                            break;
                        case Enums.HorizontalAlignment.Right:
                            buttonStrip.style.alignItems = "flex-end";
                            break;
                        default:
                            buttonStrip.style.alignItems = "flex-start";
                            break;
                    }
                }
                else {
                    switch (this._owner.hostConfig.actions.actionAlignment) {
                        case Enums.ActionAlignment.Center:
                            buttonStrip.style.alignItems = "center";
                            break;
                        case Enums.ActionAlignment.Right:
                            buttonStrip.style.alignItems = "flex-end";
                            break;
                        case Enums.ActionAlignment.Stretch:
                            buttonStrip.style.alignItems = "stretch";
                            break;
                        default:
                            buttonStrip.style.alignItems = "flex-start";
                            break;
                    }
                }
            }

            for (var i = 0; i < this.items.length; i++) {
                if (isActionAllowed(this.items[i], forbiddenActionTypes)) {
                    var actionButton = new ActionButton(this.items[i]);
                    actionButton.action.renderedElement.style.overflow = "hidden";
                    actionButton.action.renderedElement.style.overflow = "table-cell";
                    actionButton.action.renderedElement.style.flex = this._owner.hostConfig.actions.actionAlignment === Enums.ActionAlignment.Stretch ? "0 1 100%" : "0 1 auto";
                    actionButton.onClick = (ab) => { this.actionClicked(ab); };

                    this.buttons.push(actionButton);

                    buttonStrip.appendChild(actionButton.action.renderedElement);

                    this._renderedActionCount++;

                    if (this._renderedActionCount >= this._owner.hostConfig.actions.maxActions || i == this.items.length - 1) {
                        break;
                    }
                    else if (this._owner.hostConfig.actions.buttonSpacing > 0) {
                        var spacer = document.createElement("div");

                        if (orientation === Enums.Orientation.Horizontal) {
                            spacer.style.flex = "0 0 auto";
                            spacer.style.width = this._owner.hostConfig.actions.buttonSpacing + "px";
                        }
                        else {
                            spacer.style.height = this._owner.hostConfig.actions.buttonSpacing + "px";
                        }

                        Utils.appendChild(buttonStrip, spacer);
                    }
                }
            }

            var buttonStripContainer = document.createElement("div");
            buttonStripContainer.style.overflow = "hidden";
            buttonStripContainer.appendChild(buttonStrip);

            Utils.appendChild(element, buttonStripContainer);
        }

        Utils.appendChild(element, this._actionCardContainer);

        for (var i = 0; i < this.buttons.length; i++) {
            if (this.buttons[i].state == ActionButtonState.Expanded) {
                this.expandShowCardAction(<ShowCardAction>this.buttons[i].action, false);

                break;
            }
        }

        return this._renderedActionCount > 0 ? element : null;
    }

    addAction(action: Action) {
        if ((!action.parent || action.parent === this._owner) && this.items.indexOf(action) < 0) {
            this.items.push(action);

            if (!action.parent) {
                action.setParent(this._owner);
            }

            invokeSetCollection(action, this);
        }
        else {
            throw new Error("The action already belongs to another element.")
        }
    }

    removeAction(action: Action): boolean {
        if (this.expandedAction && this._expandedAction == action) {
            this.collapseExpandedAction();
        }

        var actionIndex = this.items.indexOf(action);

        if (actionIndex >= 0) {
            this.items.splice(actionIndex, 1);

            action.setParent(null);

            invokeSetCollection(action, null);

            return true;
        }

        return false;
    }

    clear() {
        this.items = [];
        this.buttons = [];

        this._expandedAction = null;
        this._renderedActionCount = 0;
    }

    getAllInputs(): Array<Input> {
        var result: Array<Input> = [];

        for (var i = 0; i < this.items.length; i++) {
            var action = this.items[i];

            result = result.concat(action.getAllInputs());
        }

        return result;
    }

    get renderedActionCount(): number {
        return this._renderedActionCount;
    }

    get expandedAction(): ShowCardAction {
        return this._expandedAction;
    }
}

export class ActionSet extends CardElement {
    private _actionCollection: ActionCollection;

    protected internalRender(): HTMLElement {
        return this._actionCollection.render(this.orientation ? this.orientation : this.hostConfig.actions.actionsOrientation, this.isDesignMode());
    }

    orientation?: Enums.Orientation = null;

    constructor() {
        super();

        this._actionCollection = new ActionCollection(this);
    }

    toJSON() {
        let result = super.toJSON();

        Utils.setEnumProperty(Enums.Orientation, result, "orientation", this.orientation);
        Utils.setProperty(result, "actions", this._actionCollection.toJSON());

        return result;
    }

    isBleeding(): boolean {
        return this._actionCollection.expandedAction ? true : false;
    }

    getJsonTypeName(): string {
        return "ActionSet";
    }

    getActionCount(): number {
        return this._actionCollection.items.length;
    }

    getActionAt(index: number): Action {
        if (index >= 0 && index < this.getActionCount()) {
            return this._actionCollection.items[index];
        }
        else {
            super.getActionAt(index);
        }
    }

    validate(): Array<IValidationError> {
        return this._actionCollection.validate();
    }

    parse(json: any) { //, itemsCollectionPropertyName: string = "items") {
        super.parse(json);

        var jsonOrientation = json["orientation"];

        if (jsonOrientation) {
            this.orientation = Utils.getEnumValueOrDefault(Enums.Orientation, jsonOrientation, Enums.Orientation.Horizontal);
        }

        if (json["actions"] != undefined) {
            var jsonActions = json["actions"] as Array<any>;

            for (var i = 0; i < jsonActions.length; i++) {
                let action = createActionInstance(jsonActions[i]);

                if (action) {
                    action.setParent(this);
                    action.parse(jsonActions[i]);

                    this.addAction(action);
                }
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
    mode: Enums.BackgroundImageMode = Enums.BackgroundImageMode.Stretch;
    horizontalAlignment: Enums.HorizontalAlignment = Enums.HorizontalAlignment.Left;
    verticalAlignment: Enums.VerticalAlignment = Enums.VerticalAlignment.Top;

    parse(json: any) {
        this.url = json["url"];
        this.mode = Utils.getEnumValueOrDefault(Enums.BackgroundImageMode, json["mode"], this.mode);
        this.horizontalAlignment = Utils.getEnumValueOrDefault(Enums.HorizontalAlignment, json["horizontalAlignment"], this.horizontalAlignment);
        this.verticalAlignment = Utils.getEnumValueOrDefault(Enums.VerticalAlignment, json["verticalAlignment"], this.verticalAlignment);
    }

    apply(element: HTMLElement) {
        if (this.url) {
            element.style.backgroundImage = "url('" + this.url + "')";

            switch (this.mode) {
                case Enums.BackgroundImageMode.Repeat:
                    element.style.backgroundRepeat = "repeat";
                    break;
                case Enums.BackgroundImageMode.RepeatHorizontally:
                    element.style.backgroundRepeat = "repeat-x";
                    break;
                case Enums.BackgroundImageMode.RepeatVertically:
                    element.style.backgroundRepeat = "repeat-y";
                    break;
                case Enums.BackgroundImageMode.Stretch:
                default:
                    element.style.backgroundRepeat = "no-repeat";
                    element.style.backgroundSize = "cover";
                    break;
            }

            switch (this.horizontalAlignment) {
                case Enums.HorizontalAlignment.Center:
                    element.style.backgroundPositionX = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.style.backgroundPositionX = "right";
                    break;
            }

            switch (this.verticalAlignment) {
                case Enums.VerticalAlignment.Center:
                    element.style.backgroundPositionY = "center";
                    break;
                case Enums.VerticalAlignment.Bottom:
                    element.style.backgroundPositionY = "bottom";
                    break;
            }
        }
    }
}

export abstract class CardElementContainer extends CardElement {
    abstract getItemCount(): number;
    abstract getItemAt(index: number): CardElement;
    abstract removeItem(item: CardElement): boolean;
}

export class Container extends CardElementContainer {
    private _selectAction: Action;
    private _items: Array<CardElement> = [];
    private _renderedItems: Array<CardElement> = [];
    private _style?: string = null;

    private isElementAllowed(element: CardElement, forbiddenElementTypes: Array<string>) {
        if (!this.hostConfig.supportsInteractivity && element.isInteractive) {
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

    private insertItemAt(item: CardElement, index: number) {
        if (!item.parent) {
            if (item.isStandalone) {
                if (index < 0 || index >= this._items.length) {
                    this._items.push(item);
                }
                else {
                    this._items.splice(index, 0, item);
                }

                item.setParent(this);
            }
            else {
                throw new Error("Elements of type " + item.getJsonTypeName() + " cannot be used as standalone elements.");
            }
        }
        else {
            throw new Error("The element already belongs to another container.")
        }
    }

    private get hasExplicitStyle(): boolean {
        return this._style != null;
    }

    protected getItemsCollectionPropertyName(): string {
        return "items";
    }

    protected isLastElementBleeding(): boolean {
        return this._renderedItems.length > 0 ? this._renderedItems[this._renderedItems.length - 1].isBleeding() : false;
    }

    protected applyPadding() {
        if (!this.renderedElement) {
            return;
        }

        if (this.padding) {
            var physicalPadding = this.padding.toSpacingDefinition(this.hostConfig);

            this.renderedElement.style.paddingTop = physicalPadding.top + "px";
            this.renderedElement.style.paddingRight = physicalPadding.right + "px";
            this.renderedElement.style.paddingBottom = physicalPadding.bottom + "px";
            this.renderedElement.style.paddingLeft = physicalPadding.left + "px";
        }
        else if (this.hasBackground) {
            var physicalMargin: SpacingDefinition = new SpacingDefinition();
            var physicalPadding: SpacingDefinition = new SpacingDefinition();

            var useAutoPadding = (this.parent ? this.parent.canContentBleed() : false) && AdaptiveCard.useAutomaticContainerBleeding;

            if (useAutoPadding) {
                var effectivePadding = this.getNonZeroPadding();
                var effectiveMargin: PaddingDefinition = new PaddingDefinition(
                    effectivePadding.top,
                    effectivePadding.right,
                    effectivePadding.bottom,
                    effectivePadding.left);

                if (!this.isAtTheVeryTop()) {
                    effectivePadding.top = Enums.Spacing.None;
                    effectiveMargin.top = Enums.Spacing.None;
                }

                if (!this.isAtTheVeryBottom()) {
                    effectivePadding.bottom = Enums.Spacing.None;
                    effectiveMargin.bottom = Enums.Spacing.None;
                }

                if (!this.isAtTheVeryLeft()) {
                    effectivePadding.left = Enums.Spacing.None;
                    effectiveMargin.left = Enums.Spacing.None;
                }

                if (!this.isAtTheVeryRight()) {
                    effectivePadding.right = Enums.Spacing.None;
                    effectiveMargin.right = Enums.Spacing.None;
                }

                if (effectivePadding.left != Enums.Spacing.None || effectivePadding.right != Enums.Spacing.None) {
                    if (effectivePadding.left == Enums.Spacing.None) {
                        effectivePadding.left = effectivePadding.right;
                    }

                    if (effectivePadding.right == Enums.Spacing.None) {
                        effectivePadding.right = effectivePadding.left;
                    }
                }

                if (effectivePadding.top != Enums.Spacing.None || effectivePadding.bottom != Enums.Spacing.None) {
                    if (effectivePadding.top == Enums.Spacing.None) {
                        effectivePadding.top = effectivePadding.bottom;
                    }

                    if (effectivePadding.bottom == Enums.Spacing.None) {
                        effectivePadding.bottom = effectivePadding.top;
                    }
                }

                if (effectivePadding.top != Enums.Spacing.None
                    || effectivePadding.right != Enums.Spacing.None
                    || effectivePadding.bottom != Enums.Spacing.None
                    || effectivePadding.left != Enums.Spacing.None) {
                    if (effectivePadding.top == Enums.Spacing.None) {
                        effectivePadding.top = Enums.Spacing.Default;
                    }

                    if (effectivePadding.right == Enums.Spacing.None) {
                        effectivePadding.right = Enums.Spacing.Default;
                    }

                    if (effectivePadding.bottom == Enums.Spacing.None) {
                        effectivePadding = Object.assign(
                            { },
                            effectivePadding,
                            { bottom: Enums.Spacing.Default }
                        );
                    }

                    if (effectivePadding.left == Enums.Spacing.None) {
                        effectivePadding = Object.assign(
                            { },
                            effectivePadding,
                            { left: Enums.Spacing.Default }
                        );
                    }
                }

                if (effectivePadding.top == Enums.Spacing.None &&
                    effectivePadding.right == Enums.Spacing.None &&
                    effectivePadding.bottom == Enums.Spacing.None &&
                    effectivePadding.left == Enums.Spacing.None) {
                    effectivePadding = new PaddingDefinition(
                        Enums.Spacing.Padding,
                        Enums.Spacing.Padding,
                        Enums.Spacing.Padding,
                        Enums.Spacing.Padding);
                }

                physicalMargin = effectiveMargin.toSpacingDefinition(this.hostConfig);
                physicalPadding = effectivePadding.toSpacingDefinition(this.hostConfig);
            }
            else {
                physicalPadding = new PaddingDefinition(
                    Enums.Spacing.Padding,
                    Enums.Spacing.Padding,
                    Enums.Spacing.Padding,
                    Enums.Spacing.Padding
                ).toSpacingDefinition(this.hostConfig);
            }

            this.renderedElement.style.marginTop = "-" + physicalMargin.top + "px";
            this.renderedElement.style.marginRight = "-" + physicalMargin.right + "px";
            this.renderedElement.style.marginBottom = "-" + physicalMargin.bottom + "px";
            this.renderedElement.style.marginLeft = "-" + physicalMargin.left + "px";

            this.renderedElement.style.paddingTop = physicalPadding.top + "px";
            this.renderedElement.style.paddingRight = physicalPadding.right + "px";
            this.renderedElement.style.paddingBottom = physicalPadding.bottom + "px";
            this.renderedElement.style.paddingLeft = physicalPadding.left + "px";

            if (this.separatorElement) {
                if (this.separatorOrientation == Enums.Orientation.Horizontal) {
                    this.separatorElement.style.marginLeft = "-" + physicalMargin.left + "px";
                    this.separatorElement.style.marginRight = "-" + physicalMargin.right + "px";
                }
                else {
                    this.separatorElement.style.marginTop = "-" + physicalMargin.top + "px";
                    this.separatorElement.style.marginBottom = "-" + physicalMargin.bottom + "px";
                }
            }
        }

        if (this.isLastElementBleeding()) {
            this.renderedElement.style.paddingBottom = "0px";
        }
    }

    protected internalRender(): HTMLElement {
        this._renderedItems = [];

        // Cache hostConfig to avoid walking the parent hierarchy several times
        let hostConfig = this.hostConfig;

        var element = document.createElement("div");
        element.className = hostConfig.makeCssClassName("ac-container");
        element.style.display = "flex";
        element.style.flexDirection = "column";

        if (AdaptiveCard.useAdvancedCardBottomTruncation) {
            // Forces the container to be at least as tall as its content.
            //
            // Fixes a quirk in Chrome where, for nested flex elements, the
            // inner element's height would never exceed the outer element's
            // height. This caused overflow truncation to break -- containers
            // would always be measured as not overflowing, since their heights
            // were constrained by their parents as opposed to truly reflecting
            // the height of their content.
            //
            // See the "Browser Rendering Notes" section of this answer:
            // https://stackoverflow.com/questions/36247140/why-doesnt-flex-item-shrink-past-content-size
            element.style.minHeight = '-webkit-min-content';
        }

        switch (this.verticalContentAlignment) {
            case Enums.VerticalAlignment.Center:
                element.style.justifyContent = "center";
                break;
            case Enums.VerticalAlignment.Bottom:
                element.style.justifyContent = "flex-end";
                break;
            default:
                element.style.justifyContent = "flex-start";
                break;
        }

        if (this.hasBackground) {
            if (this.backgroundImage) {
                this.backgroundImage.apply(element);
            }

            var styleDefinition = this.hostConfig.containerStyles.getStyleByName(this.style, this.hostConfig.containerStyles.default);

            if (!Utils.isNullOrEmpty(styleDefinition.backgroundColor)) {
                element.style.backgroundColor = Utils.stringToCssColor(styleDefinition.backgroundColor);
            }
        }

        if (this.selectAction && hostConfig.supportsInteractivity) {
            element.classList.add(hostConfig.makeCssClassName("ac-selectable"));
            element.tabIndex = 0;
            element.setAttribute("role", "button");
            element.setAttribute("aria-label", this.selectAction.title);

            element.onclick = (e) => {
                if (this.selectAction != null) {
                    this.selectAction.execute();
                    e.cancelBubble = true;
                }
            }

            element.onkeypress = (e) => {
                if (this.selectAction != null) {
                    // Enter or space pressed
                    if (e.keyCode == 13 || e.keyCode == 32) {
                        this.selectAction.execute();
                    }
                }
            }
        }

        if (this._items.length > 0) {
            for (var i = 0; i < this._items.length; i++) {
                var renderedElement = this.isElementAllowed(this._items[i], this.getForbiddenElementTypes()) ? this._items[i].render() : null;

                if (renderedElement) {
                    if (this._renderedItems.length > 0 && this._items[i].separatorElement) {
                        this._items[i].separatorElement.style.flex = "0 0 auto";

                        Utils.appendChild(element, this._items[i].separatorElement);
                    }

                    Utils.appendChild(element, renderedElement);

                    this._renderedItems.push(this._items[i]);
                }
            }
        }
        else {
            if (this.isDesignMode()) {
                var placeholderElement = this.createPlaceholderElement();
                placeholderElement.style.width = "100%";
                placeholderElement.style.height = "100%";

                element.appendChild(placeholderElement);
            }
        }

        return element;
    }

    protected truncateOverflow(maxHeight: number): boolean {
        // Add 1 to account for rounding differences between browsers
        var boundary = this.renderedElement.offsetTop + maxHeight + 1;

        var handleElement = (cardElement: CardElement) => {
            let elt = cardElement.renderedElement;

            if (elt) {
                switch (Utils.getFitStatus(elt, boundary)) {
                    case Enums.ContainerFitStatus.FullyInContainer:
                        let sizeChanged = cardElement['resetOverflow']();
                        // If the element's size changed after resetting content,
                        // we have to check if it still fits fully in the card
                        if (sizeChanged) {
                            handleElement(cardElement);
                        }
                        break;
                    case Enums.ContainerFitStatus.Overflowing:
                        let maxHeight = boundary - elt.offsetTop;
                        cardElement['handleOverflow'](maxHeight);
                        break;
                    case Enums.ContainerFitStatus.FullyOutOfContainer:
                        cardElement['handleOverflow'](0);
                        break;
                }
            }
        };

        for (let item of this._items) {
            handleElement(item);
        }
        
        return true;
    }

    protected undoOverflowTruncation() {
        for (let item of this._items) {
            item['resetOverflow']();
        }
    }

    protected get hasBackground(): boolean {
        var parentContainer = this.getParentContainer();

        return this.backgroundImage != undefined || (this.hasExplicitStyle && (parentContainer ? parentContainer.style != this.style : false));
    }

    protected get defaultStyle(): string {
        return Enums.ContainerStyle.Default;
    }

    protected get allowCustomStyle(): boolean {
        return true;
    }

    backgroundImage: BackgroundImage;
    verticalContentAlignment: Enums.VerticalAlignment = Enums.VerticalAlignment.Top;

    toJSON() {
        let result = super.toJSON();

        if (this._selectAction) {
            Utils.setProperty(result, "selectAction", this._selectAction.toJSON());
        }

        if (this.backgroundImage) {
            Utils.setProperty(result, "backgroundImage", this.backgroundImage.url);
        }

        Utils.setProperty(result, "style", this.style, "default");
        Utils.setEnumProperty(Enums.VerticalAlignment, result, "verticalContentAlignment", this.verticalContentAlignment, Enums.VerticalAlignment.Top);

        if (this._items.length > 0) {
            let elements = [];

            for (let element of this._items) {
                elements.push(element.toJSON());
            }

            Utils.setProperty(result, this.getItemsCollectionPropertyName(), elements);
        }

        return result;
    }

    isBleeding(): boolean {
        return this.isLastElementBleeding();
    }

    getItemCount(): number {
        return this._items.length;
    }

    getItemAt(index: number): CardElement {
        return this._items[index];
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
        for (var i = this._items.length - 1; i >= 0; i--) {
            if (this._items[i].isVisible) {
                return this._items[i] == element;
            }
        }

        return false;
    }

    validate(): Array<IValidationError> {
        var result: Array<IValidationError> = [];

        if (this._style) {
            var styleDefinition = this.hostConfig.containerStyles.getStyleByName(this._style);

            if (!styleDefinition) {
                result.push(
                    {
                        error: Enums.ValidationError.InvalidPropertyValue,
                        message: "Unknown container style: " + this._style
                    });
            }
        }

        for (var i = 0; i < this._items.length; i++) {
            if (!this.hostConfig.supportsInteractivity && this._items[i].isInteractive) {
                result.push(
                    {
                        error: Enums.ValidationError.InteractivityNotAllowed,
                        message: "Interactivity is not allowed."
                    });
            }

            if (!this.isElementAllowed(this._items[i], this.getForbiddenElementTypes())) {
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

    parse(json: any) {
        super.parse(json);

        this._items = [];
        this._renderedItems = [];

        var jsonBackgroundImage = json["backgroundImage"];

        if (jsonBackgroundImage) {
            this.backgroundImage = new BackgroundImage();

            if (typeof jsonBackgroundImage === "string") {
                this.backgroundImage.url = jsonBackgroundImage;
                this.backgroundImage.mode = Enums.BackgroundImageMode.Stretch;
            }
            else if (typeof jsonBackgroundImage === "object") {
                this.backgroundImage = new BackgroundImage();
                this.backgroundImage.parse(json["backgroundImage"]);
            }
        }

        this.verticalContentAlignment = Utils.getEnumValueOrDefault(Enums.VerticalAlignment, json["verticalContentAlignment"], this.verticalContentAlignment);

        this._style = json["style"];

        if (json[this.getItemsCollectionPropertyName()] != null) {
            var items = json[this.getItemsCollectionPropertyName()] as Array<any>;

            this.clear();

            for (var i = 0; i < items.length; i++) {
                var elementType = items[i]["type"];

                var element = AdaptiveCard.elementTypeRegistry.createInstance(elementType);

                if (!element) {
                    raiseParseError(
                        {
                            error: Enums.ValidationError.UnknownElementType,
                            message: "Unknown element type: " + elementType
                        });
                }
                else {
                    this.addItem(element);

                    element.parse(items[i]);
                }
            }
        }

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            this.selectAction = createActionInstance(selectActionJson);

            if (this.selectAction) {
                this.selectAction.setParent(this);
                this.selectAction.parse(selectActionJson);
            }
        }
    }

    addItem(item: CardElement) {
        this.insertItemAt(item, -1);
    }

    insertItemBefore(item: CardElement, insertBefore: CardElement) {
        this.insertItemAt(item, this._items.indexOf(insertBefore));
    }

    insertItemAfter(item: CardElement, insertAfter: CardElement) {
        this.insertItemAt(item, this._items.indexOf(insertAfter) + 1);
    }

    removeItem(item: CardElement): boolean {
        var itemIndex = this._items.indexOf(item);

        if (itemIndex >= 0) {
            this._items.splice(itemIndex, 1);

            item.setParent(null);

            this.updateLayout();

            return true;
        }

        return false;
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
        super.updateLayout(processChildren);

        this.applyPadding();

        if (processChildren) {
            for (var i = 0; i < this._items.length; i++) {
                this._items[i].updateLayout();
            }
        }
    }

    get style(): string {
        if (this.allowCustomStyle) {
            return this._style && this.hostConfig.containerStyles.getStyleByName(this._style) ? this._style : this.defaultStyle;
        }
        else {
            return this.defaultStyle;
        }
    }

    set style(value: string) {
        this._style = value;
    }

    get padding(): PaddingDefinition {
        return this.getPadding();
    }

    set padding(value: PaddingDefinition) {
        this.setPadding(value);
    }

    get selectAction(): Action {
        return this._selectAction;
    }

    set selectAction(value: Action) {
        this._selectAction = value;

        if (this._selectAction) {
            this._selectAction.setParent(this);
        }
    }
}

export class Column extends Container {
    private _computedWeight: number = 0;

    protected adjustRenderedElementSize(renderedElement: HTMLElement) {
        if (this.isDesignMode()) {
            renderedElement.style.minWidth = "20px";
            renderedElement.style.minHeight = "20px";
        }
        else {
            renderedElement.style.minWidth = "0";
        }

        if (this.width instanceof Utils.SizeAndUnit) {
            if (this.width.unit == Enums.SizeUnit.Pixel) {
                renderedElement.style.flex = "0 0 " + this.width.physicalSize + "px";
            }
            else {
                renderedElement.style.flex = "1 1 " + (this._computedWeight > 0 ? this._computedWeight : this.width.physicalSize) + "%";
            }
        }
        else if (this.width === "auto") {
            renderedElement.style.flex = "0 1 auto";
        }
        else {
            // Stretch
            renderedElement.style.flex = "1 1 50px";
        }
    }

    protected get separatorOrientation(): Enums.Orientation {
        return Enums.Orientation.Vertical;
    }

    width: Utils.SizeAndUnit | "auto" | "stretch" = "auto";

    getJsonTypeName(): string {
        return "Column";
    }

    toJSON() {
        let result = super.toJSON();

        if (this.width instanceof SizeAndUnit) {
            if (this.width.unit == Enums.SizeUnit.Pixel) {
                Utils.setProperty(result, "width", this.width.physicalSize + "px");
            }
            else {
                Utils.setProperty(result, "width", this.width.physicalSize);
            }
        }
        else {
            Utils.setProperty(result, "width", this.width);
        }

        return result;
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
            if (jsonWidth > 0) {
                this.width = new Utils.SizeAndUnit(jsonWidth, Enums.SizeUnit.Weight);
            }
            else {
                invalidWidth = true;
            }
        }
        else if (typeof jsonWidth === "string") {
            if (jsonWidth != "auto" && jsonWidth != "stretch") {
                try {
                    this.width = Utils.SizeAndUnit.parse(jsonWidth);
                }
                catch (e) {
                    invalidWidth = true;
                }
            }
            else {
                this.width = jsonWidth;
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
    }

    get hasVisibleSeparator(): boolean {
        if (this.parent && this.parent instanceof ColumnSet) {
            return !this.parent.isLeftMostElement(this);
        }
        else {
            return false;
        }
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class ColumnSet extends CardElementContainer {
    private _columns: Array<Column> = [];
    private _selectAction: Action;

    protected applyPadding() {
        if (this.padding) {
            if (this.renderedElement) {
                var physicalPadding = this.padding.toSpacingDefinition(this.hostConfig);

                this.renderedElement.style.paddingTop = physicalPadding.top + "px";
                this.renderedElement.style.paddingRight = physicalPadding.right + "px";
                this.renderedElement.style.paddingBottom = physicalPadding.bottom + "px";
                this.renderedElement.style.paddingLeft = physicalPadding.left + "px";
            }
        }
    }

    protected internalRender(): HTMLElement {
        if (this._columns.length > 0) {
            // Cache hostConfig to avoid walking the parent hierarchy several times
            let hostConfig = this.hostConfig;

            var element = document.createElement("div");
            element.className = hostConfig.makeCssClassName("ac-columnSet");
            element.style.display = "flex";

            if (AdaptiveCard.useAdvancedCardBottomTruncation) {
                // See comment in Container.internalRender()
                element.style.minHeight = '-webkit-min-content';
            }

            if (this.selectAction && hostConfig.supportsInteractivity) {
                element.classList.add(hostConfig.makeCssClassName("ac-selectable"));

                element.onclick = (e) => {
                    this.selectAction.execute();
                    e.cancelBubble = true;
                }
            }

            switch (this.horizontalAlignment) {
                case Enums.HorizontalAlignment.Center:
                    element.style.justifyContent = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.style.justifyContent = "flex-end";
                    break;
                default:
                    element.style.justifyContent = "flex-start";
                    break;
            }

            var totalWeight: number = 0;

            for (let column of this._columns) {
                if (column.width instanceof Utils.SizeAndUnit && (column.width.unit == Enums.SizeUnit.Weight)) {
                    totalWeight += column.width.physicalSize;
                }
            }

            var renderedColumnCount: number = 0;

            for (let column of this._columns) {
                if (column.width instanceof Utils.SizeAndUnit && column.width.unit == Enums.SizeUnit.Weight && totalWeight > 0) {
                    var computedWeight = 100 / totalWeight * column.width.physicalSize;

                    // Best way to emulate "internal" access I know of
                    column["_computedWeight"] = computedWeight;
                }

                var renderedColumn = column.render();

                if (renderedColumn) {
                    if (renderedColumnCount > 0 && column.separatorElement) {
                        column.separatorElement.style.flex = "0 0 auto";

                        Utils.appendChild(element, column.separatorElement);
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

    protected truncateOverflow(maxHeight: number): boolean {
        for (let column of this._columns) {
            column['handleOverflow'](maxHeight);
        }

        return true;
    }

    protected undoOverflowTruncation() {
        for (let column of this._columns) {
            column['resetOverflow']();
        }
    }

    toJSON() {
        let result = super.toJSON();

        if (this._selectAction) {
            Utils.setProperty(result, "selectAction", this.selectAction.toJSON());
        }

        if (this._columns.length > 0) {
            let columns = [];

            for (let column of this._columns) {
                columns.push(column.toJSON());
            }

            Utils.setProperty(result, "columns", columns);
        }

        return result;
    }

    isFirstElement(element: CardElement): boolean {
        for (var i = 0; i < this._columns.length; i++) {
            if (this._columns[i].isVisible) {
                return this._columns[i] == element;
            }
        }

        return false;
    }

    getCount(): number {
        return this._columns.length;
    }

    getItemCount(): number {
        return this.getCount();
    }

    getColumnAt(index: number): Column {
        return this._columns[index];
    }

    getItemAt(index: number): CardElement {
        return this.getColumnAt(index);
    }

    getJsonTypeName(): string {
        return "ColumnSet";
    }

    parse(json: any) {
        super.parse(json);

        var selectActionJson = json["selectAction"];

        if (selectActionJson != undefined) {
            this.selectAction = createActionInstance(selectActionJson);

            if (this.selectAction) {
                this.selectAction.setParent(this);
                this.selectAction.parse(selectActionJson);
            }
        }

        if (json["columns"] != null) {
            let jsonColumns = json["columns"] as Array<any>;
            this._columns = [];
            for (let i = 0; i < jsonColumns.length; i++) {
                var column = new Column();

                column.parse(jsonColumns[i]);

                this.addColumn(column);
            }
        }
    }

    validate(): Array<IValidationError> {
        var result: Array<IValidationError> = [];
        var weightedColumns: number = 0;
        var stretchedColumns: number = 0;

        for (var i = 0; i < this._columns.length; i++) {
            if (typeof this._columns[i].width === "number") {
                weightedColumns++;
            }
            else if (this._columns[i].width === "stretch") {
                stretchedColumns++;
            }

            result = result.concat(this._columns[i].validate());
        }

        if (weightedColumns > 0 && stretchedColumns > 0) {
            result.push(
                {
                    error: Enums.ValidationError.Hint,
                    message: "It is not recommended to use weighted and stretched columns in the same ColumnSet, because in such a situation stretched columns will always get the minimum amount of space."
                });
        }

        return result;
    }

    updateLayout(processChildren: boolean = true) {
        super.updateLayout(processChildren);

        this.applyPadding();
        
        if (processChildren) {
            for (var i = 0; i < this._columns.length; i++) {
                this._columns[i].updateLayout();
            }
        }
    }

    addColumn(column: Column) {
        if (!column.parent) {
            this._columns.push(column);

            column.setParent(this);
        }
        else {
            throw new Error("This column already belongs to another ColumnSet.");
        }
    }

    removeItem(item: CardElement): boolean {
        if (item instanceof Column) {
            var itemIndex = this._columns.indexOf(item);

            if (itemIndex >= 0) {
                this._columns.splice(itemIndex, 1);

                item.setParent(null);

                this.updateLayout();

                return true;
            }
        }

        return false;
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

    get padding(): PaddingDefinition {
        return this.getPadding();
    }

    set padding(value: PaddingDefinition) {
        this.setPadding(value);
    }

    get selectAction(): Action {
        return this._selectAction;
    }

    set selectAction(value: Action) {
        this._selectAction = value;

        if (this._selectAction) {
            this._selectAction.setParent(this);
        }
    }
}

export class Version {
    private _versionString: string;
    private _major: number;
    private _minor: number;
    private _isValid: boolean = true;

    constructor(major: number = 1, minor: number = 1) {
        this._major = major;
        this._minor = minor;
    }

    static parse(versionString: string): Version {
        if (!versionString) {
            return null;
        }

        var result = new Version();
        result._versionString = versionString;

        var regEx = /(\d+).(\d+)/gi;
        var matches = regEx.exec(versionString);

        if (matches != null && matches.length == 3) {
            result._major = parseInt(matches[1]);
            result._minor = parseInt(matches[2]);
        }
        else {
            result._isValid = false;
        }

        return result;
    }

    toString(): string {
        return !this._isValid ? this._versionString : this._major + "." + this._minor;
    }

    get major(): number {
        return this._major;
    }

    get minor(): number {
        return this._minor;
    }

    get isValid(): boolean {
        return this._isValid;
    }
}

function raiseImageLoadedEvent(image: Image) {
    let card = image.getRootElement() as AdaptiveCard;
    let onImageLoadedHandler = (card && card.onImageLoaded) ? card.onImageLoaded : AdaptiveCard.onImageLoaded;

    if (onImageLoadedHandler) {
        onImageLoadedHandler(image);
    }
}

function raiseAnchorClickedEvent(element: CardElement, anchor: HTMLAnchorElement): boolean {
    let card = element.getRootElement() as AdaptiveCard;
    let onAnchorClickedHandler = (card && card.onAnchorClicked) ? card.onAnchorClicked : AdaptiveCard.onAnchorClicked;

    return onAnchorClickedHandler != null ? onAnchorClickedHandler(card, anchor) : false;
}

function raiseExecuteActionEvent(action: Action) {
    let card = action.parent.getRootElement() as AdaptiveCard;
    let onExecuteActionHandler = (card && card.onExecuteAction) ? card.onExecuteAction : AdaptiveCard.onExecuteAction;

    if (onExecuteActionHandler) {
        action.prepare(action.parent.getRootElement().getAllInputs());

        onExecuteActionHandler(action);
    }
}

function raiseInlineCardExpandedEvent(action: ShowCardAction, isExpanded: boolean) {
    let card = action.parent.getRootElement() as AdaptiveCard;
    let onInlineCardExpandedHandler = (card && card.onInlineCardExpanded) ? card.onInlineCardExpanded : AdaptiveCard.onInlineCardExpanded;

    if (onInlineCardExpandedHandler) {
        onInlineCardExpandedHandler(action, isExpanded);
    }
}

function raiseElementVisibilityChangedEvent(element: CardElement, shouldUpdateLayout: boolean = true) {
    let rootElement = element.getRootElement();

    if (shouldUpdateLayout) {
        rootElement.updateLayout();
    }

    let card = rootElement as AdaptiveCard;
    let onElementVisibilityChangedHandler = (card && card.onElementVisibilityChanged) ? card.onElementVisibilityChanged : AdaptiveCard.onElementVisibilityChanged;

    if (onElementVisibilityChangedHandler != null) {
        onElementVisibilityChangedHandler(element);
    }
}

function raiseParseElementEvent(element: CardElement, json: any) {
    let card = element.getRootElement() as AdaptiveCard;
    let onParseElementHandler = (card && card.onParseElement) ? card.onParseElement : AdaptiveCard.onParseElement;

    if (onParseElementHandler != null) {
        onParseElementHandler(element, json);
    }
}

function raiseParseActionEvent(action: Action, json: any) {
	let card = action.parent ? action.parent.getRootElement() as AdaptiveCard : null;
	let onParseActionHandler = (card && card.onParseAction) ? card.onParseAction : AdaptiveCard.onParseAction;

	if (onParseActionHandler != null) {
		onParseActionHandler(action, json);
	}
}

function raiseParseError(error: IValidationError) {
    if (AdaptiveCard.onParseError != null) {
        AdaptiveCard.onParseError(error);
    }
}

export interface ITypeRegistration<T> {
    typeName: string,
    createInstance: () => T;
}

export abstract class ContainerWithActions extends Container {
    private _actionCollection: ActionCollection;

    protected internalRender(): HTMLElement {
        var element = super.internalRender();

        var renderedActions = this._actionCollection.render(this.hostConfig.actions.actionsOrientation, false);

        if (renderedActions) {
            Utils.appendChild(
                element,
                Utils.renderSeparation(
                    {
                        spacing: this.hostConfig.getEffectiveSpacing(this.hostConfig.actions.spacing),
                        lineThickness: null,
                        lineColor: null
                    },
                    Enums.Orientation.Horizontal));
            Utils.appendChild(element, renderedActions);
        }

        return element.children.length > 0 ? element : null;
    }

    protected isLastElementBleeding(): boolean {
        if (this._actionCollection.renderedActionCount == 0) {
            return super.isLastElementBleeding() ? !this.isDesignMode() : false;
        }
        else {
            if (this._actionCollection.items.length == 1) {
                return this._actionCollection.expandedAction != null && !this.hostConfig.actions.preExpandSingleShowCardAction;
            }
            else {
                return this._actionCollection.expandedAction != null;
            }
        }
    }

    constructor() {
        super();

        this._actionCollection = new ActionCollection(this);
    }

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "actions", this._actionCollection.toJSON());

        return result;
    }

    getActionCount(): number {
        return this._actionCollection.items.length;
    }

    getActionAt(index: number): Action {
        if (index >= 0 && index < this.getActionCount()) {
            return this._actionCollection.items[index];
        }
        else {
            super.getActionAt(index);
        }
    }

    getActionById(id: string): Action {
        var result: Action = this._actionCollection.getActionById(id);

        return result ? result : super.getActionById(id);
    }

    parse(json) {
        super.parse(json);

        this._actionCollection.clear();

        if (json["actions"] != undefined) {
            var jsonActions = json["actions"] as Array<any>;

            for (var i = 0; i < jsonActions.length; i++) {
                var action = createActionInstance(jsonActions[i]);

                if (action != null) {
                    action.setParent(this);
                    action.parse(jsonActions[i]);

                    this.addAction(action);
                }
            }
        }
    }

    validate(): Array<IValidationError> {
        var result = super.validate();

        if (this._actionCollection) {
            result = result.concat(this._actionCollection.validate());
        }

        return result;
    }

    isLastElement(element: CardElement): boolean {
        return super.isLastElement(element) && this._actionCollection.items.length == 0;
    }

    addAction(action: Action) {
        if (action) {
            this._actionCollection.addAction(action);
        }
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

export abstract class TypeRegistry<T> {
    private _items: Array<ITypeRegistration<T>> = [];

    private findTypeRegistration(typeName: string): ITypeRegistration<T> {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].typeName === typeName) {
                return this._items[i];
            }
        }

        return null;
    }

    constructor() {
        this.reset();
    }

    clear() {
        this._items = [];
    }

    abstract reset();

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

    getItemCount(): number {
        return this._items.length;
    }

    getItemAt(index: number): ITypeRegistration<T> {
        return this._items[index];
    }
}

export class ElementTypeRegistry extends TypeRegistry<CardElement> {
    reset() {
        this.clear();

        this.registerType("Container", () => { return new Container(); });
        this.registerType("TextBlock", () => { return new TextBlock(); });
        this.registerType("Image", () => { return new Image(); });
        this.registerType("ImageSet", () => { return new ImageSet(); });
        this.registerType("FactSet", () => { return new FactSet(); });
        this.registerType("ColumnSet", () => { return new ColumnSet(); });
        this.registerType("Input.Text", () => { return new TextInput(); });
        this.registerType("Input.Date", () => { return new DateInput(); });
        this.registerType("Input.Time", () => { return new TimeInput(); });
        this.registerType("Input.Number", () => { return new NumberInput(); });
        this.registerType("Input.ChoiceSet", () => { return new ChoiceSetInput(); });
        this.registerType("Input.Toggle", () => { return new ToggleInput(); });
    }
}

export class ActionTypeRegistry extends TypeRegistry<Action> {
    reset() {
        this.clear();

        this.registerType("Action.OpenUrl", () => { return new OpenUrlAction(); });
        this.registerType("Action.Submit", () => { return new SubmitAction(); });
        this.registerType("Action.ShowCard", () => { return new ShowCardAction(); });
    }
}

export class AdaptiveCard extends ContainerWithActions {
    private static currentVersion: Version = new Version(1, 0);

    static useAutomaticContainerBleeding: boolean = false;
    static useAdvancedTextBlockTruncation: boolean = true;
    static useAdvancedCardBottomTruncation: boolean = false;
    static useMarkdownInRadioButtonAndCheckbox: boolean = true;

    static readonly elementTypeRegistry = new ElementTypeRegistry();
    static readonly actionTypeRegistry = new ActionTypeRegistry();

    static onAnchorClicked: (rootCard: AdaptiveCard, anchor: HTMLAnchorElement) => boolean = null;
    static onExecuteAction: (action: Action) => void = null;
    static onElementVisibilityChanged: (element: CardElement) => void = null;
    static onImageLoaded: (image: Image) => void = null;
    static onInlineCardExpanded: (action: ShowCardAction, isExpanded: boolean) => void = null;
    static onParseElement: (element: CardElement, json: any) => void = null;
    static onParseAction: (element: Action, json: any) => void = null;
    static onParseError: (error: IValidationError) => void = null;

    static processMarkdown = function (text: string): string {
        // Check for markdownit
        if (window["markdownit"]) {
            return window["markdownit"]().render(text);
        }

        return text;
    }

    private isVersionSupported(): boolean {
        if (this.bypassVersionCheck) {
            return true;
        }
        else {
            var unsupportedVersion: boolean =
                !this.version ||
                (AdaptiveCard.currentVersion.major < this.version.major) ||
                (AdaptiveCard.currentVersion.major == this.version.major && AdaptiveCard.currentVersion.minor < this.version.minor);

            return !unsupportedVersion;
        }
    }

    private _cardTypeName?: string = "AdaptiveCard";

    protected getItemsCollectionPropertyName(): string {
        return "body";
    }

    protected applyPadding() {
        if (!this.renderedElement) {
            return;
        }

        var effectivePadding = this.padding ? this.padding.toSpacingDefinition(this.hostConfig) : this.internalPadding.toSpacingDefinition(this.hostConfig);

        this.renderedElement.style.paddingTop = effectivePadding.top + "px";
        this.renderedElement.style.paddingRight = effectivePadding.right + "px";
        this.renderedElement.style.paddingBottom = effectivePadding.bottom + "px";
        this.renderedElement.style.paddingLeft = effectivePadding.left + "px";

        if (this.isLastElementBleeding()) {
            this.renderedElement.style.paddingBottom = "0px";
        }
    }

    protected internalRender(): HTMLElement {
        var renderedElement = super.internalRender();

        if (AdaptiveCard.useAdvancedCardBottomTruncation) {
            // Unlike containers, the root card element should be allowed to
            // be shorter than its content (otherwise the overflow truncation
            // logic would never get triggered)
            renderedElement.style.minHeight = null;
        }

        return renderedElement;
    }

    protected get bypassVersionCheck(): boolean {
        return false;
    }

    protected get defaultPadding(): PaddingDefinition {
        return new PaddingDefinition(
            Enums.Spacing.Padding,
            Enums.Spacing.Padding,
            Enums.Spacing.Padding,
            Enums.Spacing.Padding);
    }

    protected get allowCustomPadding(): boolean {
        return false;
    }

    protected get allowCustomStyle() {
        return this.hostConfig.adaptiveCard && this.hostConfig.adaptiveCard.allowCustomStyle;
    }

    protected get hasBackground(): boolean {
        return true;
    }

    onAnchorClicked: (rootCard: AdaptiveCard, anchor: HTMLAnchorElement) => boolean = null;
    onExecuteAction: (action: Action) => void = null;
    onElementVisibilityChanged: (element: CardElement) => void = null;
    onImageLoaded: (image: Image) => void = null;
    onInlineCardExpanded: (action: ShowCardAction, isExpanded: boolean) => void = null;
    onParseElement: (element: CardElement, json: any) => void = null;
	onParseAction: (element: Action, json: any) => void = null;

    version?: Version = new Version(1, 0);
    fallbackText: string;
    designMode: boolean = false;

    getJsonTypeName(): string {
        return "AdaptiveCard";
    }

    toJSON() {
        let result = super.toJSON();

        if (!this.bypassVersionCheck && this.version) {
            Utils.setProperty(result, "version", this.version.toString());
        }

        Utils.setProperty(result, "fallbackText", this.fallbackText);

        return result;
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

        if (!this.bypassVersionCheck && (!this.version || !this.version.isValid)) {
            result.push(
                {
                    error: Enums.ValidationError.PropertyCantBeNull,
                    message: !this.version ? "The version property must be specified." : "Invalid version: " + this.version
                });
        }
        else if (!this.isVersionSupported()) {
            result.push(
                {
                    error: Enums.ValidationError.UnsupportedCardVersion,
                    message: "The specified card version (" + this.version + ") is not supported. The maximum supported card version is " + AdaptiveCard.currentVersion
                });
        }

        return result.concat(super.validate());
    }

    parse(json: any) {
        this._cardTypeName = json["type"];

        var langId = json["lang"];

        if (langId && typeof langId === "string") {
            try {
                this.lang = langId;
            }
            catch (e) {
                raiseParseError(
                    {
                        error: Enums.ValidationError.InvalidPropertyValue,
                        message: e.message
                    });                        
            }
        }

        this.version = Version.parse(json["version"]);

        this.fallbackText = json["fallbackText"];

        super.parse(json); //, "body");
    }

    render(target?: HTMLElement): HTMLElement {
        var renderedCard: HTMLElement;

        if (!this.isVersionSupported()) {
            renderedCard = document.createElement("div");
            renderedCard.innerHTML = this.fallbackText ? this.fallbackText : "The specified card version is not supported.";
        }
        else {
            renderedCard = super.render();

            if (renderedCard) {
                renderedCard.tabIndex = 0;

                if (!Utils.isNullOrEmpty(this.speak)) {
                    renderedCard.setAttribute("aria-label", this.speak);
                }
            }
        }

        if (target) {
            target.appendChild(renderedCard);

            this.updateLayout();
        }

        return renderedCard;
    }

    updateLayout(processChildren: boolean = true) {
        super.updateLayout(processChildren);

        if (AdaptiveCard.useAdvancedCardBottomTruncation && this.isRendered()) {
            var card = this.renderedElement;
            var padding = this.hostConfig.getEffectiveSpacing(Enums.Spacing.Default);

            this['handleOverflow'](card.offsetHeight - padding);
        }
    }

    canContentBleed(): boolean {
        return true;
    }

    get hasVisibleSeparator(): boolean {
        return false;
    }
}

class InlineAdaptiveCard extends AdaptiveCard {
    protected get bypassVersionCheck(): boolean {
        return true;
    }

    protected get defaultPadding(): PaddingDefinition {
        return new PaddingDefinition(
            this.suppressStyle ? Enums.Spacing.None : Enums.Spacing.Padding,
            Enums.Spacing.Padding,
            this.suppressStyle ? Enums.Spacing.None : Enums.Spacing.Padding,
            Enums.Spacing.Padding);
    }

    protected get defaultStyle(): string {
        if (this.suppressStyle) {
            return Enums.ContainerStyle.Default;
        }
        else {
            return this.hostConfig.actions.showCard.style ? this.hostConfig.actions.showCard.style : Enums.ContainerStyle.Emphasis;
        }
    }

    suppressStyle: boolean = false;

    render(target?: HTMLElement) {
        var renderedCard = super.render(target);
        renderedCard.setAttribute("aria-live", "polite");
        renderedCard.removeAttribute("tabindex");

        return renderedCard;
    }

    getForbiddenActionTypes(): Array<any> {
        return [ShowCardAction];
    }
}

const defaultHostConfig: HostConfig.HostConfig = new HostConfig.HostConfig(
    {
        supportsInteractivity: true,
        fontFamily: "Segoe UI",
        spacing: {
            small: 10,
            default: 20,
            medium: 30,
            large: 40,
            extraLarge: 50,
            padding: 20
        },
        separator: {
            lineThickness: 1,
            lineColor: "#EEEEEE"
        },
        fontSizes: {
            small: 12,
            default: 14,
            medium: 17,
            large: 21,
            extraLarge: 26
        },
        fontWeights: {
            lighter: 200,
            default: 400,
            bolder: 600
        },
        imageSizes: {
            small: 40,
            medium: 80,
            large: 160
        },
        containerStyles: {
            default: {
                backgroundColor: "#FFFFFF",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#cc3300",
                        subtle: "#DDcc3300"
                    },
                    good: {
                        default: "#54a254",
                        subtle: "#DD54a254"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            },
            emphasis: {
                backgroundColor: "#08000000",
                foregroundColors: {
                    default: {
                        default: "#333333",
                        subtle: "#EE333333"
                    },
                    dark: {
                        default: "#000000",
                        subtle: "#66000000"
                    },
                    light: {
                        default: "#FFFFFF",
                        subtle: "#33000000"
                    },
                    accent: {
                        default: "#2E89FC",
                        subtle: "#882E89FC"
                    },
                    attention: {
                        default: "#cc3300",
                        subtle: "#DDcc3300"
                    },
                    good: {
                        default: "#54a254",
                        subtle: "#DD54a254"
                    },
                    warning: {
                        default: "#e69500",
                        subtle: "#DDe69500"
                    }
                }
            }
        },
        actions: {
            maxActions: 5,
            spacing: Enums.Spacing.Default,
            buttonSpacing: 10,
            showCard: {
                actionMode: Enums.ShowCardActionMode.Inline,
                inlineTopMargin: 16
            },
            actionsOrientation: Enums.Orientation.Horizontal,
            actionAlignment: Enums.ActionAlignment.Left
        },
        adaptiveCard: {
            allowCustomStyle: false
        },
        imageSet: {
            imageSize: Enums.Size.Medium,
            maxImageHeight: 100
        },
        factSet: {
            title: {
                color: Enums.TextColor.Default,
                size: Enums.TextSize.Default,
                isSubtle: false,
                weight: Enums.TextWeight.Bolder,
                wrap: true,
                maxWidth: 150,
            },
            value: {
                color: Enums.TextColor.Default,
                size: Enums.TextSize.Default,
                isSubtle: false,
                weight: Enums.TextWeight.Default,
                wrap: true,
            },
            spacing: 10
        }
    });
