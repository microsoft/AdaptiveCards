import * as Enums from "./enums";
import * as Utils from "./utils";
import * as HostConfig from "./host-config";
export interface IValidationError {
    error: Enums.ValidationError;
    message: string;
}
export declare abstract class CardElement {
    private _hostConfig?;
    private _internalPadding;
    private _parent;
    private _isVisibile;
    private _renderedElement;
    private _separatorElement;
    private internalRenderSeparator();
    private updateRenderedElementVisibility();
    protected internalGetNonZeroPadding(padding: HostConfig.PaddingDefinition): void;
    protected adjustRenderedElementSize(renderedElement: HTMLElement): void;
    protected showBottomSpacer(requestingElement: CardElement): void;
    protected hideBottomSpacer(requestingElement: CardElement): void;
    protected setParent(value: CardElement): void;
    protected readonly useDefaultSizing: boolean;
    protected abstract internalRender(): HTMLElement;
    protected readonly allowCustomPadding: boolean;
    protected readonly defaultPadding: HostConfig.PaddingDefinition;
    protected internalPadding: HostConfig.PaddingDefinition;
    protected readonly separatorOrientation: Enums.Orientation;
    id: string;
    speak: string;
    horizontalAlignment?: Enums.HorizontalAlignment;
    spacing: Enums.Spacing;
    separator: boolean;
    height: "auto" | "stretch";
    abstract getJsonTypeName(): string;
    abstract renderSpeech(): string;
    getNonZeroPadding(): HostConfig.PaddingDefinition;
    getForbiddenElementTypes(): Array<string>;
    getForbiddenActionTypes(): Array<any>;
    parse(json: any): void;
    validate(): Array<IValidationError>;
    render(): HTMLElement;
    updateLayout(processChildren?: boolean): void;
    isAtTheVeryTop(): boolean;
    isFirstElement(element: CardElement): boolean;
    isAtTheVeryBottom(): boolean;
    isLastElement(element: CardElement): boolean;
    isAtTheVeryLeft(): boolean;
    isLeftMostElement(element: CardElement): boolean;
    isAtTheVeryRight(): boolean;
    isRightMostElement(element: CardElement): boolean;
    canContentBleed(): boolean;
    getRootElement(): CardElement;
    getParentContainer(): Container;
    getAllInputs(): Array<Input>;
    getElementById(id: string): CardElement;
    getActionById(id: string): Action;
    hostConfig: HostConfig.HostConfig;
    readonly isInteractive: boolean;
    readonly isStandalone: boolean;
    readonly parent: CardElement;
    isVisible: boolean;
    readonly renderedElement: HTMLElement;
    readonly separatorElement: HTMLElement;
}
export declare class TextBlock extends CardElement {
    size: Enums.TextSize;
    weight: Enums.TextWeight;
    color: Enums.TextColor;
    text: string;
    isSubtle: boolean;
    wrap: boolean;
    maxLines: number;
    protected internalRender(): HTMLElement;
    parse(json: any): void;
    getJsonTypeName(): string;
    renderSpeech(): string;
}
export declare class Fact {
    name: string;
    value: string;
    speak: string;
    renderSpeech(): string;
}
export declare class FactSet extends CardElement {
    protected readonly useDefaultSizing: boolean;
    protected internalRender(): HTMLElement;
    facts: Array<Fact>;
    getJsonTypeName(): string;
    parse(json: any): void;
    renderSpeech(): string;
}
export declare class Image extends CardElement {
    private _selectAction;
    protected readonly useDefaultSizing: boolean;
    protected internalRender(): HTMLElement;
    style: Enums.ImageStyle;
    url: string;
    size: Enums.Size;
    pixelWidth?: number;
    pixelHeight?: number;
    altText: string;
    getJsonTypeName(): string;
    getActionById(id: string): Action;
    parse(json: any): void;
    renderSpeech(): string;
    selectAction: Action;
}
export declare class ImageSet extends CardElement {
    private _images;
    protected internalRender(): HTMLElement;
    imageSize: Enums.Size;
    getJsonTypeName(): string;
    parse(json: any): void;
    addImage(image: Image): void;
    renderSpeech(): string;
}
export declare abstract class Input extends CardElement implements Utils.IInput {
    id: string;
    title: string;
    defaultValue: string;
    readonly abstract value: string;
    validate(): Array<IValidationError>;
    parse(json: any): void;
    renderSpeech(): string;
    getAllInputs(): Array<Input>;
    readonly isInteractive: boolean;
}
export declare class TextInput extends Input {
    private _textareaElement;
    private _inputElement;
    protected internalRender(): HTMLElement;
    maxLength: number;
    isMultiline: boolean;
    placeholder: string;
    getJsonTypeName(): string;
    parse(json: any): void;
    readonly value: string;
}
export declare class ToggleInput extends Input {
    private _checkboxInputElement;
    protected internalRender(): HTMLElement;
    title: string;
    valueOn: string;
    valueOff: string;
    getJsonTypeName(): string;
    parse(json: any): void;
    readonly value: string;
}
export declare class Choice {
    title: string;
    value: string;
}
export declare class ChoiceSetInput extends Input {
    private _selectElement;
    private _toggleInputs;
    protected internalRender(): HTMLElement;
    choices: Array<Choice>;
    isCompact: boolean;
    isMultiSelect: boolean;
    placeholder: string;
    getJsonTypeName(): string;
    validate(): Array<IValidationError>;
    parse(json: any): void;
    readonly value: string;
}
export declare class NumberInput extends Input {
    private _numberInputElement;
    protected internalRender(): HTMLElement;
    min: string;
    max: string;
    placeholder: string;
    getJsonTypeName(): string;
    parse(json: any): void;
    readonly value: string;
}
export declare class DateInput extends Input {
    private _dateInputElement;
    protected internalRender(): HTMLElement;
    getJsonTypeName(): string;
    readonly value: string;
}
export declare class TimeInput extends Input {
    private _timeInputElement;
    protected internalRender(): HTMLElement;
    getJsonTypeName(): string;
    readonly value: string;
}
export declare abstract class Action {
    private _parent;
    private _actionCollection;
    protected setParent(value: CardElement): void;
    abstract getJsonTypeName(): string;
    execute(): void;
    private setCollection(actionCollection);
    setStatus(status: any): void;
    validate(): Array<IValidationError>;
    prepare(inputs: Array<Input>): void;
    parse(json: any): void;
    getAllInputs(): Array<Input>;
    getActionById(id: string): Action;
    id: string;
    title: string;
    readonly parent: CardElement;
}
export declare class SubmitAction extends Action {
    private _isPrepared;
    private _originalData;
    private _processedData;
    getJsonTypeName(): string;
    prepare(inputs: Array<Input>): void;
    parse(json: any): void;
    data: Object;
}
export declare class OpenUrlAction extends Action {
    url: string;
    getJsonTypeName(): string;
    validate(): Array<IValidationError>;
    parse(json: any): void;
}
export declare class HttpHeader {
    private _value;
    name: string;
    prepare(inputs: Array<Input>): void;
    value: string;
}
export declare class HttpAction extends Action {
    private _url;
    private _body;
    private _headers;
    method: string;
    getJsonTypeName(): string;
    validate(): Array<IValidationError>;
    prepare(inputs: Array<Input>): void;
    parse(json: any): void;
    url: string;
    body: string;
    readonly headers: Array<HttpHeader>;
}
export declare class ShowCardAction extends Action {
    protected setParent(value: CardElement): void;
    readonly card: AdaptiveCard;
    title: string;
    getJsonTypeName(): string;
    validate(): Array<IValidationError>;
    parse(json: any): void;
    getAllInputs(): Array<Input>;
    getActionById(id: string): Action;
}
export declare class ActionSet extends CardElement {
    private _actionCollection;
    protected internalRender(): HTMLElement;
    constructor();
    getJsonTypeName(): string;
    validate(): Array<IValidationError>;
    parse(json: any, itemsCollectionPropertyName?: string): void;
    addAction(action: Action): void;
    getAllInputs(): Array<Input>;
    renderSpeech(): string;
    readonly isInteractive: boolean;
}
export declare class BackgroundImage {
    url: string;
    mode: Enums.BackgroundImageMode;
    horizontalAlignment: Enums.HorizontalAlignment;
    verticalAlignment: Enums.VerticalAlignment;
    parse(json: any): void;
    apply(element: HTMLElement): void;
}
export declare class Container extends CardElement {
    private _selectAction;
    private isElementAllowed(element, forbiddenElementTypes);
    private _items;
    private _style?;
    private readonly hasExplicitStyle;
    protected showBottomSpacer(requestingElement: CardElement): void;
    protected hideBottomSpacer(requestingElement: CardElement): void;
    protected applyPadding(): void;
    protected internalRender(): HTMLElement;
    protected readonly hasBackground: boolean;
    protected readonly defaultStyle: Enums.ContainerStyle;
    protected readonly allowCustomStyle: boolean;
    backgroundImage: BackgroundImage;
    readonly style: Enums.ContainerStyle;
    getJsonTypeName(): string;
    isFirstElement(element: CardElement): boolean;
    isLastElement(element: CardElement): boolean;
    validate(): Array<IValidationError>;
    parse(json: any, itemsCollectionPropertyName?: string): void;
    addItem(item: CardElement): void;
    clear(): void;
    canContentBleed(): boolean;
    getAllInputs(): Array<Input>;
    getElementById(id: string): CardElement;
    getActionById(id: string): Action;
    renderSpeech(): string;
    updateLayout(processChildren?: boolean): void;
    selectAction: Action;
}
export declare class Column extends Container {
    private _computedWeight;
    protected adjustRenderedElementSize(renderedElement: HTMLElement): void;
    protected readonly separatorOrientation: Enums.Orientation;
    width: number | "auto" | "stretch";
    getJsonTypeName(): string;
    parse(json: any): void;
    readonly isStandalone: boolean;
}
export declare class ColumnSet extends CardElement {
    private _columns;
    private _selectAction;
    protected internalRender(): HTMLElement;
    getJsonTypeName(): string;
    parse(json: any): void;
    validate(): Array<IValidationError>;
    updateLayout(processChildren?: boolean): void;
    addColumn(column: Column): void;
    isLeftMostElement(element: CardElement): boolean;
    isRightMostElement(element: CardElement): boolean;
    getAllInputs(): Array<Input>;
    getElementById(id: string): CardElement;
    getActionById(id: string): Action;
    renderSpeech(): string;
    selectAction: Action;
}
export interface IVersion {
    major: number;
    minor: number;
}
export declare class TypeRegistry<T> {
    private _items;
    private findTypeRegistration(typeName);
    clear(): void;
    registerType(typeName: string, createInstance: () => T): void;
    unregisterType(typeName: string): void;
    createInstance(typeName: string): T;
}
export declare abstract class ContainerWithActions extends Container {
    private _actionCollection;
    protected internalRender(): HTMLElement;
    constructor();
    getActionById(id: string): Action;
    parse(json: any, itemsCollectionPropertyName?: string): void;
    isLastElement(element: CardElement): boolean;
    addAction(action: Action): void;
    clear(): void;
    getAllInputs(): Array<Input>;
    readonly isStandalone: boolean;
}
export declare class AdaptiveCard extends ContainerWithActions {
    private static currentVersion;
    static useAutoPadding: boolean;
    static preExpandSingleShowCardAction: boolean;
    static elementTypeRegistry: TypeRegistry<CardElement>;
    static actionTypeRegistry: TypeRegistry<Action>;
    static onAnchorClicked: (anchor: HTMLAnchorElement) => boolean;
    static onExecuteAction: (action: Action) => void;
    static onElementVisibilityChanged: (element: CardElement) => void;
    static onInlineCardExpanded: (action: ShowCardAction, isExpanded: boolean) => void;
    static onParseElement: (element: CardElement, json: any) => void;
    static onParseError: (error: IValidationError) => void;
    static initialize(): void;
    private isVersionSupported();
    private _cardTypeName;
    protected applyPadding(): void;
    protected readonly defaultPadding: HostConfig.PaddingDefinition;
    protected readonly allowCustomPadding: boolean;
    protected readonly allowCustomStyle: boolean;
    protected readonly hasBackground: boolean;
    minVersion: IVersion;
    fallbackText: string;
    getJsonTypeName(): string;
    validate(): Array<IValidationError>;
    parse(json: any): void;
    render(): HTMLElement;
    canContentBleed(): boolean;
}
