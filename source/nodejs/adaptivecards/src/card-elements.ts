// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import * as Shared from "./shared";
import * as Utils from "./utils";
import * as HostConfig from "./host-config";
import * as TextFormatters from "./text-formatters";
import * as Serialization from "./serializable-object";
import { HostCapabilities } from "./host-capabilities";

function invokeSetCollection(action: Action, collection: ActionCollection | undefined) {
    if (action && collection) {
        // Closest emulation of "internal" in TypeScript.
        action["setCollection"](collection);
    }
}

function isActionAllowed(action: Action, forbiddenActionTypes: string[]): boolean {
    if (forbiddenActionTypes) {
        for (let forbiddenType of forbiddenActionTypes) {
            if (action.getJsonTypeName() === forbiddenType) {
                return false;
            }
        }
    }

    return true;
}

enum InstanceCreationErrorType {
    UnknownType,
    ForbiddenType
}

function createCardObjectInstance<T extends CardObject>(
    parent: CardElement | undefined,
    json: any,
    forbiddenTypeNames: string[],
    allowFallback: boolean,
    createInstanceCallback: (typeName: string) => T | undefined,
    createValidationErrorCallback: (typeName: string, errorType: InstanceCreationErrorType) => Shared.IValidationError,
    errors: Shared.IValidationError[] | undefined): T | undefined {
    let result: T | undefined = undefined;

    if (json && typeof json === "object") {
        let tryToFallback = false;
        let typeName = Utils.getStringValue(json["type"]);
        
        if (forbiddenTypeNames && forbiddenTypeNames.indexOf(typeName) >= 0) {
            raiseParseError(createValidationErrorCallback(typeName, InstanceCreationErrorType.ForbiddenType), errors);
        }
        else {
            result = createInstanceCallback(typeName);

            if (!result) {
                tryToFallback = allowFallback;

                raiseParseError(createValidationErrorCallback(typeName, InstanceCreationErrorType.UnknownType), errors);
            }
            else {
                result.setParent(parent);
                result.parse(json, errors);

                tryToFallback = result.shouldFallback() && allowFallback;
            }

            if (tryToFallback) {
                let fallback = json["fallback"];

                if (!fallback && parent) {
                    parent.setShouldFallback(true);
                }
                if (typeof fallback === "string" && fallback.toLowerCase() === "drop") {
                    result = undefined;
                }
                else if (typeof fallback === "object") {
                    result = createCardObjectInstance<T>(
                        parent,
                        fallback,
                        forbiddenTypeNames,
                        true,
                        createInstanceCallback,
                        createValidationErrorCallback,
                        errors);
                }
            }
        }
    }

    return result;
}

export function createActionInstance(
    parent: CardElement,
    json: any,
    forbiddenActionTypes: string[],
    allowFallback: boolean,
    errors: Shared.IValidationError[] | undefined): Action | undefined {
    return createCardObjectInstance<Action>(
        parent,
        json,
        forbiddenActionTypes,
        allowFallback,
        (typeName: string) => { return AdaptiveCard.actionTypeRegistry.createInstance(typeName); },
        (typeName: string, errorType: InstanceCreationErrorType) => {
            if (errorType == InstanceCreationErrorType.UnknownType) {
                return {
                    error: Enums.ValidationError.UnknownActionType,
                    message: "Unknown action type: " + typeName + ". Fallback will be used if present."
                }
            }
            else {
                return {
                    error: Enums.ValidationError.ActionTypeNotAllowed,
                    message: "Action type " + typeName + " is not allowed in this context."
                }
            }
        },
        errors);
}

export function createElementInstance(
    parent: CardElement | undefined,
    json: any,
    allowFallback: boolean,
    errors: Shared.IValidationError[] | undefined): CardElement | undefined {
    return createCardObjectInstance<CardElement>(
        parent,
        json,
        [], // Forbidden types not supported for elements for now
        allowFallback,
        (typeName: string) => { return AdaptiveCard.elementTypeRegistry.createInstance(typeName); },
        (typeName: string, errorType: InstanceCreationErrorType) => {
            if (errorType == InstanceCreationErrorType.UnknownType) {
                return {
                    error: Enums.ValidationError.UnknownElementType,
                    message: "Unknown element type: " + typeName + ". Fallback will be used if present."
                }
            }
            else {
                return {
                    error: Enums.ValidationError.ElementTypeNotAllowed,
                    message: "Element type " + typeName + " is not allowed in this context."
                }
            }
        },
        errors);
}

export class ValidationFailure {
    readonly errors: Shared.IValidationError[] = [];

    constructor(readonly cardObject: CardObject) { }
}

export class ValidationResults {
    private getFailureIndex(cardObject: CardObject) {
        for (let i = 0; i < this.failures.length; i++) {
            if (this.failures[i].cardObject === cardObject) {
                return i;
            }
        }

        return -1;
    }

    readonly allIds: Shared.Dictionary<number> = {};
    readonly failures: ValidationFailure[] = [];

    addFailure(cardObject: CardObject, error: Shared.IValidationError) {
        let index = this.getFailureIndex(cardObject);
        let failure: ValidationFailure;

        if (index < 0) {
            failure = new ValidationFailure(cardObject);

            this.failures.push(failure);
        }
        else {
            failure = this.failures[index];
        }

        failure.errors.push(error);
    }
}

export abstract class CardObject extends Serialization.SerializableObject {
    static readonly typeNameProperty = new Serialization.StringPropertyDefinition(
        Shared.Versions.v1_0,
        "type",
        undefined,
        undefined,
        undefined,
        (sender: object) => {
            return (<CardObject>sender).getJsonTypeName()
        });
    static readonly idProperty = new Serialization.StringPropertyDefinition(Shared.Versions.v1_0, "id");

    protected populateSchema(schema: Serialization.SerializableObjectSchema) {
        schema.add(
            CardObject.typeNameProperty,
            CardObject.idProperty);
    }

    abstract getJsonTypeName(): string;
    abstract shouldFallback(): boolean;
    abstract setParent(parent: CardElement | undefined): void;

    internalValidateProperties(context: ValidationResults) {
        if (!Utils.isNullOrEmpty(this.id)) {
            if (context.allIds.hasOwnProperty(this.id)) {
                if (context.allIds[this.id] == 1) {
                    context.addFailure(
                        this,
                        {
                            error: Enums.ValidationError.DuplicateId,
                            message: "Duplicate Id: " + this.id
                        });
                }

                context.allIds[this.id] += 1;
            }
            else {
                context.allIds[this.id] = 1;
            }
        }
    }

    validateProperties(): ValidationResults {
        let result = new ValidationResults();

        this.internalValidateProperties(result);

        return result;
    }

    @Serialization.schemaProperty(CardObject.idProperty)
    id: string;
}

export type CardElementHeight = "auto" | "stretch";

export abstract class CardElement extends CardObject {
    //#region Schema

    static readonly langProperty = new Serialization.StringPropertyDefinition(Shared.Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig);
    static readonly isVisibleProperty = new Serialization.BooleanPropertyDefinition(Shared.Versions.v1_2, "isVisible", true);
    static readonly separatorProperty = new Serialization.BooleanPropertyDefinition(Shared.Versions.v1_0, "separator", false);
    static readonly heightProperty = new Serialization.ValueSetPropertyDefinition(
        Shared.Versions.v1_1,
        "height",
        [
            { value: "auto" },
            { value: "stretch" }
        ],
        "auto");
    static readonly horizontalAlignmentProperty = new Serialization.EnumPropertyDefinition(
        Shared.Versions.v1_0,
        "horizontalAlignment",
        Enums.HorizontalAlignment,
        Enums.HorizontalAlignment.Left);
    static readonly spacingProperty = new Serialization.EnumPropertyDefinition(
        Shared.Versions.v1_0,
        "spacing",
        Enums.Spacing,
        Enums.Spacing.Default);
    static readonly requiresProperty = new Serialization.SerializableObjectPropertyDefinition(
        Shared.Versions.v1_2,
        "requires",
        () => { return new HostCapabilities(); },
        () =>  { return new HostCapabilities(); });
    static readonly minHeightProperty = new Serialization.PixelSizePropertyDefinition(Shared.Versions.v1_2, "minHeight");

    protected populateSchema(schema: Serialization.SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.add(
            CardElement.langProperty,
            CardElement.isVisibleProperty,
            CardElement.separatorProperty,
            CardElement.heightProperty,
            CardElement.horizontalAlignmentProperty,
            CardElement.spacingProperty,
            CardElement.requiresProperty);

        if (this.supportsMinHeight) {
            schema.add(CardElement.minHeightProperty);
        }
    }

    @Serialization.schemaProperty(CardElement.minHeightProperty)
    minPixelHeight?: number;

    @Serialization.schemaProperty(CardElement.horizontalAlignmentProperty)
    horizontalAlignment: Enums.HorizontalAlignment;

    @Serialization.schemaProperty(CardElement.spacingProperty)
    spacing: Enums.Spacing;

    @Serialization.schemaProperty(CardElement.separatorProperty)
    separator: boolean;

    @Serialization.schemaProperty(CardElement.heightProperty)
    height: CardElementHeight = "auto";

    @Serialization.schemaProperty(CardElement.langProperty)
    get lang(): string | undefined {
        let lang = this.getValue(CardElement.langProperty);

        if (!Utils.isNullOrEmpty(lang)) {
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

    @Serialization.schemaProperty(CardElement.isVisibleProperty)
    get isVisible(): boolean {
        return this.getValue(CardElement.isVisibleProperty);
    }

    set isVisible(value: boolean) {
        // If the element is going to be hidden, reset any changes that were due
        // to overflow truncation (this ensures that if the element is later
        // un-hidden it has the right content)
        if (Shared.GlobalSettings.useAdvancedCardBottomTruncation && !value) {
            this.undoOverflowTruncation();
        }

        if (this.isVisible !== value) {
            this.setValue(CardElement.isVisibleProperty, value);

            this.updateRenderedElementVisibility();

            if (this._renderedElement) {
                raiseElementVisibilityChangedEvent(this);
            }
        }
    }

    //#endregion

    private _shouldFallback: boolean = false;
    private _hostConfig?: HostConfig.HostConfig;
    private _parent?: CardElement;
    private _renderedElement?: HTMLElement;
    private _separatorElement?: HTMLElement;
    private _truncatedDueToOverflow: boolean = false;
    private _defaultRenderedElementDisplayMode: string | null = null;
    private _padding?: Shared.PaddingDefinition;

    private internalRenderSeparator(): HTMLElement | undefined {
        let renderedSeparator = Utils.renderSeparation(
            this.hostConfig,
            {
                spacing: this.hostConfig.getEffectiveSpacing(this.spacing),
                lineThickness: this.separator ? this.hostConfig.separator.lineThickness : undefined,
                lineColor: this.separator ? this.hostConfig.separator.lineColor : undefined
            },
            this.separatorOrientation);

            if (Shared.GlobalSettings.alwaysBleedSeparators && renderedSeparator && this.separatorOrientation == Enums.Orientation.Horizontal) {
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
            this._renderedElement.style.display = displayMode;
        }

        if (this._separatorElement) {
            if (this.parent && this.parent.isFirstElement(this)) {
                this._separatorElement.style.display = "none";
            }
            else {
                this._separatorElement.style.display = displayMode;
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

        if (this.isHiddenDueToOverflow) {
            this.showElementHiddenDueToOverflow();
        }

        return sizeChanged;
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

        if (this.minPixelHeight) {
            renderedElement.style.minHeight = this.minPixelHeight + "px";
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
        if (this.separatorElement) {
            if (Shared.GlobalSettings.alwaysBleedSeparators && this.separatorOrientation == Enums.Orientation.Horizontal && !this.isBleeding()) {
                let padding = new Shared.PaddingDefinition();

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

    protected getDefaultPadding(): Shared.PaddingDefinition {
        return new Shared.PaddingDefinition();
    }

    protected getHasBackground(): boolean {
        return false;
    }

    protected getPadding(): Shared.PaddingDefinition | undefined {
        return this._padding;
    }

    protected setPadding(value: Shared.PaddingDefinition | undefined) {
        this._padding = value;
    }

    protected get supportsMinHeight(): boolean {
        return false;
    }

    protected get useDefaultSizing(): boolean {
        return true;
    }

    protected get allowCustomPadding(): boolean {
        return true;
    }

    protected get separatorOrientation(): Enums.Orientation {
        return Enums.Orientation.Horizontal;
    }

    protected get defaultStyle(): string {
        return Enums.ContainerStyle.Default;
    }

    customCssSelector?: string;

    abstract getJsonTypeName(): string;

    asString(): string | undefined {
        return "";
    }

    isBleeding(): boolean {
        return false;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
		super.parse(json, errors);

        raiseParseElementEvent(this, json, errors);
    }

    setParent(value: CardElement | undefined) {
        this._parent = value;
    }

    getEffectiveStyle(): string {
        if (this.parent) {
            return this.parent.getEffectiveStyle();
        }

        return this.defaultStyle;
    }

    getEffectiveStyleDefinition(): HostConfig.ContainerStyleDefinition {
        return this.hostConfig.containerStyles.getStyleByName(this.getEffectiveStyle());
    }

    getForbiddenElementTypes(): string[] {
        return [];
    }

    getForbiddenActionTypes(): any[] {
        return [];
    }

    getImmediateSurroundingPadding(
        result: Shared.PaddingDefinition,
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
        throw new Error("Index out of range.");
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
            if (this.customCssSelector) {
                this._renderedElement.classList.add(this.customCssSelector);
            }

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
        let rootElement: CardElement = this;

        while (rootElement.parent) {
            rootElement = rootElement.parent;
        }

        return rootElement;
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

    getAllInputs(): Input[] {
        return [];
    }

    getResourceInformation(): Shared.IResourceInformation[] {
        return [];
    }

    getElementById(id: string): CardElement | undefined {
        return this.id === id ? this : undefined;
    }

    getActionById(id: string): Action | undefined {
        return undefined;
    }

    shouldFallback(): boolean {
        return this._shouldFallback || !this.requires.areAllMet(this.hostConfig.hostCapabilities);
    }

    setShouldFallback(value: boolean) {
        this._shouldFallback = value;
    }

    getEffectivePadding(): Shared.PaddingDefinition {
        let padding = this.getPadding();

        return (padding && this.allowCustomPadding) ? padding : this.getDefaultPadding();
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

    get parent(): CardElement | undefined {
        return this._parent;
    }

    get requires(): HostCapabilities {
        return this.getValue(CardElement.requiresProperty);
    }

    get hasVisibleSeparator(): boolean {
        if (this.parent && this.separatorElement) {
            return !this.parent.isFirstElement(this) && (this.isVisible || this.isDesignMode());
        }
        else {
            return false;
        }
    }

    get renderedElement(): HTMLElement | undefined {
        return this._renderedElement;
    }

    get separatorElement(): HTMLElement | undefined {
        return this._separatorElement;
    }
}

export abstract class BaseTextBlock extends CardElement {
    //#region Schema

    static readonly textProperty = new Serialization.StringPropertyDefinition(
        Shared.Versions.v1_0,
        "text",
        true);
    static readonly sizeProperty = new Serialization.EnumPropertyDefinition(
        Shared.Versions.v1_0,
        "size",
        Enums.TextSize,
        Enums.TextSize.Default);
    static readonly weightProperty = new Serialization.EnumPropertyDefinition(
        Shared.Versions.v1_0,
        "weight",
        Enums.TextWeight,
        Enums.TextWeight.Default);
    static readonly colorProperty = new Serialization.EnumPropertyDefinition(
        Shared.Versions.v1_0,
        "color",
        Enums.TextColor,
        Enums.TextColor.Default);
    static readonly isSubtleProperty = new Serialization.BooleanPropertyDefinition(
        Shared.Versions.v1_0,
        "isSubtle",
        false);
    static readonly fontTypeProperty = new Serialization.EnumPropertyDefinition(
        Shared.Versions.v1_2,
        "fontType",
        Enums.FontType);

    protected populateSchema(schema: Serialization.SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.add(
            BaseTextBlock.textProperty,
            BaseTextBlock.sizeProperty,
            BaseTextBlock.weightProperty,
            BaseTextBlock.colorProperty,
            BaseTextBlock.isSubtleProperty,
            BaseTextBlock.fontTypeProperty);
    }

    @Serialization.schemaProperty(BaseTextBlock.sizeProperty)
    size: Enums.TextSize = Enums.TextSize.Default;

    @Serialization.schemaProperty(BaseTextBlock.weightProperty)
    weight: Enums.TextWeight = Enums.TextWeight.Default;

    @Serialization.schemaProperty(BaseTextBlock.colorProperty)
    color: Enums.TextColor = Enums.TextColor.Default;

    @Serialization.schemaProperty(BaseTextBlock.fontTypeProperty)
    fontType?: Enums.FontType;

    @Serialization.schemaProperty(BaseTextBlock.isSubtleProperty)
    isSubtle: boolean = false;

    @Serialization.schemaProperty(BaseTextBlock.textProperty)
    get text(): string | undefined {
        return this.getValue(BaseTextBlock.textProperty);
    }

    set text(value: string | undefined) {
        this.setText(value);
    }

    get selectAction(): Action | undefined {
        return this._selectAction;
    }

    set selectAction(value: Action | undefined) {
        this._selectAction = value;

        if (this._selectAction) {
            this._selectAction.setParent(this);
        }
    }

    //#endregion

    private _selectAction?: Action;

    protected getFontSize(fontType: HostConfig.FontTypeDefinition): number {
        switch (this.size) {
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

    protected getColorDefinition(colorSet: HostConfig.ColorSetDefinition, color: Enums.TextColor): HostConfig.TextColorDefinition {
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

    asString(): string | undefined {
        return this.text;
    }

    applyStylesTo(targetElement: HTMLElement) {
        let fontType = this.hostConfig.getFontTypeDefinition(this.fontType);

        if (fontType.fontFamily) {
            targetElement.style.fontFamily = fontType.fontFamily;
        }

        let fontSize: number;

        switch (this.size) {
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

        targetElement.style.color = <string>Utils.stringToCssColor(this.isSubtle ? colorDefinition.subtle : colorDefinition.default);

        let fontWeight: number;

        switch (this.weight) {
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
    }

    get effectiveColor(): Enums.TextColor {
        return this.color ? this.color : Enums.TextColor.Default;
    }
}

export class TextBlock extends BaseTextBlock {
    //#region Schema

    static readonly wrapProperty = new Serialization.BooleanPropertyDefinition(Shared.Versions.v1_0, "wrap", false);
    static readonly maxLinesProperty = new Serialization.NumberPropertyDefinition(Shared.Versions.v1_0, "maxLines");

    protected populateSchema(schema: Serialization.SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.add(
            TextBlock.wrapProperty,
            TextBlock.maxLinesProperty);
    }

    @Serialization.schemaProperty(TextBlock.wrapProperty)
    wrap: boolean = false;

    @Serialization.schemaProperty(TextBlock.maxLinesProperty)
    maxLines?: number;

    //#endregion

    private _computedLineHeight: number;
    private _originalInnerHtml: string;
    private _processedText?: string;
    private _treatAsPlainText: boolean = true;

    private restoreOriginalContent() {
        if (this.renderedElement !== undefined) {
            this.renderedElement.style.maxHeight = (this.maxLines && this.maxLines > 0) ? (this._computedLineHeight * this.maxLines) + 'px' : null;
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

    protected getRenderedDomElementType(): string {
        return "div";
    }

    protected internalRender(): HTMLElement | undefined {
        this._processedText = undefined;

        if (!Utils.isNullOrEmpty(this.text)) {
            let hostConfig = this.hostConfig;

            let element = document.createElement(this.getRenderedDomElementType());
            element.classList.add(hostConfig.makeCssClassName("ac-textBlock"));
            element.style.overflow = "hidden";

            this.applyStylesTo(element);

            if (this.selectAction) {
                element.onclick = (e) => {
                    e.preventDefault();
                    e.cancelBubble = true;

                    if (this.selectAction) {
                        this.selectAction.execute();
                    }
                }

                if (hostConfig.supportsInteractivity) {
                    element.tabIndex = 0
                    element.setAttribute("role", "button");
                    element.setAttribute("aria-label", this.selectAction.title);
                    element.classList.add(hostConfig.makeCssClassName("ac-selectable"));
                }
            }

            if (!this._processedText) {
                this._treatAsPlainText = true;

                let formattedText = TextFormatters.formatText(this.lang, this.text);

                if (this.useMarkdown && formattedText) {
                    if (Shared.GlobalSettings.allowMarkForTextHighlighting) {
                        formattedText = formattedText.replace(/<mark>/g, "===").replace(/<\/mark>/g, "/==");
                    }

                    let markdownProcessingResult = AdaptiveCard.applyMarkdown(formattedText);

                    if (markdownProcessingResult.didProcess && markdownProcessingResult.outputHtml) {
                        this._processedText = markdownProcessingResult.outputHtml;
                        this._treatAsPlainText = false;

                        // Only process <mark> tag if markdown processing was applied because
                        // markdown processing is also responsible for sanitizing the input string
                        if (Shared.GlobalSettings.allowMarkForTextHighlighting && this._processedText) {
                            let markStyle: string = "";
                            let effectiveStyle = this.getEffectiveStyleDefinition();

                            if (effectiveStyle.highlightBackgroundColor) {
                                markStyle += "background-color: " + effectiveStyle.highlightBackgroundColor + ";";
                            }

                            if (effectiveStyle.highlightForegroundColor) {
                                markStyle += "color: " + effectiveStyle.highlightForegroundColor + ";";
                            }

                            if (!Utils.isNullOrEmpty(markStyle)) {
                                markStyle = 'style="' + markStyle + '"';
                            }

                            this._processedText = this._processedText.replace(/===/g, "<mark " + markStyle + ">").replace(/\/==/g, "</mark>");
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
                anchor.onclick = (e) => {
                    if (raiseAnchorClickedEvent(this, e.target as HTMLAnchorElement)) {
                        e.preventDefault();
                        e.cancelBubble = true;
                    }
                }
            }

            if (this.wrap) {
                element.style.wordWrap = "break-word";

                if (this.maxLines && this.maxLines > 0) {
                    element.style.maxHeight = (this._computedLineHeight * this.maxLines) + "px";
                    element.style.overflow = "hidden";
                }
            }
            else {
                element.style.whiteSpace = "nowrap";
                element.style.textOverflow = "ellipsis";
            }

            if (Shared.GlobalSettings.useAdvancedTextBlockTruncation || Shared.GlobalSettings.useAdvancedCardBottomTruncation) {
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

        if (Shared.GlobalSettings.useAdvancedTextBlockTruncation && this.maxLines) {
            let maxHeight = this._computedLineHeight * this.maxLines;

            this.truncateIfSupported(maxHeight);
        }
    }

    useMarkdown: boolean = true;

    applyStylesTo(targetElement: HTMLElement) {
        super.applyStylesTo(targetElement);

        let parentContainer = this.getParentContainer();
        let isRtl = parentContainer ? parentContainer.isRtl() : false;

        switch (this.horizontalAlignment) {
            case Enums.HorizontalAlignment.Center:
                targetElement.style.textAlign = "center";
                break;
            case Enums.HorizontalAlignment.Right:
                targetElement.style.textAlign = isRtl ? "left" : "right";
                break;
            default:
                targetElement.style.textAlign = isRtl ? "right" : "left";
                break;
        }

        let lineHeights = this.hostConfig.lineHeights;

        if (lineHeights) {
            switch (this.size) {
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
            this._computedLineHeight = this.getFontSize(this.hostConfig.getFontTypeDefinition(this.fontType)) * 1.33;
        }

        targetElement.style.lineHeight = this._computedLineHeight + "px";
    }

    getJsonTypeName(): string {
        return "TextBlock";
    }

    updateLayout(processChildren: boolean = false) {
        super.updateLayout(processChildren);

        if (Shared.GlobalSettings.useAdvancedTextBlockTruncation && this.maxLines && this.isDisplayed()) {
            // Reset the element's innerHTML in case the available room for
            // content has increased
            this.restoreOriginalContent();
            this.truncateIfSupported(this._computedLineHeight * this.maxLines);
        }
    }
}

class Label extends TextBlock {
    protected getRenderedDomElementType(): string {
        return "label";
    }

    protected internalRender(): HTMLElement | undefined {
        let renderedElement = <HTMLLabelElement>super.internalRender();

        if (!Utils.isNullOrEmpty(this.forElementId)) {
            renderedElement.htmlFor = this.forElementId;
        }

        return renderedElement;
    }

    forElementId: string;
}

export class TextRun extends BaseTextBlock {
    //#region Schema

    static readonly italicProperty = new Serialization.BooleanPropertyDefinition(Shared.Versions.v1_2, "italic", false);
    static readonly strikethroughProperty = new Serialization.BooleanPropertyDefinition(Shared.Versions.v1_2, "strikethrough", false);
    static readonly highlightProperty = new Serialization.BooleanPropertyDefinition(Shared.Versions.v1_2, "highlight", false);

    protected populateSchema(schema: Serialization.SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.add(
            TextRun.italicProperty,
            TextRun.strikethroughProperty,
            TextRun.highlightProperty);
    }

    @Serialization.schemaProperty(TextRun.italicProperty)
    italic: boolean = false;

    @Serialization.schemaProperty(TextRun.strikethroughProperty)
    strikethrough: boolean = false;

    @Serialization.schemaProperty(TextRun.highlightProperty)
    highlight: boolean = false;

    //#endregion

    protected internalRender(): HTMLElement | undefined {
        if (!Utils.isNullOrEmpty(this.text)) {
            let hostConfig = this.hostConfig;

            let formattedText = TextFormatters.formatText(this.lang, this.text);

            if (!formattedText) {
                formattedText = "";
            }

            let element = document.createElement("span");
            element.classList.add(hostConfig.makeCssClassName("ac-textRun"));

            this.applyStylesTo(element);

            if (this.selectAction && hostConfig.supportsInteractivity) {
                let anchor = document.createElement("a");
                anchor.classList.add(hostConfig.makeCssClassName("ac-anchor"));
                anchor.href = this.selectAction.getHref();
                anchor.target = "_blank";
                anchor.onclick = (e) => {
                    e.preventDefault();
                    e.cancelBubble = true;

                    if (this.selectAction) {
                        this.selectAction.execute();
                    }
                }

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

            targetElement.style.backgroundColor = <string>Utils.stringToCssColor(this.isSubtle ? colorDefinition.highlightColors.subtle : colorDefinition.highlightColors.default);
        }
    }

    toJSON() {
        let result = super.toJSON();

        if (this.selectAction) {
            Utils.setProperty(result, "selectAction", this.selectAction.toJSON());
        }

        return result;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.selectAction = createActionInstance(
            this,
            json["selectAction"],
            [ShowCardAction.JsonTypeName],
            !this.isDesignMode(),
            errors);
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
            throw new Error("RichTextBlock.addInline: the specified card element cannot be used as a RichTextBlock inline.");
        }

        let doAdd: boolean = inline.parent === undefined || forceAdd;

        if (!doAdd && inline.parent != this) {
            throw new Error("RichTextBlock.addInline: the specified inline already belongs to another RichTextBlock.");
        }
        else {
            inline.setParent(this);

            this._inlines.push(inline);
        }
    }

    protected internalRender(): HTMLElement | undefined {
        if (this._inlines.length > 0) {
            let element = document.createElement("div");
            element.className = this.hostConfig.makeCssClassName("ac-richTextBlock");

            let parentContainer = this.getParentContainer();
            let isRtl = parentContainer ? parentContainer.isRtl() : false;

            switch (this.horizontalAlignment) {
                case Enums.HorizontalAlignment.Center:
                    element.style.textAlign = "center";
                    break;
                case Enums.HorizontalAlignment.Right:
                    element.style.textAlign = isRtl ? "left" : "right";
                    break;
                default:
                    element.style.textAlign = isRtl ? "right" : "left";
                    break;
            }

            for (let inline of this._inlines) {
                let renderedInline = inline.render();

                if (renderedInline) {
                    element.appendChild(renderedInline);
                }
            }

            return element;
        }
        else {
            return undefined;
        }
    }

    asString(): string | undefined {
        let result = "";

        for (let inline of this._inlines) {
            result += inline.asString();
        }

        return result;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this._inlines = [];

        if (Array.isArray(json["inlines"])) {
            for (let jsonInline of json["inlines"]) {
                let inline: CardElement | undefined;

                if (typeof jsonInline === "string") {
                    let textRun = new TextRun();
                    textRun.text = jsonInline;

                    inline = textRun;
                }
                else {
                    inline = createElementInstance(
                        this,
                        jsonInline,
                        false, // No fallback for inlines in 1.2
                        errors);
                }

                if (inline) {
                    this.internalAddInline(inline, true);
                }
            }
        }
    }

    toJSON() {
        let result = super.toJSON();

        if (this._inlines.length > 0) {
            let jsonInlines: any[] = [];

            for (let inline of this._inlines) {
                jsonInlines.push(inline.toJSON());
            }

            Utils.setProperty(result, "inlines", jsonInlines);
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
            throw new Error("RichTextBlock.getInlineAt: Index out of range (" + index + ")");
        }
    }

    addInline(inline: CardElement) {
        this.internalAddInline(inline);
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

export class Fact extends Serialization.SerializableObject {
    //#region Schema

    static readonly titleProperty = new Serialization.StringPropertyDefinition(Shared.Versions.v1_0, "title");
    static readonly valueProperty = new Serialization.StringPropertyDefinition(Shared.Versions.v1_0, "value");

    protected populateSchema(schema: Serialization.SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.add(
            Fact.titleProperty,
            Fact.valueProperty);
    }

    // For historic reasons, the "title" schema property is exposed as "name" in the OM.
    @Serialization.schemaProperty(Fact.titleProperty)
    name?: string;

    @Serialization.schemaProperty(Fact.valueProperty)
    value?: string;

    //#endregion

    constructor(name?: string, value?: string) {
        super();

        this.name = name;
        this.value = value;
    }
}

export class FactSet extends CardElement {
    //#region Schema

    static readonly factsProperty = new Serialization.SerializableObjectCollectionPropertyDefinition<Fact>(
        Shared.Versions.v1_0,
        "facts",
        (sourceItem: any) => { return new Fact(); },
        (sender: object) => { return []; });

    protected populateSchema(schema: Serialization.SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.add(FactSet.factsProperty);
    }

    @Serialization.schemaProperty(FactSet.factsProperty)
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
                textBlock.text = Utils.isNullOrEmpty(this.facts[i].name) ? "Title" : this.facts[i].name;
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

class ImageDimensionProperty extends Serialization.TypedPropertyDefinition<number> {
    parse(sender: any, source: Serialization.PropertyBag, errors?: Shared.IValidationError[]): number | undefined {
        let result: number | undefined = Utils.getNumberValue(source[this.legacyPropertyName], undefined);

        if (result) {
            raiseParseError(
                {
                    error: Enums.ValidationError.Deprecated,
                    message: "The " + this.legacyPropertyName + " property is deprecated and will be removed. Use the width property instead."
                },
                errors
            );
        }
        else {
            let value = source[this.name];

            if (typeof value === "string") {
                let isValid = false;

                try {
                    let size = Shared.SizeAndUnit.parse(value, true);

                    if (size.unit == Enums.SizeUnit.Pixel) {
                        result = size.physicalSize;

                        isValid = true;
                    }
                }
                catch {
                    // Do nothing. A parse error is emitted below
                }

                if (!isValid) {
                    raiseParseError(
                        {
                            error: Enums.ValidationError.InvalidPropertyValue,
                            message: "Invalid " + this.name + " value: " + value
                        },
                        errors
                    );
                }
            }
        }

        return result;
    }

    toJSON(target: object, value: any) {
        Utils.setProperty(
            target,
            this.name,
            typeof value === "number" && !isNaN(value) ? value + "px" : undefined);
    }

    constructor(
        readonly targetVersion: Shared.TargetVersion,
        readonly name: string,
        readonly legacyPropertyName: string) {
        super(targetVersion, name);
    }
}

export class Image extends CardElement {
    //#region Schema

    static readonly urlProperty = new Serialization.StringPropertyDefinition(Shared.Versions.v1_0, "url");
    static readonly altTextProperty = new Serialization.StringPropertyDefinition(Shared.Versions.v1_0, "altText");
    static readonly backgroundColorProperty = new Serialization.StringPropertyDefinition(Shared.Versions.v1_1, "backgroundColor");
    static readonly styleProperty = new Serialization.EnumPropertyDefinition(
        Shared.Versions.v1_0,
        "style",
        Enums.ImageStyle,
        Enums.ImageStyle.Default);
    static readonly sizeProperty = new Serialization.EnumPropertyDefinition(
        Shared.Versions.v1_0,
        "size",
        Enums.Size,
        Enums.Size.Auto);
    static readonly pixelWidthProperty = new ImageDimensionProperty(Shared.Versions.v1_1, "width", "pixelWidth");
    static readonly pixelHeightProperty = new ImageDimensionProperty(Shared.Versions.v1_1, "height", "pixelHeight");

    protected populateSchema(schema: Serialization.SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.add(
            Image.urlProperty,
            Image.altTextProperty,
            Image.backgroundColorProperty,
            Image.styleProperty,
            Image.sizeProperty,
            Image.pixelWidthProperty,
            Image.pixelHeightProperty);
    }

    @Serialization.schemaProperty(Image.urlProperty)
    url?: string;

    @Serialization.schemaProperty(Image.altTextProperty)
    altText?: string;

    @Serialization.schemaProperty(Image.backgroundColorProperty)
    backgroundColor?: string;

    @Serialization.schemaProperty(Image.sizeProperty)
    size: Enums.Size = Enums.Size.Auto;

    @Serialization.schemaProperty(Image.styleProperty)
    style: Enums.ImageStyle = Enums.ImageStyle.Default;

    @Serialization.schemaProperty(Image.pixelWidthProperty)
    pixelWidth?: number;

    @Serialization.schemaProperty(Image.pixelHeightProperty)
    pixelHeight?: number;

    get selectAction(): Action | undefined {
        return this._selectAction;
    }

    set selectAction(value: Action | undefined) {
        this._selectAction = value;

        if (this._selectAction) {
            this._selectAction.setParent(this);
        }
    }

    //#endregion

    private _selectAction?: Action;

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

    protected internalRender(): HTMLElement | undefined {
        let element: HTMLElement | undefined = undefined;

        if (!Utils.isNullOrEmpty(this.url)) {
            element = document.createElement("div");
            element.style.display = "flex";
            element.style.alignItems = "flex-start";

            element.onkeypress = (e) => {
                if (this.selectAction && (e.keyCode == 13 || e.keyCode == 32)) { // enter or space pressed
                    e.preventDefault();
                    e.cancelBubble = true;

                    this.selectAction.execute();
                }
            }

            element.onclick = (e) => {
                if (this.selectAction) {
                    e.preventDefault();
                    e.cancelBubble = true;

                    this.selectAction.execute();
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
            imageElement.style.maxHeight = "100%";
            imageElement.style.minWidth = "0";
            imageElement.classList.add(hostConfig.makeCssClassName("ac-image"));

            if (this.selectAction !== undefined && hostConfig.supportsInteractivity) {
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

            imageElement.style.backgroundColor = <string>Utils.stringToCssColor(this.backgroundColor);
            imageElement.src = <string>this.url;
            imageElement.alt = <string>this.altText;

            element.appendChild(imageElement);
        }

        return element;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.selectAction = createActionInstance(
            this,
            json["selectAction"],
            [ShowCardAction.JsonTypeName],
            !this.isDesignMode(),
            errors);
    }

    toJSON(): any {
        let result = super.toJSON();

        if (this._selectAction) {
            Utils.setProperty(result, "selectAction", this._selectAction.toJSON());
        }

        return result;
    }

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

    getResourceInformation(): Shared.IResourceInformation[] {
        if (!Utils.isNullOrEmpty(this.url)) {
            return [{ url: <string>this.url, mimeType: "image" }]
        }
        else {
            return [];
        }
    }
}

export abstract class CardElementContainer extends CardElement {
    private _selectAction?: Action;

    protected isElementAllowed(element: CardElement, forbiddenElementTypes: string[]) {
        if (!this.hostConfig.supportsInteractivity && element.isInteractive) {
            return false;
        }

        if (forbiddenElementTypes) {
            for (let forbiddenElementType of forbiddenElementTypes) {
                if (element.getJsonTypeName() === forbiddenElementType) {
                    return false;
                }
            }
        }

        return true;
    }

    protected applyPadding() {
        super.applyPadding();

        if (!this.renderedElement) {
            return;
        }

        let physicalPadding = new Shared.SpacingDefinition();

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

    protected getSelectAction(): Action | undefined {
        return this._selectAction;
    }

    protected setSelectAction(value: Action | undefined) {
        this._selectAction = value;

        if (this._selectAction) {
            this._selectAction.setParent(this);
        }
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

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        if (this.isSelectable) {
            this._selectAction = createActionInstance(
                this,
                json["selectAction"],
                [ShowCardAction.JsonTypeName],
                !this.isDesignMode(),
                errors);
        }
    }

    toJSON(): any {
        let result = super.toJSON();

        if (this._selectAction && this.isSelectable) {
            Utils.setProperty(result, "selectAction", this._selectAction.toJSON());
        }

        return result;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        for (let i = 0; i < this.getItemCount(); i++) {
            let item = this.getItemAt(i);

            if (!this.hostConfig.supportsInteractivity && item.isInteractive) {
                context.addFailure(
                    this,
                    {
                        error: Enums.ValidationError.InteractivityNotAllowed,
                        message: "Interactivity is not allowed."
                    });
            }

            if (!this.isElementAllowed(item, this.getForbiddenElementTypes())) {
                context.addFailure(
                    this,
                    {
                        error: Enums.ValidationError.InteractivityNotAllowed,
                        message: "Elements of type " + item.getJsonTypeName() + " are not allowed in this container."
                    });
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
                element.classList.add(hostConfig.makeCssClassName("ac-selectable"));
                element.tabIndex = 0;
                element.setAttribute("role", "button");
                element.setAttribute("aria-label", this._selectAction.title);

                element.onclick = (e) => {
                    if (this._selectAction !== undefined) {
                        e.preventDefault();
                        e.cancelBubble = true;

                        this._selectAction.execute();
                    }
                }

                element.onkeypress = (e) => {
                    if (this._selectAction !== undefined && (e.keyCode == 13 || e.keyCode == 32)) {
                        // Enter or space pressed
                        e.preventDefault();
                        e.cancelBubble = true;

                        this._selectAction.execute();
                    }
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

    getAllInputs(): Input[] {
        let result: Input[] = [];

        for (let i = 0; i < this.getItemCount(); i++) {
            result = result.concat(this.getItemAt(i).getAllInputs());
        }

        return result;
    }

    getResourceInformation(): Shared.IResourceInformation[] {
        let result: Shared.IResourceInformation[] = [];

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
}

export class ImageSet extends CardElementContainer {
    //#region Schema

    static readonly imagesProperty = new Serialization.SerializableObjectCollectionPropertyDefinition<Image>(
        Shared.Versions.v1_0,
        "images",
        (sourceItem: any) => { return new Image(); },
        (sender: object) => { return []; },
        (sender: any, item: Image) => { item.setParent(<CardElement>sender); });
    static readonly sizeProperty = new Serialization.EnumPropertyDefinition(
        Shared.Versions.v1_0,
        "size",
        Enums.Size,
        Enums.Size.Medium);

    protected populateSchema(schema: Serialization.SerializableObjectSchema) {
        super.populateSchema(schema);

        schema.add(
            ImageSet.imagesProperty,
            ImageSet.sizeProperty);
    }

    @Serialization.schemaProperty(ImageSet.imagesProperty)
    private _images: Image[] = [];

    @Serialization.schemaProperty(ImageSet.sizeProperty)
    imageSize: Enums.Size = Enums.Size.Medium;

    //#endregion

    protected internalRender(): HTMLElement | undefined {
        let element: HTMLElement | undefined = undefined;

        if (this._images.length > 0) {
            element = document.createElement("div");
            element.style.display = "flex";
            element.style.flexWrap = "wrap";

            for (let image of this._images) {
                image.size = this.imageSize;

                let renderedImage = image.render();

                if (renderedImage) {
                    renderedImage.style.display = "inline-flex";
                    renderedImage.style.margin = "0px";
                    renderedImage.style.marginRight = "10px";
                    renderedImage.style.maxHeight = this.hostConfig.imageSet.maxImageHeight + "px";

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

export class MediaSource extends Serialization.SerializableObject {
    mimeType?: string;
    url?: string;

    constructor(url?: string, mimeType?: string) {
        super();

        this.url = url;
        this.mimeType = mimeType;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

		this.mimeType = Utils.getStringValue(json["mimeType"]);
		this.url = Utils.getStringValue(json["url"]);
	}

	toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "mimeType", this.mimeType);
        Utils.setProperty(result, "url", this.url);

        return result;
    }

    isValid(): boolean {
        return !Utils.isNullOrEmpty(this.mimeType) && !Utils.isNullOrEmpty(this.url);
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
    static readonly supportedMediaTypes = ["audio", "video"];

    private _selectedMediaType?: string;
    private _selectedSources: MediaSource[];

    private getPosterUrl(): string {
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

    private renderPoster(): HTMLElement {
        const playButtonArrowWidth = 12;
        const playButtonArrowHeight = 15;

        let posterRootElement = document.createElement("div");
        posterRootElement.className = this.hostConfig.makeCssClassName("ac-media-poster");
        posterRootElement.setAttribute("role", "contentinfo");
        posterRootElement.setAttribute("aria-label", this.altText ? this.altText : "Media content");
        posterRootElement.style.position = "relative";
        posterRootElement.style.display = "flex";

        let posterUrl = this.getPosterUrl();

        if (posterUrl) {
            let posterImageElement = document.createElement("img");
            posterImageElement.style.width = "100%";
            posterImageElement.style.height = "100%";

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
            playButtonOuterElement.setAttribute("role", "button");
            playButtonOuterElement.setAttribute("aria-label", "Play media");
            playButtonOuterElement.className = this.hostConfig.makeCssClassName("ac-media-playButton");
            playButtonOuterElement.style.display = "flex";
            playButtonOuterElement.style.alignItems = "center";
            playButtonOuterElement.style.justifyContent = "center";
            playButtonOuterElement.onclick = (e) => {
                if (this.hostConfig.media.allowInlinePlayback) {
                    e.preventDefault();
                    e.cancelBubble = true;

                    if (this.renderedElement) {
                        let mediaPlayerElement = this.renderMediaPlayer();

                        this.renderedElement.innerHTML = "";
                        this.renderedElement.appendChild(mediaPlayerElement);

                        mediaPlayerElement.play();
                    }
                }
                else {
                    if (Media.onPlay) {
                        e.preventDefault();
                        e.cancelBubble = true;

                        Media.onPlay(this);
                    }
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

        mediaElement.controls = true;
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

    static onPlay: (sender: Media) => void;

    sources: MediaSource[] = [];
    poster: string;
    altText: string;

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

		this.poster = Utils.getStringValue(json["poster"]);
		this.altText = Utils.getStringValue(json["altText"]);

        this.sources = [];

        if (Array.isArray(json["sources"])) {
            for (let jsonSource of json["sources"]) {
                let source = new MediaSource();
                source.parse(jsonSource, errors);

                this.sources.push(source);
            }
        }
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "poster", this.poster);
        Utils.setProperty(result, "altText", this.altText);
        Utils.setArrayProperty(result, "sources", this.sources);

        return result;
    }

    getJsonTypeName(): string {
        return "Media";
    }

    getResourceInformation(): Shared.IResourceInformation[] {
        let result: Shared.IResourceInformation[] = [];

        let posterUrl = this.getPosterUrl();

        if (!Utils.isNullOrEmpty(posterUrl)) {
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

export class InputValidationOptions extends Serialization.SerializableObject {
    necessity: Enums.InputValidationNecessity = Enums.InputValidationNecessity.Optional;
    errorMessage?: string;

    parse(json: any) {
        super.parse(json);

        this.necessity = <Enums.InputValidationNecessity>Utils.getEnumValue(Enums.InputValidationNecessity, json["necessity"], this.necessity);
        this.errorMessage = Utils.getStringValue(json["errorMessage"]);
    }

    toJSON(): any {
        if (this.necessity != Enums.InputValidationNecessity.Optional || !Utils.isNullOrEmpty(this.errorMessage)) {
            let result = super.toJSON();

            Utils.setEnumProperty(Enums.InputValidationNecessity, result, "necessity", this.necessity, Enums.InputValidationNecessity.Optional);
            Utils.setProperty(result, "errorMessage", this.errorMessage);

            return result;
        }
        else {
            return undefined;
        }
    }
}

export abstract class Input extends CardElement implements Shared.IInput {
    private _outerContainerElement: HTMLElement;
    private _inputControlContainerElement: HTMLElement;
    private _errorMessageElement?: HTMLElement;
    private _renderedInputControlElement: HTMLElement;
    private _defaultValue?: string;

    protected get isNullable(): boolean {
        return true;
    }

    protected get renderedInputControlElement(): HTMLElement {
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

        this._inputControlContainerElement = document.createElement("div");
        this._inputControlContainerElement.className = hostConfig.makeCssClassName("ac-input-container");
        this._inputControlContainerElement.style.display = "flex";

        let renderedInputControlElement = this.internalRender();

        if (renderedInputControlElement) {
            this._renderedInputControlElement = renderedInputControlElement;
            this._renderedInputControlElement.style.minWidth = "0px";

            if (Shared.GlobalSettings.useBuiltInInputValidation && this.isNullable && this.validation.necessity == Enums.InputValidationNecessity.RequiredWithVisualCue) {
                this._renderedInputControlElement.classList.add(hostConfig.makeCssClassName("ac-input-required"));
            }

            this._inputControlContainerElement.appendChild(this._renderedInputControlElement);

            this._outerContainerElement.appendChild(this._inputControlContainerElement);

            return this._outerContainerElement;
        }

        return undefined;
    }

    protected valueChanged() {
        this.resetValidationFailureCue();

        if (this.onValueChanged) {
            this.onValueChanged(this);
        }

        raiseInputValueChangedEvent(this);
    }

    protected resetValidationFailureCue() {
        if (Shared.GlobalSettings.useBuiltInInputValidation && this.renderedElement) {
            this._renderedInputControlElement.classList.remove(this.hostConfig.makeCssClassName("ac-input-validation-failed"));

            if (this._errorMessageElement) {
                this._outerContainerElement.removeChild(this._errorMessageElement);

                this._errorMessageElement = undefined;
            }
        }
    }

    protected showValidationErrorMessage() {
        if (this.renderedElement && Shared.GlobalSettings.useBuiltInInputValidation && Shared.GlobalSettings.displayInputValidationErrors && !Utils.isNullOrEmpty(this.validation.errorMessage)) {
            this._errorMessageElement = document.createElement("span");
            this._errorMessageElement.className = this.hostConfig.makeCssClassName("ac-input-validation-error-message");
            this._errorMessageElement.textContent = <string>this.validation.errorMessage;

            this._outerContainerElement.appendChild(this._errorMessageElement);
        }
    }

    protected parseInputValue(value: string | undefined): string | undefined {
        return value;
    }

    abstract get value(): string | undefined;

    onValueChanged: (sender: Input) => void;

    readonly validation = new InputValidationOptions();

    title: string;

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "title", this.title);
        Utils.setProperty(result, "value", this.renderedElement && !Utils.isNullOrEmpty(this.value) ? this.value : this.defaultValue);

        if (Shared.GlobalSettings.useBuiltInInputValidation) {
            Utils.setProperty(result, "validation", this.validation.toJSON());
        }

        return result;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (Utils.isNullOrEmpty(this.id)) {
            context.addFailure(
                this,
                {
                    error: Enums.ValidationError.PropertyCantBeNull,
                    message: "All inputs must have a unique Id"
                });
        }
    }

    validateValue(): boolean {
        if (Shared.GlobalSettings.useBuiltInInputValidation) {
            this.resetValidationFailureCue();

            let result = this.validation.necessity != Enums.InputValidationNecessity.Optional ? !Utils.isNullOrEmpty(this.value) : true;

            if (!result && this.renderedElement) {
                this._renderedInputControlElement.classList.add(this.hostConfig.makeCssClassName("ac-input-validation-failed"));

                this.showValidationErrorMessage();
            }

            return result;
        }
        else {
            return true;
        }
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.id = Utils.getStringValue(json["id"]);
        this.defaultValue = Utils.getStringValue(json["value"]);

        if (Shared.GlobalSettings.useBuiltInInputValidation) {
            let jsonValidation = json["validation"];

            if (jsonValidation) {
                this.validation.parse(jsonValidation);
            }
        }
    }

    getAllInputs(): Input[] {
        return [this];
    }

    get defaultValue(): string | undefined {
        return this._defaultValue;
    }

    set defaultValue(value: string | undefined) {
        this._defaultValue = this.parseInputValue(value);
    }

    get isInteractive(): boolean {
        return true;
    }
}

export class TextInput extends Input {
    private _inlineAction?: Action;

    protected internalRender(): HTMLElement | undefined {
        if (this.isMultiline) {
            let textareaElement = document.createElement("textarea");
            textareaElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-textInput", "ac-multiline");
            textareaElement.style.flex = "1 1 auto";
            textareaElement.tabIndex = 0;

            if (!Utils.isNullOrEmpty(this.placeholder)) {
                textareaElement.placeholder = this.placeholder;
                textareaElement.setAttribute("aria-label", this.placeholder)
            }

            if (!Utils.isNullOrEmpty(this.defaultValue)) {
                textareaElement.value = <string>this.defaultValue;
            }

            if (this.maxLength && this.maxLength > 0) {
                textareaElement.maxLength = this.maxLength;
            }

            textareaElement.oninput = () => { this.valueChanged(); }
            textareaElement.onkeypress = (e: KeyboardEvent) => {
                // Ctrl+Enter pressed
                if (e.keyCode == 10 && this.inlineAction) {
                    this.inlineAction.execute();
                }
            }

            return textareaElement;
        }
        else {
            let inputElement = document.createElement("input");
            inputElement.type = Enums.InputTextStyle[this.style].toLowerCase();
            inputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-textInput");
            inputElement.style.flex = "1 1 auto";
            inputElement.tabIndex = 0;

            if (!Utils.isNullOrEmpty(this.placeholder)) {
                inputElement.placeholder = this.placeholder;
                inputElement.setAttribute("aria-label", this.placeholder)
            }

            if (!Utils.isNullOrEmpty(this.defaultValue)) {
                inputElement.value = <string>this.defaultValue;
            }

            if (this.maxLength && this.maxLength > 0) {
                inputElement.maxLength = this.maxLength;
            }

            inputElement.oninput = () => { this.valueChanged(); }
            inputElement.onkeypress = (e: KeyboardEvent) => {
                // Enter pressed
                if (e.keyCode == 13 && this.inlineAction) {
                    this.inlineAction.execute();
                }
            }

            return inputElement;
        }
    }

    protected overrideInternalRender(): HTMLElement | undefined {
        let renderedInputControl = super.overrideInternalRender();

        if (this.inlineAction) {
            let button = document.createElement("button");
            button.className = this.hostConfig.makeCssClassName("ac-inlineActionButton");
            button.onclick = (e) => {
                e.preventDefault();
                e.cancelBubble = true;

                if (this.inlineAction) {
                    this.inlineAction.execute();
                }
            };

            if (!Utils.isNullOrEmpty(this.inlineAction.iconUrl)) {
                button.classList.add("iconOnly");

                let icon = document.createElement("img");
                icon.style.height = "100%";

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

                    if (this.inlineAction) {
                        button.textContent = !Utils.isNullOrEmpty(this.inlineAction.title) ? this.inlineAction.title : "Title";
                    }
                    else {
                        button.textContent = "Title";
                    }
                }
                icon.src = this.inlineAction.iconUrl;

                button.appendChild(icon);

                if (!Utils.isNullOrEmpty(this.inlineAction.title)) {
                    button.title = this.inlineAction.title;
                }
            }
            else {
                button.classList.add("textOnly");
                button.textContent = !Utils.isNullOrEmpty(this.inlineAction.title) ? this.inlineAction.title : "Title";
            }

            button.style.marginLeft = "8px";

            this.inputControlContainerElement.appendChild(button);
        }

        return renderedInputControl;
    }

    maxLength: number;
    isMultiline: boolean = false;
    placeholder: string;
    style: Enums.InputTextStyle = Enums.InputTextStyle.Text;

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

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "placeholder", this.placeholder);
        Utils.setNumberProperty(result, "maxLength", this.maxLength);
        Utils.setProperty(result, "isMultiline", this.isMultiline, false);
        Utils.setEnumProperty(Enums.InputTextStyle, result, "style", this.style, Enums.InputTextStyle.Text);

        if (this._inlineAction) {
            Utils.setProperty(result, "inlineAction", this._inlineAction.toJSON());
        }

        return result;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.maxLength = <number>Utils.getNumberValue(json["maxLength"]);
        this.isMultiline = <boolean>Utils.getBoolValue(json["isMultiline"], this.isMultiline);
        this.placeholder = Utils.getStringValue(json["placeholder"]);
        this.style = <Enums.InputTextStyle>Utils.getEnumValue(Enums.InputTextStyle, json["style"], this.style);
        this.inlineAction = createActionInstance(
            this,
            json["inlineAction"],
            [ShowCardAction.JsonTypeName],
            !this.isDesignMode(),
            errors);
    }

    get inlineAction(): Action | undefined {
        return this._inlineAction;
    }

    set inlineAction(value: Action | undefined) {
        this._inlineAction = value;

        if (this._inlineAction) {
            this._inlineAction.setParent(this);
        }
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
    private _checkboxInputElement: HTMLInputElement;

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
        this._checkboxInputElement.setAttribute("aria-label", this.title);
        this._checkboxInputElement.tabIndex = 0;

        if (this.defaultValue == this.valueOn) {
            this._checkboxInputElement.checked = true;
        }

        this._checkboxInputElement.onchange = () => { this.valueChanged(); }

        Utils.appendChild(element, this._checkboxInputElement);

        if (!Utils.isNullOrEmpty(this.title) || this.isDesignMode()) {
            let label = new Label();
            label.setParent(this);
            label.forElementId = this._checkboxInputElement.id;
            label.hostConfig = this.hostConfig;
            label.text = Utils.isNullOrEmpty(this.title) ? this.getJsonTypeName() : this.title;
            label.useMarkdown = Shared.GlobalSettings.useMarkdownInRadioButtonAndCheckbox;
            label.wrap = this.wrap;

            let labelElement = label.render();

            if (labelElement) {
                labelElement.style.display = "inline-block";
                labelElement.style.flex = "1 1 auto";
                labelElement.style.marginLeft = "6px";
                labelElement.style.verticalAlign = "middle";

                let spacerElement = document.createElement("div");
                spacerElement.style.width = "6px";

                Utils.appendChild(element, spacerElement);
                Utils.appendChild(element, labelElement);
            }
        }

        return element;
    }

    protected get isNullable(): boolean {
        return false;
    }

    valueOn: string = "true";
    valueOff: string = "false";
    wrap: boolean = false;

    getJsonTypeName(): string {
        return "Input.Toggle";
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "valueOn", this.valueOn, "true");
        Utils.setProperty(result, "valueOff", this.valueOff, "false");
        Utils.setProperty(result, "wrap", this.wrap);

        return result;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.title = Utils.getStringValue(json["title"]);
        this.valueOn = Utils.getStringValue(json["valueOn"], this.valueOn);
        this.valueOff = Utils.getStringValue(json["valueOff"], this.valueOff);
        this.wrap = <boolean>Utils.getBoolValue(json["wrap"], this.wrap);
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

export class Choice extends Serialization.SerializableObject {
    title?: string;
    value?: string;

    constructor(title?: string, value?: string) {
        super();

        this.title = title;
        this.value = value;
    }

    parse(json: any) {
        super.parse(json);

        this.title = Utils.getStringValue(json["title"]);
        this.value = Utils.getStringValue(json["value"]);
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "title", this.title);
        Utils.setProperty(result, "value", this.value);

        return result;
    }
}

export class ChoiceSetInput extends Input {
    private static uniqueCategoryCounter = 0;

    private static getUniqueCategoryName(): string {
        let uniqueCwtegoryName = "__ac-category" + ChoiceSetInput.uniqueCategoryCounter;

        ChoiceSetInput.uniqueCategoryCounter++;

        return uniqueCwtegoryName;
    }

    private _selectElement: HTMLSelectElement;
    private _toggleInputs: HTMLInputElement[];

    protected internalRender(): HTMLElement | undefined {
        if (!this.isMultiSelect) {
            if (this.isCompact) {
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

                this._selectElement.onchange = () => { this.valueChanged(); }

                return this._selectElement;
            }
            else {
                // Render as a series of radio buttons
                let uniqueCategoryName = ChoiceSetInput.getUniqueCategoryName();

                let element = document.createElement("div");
                element.className = this.hostConfig.makeCssClassName("ac-input", "ac-choiceSetInput-expanded");
                element.style.width = "100%";

                this._toggleInputs = [];

                let i = 0;

                for (let choice of this.choices) {
                    let radioInput = document.createElement("input");
                    radioInput.id = Utils.generateUniqueId();
                    radioInput.type = "radio";
                    radioInput.style.margin = "0";
                    radioInput.style.display = "inline-block";
                    radioInput.style.verticalAlign = "middle";
                    radioInput.name = Utils.isNullOrEmpty(this.id) ? uniqueCategoryName : this.id;
                    radioInput.value = <string>choice.value;
                    radioInput.style.flex = "0 0 auto";
                    radioInput.setAttribute("aria-label", <string>choice.title);

                    if (this.choices[i].value == this.defaultValue) {
                        radioInput.checked = true;
                    }

                    radioInput.onchange = () => { this.valueChanged(); }

                    this._toggleInputs.push(radioInput);

                    let compoundInput = document.createElement("div");
                    compoundInput.style.display = "flex";
                    compoundInput.style.alignItems = "center";

                    Utils.appendChild(compoundInput, radioInput);

                    let label = new Label();
                    label.setParent(this);
                    label.forElementId = radioInput.id;
                    label.hostConfig = this.hostConfig;
                    label.text = Utils.isNullOrEmpty(choice.title) ? "Choice " + (i++) : choice.title;
                    label.useMarkdown = Shared.GlobalSettings.useMarkdownInRadioButtonAndCheckbox;
                    label.wrap = this.wrap;

                    let labelElement = label.render();
                    
                    if (labelElement) {
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
        }
        else {
            // Render as a list of toggle inputs
            let defaultValues = this.defaultValue ? this.defaultValue.split(this.hostConfig.choiceSetInputValueSeparator) : undefined;

            let element = document.createElement("div");
            element.className = this.hostConfig.makeCssClassName("ac-input", "ac-choiceSetInput-multiSelect");
            element.style.width = "100%";

            this._toggleInputs = [];

            let i = 0;

            for (let choice of this.choices) {
                let checkboxInput = document.createElement("input");
                checkboxInput.id = Utils.generateUniqueId();
                checkboxInput.type = "checkbox";
                checkboxInput.style.margin = "0";
                checkboxInput.style.display = "inline-block";
                checkboxInput.style.verticalAlign = "middle";
                checkboxInput.value = <string>choice.value;
                checkboxInput.style.flex = "0 0 auto";
                checkboxInput.setAttribute("aria-label", <string>choice.title);

                if (defaultValues) {
                    if (defaultValues.indexOf(<string>choice.value) >= 0) {
                        checkboxInput.checked = true;
                    }
                }

                checkboxInput.onchange = () => { this.valueChanged(); }

                this._toggleInputs.push(checkboxInput);

                let compoundInput = document.createElement("div");
                compoundInput.style.display = "flex";
                compoundInput.style.alignItems = "center";

                Utils.appendChild(compoundInput, checkboxInput);

                let label = new Label();
                label.setParent(this);
                label.forElementId = checkboxInput.id;
                label.hostConfig = this.hostConfig;
                label.text = Utils.isNullOrEmpty(choice.title) ? "Choice " + (i++) : choice.title;
                label.useMarkdown = Shared.GlobalSettings.useMarkdownInRadioButtonAndCheckbox;
                label.wrap = this.wrap;

                let labelElement = label.render();

                if (labelElement) {
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
    }

    choices: Choice[] = [];
    isCompact: boolean = false;
    isMultiSelect: boolean = false;
    placeholder: string;
    wrap: boolean = false;

    getJsonTypeName(): string {
        return "Input.ChoiceSet";
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "placeholder", this.placeholder);
        Utils.setArrayProperty(result, "choices", this.choices);
        Utils.setProperty(result, "style", this.isCompact ? undefined : "expanded");
        Utils.setProperty(result, "isMultiSelect", this.isMultiSelect, false);
        Utils.setProperty(result, "wrap", this.wrap, false);

        return result;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (this.choices.length == 0) {
            context.addFailure(
                this,
                {
                    error: Enums.ValidationError.CollectionCantBeEmpty,
                    message: "An Input.ChoiceSet must have at least one choice defined."
                });
        }

        for (let choice of this.choices) {
            if (!choice.title || !choice.value) {
                context.addFailure(
                    this,
                    {
                        error: Enums.ValidationError.PropertyCantBeNull,
                        message: "All choices in an Input.ChoiceSet must have their title and value properties set."
                    });
            }
        }
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.isCompact = !(json["style"] === "expanded");
        this.isMultiSelect = <boolean>Utils.getBoolValue(json["isMultiSelect"], this.isMultiSelect);
        this.placeholder = Utils.getStringValue(json["placeholder"]);

        this.choices = [];

        if (Array.isArray(json["choices"])) {
            for (let jsonChoice of json["choices"]) {
                let choice = new Choice();
                choice.parse(jsonChoice);

                this.choices.push(choice);
            }
        }

        this.wrap = <boolean>Utils.getBoolValue(json["wrap"], this.wrap);
    }

    get value(): string | undefined {
        if (!this.isMultiSelect) {
            if (this.isCompact) {
                if (this._selectElement) {
                    return this._selectElement.selectedIndex > 0 ? this._selectElement.value : undefined;
                }

                return undefined;
            }
            else {
                if (!this._toggleInputs || this._toggleInputs.length == 0) {
                    return undefined;
                }

                for (let toggleInput of this._toggleInputs) {
                    if (toggleInput.checked) {
                        return toggleInput.value;
                    }
                }

                return undefined;
            }
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

            return Utils.isNullOrEmpty(result) ? undefined : result;
        }
    }
}

export class NumberInput extends Input {
    private _numberInputElement: HTMLInputElement;
    private _min?: number;
    private _max?: number;

    protected internalRender(): HTMLElement | undefined {
        this._numberInputElement = document.createElement("input");
        this._numberInputElement.setAttribute("type", "number");

        if (this.min) {
            this._numberInputElement.setAttribute("min", this.min.toString());
        }

        if (this.max) {
            this._numberInputElement.setAttribute("max", this.max.toString());
        }

        this._numberInputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-numberInput");
        this._numberInputElement.style.width = "100%";
        this._numberInputElement.tabIndex = 0;

        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._numberInputElement.value = <string>this.defaultValue;
        }

        if (!Utils.isNullOrEmpty(this.placeholder)) {
            this._numberInputElement.placeholder = this.placeholder;
            this._numberInputElement.setAttribute("aria-label", this.placeholder);
        }

        this._numberInputElement.oninput = () => { this.valueChanged(); }

        return this._numberInputElement;
    }

    placeholder: string;

    getJsonTypeName(): string {
        return "Input.Number";
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "placeholder", this.placeholder);
        Utils.setNumberProperty(result, "min", this.min);
        Utils.setNumberProperty(result, "max", this.max);

        return result;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.placeholder = Utils.getStringValue(json["placeholder"]);
        this.min = Utils.getNumberValue(json["min"]);
        this.max = Utils.getNumberValue(json["max"]);
    }

    get min(): number | undefined {
        return this._min;
    }

    set min(value: number | undefined) {
        this._min = value;
    }

    get max(): number | undefined {
        return this._max;
    }

    set max(value: number | undefined) {
        this._max = value;
    }

    get value(): string | undefined {
        return this._numberInputElement ? this._numberInputElement.value : undefined;
    }

    get valueAsNumber(): number | undefined {
        return this._numberInputElement ? this._numberInputElement.valueAsNumber : undefined;
    }
}

export class DateInput extends Input {
    private _dateInputElement: HTMLInputElement;
    private _min?: string;
    private _max?: string;

    protected internalRender(): HTMLElement | undefined {
        this._dateInputElement = document.createElement("input");
        this._dateInputElement.setAttribute("type", "date");
        this._dateInputElement.setAttribute("min", <string>this.min);
        this._dateInputElement.setAttribute("max", <string>this.max);
        this._dateInputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-dateInput");
        this._dateInputElement.style.width = "100%";

        this._dateInputElement.oninput = () => { this.valueChanged(); }

        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._dateInputElement.value = <string>this.defaultValue;
        }

        return this._dateInputElement;
    }

    getJsonTypeName(): string {
        return "Input.Date";
    }

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "min", this.min);
        Utils.setProperty(result, "max", this.max);

        return result;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.min = Utils.getStringValue(json["min"]);
        this.max = Utils.getStringValue(json["max"]);
    }

    get min(): string | undefined {
        return this._min;
    }

    set min(value: string | undefined) {
        this._min = this.parseInputValue(value);
    }

    get max(): string | undefined {
        return this._max;
    }

    set max(value: string | undefined) {
        this._max = this.parseInputValue(value);
    }

    get value(): string | undefined {
        return this._dateInputElement ? this._dateInputElement.value : undefined;
    }
}

export class TimeInput extends Input {
    private _timeInputElement: HTMLInputElement;
    private _min?: string;
    private _max?: string;

    protected internalRender(): HTMLElement | undefined {
        this._timeInputElement = document.createElement("input");
        this._timeInputElement.setAttribute("type", "time");
        this._timeInputElement.setAttribute("min", <string>this.min);
        this._timeInputElement.setAttribute("max", <string>this.max);
        this._timeInputElement.className = this.hostConfig.makeCssClassName("ac-input", "ac-timeInput");
        this._timeInputElement.style.width = "100%";
        this._timeInputElement.oninput = () => { this.valueChanged(); }

        if (!Utils.isNullOrEmpty(this.defaultValue)) {
            this._timeInputElement.value = <string>this.defaultValue;
        }

        return this._timeInputElement;
    }

    protected parseInputValue(value: string | undefined): string | undefined {
        if (!Utils.isNullOrEmpty(value) && /^[0-9]{2}:[0-9]{2}$/.test(<string>value)) {
            return value;
        }
        else {
            return undefined;
        }
    }

    getJsonTypeName(): string {
        return "Input.Time";
    }

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "min", this.min);
        Utils.setProperty(result, "max", this.max);

        return result;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.min = Utils.getStringValue(json["min"]);
        this.max = Utils.getStringValue(json["max"]);
    }

    get min(): string | undefined {
        return this._min;
    }

    set min(value: string | undefined) {
        this._min = this.parseInputValue(value);
    }

    get max(): string | undefined {
        return this._max;
    }

    set max(value: string | undefined) {
        this._max = this.parseInputValue(value);
    }

    get value(): string | undefined {
        return this._timeInputElement ? this._timeInputElement.value : undefined;
    }
}

enum ActionButtonState {
    Normal,
    Expanded,
    Subdued
}

class ActionButton {
    private _parentContainerStyle: string;
    private _state: ActionButtonState = ActionButtonState.Normal;

    private updateCssStyle() {
        if (this.action.parent && this.action.renderedElement) {
            let hostConfig = this.action.parent.hostConfig;

            this.action.renderedElement.className = hostConfig.makeCssClassName("ac-pushButton");

            if (!Utils.isNullOrEmpty(this._parentContainerStyle)) {
                this.action.renderedElement.classList.add("style-" + this._parentContainerStyle);
            }

            /*
            if (this.action instanceof ShowCardAction) {
                this.action.renderedElement.classList.add(hostConfig.makeCssClassName("expandable"));
            }
            */

            this.action.updateActionButtonCssStyle(this.action.renderedElement);

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

            if (!Utils.isNullOrEmpty(this.action.style)) {
                if (this.action.style === Enums.ActionStyle.Positive) {
                    this.action.renderedElement.classList.add(...hostConfig.makeCssClassNames("primary", "style-positive"));
                }
                else {
                    this.action.renderedElement.classList.add(...hostConfig.makeCssClassNames("style-" + this.action.style.toLowerCase()));
                }
            }
        }
    }

    readonly action: Action;

    constructor(action: Action, parentContainerStyle: string) {
        this.action = action;
        this._parentContainerStyle = parentContainerStyle;
    }

    onClick?: (actionButton: ActionButton) => void;

    render() {
        this.action.render();

        if (this.action.renderedElement) {
            this.action.renderedElement.onclick = (e) => {
                e.preventDefault();
                e.cancelBubble = true;

                this.click();
            };

            this.updateCssStyle();
        }
    }

    click() {
        if (this.onClick !== undefined) {
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

export abstract class Action extends CardObject {
    private _shouldFallback: boolean = false;
    private _parent?: CardElement;
    private _actionCollection?: ActionCollection; // hold the reference to its action collection
    private _renderedElement?: HTMLElement;

    private setCollection(actionCollection: ActionCollection) {
        this._actionCollection = actionCollection;
    }

    protected addCssClasses(element: HTMLElement) {
        // Do nothing in base implementation
    }

    protected internalGetReferencedInputs(allInputs: Input[]): Shared.Dictionary<Input> {
        return {};
    }

    protected internalPrepareForExecution(inputs: Shared.Dictionary<Input> | undefined) {
        // Do nothing in base implementation
    }

    protected internalValidateInputs(referencedInputs: Shared.Dictionary<Input> | undefined): Input[] {
        let result: Input[] = [];

        if (Shared.GlobalSettings.useBuiltInInputValidation && !this.ignoreInputValidation && referencedInputs) {
            for (let key of Object.keys(referencedInputs)) {
                let input = referencedInputs[key];

                if (!input.validateValue()) {
                    result.push(input);
                }
            }
        }

        return result;
    }

    abstract getJsonTypeName(): string;

    readonly requires = new HostCapabilities();

    title: string;
    iconUrl: string;
    style: string = Enums.ActionStyle.Default;

    onExecute: (sender: Action) => void;

    getHref(): string {
        return "";
    }

    toJSON(): any {
		let result = super.toJSON();

        Utils.setProperty(result, "type", this.getJsonTypeName());
        Utils.setProperty(result, "title", this.title);
        Utils.setProperty(result, "iconUrl", this.iconUrl);
        Utils.setProperty(result, "style", this.style, Enums.ActionStyle.Default);

        return result;
    }

    updateActionButtonCssStyle(actionButtonElement: HTMLElement): void {
        // Do nothing in base implementation
    }

    render(baseCssClass: string = "ac-pushButton") {
        // Cache hostConfig for perf
        let hostConfig = this.hostConfig;

        let buttonElement = document.createElement("button");

        this.addCssClasses(buttonElement);

        buttonElement.setAttribute("aria-label", this.title);
        buttonElement.type = "button";
        buttonElement.style.display = "flex";
        buttonElement.style.alignItems = "center";
        buttonElement.style.justifyContent = "center";

        let hasTitle = !Utils.isNullOrEmpty(this.title);

        let titleElement = document.createElement("div");
        titleElement.style.overflow = "hidden";
        titleElement.style.textOverflow = "ellipsis";

        if (!(hostConfig.actions.iconPlacement == Enums.ActionIconPlacement.AboveTitle || hostConfig.actions.allowTitleToWrap)) {
            titleElement.style.whiteSpace = "nowrap";
        }

        if (hasTitle) {
            titleElement.innerText = this.title;
        }

        if (Utils.isNullOrEmpty(this.iconUrl)) {
            buttonElement.classList.add("noIcon");

            buttonElement.appendChild(titleElement);
        }
        else {
            let iconElement = document.createElement("img");
            iconElement.src = this.iconUrl;
            iconElement.style.width = hostConfig.actions.iconSize + "px";
            iconElement.style.height = hostConfig.actions.iconSize + "px";
            iconElement.style.flex = "0 0 auto";

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

    setParent(value: CardElement | undefined) {
        this._parent = value;
    }

    execute() {
        if (this.onExecute) {
            this.onExecute(this);
        }

        raiseExecuteActionEvent(this);
    }

    prepareForExecution(): boolean {
        let referencedInputs = this.getReferencedInputs();

        if (this.internalValidateInputs(referencedInputs).length > 0) {
            return false;
        }

        this.internalPrepareForExecution(referencedInputs);

        return true;
    };

    parse(json: any, errors?: Shared.IValidationError[]) {
		super.parse(json, errors);

        raiseParseActionEvent(this, json, errors);

        this.requires.parse(json["requires"], errors);

        if (!json["title"] && json["title"] !== "") {
            raiseParseError(
                {
                    error: Enums.ValidationError.PropertyCantBeNull,
                    message: "Actions should always have a title."
                },
                errors
            );
        }

        this.title = Utils.getStringValue(json["title"]);
        this.iconUrl = Utils.getStringValue(json["iconUrl"]);
        this.style = Utils.getStringValue(json["style"], this.style);
    }

    remove(): boolean {
        if (this._actionCollection) {
            return this._actionCollection.removeAction(this);
        }

        return false;
    }

    getAllInputs(): Input[] {
        return [];
    }

    getResourceInformation(): Shared.IResourceInformation[] {
        if (!Utils.isNullOrEmpty(this.iconUrl)) {
            return [{ url: this.iconUrl, mimeType: "image" }]
        }
        else {
            return [];
        }
    }

    getActionById(id: string): Action | undefined {
        if (this.id == id) {
            return this;
        }
        else {
            return undefined;
        }
    }

    getReferencedInputs(): Shared.Dictionary<Input> | undefined {
        return this.parent ? this.internalGetReferencedInputs(this.parent.getRootElement().getAllInputs()) : undefined;
    }

    validateInputs() {
        return this.internalValidateInputs(this.getReferencedInputs());
    }

    shouldFallback(): boolean {
        return this._shouldFallback || !this.requires.areAllMet(this.hostConfig.hostCapabilities);
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

    get ignoreInputValidation(): boolean {
        return true;
    }

    get parent(): CardElement | undefined {
        return this._parent;
    }

    get renderedElement(): HTMLElement | undefined {
        return this._renderedElement;
    }

    get hostConfig(): HostConfig.HostConfig {
        return this.parent ? this.parent.hostConfig : defaultHostConfig;
    }
}

export class SubmitAction extends Action {
    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.Submit" = "Action.Submit";

    private _isPrepared: boolean = false;
    private _originalData?: object;
    private _processedData?: { [key: string]: any };
    private _ignoreInputValidation: boolean = false;

    protected internalGetReferencedInputs(allInputs: Input[]): Shared.Dictionary<Input> {
        let result: Shared.Dictionary<Input> = {};

        for (let input of allInputs) {
            result[input.id] = input;
        }

        return result;
    }

    protected internalPrepareForExecution(inputs: Shared.Dictionary<Input>) {
        if (this._originalData) {
            this._processedData = JSON.parse(JSON.stringify(this._originalData));
        }
        else {
            this._processedData = {};
        }

        if (this._processedData) {
            for (let key of Object.keys(inputs)) {
                let input = inputs[key];

                if (input.value !== undefined) {
                    this._processedData[input.id] = input.value;
                }
            }
        }

        this._isPrepared = true;
    }

    getJsonTypeName(): string {
        return SubmitAction.JsonTypeName;
    }

    toJSON() {
        let result = super.toJSON();

        Utils.setProperty(result, "ignoreInputValidation", this.ignoreInputValidation, false);
        Utils.setProperty(result, "data", this._originalData);

        return result;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this._ignoreInputValidation = <boolean>Utils.getBoolValue(json["ignoreInputValidation"], this._ignoreInputValidation);
        this.data = json["data"];
    }

    get ignoreInputValidation(): boolean {
        return this._ignoreInputValidation;
    }

    set ignoreInputValidation(value: boolean) {
        this._ignoreInputValidation = value;
    }

    get data(): object | undefined {
        return this._isPrepared ? this._processedData : this._originalData;
    }

    set data(value: object | undefined) {
        this._originalData = value;
        this._isPrepared = false;
    }
}

export class OpenUrlAction extends Action {
    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.OpenUrl" = "Action.OpenUrl";

    url: string;

    getJsonTypeName(): string {
        return OpenUrlAction.JsonTypeName;
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "url", this.url);

        return result;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (Utils.isNullOrEmpty(this.url)) {
            context.addFailure(
                this,
                {
                    error: Enums.ValidationError.PropertyCantBeNull,
                    message: "An Action.OpenUrl must have its url property set."
                });
        }
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.url = Utils.getStringValue(json["url"]);
    }

    getHref(): string {
        return this.url;
    }
}

export class ToggleVisibilityAction extends Action {
    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.ToggleVisibility" = "Action.ToggleVisibility";

    targetElements: { [key: string]: any } = {};

    getJsonTypeName(): string {
        return ToggleVisibilityAction.JsonTypeName;
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

    parse(json: any) {
        super.parse(json);

        this.targetElements = {};

        let jsonTargetElements = json["targetElements"];

        if (jsonTargetElements && Array.isArray(jsonTargetElements)) {
            for (let item of jsonTargetElements) {
                if (typeof item === "string") {
                    this.targetElements[item] = undefined;
                }
                else if (typeof item === "object") {
                    let jsonElementId = item["elementId"];

                    if (jsonElementId && typeof jsonElementId === "string") {
                        this.targetElements[jsonElementId] = Utils.getBoolValue(item["isVisible"], undefined);
                    }
                }
            }
        }
    }

    toJSON() {
        let result = super.toJSON();

        let targetElements: any[] = [];

        for (let id of Object.keys(this.targetElements)) {
            if (typeof this.targetElements[id] === "boolean") {
                targetElements.push(
                    {
                        elementId: id,
                        isVisible: this.targetElements[id]
                    }
                );
            }
            else {
                targetElements.push(id);
            }
        }

        result["targetElements"] = targetElements;

        return result;
    }

    addTargetElement(elementId: string, isVisible: boolean | undefined = undefined) {
        this.targetElements[elementId] = isVisible;
    }

    removeTargetElement(elementId: string) {
        delete this.targetElements[elementId];
    }
}

export class HttpHeader extends Serialization.SerializableObject {
    private _value = new Shared.StringWithSubstitutions();

    name: string;

    constructor(name: string = "", value: string = "") {
        super();

        this.name = name;
        this.value = value;
    }

    parse(json: any) {
        super.parse(json);

        this.name = Utils.getStringValue(json["name"]);
        this.value = Utils.getStringValue(json["value"]);
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "name", this.name);
        Utils.setProperty(result, "value", this._value.getOriginal());

        return result;
    }

    getReferencedInputs(inputs: Input[], referencedInputs: Shared.Dictionary<Input>) {
        this._value.getReferencedInputs(inputs, referencedInputs);
    }

    prepareForExecution(inputs: Shared.Dictionary<Input>) {
        this._value.substituteInputValues(inputs, Shared.ContentTypes.applicationXWwwFormUrlencoded);
    }

    get value(): string | undefined {
        return this._value.get();
    }

    set value(newValue: string | undefined) {
        this._value.set(newValue);
    }
}

export class HttpAction extends Action {
    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.Http" = "Action.Http";

    private _url = new Shared.StringWithSubstitutions();
    private _body = new Shared.StringWithSubstitutions();
    private _headers: HttpHeader[] = [];
    private _ignoreInputValidation: boolean = false;

    protected internalGetReferencedInputs(allInputs: Input[]): Shared.Dictionary<Input> {
        let result: Shared.Dictionary<Input> = {};

        this._url.getReferencedInputs(allInputs, result);

        for (let header of this._headers) {
            header.getReferencedInputs(allInputs, result);
        }

        this._body.getReferencedInputs(allInputs, result);

        return result;
    }

    protected internalPrepareForExecution(inputs: Shared.Dictionary<Input>) {
        this._url.substituteInputValues(inputs, Shared.ContentTypes.applicationXWwwFormUrlencoded);

        let contentType = Shared.ContentTypes.applicationJson;

        for (let header of this._headers) {
            header.prepareForExecution(inputs);

            if (!Utils.isNullOrEmpty(header.name) && header.name.toLowerCase() == "content-type") {
                contentType = <string>header.value;
            }
        }

        this._body.substituteInputValues(inputs, contentType);
    };

    method: string;

    getJsonTypeName(): string {
        return HttpAction.JsonTypeName;
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "method", this.method);
        Utils.setProperty(result, "url", this._url.getOriginal());
        Utils.setProperty(result, "body", this._body.getOriginal());
        Utils.setProperty(result, "ignoreInputValidation", this.ignoreInputValidation, false);
        Utils.setArrayProperty(result, "headers", this.headers);

        return result;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (Utils.isNullOrEmpty(this.url)) {
            context.addFailure(
                this,
                {
                    error: Enums.ValidationError.PropertyCantBeNull,
                    message: "An Action.Http must have its url property set."
                });
        }

        if (this.headers.length > 0) {
            for (let header of this.headers) {
                if (!header.name) {
                    context.addFailure(
                        this,
                        {
                            error: Enums.ValidationError.PropertyCantBeNull,
                            message: "All headers of an Action.Http must have their name and value properties set."
                        });
                }
            }
        }
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.url = Utils.getStringValue(json["url"]);
        this.method = Utils.getStringValue(json["method"]);
        this.body = Utils.getStringValue(json["body"]);
        this._ignoreInputValidation = <boolean>Utils.getBoolValue(json["ignoreInputValidation"], this._ignoreInputValidation);

        this._headers = [];

        if (Array.isArray(json["headers"])) {
            for (let jsonHeader of json["headers"]) {
                let httpHeader = new HttpHeader();
                httpHeader.parse(jsonHeader);

                this.headers.push(httpHeader);
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

    get headers(): HttpHeader[] {
        return this._headers ? this._headers : [];
    }

    set headers(value: HttpHeader[]) {
        this._headers = value;
    }
}

export class ShowCardAction extends Action {
    // Note the "weird" way this field is declared is to work around a breaking
    // change introduced in TS 3.1 wrt d.ts generation. DO NOT CHANGE
    static readonly JsonTypeName: "Action.ShowCard" = "Action.ShowCard";

    protected addCssClasses(element: HTMLElement) {
        super.addCssClasses(element);

        if (this.parent) {
            element.classList.add(this.parent.hostConfig.makeCssClassName("expandable"));
        }
    }

    readonly card: AdaptiveCard = new InlineAdaptiveCard();

    getJsonTypeName(): string {
        return ShowCardAction.JsonTypeName;
    }

    toJSON(): any {
        let result = super.toJSON();

        if (this.card) {
            Utils.setProperty(result, "card", this.card.toJSON());
        }

        return result;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        this.card.internalValidateProperties(context);
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        let jsonCard = json["card"];

        if (jsonCard) {
            this.card.parse(jsonCard, errors);
        }
        else {
            raiseParseError(
                {
                    error: Enums.ValidationError.PropertyCantBeNull,
                    message: "An Action.ShowCard must have its \"card\" property set to a valid AdaptiveCard object."
                },
                errors
            );
        }
    }

    updateActionButtonCssStyle(actionButtonElement: HTMLElement): void {
        super.updateActionButtonCssStyle(actionButtonElement);

        if (this.parent) {
            actionButtonElement.classList.add(this.parent.hostConfig.makeCssClassName("expandable"));
        }
    }

    setParent(value: CardElement) {
        super.setParent(value);

        this.card.setParent(value);
    }

    getAllInputs(): Input[] {
        return this.card.getAllInputs();
    }

    getResourceInformation(): Shared.IResourceInformation[] {
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

class ActionCollection {
    private _owner: CardElement;
    private _actionCardContainer: HTMLDivElement;
    private _expandedAction?: ShowCardAction;
    private _renderedActionCount: number = 0;
    private _actionCard?: HTMLElement;

    private refreshContainer() {
        this._actionCardContainer.innerHTML = "";

        if (!this._actionCard) {
            this._actionCardContainer.style.marginTop = "0px";

            return;
        }

        this._actionCardContainer.style.marginTop = this._renderedActionCount > 0 ? this._owner.hostConfig.actions.showCard.inlineTopMargin + "px" : "0px";

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

    private hideActionCard() {
        let previouslyExpandedAction = this._expandedAction;

        this._expandedAction = undefined;
        this._actionCard = undefined;

        this.refreshContainer();

        if (previouslyExpandedAction) {
            this.layoutChanged();

            raiseInlineCardExpandedEvent(previouslyExpandedAction, false);
        }
    }

    private showActionCard(action: ShowCardAction, suppressStyle: boolean = false, raiseEvent: boolean = true) {
        (<InlineAdaptiveCard>action.card).suppressStyle = suppressStyle;

        let renderedCard = action.card.render();

        this._actionCard = renderedCard;
        this._expandedAction = action;

        this.refreshContainer();

        if (raiseEvent) {
            this.layoutChanged();

            raiseInlineCardExpandedEvent(action, true);
        }
    }

    private collapseExpandedAction() {
        for (let button of this.buttons) {
            button.state = ActionButtonState.Normal;
        }

        this.hideActionCard();
    }

    private expandShowCardAction(action: ShowCardAction, raiseEvent: boolean) {
        for (let button of this.buttons) {
            if (button.action !== action) {
                button.state = ActionButtonState.Subdued;
            }
            else {
                button.state = ActionButtonState.Expanded;
            }
        }

        this.showActionCard(
            action,
            !(this._owner.isAtTheVeryLeft() && this._owner.isAtTheVeryRight()),
            raiseEvent);
    }

    private actionClicked(actionButton: ActionButton) {
        if (!(actionButton.action instanceof ShowCardAction)) {
            for (let button of this.buttons) {
                button.state = ActionButtonState.Normal;
            }

            this.hideActionCard();

            actionButton.action.execute();
        }
        else {
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

    private getParentContainer(): Container | undefined {
        if (this._owner instanceof Container) {
            return this._owner;
        }
        else {
            return this._owner.getParentContainer();
        }
    }

    private findActionButton(action: Action): ActionButton | undefined {
        for (let actionButton of this.buttons) {
            if (actionButton.action == action) {
                return actionButton;
            }
        }

        return undefined;
    }

    items: Action[] = [];
    buttons: ActionButton[] = [];

    constructor(owner: CardElement) {
        this._owner = owner;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        this.clear();

        if (json && json instanceof Array) {
            for (let jsonAction of json) {
                let action = createActionInstance(
                    this._owner,
                    jsonAction,
                    [],
                    !this._owner.isDesignMode(),
                    errors);

                if (action) {
                    this.addAction(action);
                }
            }
        }
    }

    toJSON(): any {
        if (this.items.length > 0) {
            let result = [];

            for (let action of this.items) {
                result.push(action.toJSON());
            }

            return result;
        }
        else {
            return undefined;
        }
    }

    getActionById(id: string): Action | undefined {
        let result: Action | undefined = undefined;

        for (let item of this.items) {
            result = item.getActionById(id);

            if (result) {
                break;
            }
        }

        return result;
    }

    validateProperties(context: ValidationResults) {
        if (this._owner.hostConfig.actions.maxActions && this.items.length > this._owner.hostConfig.actions.maxActions) {
            context.addFailure(
                this._owner,
                {
                    error: Enums.ValidationError.TooManyActions,
                    message: "A maximum of " + this._owner.hostConfig.actions.maxActions + " actions are allowed."
                });
        }

        if (this.items.length > 0 && !this._owner.hostConfig.supportsInteractivity) {
            context.addFailure(
                this._owner,
                {
                    error: Enums.ValidationError.InteractivityNotAllowed,
                    message: "Interactivity is not allowed."
                });
        }

        for (let item of this.items) {
            if (!isActionAllowed(item, this._owner.getForbiddenActionTypes())) {
                context.addFailure(
                    this._owner,
                    {
                        error: Enums.ValidationError.ActionTypeNotAllowed,
                        message: "Actions of type " + item.getJsonTypeName() + " are not allowe."
                    });
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
        let maxActions = hostConfig.actions.maxActions ? Math.min(hostConfig.actions.maxActions, this.items.length) : this.items.length;
        let forbiddenActionTypes = this._owner.getForbiddenActionTypes();

        this._actionCardContainer = document.createElement("div");
        this._renderedActionCount = 0;

        if (hostConfig.actions.preExpandSingleShowCardAction && maxActions == 1 && this.items[0] instanceof ShowCardAction && isActionAllowed(this.items[0], forbiddenActionTypes)) {
            this.showActionCard(<ShowCardAction>this.items[0], true);
            this._renderedActionCount = 1;
        }
        else {
            let buttonStrip = document.createElement("div");
            buttonStrip.className = hostConfig.makeCssClassName("ac-actionSet");
            buttonStrip.style.display = "flex";

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

            let parentContainer = this.getParentContainer();

            if (parentContainer) {
                let parentContainerStyle = parentContainer.getEffectiveStyle();

                for (let i = 0; i < this.items.length; i++) {
                    if (isActionAllowed(this.items[i], forbiddenActionTypes)) {
                        let actionButton = this.findActionButton(this.items[i]);

                        if (!actionButton) {
                            actionButton = new ActionButton(this.items[i], parentContainerStyle);
                            actionButton.onClick = (ab) => { this.actionClicked(ab); };

                            this.buttons.push(actionButton);
                        }

                        actionButton.render();

                        if (actionButton.action.renderedElement) {
                            if (hostConfig.actions.actionsOrientation == Enums.Orientation.Horizontal && hostConfig.actions.actionAlignment == Enums.ActionAlignment.Stretch) {
                                actionButton.action.renderedElement.style.flex = "0 1 100%";
                            }
                            else {
                                actionButton.action.renderedElement.style.flex = "0 1 auto";
                            }

                            buttonStrip.appendChild(actionButton.action.renderedElement);

                            this._renderedActionCount++;

                            if (this._renderedActionCount >= hostConfig.actions.maxActions || i == this.items.length - 1) {
                                break;
                            }
                            else if (hostConfig.actions.buttonSpacing > 0) {
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
                }
            }

            let buttonStripContainer = document.createElement("div");
            buttonStripContainer.style.overflow = "hidden";
            buttonStripContainer.appendChild(buttonStrip);

            Utils.appendChild(element, buttonStripContainer);
        }

        Utils.appendChild(element, this._actionCardContainer);

        for (let button of this.buttons) {
            if (button.state == ActionButtonState.Expanded) {
                this.expandShowCardAction(<ShowCardAction>button.action, false);

                break;
            }
        }

        return this._renderedActionCount > 0 ? element : undefined;
    }

    addAction(action: Action) {
        if (!action) {
            throw new Error("The action parameter cannot be null.");
        }

        if ((!action.parent || action.parent === this._owner) && this.items.indexOf(action) < 0) {
            this.items.push(action);

            if (!action.parent) {
                action.setParent(this._owner);
            }

            invokeSetCollection(action, this);
        }
        else {
            throw new Error("The action already belongs to another element.");
        }
    }

    removeAction(action: Action): boolean {
        if (this.expandedAction && this._expandedAction == action) {
            this.collapseExpandedAction();
        }

        let actionIndex = this.items.indexOf(action);

        if (actionIndex >= 0) {
            this.items.splice(actionIndex, 1);

            action.setParent(undefined);

            invokeSetCollection(action, undefined);

            for (let i = 0; i < this.buttons.length; i++) {
                if (this.buttons[i].action == action) {
                    this.buttons.splice(i, 1);

                    break;
                }
            }

            return true;
        }

        return false;
    }

    clear() {
        this.items = [];
        this.buttons = [];

        this._expandedAction = undefined;
        this._renderedActionCount = 0;
    }

    getAllInputs(): Input[] {
        let result: Input[] = [];

        for (let action of this.items) {
            result = result.concat(action.getAllInputs());
        }

        return result;
    }

    getResourceInformation(): Shared.IResourceInformation[] {
        let result: Shared.IResourceInformation[] = [];

        for (let action of this.items) {
            result = result.concat(action.getResourceInformation());
        }

        return result;
    }

    get renderedActionCount(): number {
        return this._renderedActionCount;
    }

    get expandedAction(): ShowCardAction | undefined {
        return this._expandedAction;
    }
}

export class ActionSet extends CardElement {
    private _actionCollection: ActionCollection;

    protected internalRender(): HTMLElement | undefined {
        return this._actionCollection.render(this.orientation ? this.orientation : this.hostConfig.actions.actionsOrientation, this.isDesignMode());
    }

    orientation?: Enums.Orientation;

    constructor() {
        super();

        this._actionCollection = new ActionCollection(this);
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setEnumProperty(Enums.Orientation, result, "orientation", this.orientation);
        Utils.setProperty(result, "actions", this._actionCollection.toJSON());

        return result;
    }

    isBleedingAtBottom(): boolean {
        if (this._actionCollection.renderedActionCount == 0) {
            return super.isBleedingAtBottom();
        }
        else {
            if (this._actionCollection.items.length == 1) {
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
        return this._actionCollection.items.length;
    }

    getActionAt(index: number): Action | undefined {
        if (index >= 0 && index < this.getActionCount()) {
            return this._actionCollection.items[index];
        }
        else {
            return super.getActionAt(index);
        }
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        this._actionCollection.validateProperties(context);
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        let jsonOrientation = json["orientation"];

        if (jsonOrientation) {
            this.orientation = Utils.getEnumValue(Enums.Orientation, jsonOrientation, Enums.Orientation.Horizontal);
        }

        this._actionCollection.parse(json["actions"], errors);
    }

    addAction(action: Action) {
        this._actionCollection.addAction(action);
    }

    getAllInputs(): Input[] {
        return this._actionCollection.getAllInputs();
    }

    getResourceInformation(): Shared.IResourceInformation[] {
        return this._actionCollection.getResourceInformation();
    }

    get isInteractive(): boolean {
        return true;
    }
}

export abstract class StylableCardElementContainer extends CardElementContainer {
    private _style?: string;
    private _bleed: boolean = false;

    protected applyBackground() {
        if (this.renderedElement) {
            let styleDefinition = this.hostConfig.containerStyles.getStyleByName(this.style, this.hostConfig.containerStyles.getStyleByName(this.defaultStyle));

            if (!Utils.isNullOrEmpty(styleDefinition.backgroundColor)) {
                this.renderedElement.style.backgroundColor = <string>Utils.stringToCssColor(styleDefinition.backgroundColor);
            }
        }
    }

    protected applyPadding() {
        super.applyPadding();

        if (!this.renderedElement) {
            return;
        }

        let physicalPadding = new Shared.SpacingDefinition();

        if (this.getEffectivePadding()) {
            physicalPadding = this.hostConfig.paddingDefinitionToSpacingDefinition(this.getEffectivePadding());
        }

        this.renderedElement.style.paddingTop = physicalPadding.top + "px";
        this.renderedElement.style.paddingRight = physicalPadding.right + "px";
        this.renderedElement.style.paddingBottom = physicalPadding.bottom + "px";
        this.renderedElement.style.paddingLeft = physicalPadding.left + "px";

        if (this.isBleeding()) {
            // Bleed into the first parent that does have padding
            let padding = new Shared.PaddingDefinition();

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

            if (this.separatorElement) {
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

    protected getDefaultPadding(): Shared.PaddingDefinition {
        return this.getHasBackground() ?
            new Shared.PaddingDefinition(
                Enums.Spacing.Padding,
                Enums.Spacing.Padding,
                Enums.Spacing.Padding,
                Enums.Spacing.Padding) : super.getDefaultPadding();
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

    protected get hasExplicitStyle(): boolean {
        return this._style !== undefined;
    }

    protected get allowCustomStyle(): boolean {
        return true;
    }

    protected get supportsMinHeight(): boolean {
        return true;
    }

    isBleeding(): boolean {
		return (this.getHasBackground() || this.hostConfig.alwaysAllowBleed) && this.getBleed();
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "style", this.style);

        return result;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (this._style) {
            let styleDefinition = this.hostConfig.containerStyles.getStyleByName(this._style);

            if (!styleDefinition) {
                context.addFailure(
                    this,
                    {
                        error: Enums.ValidationError.InvalidPropertyValue,
                        message: "Unknown container style: " + this._style
                    });
            }
        }
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this._style = Utils.getStringValue(json["style"]);
    }

    render(): HTMLElement | undefined {
        let renderedElement = super.render();

        if (renderedElement && this.getHasBackground()) {
            this.applyBackground();
        }

        return renderedElement;
    }

    getEffectiveStyle(): string {
        let effectiveStyle = this.style;

        return effectiveStyle ? effectiveStyle : super.getEffectiveStyle();
    }

    get style(): string | undefined {
        if (this.allowCustomStyle) {
            if (this._style && this.hostConfig.containerStyles.getStyleByName(this._style)) {
                return this._style;
            }
        }

        return undefined;
    }

    set style(value: string | undefined) {
        this._style = value;
    }
}

export class BackgroundImage extends Serialization.SerializableObject {
    private static readonly defaultFillMode = Enums.FillMode.Cover;
    private static readonly defaultHorizontalAlignment = Enums.HorizontalAlignment.Left;
    private static readonly defaultVerticalAlignment = Enums.VerticalAlignment.Top;

    url?: string;
    fillMode: Enums.FillMode = BackgroundImage.defaultFillMode;
    horizontalAlignment: Enums.HorizontalAlignment = BackgroundImage.defaultHorizontalAlignment;
    verticalAlignment: Enums.VerticalAlignment = BackgroundImage.defaultVerticalAlignment;

    reset(): void {
        this.url = undefined;
        this.fillMode = BackgroundImage.defaultFillMode;
        this.horizontalAlignment = BackgroundImage.defaultHorizontalAlignment;
        this.verticalAlignment = BackgroundImage.defaultVerticalAlignment;
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.url = Utils.getStringValue(json["url"]);
        this.fillMode = <Enums.FillMode>Utils.getEnumValue(Enums.FillMode, json["fillMode"], this.fillMode);
        this.horizontalAlignment = <Enums.HorizontalAlignment>Utils.getEnumValue(Enums.HorizontalAlignment, json["horizontalAlignment"], this.horizontalAlignment);
        this.verticalAlignment = <Enums.VerticalAlignment>Utils.getEnumValue(Enums.VerticalAlignment, json["verticalAlignment"], this.verticalAlignment);
    }

    toJSON(): any {
        if (!this.isValid()) {
            return undefined;
        }

        if (this.fillMode == BackgroundImage.defaultFillMode &&
            this.horizontalAlignment == BackgroundImage.defaultHorizontalAlignment &&
            this.verticalAlignment == BackgroundImage.defaultVerticalAlignment) {

            return this.url;
        }
        else {
            let result = super.toJSON();

            Utils.setProperty(result, "url", this.url);
            Utils.setEnumProperty(Enums.FillMode, result, "fillMode", this.fillMode, BackgroundImage.defaultFillMode);
            Utils.setEnumProperty(Enums.HorizontalAlignment, result, "horizontalAlignment", this.horizontalAlignment, BackgroundImage.defaultHorizontalAlignment);
            Utils.setEnumProperty(Enums.VerticalAlignment, result, "verticalAlignment", this.verticalAlignment, BackgroundImage.defaultVerticalAlignment);

            return result;
        }
    }

    apply(element: HTMLElement) {
        if (this.url) {
            element.style.backgroundImage = "url('" + this.url + "')";

            switch (this.fillMode) {
                case Enums.FillMode.Repeat:
                    element.style.backgroundRepeat = "repeat";
                    break;
                case Enums.FillMode.RepeatHorizontally:
                    element.style.backgroundRepeat = "repeat-x";
                    break;
                case Enums.FillMode.RepeatVertically:
                    element.style.backgroundRepeat = "repeat-y";
                    break;
                case Enums.FillMode.Cover:
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

    isValid(): boolean {
        return !Utils.isNullOrEmpty(this.url);
    }
}

export class Container extends StylableCardElementContainer {
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
                throw new Error("Elements of type " + item.getJsonTypeName() + " cannot be used as standalone elements.");
            }
        }
        else {
            throw new Error("The element already belongs to another container.")
        }
    }

    protected supportsExcplitiHeight(): boolean {
        return true;
    }

    protected getItemsCollectionPropertyName(): string {
        return "items";
    }

    protected applyBackground() {
        if (this.backgroundImage.isValid() && this.renderedElement) {
            this.backgroundImage.apply(this.renderedElement);
        }

        super.applyBackground();
    }

    protected internalRender(): HTMLElement | undefined {
        this._renderedItems = [];

        // Cache hostConfig to avoid walking the parent hierarchy several times
        let hostConfig = this.hostConfig;

        let element = document.createElement("div");

        if (this.rtl !== undefined && this.rtl) {
            element.dir = "rtl";
        }

        element.classList.add(hostConfig.makeCssClassName("ac-container"));
        element.style.display = "flex";
        element.style.flexDirection = "column";

        if (Shared.GlobalSettings.useAdvancedCardBottomTruncation) {
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

        if (this._items.length > 0) {
            for (let item of this._items) {
                let renderedItem = this.isElementAllowed(item, this.getForbiddenElementTypes()) ? item.render() : undefined;

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

    protected get isSelectable(): boolean {
        return true;
    }

    readonly backgroundImage: BackgroundImage = new BackgroundImage();

    verticalContentAlignment: Enums.VerticalAlignment = Enums.VerticalAlignment.Top;
    rtl?: boolean;

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "backgroundImage", this.backgroundImage.toJSON());

        Utils.setEnumProperty(Enums.VerticalAlignment, result, "verticalContentAlignment", this.verticalContentAlignment, Enums.VerticalAlignment.Top);

        if (this._items.length > 0) {
            let elements = [];

            for (let element of this._items) {
                elements.push(element.toJSON());
            }

            Utils.setProperty(result, this.getItemsCollectionPropertyName(), elements);
        }

        Utils.setProperty(result, "bleed", this.bleed, false);

        return result;
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

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this.setShouldFallback(false);

        this._items = [];
        this._renderedItems = [];

        this.backgroundImage.reset();

        let jsonBackgroundImage = json["backgroundImage"];

        if (jsonBackgroundImage) {
            if (typeof jsonBackgroundImage === "string") {
                this.backgroundImage.url = jsonBackgroundImage;
                this.backgroundImage.fillMode = Enums.FillMode.Cover;
            }
            else if (typeof jsonBackgroundImage === "object") {
                this.backgroundImage.parse(jsonBackgroundImage, errors);
            }
        }

        this.verticalContentAlignment = <Enums.VerticalAlignment>Utils.getEnumValue(Enums.VerticalAlignment, json["verticalContentAlignment"], this.verticalContentAlignment);

        if (json[this.getItemsCollectionPropertyName()] != null) {
            let items = json[this.getItemsCollectionPropertyName()] as any[];

            this.clear();

            for (let i = 0; i < items.length; i++) {
                let element = createElementInstance(
                    this,
                    items[i],
                    !this.isDesignMode(),
                    errors);

                if (element) {
                    this.insertItemAt(element, -1, true);
                }
            }
        }

        this.bleed = <boolean>Utils.getBoolValue(json["bleed"], this.bleed);
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
    }

    getResourceInformation(): Shared.IResourceInformation[] {
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

    get padding(): Shared.PaddingDefinition | undefined {
        return this.getPadding();
    }

    set padding(value: Shared.PaddingDefinition | undefined) {
        this.setPadding(value);
    }

    get selectAction(): Action | undefined {
        return this.getSelectAction();
    }

    set selectAction(value: Action | undefined) {
        this.setSelectAction(value);
    }

    get bleed(): boolean {
        return this.getBleed();
    }

    set bleed(value: boolean) {
        this.setBleed(value);
    }
}

export type ColumnWidth = Shared.SizeAndUnit | "auto" | "stretch";

export class Column extends Container {
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
        else {
            let sizeAndUnit = <Shared.SizeAndUnit>this.width;

            if (sizeAndUnit.unit == Enums.SizeUnit.Pixel) {
                renderedElement.style.flex = "0 0 auto";
                renderedElement.style.width = sizeAndUnit.physicalSize + "px";
            }
            else {
                renderedElement.style.flex = "1 1 " + (this._computedWeight > 0 ? this._computedWeight : sizeAndUnit.physicalSize) + "%";
            }
        }
    }

    protected get separatorOrientation(): Enums.Orientation {
        return Enums.Orientation.Vertical;
    }

    width: ColumnWidth = "auto";

    constructor(width: ColumnWidth = "auto") {
        super();

        this.width = width;
    }

    getJsonTypeName(): string {
        return "Column";
    }

    toJSON(): any {
        let result = super.toJSON();

        if (this.width instanceof Shared.SizeAndUnit) {
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

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        let jsonWidth = json["width"];

        if (jsonWidth === undefined) {
            jsonWidth = json["size"];

            if (jsonWidth !== undefined) {
                raiseParseError(
                    {
                        error: Enums.ValidationError.Deprecated,
                        message: "The \"Column.size\" property is deprecated and will be removed. Use the \"Column.width\" property instead."
                    },
                    errors
                );
            }
        }

        if (jsonWidth) {
            let invalidWidth = false;

            try {
                this.width = Shared.SizeAndUnit.parse(jsonWidth);
            }
            catch (e) {
                if (typeof jsonWidth === "string" && (jsonWidth === "auto" || jsonWidth === "stretch")) {
                    this.width = jsonWidth;
                }
                else {
                    invalidWidth = true;
                }
            }

            if (invalidWidth) {
                raiseParseError(
                    {
                        error: Enums.ValidationError.InvalidPropertyValue,
                        message: "Invalid column width:" + jsonWidth + " - defaulting to \"auto\""
                    },
                    errors
                );
            }
        }
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

export class ColumnSet extends StylableCardElementContainer {
    private _columns: Column[] = [];
    private _renderedColumns: Column[];

    private createColumnInstance(json: any, errors: Shared.IValidationError[] | undefined): Column | undefined {
        return createCardObjectInstance<Column>(
            this,
            json,
            [], // Forbidden types not supported for elements for now
            !this.isDesignMode(),
            (typeName: string) => {
                return !typeName || typeName === "Column" ? new Column() : undefined;
            },
            (typeName: string, errorType: InstanceCreationErrorType) => {
                if (errorType == InstanceCreationErrorType.UnknownType) {
                    return {
                        error: Enums.ValidationError.UnknownElementType,
                        message: "Unknown element type: " + typeName + ". Fallback will be used if present."
                    }
                }
                else {
                    return {
                        error: Enums.ValidationError.ElementTypeNotAllowed,
                        message: "Element type " + typeName + " isn't allowed in a ColumnSet."
                    }
                }
            },
            errors);
    }

    protected internalRender(): HTMLElement | undefined {
        this._renderedColumns = [];

        if (this._columns.length > 0) {
            // Cache hostConfig to avoid walking the parent hierarchy several times
            let hostConfig = this.hostConfig;

            let element = document.createElement("div");
            element.className = hostConfig.makeCssClassName("ac-columnSet");
            element.style.display = "flex";

            if (Shared.GlobalSettings.useAdvancedCardBottomTruncation) {
                // See comment in Container.internalRender()
                element.style.minHeight = '-webkit-min-content';
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

            let totalWeight: number = 0;

            for (let column of this._columns) {
                if (column.width instanceof Shared.SizeAndUnit && (column.width.unit == Enums.SizeUnit.Weight)) {
                    totalWeight += column.width.physicalSize;
                }
            }

            for (let column of this._columns) {
                if (column.width instanceof Shared.SizeAndUnit && column.width.unit == Enums.SizeUnit.Weight && totalWeight > 0) {
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

    toJSON(): any {
        let result = super.toJSON();

        if (this._columns.length > 0) {
            let columns = [];

            for (let column of this._columns) {
                columns.push(column.toJSON());
            }

            Utils.setProperty(result, "columns", columns);
        }

        Utils.setProperty(result, "bleed", this.bleed, false);

        return result;
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

    getCount(): number {
        return this._columns.length;
    }

    getItemCount(): number {
        return this.getCount();
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

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        if (json["columns"] != null) {
            let jsonColumns = json["columns"] as any[];

            this._columns = [];

            for (let i = 0; i < jsonColumns.length; i++) {
                let column = this.createColumnInstance(jsonColumns[i], errors);

                if (column) {
                    this._columns.push(column);
                }
            }
        }

        this.bleed = <boolean>Utils.getBoolValue(json["bleed"], this.bleed);
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
                {
                    error: Enums.ValidationError.Hint,
                    message: "It is not recommended to use weighted and stretched columns in the same ColumnSet, because in such a situation stretched columns will always get the minimum amount of space."
                });
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

    get padding(): Shared.PaddingDefinition | undefined {
        return this.getPadding();
    }

    set padding(value: Shared.PaddingDefinition | undefined) {
        this.setPadding(value);
    }

    get selectAction(): Action | undefined {
        return this.getSelectAction();
    }

    set selectAction(value: Action | undefined) {
        this.setSelectAction(value);
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

    return onAnchorClickedHandler !== undefined ? onAnchorClickedHandler(element, anchor) : false;
}

function raiseExecuteActionEvent(action: Action) {
    let card = action.parent ? action.parent.getRootElement() as AdaptiveCard : undefined;
    let onExecuteActionHandler = (card && card.onExecuteAction) ? card.onExecuteAction : AdaptiveCard.onExecuteAction;

    if (onExecuteActionHandler) {
        if (action.prepareForExecution()) {
            onExecuteActionHandler(action);
        }
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

function raiseParseElementEvent(element: CardElement, json: any, errors?: Shared.IValidationError[]) {
    let card = element.getRootElement() as AdaptiveCard;
    let onParseElementHandler = (card && card.onParseElement) ? card.onParseElement : AdaptiveCard.onParseElement;

    if (onParseElementHandler !== undefined) {
        onParseElementHandler(element, json, errors);
    }
}

function raiseParseActionEvent(action: Action, json: any, errors?: Shared.IValidationError[]) {
    let card = action.parent ? action.parent.getRootElement() as AdaptiveCard : undefined;
    let onParseActionHandler = (card && card.onParseAction) ? card.onParseAction : AdaptiveCard.onParseAction;

    if (onParseActionHandler !== undefined) {
        onParseActionHandler(action, json, errors);
    }
}

function raiseParseError(error: Shared.IValidationError, errors: Shared.IValidationError[] | undefined) {
    if (errors) {
        errors.push(error);
    }

    if (AdaptiveCard.onParseError !== undefined) {
        AdaptiveCard.onParseError(error);
    }
}

export interface ITypeRegistration<T> {
    typeName: string,
    createInstance: () => T;
}

export abstract class ContainerWithActions extends Container {
    private _actionCollection: ActionCollection;

    protected internalRender(): HTMLElement | undefined {
        let element = super.internalRender();

        if (element) {
            let renderedActions = this._actionCollection.render(this.hostConfig.actions.actionsOrientation, false);

            if (renderedActions) {
                Utils.appendChild(
                    element,
                    Utils.renderSeparation(
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

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "actions", this._actionCollection.toJSON());

        return result;
    }

    getActionCount(): number {
        return this._actionCollection.items.length;
    }

    getActionAt(index: number): Action | undefined {
        if (index >= 0 && index < this.getActionCount()) {
            return this._actionCollection.items[index];
        }
        else {
            return super.getActionAt(index);
        }
    }

    getActionById(id: string): Action | undefined {
        let result: Action | undefined = this._actionCollection.getActionById(id);

        return result ? result : super.getActionById(id);
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        this._actionCollection.parse(json["actions"], errors);
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (this._actionCollection) {
            this._actionCollection.validateProperties(context);
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

    getAllInputs(): Input[] {
        return super.getAllInputs().concat(this._actionCollection.getAllInputs());
    }

    getResourceInformation(): Shared.IResourceInformation[] {
        return super.getResourceInformation().concat(this._actionCollection.getResourceInformation());
    }

    isBleedingAtBottom(): boolean {
        if (this._actionCollection.renderedActionCount == 0) {
            return super.isBleedingAtBottom();
        }
        else {
            if (this._actionCollection.items.length == 1) {
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

export abstract class TypeRegistry<T> {
    private _items: ITypeRegistration<T>[] = [];

    private findTypeRegistration(typeName: string): ITypeRegistration<T> | undefined {
        for (let item of this._items) {
            if (item.typeName === typeName) {
                return item;
            }
        }

        return undefined;
    }

    constructor() {
        this.reset();
    }

    clear() {
        this._items = [];
    }

    abstract reset(): void;

    registerType(typeName: string, createInstance: () => T) {
        let registrationInfo = this.findTypeRegistration(typeName);

        if (registrationInfo !== undefined) {
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
        for (let i = 0; i < this._items.length; i++) {
            if (this._items[i].typeName === typeName) {
                this._items.splice(i, 1);

                return;
            }
        }
    }

    createInstance(typeName: string): T | undefined {
        let registrationInfo = this.findTypeRegistration(typeName);

        return registrationInfo ? registrationInfo.createInstance() : undefined;
    }

    getItemCount(): number {
        return this._items.length;
    }

    getItemAt(index: number): ITypeRegistration<T> {
        return this._items[index];
    }
}

export class ElementTypeRegistry extends TypeRegistry<CardElement> {
    reset(): void {
        this.clear();

        this.registerType("Container", () => { return new Container(); });
        this.registerType("TextBlock", () => { return new TextBlock(); });
        this.registerType("RichTextBlock", () => { return new RichTextBlock(); });
        this.registerType("TextRun", () => { return new TextRun(); });
        this.registerType("Image", () => { return new Image(); });
        this.registerType("ImageSet", () => { return new ImageSet(); });
        this.registerType("Media", () => { return new Media(); });
        this.registerType("FactSet", () => { return new FactSet(); });
        this.registerType("ColumnSet", () => { return new ColumnSet(); });
        this.registerType("ActionSet", () => { return new ActionSet(); });
        this.registerType("Input.Text", () => { return new TextInput(); });
        this.registerType("Input.Date", () => { return new DateInput(); });
        this.registerType("Input.Time", () => { return new TimeInput(); });
        this.registerType("Input.Number", () => { return new NumberInput(); });
        this.registerType("Input.ChoiceSet", () => { return new ChoiceSetInput(); });
        this.registerType("Input.Toggle", () => { return new ToggleInput(); });
    }
}

export class ActionTypeRegistry extends TypeRegistry<Action> {
    reset(): void {
        this.clear();

        this.registerType(OpenUrlAction.JsonTypeName, () => { return new OpenUrlAction(); });
        this.registerType(SubmitAction.JsonTypeName, () => { return new SubmitAction(); });
        this.registerType(ShowCardAction.JsonTypeName, () => { return new ShowCardAction(); });
        this.registerType(ToggleVisibilityAction.JsonTypeName, () => { return new ToggleVisibilityAction(); });
    }
}

export interface IMarkdownProcessingResult {
    didProcess: boolean;
    outputHtml?: any;
}

export class AdaptiveCard extends ContainerWithActions {
    private static currentVersion: Shared.Version = new Shared.Version(1, 2);

    static readonly elementTypeRegistry = new ElementTypeRegistry();
    static readonly actionTypeRegistry = new ActionTypeRegistry();

    static onAnchorClicked?: (element: CardElement, anchor: HTMLAnchorElement) => boolean;
    static onExecuteAction?: (action: Action) => void;
    static onElementVisibilityChanged?: (element: CardElement) => void;
    static onImageLoaded?: (image: Image) => void;
    static onInlineCardExpanded?: (action: ShowCardAction, isExpanded: boolean) => void;
    static onInputValueChanged?: (input: Input) => void;
    static onParseElement?: (element: CardElement, json: any, errors?: Shared.IValidationError[]) => void;
    static onParseAction?: (element: Action, json: any, errors?: Shared.IValidationError[]) => void;
    static onParseError?: (error: Shared.IValidationError) => void;
    static onProcessMarkdown?: (text: string, result: IMarkdownProcessingResult) => void;

    static get processMarkdown(): (text: string) => string {
        throw new Error("The processMarkdown event has been removed. Please update your code and set onProcessMarkdown instead.")
    }

    static set processMarkdown(value: (text: string) => string) {
        throw new Error("The processMarkdown event has been removed. Please update your code and set onProcessMarkdown instead.")
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
            console.warn("Markdown processing isn't enabled. Please see https://www.npmjs.com/package/adaptivecards#supporting-markdown")
        }

        return result;
    }

    private _cardTypeName?: string = "AdaptiveCard";
    private _fallbackCard?: AdaptiveCard;

    private isVersionSupported(): boolean {
        if (this.bypassVersionCheck) {
            return true;
        }
        else {
            let unsupportedVersion: boolean =
                !this.version ||
                !this.version.isValid ||
                (AdaptiveCard.currentVersion.major < this.version.major) ||
                (AdaptiveCard.currentVersion.major == this.version.major && AdaptiveCard.currentVersion.minor < this.version.minor);

            return !unsupportedVersion;
        }
    }

    protected getItemsCollectionPropertyName(): string {
        return "body";
    }

    protected internalRender(): HTMLElement | undefined {
        let renderedElement = super.internalRender();

        if (Shared.GlobalSettings.useAdvancedCardBottomTruncation && renderedElement) {
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

    protected getDefaultPadding(): Shared.PaddingDefinition {
        return new Shared.PaddingDefinition(
            Enums.Spacing.Padding,
            Enums.Spacing.Padding,
            Enums.Spacing.Padding,
            Enums.Spacing.Padding);
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

    onAnchorClicked?: (element: CardElement, anchor: HTMLAnchorElement) => boolean;
    onExecuteAction?: (action: Action) => void;
    onElementVisibilityChanged?: (element: CardElement) => void;
    onImageLoaded?: (image: Image) => void;
    onInlineCardExpanded?: (action: ShowCardAction, isExpanded: boolean) => void;
    onInputValueChanged?: (input: Input) => void;
    onParseElement?: (element: CardElement, json: any, errors?: Shared.IValidationError[]) => void;
    onParseAction?: (element: Action, json: any, errors?: Shared.IValidationError[]) => void;

    version?: Shared.Version = new Shared.Version(1, 0);
    fallbackText: string;
    speak: string;
    designMode: boolean = false;

    getJsonTypeName(): string {
        return "AdaptiveCard";
    }

    toJSON(): any {
        let result = super.toJSON();

        Utils.setProperty(result, "$schema", "http://adaptivecards.io/schemas/adaptive-card.json");

        if (!this.bypassVersionCheck && this.version) {
            Utils.setProperty(result, "version", this.version.toString());
        }

        Utils.setProperty(result, "fallbackText", this.fallbackText);
        Utils.setProperty(result, "lang", this.lang);
        Utils.setProperty(result, "speak", this.speak);

        return result;
    }

    internalValidateProperties(context: ValidationResults) {
        super.internalValidateProperties(context);

        if (this._cardTypeName != "AdaptiveCard") {
            context.addFailure(
                this,
                {
                    error: Enums.ValidationError.MissingCardType,
                    message: "Invalid or missing card type. Make sure the card's type property is set to \"AdaptiveCard\"."
                });
        }

        if (!this.bypassVersionCheck && !this.version) {
            context.addFailure(
                this,
                {
                    error: Enums.ValidationError.PropertyCantBeNull,
                    message: "The version property must be specified."
                });
        }
        else if (!this.isVersionSupported()) {
            context.addFailure(
                this,
                {
                    error: Enums.ValidationError.UnsupportedCardVersion,
                    message: "The specified card version (" + this.version + ") is not supported. The maximum supported card version is " + AdaptiveCard.currentVersion
                });
        }
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        this._fallbackCard = undefined;

        this._cardTypeName = Utils.getStringValue(json["type"]);
        this.speak = Utils.getStringValue(json["speak"]);

		let langId = Utils.getStringValue(json["lang"]);

        if (langId && typeof langId === "string") {
            try {
                this.lang = langId;
            }
            catch (e) {
                raiseParseError(
                    {
                        error: Enums.ValidationError.InvalidPropertyValue,
                        message: e.message
                    },
                    errors
                );
            }
        }

        this.version = Shared.Version.parse(json["version"], errors);

        this.fallbackText = Utils.getStringValue(json["fallbackText"]);

        let fallbackElement = createElementInstance(
            undefined,
            json["fallback"],
            !this.isDesignMode(),
            errors);

        if (fallbackElement) {
            this._fallbackCard = new AdaptiveCard();
            this._fallbackCard.addItem(fallbackElement);
        }

        super.parse(json, errors);
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
                renderedCard.tabIndex = 0;

                if (!Utils.isNullOrEmpty(this.speak)) {
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

        if (Shared.GlobalSettings.useAdvancedCardBottomTruncation && this.isDisplayed()) {
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
    protected getDefaultPadding(): Shared.PaddingDefinition {
        return new Shared.PaddingDefinition(
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

    getForbiddenActionTypes(): any[] {
        return [ShowCardAction];
    }
}

const defaultHostConfig: HostConfig.HostConfig = new HostConfig.HostConfig(
    {
        supportsInteractivity: true,
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
        fontTypes: {
            default: {
                fontFamily: "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif",
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
                }
            },
            monospace: {
                fontFamily: "'Courier New', Courier, monospace",
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
                }
            }
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
            },
            accent: {
                backgroundColor: "#C7DEF9",
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
            good: {
                backgroundColor: "#CCFFCC",
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
            attention: {
                backgroundColor: "#FFC5B2",
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
            warning: {
                backgroundColor: "#FFE2B2",
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