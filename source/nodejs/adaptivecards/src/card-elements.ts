// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import { PaddingDefinition, GlobalSettings, SizeAndUnit,SpacingDefinition, ISeparationDefinition,
    Dictionary, StringWithSubstitutions, ContentTypes, IInput, IResourceInformation } from "./shared";
import * as Utils from "./utils";
import { HostConfig, defaultHostConfig, BaseTextDefinition, FontTypeDefinition, ColorSetDefinition, TextColorDefinition, ContainerStyleDefinition, TextStyleDefinition } from "./host-config";
import * as TextFormatters from "./text-formatters";
import { CardObject, ValidationResults } from "./card-object";
import { Versions, Version, property, BaseSerializationContext, SerializableObject, SerializableObjectSchema, StringProperty,
    BoolProperty, ValueSetProperty, EnumProperty, SerializableObjectCollectionProperty, SerializableObjectProperty, PixelSizeProperty,
    NumProperty, PropertyBag, CustomProperty, PropertyDefinition, StringArrayProperty } from "./serialization";
import { CardObjectRegistry, GlobalRegistry } from "./registry";
import { Strings } from "./strings";
import { MenuItem, PopupMenu } from "./controls";

export function renderSeparation(hostConfig: HostConfig, separationDefinition: ISeparationDefinition, orientation: Enums.Orientation): HTMLElement | undefined {
    if (separationDefinition.spacing > 0 || (separationDefinition.lineThickness && separationDefinition.lineThickness > 0)) {
        let separator = document.createElement("div");
        separator.className = hostConfig.makeCssClassName("ac-" + (orientation == Enums.Orientation.Horizontal ? "horizontal" : "vertical") + "-separator");
        separator.setAttribute("aria-hidden", "true");

        let color = separationDefinition.lineColor ? Utils.stringToCssColor(separationDefinition.lineColor) : "";

        if (orientation == Enums.Orientation.Horizontal) {
            if (separationDefinition.lineThickness) {
                separator.style.paddingTop = (separationDefinition.spacing / 2) + "px";
                separator.style.marginBottom = (separationDefinition.spacing / 2) + "px";
                separator.style.borderBottom = separationDefinition.lineThickness + "px solid " + color;
            }
            else {
                separator.style.height = separationDefinition.spacing + "px";
            }
        }
        else {
            if (separationDefinition.lineThickness) {
                separator.style.paddingLeft = (separationDefinition.spacing / 2) + "px";
                separator.style.marginRight = (separationDefinition.spacing / 2) + "px";
                separator.style.borderRight = separationDefinition.lineThickness + "px solid " + color;
            }
            else {
                separator.style.width = separationDefinition.spacing + "px";
            }
        }

        separator.style.overflow = "hidden";
        separator.style.flex = "0 0 auto";

        return separator;
    }
    else {
        return undefined;
    }
}

export type CardElementHeight = "auto" | "stretch";

export abstract class CardElement extends CardObject {
    //#region Schema

    static readonly langProperty = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig);
    static readonly isVisibleProperty = new BoolProperty(Versions.v1_2, "isVisible", true);
    static readonly separatorProperty = new BoolProperty(Versions.v1_0, "separator", false);
    static readonly heightProperty = new ValueSetProperty(
        Versions.v1_1,
        "height",
        [
            { value: "auto" },
            { value: "stretch" }
        ],
        "auto");
    static readonly horizontalAlignmentProperty = new EnumProperty(
        Versions.v1_0,
        "horizontalAlignment",
        Enums.HorizontalAlignment);
    static readonly spacingProperty = new EnumProperty(
        Versions.v1_0,
        "spacing",
        Enums.Spacing,
        Enums.Spacing.Default);

    @property(CardElement.horizontalAlignmentProperty)
    horizontalAlignment?: Enums.HorizontalAlignment;

    @property(CardElement.spacingProperty)
    spacing: Enums.Spacing;

    @property(CardElement.separatorProperty)
    separator: boolean;

    @property(CardElement.heightProperty)
    height: CardElementHeight;

    @property(CardElement.langProperty)
    get lang(): string | undefined {
        let lang = this.getValue(CardElement.langProperty);

        if (lang) {
            return lang;
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

    set lang(value: string | undefined) {
        this.setValue(CardElement.langProperty, value);
    }

    @property(CardElement.isVisibleProperty)
    get isVisible(): boolean {
        return this.getValue(CardElement.isVisibleProperty);
    }

    set isVisible(value: boolean) {
        // If the element is going to be hidden, reset any changes that were due
        // to overflow truncation (this ensures that if the element is later
        // un-hidden it has the right content)
        if (GlobalSettings.useAdvancedCardBottomTruncation && !value) {
            this.undoOverflowTruncation();
        }

        if (this.isVisible !== value) {
            this.setValue(CardElement.isVisibleProperty, value);

            this.updateRenderedElementVisibility();

            if (this._renderedElement) {
                raiseElementVisibilityChangedEvent(this);
            }
        }

        if (this._renderedElement) {
            this._renderedElement.setAttribute("aria-expanded", value.toString());
        }
    }

    //#endregion

    private _hostConfig?: HostConfig;
    private _separatorElement?: HTMLElement;
    private _truncatedDueToOverflow: boolean = false;
    private _defaultRenderedElementDisplayMode?: string;
    private _padding?: PaddingDefinition;

    private internalRenderSeparator(): HTMLElement | undefined {
        let renderedSeparator = renderSeparation(
            this.hostConfig,
            {
                spacing: this.hostConfig.getEffectiveSpacing(this.spacing),
                lineThickness: this.separator ? this.hostConfig.separator.lineThickness : undefined,
                lineColor: this.separator ? this.hostConfig.separator.lineColor : undefined
            },
            this.separatorOrientation);

            if (GlobalSettings.alwaysBleedSeparators && renderedSeparator && this.separatorOrientation == Enums.Orientation.Horizontal) {
                // Adjust separator's margins if the option to always bleed separators is turned on
                let parentContainer = this.getParentContainer();

                if (parentContainer && parentContainer.getEffectivePadding()) {
                    let parentPhysicalPadding = this.hostConfig.paddingDefinitionToSpacingDefinition(parentContainer.getEffectivePadding());

                    renderedSeparator.style.marginLeft = "-" + parentPhysicalPadding.left + "px";
                    renderedSeparator.style.marginRight = "-" + parentPhysicalPadding.right + "px";
                }
            }

            return renderedSeparator;
    }

    private updateRenderedElementVisibility() {
        let displayMode = this.isDesignMode() || this.isVisible ? this._defaultRenderedElementDisplayMode : "none";

        if (this._renderedElement) {
            if (displayMode) {
                this._renderedElement.style.display = displayMode;
            }
            else {
                this._renderedElement.style.removeProperty("display");
            }
        }

        if (this._separatorElement) {
            if (this.parent && this.parent.isFirstElement(this)) {
                this._separatorElement.style.display = "none";
            }
            else {
                if (displayMode) {
                    this._separatorElement.style.display = displayMode;
                }
                else {
                    this._separatorElement.style.removeProperty("display");
                }
            }
        }
    }

    private hideElementDueToOverflow() {
        if (this._renderedElement && this.isVisible) {
            this._renderedElement.style.visibility = "hidden";

            this.isVisible = false;
            raiseElementVisibilityChangedEvent(this, false);
        }
    }

    private showElementHiddenDueToOverflow() {
        if (this._renderedElement && !this.isVisible) {
            this._renderedElement.style.removeProperty("visibility");

            this.isVisible = true;
            raiseElementVisibilityChangedEvent(this, false);
        }
    }

    // Marked private to emulate internal access
    private handleOverflow(maxHeight: number) {
        if (this.isVisible || this.isHiddenDueToOverflow()) {
            let handled = this.truncateOverflow(maxHeight);

            // Even if we were unable to truncate the element to fit this time,
            // it still could have been previously truncated
            this._truncatedDueToOverflow = handled || this._truncatedDueToOverflow;

            if (!handled) {
                this.hideElementDueToOverflow();
            }
            else if (handled && !this.isVisible) {
                this.showElementHiddenDueToOverflow();
            }
        }
    }

    // Marked private to emulate internal access
    private resetOverflow(): boolean {
        let sizeChanged = false;

        if (this._truncatedDueToOverflow) {
            this.undoOverflowTruncation();
            this._truncatedDueToOverflow = false;
            sizeChanged = true;
        }

        if (this.isHiddenDueToOverflow()) {
            this.showElementHiddenDueToOverflow();
        }

        return sizeChanged;
    }

    protected getDefaultSerializationContext(): BaseSerializationContext {
        return new SerializationContext();
    }

    protected createPlaceholderElement(): HTMLElement {
        let styleDefinition = this.getEffectiveStyleDefinition();
        let foregroundCssColor = Utils.stringToCssColor(styleDefinition.foregroundColors.default.subtle);

        let element = document.createElement("div");
        element.style.border = "1px dashed " + foregroundCssColor;
        element.style.padding = "4px";
        element.style.minHeight = "32px";
        element.style.fontSize = "10px";
        element.style.color = <string>foregroundCssColor;
        element.innerText = "Empty " + this.getJsonTypeName();

        return element;
    }

    protected adjustRenderedElementSize(renderedElement: HTMLElement) {
        if (this.height === "auto") {
            renderedElement.style.flex = "0 0 auto";
        }
        else {
            renderedElement.style.flex = "1 1 auto";
        }
    }

    protected isDisplayed(): boolean {
        return this._renderedElement !== undefined && this.isVisible && this._renderedElement.offsetHeight > 0;
    }

    protected abstract internalRender(): HTMLElement | undefined;

    protected overrideInternalRender(): HTMLElement | undefined {
        return this.internalRender();
    }

    protected applyPadding() {
        if (this.separatorElement && this.separatorOrientation === Enums.Orientation.Horizontal) {
            if (GlobalSettings.alwaysBleedSeparators && !this.isBleeding()) {
                let padding = new PaddingDefinition();

                this.getImmediateSurroundingPadding(padding);

                let physicalPadding = this.hostConfig.paddingDefinitionToSpacingDefinition(padding);

                this.separatorElement.style.marginLeft = "-" + physicalPadding.left + "px";
                this.separatorElement.style.marginRight = "-" + physicalPadding.right + "px";
            }
            else {
                this.separatorElement.style.marginRight = "0";
                this.separatorElement.style.marginLeft = "0";
            }
        }
    }

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

    protected getDefaultPadding(): PaddingDefinition {
        return new PaddingDefinition();
    }

    protected getHasBackground(): boolean {
        return false;
    }

    protected getHasBorder(): boolean {
        return false;
    }

    protected getPadding(): PaddingDefinition | undefined {
        return this._padding;
    }

    protected setPadding(value: PaddingDefinition | undefined) {
        this._padding = value;
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return context.elementRegistry.findByName(this.getJsonTypeName()) !== undefined;
    }

    protected get useDefaultSizing(): boolean {
        return true;
    }

    protected get separatorOrientation(): Enums.Orientation {
        return Enums.Orientation.Horizontal;
    }

    protected get defaultStyle(): string {
        return Enums.ContainerStyle.Default;
    }

    customCssSelector?: string;

    parse(source: any, context?: SerializationContext) {
        super.parse(source, context ? context : new SerializationContext());
    }

    asString(): string | undefined {
        return "";
    }

    isBleeding(): boolean {
        return false;
    }

    getEffectiveStyle(): string {
        if (this.parent) {
            return this.parent.getEffectiveStyle();
        }

        return this.defaultStyle;
    }

    getEffectiveStyleDefinition(): ContainerStyleDefinition {
        return this.hostConfig.containerStyles.getStyleByName(this.getEffectiveStyle());
    }

    getEffectiveTextStyleDefinition(): TextStyleDefinition {
        if (this.parent) {
            return this.parent.getEffectiveTextStyleDefinition();
        }

        return this.hostConfig.textStyles.default;
    }

    getForbiddenActionTypes(): ActionType[] {
        return [];
    }

    getImmediateSurroundingPadding(
        result: PaddingDefinition,
        processTop: boolean = true,
        processRight: boolean = true,
        processBottom: boolean = true,
        processLeft: boolean = true) {
        if (this.parent) {
            let doProcessTop = processTop && this.parent.isTopElement(this);
            let doProcessRight = processRight && this.parent.isRightMostElement(this);
            let doProcessBottom = processBottom && this.parent.isBottomElement(this);
            let doProcessLeft = processLeft && this.parent.isLeftMostElement(this);

            let effectivePadding = this.parent.getEffectivePadding();

            if (effectivePadding) {
                if (doProcessTop && effectivePadding.top != Enums.Spacing.None) {
                    result.top = effectivePadding.top;

                    doProcessTop = false;
                }

                if (doProcessRight && effectivePadding.right != Enums.Spacing.None) {
                    result.right = effectivePadding.right;

                    doProcessRight = false;
                }

                if (doProcessBottom && effectivePadding.bottom != Enums.Spacing.None) {
                    result.bottom = effectivePadding.bottom;

                    doProcessBottom = false;
                }

                if (doProcessLeft && effectivePadding.left != Enums.Spacing.None) {
                    result.left = effectivePadding.left;

                    doProcessLeft = false;
                }
            }

            if (doProcessTop || doProcessRight || doProcessBottom || doProcessLeft) {
                this.parent.getImmediateSurroundingPadding(
                    result,
                    doProcessTop,
                    doProcessRight,
                    doProcessBottom,
                    doProcessLeft);
            }
        }
    }

    getActionCount(): number {
        return 0;
    }

    getActionAt(index: number): Action | undefined {
        throw new Error(Strings.errors.indexOutOfRange(index));
    }

    indexOfAction(action: Action): number {
        for (let i = 0; i < this.getActionCount(); i++) {
            if (this.getActionAt(i) === action) {
                return i;
            }
        }

        return -1;
    }

    remove(): boolean {
        if (this.parent && this.parent instanceof CardElementContainer) {
            return this.parent.removeItem(this);
        }

        return false;
    }

    render(): HTMLElement | undefined {
        this._renderedElement = this.overrideInternalRender();
        this._separatorElement = this.internalRenderSeparator();

        if (this._renderedElement) {
            if (this.id) {
                this._renderedElement.id = this.id;
            }

            if (this.customCssSelector) {
                this._renderedElement.classList.add(this.customCssSelector);
            }

            this._renderedElement.style.boxSizing = "border-box";
            this._defaultRenderedElementDisplayMode = this._renderedElement.style.display ? this._renderedElement.style.display : undefined;

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
        this.applyPadding();
    }

    indexOf(cardElement: CardElement): number {
        return -1;
    }

    isDesignMode(): boolean {
        let rootElement = this.getRootElement();

        return rootElement instanceof AdaptiveCard && rootElement.designMode;
    }

    isFirstElement(element: CardElement): boolean {
        return true;
    }

    isLastElement(element: CardElement): boolean {
        return true;
    }

    isAtTheVeryLeft(): boolean {
        return this.parent ? this.parent.isLeftMostElement(this) && this.parent.isAtTheVeryLeft() : true;
    }

    isAtTheVeryRight(): boolean {
        return this.parent ? this.parent.isRightMostElement(this) && this.parent.isAtTheVeryRight() : true;
    }

    isAtTheVeryTop(): boolean {
        return this.parent ? this.parent.isFirstElement(this) && this.parent.isAtTheVeryTop() : true;
    }

    isAtTheVeryBottom(): boolean {
        return this.parent ? this.parent.isLastElement(this) && this.parent.isAtTheVeryBottom() : true;
    }

    isBleedingAtTop(): boolean {
        return false;
    }

    isBleedingAtBottom(): boolean {
        return false;
    }

    isLeftMostElement(element: CardElement): boolean {
        return true;
    }

    isRightMostElement(element: CardElement): boolean {
        return true;
    }

    isTopElement(element: CardElement): boolean {
        return this.isFirstElement(element);
    }

    isBottomElement(element: CardElement): boolean {
        return this.isLastElement(element);
    }

    isHiddenDueToOverflow(): boolean {
        return this._renderedElement !== undefined && this._renderedElement.style.visibility == 'hidden';
    }

    getRootElement(): CardElement {
        return this.getRootObject() as CardElement;
    }

    getParentContainer(): Container | undefined {
        let currentElement = this.parent;

        while (currentElement) {
            if (currentElement instanceof Container) {
                return <Container>currentElement;
            }

            currentElement = currentElement.parent;
        }

        return undefined;
    }

    getAllInputs(processActions: boolean = true): Input[] {
        return [];
    }

    getResourceInformation(): IResourceInformation[] {
        return [];
    }

    getElementById(id: string): CardElement | undefined {
        return this.id === id ? this : undefined;
    }

    getActionById(id: string): Action | undefined {
        return undefined;
    }

    getEffectivePadding(): PaddingDefinition {
        let padding = this.getPadding();

        return padding ? padding : this.getDefaultPadding();
    }

    getEffectiveHorizontalAlignment(): Enums.HorizontalAlignment {
        if (this.horizontalAlignment !== undefined) {
            return this.horizontalAlignment;
        }

        if (this.parent) {
            return this.parent.getEffectiveHorizontalAlignment();
        }

        return Enums.HorizontalAlignment.Left;
    }

    get hostConfig(): HostConfig {
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

    set hostConfig(value: HostConfig) {
        this._hostConfig = value;
    }

    get index(): number {
        if (this.parent) {
            return this.parent.indexOf(this);
        }
        else {
            return 0;
        }
    }

    get isInteractive(): boolean {
        return false;
    }

    get isStandalone(): boolean {
        return true;
    }

    get isInline(): boolean {
        return false;
    }

    get hasVisibleSeparator(): boolean {
        if (this.parent && this.separatorElement) {
            return !this.parent.isFirstElement(this) && (this.isVisible || this.isDesignMode());
        }
        else {
            return false;
        }
    }

    get separatorElement(): HTMLElement | undefined {
        return this._separatorElement;
    }

    get parent(): CardElement | undefined {
        return <CardElement>this._parent;
    }
}

export class ActionProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: SerializationContext): Action | undefined {
        let parent = <CardElement>sender;

        return context.parseAction(
            parent,
            source[this.name],
            this.forbiddenActionTypes,
            parent.isDesignMode());
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: Action | undefined, context: SerializationContext) {
        context.serializeValue(target, this.name, value ? value.toJSON(context) : undefined, undefined, true);
    }

    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly forbiddenActionTypes: string[] = []) {
        super(targetVersion, name, undefined);
    }
}

export abstract class BaseTextBlock extends CardElement {
    //#region Schema

    static readonly textProperty = new StringProperty(Versions.v1_0, "text", true);
    static readonly sizeProperty = new EnumProperty(Versions.v1_0, "size", Enums.TextSize);
    static readonly weightProperty = new EnumProperty(Versions.v1_0, "weight", Enums.TextWeight);
    static readonly colorProperty = new EnumProperty(Versions.v1_0, "color", Enums.TextColor);
    static readonly isSubtleProperty = new BoolProperty(Versions.v1_0, "isSubtle");
    static readonly fontTypeProperty = new EnumProperty(Versions.v1_2, "fontType", Enums.FontType);
    static readonly selectActionProperty = new ActionProperty(Versions.v1_1, "selectAction", [ "Action.ShowCard" ]);

    protected populateSchema(schema: SerializableObjectSchema) {
        super.populateSchema(schema);

        // selectAction is declared on BaseTextBlock but is only exposed on TextRun,
        // so the property is removed from the BaseTextBlock schema.
        schema.remove(BaseTextBlock.selectActionProperty);
    }

    @property(BaseTextBlock.sizeProperty)
    size?: Enums.TextSize;

    @property(BaseTextBlock.weightProperty)
    weight?: Enums.TextWeight;

    @property(BaseTextBlock.colorProperty)
    color?: Enums.TextColor;

    @property(BaseTextBlock.fontTypeProperty)
    fontType?: Enums.FontType;

    @property(BaseTextBlock.isSubtleProperty)
    isSubtle?: boolean;

    @property(BaseTextBlock.textProperty)
    get text(): string | undefined {
        return this.getValue(BaseTextBlock.textProperty);
    }

    set text(value: string | undefined) {
        this.setText(value);
    }

    @property(BaseTextBlock.selectActionProperty)
    selectAction?: Action;

    //#endregion

    protected getFontSize(fontType: FontTypeDefinition): number {
        switch (this.effectiveSize) {
            case Enums.TextSize.Small:
                return fontType.fontSizes.small;
            case Enums.TextSize.Medium:
                return fontType.fontSizes.medium;
            case Enums.TextSize.Large:
                return fontType.fontSizes.large;
            case Enums.TextSize.ExtraLarge:
                return fontType.fontSizes.extraLarge;
            default:
                return fontType.fontSizes.default;
        }
    }

    protected getColorDefinition(colorSet: ColorSetDefinition, color: Enums.TextColor): TextColorDefinition {
        switch (color) {
            case Enums.TextColor.Accent:
                return colorSet.accent;
            case Enums.TextColor.Dark:
                return colorSet.dark;
            case Enums.TextColor.Light:
                return colorSet.light;
            case Enums.TextColor.Good:
                return colorSet.good;
            case Enums.TextColor.Warning:
                return colorSet.warning;
            case Enums.TextColor.Attention:
                return colorSet.attention;
            default:
                return colorSet.default;
        }
    }

    protected setText(value: string | undefined) {
        this.setValue(BaseTextBlock.textProperty, value);
    }

    ariaHidden: boolean = false;

    constructor(text?: string) {
        super();

        if (text) {
            this.text = text;
        }
    }

    init(textDefinition: BaseTextDefinition) {
        this.size = textDefinition.size;
        this.weight = textDefinition.weight;
        this.color = textDefinition.color;
        this.isSubtle = textDefinition.isSubtle;
    }

    asString(): string | undefined {
        return this.text;
    }

    applyStylesTo(targetElement: HTMLElement) {
        let fontType = this.hostConfig.getFontTypeDefinition(this.effectiveFontType);

        if (fontType.fontFamily) {
            targetElement.style.fontFamily = fontType.fontFamily;
        }

        let fontSize: number;

        switch (this.effectiveSize) {
            case Enums.TextSize.Small:
                fontSize = fontType.fontSizes.small;
                break;
            case Enums.TextSize.Medium:
                fontSize = fontType.fontSizes.medium;
                break;
            case Enums.TextSize.Large:
                fontSize = fontType.fontSizes.large;
                break;
            case Enums.TextSize.ExtraLarge:
                fontSize = fontType.fontSizes.extraLarge;
                break;
            default:
                fontSize = fontType.fontSizes.default;
                break;
        }

        targetElement.style.fontSize = fontSize + "px";

        let colorDefinition = this.getColorDefinition(this.getEffectiveStyleDefinition().foregroundColors, this.effectiveColor);

        targetElement.style.color = <string>Utils.stringToCssColor(this.effectiveIsSubtle ? colorDefinition.subtle : colorDefinition.default);

        let fontWeight: number;

        switch (this.effectiveWeight) {
            case Enums.TextWeight.Lighter:
                fontWeight = fontType.fontWeights.lighter;
                break;
            case Enums.TextWeight.Bolder:
                fontWeight = fontType.fontWeights.bolder;
                break;
            default:
                fontWeight = fontType.fontWeights.default;
                break;
        }

        targetElement.style.fontWeight = fontWeight.toString();

        if (this.ariaHidden) {
            targetElement.setAttribute("aria-hidden", "true");
        }
    }

    get effectiveColor(): Enums.TextColor {
        return this.color !== undefined ? this.color : this.getEffectiveTextStyleDefinition().color;
    }

    get effectiveFontType(): Enums.FontType {
        return this.fontType !== undefined ? this.fontType : this.getEffectiveTextStyleDefinition().fontType;
    }

    get effectiveIsSubtle(): boolean {
        return this.isSubtle !== undefined ? this.isSubtle : this.getEffectiveTextStyleDefinition().isSubtle;
    }

    get effectiveSize(): Enums.TextSize {
        return this.size !== undefined ? this.size : this.getEffectiveTextStyleDefinition().size;
    }

    get effectiveWeight(): Enums.TextWeight {
        return this.weight !== undefined ? this.weight : this.getEffectiveTextStyleDefinition().weight;
    }
}

export type TextBlockStyle = "default" | "heading" | "columnHeader";

export class TextBlock extends BaseTextBlock {
    //#region Schema

    static readonly wrapProperty = new BoolProperty(Versions.v1_0, "wrap", false);
    static readonly maxLinesProperty = new NumProperty(Versions.v1_0, "maxLines");
    static readonly styleProperty = new ValueSetProperty(
        Versions.v1_5,
        "style",
        [
            { value: "default" },
            { value: "columnHeader" },
            { value: "heading" }
        ]);

    @property(TextBlock.wrapProperty)
    wrap: boolean = false;

    @property(TextBlock.maxLinesProperty)
    maxLines?: number;

    @property(TextBlock.styleProperty)
    style?: TextBlockStyle;

    //#endregion

    private _computedLineHeight: number;
    private _originalInnerHtml: string;
    private _processedText?: string;
    private _treatAsPlainText: boolean = true;

    private restoreOriginalContent() {
        if (this.renderedElement !== undefined) {
            if (this.maxLines && this.maxLines > 0) {
                this.renderedElement.style.maxHeight = this._computedLineHeight * this.maxLines + "px";
            }

            this.renderedElement.innerHTML = this._originalInnerHtml;
        }
    }

    private truncateIfSupported(maxHeight: number): boolean {
        if (this.renderedElement !== undefined) {
            // For now, only truncate TextBlocks that contain just a single
            // paragraph -- since the maxLines calculation doesn't take into
            // account Markdown lists
            let children = this.renderedElement.children;
            let isTextOnly = !children.length;
            let truncationSupported = isTextOnly || children.length == 1 && (<HTMLElement>children[0]).tagName.toLowerCase() == 'p';

            if (truncationSupported) {
                let element = isTextOnly ? this.renderedElement : <HTMLElement>children[0];

                Utils.truncate(element, maxHeight, this._computedLineHeight);

                return true;
            }
        }

        return false;
    }

    protected setText(value: string) {
        super.setText(value);

        this._processedText = undefined;
    }

    protected internalRender(): HTMLElement | undefined {
        this._processedText = undefined;

        if (this.text) {
            let preProcessedText = this.preProcessPropertyValue(BaseTextBlock.textProperty);
            let hostConfig = this.hostConfig;

            let element: HTMLElement;

            if (this.forElementId) {
                let labelElement = document.createElement("label");
                labelElement.htmlFor = this.forElementId;

                element = labelElement;
            }
            else {
                element = document.createElement("div");
            }

            element.classList.add(hostConfig.makeCssClassName("ac-textBlock"));
            element.style.overflow = "hidden";

            this.applyStylesTo(element);

            if (this.style === "heading") {
                element.setAttribute("role", "heading");

                let headingLevel = this.hostConfig.textBlock.headingLevel;

                if (headingLevel !== undefined && headingLevel > 0) {
                    element.setAttribute("aria-level", headingLevel.toString());
                }
            }

            if (this.selectAction && hostConfig.supportsInteractivity) {
                element.onclick = (e) => {
                    if (this.selectAction && this.selectAction.isEnabled) {
                        e.preventDefault();
                        e.cancelBubble = true;

                        this.selectAction.execute();
                    }
                }

                this.selectAction.setupElementForAccessibility(element);

                if (this.selectAction.isEnabled) {
                    element.classList.add(hostConfig.makeCssClassName("ac-selectable"));
                }
            }

            if (!this._processedText) {
                this._treatAsPlainText = true;

                let formattedText = TextFormatters.formatText(this.lang, preProcessedText);

                if (this.useMarkdown && formattedText) {
                    if (GlobalSettings.allowMarkForTextHighlighting) {
                        formattedText = formattedText.replace(/<mark>/g, "===").replace(/<\/mark>/g, "/==/");
                    }

                    let markdownProcessingResult = AdaptiveCard.applyMarkdown(formattedText);

                    if (markdownProcessingResult.didProcess && markdownProcessingResult.outputHtml) {
                        this._processedText = markdownProcessingResult.outputHtml;
                        this._treatAsPlainText = false;

                        // Only process <mark> tag if markdown processing was applied because
                        // markdown processing is also responsible for sanitizing the input string
                        if (GlobalSettings.allowMarkForTextHighlighting && this._processedText) {
                            let markStyle: string = "";
                            let effectiveStyle = this.getEffectiveStyleDefinition();

                            if (effectiveStyle.highlightBackgroundColor) {
                                markStyle += "background-color: " + effectiveStyle.highlightBackgroundColor + ";";
                            }

                            if (effectiveStyle.highlightForegroundColor) {
                                markStyle += "color: " + effectiveStyle.highlightForegroundColor + ";";
                            }

                            if (markStyle) {
                                markStyle = 'style="' + markStyle + '"';
                            }

                            this._processedText = this._processedText.replace(/===/g, "<mark " + markStyle + ">").replace(/\/==\//g, "</mark>");
                        }
                    } else {
                        this._processedText = formattedText;
                        this._treatAsPlainText = true;
                    }
                }
                else {
                    this._processedText = formattedText;
                    this._treatAsPlainText = true;
                }
            }

            if (!this._processedText) {
                this._processedText = "";
            }

            if (this._treatAsPlainText) {
                element.innerText = this._processedText;
            }
            else {
                element.innerHTML = this._processedText;
            }

            if (element.firstElementChild instanceof HTMLElement) {
                let firstElementChild = <HTMLElement>element.firstElementChild;
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

            let anchors = element.getElementsByTagName("a");

            for (let i = 0; i < anchors.length; i++) {
                let anchor = <HTMLAnchorElement>anchors[i];
                anchor.classList.add(hostConfig.makeCssClassName("ac-anchor"));
                anchor.target = "_blank";
                anchor.onclick = (e: MouseEvent) => {
                    if (raiseAnchorClickedEvent(this, e.target as HTMLAnchorElement, e)) {
                        e.preventDefault();
                        e.cancelBubble = true;
                    }
                }
                anchor.oncontextmenu = (e: MouseEvent) => {
                    if (raiseAnchorClickedEvent(this, e.target as HTMLAnchorElement, e)) {
                        e.preventDefault();
                        e.cancelBubble = true;

                        return false;
                    }

                    return true;
                }
            }

            if (this.wrap) {
                element.style.wordWrap = "break-word";

                if (this.maxLines && this.maxLines > 0) {
                    element.style.overflow = "hidden";

                    if (Utils.isInternetExplorer() || !GlobalSettings.useWebkitLineClamp) {
                        element.style.maxHeight = (this._computedLineHeight * this.maxLines) + "px";
                    }
                    else {
                        // While non standard, --webkit-line-clamp works in every browser (except IE)
                        // and is a great solution to support the maxLines feature with ellipsis
                        // truncation. With --webkit-line-clamp there is need to use explicit line heights
                        element.style.removeProperty("line-height");
                        element.style.display = "-webkit-box";
                        element.style.webkitBoxOrient = "vertical";
                        element.style.webkitLineClamp = this.maxLines.toString();
                    }
                }
            }
            else {
                element.style.whiteSpace = "nowrap";
                element.style.textOverflow = "ellipsis";
            }

            if (GlobalSettings.useAdvancedTextBlockTruncation || GlobalSettings.useAdvancedCardBottomTruncation) {
                this._originalInnerHtml = element.innerHTML;
            }

            return element;
        }
        else {
            return undefined;
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

        if (GlobalSettings.useAdvancedTextBlockTruncation && this.maxLines) {
            let maxHeight = this._computedLineHeight * this.maxLines;

            this.truncateIfSupported(maxHeight);
        }
    }

    useMarkdown: boolean = true;
    forElementId?: string;

    applyStylesTo(targetElement: HTMLElement) {
        super.applyStylesTo(targetElement);

        switch (this.getEffectiveHorizontalAlignment()) {
            case Enums.HorizontalAlignment.Center:
                targetElement.style.textAlign = "center";
                break;
            case Enums.HorizontalAlignment.Right:
                targetElement.style.textAlign = "end";
                break;
            default:
                targetElement.style.textAlign = "start";
                break;
        }

        let lineHeights = this.hostConfig.lineHeights;

        if (lineHeights) {
            switch (this.effectiveSize) {
                case Enums.TextSize.Small:
                    this._computedLineHeight = lineHeights.small;
                    break;
                case Enums.TextSize.Medium:
                    this._computedLineHeight = lineHeights.medium;
                    break;
                case Enums.TextSize.Large:
                    this._computedLineHeight = lineHeights.large;
                    break;
                case Enums.TextSize.ExtraLarge:
                    this._computedLineHeight = lineHeights.extraLarge;
                    break;
                default:
                    this._computedLineHeight = lineHeights.default;
                    break;
            }
        }
        else {
            // Looks like 1.33 is the magic number to compute line-height
            // from font size.
            this._computedLineHeight = this.getFontSize(this.hostConfig.getFontTypeDefinition(this.effectiveFontType)) * 1.33;
        }

        targetElement.style.lineHeight = this._computedLineHeight + "px";
    }

    getJsonTypeName(): string {
        return "TextBlock";
    }

    getEffectiveTextStyleDefinition(): TextStyleDefinition {
        if (this.style) {
            return this.hostConfig.textStyles.getStyleByName(this.style);
        }

        return super.getEffectiveTextStyleDefinition();
    }

    updateLayout(processChildren: boolean = false) {
        super.updateLayout(processChildren);

        if (GlobalSettings.useAdvancedTextBlockTruncation && this.maxLines && this.isDisplayed()) {
            // Reset the element's innerHTML in case the available room for
            // content has increased
            this.restoreOriginalContent();
            this.truncateIfSupported(this._computedLineHeight * this.maxLines);
        }
    }
}

export class TextRun extends BaseTextBlock {
    //#region Schema

    static readonly italicProperty = new BoolProperty(Versions.v1_2, "italic", false);
    static readonly strikethroughProperty = new BoolProperty(Versions.v1_2, "strikethrough", false);
    static readonly highlightProperty = new BoolProperty(Versions.v1_2, "highlight", false);
    static readonly underlineProperty = new BoolProperty(Versions.v1_3, "underline", false);

    protected populateSchema(schema: SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.add(BaseTextBlock.selectActionProperty);
    }

    @property(TextRun.italicProperty)
    italic: boolean = false;

    @property(TextRun.strikethroughProperty)
    strikethrough: boolean = false;

    @property(TextRun.highlightProperty)
    highlight: boolean = false;

    @property(TextRun.underlineProperty)
    underline: boolean = false;

    //#endregion

    protected internalRender(): HTMLElement | undefined {
        if (this.text) {
            let preProcessedText = this.preProcessPropertyValue(BaseTextBlock.textProperty);
            let hostConfig = this.hostConfig;

            let formattedText = TextFormatters.formatText(this.lang, preProcessedText);

            if (!formattedText) {
                formattedText = "";
            }

            let element = document.createElement("span");
            element.classList.add(hostConfig.makeCssClassName("ac-textRun"));

            this.applyStylesTo(element);

            if (this.selectAction && hostConfig.supportsInteractivity) {
                let anchor = document.createElement("a");
                anchor.classList.add(hostConfig.makeCssClassName("ac-anchor"));

                let href = this.selectAction.getHref();

                anchor.href = href ? href : "";
                anchor.target = "_blank";
                anchor.onclick = (e) => {
                    if (this.selectAction && this.selectAction.isEnabled) {
                        e.preventDefault();
                        e.cancelBubble = true;

                        this.selectAction.execute();
                    }
                }

                this.selectAction.setupElementForAccessibility(anchor);

                anchor.innerText = formattedText;

                element.appendChild(anchor);
            }
            else {
                element.innerText = formattedText;
            }

            return element;
        }
        else {
            return undefined;
        }
    }

    applyStylesTo(targetElement: HTMLElement) {
        super.applyStylesTo(targetElement);

        if (this.italic) {
            targetElement.style.fontStyle = "italic";
        }

        if (this.strikethrough) {
            targetElement.style.textDecoration = "line-through";
        }

        if (this.highlight) {
            let colorDefinition = this.getColorDefinition(this.getEffectiveStyleDefinition().foregroundColors, this.effectiveColor);

            targetElement.style.backgroundColor = <string>Utils.stringToCssColor(this.effectiveIsSubtle ? colorDefinition.highlightColors.subtle : colorDefinition.highlightColors.default);
        }

        if (this.underline) {
            targetElement.style.textDecoration = "underline";
        }
    }

    getJsonTypeName(): string {
        return "TextRun";
    }

    get isStandalone(): boolean {
        return false;
    }

    get isInline(): boolean {
        return true;
    }
}

export class RichTextBlock extends CardElement {
    private _inlines: CardElement[] = [];

    private internalAddInline(inline: CardElement, forceAdd: boolean = false) {
        if (!inline.isInline) {
            throw new Error(Strings.errors.elementCannotBeUsedAsInline());
        }

        let doAdd: boolean = inline.parent === undefined || forceAdd;

        if (!doAdd && inline.parent != this) {
            throw new Error(Strings.errors.inlineAlreadyParented());
        }
        else {
            inline.setParent(this);

            this._inlines.push(inline);
        }
    }

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        this._inlines = [];

        if (Array.isArray(source["inlines"])) {
            for (let jsonInline of source["inlines"]) {
                let inline: CardElement | undefined;

                if (typeof jsonInline === "string") {
                    let textRun = new TextRun();
                    textRun.text = jsonInline;

                    inline = textRun;
                }
                else {
                    // No fallback for inlines in 1.2
                    inline = context.parseElement(this, jsonInline, false);
                }

                if (inline) {
                    this.internalAddInline(inline, true);
                }
            }
        }
    }

    protected internalToJSON(target: PropertyBag, context: SerializationContext) {
        super.internalToJSON(target, context);

        if (this._inlines.length > 0) {
            let jsonInlines: any[] = [];

            for (let inline of this._inlines) {
                jsonInlines.push(inline.toJSON(context));
            }

            context.serializeValue(target, "inlines", jsonInlines);
        }
    }

    protected internalRender(): HTMLElement | undefined {
        if (this._inlines.length > 0) {
            let element: HTMLElement;

            if (this.forElementId) {
                let labelElement = document.createElement("label");
                labelElement.htmlFor = this.forElementId;

                element = labelElement;
            }
            else {
                element = document.createElement("div");
            }

            element.className = this.hostConfig.makeCssClassName("ac-richTextBlock");

            switch (this.getEffectiveHorizontalAlignment()) {
                case Enums.HorizontalAlignment.Center:
                    element.style.textAlign = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.style.textAlign = "end";
                    break;
                default:
                    element.style.textAlign = "start";
                    break;
            }

            let renderedInlines: number = 0;

            for (let inline of this._inlines) {
                let renderedInline = inline.render();

                if (renderedInline) {
                    element.appendChild(renderedInline);

                    renderedInlines++;
                }
            }

            if (renderedInlines > 0) {
                return element;
            }
        }

        return undefined;
    }

    forElementId?: string;

    asString(): string | undefined {
        let result = "";

        for (let inline of this._inlines) {
            result += inline.asString();
        }

        return result;
    }

    getJsonTypeName(): string {
        return "RichTextBlock";
    }

    getInlineCount(): number {
        return this._inlines.length;
    }

    getInlineAt(index: number): CardElement {
        if (index >= 0 && index < this._inlines.length) {
            return this._inlines[index];
        }
        else {
            throw new Error(Strings.errors.indexOutOfRange(index));
        }
    }

    addInline(inline: CardElement | string) {
        if (typeof inline === "string") {
            this.internalAddInline(new TextRun(inline));
        }
        else {
            this.internalAddInline(inline);
        }
    }

    removeInline(inline: CardElement): boolean {
        let index = this._inlines.indexOf(inline);

        if (index >= 0) {
            this._inlines[index].setParent(undefined);
            this._inlines.splice(index, 1);

            return true;
        }

        return false;
    }
}

export class Fact extends SerializableObject {
    //#region Schema

    static readonly titleProperty = new StringProperty(Versions.v1_0, "title");
    static readonly valueProperty = new StringProperty(Versions.v1_0, "value");

    // For historic reasons, the "title" schema property is exposed as "name" in the OM.
    @property(Fact.titleProperty)
    name?: string;

    @property(Fact.valueProperty)
    value?: string;

    //#endregion

    protected getSchemaKey(): string {
        return "Fact";
    }

    constructor(name?: string, value?: string) {
        super();

        this.name = name;
        this.value = value;
    }
}

export class FactSet extends CardElement {
    //#region Schema

    static readonly factsProperty = new SerializableObjectCollectionProperty(Versions.v1_0, "facts", Fact);

    @property(FactSet.factsProperty)
    facts: Fact[];

    //#endregion

    protected get useDefaultSizing(): boolean {
        return false;
    }

    protected internalRender(): HTMLElement | undefined {
        let element: HTMLElement | undefined = undefined;
        let hostConfig = this.hostConfig;

        if (this.facts.length > 0) {
            element = document.createElement("table");
            element.style.borderWidth = "0px";
            element.style.borderSpacing = "0px";
            element.style.borderStyle = "none";
            element.style.borderCollapse = "collapse";
            element.style.display = "block";
            element.style.overflow = "hidden";
            element.classList.add(hostConfig.makeCssClassName("ac-factset"));
            element.setAttribute("role", "presentation");

            for (let i = 0; i < this.facts.length; i++) {
                let trElement = document.createElement("tr");

                if (i > 0) {
                    trElement.style.marginTop = hostConfig.factSet.spacing + "px";
                }

                // Title column
                let tdElement = document.createElement("td");
                tdElement.style.padding = "0";
                tdElement.classList.add(hostConfig.makeCssClassName("ac-fact-title"));

                if (hostConfig.factSet.title.maxWidth) {
                    tdElement.style.maxWidth = hostConfig.factSet.title.maxWidth + "px";
                }

                tdElement.style.verticalAlign = "top";

                let textBlock = new TextBlock();
                textBlock.setParent(this);
                textBlock.text = (!this.facts[i].name && this.isDesignMode()) ? "Title" : this.facts[i].name;
                textBlock.size = hostConfig.factSet.title.size;
                textBlock.color = hostConfig.factSet.title.color;
                textBlock.isSubtle = hostConfig.factSet.title.isSubtle;
                textBlock.weight = hostConfig.factSet.title.weight;
                textBlock.wrap = hostConfig.factSet.title.wrap;
                textBlock.spacing = Enums.Spacing.None;

                Utils.appendChild(tdElement, textBlock.render());
                Utils.appendChild(trElement, tdElement);

                // Spacer column
                tdElement = document.createElement("td");
                tdElement.style.width = "10px";

                Utils.appendChild(trElement, tdElement);

                // Value column
                tdElement = document.createElement("td");
                tdElement.style.padding = "0";
                tdElement.style.verticalAlign = "top";
                tdElement.classList.add(hostConfig.makeCssClassName("ac-fact-value"));

                textBlock = new TextBlock();
                textBlock.setParent(this);
                textBlock.text = this.facts[i].value;
                textBlock.size = hostConfig.factSet.value.size;
                textBlock.color = hostConfig.factSet.value.color;
                textBlock.isSubtle = hostConfig.factSet.value.isSubtle;
                textBlock.weight = hostConfig.factSet.value.weight;
                textBlock.wrap = hostConfig.factSet.value.wrap;
                textBlock.spacing = Enums.Spacing.None;

                Utils.appendChild(tdElement, textBlock.render());
                Utils.appendChild(trElement, tdElement);
                Utils.appendChild(element, trElement);
            }
        }

        return element;
    }

    getJsonTypeName(): string {
        return "FactSet";
    }
}

class ImageDimensionProperty extends PropertyDefinition {
    getInternalName(): string {
        return this.internalName;
    }

    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): number | undefined {
        let result: number | undefined = undefined;
        let sourceValue = source[this.name];

        if (sourceValue === undefined) {
            return this.defaultValue;
        }

        let isValid = false;

        if (typeof sourceValue === "string") {
            try {
                let size = SizeAndUnit.parse(sourceValue, true);

                if (size.unit == Enums.SizeUnit.Pixel) {
                    result = size.physicalSize;

                    isValid = true;
                }
            }
            catch {
                // Swallow the exception
            }

            // If the source value isn't valid per this property definition,
            // check its validity per the fallback property, if specified
            if (!isValid && this.fallbackProperty) {
                isValid = this.fallbackProperty.isValidValue(sourceValue, context);
            }
        }

        if (!isValid) {
            context.logParseEvent(
                sender,
                Enums.ValidationEvent.InvalidPropertyValue,
                Strings.errors.invalidPropertyValue(sourceValue, this.name));
        }

        return result;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: number | undefined, context: BaseSerializationContext) {
        context.serializeValue(
            target,
            this.name,
            typeof value === "number" && !isNaN(value) ? value + "px" : undefined);
    }

    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly internalName: string,
        readonly fallbackProperty?: ValueSetProperty) {
        super(targetVersion, name);
    }
}

export class Image extends CardElement {
    //#region Schema

    static readonly urlProperty = new StringProperty(Versions.v1_0, "url");
    static readonly altTextProperty = new StringProperty(Versions.v1_0, "altText");
    static readonly backgroundColorProperty = new StringProperty(Versions.v1_1, "backgroundColor");
    static readonly styleProperty = new EnumProperty(
        Versions.v1_0,
        "style",
        Enums.ImageStyle,
        Enums.ImageStyle.Default);
    static readonly sizeProperty = new EnumProperty(
        Versions.v1_0,
        "size",
        Enums.Size,
        Enums.Size.Auto);
    static readonly pixelWidthProperty = new ImageDimensionProperty(Versions.v1_1, "width", "pixelWidth");
    static readonly pixelHeightProperty = new ImageDimensionProperty(Versions.v1_1, "height", "pixelHeight", CardElement.heightProperty);
    static readonly selectActionProperty = new ActionProperty(Versions.v1_1, "selectAction", [ "Action.ShowCard" ]);

    protected populateSchema(schema: SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.remove(CardElement.heightProperty);
    }

    @property(Image.urlProperty)
    url?: string;

    @property(Image.altTextProperty)
    altText?: string;

    @property(Image.backgroundColorProperty)
    backgroundColor?: string;

    @property(Image.sizeProperty)
    size: Enums.Size = Enums.Size.Auto;

    @property(Image.styleProperty)
    style: Enums.ImageStyle = Enums.ImageStyle.Default;

    @property(Image.pixelWidthProperty)
    pixelWidth?: number;

    @property(Image.pixelHeightProperty)
    pixelHeight?: number;

    @property(Image.selectActionProperty)
    selectAction?: Action;

    //#endregion

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
            if (this.maxHeight) {
                // If the image is constrained in height, we set its height property and
                // auto and stretch are ignored (default to medium). THis is necessary for
                // ImageSet which uses a maximum image height as opposed to the cards width
                // as a constraining dimension
                switch (this.size) {
                    case Enums.Size.Small:
                        element.style.height = this.hostConfig.imageSizes.small + "px";
                        break;
                    case Enums.Size.Large:
                        element.style.height = this.hostConfig.imageSizes.large + "px";
                        break;
                    default:
                        element.style.height = this.hostConfig.imageSizes.medium + "px";
                        break;
                }

                element.style.maxHeight = this.maxHeight + "px";
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

                element.style.maxHeight = "100%";
            }
        }
    }

    protected get useDefaultSizing() {
        return false;
    }

    protected internalRender(): HTMLElement | undefined {
        let element: HTMLElement | undefined = undefined;

        if (this.url) {
            element = document.createElement("div");
            element.style.display = "flex";
            element.style.alignItems = "flex-start";

            // Cache hostConfig to avoid walking the parent hierarchy multiple times
            let hostConfig = this.hostConfig;

            switch (this.getEffectiveHorizontalAlignment()) {
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

            let imageElement = document.createElement("img");
            imageElement.onload = (e: Event) => {
                raiseImageLoadedEvent(this);
            }
            imageElement.onerror = (e: Event) => {
                if (this.renderedElement) {
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
                }

                raiseImageLoadedEvent(this);
            }
            imageElement.style.minWidth = "0";
            imageElement.classList.add(hostConfig.makeCssClassName("ac-image"));

            if (this.selectAction && hostConfig.supportsInteractivity) {
                imageElement.onkeypress = (e) => {
                    if (this.selectAction && this.selectAction.isEnabled && (e.code == "Enter" || e.code == "Space")) { // enter or space pressed
                        e.preventDefault();
                        e.cancelBubble = true;

                        this.selectAction.execute();
                    }
                }

                imageElement.onclick = (e) => {
                    if (this.selectAction && this.selectAction.isEnabled) {
                        e.preventDefault();
                        e.cancelBubble = true;

                        this.selectAction.execute();
                    }
                }

                this.selectAction.setupElementForAccessibility(imageElement);

                if (this.selectAction.isEnabled) {
                    imageElement.classList.add(hostConfig.makeCssClassName("ac-selectable"));
                }
            }

            this.applySize(imageElement);

            if (this.style === Enums.ImageStyle.Person) {
                imageElement.style.borderRadius = "50%";
                imageElement.style.backgroundPosition = "50% 50%";
                imageElement.style.backgroundRepeat = "no-repeat";
            }

            imageElement.style.backgroundColor = <string>Utils.stringToCssColor(this.backgroundColor);
            imageElement.src = <string>this.preProcessPropertyValue(Image.urlProperty);

            const altTextProperty = this.preProcessPropertyValue(Image.altTextProperty);
            if (altTextProperty) {
                imageElement.alt = <string>altTextProperty;
            }

            element.appendChild(imageElement);
        }

        return element;
    }

    maxHeight?: number;

    getJsonTypeName(): string {
        return "Image";
    }

    getActionById(id: string) {
        let result = super.getActionById(id);

        if (!result && this.selectAction) {
            result = this.selectAction.getActionById(id);
        }

        return result;
    }

    getResourceInformation(): IResourceInformation[] {
        return this.url ? [{ url: this.url, mimeType: "image" }] : [];
    }
}

export abstract class CardElementContainer extends CardElement {
    //#region Schema

    static readonly selectActionProperty = new ActionProperty(Versions.v1_1, "selectAction", [ "Action.ShowCard" ]);

    protected populateSchema(schema: SerializableObjectSchema) {
        super.populateSchema(schema);

        if (!this.isSelectable) {
            schema.remove(CardElementContainer.selectActionProperty);
        }
    }

    @property(CardElementContainer.selectActionProperty)
    protected _selectAction?: Action;

    //#endregion

    protected isElementAllowed(element: CardElement) {
        return this.hostConfig.supportsInteractivity || !element.isInteractive;
    }

    protected applyPadding() {
        super.applyPadding();

        if (!this.renderedElement) {
            return;
        }

        let physicalPadding = new SpacingDefinition();

        if (this.getEffectivePadding()) {
            physicalPadding = this.hostConfig.paddingDefinitionToSpacingDefinition(this.getEffectivePadding());
        }

        this.renderedElement.style.paddingTop = physicalPadding.top + "px";
        this.renderedElement.style.paddingRight = physicalPadding.right + "px";
        this.renderedElement.style.paddingBottom = physicalPadding.bottom + "px";
        this.renderedElement.style.paddingLeft = physicalPadding.left + "px";

        this.renderedElement.style.marginRight = "0";
        this.renderedElement.style.marginLeft = "0";
    }

    protected get isSelectable(): boolean {
        return false;
    }

    abstract getItemCount(): number;
    abstract getItemAt(index: number): CardElement;
    abstract getFirstVisibleRenderedItem(): CardElement | undefined;
    abstract getLastVisibleRenderedItem(): CardElement | undefined;
    abstract removeItem(item: CardElement): boolean;

    allowVerticalOverflow: boolean = false;

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        for (let i = 0; i < this.getItemCount(); i++) {
            let item = this.getItemAt(i);

            if (!this.hostConfig.supportsInteractivity && item.isInteractive) {
                context.addFailure(
                    this,
                    Enums.ValidationEvent.InteractivityNotAllowed,
                    Strings.errors.interactivityNotAllowed());
            }

            if (!this.isElementAllowed(item)) {
                context.addFailure(
                    this,
                    Enums.ValidationEvent.InteractivityNotAllowed,
                    Strings.errors.elementTypeNotAllowed(item.getJsonTypeName()));
            }

            item.internalValidateProperties(context);
        }

        if (this._selectAction) {
            this._selectAction.internalValidateProperties(context);
        }
    }

    render(): HTMLElement | undefined {
        let element = super.render();

        if (element) {
            let hostConfig = this.hostConfig;

            if (this.allowVerticalOverflow) {
                element.style.overflowX = "hidden";
                element.style.overflowY = "auto";
            }

            if (element && this.isSelectable && this._selectAction && hostConfig.supportsInteractivity) {
                element.onclick = (e) => {
                    if (this._selectAction && this._selectAction.isEnabled) {
                        e.preventDefault();
                        e.cancelBubble = true;

                        this._selectAction.execute();
                    }
                }

                element.onkeypress = (e) => {
                    if (this._selectAction && this._selectAction.isEnabled && (e.code == "Enter" || e.code == "Space")) {
                        // Enter or space pressed
                        e.preventDefault();
                        e.cancelBubble = true;

                        this._selectAction.execute();
                    }
                }

                this._selectAction.setupElementForAccessibility(element);

                if (this._selectAction.isEnabled) {
                    element.classList.add(hostConfig.makeCssClassName("ac-selectable"));
                }

            }
        }

        return element;
    }

    updateLayout(processChildren: boolean = true) {
        super.updateLayout(processChildren);

        if (processChildren) {
            for (let i = 0; i < this.getItemCount(); i++) {
                this.getItemAt(i).updateLayout();
            }
        }
    }

    getAllInputs(processActions: boolean = true): Input[] {
        let result: Input[] = [];

        for (let i = 0; i < this.getItemCount(); i++) {
            result = result.concat(this.getItemAt(i).getAllInputs(processActions));
        }

        return result;
    }

    getResourceInformation(): IResourceInformation[] {
        let result: IResourceInformation[] = [];

        for (let i = 0; i < this.getItemCount(); i++) {
            result = result.concat(this.getItemAt(i).getResourceInformation());
        }

        return result;
    }

    getElementById(id: string): CardElement | undefined {
        let result = super.getElementById(id);

        if (!result) {
            for (let i = 0; i < this.getItemCount(); i++) {
                result = this.getItemAt(i).getElementById(id);

                if (result) {
                    break;
                }
            }
        }

        return result;
    }

    /**
     * @inheritdoc
     */
    findDOMNodeOwner(node: Node): CardObject | undefined {
        let target: CardObject | undefined = undefined;

        for (let i = 0; i < this.getItemCount(); i++) {
            // recur through child elements
            target = this.getItemAt(i).findDOMNodeOwner(node);

            if (target) {
                return target;
            }
        }

        // if not found in children, defer to parent implementation
        return super.findDOMNodeOwner(node);
    }
}

export class ImageSet extends CardElementContainer {
    //#region Schema

    static readonly imagesProperty = new SerializableObjectCollectionProperty(
        Versions.v1_0,
        "images",
        Image,
        (sender: SerializableObject, item: Image) => { item.setParent(<CardElement>sender); });
    static readonly imageSizeProperty = new EnumProperty(
        Versions.v1_0,
        "imageSize",
        Enums.ImageSize,
        Enums.ImageSize.Medium);

    @property(ImageSet.imagesProperty)
    private _images: Image[] = [];

    @property(ImageSet.imageSizeProperty)
    imageSize: Enums.ImageSize = Enums.ImageSize.Medium;

    //#endregion

    protected internalRender(): HTMLElement | undefined {
        let element: HTMLElement | undefined = undefined;

        if (this._images.length > 0) {
            element = document.createElement("div");
            element.style.display = "flex";
            element.style.flexWrap = "wrap";

            for (let image of this._images) {
                switch (this.imageSize) {
                    case Enums.ImageSize.Small:
                        image.size = Enums.Size.Small;
                        break;
                    case Enums.ImageSize.Large:
                        image.size = Enums.Size.Large;
                        break;
                    default:
                        image.size = Enums.Size.Medium;
                        break;
                }

                image.maxHeight = this.hostConfig.imageSet.maxImageHeight;

                let renderedImage = image.render();

                if (renderedImage) {
                    renderedImage.style.display = "inline-flex";
                    renderedImage.style.margin = "0px";
                    renderedImage.style.marginRight = "10px";

                    Utils.appendChild(element, renderedImage);
                }
            }
        }

        return element;
    }

    getItemCount(): number {
        return this._images.length;
    }

    getItemAt(index: number): CardElement {
        return this._images[index];
    }

    getFirstVisibleRenderedItem(): CardElement | undefined {
        return this._images && this._images.length > 0 ? this._images[0] : undefined;
    }

    getLastVisibleRenderedItem(): CardElement | undefined {
        return this._images && this._images.length > 0 ? this._images[this._images.length - 1] : undefined;
    }

    removeItem(item: CardElement): boolean {
        if (item instanceof Image) {
            let itemIndex = this._images.indexOf(item);

            if (itemIndex >= 0) {
                this._images.splice(itemIndex, 1);

                item.setParent(undefined);

                this.updateLayout();

                return true;
            }
        }

        return false;
    }

    getJsonTypeName(): string {
        return "ImageSet";
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

    indexOf(cardElement: CardElement): number {
        return cardElement instanceof Image ? this._images.indexOf(cardElement) : -1;
    }
}

export class MediaSource extends SerializableObject {
    //#region Schema

    static readonly mimeTypeProperty = new StringProperty(Versions.v1_1, "mimeType");
    static readonly urlProperty = new StringProperty(Versions.v1_1, "url");

    @property(MediaSource.mimeTypeProperty)
    mimeType?: string;

    @property(MediaSource.urlProperty)
    url?: string;

    //#endregion

    protected getSchemaKey(): string {
        return "MediaSource";
    }

    constructor(url?: string, mimeType?: string) {
        super();

        this.url = url;
        this.mimeType = mimeType;
    }

    isValid(): boolean {
        return this.mimeType && this.url ? true : false;
    }

    render(): HTMLElement | undefined {
        let result: HTMLSourceElement | undefined = undefined;

        if (this.isValid()) {
            result = document.createElement("source");
            result.src = <string>this.url;
            result.type = <string>this.mimeType;
        }

        return result;
    }
}

export class Media extends CardElement {
    //#region Schema

    static readonly sourcesProperty = new SerializableObjectCollectionProperty(Versions.v1_1, "sources", MediaSource);
    static readonly posterProperty = new StringProperty(Versions.v1_1, "poster");
    static readonly altTextProperty = new StringProperty(Versions.v1_1, "altText");

    @property(Media.sourcesProperty)
    sources: MediaSource[] = [];

    @property(Media.posterProperty)
    poster?: string;

    @property(Media.altTextProperty)
    altText?: string;

    //#endregion

    static readonly supportedMediaTypes = ["audio", "video"];

    private _selectedMediaType?: string;
    private _selectedSources: MediaSource[];

    private getPosterUrl(): string | undefined {
        return this.poster ? this.poster : this.hostConfig.media.defaultPoster;
    }

    private processSources() {
        this._selectedSources = [];
        this._selectedMediaType = undefined;

        for (let source of this.sources) {
            let mimeComponents = source.mimeType ? source.mimeType.split('/') : [];

            if (mimeComponents.length == 2) {
                if (!this._selectedMediaType) {
                    let index = Media.supportedMediaTypes.indexOf(mimeComponents[0]);

                    if (index >= 0) {
                        this._selectedMediaType = Media.supportedMediaTypes[index];
                    }
                }
                if (mimeComponents[0] == this._selectedMediaType) {
                    this._selectedSources.push(source);
                }
            }
        }
    }

    private handlePlayButtonInvoke(event: UIEvent) : void
    {
        if (this.hostConfig.media.allowInlinePlayback) {
            event.preventDefault();
            event.cancelBubble = true;

            if (this.renderedElement) {
                let mediaPlayerElement = this.renderMediaPlayer();

                this.renderedElement.innerHTML = "";
                this.renderedElement.appendChild(mediaPlayerElement);

                mediaPlayerElement.play();
                mediaPlayerElement.focus();
            }
        }
        else {
            if (Media.onPlay) {
                event.preventDefault();
                event.cancelBubble = true;

                Media.onPlay(this);
            }
        }
    }

    private renderPoster(): HTMLElement {
        const playButtonArrowWidth = 12;
        const playButtonArrowHeight = 15;

        let posterRootElement = document.createElement("div");
        posterRootElement.className = this.hostConfig.makeCssClassName("ac-media-poster");
        posterRootElement.setAttribute("role", "contentinfo");
        posterRootElement.setAttribute("aria-label", this.altText ? this.altText : Strings.defaults.mediaPlayerAriaLabel());
        posterRootElement.style.position = "relative";
        posterRootElement.style.display = "flex";

        let posterUrl = this.getPosterUrl();

        if (posterUrl) {
            let posterImageElement = document.createElement("img");
            posterImageElement.style.width = "100%";
            posterImageElement.style.height = "100%";
            posterImageElement.setAttribute("role", "presentation");

            posterImageElement.onerror = (e: Event) => {
                if (posterImageElement.parentNode) {
                    posterImageElement.parentNode.removeChild(posterImageElement);
                }

                posterRootElement.classList.add("empty");
                posterRootElement.style.minHeight = "150px";
            }

            posterImageElement.src = posterUrl;

            posterRootElement.appendChild(posterImageElement);
        }
        else {
            posterRootElement.classList.add("empty");
            posterRootElement.style.minHeight = "150px";
        }

        if (this.hostConfig.supportsInteractivity && this._selectedSources.length > 0) {
            let playButtonOuterElement = document.createElement("div");
            playButtonOuterElement.tabIndex = 0;
            playButtonOuterElement.setAttribute("role", "button");
            playButtonOuterElement.setAttribute("aria-label", Strings.defaults.mediaPlayerPlayMedia());
            playButtonOuterElement.className = this.hostConfig.makeCssClassName("ac-media-playButton");
            playButtonOuterElement.style.display = "flex";
            playButtonOuterElement.style.alignItems = "center";
            playButtonOuterElement.style.justifyContent = "center";
            playButtonOuterElement.onclick = (e) => {
                this.handlePlayButtonInvoke(e);
            }

            playButtonOuterElement.onkeypress = (e: KeyboardEvent) => {
                if (e.code == "Enter" || e.code == "Space") { // space or enter
                    this.handlePlayButtonInvoke(e);
                }
            }

            let playButtonInnerElement = document.createElement("div");
            playButtonInnerElement.className = this.hostConfig.makeCssClassName("ac-media-playButton-arrow");
            playButtonInnerElement.style.width = playButtonArrowWidth + "px";
            playButtonInnerElement.style.height = playButtonArrowHeight + "px";
            playButtonInnerElement.style.borderTopWidth = (playButtonArrowHeight / 2) + "px";
            playButtonInnerElement.style.borderBottomWidth = (playButtonArrowHeight / 2) + "px";
            playButtonInnerElement.style.borderLeftWidth = playButtonArrowWidth + "px";
            playButtonInnerElement.style.borderRightWidth = "0";
            playButtonInnerElement.style.borderStyle = "solid";
            playButtonInnerElement.style.borderTopColor = "transparent";
            playButtonInnerElement.style.borderRightColor = "transparent";
            playButtonInnerElement.style.borderBottomColor = "transparent";
            playButtonInnerElement.style.transform = "translate(" + (playButtonArrowWidth / 10) + "px,0px)";

            playButtonOuterElement.appendChild(playButtonInnerElement);

            let playButtonContainer = document.createElement("div");
            playButtonContainer.style.position = "absolute";
            playButtonContainer.style.left = "0";
            playButtonContainer.style.top = "0";
            playButtonContainer.style.width = "100%";
            playButtonContainer.style.height = "100%";
            playButtonContainer.style.display = "flex";
            playButtonContainer.style.justifyContent = "center";
            playButtonContainer.style.alignItems = "center";

            playButtonContainer.appendChild(playButtonOuterElement);
            posterRootElement.appendChild(playButtonContainer);
        }

        return posterRootElement;
    }

    private renderMediaPlayer(): HTMLMediaElement {
        let mediaElement: HTMLMediaElement;

        if (this._selectedMediaType == "video") {
            let videoPlayer = document.createElement("video");

            let posterUrl = this.getPosterUrl();

            if (posterUrl) {
                videoPlayer.poster = posterUrl;
            }

            mediaElement = videoPlayer;
        }
        else {
            mediaElement = document.createElement("audio");
        }

        mediaElement.setAttribute("aria-label", this.altText ? this.altText : Strings.defaults.mediaPlayerAriaLabel());
        mediaElement.setAttribute("webkit-playsinline", "");
        mediaElement.setAttribute("playsinline", "");
        mediaElement.autoplay = true;
        mediaElement.controls = true;

        if (Utils.isMobileOS()) {
            mediaElement.muted = true;
        }

        mediaElement.preload = "none";
        mediaElement.style.width = "100%";

        for (let source of this.sources) {
            let renderedSource = source.render();

            Utils.appendChild(mediaElement, renderedSource);
        }

        return mediaElement;
    }

    protected internalRender(): HTMLElement | undefined {
        let element = <HTMLElement>document.createElement("div");
        element.className = this.hostConfig.makeCssClassName("ac-media");

        this.processSources();

        element.appendChild(this.renderPoster());

        return element;
    }

    static onPlay?: (sender: Media) => void;

    getJsonTypeName(): string {
        return "Media";
    }

    getResourceInformation(): IResourceInformation[] {
        let result: IResourceInformation[] = [];

        let posterUrl = this.getPosterUrl();

        if (posterUrl) {
            result.push({ url: posterUrl, mimeType: "image" });
        }

        for (let mediaSource of this.sources) {
            if (mediaSource.isValid()) {
                result.push(
                    {
                        url: <string>mediaSource.url,
                        mimeType: <string>mediaSource.mimeType
                    }
                );
            }
        }

        return result;
    }

    get selectedMediaType(): string | undefined {
        return this._selectedMediaType;
    }
}

export abstract class Input extends CardElement implements IInput {
    //#region Schema

    static readonly labelProperty = new StringProperty(Versions.v1_3, "label", true);
    static readonly isRequiredProperty = new BoolProperty(Versions.v1_3, "isRequired", false);
    static readonly errorMessageProperty = new StringProperty(Versions.v1_3, "errorMessage", true);

    @property(Input.labelProperty)
    label?: string;

    @property(Input.isRequiredProperty)
    isRequired: boolean;

    @property(Input.errorMessageProperty)
    errorMessage?: string;

    //#endregion

    private _outerContainerElement: HTMLElement;
    private _inputControlContainerElement: HTMLElement;
    private _renderedErrorMessageElement?: HTMLElement;
    private _renderedLabelElement?: HTMLElement;
    private _renderedInputControlElement?: HTMLElement;

    protected getAllLabelIds(): string[] {
        let labelIds: string[] = [];

        if (this.labelledBy) {
            labelIds.push(this.labelledBy);
        }

        if (this._renderedLabelElement) {
            labelIds.push(this._renderedLabelElement.id);
        }

        if (this._renderedErrorMessageElement) {
            labelIds.push(this._renderedErrorMessageElement.id);
        }

        return labelIds;
    }

    protected updateInputControlAriaLabelledBy() {
        if (this._renderedInputControlElement) {
            let labelIds: string[] = this.getAllLabelIds();

            if (labelIds.length > 0) {
                this._renderedInputControlElement.setAttribute("aria-labelledby", labelIds.join(" "));
            }
            else {
                this._renderedInputControlElement.removeAttribute("aria-labelledby");
            }
        }
    }

    protected get isNullable(): boolean {
        return true;
    }

    protected get renderedInputControlElement(): HTMLElement | undefined {
        return this._renderedInputControlElement;
    }

    protected get inputControlContainerElement(): HTMLElement {
        return this._inputControlContainerElement;
    }

    protected overrideInternalRender(): HTMLElement | undefined {
        let hostConfig = this.hostConfig;

        this._outerContainerElement = document.createElement("div");
        this._outerContainerElement.style.display = "flex";
        this._outerContainerElement.style.flexDirection = "column";

        let renderedInputControlId = Utils.generateUniqueId();

        if (this.label) {
            let labelRichTextBlock = new RichTextBlock();
            labelRichTextBlock.setParent(this);
            labelRichTextBlock.forElementId = renderedInputControlId;

            let labelInline = new TextRun(this.label);
            labelRichTextBlock.addInline(labelInline);

            if (this.isRequired) {
                labelInline.init(hostConfig.inputs.label.requiredInputs);

                let isRequiredCueInline = new TextRun(hostConfig.inputs.label.requiredInputs.suffix);
                isRequiredCueInline.color = hostConfig.inputs.label.requiredInputs.suffixColor;
                isRequiredCueInline.ariaHidden = true;

                labelRichTextBlock.addInline(isRequiredCueInline);
            }
            else {
                labelInline.init(hostConfig.inputs.label.optionalInputs);
            }

            this._renderedLabelElement = labelRichTextBlock.render();

            if (this._renderedLabelElement) {
                this._renderedLabelElement.id = Utils.generateUniqueId();
                this._renderedLabelElement.style.marginBottom = hostConfig.getEffectiveSpacing(hostConfig.inputs.label.inputSpacing) + "px";

                this._outerContainerElement.appendChild(this._renderedLabelElement);
            }
        }

        this._inputControlContainerElement = document.createElement("div");
        this._inputControlContainerElement.className = hostConfig.makeCssClassName("ac-input-container");
        this._inputControlContainerElement.style.display = "flex";

        if (this.height === "stretch") {
            this._inputControlContainerElement.style.alignItems = "stretch";
            this._inputControlContainerElement.style.flex = "1 1 auto";
        }

        this._renderedInputControlElement = this.internalRender();

        if (this._renderedInputControlElement) {
            this._renderedInputControlElement.id = renderedInputControlId;
            this._renderedInputControlElement.style.minWidth = "0px";

            if (this.isNullable && this.isRequired) {
                this._renderedInputControlElement.setAttribute("aria-required", "true");
                this._renderedInputControlElement.classList.add(hostConfig.makeCssClassName("ac-input-required"));
            }

            this._inputControlContainerElement.appendChild(this._renderedInputControlElement);
            this._outerContainerElement.appendChild(this._inputControlContainerElement);

            this.updateInputControlAriaLabelledBy();

            return this._outerContainerElement;
        }

        return undefined;
    }

    protected valueChanged() {
        if (this.isValid()) {
            this.resetValidationFailureCue();
        }

        if (this.onValueChanged) {
            this.onValueChanged(this);
        }

        raiseInputValueChangedEvent(this);
    }

    protected resetValidationFailureCue() {
        if (this.renderedInputControlElement) {
            this.renderedInputControlElement.classList.remove(this.hostConfig.makeCssClassName("ac-input-validation-failed"));

            this.updateInputControlAriaLabelledBy();

            if (this._renderedErrorMessageElement) {
                this._outerContainerElement.removeChild(this._renderedErrorMessageElement);

                this._renderedErrorMessageElement = undefined;
            }
        }
    }

    protected showValidationErrorMessage() {
        if (this.renderedElement && this.errorMessage && GlobalSettings.displayInputValidationErrors) {
            let errorMessageTextBlock = new TextBlock();
            errorMessageTextBlock.setParent(this);
            errorMessageTextBlock.text = this.errorMessage;
            errorMessageTextBlock.wrap = true;
            errorMessageTextBlock.init(this.hostConfig.inputs.errorMessage);

            this._renderedErrorMessageElement = errorMessageTextBlock.render();

            if (this._renderedErrorMessageElement) {
                this._renderedErrorMessageElement.id = Utils.generateUniqueId();
                this._outerContainerElement.appendChild(this._renderedErrorMessageElement);

                this.updateInputControlAriaLabelledBy();
            }
        }
    }

    onValueChanged: (sender: Input) => void;

    labelledBy?: string;

    abstract isSet(): boolean;

    focus() {
        if (this._renderedInputControlElement) {
            this._renderedInputControlElement.focus();
        }
    }

    isValid(): boolean {
        return true;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (!this.id) {
            context.addFailure(
                this,
                Enums.ValidationEvent.PropertyCantBeNull,
                Strings.errors.inputsMustHaveUniqueId());
        }

        if (this.isRequired) {
            if (!this.label) {
                context.addFailure(
                    this,
                    Enums.ValidationEvent.RequiredInputsShouldHaveLabel,
                    "Required inputs should have a label");
            }

            if (!this.errorMessage) {
                context.addFailure(
                    this,
                    Enums.ValidationEvent.RequiredInputsShouldHaveErrorMessage,
                    "Required inputs should have an error message");
            }
        }
    }

    validateValue(): boolean {
        this.resetValidationFailureCue();

        let result = this.isRequired ? this.isSet() && this.isValid() : this.isValid();

        if (!result && this.renderedInputControlElement) {
            this.renderedInputControlElement.classList.add(this.hostConfig.makeCssClassName("ac-input-validation-failed"));

            this.showValidationErrorMessage();
        }

        return result;
    }

    getAllInputs(processActions: boolean = true): Input[] {
        return [ this ];
    }

    abstract get value(): any;

    get isInteractive(): boolean {
        return true;
    }
}

export class TextInput extends Input {
    //#region Schema

    static readonly valueProperty = new StringProperty(Versions.v1_0, "value");
    static readonly maxLengthProperty = new NumProperty(Versions.v1_0, "maxLength");
    static readonly isMultilineProperty = new BoolProperty(Versions.v1_0, "isMultiline", false);
    static readonly placeholderProperty = new StringProperty(Versions.v1_0, "placeholder");
    static readonly styleProperty = new EnumProperty(
        Versions.v1_0,
        "style",
        Enums.InputTextStyle,
        Enums.InputTextStyle.Text,
        [
            { value: Enums.InputTextStyle.Text },
            { value: Enums.InputTextStyle.Tel },
            { value: Enums.InputTextStyle.Url },
            { value: Enums.InputTextStyle.Email },
            { value: Enums.InputTextStyle.Password, targetVersion: Versions.v1_5}
        ]
    );
    static readonly inlineActionProperty = new ActionProperty(Versions.v1_0, "inlineAction", [ "Action.ShowCard" ]);
    static readonly regexProperty = new StringProperty(Versions.v1_3, "regex", true);

    @property(TextInput.valueProperty)
    defaultValue?: string;

    @property(TextInput.maxLengthProperty)
    maxLength?: number;

    @property(TextInput.isMultilineProperty)
    isMultiline: boolean = false;

    @property(TextInput.placeholderProperty)
    placeholder?: string;

    @property(TextInput.styleProperty)
    style: Enums.InputTextStyle = Enums.InputTextStyle.Text;

    @property(TextInput.inlineActionProperty)
    inlineAction?: Action;

    @property(TextInput.regexProperty)
    regex?: string;

    //#endregion

    private setupInput(input: HTMLInputElement | HTMLTextAreaElement) {
        input.style.flex = "1 1 auto";
        input.tabIndex = 0;

        if (this.placeholder) {
            input.placeholder = this.placeholder;
            input.setAttribute("aria-label", this.placeholder)
        }

        if (this.defaultValue) {
            input.value = this.defaultValue;
        }

        if (this.maxLength && this.maxLength > 0) {
            input.maxLength = this.maxLength;
        }

        input.oninput = () => { this.valueChanged(); }
        input.onkeypress = (e: KeyboardEvent) => {
            // Ctrl+Enter pressed
            if (e.ctrlKey && e.code === "Enter" && this.inlineAction && this.inlineAction.isEnabled) {
                this.inlineAction.execute();
            }
        }
    }

    protected internalRender(): HTMLElement | undefined {
        let result: HTMLInputElement | HTMLTextAreaElement;

        if (this.isMultiline && this.style !== Enums.InputTextStyle.Password) {
            result = document.createElement("textarea");
            result.className = this.hostConfig.makeCssClassName("ac-input", "ac-textInput", "ac-multiline");

            if (this.height === "stretch") {
                result.style.height = "initial";
            }
        }
        else {
            result = document.createElement("input");
            result.className = this.hostConfig.makeCssClassName("ac-input", "ac-textInput");
            result.type = Enums.InputTextStyle[this.style].toLowerCase();
        }

        this.setupInput(result);

        return result;
    }

    protected overrideInternalRender(): HTMLElement | undefined {
        let renderedInputControl = super.overrideInternalRender();

        if (this.inlineAction) {
            let button = document.createElement("button");
            button.className = this.hostConfig.makeCssClassName(this.inlineAction.isEnabled ? "ac-inlineActionButton" : "ac-inlineActionButton-disabled");

            button.onclick = (e) => {
                if (this.inlineAction && this.inlineAction.isEnabled) {
                    e.preventDefault();
                    e.cancelBubble = true;

                    this.inlineAction.execute();
                }
            };

            if (this.inlineAction.iconUrl) {
                button.classList.add("iconOnly");

                let icon = document.createElement("img");
                icon.style.height = "100%";
                icon.setAttribute("role", "presentation");

                // The below trick is necessary as a workaround in Chrome where the icon is initially displayed
                // at its native size then resized to 100% of the button's height. This cfreates an unpleasant
                // flicker. On top of that, Chrome's flex implementation fails to prperly re-layout the button
                // after the image has loaded and been gicven its final size. The below trick also fixes that.
                icon.style.display = "none";
                icon.onload = () => {
                    icon.style.removeProperty("display");
                };
                icon.onerror = () => {
                    button.removeChild(icon);
                    button.classList.remove("iconOnly");
                    button.classList.add("textOnly");
                    button.textContent = this.inlineAction && this.inlineAction.title ? this.inlineAction.title : Strings.defaults.inlineActionTitle();
                }

                icon.src = this.inlineAction.iconUrl;

                button.appendChild(icon);
                button.title = this.inlineAction.title ? this.inlineAction.title : Strings.defaults.inlineActionTitle();
            }
            else {
                button.classList.add("textOnly");
                button.textContent = this.inlineAction.title ? this.inlineAction.title : Strings.defaults.inlineActionTitle();
            }

            this.inlineAction.setupElementForAccessibility(button, true);

            button.style.marginLeft = "8px";

            this.inputControlContainerElement.appendChild(button);
        }

        return renderedInputControl;
    }

    getJsonTypeName(): string {
        return "Input.Text";
    }

    getActionById(id: string) {
        let result = super.getActionById(id);

        if (!result && this.inlineAction) {
            result = this.inlineAction.getActionById(id);
        }

        return result;
    }

    isSet(): boolean {
        return this.value ? true : false;
    }

    isValid(): boolean {
        if (!this.value) {
            return true;
        }

        if (this.regex) {
            return new RegExp(this.regex, "g").test(this.value);
        }

        return true;
    }

    get value(): string | undefined {
        if (this.renderedInputControlElement) {
            if (this.isMultiline) {
                return (<HTMLTextAreaElement>this.renderedInputControlElement).value;
            }
            else {
                return (<HTMLInputElement>this.renderedInputControlElement).value;
            }
        }
        else {
            return undefined;
        }
    }
}

export class ToggleInput extends Input {
    //#region Schema

    static readonly valueProperty = new StringProperty(Versions.v1_0, "value");
    static readonly titleProperty = new StringProperty(Versions.v1_0, "title");
    static readonly valueOnProperty = new StringProperty(Versions.v1_0, "valueOn", true, undefined, "true", (sender: SerializableObject) => { return "true"; });
    static readonly valueOffProperty = new StringProperty(Versions.v1_0, "valueOff", true, undefined, "false", (sender: SerializableObject) => { return "false"; });
    static readonly wrapProperty = new BoolProperty(Versions.v1_2, "wrap", false);

    @property(ToggleInput.valueProperty)
    defaultValue?: string;

    @property(ToggleInput.titleProperty)
    title?: string;

    @property(ToggleInput.valueOnProperty)
    valueOn: string = "true";

    @property(ToggleInput.valueOffProperty)
    valueOff: string = "false";

    @property(ToggleInput.wrapProperty)
    wrap: boolean = false;

    //#endregion

    private _checkboxInputElement: HTMLInputElement;
    private _checkboxInputLabelElement: HTMLElement | undefined;

    protected updateInputControlAriaLabelledBy() {
        if (this._checkboxInputElement) {
            let joinedLabelIds = this.getAllLabelIds().join(" ");

            if (this._checkboxInputLabelElement && this._checkboxInputLabelElement.id) {
                joinedLabelIds += " " + this._checkboxInputLabelElement.id;
            }

            if (joinedLabelIds) {
                this._checkboxInputElement.setAttribute("aria-labelledby", joinedLabelIds);
            }
            else {
                this._checkboxInputElement.removeAttribute("aria-labelledby");
            }
        }
    }

    protected internalRender(): HTMLElement | undefined {
        let element = document.createElement("div");
        element.className = this.hostConfig.makeCssClassName("ac-input", "ac-toggleInput");
        element.style.width = "100%";
        element.style.display = "flex";
        element.style.alignItems = "center";

        this._checkboxInputElement = document.createElement("input");
        this._checkboxInputElement.id = Utils.generateUniqueId();
        this._checkboxInputElement.type = "checkbox";
        this._checkboxInputElement.style.display = "inline-block";
        this._checkboxInputElement.style.verticalAlign = "middle";
        this._checkboxInputElement.style.margin = "0";
        this._checkboxInputElement.style.flex = "0 0 auto";

        if (this.title) {
            this._checkboxInputElement.setAttribute("aria-label", this.title);
        }

        if (this.isRequired) {
            this._checkboxInputElement.setAttribute("aria-required", "true");
        }

        this._checkboxInputElement.tabIndex = 0;

        if (this.defaultValue == this.valueOn) {
            this._checkboxInputElement.checked = true;
        }

        this._checkboxInputElement.onchange = () => { this.valueChanged(); }

        Utils.appendChild(element, this._checkboxInputElement);

        if (this.title || this.isDesignMode()) {
            let label = new TextBlock();
            label.setParent(this);
            label.forElementId = this._checkboxInputElement.id;
            label.hostConfig = this.hostConfig;
            label.text = !this.title ? this.getJsonTypeName() : this.title;
            label.useMarkdown = GlobalSettings.useMarkdownInRadioButtonAndCheckbox;
            label.wrap = this.wrap;

            this._checkboxInputLabelElement = label.render();

            if (this._checkboxInputLabelElement) {
                this._checkboxInputLabelElement.id = Utils.generateUniqueId();
                this._checkboxInputLabelElement.style.display = "inline-block";
                this._checkboxInputLabelElement.style.flex = "1 1 auto";
                this._checkboxInputLabelElement.style.marginLeft = "6px";
                this._checkboxInputLabelElement.style.verticalAlign = "middle";

                let spacerElement = document.createElement("div");
                spacerElement.style.width = "6px";

                Utils.appendChild(element, spacerElement);
                Utils.appendChild(element, this._checkboxInputLabelElement);
            }
        }

        return element;
    }

    protected get isNullable(): boolean {
        return false;
    }

    getJsonTypeName(): string {
        return "Input.Toggle";
    }

    focus() {
        if (this._checkboxInputElement) {
            this._checkboxInputElement.focus();
        }
    }

    isSet(): boolean {
        if (this.isRequired) {
            return this.value === this.valueOn;
        }

        return this.value ? true : false;
    }

    get value(): string | undefined {
        if (this._checkboxInputElement) {
            return this._checkboxInputElement.checked ? this.valueOn : this.valueOff;
        }
        else {
            return undefined;
        }
    }
}

export class Choice extends SerializableObject {
    //#region Schema

    static readonly titleProperty = new StringProperty(Versions.v1_0, "title");
    static readonly valueProperty = new StringProperty(Versions.v1_0, "value");

    @property(Choice.titleProperty)
    title?: string;

    @property(Choice.valueProperty)
    value?: string;

    //#endregion

    protected getSchemaKey(): string {
        return "Choice";
    }

    constructor(title?: string, value?: string) {
        super();

        this.title = title;
        this.value = value;
    }
}

export class ChoiceSetInput extends Input {
    //#region Schema

    static readonly valueProperty = new StringProperty(Versions.v1_0, "value");
    static readonly choicesProperty = new SerializableObjectCollectionProperty(Versions.v1_0, "choices", Choice);
    static readonly styleProperty = new ValueSetProperty(
        Versions.v1_0,
        "style",
        [
            { value: "compact" },
            { value: "expanded" },
            { value: "filtered", targetVersion: Versions.v1_5 }
        ],
        "compact");
    static readonly isMultiSelectProperty = new BoolProperty(Versions.v1_0, "isMultiSelect", false);
    static readonly placeholderProperty = new StringProperty(Versions.v1_0, "placeholder");
    static readonly wrapProperty = new BoolProperty(Versions.v1_2, "wrap", false);

    @property(ChoiceSetInput.valueProperty)
    defaultValue?: string;

    @property(ChoiceSetInput.styleProperty)
    style?: "compact" | "expanded" | "filtered";

    get isCompact(): boolean {
        return !this.style || this.style === "compact";
    }

    set isCompact(value: boolean) {
        this.style = value ? undefined : "expanded";
    }

    @property(ChoiceSetInput.isMultiSelectProperty)
    isMultiSelect: boolean = false;

    @property(ChoiceSetInput.placeholderProperty)
    placeholder?: string;

    @property(ChoiceSetInput.wrapProperty)
    wrap: boolean = false;

    @property(ChoiceSetInput.choicesProperty)
    choices: Choice[] = [];

    //#endregion

    private static uniqueCategoryCounter = 0;

    private static getUniqueCategoryName(): string {
        let uniqueCategoryName = "__ac-category" + ChoiceSetInput.uniqueCategoryCounter;

        ChoiceSetInput.uniqueCategoryCounter++;

        return uniqueCategoryName;
    }

    private _uniqueCategoryName: string;
    private _selectElement: HTMLSelectElement | undefined;
    private _textInput: HTMLInputElement | undefined;
    private _toggleInputs: HTMLInputElement[] | undefined;
    private _labels: Array<HTMLElement | undefined>;

    // Make sure `aria-current` is applied to the currently-selected item
    private internalApplyAriaCurrent(): void {
        if (this._selectElement) {
            const options = this._selectElement.options;

            if (options) {
                for (let i = 0; i < options.length; i++) {
                    if (options[i].selected) {
                        options[i].setAttribute("aria-current", "true");
                    }
                    else {
                        options[i].removeAttribute("aria-current");
                    }
                }
            }
        }
    }

    private renderCompoundInput(cssClassName: string, type: "checkbox" | "radio", defaultValues: string[] | undefined): HTMLElement {
        let element = document.createElement("div");
        element.className = this.hostConfig.makeCssClassName("ac-input", cssClassName);
        element.style.width = "100%";

        this._toggleInputs = [];
        this._labels = [];

        for (let choice of this.choices) {
            let input = document.createElement("input");
            input.id = Utils.generateUniqueId();
            input.type = type;
            input.style.margin = "0";
            input.style.display = "inline-block";
            input.style.verticalAlign = "middle";
            input.style.flex = "0 0 auto";
            input.name = this.id ? this.id : this._uniqueCategoryName;

            if (this.isRequired) {
                input.setAttribute("aria-required", "true");
            }

            if (choice.value) {
                input.value = choice.value;
            }

            if (choice.title) {
                input.setAttribute("aria-label", choice.title);
            }

            if (defaultValues && choice.value) {
                if (defaultValues.indexOf(choice.value) >= 0) {
                    input.checked = true;
                }
            }

            input.onchange = () => { this.valueChanged(); }

            this._toggleInputs.push(input);

            let compoundInput = document.createElement("div");
            compoundInput.style.display = "flex";
            compoundInput.style.alignItems = "center";

            Utils.appendChild(compoundInput, input);

            let label = new TextBlock();
            label.setParent(this);
            label.forElementId = input.id;
            label.hostConfig = this.hostConfig;
            label.text = choice.title ? choice.title : "Choice " + this._toggleInputs.length;
            label.useMarkdown = GlobalSettings.useMarkdownInRadioButtonAndCheckbox;
            label.wrap = this.wrap;

            let labelElement = label.render();

            this._labels.push(labelElement);

            if (labelElement) {
                labelElement.id = Utils.generateUniqueId();
                labelElement.style.display = "inline-block";
                labelElement.style.flex = "1 1 auto";
                labelElement.style.marginLeft = "6px";
                labelElement.style.verticalAlign = "middle";

                let spacerElement = document.createElement("div");
                spacerElement.style.width = "6px";

                Utils.appendChild(compoundInput, spacerElement);
                Utils.appendChild(compoundInput, labelElement);
            }

            Utils.appendChild(element, compoundInput);
        }

        return element;
    }

    protected updateInputControlAriaLabelledBy() {
        if ((this.isMultiSelect || this.style === "expanded") && this._toggleInputs && this._labels) {
            let labelIds: string[] = this.getAllLabelIds();

            for (let i = 0; i < this._toggleInputs.length; i++) {
                let joinedLabelIds = labelIds.join(" ");
                let label = this._labels[i];

                if (label && label.id) {
                    joinedLabelIds += " " + label.id;
                }

                if (joinedLabelIds) {
                    this._toggleInputs[i].setAttribute("aria-labelledby", joinedLabelIds);
                }
                else {
                    this._toggleInputs[i].removeAttribute("aria-labelledby");
                }
            }
        }
        else {
            super.updateInputControlAriaLabelledBy();
        }
    }

    protected internalRender(): HTMLElement | undefined {
        this._uniqueCategoryName = ChoiceSetInput.getUniqueCategoryName();

        if (this.isMultiSelect) {
            // Render as a list of toggle inputs
            return this.renderCompoundInput(
                "ac-choiceSetInput-multiSelect",
                "checkbox",
                this.defaultValue ? this.defaultValue.split(this.hostConfig.choiceSetInputValueSeparator) : undefined);
        }
        else {
            if (this.style === "expanded") {
                // Render as a series of radio buttons
                return this.renderCompoundInput(
                    "ac-choiceSetInput-expanded",
                    "radio",
                    this.defaultValue ? [ this.defaultValue ] : undefined);
            }
            else if (this.style === "filtered") {
                // Render as a text input coupled with a datalist
                let inputContainer = document.createElement("div");
                inputContainer.style.width = "100%";

                this._textInput = document.createElement("input");
                this._textInput.className = this.hostConfig.makeCssClassName("ac-input", "ac-multichoiceInput", "ac-choiceSetInput-filtered");
                this._textInput.type = "text";
                this._textInput.style.width = "100%";
                this._textInput.oninput = () => {
                    this.valueChanged();

                    if (this._textInput) {
                        // Remove aria-label when value is not empty so narration software doesn't
                        // read the placeholder
                        if (this.value) {
                            this._textInput.removeAttribute("placeholder");
                            this._textInput.removeAttribute("aria-label");
                        }
                        else if (this.placeholder) {
                            this._textInput.placeholder = this.placeholder;
                            this._textInput.setAttribute("aria-label", this.placeholder);
                        }
                    }
                }

                if (this.defaultValue) {
                    this._textInput.value = this.defaultValue;
                }

                if (this.placeholder && !this._textInput.value) {
                    this._textInput.placeholder = this.placeholder;
                    this._textInput.setAttribute("aria-label", this.placeholder);
                }

                let dataList = document.createElement("datalist");
                dataList.id = Utils.generateUniqueId();

                for (let choice of this.choices) {
                    let option = document.createElement("option");
                    // To fix https://stackoverflow.com/questions/29882361/show-datalist-labels-but-submit-the-actual-value
                    // value is mapped to choice.title other than choice.value
                    option.value = <string>choice.title;
                    option.setAttribute("aria-label", <string>choice.title);

                    dataList.appendChild(option);
                }

                this._textInput.setAttribute("list", dataList.id);

                inputContainer.append(this._textInput, dataList);

                return inputContainer;
            }
            else {
                // Render as a combo box
                this._selectElement = document.createElement("select");
                this._selectElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-multichoiceInput", "ac-choiceSetInput-compact");
                this._selectElement.style.width = "100%";

                let option = document.createElement("option");
                option.selected = true;
                option.disabled = true;
                option.hidden = true;
                option.value = "";

                if (this.placeholder) {
                    option.text = this.placeholder;
                }

                Utils.appendChild(this._selectElement, option);

                for (let choice of this.choices) {
                    let option = document.createElement("option");
                    option.value = <string>choice.value;
                    option.text = <string>choice.title;
                    option.setAttribute("aria-label", <string>choice.title);

                    if (choice.value == this.defaultValue) {
                        option.selected = true;
                    }

                    Utils.appendChild(this._selectElement, option);
                }

                this._selectElement.onchange = () => {
                    this.internalApplyAriaCurrent();
                    this.valueChanged();
                }

                this.internalApplyAriaCurrent();

                return this._selectElement;
            }
        }
    }

    getJsonTypeName(): string {
        return "Input.ChoiceSet";
    }

    focus() {
        if (this._toggleInputs && (this.isMultiSelect || this.style === "expanded")) {
            if (this._toggleInputs.length > 0) {
                this._toggleInputs[0].focus();
            }
        }
        else if (this._textInput) {
            this._textInput.focus();
        }
        else {
            super.focus();
        }
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (this.choices.length == 0) {
            context.addFailure(
                this,
                Enums.ValidationEvent.CollectionCantBeEmpty,
                Strings.errors.choiceSetMustHaveAtLeastOneChoice());
        }

        for (let choice of this.choices) {
            if (!choice.title || !choice.value) {
                context.addFailure(
                    this,
                    Enums.ValidationEvent.PropertyCantBeNull,
                    Strings.errors.choiceSetChoicesMustHaveTitleAndValue());
            }
        }
    }

    isSet(): boolean {
        return this.value ? true : false;
    }

    isValid(): boolean {
        if (this._textInput) {
            if (this.value === "" || this.value === this.placeholder) {
                return true;
            }
            for (let choice of this.choices) {
                if (this.value === choice.value) {
                    return true;
                }
            }

            return false;
        }

        return super.isValid();
    }

    get value(): string | undefined {
        if (!this.isMultiSelect) {
            if (this._selectElement) {
                return this._selectElement.selectedIndex > 0 ? this._selectElement.value : undefined;
            }
            else if (this._textInput) {
                for (let choice of this.choices)
                {
                    if (choice.title && this._textInput.value === choice.title)
                    {
                        return choice.value;
                    }
                }
                return this._textInput.value;
            }
            else if (this._toggleInputs && this._toggleInputs.length > 0) {
                for (let toggleInput of this._toggleInputs) {
                    if (toggleInput.checked) {
                        return toggleInput.value;
                    }
                }
            }

            return undefined;
        }
        else {
            if (!this._toggleInputs || this._toggleInputs.length == 0) {
                return undefined;
            }

            let result: string = "";

            for (let toggleInput of this._toggleInputs) {
                if (toggleInput.checked) {
                    if (result != "") {
                        result += this.hostConfig.choiceSetInputValueSeparator;
                    }

                    result += toggleInput.value;
                }
            }

            return result ? result : undefined;
        }
    }
}

export class NumberInput extends Input {
    //#region Schema

    static readonly valueProperty = new NumProperty(Versions.v1_0, "value");
    static readonly placeholderProperty = new StringProperty(Versions.v1_0, "placeholder");
    static readonly minProperty = new NumProperty(Versions.v1_0, "min");
    static readonly maxProperty = new NumProperty(Versions.v1_0, "max");

    @property(NumberInput.valueProperty)
    defaultValue?: number;

    @property(NumberInput.minProperty)
    min?: number;

    @property(NumberInput.maxProperty)
    max?: number;

    @property(NumberInput.placeholderProperty)
    placeholder?: string;

    //#endregion

    private _numberInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement | undefined {
        this._numberInputElement = document.createElement("input");
        this._numberInputElement.setAttribute("type", "number");

        if (this.min !== undefined) {
            this._numberInputElement.setAttribute("min", this.min.toString());
        }

        if (this.max !== undefined) {
            this._numberInputElement.setAttribute("max", this.max.toString());
        }

        this._numberInputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-numberInput");
        this._numberInputElement.style.width = "100%";
        this._numberInputElement.tabIndex = 0;

        if (this.defaultValue !== undefined) {
            this._numberInputElement.valueAsNumber = this.defaultValue;
        }

        if (this.placeholder) {
            this._numberInputElement.placeholder = this.placeholder;
            this._numberInputElement.setAttribute("aria-label", this.placeholder);
        }

        this._numberInputElement.oninput = () => { this.valueChanged(); }

        return this._numberInputElement;
    }

    getJsonTypeName(): string {
        return "Input.Number";
    }

    isSet(): boolean {
        return this.value !== undefined && !isNaN(this.value);
    }

    isValid(): boolean {
        if (this.value === undefined) {
            return !this.isRequired;
        }

        let result = true;

        if (this.min !== undefined) {
            result = result && (this.value >= this.min);
        }

        if (this.max !== undefined) {
            result = result && (this.value <= this.max);
        }

        return result;
    }

    get value(): number | undefined {
        return this._numberInputElement ? this._numberInputElement.valueAsNumber : undefined;
    }
}

export class DateInput extends Input {
    //#region Schema

    static readonly valueProperty = new StringProperty(Versions.v1_0, "value");
    static readonly placeholderProperty = new StringProperty(Versions.v1_0, "placeholder");
    static readonly minProperty = new StringProperty(Versions.v1_0, "min");
    static readonly maxProperty = new StringProperty(Versions.v1_0, "max");

    @property(DateInput.valueProperty)
    defaultValue?: string;

    @property(DateInput.minProperty)
    min?: string;

    @property(DateInput.maxProperty)
    max?: string;

    @property(DateInput.placeholderProperty)
    placeholder?: string;

    //#endregion

    private _dateInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement | undefined {
        this._dateInputElement = document.createElement("input");
        this._dateInputElement.setAttribute("type", "date");

        if (this.min) {
            this._dateInputElement.setAttribute("min", this.min);
        }

        if (this.max) {
            this._dateInputElement.setAttribute("max", this.max);
        }

        if (this.placeholder) {
            this._dateInputElement.placeholder = this.placeholder;
            this._dateInputElement.setAttribute("aria-label", this.placeholder);
        }

        this._dateInputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-dateInput");
        this._dateInputElement.style.width = "100%";

        this._dateInputElement.oninput = () => { this.valueChanged(); }

        if (this.defaultValue) {
            this._dateInputElement.value = this.defaultValue;
        }

        return this._dateInputElement;
    }

    getJsonTypeName(): string {
        return "Input.Date";
    }

    isSet(): boolean {
        return this.value ? true : false;
    }

    isValid(): boolean {
        if (!this.value) {
            return !this.isRequired;
        }

        let valueAsDate = new Date(this.value);

        let result = true;

        if (this.min) {
            let minDate = new Date(this.min);

            result = result && (valueAsDate >= minDate);
        }

        if (this.max) {
            let maxDate = new Date(this.max);

            result = result && (valueAsDate <= maxDate);
        }

        return result;
    }

    get value(): string | undefined {
        return this._dateInputElement ? this._dateInputElement.value : undefined;
    }
}

export class TimeProperty extends CustomProperty<string | undefined> {
    constructor(readonly targetVersion: Version, readonly name: string) {
        super(
            targetVersion,
            name,
            (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
                let value = source[property.name];

                if (typeof value === "string" && value && /^[0-9]{2}:[0-9]{2}$/.test(value)) {
                    return value;
                }

                return undefined;
            },
            (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: string | undefined, context: BaseSerializationContext) => {
                context.serializeValue(target, property.name, value);
            });
    }
}

export class TimeInput extends Input {
    private static convertTimeStringToDate(timeString: string): Date {
        return new Date("1973-09-04T" + timeString + ":00Z");
    }

    //#region Schema

    static readonly valueProperty = new TimeProperty(Versions.v1_0, "value");
    static readonly placeholderProperty = new StringProperty(Versions.v1_0, "placeholder");
    static readonly minProperty = new TimeProperty(Versions.v1_0, "min");
    static readonly maxProperty = new TimeProperty(Versions.v1_0, "max");

    @property(TimeInput.valueProperty)
    defaultValue?: string;

    @property(TimeInput.minProperty)
    min?: string;

    @property(TimeInput.maxProperty)
    max?: string;

    @property(TimeInput.placeholderProperty)
    placeholder?: string;

    //#endregion

    private _timeInputElement: HTMLInputElement;

    protected internalRender(): HTMLElement | undefined {
        this._timeInputElement = document.createElement("input");
        this._timeInputElement.setAttribute("type", "time");
        this._timeInputElement.setAttribute("min", <string>this.min);
        this._timeInputElement.setAttribute("max", <string>this.max);
        this._timeInputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-timeInput");
        this._timeInputElement.style.width = "100%";
        this._timeInputElement.oninput = () => { this.valueChanged(); }

        if (this.placeholder) {
            this._timeInputElement.placeholder = this.placeholder;
            this._timeInputElement.setAttribute("aria-label", this.placeholder);
        }

        if (this.defaultValue) {
            this._timeInputElement.value = this.defaultValue;
        }

        return this._timeInputElement;
    }

    getJsonTypeName(): string {
        return "Input.Time";
    }

    isSet(): boolean {
        return this.value ? true : false;
    }

    isValid(): boolean {
        if (!this.value) {
            return !this.isRequired;
        }

        let valueAsDate = TimeInput.convertTimeStringToDate(this.value);

        let result = true;

        if (this.min) {
            let minDate = TimeInput.convertTimeStringToDate(this.min);

            result = result && (valueAsDate >= minDate);
        }

        if (this.max) {
            let maxDate = TimeInput.convertTimeStringToDate(this.max);

            result = result && (valueAsDate <= maxDate);
        }

        return result;
    }

    get value(): string | undefined {
        return this._timeInputElement ? this._timeInputElement.value : undefined;
    }
}

export const enum ActionButtonState {
    Normal,
    Expanded,
    Subdued
}

export type ActionType = { new(): Action };

export abstract class Action extends CardObject {
    //#region Schema

    static readonly titleProperty = new StringProperty(Versions.v1_0, "title");
    static readonly iconUrlProperty = new StringProperty(Versions.v1_1, "iconUrl");
    static readonly styleProperty = new ValueSetProperty(
        Versions.v1_2,
        "style",
        [
            { value: Enums.ActionStyle.Default },
            { value: Enums.ActionStyle.Positive },
            { value: Enums.ActionStyle.Destructive }
        ],
        Enums.ActionStyle.Default);
    static readonly modeProperty = new ValueSetProperty(
        Versions.v1_5,
        "mode",
        [
            { value: Enums.ActionMode.Primary },
            { value: Enums.ActionMode.Secondary }
        ],
        Enums.ActionMode.Primary);
    static readonly tooltipProperty = new StringProperty(Versions.v1_5, "tooltip");
    static readonly isEnabledProperty = new BoolProperty(Versions.v1_5, "isEnabled", true);

    @property(Action.titleProperty)
    title?: string;

    @property(Action.iconUrlProperty)
    iconUrl?: string;

    @property(Action.styleProperty)
    style: string = Enums.ActionStyle.Default;

    @property(Action.modeProperty)
    mode: string = Enums.ActionMode.Primary;

    @property(Action.tooltipProperty)
    tooltip?: string;

    @property(Action.isEnabledProperty)
    isEnabled: boolean;

    //#endregion

    private renderButtonContent() {
        if (this.renderedElement) {
            // Cache hostConfig for perf
            let hostConfig = this.hostConfig;

            let titleElement = document.createElement("div");
            titleElement.style.overflow = "hidden";
            titleElement.style.textOverflow = "ellipsis";

            if (!(hostConfig.actions.iconPlacement == Enums.ActionIconPlacement.AboveTitle || hostConfig.actions.allowTitleToWrap)) {
                titleElement.style.whiteSpace = "nowrap";
            }

            if (this.title) {
                titleElement.innerText = this.title;
            }

            if (!this.iconUrl) {
                this.renderedElement.classList.add("noIcon");
                this.renderedElement.appendChild(titleElement);
            }
            else {
                let iconElement = document.createElement("img");
                iconElement.src = this.iconUrl;
                iconElement.style.width = hostConfig.actions.iconSize + "px";
                iconElement.style.height = hostConfig.actions.iconSize + "px";
                iconElement.style.flex = "0 0 auto";

                if (hostConfig.actions.iconPlacement == Enums.ActionIconPlacement.AboveTitle) {
                    this.renderedElement.classList.add("iconAbove");
                    this.renderedElement.style.flexDirection = "column";

                    if (this.title) {
                        iconElement.style.marginBottom = "6px";
                    }
                }
                else {
                    this.renderedElement.classList.add("iconLeft");

                    iconElement.style.maxHeight = "100%";

                    if (this.title) {
                        iconElement.style.marginRight = "6px";
                    }
                }

                this.renderedElement.appendChild(iconElement);
                this.renderedElement.appendChild(titleElement);
            }
        }
    }

    private getParentContainer(): Container | undefined {
        if (this.parent instanceof Container) {
            return this.parent;
        }

        return this.parent ? this.parent.getParentContainer() : undefined;
    }

    private _state: ActionButtonState = ActionButtonState.Normal;
    private _actionCollection?: ActionCollection; // hold the reference to its action collection
    private _isFocusable: boolean = true;

    protected updateCssClasses() {
        if (this.parent && this.renderedElement) {
            let hostConfig = this.parent.hostConfig;

            this.renderedElement.className = hostConfig.makeCssClassName(this.isEnabled ? "ac-pushButton" : "ac-pushButton-disabled");

            let parentContainer = this.getParentContainer();

            if (parentContainer) {
                let parentContainerStyle = parentContainer.getEffectiveStyle();

                if (parentContainerStyle) {
                    this.renderedElement.classList.add("style-" + parentContainerStyle);
                }
            }

            this.renderedElement.tabIndex = this.isFocusable ? 0 : -1;

            switch (this._state) {
                case ActionButtonState.Expanded:
                    this.renderedElement.classList.add(hostConfig.makeCssClassName("expanded"));
                    break;
                case ActionButtonState.Subdued:
                    this.renderedElement.classList.add(hostConfig.makeCssClassName("subdued"));
                    break;
            }

            if (this.style && this.isEnabled) {
                if (this.style === Enums.ActionStyle.Positive) {
                    this.renderedElement.classList.add(...hostConfig.makeCssClassNames("primary", "style-positive"));
                }
                else {
                    this.renderedElement.classList.add(...hostConfig.makeCssClassNames("style-" + this.style.toLowerCase()));
                }
            }
        }
    }

    protected getDefaultSerializationContext(): BaseSerializationContext {
        return new SerializationContext();
    }

    protected internalGetReferencedInputs(): Dictionary<Input> {
        return {};
    }

    protected internalPrepareForExecution(inputs: Dictionary<Input> | undefined) {
        // Do nothing in base implementation
    }

    protected internalValidateInputs(referencedInputs: Dictionary<Input> | undefined): Input[] {
        let result: Input[] = [];

        if (referencedInputs) {
            for (let key of Object.keys(referencedInputs)) {
                let input = referencedInputs[key];

                if (!input.validateValue()) {
                    result.push(input);
                }
            }
        }

        return result;
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return context.actionRegistry.findByName(this.getJsonTypeName()) !== undefined;
    }

    protected raiseExecuteActionEvent() {
        if (this.onExecute) {
            this.onExecute(this);
        }

        raiseExecuteActionEvent(this);
    }

    onExecute: (sender: Action) => void;

    getHref(): string | undefined {
        return "";
    }

    getAriaRole(): string {
        return "button";
    }

    setupElementForAccessibility(element: HTMLElement, promoteTooltipToLabel: boolean = false) {
        element.tabIndex = this.isEnabled ? 0 : -1;

        element.setAttribute("role", this.getAriaRole());

        if (element instanceof HTMLButtonElement) {
            element.disabled = !this.isEnabled;
        }

        if (!this.isEnabled) {
            element.setAttribute("aria-disabled", "true");
        }
        else {
            element.classList.add(this.hostConfig.makeCssClassName("ac-selectable"));
        }

        if (this.title) {
            element.setAttribute("aria-label", this.title);
            element.title = this.title;
        }

        if (this.tooltip) {
            let targetAriaAttribute = promoteTooltipToLabel ? (this.title ? "aria-description" : "aria-label") : "aria-description";

            element.setAttribute(targetAriaAttribute, this.tooltip);
            element.title = this.tooltip;
        }
    }

    parse(source: any, context?: SerializationContext) {
        return super.parse(source, context ? context : new SerializationContext());
    }

    render() {
        let buttonElement = document.createElement("button");
        buttonElement.type = "button";
        buttonElement.style.display = "flex";
        buttonElement.style.alignItems = "center";
        buttonElement.style.justifyContent = "center";
        buttonElement.onclick = (e) => {
            if (this.isEnabled) {
                e.preventDefault();
                e.cancelBubble = true;

                this.execute();
            }
        };

        this._renderedElement = buttonElement;

        this.renderButtonContent();
        this.updateCssClasses();
        this.setupElementForAccessibility(buttonElement);
    }

    execute() {
        if (this._actionCollection) {
            this._actionCollection.actionExecuted(this);
        }

        this.raiseExecuteActionEvent();
    }

    prepareForExecution(): boolean {
        let referencedInputs = this.getReferencedInputs();
        let invalidInputs = this.internalValidateInputs(referencedInputs);

        if (invalidInputs.length > 0) {
            invalidInputs[0].focus();

            return false;
        }

        this.internalPrepareForExecution(referencedInputs);

        return true;
    };

    remove(): boolean {
        if (this._actionCollection) {
            return this._actionCollection.removeAction(this);
        }

        return false;
    }

    getAllInputs(processActions: boolean = true): Input[] {
        return [];
    }

    getResourceInformation(): IResourceInformation[] {
        return this.iconUrl ? [{ url: this.iconUrl, mimeType: "image" }] : [];
    }

    getActionById(id: string): Action | undefined {
        return this.id === id ? this : undefined;
    }

    getReferencedInputs(): Dictionary<Input> | undefined {
        return this.internalGetReferencedInputs();
    }

    /**
     * Validates the inputs associated with this action.
     *
     * @returns A list of inputs that failed validation, or an empty array if no input failed validation.
     */
    validateInputs(): Input[] {
        return this.internalValidateInputs(this.getReferencedInputs());
    }

    get isPrimary(): boolean {
        return this.style == Enums.ActionStyle.Positive;
    }

    set isPrimary(value: boolean) {
        if (value) {
            this.style = Enums.ActionStyle.Positive;
        }
        else {
            if (this.style == Enums.ActionStyle.Positive) {
                this.style = Enums.ActionStyle.Default;
            }
        }
    }

    get hostConfig(): HostConfig {
        return this.parent ? this.parent.hostConfig : defaultHostConfig;
    }

    get parent(): CardElement | undefined {
        return <CardElement>this._parent;
    }

    get state(): ActionButtonState {
        return this._state;
    }

    set state(value: ActionButtonState) {
        if (this._state !== value) {
            this._state = value;

            this.updateCssClasses();
        }
    }

    get isFocusable(): boolean {
        return this._isFocusable;
    }

    set isFocusable(value: boolean) {
        if (this._isFocusable !== value) {
            this._isFocusable = value;

            this.updateCssClasses();
        }
    }
}

export abstract class SubmitActionBase extends Action {
    //#region Schema

    static readonly dataProperty = new PropertyDefinition(Versions.v1_0, "data");
    static readonly associatedInputsProperty = new CustomProperty(
        Versions.v1_3,
        "associatedInputs",
        (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
            let value = source[property.name];

            if (value !== undefined && typeof value === "string") {
                return value.toLowerCase() === "none" ? "none" : "auto";
            }

            return undefined;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: string | undefined, context: BaseSerializationContext) => {
            context.serializeValue(target, property.name, value);
        });

    @property(SubmitActionBase.dataProperty)
    private _originalData?: PropertyBag;

    @property(SubmitActionBase.associatedInputsProperty)
    associatedInputs?: "auto" | "none";

    //#endregion

    private _isPrepared: boolean = false;
    private _processedData?: PropertyBag;

    protected internalGetReferencedInputs(): Dictionary<Input> {
        let result: Dictionary<Input> = {};

        if (this.associatedInputs !== "none") {
            let current: CardElement | undefined = this.parent;
            let inputs: Input[] = [];

            while (current) {
                inputs = inputs.concat(current.getAllInputs(false));

                current = current.parent;
            }

            for (let input of inputs) {
                if (input.id) {
                    result[input.id] = input;
                }
            }
        }

        return result;
    }

    protected internalPrepareForExecution(inputs: Dictionary<Input> | undefined) {
        if (this._originalData) {
            this._processedData = JSON.parse(JSON.stringify(this._originalData));
        }
        else {
            this._processedData = {};
        }

        if (this._processedData && inputs) {
            for (let key of Object.keys(inputs)) {
                let input = inputs[key];

                if (input.id && input.isSet()) {
                    this._processedData[input.id] = typeof input.value === "string" ? input.value : input.value.toString();
                }
            }
        }

        this._isPrepared = true;
    }

    get data(): object | undefined {
        return this._isPrepared ? this._processedData : this._originalData;
    }

    set data(value: object | undefined) {
        this._originalData = value;
        this._isPrepared = false;
    }
}

export class SubmitAction extends SubmitActionBase {
    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.Submit" = "Action.Submit";

    getJsonTypeName(): string {
        return SubmitAction.JsonTypeName;
    }
}

export class ExecuteAction extends SubmitActionBase {
    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.Execute" = "Action.Execute";

    //#region Schema

    static readonly verbProperty = new StringProperty(Versions.v1_4, "verb");

    @property(ExecuteAction.verbProperty)
    verb: string;

    //#endregion

    getJsonTypeName(): string {
        return ExecuteAction.JsonTypeName;
    }
}

export class OpenUrlAction extends Action {
    //#region Schema

    static readonly urlProperty = new StringProperty(Versions.v1_0, "url");

    @property(OpenUrlAction.urlProperty)
    url?: string;

    //#endregion

    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.OpenUrl" = "Action.OpenUrl";

    getJsonTypeName(): string {
        return OpenUrlAction.JsonTypeName;
    }

    getAriaRole() : string {
        return "link";
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (!this.url) {
            context.addFailure(
                this,
                Enums.ValidationEvent.PropertyCantBeNull,
                Strings.errors.propertyMustBeSet("url"));
        }
    }

    getHref(): string | undefined {
        return this.url;
    }
}

export class ToggleVisibilityAction extends Action {
    //#region Schema

    static readonly targetElementsProperty = new CustomProperty<PropertyBag>(
        Versions.v1_2,
        "targetElements",
        (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
            let result: PropertyBag = {}

            if (Array.isArray(source[property.name])) {
                for (let item of source[property.name]) {
                    if (typeof item === "string") {
                        result[item] = undefined;
                    }
                    else if (typeof item === "object") {
                        let elementId = item["elementId"];

                        if (typeof elementId === "string") {
                            result[elementId] = Utils.parseBool(item["isVisible"]);
                        }
                    }
                }
            }

            return result;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: PropertyBag, context: BaseSerializationContext) => {
            let targetElements: any[] = [];

            for (let id of Object.keys(value)) {
                if (typeof value[id] === "boolean") {
                    targetElements.push(
                        {
                            elementId: id,
                            isVisible: value[id]
                        }
                    );
                }
                else {
                    targetElements.push(id);
                }
            }

            context.serializeArray(target, property.name, targetElements);
        },
        {},
        (sender: SerializableObject) => { return {}; });

    @property(ToggleVisibilityAction.targetElementsProperty)
    targetElements: { [key: string]: any } = {};

    //#endregion

    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.ToggleVisibility" = "Action.ToggleVisibility";

    private updateAriaControlsAttribute() {
        // apply aria labels to make it clear which elements this action will toggle
        if (this.targetElements) {
            const elementIds = Object.keys(this.targetElements);

            if (this._renderedElement) {
                if (elementIds.length > 0) {
                    this._renderedElement.setAttribute("aria-controls", elementIds.join(" "));
                }
                else {
                    this._renderedElement.removeAttribute("aria-controls");
                }
            }
        }
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (!this.targetElements) {
            context.addFailure(
                this,
                Enums.ValidationEvent.PropertyCantBeNull,
                Strings.errors.propertyMustBeSet("targetElements"));
        }
    }

    getJsonTypeName(): string {
        return ToggleVisibilityAction.JsonTypeName;
    }

    render() {
        super.render();

        this.updateAriaControlsAttribute();
    }

    execute() {
        if (this.parent) {
            for (let elementId of Object.keys(this.targetElements)) {
                let targetElement = this.parent.getRootElement().getElementById(elementId);

                if (targetElement) {
                    if (typeof this.targetElements[elementId] === "boolean") {
                        targetElement.isVisible = this.targetElements[elementId];
                    }
                    else {
                        targetElement.isVisible = !targetElement.isVisible;
                    }
                }
            }
        }
    }

    addTargetElement(elementId: string, isVisible: boolean | undefined = undefined) {
        this.targetElements[elementId] = isVisible;
        this.updateAriaControlsAttribute();
    }

    removeTargetElement(elementId: string) {
        delete this.targetElements[elementId];
        this.updateAriaControlsAttribute();
    }
}

class StringWithSubstitutionProperty extends PropertyDefinition  {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): StringWithSubstitutions {
        let result = new StringWithSubstitutions();
        result.set(Utils.parseString(source[this.name]));

        return result;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: StringWithSubstitutions, context: BaseSerializationContext): void {
        context.serializeValue(target, this.name, value.getOriginal());
    }

    constructor(
        readonly targetVersion: Version,
        readonly name: string) {
        super(targetVersion, name, undefined, () => { return new StringWithSubstitutions(); });
    }
}

export class HttpHeader extends SerializableObject {
    //#region Schema

    static readonly nameProperty = new StringProperty(Versions.v1_0, "name");
    static readonly valueProperty = new StringWithSubstitutionProperty(Versions.v1_0, "value");

    protected getSchemaKey(): string {
        return "HttpHeader";
    }

    @property(HttpHeader.nameProperty)
    name: string;

    @property(HttpHeader.valueProperty)
    private _value: StringWithSubstitutions;

    //#endregion

    constructor(name: string = "", value: string = "") {
        super();

        this.name = name;
        this.value = value;
    }

    getReferencedInputs(inputs: Input[], referencedInputs: Dictionary<Input>) {
        this._value.getReferencedInputs(inputs, referencedInputs);
    }

    prepareForExecution(inputs: Dictionary<Input>) {
        this._value.substituteInputValues(inputs, ContentTypes.applicationXWwwFormUrlencoded);
    }

    get value(): string | undefined {
        return this._value.get();
    }

    set value(newValue: string | undefined) {
        this._value.set(newValue);
    }
}

export class HttpAction extends Action {
    //#region Schema

    static readonly urlProperty = new StringWithSubstitutionProperty(Versions.v1_0, "url");
    static readonly bodyProperty = new StringWithSubstitutionProperty(Versions.v1_0, "body");
    static readonly methodProperty = new StringProperty(Versions.v1_0, "method");
    static readonly headersProperty = new SerializableObjectCollectionProperty(Versions.v1_0, "headers", HttpHeader);
    static readonly ignoreInputValidationProperty = new BoolProperty(Versions.v1_3, "ignoreInputValidation", false);

    @property(HttpAction.urlProperty)
    private _url: StringWithSubstitutions;

    @property(HttpAction.bodyProperty)
    private _body: StringWithSubstitutions;

    @property(HttpAction.methodProperty)
    method?: string;

    @property(HttpAction.headersProperty)
    headers: HttpHeader[];

    @property(HttpAction.ignoreInputValidationProperty)
    private _ignoreInputValidation: boolean = false;

    //#endregion

    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.Http" = "Action.Http";

    protected internalGetReferencedInputs(): Dictionary<Input> {
        let allInputs = this.parent ? this.parent.getRootElement().getAllInputs() : [];
        let result: Dictionary<Input> = {};

        this._url.getReferencedInputs(allInputs, result);

        for (let header of this.headers) {
            header.getReferencedInputs(allInputs, result);
        }

        this._body.getReferencedInputs(allInputs, result);

        return result;
    }

    protected internalPrepareForExecution(inputs: Dictionary<Input> | undefined) {
        if (inputs) {
            this._url.substituteInputValues(inputs, ContentTypes.applicationXWwwFormUrlencoded);

            let contentType = ContentTypes.applicationJson;

            for (let header of this.headers) {
                header.prepareForExecution(inputs);

                if (header.name && header.name.toLowerCase() == "content-type") {
                    contentType = <string>header.value;
                }
            }

            this._body.substituteInputValues(inputs, contentType);
        }
    };

    getJsonTypeName(): string {
        return HttpAction.JsonTypeName;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (!this.url) {
            context.addFailure(
                this,
                Enums.ValidationEvent.PropertyCantBeNull,
                Strings.errors.propertyMustBeSet("url"));
        }

        if (this.headers.length > 0) {
            for (let header of this.headers) {
                if (!header.name) {
                    context.addFailure(
                        this,
                        Enums.ValidationEvent.PropertyCantBeNull,
                        Strings.errors.actionHttpHeadersMustHaveNameAndValue());
                }
            }
        }
    }

    get ignoreInputValidation(): boolean {
        return this._ignoreInputValidation;
    }

    set ignoreInputValidation(value: boolean) {
        this._ignoreInputValidation = value;
    }

    get url(): string | undefined {
        return this._url.get();
    }

    set url(value: string | undefined) {
        this._url.set(value);
    }

    get body(): string | undefined {
        return this._body.get();
    }

    set body(value: string | undefined) {
        this._body.set(value);
    }
}

export class ShowCardAction extends Action {
    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.ShowCard" = "Action.ShowCard";

    protected updateCssClasses() {
        super.updateCssClasses();

        if (this.renderedElement) {
            let effectiveHostConfig = this.parent ? this.parent.hostConfig : defaultHostConfig;

            this.renderedElement.classList.add(effectiveHostConfig.makeCssClassName("expandable"));
            this.renderedElement.setAttribute("aria-expanded", (this.state === ActionButtonState.Expanded).toString());
        }
    }

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        let jsonCard = source["card"];

        if (jsonCard) {
            this.card.parse(jsonCard, context);
        }
        else {
            context.logParseEvent(
                this,
                Enums.ValidationEvent.PropertyCantBeNull,
                Strings.errors.showCardMustHaveCard());
        }
    }

    protected internalToJSON(target: PropertyBag, context: SerializationContext) {
        super.internalToJSON(target, context);

        if (this.card) {
            context.serializeValue(target, "card", this.card.toJSON(context));
        }
    }

    protected raiseExecuteActionEvent() {
        if (this.hostConfig.actions.showCard.actionMode === Enums.ShowCardActionMode.Popup) {
            // Only raise the event in Popup mode.
            super.raiseExecuteActionEvent();
        }
    }

    readonly card: AdaptiveCard = new InlineAdaptiveCard();

    getJsonTypeName(): string {
        return ShowCardAction.JsonTypeName;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        this.card.internalValidateProperties(context);
    }

    setParent(value: CardElement) {
        super.setParent(value);

        this.card.setParent(value);
    }

    getAllInputs(processActions: boolean = true): Input[] {
        return this.card.getAllInputs(processActions);
    }

    getResourceInformation(): IResourceInformation[] {
        return super.getResourceInformation().concat(this.card.getResourceInformation());
    }

    getActionById(id: string): Action | undefined {
        let result = super.getActionById(id);

        if (!result) {
            result = this.card.getActionById(id);
        }

        return result;
    }
}

class OverflowAction extends Action {
    static readonly JsonTypeName: "Action.Overflow" = "Action.Overflow";

    constructor(private actions: Action[]) {
        super();

        this.title = Strings.defaults.overflowButtonText();
    }

    getActions(): readonly Action[] {
        return this.actions;
    }

    getJsonTypeName(): string {
        return ShowCardAction.JsonTypeName;
    }

    execute() {
        const shouldDisplayPopupMenu = !raiseDisplayOverflowActionMenuEvent(this, this.renderedElement);

        if (shouldDisplayPopupMenu && this.renderedElement) {
            let contextMenu = new PopupMenu();
            contextMenu.hostConfig = this.hostConfig;

            for (let i = 0; i < this.actions.length; i++) {
                const menuItem = new MenuItem(i.toString(), this.actions[i].title ?? "");
                menuItem.isEnabled = this.actions[i].isEnabled;
                menuItem.onClick = () => {
                    let actionToExecute = this.actions[i];

                    contextMenu.closePopup(false);

                    if (actionToExecute.isEnabled) {
                        actionToExecute.execute();
                    }
                };

                contextMenu.items.add(menuItem);
            };

            contextMenu.popup(this.renderedElement);
        }
	}
}

class ActionCollection {
    private _owner: CardElement;
    private _actionCardContainer: HTMLDivElement;
    private _expandedAction?: ShowCardAction;
    private _actionCard?: HTMLElement;

    private isActionAllowed(action: Action): boolean {
        let forbiddenTypes = this._owner.getForbiddenActionTypes();

        if (forbiddenTypes) {
            for (let forbiddenType of forbiddenTypes) {
                if (action.constructor === forbiddenType) {
                    return false;
                }
            }
        }

        return true;
    }

    private refreshContainer() {
        this._actionCardContainer.innerHTML = "";

        if (!this._actionCard) {
            this._actionCardContainer.style.marginTop = "0px";

            return;
        }

        this._actionCardContainer.style.marginTop = this.renderedActionCount > 0 ? this._owner.hostConfig.actions.showCard.inlineTopMargin + "px" : "0px";

        let padding = this._owner.getEffectivePadding();

        this._owner.getImmediateSurroundingPadding(padding);

        let physicalPadding = this._owner.hostConfig.paddingDefinitionToSpacingDefinition(padding);

        if (this._actionCard) {
            this._actionCard.style.paddingLeft = physicalPadding.left + "px";
            this._actionCard.style.paddingRight = physicalPadding.right + "px";

            this._actionCard.style.marginLeft = "-" + physicalPadding.left + "px";
            this._actionCard.style.marginRight = "-" + physicalPadding.right + "px";

            if (physicalPadding.bottom != 0 && !this._owner.isDesignMode()) {
                this._actionCard.style.paddingBottom = physicalPadding.bottom + "px";
                this._actionCard.style.marginBottom = "-" + physicalPadding.bottom + "px";
            }

            Utils.appendChild(this._actionCardContainer, this._actionCard);
        }
    }

    private layoutChanged() {
        this._owner.getRootElement().updateLayout();
    }

    private showActionCard(action: ShowCardAction, suppressStyle: boolean = false, raiseEvent: boolean = true) {
        (<InlineAdaptiveCard>action.card).suppressStyle = suppressStyle;

        // Always re-render a ShowCard action in design mode; reuse already rendered ShowCard (if available) otherwise
        let renderedCard = action.card.renderedElement && !this._owner.isDesignMode() ? action.card.renderedElement : action.card.render();

        this._actionCard = renderedCard;
        this._expandedAction = action;

        this.refreshContainer();

        if (raiseEvent) {
            this.layoutChanged();

            raiseInlineCardExpandedEvent(action, true);
        }
    }

    private collapseExpandedAction() {
        for (let action of this._renderedActions) {
            action.state = ActionButtonState.Normal;
        }

        let previouslyExpandedAction = this._expandedAction;

        this._expandedAction = undefined;
        this._actionCard = undefined;

        this.refreshContainer();

        if (previouslyExpandedAction) {
            this.layoutChanged();

            raiseInlineCardExpandedEvent(previouslyExpandedAction, false);
        }
    }

    private expandShowCardAction(action: ShowCardAction, raiseEvent: boolean) {
        let afterSelectedAction = false;

        for (let renderedAction of this._renderedActions) {
            // Remove actions after selected action from tabOrder, to skip focus directly to expanded card
            if (afterSelectedAction) {
                renderedAction.isFocusable = false;
            }

            if (renderedAction !== action) {
                renderedAction.state = ActionButtonState.Subdued;
            }
            else {
                renderedAction.state = ActionButtonState.Expanded;

                afterSelectedAction = true;

                if (renderedAction.renderedElement) {
                    renderedAction.renderedElement.onblur = (e) => {
                        for (let ra of this._renderedActions) {
                            ra.isFocusable = true;
                        }
                    }
                }
            }
        }

        this.showActionCard(
            action,
            !(this._owner.isAtTheVeryLeft() && this._owner.isAtTheVeryRight()),
            raiseEvent);
    }

    private _items: Action[] = [];
    private _overflowAction?: OverflowAction;
    private _renderedActions: Action[] = [];

    constructor(owner: CardElement) {
        this._owner = owner;
    }

    actionExecuted(action: Action) {
        if (!(action instanceof ShowCardAction)) {
            this.collapseExpandedAction();
        }
        else {
            if (action === this._expandedAction) {
                this.collapseExpandedAction();
            }
            else if (this._owner.hostConfig.actions.showCard.actionMode === Enums.ShowCardActionMode.Inline) {
                this.expandShowCardAction(action, true);
            }
        }
    }

    parse(source: any, context: SerializationContext) {
        this.clear();

        if (Array.isArray(source)) {
            for (let jsonAction of source) {
                let action = context.parseAction(
                    this._owner,
                    jsonAction,
                    [],
                    !this._owner.isDesignMode());

                if (action) {
                    this.addAction(action);
                }
            }
        }
    }

    toJSON(target: PropertyBag, propertyName: string, context: SerializationContext): any {
        context.serializeArray(target, propertyName, this._items);
    }

    getActionAt(id: number): Action | undefined {
        return this._items[id];
    }

    getActionCount(): number {
        return this._items.length;
    }

    getActionById(id: string): Action | undefined {
        let result: Action | undefined = undefined;

        for (let item of this._items) {
            result = item.getActionById(id);

            if (result) {
                break;
            }
        }

        return result;
    }

    validateProperties(context: ValidationResults) {
        if (this._owner.hostConfig.actions.maxActions && this._items.length > this._owner.hostConfig.actions.maxActions) {
            context.addFailure(
                this._owner,
                Enums.ValidationEvent.TooManyActions,
                Strings.errors.tooManyActions(this._owner.hostConfig.actions.maxActions));
        }

        if (this._items.length > 0 && !this._owner.hostConfig.supportsInteractivity) {
            context.addFailure(
                this._owner,
                Enums.ValidationEvent.InteractivityNotAllowed,
                Strings.errors.interactivityNotAllowed());
        }

        for (let item of this._items) {
            if (!this.isActionAllowed(item)) {
                context.addFailure(
                    this._owner,
                    Enums.ValidationEvent.ActionTypeNotAllowed,
                    Strings.errors.actionTypeNotAllowed(item.getJsonTypeName()));
            }

            item.internalValidateProperties(context);
        }
    }

    render(orientation: Enums.Orientation, isDesignMode: boolean): HTMLElement | undefined {
        // Cache hostConfig for better perf
        let hostConfig = this._owner.hostConfig;

        if (!hostConfig.supportsInteractivity) {
            return undefined;
        }

        let element = document.createElement("div");
        let maxActions = hostConfig.actions.maxActions ? Math.min(hostConfig.actions.maxActions, this._items.length) : this._items.length;

        this._actionCardContainer = document.createElement("div");
        this._renderedActions = [];

        if (hostConfig.actions.preExpandSingleShowCardAction && maxActions == 1 && this._items[0] instanceof ShowCardAction && this.isActionAllowed(this._items[0])) {
            this.showActionCard(<ShowCardAction>this._items[0], true);
            this._renderedActions.push(this._items[0]);
        }
        else {
            let buttonStrip = document.createElement("div");
            buttonStrip.className = hostConfig.makeCssClassName("ac-actionSet");
            buttonStrip.style.display = "flex";
            buttonStrip.setAttribute("role", "menubar");

            if (orientation == Enums.Orientation.Horizontal) {
                buttonStrip.style.flexDirection = "row";

                if (this._owner.horizontalAlignment && hostConfig.actions.actionAlignment != Enums.ActionAlignment.Stretch) {
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
                    switch (hostConfig.actions.actionAlignment) {
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

                if (this._owner.horizontalAlignment && hostConfig.actions.actionAlignment != Enums.ActionAlignment.Stretch) {
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
                    switch (hostConfig.actions.actionAlignment) {
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

            const allowedActions = this._items.filter(this.isActionAllowed.bind(this));

            let primaryActions: Action[] = [];
            let secondaryActions: Action[] = [];

            if (!this._owner.isDesignMode()) {
                allowedActions.forEach(action => action.mode === Enums.ActionMode.Secondary ? secondaryActions.push(action) : primaryActions.push(action));

                // If primaryActions.length > maxActions, extra actions are moved to overflow
                const overflowPrimaryActions = primaryActions.splice(hostConfig.actions.maxActions);

                if (GlobalSettings.allowMoreThanMaxActionsInOverflowMenu) {
                    secondaryActions.push(...overflowPrimaryActions);
                }

                let shouldRenderOverflowActionButton = true;

                if (secondaryActions.length > 0) {
                    if (!this._overflowAction) {
                        this._overflowAction = new OverflowAction(secondaryActions);
                        this._overflowAction.setParent(this._owner);
                        this._overflowAction["_actionCollection"] = this;
                    }

                    let isRootAction = this._owner instanceof AdaptiveCard && !this._owner.parent;
                    shouldRenderOverflowActionButton = !raiseRenderOverflowActionsEvent(this._overflowAction, isRootAction);
                }

                if (this._overflowAction && shouldRenderOverflowActionButton) {
                    primaryActions.push(this._overflowAction);
                }
            }
            else {
                primaryActions = allowedActions;
            }

            for (let i = 0; i < primaryActions.length; i++) {
                let action = primaryActions[i];
                action.render();

                if (action.renderedElement) {
                    if (primaryActions.length > 1) {
                        action.renderedElement.setAttribute("aria-posinset", (i + 1).toString());
                        action.renderedElement.setAttribute("aria-setsize", primaryActions.length.toString());
                        action.renderedElement.setAttribute("role", "menuitem");
                    }

                    if (hostConfig.actions.actionsOrientation == Enums.Orientation.Horizontal && hostConfig.actions.actionAlignment == Enums.ActionAlignment.Stretch) {
                        action.renderedElement.style.flex = "0 1 100%";
                    }
                    else {
                        action.renderedElement.style.flex = "0 1 auto";
                    }

                    buttonStrip.appendChild(action.renderedElement);

                    this._renderedActions.push(action);

                    if (i < primaryActions.length - 1 && hostConfig.actions.buttonSpacing > 0) {
                        let spacer = document.createElement("div");

                        if (orientation === Enums.Orientation.Horizontal) {
                            spacer.style.flex = "0 0 auto";
                            spacer.style.width = hostConfig.actions.buttonSpacing + "px";
                        }
                        else {
                            spacer.style.height = hostConfig.actions.buttonSpacing + "px";
                        }

                        Utils.appendChild(buttonStrip, spacer);
                    }
                }
            }

            let buttonStripContainer = document.createElement("div");
            buttonStripContainer.style.overflow = "hidden";
            buttonStripContainer.appendChild(buttonStrip);

            Utils.appendChild(element, buttonStripContainer);
        }

        Utils.appendChild(element, this._actionCardContainer);

        for (let renderedAction of this._renderedActions) {
            if (renderedAction.state == ActionButtonState.Expanded) {
                this.expandShowCardAction(<ShowCardAction>renderedAction, false);

                break;
            }
        }

        return this._renderedActions.length > 0 ? element : undefined;
    }

    addAction(action: Action) {
        if (!action) {
            throw new Error("The action parameter cannot be null.");
        }

        if ((!action.parent || action.parent === this._owner) && this._items.indexOf(action) < 0) {
            this._items.push(action);

            if (!action.parent) {
                action.setParent(this._owner);
            }

            action["_actionCollection"] = this;
        }
        else {
            throw new Error(Strings.errors.actionAlreadyParented());
        }
    }

    removeAction(action: Action): boolean {
        if (this.expandedAction && this._expandedAction == action) {
            this.collapseExpandedAction();
        }

        let actionIndex = this._items.indexOf(action);

        if (actionIndex >= 0) {
            this._items.splice(actionIndex, 1);

            action.setParent(undefined);

            action["_actionCollection"] = undefined;

            for (let i = 0; i < this._renderedActions.length; i++) {
                if (this._renderedActions[i] == action) {
                    this._renderedActions.splice(i, 1);

                    break;
                }
            }

            return true;
        }

        return false;
    }

    clear() {
        this._items = [];
        this._renderedActions = [];
        this._expandedAction = undefined;
    }

    getAllInputs(processActions: boolean = true): Input[] {
        let result: Input[] = [];

        if (processActions) {
            for (let action of this._items) {
                result = result.concat(action.getAllInputs());
            }
        }

        return result;
    }

    getResourceInformation(): IResourceInformation[] {
        let result: IResourceInformation[] = [];

        for (let action of this._items) {
            result = result.concat(action.getResourceInformation());
        }

        return result;
    }

    get renderedActionCount(): number {
        return this._renderedActions.length;
    }

    get expandedAction(): ShowCardAction | undefined {
        return this._expandedAction;
    }
}

export class ActionSet extends CardElement {
    //#region Schema

    static readonly orientationProperty = new EnumProperty(Versions.v1_1, "orientation", Enums.Orientation);

    @property(ActionSet.orientationProperty)
    orientation?: Enums.Orientation;

    //#endregion

    private _actionCollection: ActionCollection;

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        this._actionCollection.parse(source["actions"], context);
    }

    protected internalToJSON(target: PropertyBag, context: SerializationContext) {
        super.internalToJSON(target, context);

        this._actionCollection.toJSON(target, "actions", context);
    }

    protected internalRender(): HTMLElement | undefined {
        return this._actionCollection.render(this.orientation !== undefined ? this.orientation : this.hostConfig.actions.actionsOrientation, this.isDesignMode());
    }

    constructor() {
        super();

        this._actionCollection = new ActionCollection(this);
    }

    isBleedingAtBottom(): boolean {
        if (this._actionCollection.renderedActionCount == 0) {
            return super.isBleedingAtBottom();
        }
        else {
            if (this._actionCollection.getActionCount() == 1) {
                return this._actionCollection.expandedAction !== undefined && !this.hostConfig.actions.preExpandSingleShowCardAction;
            }
            else {
                return this._actionCollection.expandedAction !== undefined;
            }
        }
    }

    getJsonTypeName(): string {
        return "ActionSet";
    }

    getActionCount(): number {
        return this._actionCollection.getActionCount();
    }

    getActionAt(index: number): Action | undefined {
        if (index >= 0 && index < this.getActionCount()) {
            return this._actionCollection.getActionAt(index);
        }
        else {
            return super.getActionAt(index);
        }
    }

    getActionById(id: string): Action | undefined {
        let result: Action | undefined = this._actionCollection.getActionById(id);

        return result ? result : super.getActionById(id);
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        this._actionCollection.validateProperties(context);
    }

    addAction(action: Action) {
        this._actionCollection.addAction(action);
    }

    getAllInputs(processActions: boolean = true): Input[] {
        return processActions ? this._actionCollection.getAllInputs() : [];
    }

    getResourceInformation(): IResourceInformation[] {
        return this._actionCollection.getResourceInformation();
    }

    /**
     * @inheritdoc
     */
    findDOMNodeOwner(node: Node): CardObject | undefined {
        let target: CardObject | undefined = undefined;

        for (let i = 0; i < this.getActionCount(); i++) {
            let action = this.getActionAt(i);

            if (action) {
                // recur through each Action
                target = action.findDOMNodeOwner(node);

                if (target) {
                    return target;
                }
            }
        }

        // if not found in any Action, defer to parent implementation
        return super.findDOMNodeOwner(node);
    }

    get isInteractive(): boolean {
        return true;
    }
}

export class ContainerStyleProperty extends ValueSetProperty {
    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly defaultValue?: string,
        readonly onGetInitialValue?: (sender: SerializableObject) => string) {
        super(
            targetVersion,
            name,
            [
                { value: Enums.ContainerStyle.Default },
                { value: Enums.ContainerStyle.Emphasis },
                { targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Accent },
                { targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Good },
                { targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Attention },
                { targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Warning }
            ],
            defaultValue,
            onGetInitialValue);
    }
}

export abstract class StylableCardElementContainer extends CardElementContainer {
    //#region Schema

    static readonly styleProperty = new ContainerStyleProperty(Versions.v1_0, "style");

    @property(StylableCardElementContainer.styleProperty)
    get style(): string | undefined {
        if (this.allowCustomStyle) {
            let style = this.getValue(StylableCardElementContainer.styleProperty);

            if (style && this.hostConfig.containerStyles.getStyleByName(style)) {
                return style;
            }
        }

        return undefined;
    }

    set style(value: string | undefined) {
        this.setValue(StylableCardElementContainer.styleProperty, value);
    }

    //#endregion

    protected get allowCustomStyle(): boolean {
        return true;
    }

    protected get hasExplicitStyle(): boolean {
        return this.getValue(StylableCardElementContainer.styleProperty) !== undefined;
    }

    protected applyBorder() {
        // No border in base implementation
    }

    protected applyBackground() {
        if (this.renderedElement) {
            let styleDefinition = this.hostConfig.containerStyles.getStyleByName(this.style, this.hostConfig.containerStyles.getStyleByName(this.defaultStyle));

            if (styleDefinition.backgroundColor) {
                const bgColor = <string>Utils.stringToCssColor(styleDefinition.backgroundColor);
                this.renderedElement.style.backgroundColor = bgColor;
            }
        }
    }

    protected applyPadding() {
        super.applyPadding();

        if (!this.renderedElement) {
            return;
        }

        let physicalPadding = new SpacingDefinition();

        if (this.getEffectivePadding()) {
            physicalPadding = this.hostConfig.paddingDefinitionToSpacingDefinition(this.getEffectivePadding());
        }

        this.renderedElement.style.paddingTop = physicalPadding.top + "px";
        this.renderedElement.style.paddingRight = physicalPadding.right + "px";
        this.renderedElement.style.paddingBottom = physicalPadding.bottom + "px";
        this.renderedElement.style.paddingLeft = physicalPadding.left + "px";

        if (this.isBleeding()) {
            // Bleed into the first parent that does have padding
            let padding = new PaddingDefinition();

            this.getImmediateSurroundingPadding(padding);

            let surroundingPadding = this.hostConfig.paddingDefinitionToSpacingDefinition(padding);

            this.renderedElement.style.marginRight = "-" + surroundingPadding.right + "px";
            this.renderedElement.style.marginLeft = "-" + surroundingPadding.left + "px";

            if (!this.isDesignMode()) {
                this.renderedElement.style.marginTop = "-" + surroundingPadding.top + "px";
                this.renderedElement.style.marginBottom = "-" + surroundingPadding.bottom + "px";
            }

            if (this.separatorElement && this.separatorOrientation == Enums.Orientation.Horizontal) {
                this.separatorElement.style.marginLeft = "-" + surroundingPadding.left + "px";
                this.separatorElement.style.marginRight = "-" + surroundingPadding.right + "px";
            }
        }
        else {
            this.renderedElement.style.marginRight = "0";
            this.renderedElement.style.marginLeft = "0";
            this.renderedElement.style.marginTop = "0";
            this.renderedElement.style.marginBottom = "0";

            if (this.separatorElement && this.separatorOrientation === Enums.Orientation.Horizontal) {
                this.separatorElement.style.marginRight = "0";
                this.separatorElement.style.marginLeft = "0";
            }
        }
    }

    protected getHasBackground(): boolean {
        let currentElement: CardElement | undefined = this.parent;

        while (currentElement) {
            let currentElementHasBackgroundImage = currentElement instanceof Container ? currentElement.backgroundImage.isValid() : false;

            if (currentElement instanceof StylableCardElementContainer) {
                if (this.hasExplicitStyle && (currentElement.getEffectiveStyle() != this.getEffectiveStyle() || currentElementHasBackgroundImage)) {
                    return true;
                }
            }

            currentElement = currentElement.parent;
        }

        return false;
    }

    protected getDefaultPadding(): PaddingDefinition {
        return this.getHasBackground() || this.getHasBorder() ?
            new PaddingDefinition(
                Enums.Spacing.Padding,
                Enums.Spacing.Padding,
                Enums.Spacing.Padding,
                Enums.Spacing.Padding) : super.getDefaultPadding();
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        let explicitStyle = this.getValue(StylableCardElementContainer.styleProperty);

        if (explicitStyle !== undefined) {
            let styleDefinition = this.hostConfig.containerStyles.getStyleByName(explicitStyle);

            if (!styleDefinition) {
                context.addFailure(
                    this,
                    Enums.ValidationEvent.InvalidPropertyValue,
                    Strings.errors.invalidPropertyValue(explicitStyle, "style"));
            }
        }
    }

    render(): HTMLElement | undefined {
        let renderedElement = super.render();

        if (renderedElement && this.getHasBackground()) {
            this.applyBackground();
        }

        this.applyBorder();

        return renderedElement;
    }

    getEffectiveStyle(): string {
        let effectiveStyle = this.style;

        return effectiveStyle ? effectiveStyle : super.getEffectiveStyle();
    }
}

export abstract class ContainerBase extends StylableCardElementContainer {
    //#region Schema

    static readonly bleedProperty = new BoolProperty(Versions.v1_2, "bleed", false);
    static readonly minHeightProperty = new PixelSizeProperty(Versions.v1_2, "minHeight");

    @property(ContainerBase.bleedProperty)
    private _bleed: boolean = false;

    @property(ContainerBase.minHeightProperty)
    minPixelHeight?: number;

    //#endregion

    protected adjustRenderedElementSize(renderedElement: HTMLElement) {
        super.adjustRenderedElementSize(renderedElement);

        if (this.minPixelHeight) {
            renderedElement.style.minHeight = this.minPixelHeight + "px";
        }
    }

    protected getHasExpandedAction(): boolean {
        return false;
    }

    protected getBleed(): boolean {
        return this._bleed;
    }

    protected setBleed(value: boolean) {
        this._bleed = value;
    }

    protected get renderedActionCount(): number {
        return 0;
    }

    isBleeding(): boolean {
		return (this.getHasBackground() || this.hostConfig.alwaysAllowBleed) && this.getBleed();
    }
}

export class BackgroundImage extends SerializableObject {
    //#region Schema

    static readonly urlProperty = new StringProperty(Versions.v1_0, "url");
    static readonly fillModeProperty = new EnumProperty(Versions.v1_2, "fillMode", Enums.FillMode, Enums.FillMode.Cover);
    static readonly horizontalAlignmentProperty = new EnumProperty(Versions.v1_2, "horizontalAlignment", Enums.HorizontalAlignment, Enums.HorizontalAlignment.Left);
    static readonly verticalAlignmentProperty = new EnumProperty(Versions.v1_2, "verticalAlignment", Enums.VerticalAlignment, Enums.VerticalAlignment.Top);

    @property(BackgroundImage.urlProperty)
    url?: string;

    @property(BackgroundImage.fillModeProperty)
    fillMode: Enums.FillMode;

    @property(BackgroundImage.horizontalAlignmentProperty)
    horizontalAlignment: Enums.HorizontalAlignment;

    @property(BackgroundImage.verticalAlignmentProperty)
    verticalAlignment: Enums.VerticalAlignment;

    //#endregion

    protected getSchemaKey(): string {
        return "BackgroundImage";
    }

    protected internalParse(source: any, context: BaseSerializationContext) {
        if (typeof source === "string") {
            this.resetDefaultValues();
            this.url = source;
        }
        else {
            return super.internalParse(source, context);
        }
    }

    apply(element: CardElement) {
        if (this.url && element.renderedElement) {
            element.renderedElement.style.backgroundImage = "url('" + element.preProcessPropertyValue(BackgroundImage.urlProperty, this.url) + "')";

            switch (this.fillMode) {
                case Enums.FillMode.Repeat:
                    element.renderedElement.style.backgroundRepeat = "repeat";
                    break;
                case Enums.FillMode.RepeatHorizontally:
                    element.renderedElement.style.backgroundRepeat = "repeat-x";
                    break;
                case Enums.FillMode.RepeatVertically:
                    element.renderedElement.style.backgroundRepeat = "repeat-y";
                    break;
                case Enums.FillMode.Cover:
                default:
                    element.renderedElement.style.backgroundRepeat = "no-repeat";
                    element.renderedElement.style.backgroundSize = "cover";
                    break;
            }

            switch (this.horizontalAlignment) {
                case Enums.HorizontalAlignment.Center:
                    element.renderedElement.style.backgroundPositionX = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.renderedElement.style.backgroundPositionX = "right";
                    break;
            }

            switch (this.verticalAlignment) {
                case Enums.VerticalAlignment.Center:
                    element.renderedElement.style.backgroundPositionY = "center";
                    break;
                case Enums.VerticalAlignment.Bottom:
                    element.renderedElement.style.backgroundPositionY = "bottom";
                    break;
            }
        }
    }

    isValid(): boolean {
        return this.url ? true : false;
    }
}

export class Container extends ContainerBase {
    //#region Schema

    static readonly backgroundImageProperty = new SerializableObjectProperty(
        Versions.v1_0,
        "backgroundImage",
        BackgroundImage);
    static readonly verticalContentAlignmentProperty = new EnumProperty(
        Versions.v1_1,
        "verticalContentAlignment",
        Enums.VerticalAlignment);
    static readonly rtlProperty = new BoolProperty(Versions.v1_0, "rtl");

    @property(Container.backgroundImageProperty)
    get backgroundImage(): BackgroundImage {
        return this.getValue(Container.backgroundImageProperty);
    }

    @property(Container.verticalContentAlignmentProperty)
    verticalContentAlignment?: Enums.VerticalAlignment;

    @property(Container.rtlProperty)
    rtl?: boolean;

    //#endregion

    private _items: CardElement[] = [];
    private _renderedItems: CardElement[] = [];

    private insertItemAt(
        item: CardElement,
        index: number,
        forceInsert: boolean) {
        if (!item.parent || forceInsert) {
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
                throw new Error(Strings.errors.elementTypeNotStandalone(item.getJsonTypeName()));
            }
        }
        else {
            throw new Error(Strings.errors.elementAlreadyParented());
        }
    }

    protected getItemsCollectionPropertyName(): string {
        return "items";
    }

    protected applyBackground() {
        if (this.backgroundImage.isValid() && this.renderedElement) {
            this.backgroundImage.apply(this);
        }

        super.applyBackground();
    }

    protected internalRender(): HTMLElement | undefined {
        this._renderedItems = [];

        // Cache hostConfig to avoid walking the parent hierarchy several times
        let hostConfig = this.hostConfig;

        let element = document.createElement("div");

        if (this.rtl !== undefined) {
            element.dir = this.rtl ? "rtl" : "ltr";
        }

        element.classList.add(hostConfig.makeCssClassName("ac-container"));
        element.style.display = "flex";
        element.style.flexDirection = "column";

        if (GlobalSettings.useAdvancedCardBottomTruncation) {
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

        switch (this.getEffectiveVerticalContentAlignment()) {
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

        if (this._items.length > 0) {
            for (let item of this._items) {
                let renderedItem = this.isElementAllowed(item) ? item.render() : undefined;

                if (renderedItem) {
                    if (this._renderedItems.length > 0 && item.separatorElement) {
                        item.separatorElement.style.flex = "0 0 auto";

                        Utils.appendChild(element, item.separatorElement);
                    }

                    Utils.appendChild(element, renderedItem);

                    this._renderedItems.push(item);
                }
            }
        }
        else {
            if (this.isDesignMode()) {
                let placeholderElement = this.createPlaceholderElement();
                placeholderElement.style.width = "100%";
                placeholderElement.style.height = "100%";

                element.appendChild(placeholderElement);
            }
        }

        return element;
    }

    protected truncateOverflow(maxHeight: number): boolean {
        if (this.renderedElement) {
            // Add 1 to account for rounding differences between browsers
            let boundary = this.renderedElement.offsetTop + maxHeight + 1;

            let handleElement = (cardElement: CardElement) => {
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

        return false;
    }

    protected undoOverflowTruncation() {
        for (let item of this._items) {
            item['resetOverflow']();
        }
    }

    protected getHasBackground(): boolean {
        return this.backgroundImage.isValid() || super.getHasBackground();
    }

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        this.clear();
        this.setShouldFallback(false);

        let jsonItems = source[this.getItemsCollectionPropertyName()];

        if (Array.isArray(jsonItems)) {
            for (let item of jsonItems) {
                let element = context.parseElement(this, item, !this.isDesignMode());

                if (element) {
                    this.insertItemAt(element, -1, true);
                }
            }
        }
    }

    protected internalToJSON(target: PropertyBag, context: SerializationContext) {
        super.internalToJSON(target, context);

        context.serializeArray(target, this.getItemsCollectionPropertyName(), this._items);
    }

    protected get isSelectable(): boolean {
        return true;
    }

    getEffectiveVerticalContentAlignment(): Enums.VerticalAlignment {
        if (this.verticalContentAlignment !== undefined) {
            return this.verticalContentAlignment;
        }

        let parentContainer = this.getParentContainer();

        return parentContainer ? parentContainer.getEffectiveVerticalContentAlignment() : Enums.VerticalAlignment.Top;
    }

    getItemCount(): number {
        return this._items.length;
    }

    getItemAt(index: number): CardElement {
        return this._items[index];
    }

    getFirstVisibleRenderedItem(): CardElement | undefined {
        if (this.renderedElement && this._renderedItems && this._renderedItems.length > 0) {
            for (let item of this._renderedItems) {
                if (item.isVisible) {
                    return item;
                }
            };
        }

        return undefined;
    }

    getLastVisibleRenderedItem(): CardElement | undefined {
        if (this.renderedElement && this._renderedItems && this._renderedItems.length > 0) {
            for (let i = this._renderedItems.length - 1; i >= 0; i--) {
                if (this._renderedItems[i].isVisible) {
                    return this._renderedItems[i];
                }
            }
        }

        return undefined;
    }

    getJsonTypeName(): string {
        return "Container";
    }

    isFirstElement(element: CardElement): boolean {
        let designMode = this.isDesignMode();

        for (let item of this._items) {
            if (item.isVisible || designMode) {
                return item == element;
            }
        }

        return false;
    }

    isLastElement(element: CardElement): boolean {
        let designMode = this.isDesignMode();

        for (let i = this._items.length - 1; i >= 0; i--) {
            if (this._items[i].isVisible || designMode) {
                return this._items[i] == element;
            }
        }

        return false;
    }

    isRtl(): boolean {
        if (this.rtl !== undefined) {
            return this.rtl;
        }
        else {
            let parentContainer = this.getParentContainer();

            return parentContainer ? parentContainer.isRtl() : false;
        }
    }

    isBleedingAtTop(): boolean {
        let firstRenderedItem = this.getFirstVisibleRenderedItem();

        return this.isBleeding() || (firstRenderedItem ? firstRenderedItem.isBleedingAtTop() : false);
    }

    isBleedingAtBottom(): boolean {
        let lastRenderedItem = this.getLastVisibleRenderedItem();

        return this.isBleeding() || (lastRenderedItem ? lastRenderedItem.isBleedingAtBottom() && lastRenderedItem.getEffectiveStyle() == this.getEffectiveStyle() : false);
    }

    indexOf(cardElement: CardElement): number {
        return this._items.indexOf(cardElement);
    }

    addItem(item: CardElement) {
        this.insertItemAt(item, -1, false);
    }

    insertItemBefore(item: CardElement, insertBefore: CardElement) {
        this.insertItemAt(item, this._items.indexOf(insertBefore), false);
    }

    insertItemAfter(item: CardElement, insertAfter: CardElement) {
        this.insertItemAt(item, this._items.indexOf(insertAfter) + 1, false);
    }

    removeItem(item: CardElement): boolean {
        let itemIndex = this._items.indexOf(item);

        if (itemIndex >= 0) {
            this._items.splice(itemIndex, 1);

            item.setParent(undefined);

            this.updateLayout();

            return true;
        }

        return false;
    }

    clear() {
        this._items = [];
        this._renderedItems = [];
    }

    getResourceInformation(): IResourceInformation[] {
        let result = super.getResourceInformation();

        if (this.backgroundImage.isValid()) {
            result.push(
                {
                    url: <string>this.backgroundImage.url,
                    mimeType: "image"
                }
            );
        }

        return result;
    }

    getActionById(id: string): Action | undefined {
        let result: Action | undefined = super.getActionById(id);

        if (!result) {
            if (this.selectAction) {
                result = this.selectAction.getActionById(id);
            }

            if (!result) {
                for (let item of this._items) {
                    result = item.getActionById(id);

                    if (result) {
                        break;
                    }
                }
            }
        }

        return result;
    }

    get padding(): PaddingDefinition | undefined {
        return this.getPadding();
    }

    set padding(value: PaddingDefinition | undefined) {
        this.setPadding(value);
    }

    get selectAction(): Action | undefined {
        return this._selectAction;
    }

    set selectAction(value: Action | undefined) {
        this._selectAction = value;
    }

    get bleed(): boolean {
        return this.getBleed();
    }

    set bleed(value: boolean) {
        this.setBleed(value);
    }
}

export type ColumnWidth = SizeAndUnit | "auto" | "stretch";

export class Column extends Container {
    //#region Schema

    static readonly widthProperty = new CustomProperty<ColumnWidth>(
        Versions.v1_0,
        "width",
        (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
            let result: ColumnWidth = property.defaultValue;
            let value = source[property.name];
            let invalidWidth = false;

            if (typeof value === "number" && !isNaN(value)) {
                result = new SizeAndUnit(value, Enums.SizeUnit.Weight);
            }
            else if (value === "auto" || value === "stretch") {
                result = value;
            }
            else if (typeof value === "string") {
                try {
                    result = SizeAndUnit.parse(value);

                    if (result.unit === Enums.SizeUnit.Pixel && property.targetVersion.compareTo(context.targetVersion) > 0) {
                        invalidWidth = true;
                    }
                }
                catch (e) {
                    invalidWidth = true;
                }
            }
            else {
                invalidWidth = true;
            }

            if (invalidWidth) {
                context.logParseEvent(
                    sender,
                    Enums.ValidationEvent.InvalidPropertyValue,
                    Strings.errors.invalidColumnWidth(value));

                result = "auto";
            }

            return result;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: ColumnWidth, context: BaseSerializationContext) => {
            if (value instanceof SizeAndUnit) {
                if (value.unit === Enums.SizeUnit.Pixel) {
                    context.serializeValue(target, "width", value.physicalSize + "px");
                }
                else {
                    context.serializeNumber(target, "width", value.physicalSize);
                }
            }
            else {
                context.serializeValue(target, "width", value);
            }
        },
        "stretch");

    @property(Column.widthProperty)
    width: ColumnWidth = "stretch";

    //#endregion

    private _computedWeight: number = 0;

    protected adjustRenderedElementSize(renderedElement: HTMLElement) {
        const minDesignTimeColumnHeight = 20;

        if (this.isDesignMode()) {
            renderedElement.style.minWidth = "20px";
            renderedElement.style.minHeight = (!this.minPixelHeight ? minDesignTimeColumnHeight : Math.max(this.minPixelHeight, minDesignTimeColumnHeight)) + "px";
        }
        else {
            renderedElement.style.minWidth = "0";

            if (this.minPixelHeight) {
                renderedElement.style.minHeight = this.minPixelHeight + "px";
            }
        }

        if (this.width === "auto") {
            renderedElement.style.flex = "0 1 auto";
        }
        else if (this.width === "stretch") {
            renderedElement.style.flex = "1 1 50px";
        }
        else if (this.width instanceof SizeAndUnit) {
            if (this.width.unit == Enums.SizeUnit.Pixel) {
                renderedElement.style.flex = "0 0 auto";
                renderedElement.style.width = this.width.physicalSize + "px";
            }
            else {
                renderedElement.style.flex = "1 1 " + (this._computedWeight > 0 ? this._computedWeight : this.width.physicalSize) + "%";
            }
        }
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return true;
    }

    protected get separatorOrientation(): Enums.Orientation {
        return Enums.Orientation.Vertical;
    }

    constructor(width: ColumnWidth = "stretch") {
        super();

        this.width = width;
    }

    getJsonTypeName(): string {
        return "Column";
    }

    get hasVisibleSeparator(): boolean {
        if (this.parent && this.parent instanceof ColumnSet) {
            return this.separatorElement !== undefined && !this.parent.isLeftMostElement(this);
        }
        else {
            return false;
        }
    }

    get isStandalone(): boolean {
        return false;
    }
}

export class ColumnSet extends ContainerBase {
    private _columns: Column[] = [];
    private _renderedColumns: Column[];

    private createColumnInstance(source: any, context: SerializationContext): Column | undefined {
        return context.parseCardObject<Column>(
            this,
            source,
            [], // Forbidden types not supported for elements for now
            !this.isDesignMode(),
            (typeName: string) => {
                return !typeName || typeName === "Column" ? new Column() : undefined;
            },
            (typeName: string, errorType: Enums.TypeErrorType) => {
                context.logParseEvent(
                    undefined,
                    Enums.ValidationEvent.ElementTypeNotAllowed,
                    Strings.errors.elementTypeNotAllowed(typeName));
            });
    }

    protected internalRender(): HTMLElement | undefined {
        this._renderedColumns = [];

        if (this._columns.length > 0) {
            // Cache hostConfig to avoid walking the parent hierarchy several times
            let hostConfig = this.hostConfig;

            let element = document.createElement("div");
            element.className = hostConfig.makeCssClassName("ac-columnSet");
            element.style.display = "flex";

            if (GlobalSettings.useAdvancedCardBottomTruncation) {
                // See comment in Container.internalRender()
                element.style.minHeight = '-webkit-min-content';
            }

            switch (this.getEffectiveHorizontalAlignment()) {
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

            let totalWeight: number = 0;

            for (let column of this._columns) {
                if (column.width instanceof SizeAndUnit && (column.width.unit == Enums.SizeUnit.Weight)) {
                    totalWeight += column.width.physicalSize;
                }
            }

            for (let column of this._columns) {
                if (column.width instanceof SizeAndUnit && column.width.unit == Enums.SizeUnit.Weight && totalWeight > 0) {
                    let computedWeight = 100 / totalWeight * column.width.physicalSize;

                    // Best way to emulate "internal" access I know of
                    column["_computedWeight"] = computedWeight;
                }

                let renderedColumn = column.render();

                if (renderedColumn) {
                    if (this._renderedColumns.length > 0 && column.separatorElement) {
                        column.separatorElement.style.flex = "0 0 auto";

                        Utils.appendChild(element, column.separatorElement);
                    }

                    Utils.appendChild(element, renderedColumn);

                    this._renderedColumns.push(column);
                }
            }

            return this._renderedColumns.length > 0 ? element : undefined;
        }
        else {
            return undefined;
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

    protected get isSelectable(): boolean {
        return true;
    }

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        this._columns = [];
        this._renderedColumns = [];

        let jsonColumns = source["columns"];

        if (Array.isArray(jsonColumns)) {
            for (let item of jsonColumns) {
                let column = this.createColumnInstance(item, context);

                if (column) {
                    this._columns.push(column);
                }
            }
        }
    }

    protected internalToJSON(target: PropertyBag, context: SerializationContext) {
        super.internalToJSON(target, context);

        context.serializeArray(target, "columns", this._columns);
    }

    isFirstElement(element: CardElement): boolean {
        for (let column of this._columns) {
            if (column.isVisible) {
                return column == element;
            }
        }

        return false;
    }

    isBleedingAtTop(): boolean {
        if (this.isBleeding()) {
            return true;
        }

        if (this._renderedColumns && this._renderedColumns.length > 0) {
            for (let column of this._columns) {
                if (column.isBleedingAtTop()) {
                    return true;
                }
            }
        }

        return false;
    }

    isBleedingAtBottom(): boolean {
        if (this.isBleeding()) {
            return true;
        }

        if (this._renderedColumns && this._renderedColumns.length > 0) {
            for (let column of this._columns) {
                if (column.isBleedingAtBottom()) {
                    return true;
                }
            }
        }

        return false;
    }

    getItemCount(): number {
        return this._columns.length;
    }

    getFirstVisibleRenderedItem(): CardElement | undefined {
        if (this.renderedElement && this._renderedColumns && this._renderedColumns.length > 0) {
            return this._renderedColumns[0];
        }
        else {
            return undefined;
        }
    }

    getLastVisibleRenderedItem(): CardElement | undefined {
        if (this.renderedElement && this._renderedColumns && this._renderedColumns.length > 0) {
            return this._renderedColumns[this._renderedColumns.length - 1];
        }
        else {
            return undefined;
        }
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

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        let weightedColumns: number = 0;
        let stretchedColumns: number = 0;

        for (let column of this._columns) {
            if (typeof column.width === "number") {
                weightedColumns++;
            }
            else if (column.width === "stretch") {
                stretchedColumns++;
            }
        }

        if (weightedColumns > 0 && stretchedColumns > 0) {
            context.addFailure(
                this,
                Enums.ValidationEvent.Hint,
                Strings.hints.dontUseWeightedAndStrecthedColumnsInSameSet());
        }
    }

    addColumn(column: Column) {
        if (!column.parent) {
            this._columns.push(column);

            column.setParent(this);
        }
        else {
            throw new Error(Strings.errors.columnAlreadyBelongsToAnotherSet());
        }
    }

    removeItem(item: CardElement): boolean {
        if (item instanceof Column) {
            let itemIndex = this._columns.indexOf(item);

            if (itemIndex >= 0) {
                this._columns.splice(itemIndex, 1);

                item.setParent(undefined);

                this.updateLayout();

                return true;
            }
        }

        return false;
    }

    indexOf(cardElement: CardElement): number {
        return cardElement instanceof Column ? this._columns.indexOf(cardElement) : -1;
    }

    isLeftMostElement(element: CardElement): boolean {
        return this._columns.indexOf(<Column>element) == 0;
    }

    isRightMostElement(element: CardElement): boolean {
        return this._columns.indexOf(<Column>element) == this._columns.length - 1;
    }

    isTopElement(element: CardElement): boolean {
        return this._columns.indexOf(<Column>element) >= 0;
    }

    isBottomElement(element: CardElement): boolean {
        return this._columns.indexOf(<Column>element) >= 0;
    }

    getActionById(id: string): Action | undefined {
        let result: Action | undefined = undefined;

        for (let column of this._columns) {
            result = column.getActionById(id);

            if (result) {
                break;
            }
        }

        return result;
    }

    get bleed(): boolean {
        return this.getBleed();
    }

    set bleed(value: boolean) {
        this.setBleed(value);
    }

    get padding(): PaddingDefinition | undefined {
        return this.getPadding();
    }

    set padding(value: PaddingDefinition | undefined) {
        this.setPadding(value);
    }

    get selectAction(): Action | undefined {
        return this._selectAction;
    }

    set selectAction(value: Action | undefined) {
        this._selectAction = value;
    }
}

function raiseImageLoadedEvent(image: Image) {
    let card = image.getRootElement() as AdaptiveCard;
    let onImageLoadedHandler = (card && card.onImageLoaded) ? card.onImageLoaded : AdaptiveCard.onImageLoaded;

    if (onImageLoadedHandler) {
        onImageLoadedHandler(image);
    }
}

function raiseAnchorClickedEvent(element: CardElement, anchor: HTMLAnchorElement, ev?: MouseEvent): boolean {
    let card = element.getRootElement() as AdaptiveCard;
    let onAnchorClickedHandler = (card && card.onAnchorClicked) ? card.onAnchorClicked : AdaptiveCard.onAnchorClicked;

    return onAnchorClickedHandler !== undefined ? onAnchorClickedHandler(element, anchor, ev) : false;
}

function raiseExecuteActionEvent(action: Action) {
    let card = action.parent ? action.parent.getRootElement() as AdaptiveCard : undefined;
    let onExecuteActionHandler = (card && card.onExecuteAction) ? card.onExecuteAction : AdaptiveCard.onExecuteAction;

    if (action.prepareForExecution() && onExecuteActionHandler) {
        onExecuteActionHandler(action);
    }
}

function raiseInlineCardExpandedEvent(action: ShowCardAction, isExpanded: boolean) {
    let card = action.parent ? action.parent.getRootElement() as AdaptiveCard : undefined;
    let onInlineCardExpandedHandler = (card && card.onInlineCardExpanded) ? card.onInlineCardExpanded : AdaptiveCard.onInlineCardExpanded;

    if (onInlineCardExpandedHandler) {
        onInlineCardExpandedHandler(action, isExpanded);
    }
}

function raiseInputValueChangedEvent(input: Input) {
    let card = input.getRootElement() as AdaptiveCard;
    let onInputValueChangedHandler = (card && card.onInputValueChanged) ? card.onInputValueChanged : AdaptiveCard.onInputValueChanged;

    if (onInputValueChangedHandler) {
        onInputValueChangedHandler(input);
    }
}

function raiseElementVisibilityChangedEvent(element: CardElement, shouldUpdateLayout: boolean = true) {
    let rootElement = element.getRootElement();

    if (shouldUpdateLayout) {
        rootElement.updateLayout();
    }

    let card = rootElement as AdaptiveCard;
    let onElementVisibilityChangedHandler = (card && card.onElementVisibilityChanged) ? card.onElementVisibilityChanged : AdaptiveCard.onElementVisibilityChanged;

    if (onElementVisibilityChangedHandler !== undefined) {
        onElementVisibilityChangedHandler(element);
    }
}

/**
 * @returns return false to continue with default context menu; return true to skip SDK default context menu
 */
function raiseDisplayOverflowActionMenuEvent(action: OverflowAction, target?: HTMLElement): boolean {
    let card = action.parent ? action.parent.getRootElement() as AdaptiveCard : undefined;
    let onDisplayOverflowActionMenuHandler = (card && card.onDisplayOverflowActionMenu) ? card.onDisplayOverflowActionMenu : AdaptiveCard.onDisplayOverflowActionMenu;

    return onDisplayOverflowActionMenuHandler !== undefined ? onDisplayOverflowActionMenuHandler(action.getActions(), target) : false;
}

/**
 * @returns return false to continue with default action button; return true to skip SDK default action button
 */
function raiseRenderOverflowActionsEvent(action: OverflowAction, isAtRootLevelActions: boolean): boolean {
    let card = action.parent ? action.parent.getRootElement() as AdaptiveCard : undefined;
    let onRenderOverflowActionsHandler = (card && card.onRenderOverflowActions) ? card.onRenderOverflowActions : AdaptiveCard.onRenderOverflowActions;

    return onRenderOverflowActionsHandler !== undefined ? onRenderOverflowActionsHandler(action.getActions(), isAtRootLevelActions) : false;
}

export abstract class ContainerWithActions extends Container {
    private _actionCollection: ActionCollection;

    protected internalParse(source: any, context: SerializationContext) {
        super.internalParse(source, context);

        this._actionCollection.parse(source["actions"], context);
    }

    protected internalToJSON(target: PropertyBag, context: SerializationContext) {
        super.internalToJSON(target, context);

        this._actionCollection.toJSON(target, "actions", context);
    }

    protected internalRender(): HTMLElement | undefined {
        let element = super.internalRender();

        if (element) {
            let renderedActions = this._actionCollection.render(this.hostConfig.actions.actionsOrientation, false);

            if (renderedActions) {
                Utils.appendChild(
                    element,
                    renderSeparation(
                        this.hostConfig,
                        {
                            spacing: this.hostConfig.getEffectiveSpacing(this.hostConfig.actions.spacing)
                        },
                        Enums.Orientation.Horizontal));
                Utils.appendChild(element, renderedActions);
            }

            if (this.renderIfEmpty) {
                return element;
            }
            else {
                return element.children.length > 0 ? element : undefined;
            }
        }
        else {
            return undefined;
        }
    }

    protected getHasExpandedAction(): boolean {
        if (this.renderedActionCount == 0) {
            return false;
        }
        else if (this.renderedActionCount == 1) {
            return this._actionCollection.expandedAction !== undefined && !this.hostConfig.actions.preExpandSingleShowCardAction;
        }
        else {
            return this._actionCollection.expandedAction !== undefined;
        }
    }

    protected get renderedActionCount(): number {
        return this._actionCollection.renderedActionCount;
    }

    protected get renderIfEmpty(): boolean {
        return false;
    }

    constructor() {
        super();

        this._actionCollection = new ActionCollection(this);
    }

    getActionCount(): number {
        return this._actionCollection.getActionCount();
    }

    getActionAt(index: number): Action | undefined {
        if (index >= 0 && index < this.getActionCount()) {
            return this._actionCollection.getActionAt(index);
        }
        else {
            return super.getActionAt(index);
        }
    }

    getActionById(id: string): Action | undefined {
        let result: Action | undefined = this._actionCollection.getActionById(id);

        return result ? result : super.getActionById(id);
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (this._actionCollection) {
            this._actionCollection.validateProperties(context);
        }
    }

    isLastElement(element: CardElement): boolean {
        return super.isLastElement(element) && this._actionCollection.getActionCount() == 0;
    }

    addAction(action: Action) {
        this._actionCollection.addAction(action);
    }

    clear() {
        super.clear();

        this._actionCollection.clear();
    }

    getAllInputs(processActions: boolean = true): Input[] {
        let result = super.getAllInputs(processActions);

        if (processActions) {
            result = result.concat(this._actionCollection.getAllInputs(processActions));
        }

        return result;
    }

    getResourceInformation(): IResourceInformation[] {
        return super.getResourceInformation().concat(this._actionCollection.getResourceInformation());
    }

    isBleedingAtBottom(): boolean {
        if (this._actionCollection.renderedActionCount == 0) {
            return super.isBleedingAtBottom();
        }
        else {
            if (this._actionCollection.getActionCount() == 1) {
                return this._actionCollection.expandedAction !== undefined && !this.hostConfig.actions.preExpandSingleShowCardAction;
            }
            else {
                return this._actionCollection.expandedAction !== undefined;
            }
        }
    }

    get isStandalone(): boolean {
        return false;
    }
}

export interface IMarkdownProcessingResult {
    didProcess: boolean;
    outputHtml?: any;
}

export class RefreshActionProperty extends PropertyDefinition {
    parse(sender: RefreshDefinition, source: PropertyBag, context: SerializationContext): ExecuteAction | undefined {
        let action = context.parseAction(
            sender.parent,
            source[this.name],
            [],
            false);

        if (action !== undefined) {
            if (action instanceof ExecuteAction) {
                return action;
            }

            context.logParseEvent(
                sender,
                Enums.ValidationEvent.ActionTypeNotAllowed,
                Strings.errors.actionTypeNotAllowed(action.getJsonTypeName()));
        }

        context.logParseEvent(
            sender,
            Enums.ValidationEvent.PropertyCantBeNull,
            Strings.errors.propertyMustBeSet("action"));

        return undefined;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: ExecuteAction | undefined, context: SerializationContext) {
        context.serializeValue(target, this.name, value ? value.toJSON(context) : undefined, undefined, true);
    }

    constructor(readonly targetVersion: Version, readonly name: string) {
        super(targetVersion, name, undefined);
    }
}

export class RefreshDefinition extends SerializableObject {
    //#region Schema

    static readonly actionProperty = new RefreshActionProperty(Versions.v1_4, "action");
    static readonly userIdsProperty = new StringArrayProperty(Versions.v1_4, "userIds");

    @property(RefreshDefinition.actionProperty)
    get action(): ExecuteAction {
        return this.getValue(RefreshDefinition.actionProperty);
    }

    set action(value: ExecuteAction) {
        this.setValue(RefreshDefinition.actionProperty, value);

        if (value) {
            value.setParent(this.parent);
        }
    }

    @property(RefreshDefinition.userIdsProperty)
    userIds?: string[];

    protected getSchemaKey(): string {
        return "RefreshDefinition";
    }

    //#endregion

    parent: CardElement;
}

export class AuthCardButton extends SerializableObject {
    //#region Schema

    static readonly typeProperty = new StringProperty(Versions.v1_4, "type");
    static readonly titleProperty = new StringProperty(Versions.v1_4, "title");
    static readonly imageProperty = new StringProperty(Versions.v1_4, "image");
    static readonly valueProperty = new StringProperty(Versions.v1_4, "value");

    protected getSchemaKey(): string {
        return "AuthCardButton";
    }

    //#endregion

    @property(AuthCardButton.typeProperty)
    type: string;

    @property(AuthCardButton.titleProperty)
    title?: string;

    @property(AuthCardButton.imageProperty)
    image?: string;

    @property(AuthCardButton.valueProperty)
    value: string;
}

export class TokenExchangeResource extends SerializableObject {
    //#region Schema

    static readonly idProperty = new StringProperty(Versions.v1_4, "id");
    static readonly uriProperty = new StringProperty(Versions.v1_4, "uri");
    static readonly providerIdProperty = new StringProperty(Versions.v1_4, "providerId");

    protected getSchemaKey(): string {
        return "TokenExchangeResource";
    }

    //#endregion

    @property(TokenExchangeResource.idProperty)
    id?: string;

    @property(TokenExchangeResource.uriProperty)
    uri?: string;

    @property(TokenExchangeResource.providerIdProperty)
    providerId?: string;
}

export class Authentication extends SerializableObject {
    //#region Schema

    static readonly textProperty = new StringProperty(Versions.v1_4, "text");
    static readonly connectionNameProperty = new StringProperty(Versions.v1_4, "connectionName");
    static readonly buttonsProperty = new SerializableObjectCollectionProperty(Versions.v1_4, "buttons", AuthCardButton);
    static readonly tokenExchangeResourceProperty = new SerializableObjectProperty(Versions.v1_4, "tokenExchangeResource", TokenExchangeResource, true);

    protected getSchemaKey(): string {
        return "Authentication";
    }

    //#endregion

    @property(Authentication.textProperty)
    text?: string;

    @property(Authentication.connectionNameProperty)
    connectionName?: string;

    @property(Authentication.buttonsProperty)
    buttons: AuthCardButton[];

    @property(Authentication.tokenExchangeResourceProperty)
    tokenExchangeResource?: TokenExchangeResource;
}

// @dynamic
export class AdaptiveCard extends ContainerWithActions {
    static readonly schemaUrl = "http://adaptivecards.io/schemas/adaptive-card.json";

    //#region Schema

    protected static readonly $schemaProperty = new CustomProperty<string>(
        Versions.v1_0,
        "$schema",
        (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
            return AdaptiveCard.schemaUrl;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: Versions | undefined, context: BaseSerializationContext) => {
            context.serializeValue(target, property.name, AdaptiveCard.schemaUrl);
        });

    static readonly versionProperty = new CustomProperty<Version | undefined>(
        Versions.v1_0,
        "version",
        (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
            let version = Version.parse(source[property.name], context);

            if (version === undefined) {
                version = Versions.latest;

                context.logParseEvent(
                    sender,
                    Enums.ValidationEvent.InvalidPropertyValue,
                    Strings.errors.invalidCardVersion(version.toString()));
            }

            return version;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: Versions | undefined, context: BaseSerializationContext) => {
            if (value !== undefined) {
                context.serializeValue(target, property.name, value.toString());
            }
        },
        Versions.v1_0);
    static readonly fallbackTextProperty = new StringProperty(Versions.v1_0, "fallbackText");
    static readonly speakProperty = new StringProperty(Versions.v1_0, "speak");
    static readonly refreshProperty = new SerializableObjectProperty(Versions.v1_4, "refresh", RefreshDefinition, true);
    static readonly authenticationProperty = new SerializableObjectProperty(Versions.v1_4, "authentication", Authentication, true);

    @property(AdaptiveCard.versionProperty)
    version: Version;

    @property(AdaptiveCard.fallbackTextProperty)
    fallbackText?: string;

    @property(AdaptiveCard.speakProperty)
    speak?: string;

    @property(AdaptiveCard.refreshProperty)
    get refresh(): RefreshDefinition | undefined {
        return this.getValue(AdaptiveCard.refreshProperty);
    }

    set refresh(value: RefreshDefinition | undefined) {
        this.setValue(AdaptiveCard.refreshProperty, value);

        if (value) {
            value.parent = this;
        }
    }

    @property(AdaptiveCard.authenticationProperty)
    authentication?: Authentication;

    //#endregion

    static onAnchorClicked?: (element: CardElement, anchor: HTMLAnchorElement, ev?: MouseEvent) => boolean;
    static onExecuteAction?: (action: Action) => void;
    static onElementVisibilityChanged?: (element: CardElement) => void;
    static onImageLoaded?: (image: Image) => void;
    static onInlineCardExpanded?: (action: ShowCardAction, isExpanded: boolean) => void;
    static onInputValueChanged?: (input: Input) => void;
    static onProcessMarkdown?: (text: string, result: IMarkdownProcessingResult) => void;
    static onDisplayOverflowActionMenu?: (actions: readonly Action[], target?: HTMLElement) => boolean;
    static onRenderOverflowActions?: (actions: readonly Action[], isRootLevelActions: boolean) => boolean;

    static get processMarkdown(): (text: string) => string {
        throw new Error(Strings.errors.processMarkdownEventRemoved());
    }

    static set processMarkdown(value: (text: string) => string) {
        throw new Error(Strings.errors.processMarkdownEventRemoved());
    }

    static applyMarkdown(text: string): IMarkdownProcessingResult {
        let result: IMarkdownProcessingResult = {
            didProcess: false
        };

        if (AdaptiveCard.onProcessMarkdown) {
            AdaptiveCard.onProcessMarkdown(text, result);
        }
        else if ((<any>window).markdownit) {
            // Check for markdownit
            let markdownIt: any = (<any>window).markdownit;
            result.outputHtml = markdownIt().render(text);
            result.didProcess = true;
        }
        else {
            console.warn(Strings.errors.markdownProcessingNotEnabled)
        }

        return result;
    }

    private _fallbackCard?: AdaptiveCard;

    private isVersionSupported(): boolean {
        if (this.bypassVersionCheck) {
            return true;
        }
        else {
            let unsupportedVersion: boolean =
                !this.version ||
                !this.version.isValid ||
                (this.maxVersion.major < this.version.major) ||
                (this.maxVersion.major == this.version.major && this.maxVersion.minor < this.version.minor);

            return !unsupportedVersion;
        }
    }

    protected getDefaultSerializationContext(): BaseSerializationContext {
        return new SerializationContext(this.version);
    }

    protected getItemsCollectionPropertyName(): string {
        return "body";
    }

    protected internalParse(source: any, context: SerializationContext) {
        this._fallbackCard = undefined;

        let fallbackElement = context.parseElement(undefined, source["fallback"], !this.isDesignMode());

        if (fallbackElement) {
            this._fallbackCard = new AdaptiveCard();
            this._fallbackCard.addItem(fallbackElement);
        }

        super.internalParse(source, context);
    }

    protected internalToJSON(target: PropertyBag, context: SerializationContext) {
        this.setValue(AdaptiveCard.versionProperty, context.targetVersion);

        super.internalToJSON(target, context);
    }

    protected internalRender(): HTMLElement | undefined {
        let renderedElement = super.internalRender();

        if (GlobalSettings.useAdvancedCardBottomTruncation && renderedElement) {
            // Unlike containers, the root card element should be allowed to
            // be shorter than its content (otherwise the overflow truncation
            // logic would never get triggered)
            renderedElement.style.removeProperty("minHeight");
        }

        return renderedElement;
    }

    protected getHasBackground(): boolean {
        return true;
    }

    protected getDefaultPadding(): PaddingDefinition {
        return new PaddingDefinition(
            Enums.Spacing.Padding,
            Enums.Spacing.Padding,
            Enums.Spacing.Padding,
            Enums.Spacing.Padding);
    }

    protected shouldSerialize(context: SerializationContext): boolean {
        return true;
    }

    protected get renderIfEmpty(): boolean {
        return true;
    }

    protected get bypassVersionCheck(): boolean {
        return false;
    }

    protected get allowCustomStyle() {
        return this.hostConfig.adaptiveCard && this.hostConfig.adaptiveCard.allowCustomStyle;
    }

    protected get hasBackground(): boolean {
        return true;
    }

    onAnchorClicked?: (element: CardElement, anchor: HTMLAnchorElement, ev?: MouseEvent) => boolean;
    onExecuteAction?: (action: Action) => void;
    onElementVisibilityChanged?: (element: CardElement) => void;
    onImageLoaded?: (image: Image) => void;
    onInlineCardExpanded?: (action: ShowCardAction, isExpanded: boolean) => void;
    onInputValueChanged?: (input: Input) => void;
    onDisplayOverflowActionMenu?: (actions: readonly Action[], target?: HTMLElement) => boolean;
    onRenderOverflowActions?: (actions: readonly Action[], isRootLevelActions: boolean) => boolean;

    designMode: boolean = false;

    getJsonTypeName(): string {
        return "AdaptiveCard";
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (this.getValue(CardElement.typeNameProperty) !== "AdaptiveCard") {
            context.addFailure(
                this,
                Enums.ValidationEvent.MissingCardType,
                Strings.errors.invalidCardType());
        }

        if (!this.bypassVersionCheck && !this.version) {
            context.addFailure(
                this,
                Enums.ValidationEvent.PropertyCantBeNull,
                Strings.errors.propertyMustBeSet("version"));
        }
        else if (!this.isVersionSupported()) {
            context.addFailure(
                this,
                Enums.ValidationEvent.UnsupportedCardVersion,
                Strings.errors.unsupportedCardVersion(this.version.toString(), this.maxVersion.toString()));
        }
    }

    render(target?: HTMLElement): HTMLElement | undefined {
        let renderedCard: HTMLElement | undefined;

        if (this.shouldFallback() && this._fallbackCard) {
            this._fallbackCard.hostConfig = this.hostConfig;

            renderedCard = this._fallbackCard.render();
        }
        else {
            renderedCard = super.render();

            if (renderedCard) {
                renderedCard.classList.add(this.hostConfig.makeCssClassName("ac-adaptiveCard"));

                // Having a tabIndex on the root container for a card can mess up accessibility in some scenarios.
                // However, we've shipped this behavior before, and so can't just turn it off in a point release. For
                // now, to unblock accessibility scenarios for our customers, we've got an option to turn it off. In a
                // future release, we should strongly consider flipping the default such that we *don't* emit a tabIndex
                // by default.
                if (GlobalSettings.setTabIndexAtCardRoot) {
                    renderedCard.tabIndex = 0;
                }

                if (this.speak) {
                    renderedCard.setAttribute("aria-label", this.speak);
                }
            }
        }

        if (target) {
            Utils.appendChild(target, renderedCard);

            this.updateLayout();
        }

        return renderedCard;
    }

    updateLayout(processChildren: boolean = true) {
        super.updateLayout(processChildren);

        if (GlobalSettings.useAdvancedCardBottomTruncation && this.isDisplayed()) {
            let padding = this.hostConfig.getEffectiveSpacing(Enums.Spacing.Default);

            this['handleOverflow']((<HTMLElement>this.renderedElement).offsetHeight - padding);
        }
    }

    shouldFallback(): boolean {
        return super.shouldFallback() || !this.isVersionSupported();
    }

    get hasVisibleSeparator(): boolean {
        return false;
    }
}

class InlineAdaptiveCard extends AdaptiveCard {
    //#region Schema

    protected getSchemaKey(): string {
        return "InlineAdaptiveCard";
    }

    protected populateSchema(schema: SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.remove(
            AdaptiveCard.$schemaProperty,
            AdaptiveCard.versionProperty);
    }

    //#endregion

    protected getDefaultPadding(): PaddingDefinition {
        return new PaddingDefinition(
            this.suppressStyle ? Enums.Spacing.None : Enums.Spacing.Padding,
            Enums.Spacing.Padding,
            this.suppressStyle ? Enums.Spacing.None : Enums.Spacing.Padding,
            Enums.Spacing.Padding);
    }

    protected get bypassVersionCheck(): boolean {
        return true;
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

    render(target?: HTMLElement): HTMLElement | undefined {
        let renderedCard = super.render(target);

        if (renderedCard) {
            renderedCard.setAttribute("aria-live", "polite");
            renderedCard.removeAttribute("tabindex");
        }

        return renderedCard;
    }
}

export class SerializationContext extends BaseSerializationContext {
    private _elementRegistry?: CardObjectRegistry<CardElement>;
    private _actionRegistry?: CardObjectRegistry<Action>;

    private internalParseCardObject<T extends CardObject>(
        parent: CardElement | undefined,
        source: any,
        forbiddenTypeNames: string[],
        allowFallback: boolean,
        createInstanceCallback: (typeName: string | undefined) => T | undefined,
        logParseEvent: (typeName: string | undefined, errorType: Enums.TypeErrorType) => void): T | undefined {
        let result: T | undefined = undefined;

        if (source && typeof source === "object") {
            let typeName = Utils.parseString(source["type"]);

            if (typeName && forbiddenTypeNames.indexOf(typeName) >= 0) {
                logParseEvent(typeName, Enums.TypeErrorType.ForbiddenType);
            }
            else {
                let tryToFallback = false;

                result = createInstanceCallback(typeName);

                if (!result) {
                    tryToFallback = GlobalSettings.enableFallback && allowFallback;

                    logParseEvent(typeName, Enums.TypeErrorType.UnknownType);
                }
                else {
                    result.setParent(parent);
                    result.parse(source, this);

                    tryToFallback = GlobalSettings.enableFallback && allowFallback && result.shouldFallback();
                }

                if (tryToFallback) {
                    let fallback = source["fallback"];

                    if (!fallback && parent) {
                        parent.setShouldFallback(true);
                    }
                    if (typeof fallback === "string" && fallback.toLowerCase() === "drop") {
                        result = undefined;
                    }
                    else if (typeof fallback === "object") {
                        result = this.internalParseCardObject<T>(
                            parent,
                            fallback,
                            forbiddenTypeNames,
                            true,
                            createInstanceCallback,
                            logParseEvent);
                    }
                }
            }
        }

        return result;
    }

    protected cardObjectParsed(o: SerializableObject, source: any) {
        if (o instanceof Action && this.onParseAction) {
            this.onParseAction(o, source, this);
        }
        else if (o instanceof CardElement && this.onParseElement) {
            this.onParseElement(o, source, this);
        }
    }

    onParseAction?: (action: Action, source: any, context: SerializationContext) => void;
    onParseElement?: (element: CardElement, source: any, context: SerializationContext) => void;

    shouldSerialize(o: SerializableObject): boolean {
        if (o instanceof Action) {
            return this.actionRegistry.findByName(o.getJsonTypeName()) !== undefined;
        }
        else if (o instanceof CardElement) {
            return this.elementRegistry.findByName(o.getJsonTypeName()) !== undefined;
        }
        else {
            return true;
        }
    }

    parseCardObject<T extends CardObject>(
        parent: CardElement | undefined,
        source: any,
        forbiddenTypeNames: string[],
        allowFallback: boolean,
        createInstanceCallback: (typeName: string) => T | undefined,
        logParseEvent: (typeName: string, errorType: Enums.TypeErrorType) => void): T | undefined {
        let result = this.internalParseCardObject(
            parent,
            source,
            forbiddenTypeNames,
            allowFallback,
            createInstanceCallback,
            logParseEvent);

        if (result !== undefined) {
            this.cardObjectParsed(result, source);
        }

        return result;
    }

    parseElement(parent: CardElement | undefined, source: any, allowFallback: boolean): CardElement | undefined {
        return this.parseCardObject<CardElement>(
            parent,
            source,
            [], // Forbidden types not supported for elements for now
            allowFallback,
            (typeName: string) => {
                return this.elementRegistry.createInstance(typeName, this.targetVersion);
            },
            (typeName: string, errorType: Enums.TypeErrorType) => {
                if (errorType === Enums.TypeErrorType.UnknownType) {
                    this.logParseEvent(
                        undefined,
                        Enums.ValidationEvent.UnknownElementType,
                        Strings.errors.unknownElementType(typeName));
                }
                else {
                    this.logParseEvent(
                        undefined,
                        Enums.ValidationEvent.ElementTypeNotAllowed,
                        Strings.errors.elementTypeNotAllowed(typeName));
                }
            });
    }

    parseAction(
        parent: CardElement,
        source: any,
        forbiddenActionTypes: string[],
        allowFallback: boolean): Action | undefined {
        return this.parseCardObject<Action>(
            parent,
            source,
            forbiddenActionTypes,
            allowFallback,
            (typeName: string) => {
                return this.actionRegistry.createInstance(typeName, this.targetVersion);
            },
            (typeName: string, errorType: Enums.TypeErrorType) => {
                if (errorType == Enums.TypeErrorType.UnknownType) {
                    this.logParseEvent(
                        undefined,
                        Enums.ValidationEvent.UnknownActionType,
                        Strings.errors.unknownActionType(typeName));
                }
                else {
                    this.logParseEvent(
                        undefined,
                        Enums.ValidationEvent.ActionTypeNotAllowed,
                        Strings.errors.actionTypeNotAllowed(typeName));
                }
            });
    }

    get elementRegistry(): CardObjectRegistry<CardElement> {
        return this._elementRegistry ? this._elementRegistry : GlobalRegistry.elements;
    }

    // Not using a property setter here because the setter should accept "undefined"
    // whereas the getter should never return undefined.
    setElementRegistry(value: CardObjectRegistry<CardElement> | undefined) {
        this._elementRegistry = value;
    }

    get actionRegistry(): CardObjectRegistry<Action> {
        return this._actionRegistry ? this._actionRegistry : GlobalRegistry.actions;
    }

    // Not using a property setter here because the setter should accept "undefined"
    // whereas the getter should never return undefined.
    setActionRegistry(value: CardObjectRegistry<Action> | undefined) {
        this._actionRegistry = value;
    }
}

GlobalRegistry.defaultElements.register("Container", Container);
GlobalRegistry.defaultElements.register("TextBlock", TextBlock);
GlobalRegistry.defaultElements.register("RichTextBlock", RichTextBlock, Versions.v1_2);
GlobalRegistry.defaultElements.register("TextRun", TextRun, Versions.v1_2);
GlobalRegistry.defaultElements.register("Image", Image);
GlobalRegistry.defaultElements.register("ImageSet", ImageSet);
GlobalRegistry.defaultElements.register("Media", Media, Versions.v1_1);
GlobalRegistry.defaultElements.register("FactSet", FactSet);
GlobalRegistry.defaultElements.register("ColumnSet", ColumnSet);
GlobalRegistry.defaultElements.register("ActionSet", ActionSet, Versions.v1_2);
GlobalRegistry.defaultElements.register("Input.Text", TextInput);
GlobalRegistry.defaultElements.register("Input.Date", DateInput);
GlobalRegistry.defaultElements.register("Input.Time", TimeInput);
GlobalRegistry.defaultElements.register("Input.Number", NumberInput);
GlobalRegistry.defaultElements.register("Input.ChoiceSet", ChoiceSetInput);
GlobalRegistry.defaultElements.register("Input.Toggle", ToggleInput);

GlobalRegistry.defaultActions.register(OpenUrlAction.JsonTypeName, OpenUrlAction);
GlobalRegistry.defaultActions.register(SubmitAction.JsonTypeName, SubmitAction);
GlobalRegistry.defaultActions.register(ShowCardAction.JsonTypeName, ShowCardAction);
GlobalRegistry.defaultActions.register(ToggleVisibilityAction.JsonTypeName, ToggleVisibilityAction, Versions.v1_2);
GlobalRegistry.defaultActions.register(ExecuteAction.JsonTypeName, ExecuteAction, Versions.v1_4);
