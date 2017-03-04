declare module 'adaptive-card-html-renderer/Enumerations' {
	export enum ActionButtonStyle {
	    Link = 0,
	    Push = 1,
	}
	export enum ActionButtonState {
	    Normal = 0,
	    Expanded = 1,
	    Subdued = 2,
	}
	export enum Size {
	    Auto = 0,
	    Stretch = 1,
	    Small = 2,
	    Medium = 3,
	    Large = 4,
	}
	export enum TextSize {
	    Small = 0,
	    Normal = 1,
	    Medium = 2,
	    Large = 3,
	    ExtraLarge = 4,
	}
	export enum TextWeight {
	    Lighter = 0,
	    Normal = 1,
	    Bolder = 2,
	}
	export enum TextColor {
	    Default = 0,
	    Dark = 1,
	    Light = 2,
	    Accent = 3,
	    Good = 4,
	    Warning = 5,
	    Attention = 6,
	}
	export enum HorizontalAlignment {
	    Left = 0,
	    Center = 1,
	    Right = 2,
	}
	export enum ImageStyle {
	    Normal = 0,
	    Person = 1,
	}
	export enum Separation {
	    None = 0,
	    Default = 1,
	    Strong = 2,
	}
	export enum RenderError {
	    MissingCardType = 0,
	    UnsupportedVersion = 1,
	    ElementTypeNotAllowed = 2,
	    ActionTypeNotAllowed = 3,
	    NestedActionNotAllowed = 4,
	    TooManyActions = 5,
	}
	export function stringToSize(value: string, defaultValue: Size): Size;
	export function stringToTextSize(value: string, defaultValue: TextSize): TextSize;
	export function stringToTextWeight(value: string, defaultValue: TextWeight): TextWeight;
	export function stringToTextColor(value: string, defaultValue: TextColor): TextColor;
	export function stringToHorizontalAlignment(value: string, defaultValue: HorizontalAlignment): HorizontalAlignment;
	export function stringToImageStyle(value: string, defaultValue: ImageStyle): ImageStyle;
	export function stringToSeparation(value: string, defaultValue: Separation): Separation;

}
declare module 'adaptive-card-html-renderer/Utils' {
	export function processMarkdown(text: string): any;
	export function isNullOrEmpty(value: string): boolean;
	export function appendChild(node: Node, child: Node): void;
	export function getClassNameFromInstance(object: any): string;
	export function getClassNameFromConstructor(constructor: any): string;

}
declare module 'adaptive-card-html-renderer/TextFormatters' {
	export function formatText(text: string): string;

}
declare module 'adaptive-card-html-renderer/CardElements' {
	import * as Enums from 'adaptive-card-html-renderer/Enumerations';
	export abstract class CardElement {
	    private _container;
	    speak: string;
	    horizontalAlignment: Enums.HorizontalAlignment;
	    separation: Enums.Separation;
	    constructor(container: Container);
	    readonly container: Container;
	    readonly hideOverflow: boolean;
	    readonly useDefaultSizing: boolean;
	    abstract render(): HTMLElement;
	    abstract renderSpeech(): string;
	    removeTopSpacing(element: HTMLElement): void;
	    adjustLayout(element: HTMLElement): void;
	    internalRender(): HTMLElement;
	}
	export class TextBlock extends CardElement {
	    static TypeName: string;
	    size: Enums.TextSize;
	    weight: Enums.TextWeight;
	    color: Enums.TextColor;
	    text: string;
	    isSubtle: boolean;
	    wrap: boolean;
	    render(): HTMLElement;
	    renderSpeech(): string;
	    removeTopSpacing(element: HTMLElement): void;
	}
	export class Fact {
	    name: string;
	    value: string;
	    speak: string;
	    renderSpeech(): string;
	}
	export class FactSet extends CardElement {
	    static TypeName: string;
	    private _facts;
	    readonly facts: Array<Fact>;
	    render(): HTMLElement;
	    renderSpeech(): string;
	    readonly useDefaultSizing: boolean;
	}
	export class Image extends CardElement {
	    static TypeName: string;
	    style: Enums.ImageStyle;
	    url: string;
	    size: Enums.Size;
	    selectAction: ActionExternal;
	    readonly useDefaultSizing: boolean;
	    render(): HTMLElement;
	    renderSpeech(): string;
	}
	export class ImageSet extends CardElement {
	    static TypeName: string;
	    private _images;
	    imageSize: Enums.Size;
	    readonly images: Array<Image>;
	    render(): HTMLElement;
	    renderSpeech(): string;
	}
	export abstract class Input extends CardElement {
	    id: string;
	    title: string;
	    defaultValue: string;
	    readonly abstract value: string;
	    renderSpeech(): string;
	}
	export class InputText extends Input {
	    static TypeName: string;
	    private _textareaElement;
	    maxLength: number;
	    isMultiline: boolean;
	    placeholder: string;
	    constructor(container: Container);
	    readonly value: string;
	    render(): HTMLElement;
	}
	export class InputToggle extends Input {
	    static TypeName: string;
	    private _checkboxInputElement;
	    title: string;
	    valueOn: string;
	    valueOff: string;
	    readonly value: string;
	    render(): HTMLElement;
	}
	export class Choice {
	    title: string;
	    value: string;
	}
	export class InputChoiceSet extends Input {
	    static TypeName: string;
	    private _selectElement;
	    private _toggleInputs;
	    choices: Array<Choice>;
	    isCompact: boolean;
	    isMultiSelect: boolean;
	    placeholder: string;
	    constructor(container: Container);
	    readonly value: string;
	    render(): HTMLElement;
	}
	export class InputNumber extends Input {
	    static TypeName: string;
	    private _numberInputElement;
	    min: string;
	    max: string;
	    constructor(container: Container);
	    readonly value: string;
	    render(): HTMLElement;
	}
	export class InputDate extends Input {
	    static TypeName: string;
	    private _dateInputElement;
	    constructor(container: Container);
	    readonly value: string;
	    render(): HTMLElement;
	}
	export class InputTime extends Input {
	    static TypeName: string;
	    private _timeInputElement;
	    constructor(container: Container);
	    readonly value: string;
	    render(): HTMLElement;
	}
	export class ActionButton {
	    private _action;
	    private _style;
	    private _element;
	    private _state;
	    private _text;
	    private click();
	    private updateCssStyle();
	    constructor(action: Action, style: Enums.ActionButtonStyle);
	    onClick: (actionButton: ActionButton) => void;
	    readonly action: Action;
	    text: string;
	    readonly element: HTMLElement;
	    state: Enums.ActionButtonState;
	}
	export abstract class Action {
	    title: string;
	    abstract execute(): any;
	    parse(json: any): void;
	    renderUi(): HTMLElement;
	    readonly hasUi: boolean;
	}
	export abstract class ActionExternal extends Action {
	    onExecute: (action: ActionExternal) => void;
	    execute(): void;
	}
	export class ActionSubmit extends ActionExternal {
	    static TypeName: string;
	    data: string;
	}
	export class ActionOpenUrl extends ActionExternal {
	    static TypeName: string;
	    url: string;
	}
	export class HttpHeader {
	    name: string;
	    value: string;
	}
	export class ActionHttp extends ActionExternal {
	    static TypeName: string;
	    private _headers;
	    url: string;
	    method: string;
	    body: string;
	    readonly headers: Array<HttpHeader>;
	}
	export class ActionShowCard extends Action {
	    static TypeName: string;
	    card: Container;
	    title: string;
	    execute(): void;
	    readonly hasUi: boolean;
	    renderUi(): HTMLElement;
	}
	export class ActionCollection {
	    private _container;
	    private _actionButtons;
	    private _actionCardContainer;
	    private _items;
	    private _expandedAction;
	    private hideActionCardPane();
	    private showActionCardPane(action);
	    private actionClicked(actionButton);
	    private static checkActionTypeIsAllowed(action);
	    constructor(container: Container);
	    readonly container: Container;
	    readonly items: Array<Action>;
	    readonly hideOverflow: boolean;
	    render(): HTMLElement;
	}
	export class Container extends CardElement {
	    static TypeName: string;
	    private _items;
	    private _element;
	    private _textColor;
	    private _itemsCollectionPropertyName;
	    private static checkElementTypeIsAllowed(element);
	    protected readonly cssClassName: string;
	    backgroundImageUrl: string;
	    backgroundColor: string;
	    actionButtonStyle: Enums.ActionButtonStyle;
	    actions: ActionCollection;
	    selectAction: ActionExternal;
	    constructor(container: Container, itemsCollectionPropertyName?: string);
	    readonly hideOverflow: boolean;
	    textColor: Enums.TextColor;
	    readonly itemCount: number;
	    getAllInputs(output: Array<Input>): void;
	    addItem(element: CardElement): void;
	    isLastItem(element: CardElement): boolean;
	    getItem(index: number): CardElement;
	    showBottomSpacer(requestingElement?: CardElement): void;
	    hideBottomSpacer(requestingElement?: CardElement): void;
	    render(): HTMLElement;
	    renderSpeech(): string;
	    getRootContainer(): Container;
	}
	export class Column extends Container {
	    weight: number;
	    protected readonly cssClassName: string;
	    adjustLayout(element: HTMLElement): void;
	}
	export class ColumnSet extends CardElement {
	    static TypeName: string;
	    private _columns;
	    readonly columns: Array<Column>;
	    render(): HTMLElement;
	    renderSpeech(): string;
	}
	export interface IVersion {
	    major: number;
	    minor: number;
	}
	export interface IRenderOptions {
	    actionShowCardInPopup: boolean;
	    defaultActionButtonStyle: Enums.ActionButtonStyle;
	    defaultSeparation: Enums.Separation;
	    supportedElementTypes: any[];
	    supportedActionTypes: any[];
	    supportsNestedActions: boolean;
	    maxActions?: number;
	}
	export class AdaptiveCard {
	    private static currentVersion;
	    static onShowPopupCard: (action: ActionShowCard, renderedCard: HTMLElement) => void;
	    static onRenderError: (error: Enums.RenderError, message: string) => void;
	    static showPopupCard(action: ActionShowCard, renderedCard: HTMLElement): void;
	    static renderOptions: IRenderOptions;
	    static raiseRenderError(error: Enums.RenderError, data: string): void;
	    private _root;
	    onExecuteAction: (action: ActionExternal) => void;
	    minVersion: IVersion;
	    fallbackText: string;
	    readonly root: Container;
	    executeAction(action: ActionExternal): void;
	    render(): HTMLElement;
	    renderSpeech(): string;
	}

}
declare module 'adaptive-card-html-renderer/Adaptive' {
	export * from 'adaptive-card-html-renderer/CardElements';
	export * from 'adaptive-card-html-renderer/Enumerations';

}
declare module 'adaptive-card-html-renderer/JsonParser' {
	import * as Adaptive from 'adaptive-card-html-renderer/CardElements';
	export class JsonParser {
	    private _card;
	    private parseBaseAction(json, action);
	    private parseExternalAction(json, action);
	    private parseActionOpenUrl(json, action);
	    private parseActionHttp(json, action);
	    private parseActionSubmit(json, action);
	    private parseActionShowCard(json, action, parentContainer);
	    private createAction(json, container);
	    private parseCardElement(json, cardElement);
	    private parseTextBlock(json, textBlock);
	    private parseImage(json, image);
	    private parseImageSet(json, imageSet);
	    private parseFactSet(json, factSet);
	    private parseActionCollection(json, actions);
	    private parseContainer(json, container, itemsCollectionPropertyName);
	    private parseColumn(json, column);
	    private parseColumnSet(json, columnSet);
	    private parseInput(json, input);
	    private parseInputText(json, input);
	    private parseInputNumber(json, input);
	    private parseInputDate(json, input);
	    private parseInputTime(json, input);
	    private parseInputToggle(json, input);
	    private parseInputChoiceSet(json, input);
	    private createCardElement(json, container);
	    parse(json: any): Adaptive.AdaptiveCard;
	}

}
declare module 'adaptive-card-html-renderer/Schema' {
	export interface IActionBase extends ITypedElement {
	    speak?: string;
	    title: string;
	}
	export interface IActionHttp extends IActionBase {
	    body?: string;
	    headers?: any;
	    method?: string;
	    url: string;
	}
	export interface IActionOpenUrl extends IActionBase {
	    url: string;
	}
	export interface IActionShowCard extends IActionBase {
	    card: ICard;
	}
	export interface IActionSubmit extends IActionBase {
	    data?: any;
	}
	export interface ICard extends ITypedElement {
	    actions?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit)[];
	    backgroundImage?: string;
	    body?: (ITextBlock | IImage | IImageSet | IFactSet | IContainer | IColumnSet | IInputDate | IInputNumber | IInputText | IInputTime | IInputToggle)[];
	    speak?: string;
	    title?: string;
	}
	export interface ICardElement extends ITypedElement {
	    speak?: string;
	}
	export interface IColumn extends IContainer {
	    size?: string;
	}
	export interface IColumnSet extends ICardElement {
	    columns: IColumn[];
	}
	export interface IContainerBase extends ICardElement {
	    actions?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit)[];
	    items?: (ITextBlock | IImage | IImageSet | IFactSet | IContainer | IColumnSet | IInputDate | IInputNumber | IInputText | IInputTime | IInputToggle)[];
	    selectAction?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit);
	    startGroup?: boolean;
	}
	export interface IContainer extends IContainerBase {
	}
	export interface IFact {
	    title: string;
	    speak?: string;
	    value: string;
	}
	export interface IFactSet extends ICardElement {
	    facts: IFact[];
	}
	export interface IImage extends ICardElement {
	    altText?: string;
	    horizontalAlignment?: HorizontalAlignment;
	    selectAction?: IActionBase;
	    size?: ImageSize;
	    style?: ImageStyle;
	    url: string;
	}
	export interface IImageSet extends ICardElement {
	    images: IImage[];
	    size?: ImageSize;
	}
	export interface IInput extends ICardElement {
	    id: string;
	}
	export interface IInputDate extends IInput {
	    max?: string;
	    min?: string;
	    placeholder?: string;
	    value?: string;
	}
	export interface IInputNumber extends IInput {
	    max?: string;
	    min?: string;
	    placeholder?: string;
	    value?: string;
	}
	export interface IInputText extends IInput {
	    isMultiline?: boolean;
	    maxLength?: number;
	    style?: TextInputStyle;
	    placeholder?: string;
	    value?: string;
	}
	export interface IInputTime extends IInput {
	    max?: string;
	    min?: string;
	    placeholder?: string;
	    value?: string;
	}
	export interface IInputToggle extends IInput {
	    title: string;
	    value?: string;
	    valueOn?: string;
	    valueOff?: string;
	}
	export interface ITextBlock extends ICardElement {
	    color?: TextColor;
	    horizontalAlignment?: HorizontalAlignment;
	    isSubtle?: boolean;
	    maxLines?: number;
	    size?: TextSize;
	    text: string;
	    weight?: TextWeight;
	    wrap?: boolean;
	}
	export interface ITypedElement {
	    type: string;
	}
	export type HorizontalAlignment = "left" | "center" | "right";
	export type ImageSize = "auto" | "stretch" | "small" | "medium" | "large";
	export type ImageStyle = "normal" | "person";
	export type TextColor = "default" | "dark" | "light" | "accent" | "good" | "warning" | "attention";
	export type TextInputStyle = "text" | "tel" | "url" | "email";
	export type TextSize = "small" | "normal" | "medium" | "large" | "extraLarge";
	export type TextWeight = "lighter" | "normal" | "bolder";
	export class TypedElement implements ITypedElement {
	    constructor(type: string);
	    type: string;
	}
	export class Card extends TypedElement implements ICard {
	    constructor(init?: Partial<ICard>);
	    actions?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit)[];
	    backgroundImage?: string;
	    body?: (ITextBlock | IImage | IImageSet | IFactSet | IContainer | IColumnSet | IInputDate | IInputNumber | IInputText | IInputTime | IInputToggle)[];
	    speak?: string;
	    title?: string;
	}
	export class ActionBase extends TypedElement implements IActionBase {
	    constructor(type: string, init?: Partial<IActionBase>);
	    speak?: string;
	    title: string;
	}
	export class ActionHttp extends ActionBase implements IActionHttp {
	    constructor(init?: Partial<IActionHttp>);
	    body?: string;
	    headers?: any;
	    method?: string;
	    url: string;
	}
	export class ActionOpenUrl extends ActionBase implements IActionOpenUrl {
	    constructor(init?: Partial<IActionOpenUrl>);
	    url: string;
	}
	export class ActionShowCard extends ActionBase implements IActionShowCard {
	    constructor(init?: Partial<IActionShowCard>);
	    card: ICard;
	}
	export class ActionSubmit extends ActionBase implements IActionSubmit {
	    constructor(init?: Partial<IActionSubmit>);
	    data?: any;
	}
	export class CardElement extends TypedElement implements ICardElement {
	    constructor(type: string, init?: Partial<ICardElement>);
	    speak?: string;
	}
	export class ColumnSet extends CardElement implements IColumnSet {
	    constructor(init?: Partial<IColumnSet>);
	    columns: IColumn[];
	}
	export class ContainerBase extends CardElement implements IContainerBase {
	    constructor(type: string, init?: Partial<IContainerBase>);
	    actions?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit)[];
	    items?: (ITextBlock | IImage | IImageSet | IFactSet | IContainer | IColumnSet | IInputDate | IInputNumber | IInputText | IInputTime | IInputToggle)[];
	    selectAction?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit);
	    startGroup?: boolean;
	}
	export class Container extends ContainerBase implements IContainer {
	    constructor(init?: Partial<IContainer>);
	}
	export class Column extends ContainerBase implements IColumn {
	    constructor(init?: Partial<IColumn>);
	    size?: string;
	}
	export class Fact implements IFact {
	    constructor(init?: Partial<IFact>);
	    title: string;
	    speak?: string;
	    value: string;
	}
	export class FactSet extends CardElement implements IFactSet {
	    constructor(init?: Partial<IFactSet>);
	    facts: IFact[];
	}
	export class Image extends CardElement implements IImage {
	    constructor(init?: Partial<IImage>);
	    altText?: string;
	    horizontalAlignment?: HorizontalAlignment;
	    selectAction?: IActionBase;
	    size?: ImageSize;
	    style?: ImageStyle;
	    url: string;
	}
	export class ImageSet extends CardElement implements IImageSet {
	    constructor(init?: Partial<IImageSet>);
	    images: IImage[];
	    size?: ImageSize;
	}
	export class Input extends CardElement implements IInput {
	    constructor(type: string, init?: Partial<IInput>);
	    id: string;
	}
	export class InputDate extends Input implements IInputDate {
	    constructor(init?: Partial<IInputDate>);
	    max?: string;
	    min?: string;
	    placeholder?: string;
	    value?: string;
	}
	export class InputNumber extends Input implements IInputNumber {
	    constructor(init?: Partial<IInputNumber>);
	    max?: string;
	    min?: string;
	    placeholder?: string;
	    value?: string;
	}
	export class InputText extends Input implements IInputText {
	    constructor(init?: Partial<IInputText>);
	    isMultiline?: boolean;
	    maxLength?: number;
	    style?: TextInputStyle;
	    placeholder?: string;
	    value?: string;
	}
	export class InputTime extends Input implements IInputTime {
	    constructor(init?: Partial<IInputTime>);
	    max?: string;
	    min?: string;
	    placeholder?: string;
	    value?: string;
	}
	export class InputToggle extends Input implements IInputToggle {
	    constructor(init?: Partial<IInputToggle>);
	    title: string;
	    value?: string;
	    valueOn?: string;
	    valueOff?: string;
	}
	export class TextBlock extends TypedElement implements ITextBlock {
	    constructor(init?: Partial<ITextBlock>);
	    color?: TextColor;
	    horizontalAlignment?: HorizontalAlignment;
	    isSubtle?: boolean;
	    maxLines?: number;
	    size?: TextSize;
	    text: string;
	    weight?: TextWeight;
	    wrap?: boolean;
	}

}
