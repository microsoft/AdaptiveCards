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
    horizontalAlignment?: HorizontalAlignment;
    separation?: Separation;
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
export declare type HorizontalAlignment = "left" | "center" | "right";
export declare type ImageSize = "auto" | "stretch" | "small" | "medium" | "large";
export declare type ImageStyle = "normal" | "person";
export declare type TextColor = "default" | "dark" | "light" | "accent" | "good" | "warning" | "attention";
export declare type TextInputStyle = "text" | "tel" | "url" | "email";
export declare type TextSize = "small" | "normal" | "medium" | "large" | "extraLarge";
export declare type TextWeight = "lighter" | "normal" | "bolder";
export declare type Separation = "none" | "default" | "strong";
export declare class TypedElement implements ITypedElement {
    constructor(type: string);
    type: string;
}
export declare class Card extends TypedElement implements ICard {
    constructor(init?: Partial<ICard>);
    actions?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit)[];
    backgroundImage?: string;
    body?: (ITextBlock | IImage | IImageSet | IFactSet | IContainer | IColumnSet | IInputDate | IInputNumber | IInputText | IInputTime | IInputToggle)[];
    speak?: string;
    title?: string;
}
export declare class ActionBase extends TypedElement implements IActionBase {
    constructor(type: string, init?: Partial<IActionBase>);
    speak?: string;
    title: string;
}
export declare class ActionHttp extends ActionBase implements IActionHttp {
    constructor(init?: Partial<IActionHttp>);
    body?: string;
    headers?: any;
    method?: string;
    url: string;
}
export declare class ActionOpenUrl extends ActionBase implements IActionOpenUrl {
    constructor(init?: Partial<IActionOpenUrl>);
    url: string;
}
export declare class ActionShowCard extends ActionBase implements IActionShowCard {
    constructor(init?: Partial<IActionShowCard>);
    card: ICard;
}
export declare class ActionSubmit extends ActionBase implements IActionSubmit {
    constructor(init?: Partial<IActionSubmit>);
    data?: any;
}
export declare class CardElement extends TypedElement implements ICardElement {
    constructor(type: string, init?: Partial<ICardElement>);
    speak?: string;
}
export declare class ColumnSet extends CardElement implements IColumnSet {
    constructor(init?: Partial<IColumnSet>);
    columns: IColumn[];
}
export declare class ContainerBase extends CardElement implements IContainerBase {
    constructor(type: string, init?: Partial<IContainerBase>);
    actions?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit)[];
    items?: (ITextBlock | IImage | IImageSet | IFactSet | IContainer | IColumnSet | IInputDate | IInputNumber | IInputText | IInputTime | IInputToggle)[];
    selectAction?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit);
    startGroup?: boolean;
}
export declare class Container extends ContainerBase implements IContainer {
    constructor(init?: Partial<IContainer>);
}
export declare class Column extends ContainerBase implements IColumn {
    constructor(init?: Partial<IColumn>);
    size?: string;
}
export declare class Fact implements IFact {
    constructor(init?: Partial<IFact>);
    title: string;
    speak?: string;
    value: string;
}
export declare class FactSet extends CardElement implements IFactSet {
    constructor(init?: Partial<IFactSet>);
    facts: IFact[];
}
export declare class Image extends CardElement implements IImage {
    constructor(init?: Partial<IImage>);
    altText?: string;
    horizontalAlignment?: HorizontalAlignment;
    selectAction?: IActionBase;
    size?: ImageSize;
    style?: ImageStyle;
    url: string;
}
export declare class ImageSet extends CardElement implements IImageSet {
    constructor(init?: Partial<IImageSet>);
    images: IImage[];
    size?: ImageSize;
}
export declare class Input extends CardElement implements IInput {
    constructor(type: string, init?: Partial<IInput>);
    id: string;
}
export declare class InputDate extends Input implements IInputDate {
    constructor(init?: Partial<IInputDate>);
    max?: string;
    min?: string;
    placeholder?: string;
    value?: string;
}
export declare class InputNumber extends Input implements IInputNumber {
    constructor(init?: Partial<IInputNumber>);
    max?: string;
    min?: string;
    placeholder?: string;
    value?: string;
}
export declare class InputText extends Input implements IInputText {
    constructor(init?: Partial<IInputText>);
    isMultiline?: boolean;
    maxLength?: number;
    style?: TextInputStyle;
    placeholder?: string;
    value?: string;
}
export declare class InputTime extends Input implements IInputTime {
    constructor(init?: Partial<IInputTime>);
    max?: string;
    min?: string;
    placeholder?: string;
    value?: string;
}
export declare class InputToggle extends Input implements IInputToggle {
    constructor(init?: Partial<IInputToggle>);
    title: string;
    value?: string;
    valueOn?: string;
    valueOff?: string;
}
export declare class TextBlock extends TypedElement implements ITextBlock {
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
