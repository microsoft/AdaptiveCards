import { HorizontalAlignment, Spacing } from "./adaptivecards";


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
    card: IAdaptiveCard;
}
export interface IActionSubmit extends IActionBase {
    data?: any;
}
export interface IVersion {
    major: number;
    minor: number;
    
}
export interface IBackgroundImage {
    url: string;    
}
export interface IAdaptiveCard extends ITypedElement {
    type: string;
    version?: IVersion | string;
    backgroundImage?: IBackgroundImage | string;
    body?: (any)[];
    actions?: (IActionBase)[];    
    speak?: string;
    [propName: string]: any;
}
export interface ICardElement extends ITypedElement {
    type: string,
    id?: string;
    horizontalAlignment?: HorizontalAlignment;
    spacing?: Spacing;
    separator?: boolean;
    [propName: string]: any;    
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

export type ImageSize = "auto" | "stretch" | "small" | "medium" | "large";
export type ImageStyle = "normal" | "person";
export type TextColor = "default" | "dark" | "light" | "accent" | "good" | "warning" | "attention";
export type TextInputStyle = "text" | "tel" | "url" | "email";
export type TextSize = "small" | "normal" | "medium" | "large" | "extraLarge";
export type TextWeight = "lighter" | "normal" | "bolder";

export class TypedElement implements ITypedElement {
    public constructor(type: string) {
        this.type = type;
    }

    type: string;
}

export class Card extends TypedElement implements IAdaptiveCard {
    public constructor(init?: Partial<IAdaptiveCard>) {
        super("AdaptiveCard");
        Object.assign(this, init);
        if (!this.actions)
            this.actions = [];
        if (!this.body)
            this.body = [];
    }

    actions?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit)[];
    backgroundImage?: string;
    body?: (ITextBlock | IImage | IImageSet | IFactSet | IContainer | IColumnSet | IInputDate | IInputNumber | IInputText | IInputTime | IInputToggle)[];
    speak?: string;
    title?: string;
}

export class ActionBase extends TypedElement implements IActionBase {
    public constructor(type: string, init?: Partial<IActionBase>) {
        super(type);
        Object.assign(this, init);
    }

    speak?: string;
    title: string;
}

export class ActionHttp extends ActionBase implements IActionHttp {
    public constructor(init?: Partial<IActionHttp>) {
        super("Action.Http", init);
        Object.assign(this, init);
    }
    body?: string;
    headers?: any;
    method?: string;
    url: string;
}

export class ActionOpenUrl extends ActionBase implements IActionOpenUrl {
    public constructor(init?: Partial<IActionOpenUrl>) {
        super("Action.OpenUrl", init);
        Object.assign(this, init);
    }
    url: string;
}

export class ActionShowCard extends ActionBase implements IActionShowCard {
    public constructor(init?: Partial<IActionShowCard>) {
        super("Action.ShowCard", init);
        Object.assign(this, init);
        if (!this.card)
            this.card = new Card(null);
    }
    card: IAdaptiveCard;
}

export class ActionSubmit extends ActionBase implements IActionSubmit {
    public constructor(init?: Partial<IActionSubmit>) {
        super("Action.ShowCard", init);
        Object.assign(this, init);
    }
    data?: any;
}


export class CardElement extends TypedElement implements ICardElement {
    public constructor(type: string, init?: Partial<ICardElement>) {
        super(type);
        Object.assign(this, init);
    }
    speak?: string;
}


export class ColumnSet extends CardElement implements IColumnSet {
    public constructor(init?: Partial<IColumnSet>) {
        super("ColumnSet", init);
        Object.assign(this, init);
        if (!this.columns)
            this.columns = [];
    }
    columns: IColumn[];
}

export class ContainerBase extends CardElement implements IContainerBase {
    public constructor(type: string, init?: Partial<IContainerBase>) {
        super(type, init);
        Object.assign(this, init);
        if (!this.items)
            this.items = [];
        if (!this.actions)
            this.actions = [];
    }
    actions?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit)[];
    items?: (ITextBlock | IImage | IImageSet | IFactSet | IContainer | IColumnSet | IInputDate | IInputNumber | IInputText | IInputTime | IInputToggle)[];;
    selectAction?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit);
    startGroup?: boolean;
}

export class Container extends ContainerBase implements IContainer {
    public constructor(init?: Partial<IContainer>) {
        super("Container", init);
        Object.assign(this, init);
    }
}

export class Column extends ContainerBase implements IColumn {
    public constructor(init?: Partial<IColumn>) {
        super("Column", init);
        Object.assign(this, init);
    }

    size?: string;
}

export class Fact implements IFact {
    public constructor(init?: Partial<IFact>) {
        Object.assign(this, init);
    }
    title: string;
    speak?: string;
    value: string;
}

export class FactSet extends CardElement implements IFactSet {
    public constructor(init?: Partial<IFactSet>) {
        super("FactSet", init);
        Object.assign(this, init);
        if (!this.facts)
            this.facts = [];
    }

    facts: IFact[];
}

export class Image extends CardElement implements IImage {
    public constructor(init?: Partial<IImage>) {
        super("Image", init);
        Object.assign(this, init);
    }

    altText?: string;
    horizontalAlignment?: HorizontalAlignment;
    selectAction?: IActionBase;
    size?: ImageSize;
    style?: ImageStyle;
    url: string;
}

export class ImageSet extends CardElement implements IImageSet {
    public constructor(init?: Partial<IImageSet>) {
        super("ImageSet");
        Object.assign(this, init);
        if (!this.images)
            this.images = [];
    }
    images: IImage[];
    size?: ImageSize;
}

export class Input extends CardElement implements IInput {
    public constructor(type: string, init?: Partial<IInput>) {
        super(type);
        Object.assign(this, init);
    }
    id: string;
}

export class InputDate extends Input implements IInputDate {
    public constructor(init?: Partial<IInputDate>) {
        super("Input.Date", init);
        Object.assign(this, init);
    }
    max?: string;
    min?: string;
    placeholder?: string;
    value?: string;
}

export class InputNumber extends Input implements IInputNumber {
    public constructor(init?: Partial<IInputNumber>) {
        super("Input.Number", init);
        Object.assign(this, init);
    }
    max?: string;
    min?: string;
    placeholder?: string;
    value?: string;
}

export class InputText extends Input implements IInputText {
    public constructor(init?: Partial<IInputText>) {
        super("Input.Text", init);
        Object.assign(this, init);
    }
    isMultiline?: boolean;
    maxLength?: number;
    style?: TextInputStyle;
    placeholder?: string;
    value?: string;
}

export class InputTime extends Input implements IInputTime {
    public constructor(init?: Partial<IInputTime>) {
        super("Input.Time", init);
        Object.assign(this, init);
    }
    max?: string;
    min?: string;
    placeholder?: string;
    value?: string;
}

export class InputToggle extends Input implements IInputToggle {
    public constructor(init?: Partial<IInputToggle>) {
        super("Input.Toggle", init);
        Object.assign(this, init);
    }
    title: string;
    value?: string;
    valueOn?: string;
    valueOff?: string;
}

export class TextBlock extends TypedElement implements ITextBlock {
    public constructor(init?: Partial<ITextBlock>) {
        super("TextBlock");
        Object.assign(this, init);
    }

    color?: TextColor;
    horizontalAlignment?: HorizontalAlignment;
    isSubtle?: boolean;
    maxLines?: number;
    size?: TextSize;
    text: string;
    weight?: TextWeight;
    wrap?: boolean;
}
