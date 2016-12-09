export declare function processMarkdown(text: string): any;
export declare enum Size {
    Auto = 0,
    Stretch = 1,
    Small = 2,
    Medium = 3,
    Large = 4,
}
export declare enum TextSize {
    Small = 0,
    Normal = 1,
    Medium = 2,
    Large = 3,
    ExtraLarge = 4,
}
export declare enum TextWeight {
    Lighter = 0,
    Normal = 1,
    Bolder = 2,
}
export declare enum TextColor {
    Default = 0,
    Dark = 1,
    Light = 2,
    Accent = 3,
    Good = 4,
    Warning = 5,
    Attention = 6,
}
export declare enum HorizontalAlignment {
    Left = 0,
    Center = 1,
    Right = 2,
}
export declare enum ImageStyle {
    Normal = 0,
    Person = 1,
}
export declare function stringToSize(value: string, defaultValue: Size): Size;
export declare function stringToTextSize(value: string, defaultValue: TextSize): TextSize;
export declare function stringToTextWeight(value: string, defaultValue: TextWeight): TextWeight;
export declare function stringToTextColor(value: string, defaultValue: TextColor): TextColor;
export declare function stringToHorizontalAlignment(value: string, defaultValue: HorizontalAlignment): HorizontalAlignment;
export declare function stringToImageStyle(value: string, defaultValue: ImageStyle): ImageStyle;
export interface IEvent<TSender> {
    subscribe(fn: (sender: TSender, args: any) => void): void;
    unsubscribe(fn: (sender: TSender, args: any) => void): void;
}
export declare function isNullOrEmpty(value: string): boolean;
export declare function appendChild(node: Node, child: Node): void;
export declare abstract class CardElement {
    static createElement(container: Container, typeName: string): CardElement;
    private _container;
    size: Size;
    horizontalAlignment: HorizontalAlignment;
    constructor(container: Container);
    readonly container: Container;
    readonly hideOverflow: boolean;
    readonly useDefaultSizing: boolean;
    abstract render(): HTMLElement;
    removeTopSpacing(element: HTMLElement): void;
    adjustLayout(element: HTMLElement): void;
    internalRender(): HTMLElement;
    parse(json: any): void;
}
export declare class TextBlock extends CardElement {
    textSize: TextSize;
    textWeight: TextWeight;
    textColor: TextColor;
    text: string;
    isSubtle: boolean;
    wrap: boolean;
    parse(json: any): void;
    render(): HTMLElement;
    removeTopSpacing(element: HTMLElement): void;
}
export declare class Fact {
    name: string;
    value: string;
    parse(json: any): void;
}
export declare class FactGroup extends CardElement {
    private _items;
    readonly items: Array<Fact>;
    parse(json: any): void;
    render(): HTMLElement;
}
export declare class Image extends CardElement {
    style: ImageStyle;
    url: string;
    readonly useDefaultSizing: boolean;
    parse(json: any): void;
    render(): HTMLElement;
}
export declare class ImageGallery extends CardElement {
    private _items;
    imageSize: Size;
    readonly items: Array<Image>;
    parse(json: any): void;
    render(): HTMLElement;
}
export declare abstract class Action {
    private _owner;
    name: string;
    static create(owner: CardElement, typeName: string): Action;
    readonly owner: CardElement;
    constructor(owner: CardElement);
    parse(json: any): void;
    renderUi(container: Container, requiresTopSpacer?: boolean): HTMLElement;
    readonly hasUi: boolean;
}
export declare abstract class ExternalAction extends Action {
}
export declare class TargetUri {
    os: string;
    uri: string;
    parse(json: any): void;
}
export declare class OpenUri extends ExternalAction {
    private _targets;
    addTarget(): TargetUri;
    parse(json: any): void;
}
export declare class HttpPOST extends ExternalAction {
    target: string;
    body: string;
    bodyContentType: string;
    successMessage: string;
    errorMessage: string;
    parse(json: any): void;
}
export declare abstract class Input extends CardElement {
    id: string;
    title: string;
    value: string;
    static createInput(container: Container, typeName: string): Input;
    parse(json: any): void;
    abstract render(): HTMLElement;
}
export declare class TextInput extends Input {
    maxLength: number;
    isMultiline: boolean;
    constructor(container: Container);
    parse(json: any): void;
    render(): HTMLElement;
}
export declare class Choice {
    display: string;
    value: string;
    parse(json: any): void;
}
export declare class MultichoiceInput extends Input {
    private _choices;
    constructor(container: Container);
    parse(json: any): void;
    render(): HTMLElement;
}
export declare class DateInput extends Input {
    includeTime: boolean;
    constructor(container: Container);
    parse(json: any): void;
    render(): HTMLElement;
}
export declare class ActionCard extends Action {
    private _allowedActionTypes;
    private _inputs;
    private _actions;
    private _card;
    name: string;
    readonly hasUi: boolean;
    readonly inputs: Array<Input>;
    readonly actions: Array<Action>;
    parse(json: any): void;
    private actionClicked(actionButton);
    renderUi(container: Container, needsTopSpacer?: boolean): HTMLElement;
}
export declare enum ActionButtonStyle {
    Link = 0,
    Push = 1,
}
export declare enum ActionButtonState {
    Normal = 0,
    Expanded = 1,
    Subdued = 2,
}
export declare class ActionButton {
    private _action;
    private _style;
    private _onClick;
    private _element;
    private _state;
    private _text;
    private click();
    private updateCssStyle();
    constructor(action: Action, style: ActionButtonStyle);
    readonly action: Action;
    readonly onClick: IEvent<ActionButton>;
    text: string;
    readonly element: HTMLElement;
    state: ActionButtonState;
}
export declare class ActionGroup extends CardElement {
    static buttonStyle: ActionButtonStyle;
    private _actionButtons;
    private _actionCardContainer;
    private _actions;
    private _expandedAction;
    private hideActionCardPane();
    private showActionCardPane(action);
    private actionClicked(actionButton);
    readonly actions: Array<Action>;
    readonly hideOverflow: boolean;
    parse(json: any): void;
    render(): HTMLElement;
}
export declare class Separator extends CardElement {
    parse(json: any): void;
    render(): HTMLDivElement;
}
export declare class Container extends CardElement {
    private _forbiddenItemTypes;
    private _items;
    private _element;
    private _textColor;
    private isAllowedItemType(elementType);
    protected readonly cssClassName: string;
    backgroundImageUrl: string;
    backgroundColor: string;
    constructor(container: Container, forbiddenItemTypes?: Array<string>);
    readonly items: Array<CardElement>;
    readonly elementCount: number;
    readonly hideOverflow: boolean;
    textColor: TextColor;
    addElement(element: CardElement): void;
    isLastElement(element: CardElement): boolean;
    getElement(index: number): CardElement;
    showBottomSpacer(requestingElement: CardElement): void;
    hideBottomSpacer(requestingElement: CardElement): void;
    parse(json: any): void;
    render(): HTMLElement;
    getRootContainer(): Container;
}
export declare class Column extends Container {
    private _useWeight;
    private _weight;
    protected readonly cssClassName: string;
    parse(json: any): void;
    adjustLayout(element: HTMLElement): void;
}
export declare class ColumnGroup extends CardElement {
    private _items;
    addColumn(): Column;
    parse(json: any): void;
    render(): HTMLElement;
}
export declare class AdaptiveCard {
    private _rootContainer;
    textColor: TextColor;
    parse(json: any): void;
    render(): HTMLElement;
}
