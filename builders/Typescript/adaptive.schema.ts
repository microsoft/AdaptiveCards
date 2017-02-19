
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
    name: string;
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
    public constructor(type: string) {
        this.type = type;
    }

    type: string;
}

export class AdaptiveCard extends TypedElement implements ICard {
    public constructor(el: ICard = null) {
        super("AdaptiveCard");
        if (el) {
            this.actions = (el.actions) ? el.actions : new Array();
            this.backgroundImage = el.backgroundImage;
            this.body = (el.body) ? el.body : new Array();
            this.speak = el.speak;
            this.title = el.title;
        }
    }

    actions?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit)[];
    backgroundImage?: string;
    body?: (ITextBlock | IImage | IImageSet | IFactSet | IContainer | IColumnSet | IInputDate | IInputNumber | IInputText | IInputTime | IInputToggle)[];
    speak?: string;
    title?: string;
}

export class ActionBase extends TypedElement implements IActionBase {
    public constructor(type: string, el: IActionBase = null) {
        super(type);
        if (el) {
            this.speak = el.speak;
            this.title = el.title;
        }
    }

    speak?: string;
    title: string;
}

export class ActionHttp extends ActionBase implements IActionHttp {
    public constructor(el: IActionHttp = null) {
        super("Action.Http", el);
        if (el) {
            this.body = el.body;
            this.headers = el.headers;
            this.method = el.method;
            this.url = el.url;
        }
    }
    body?: string;
    headers?: any;
    method?: string;
    url: string;
}

export class ActionOpenUrl extends ActionBase implements IActionOpenUrl {
    public constructor(el: IActionOpenUrl = null) {
        super("Action.OpenUrl", el);
        if (el) {
            this.url = el.url;
        }
    }
    url: string;
}

export class ActionShowCard extends ActionBase implements IActionShowCard {
    public constructor(el: IActionShowCard = null) {
        super("Action.ShowCard", el);
        if (el)
            this.card = el.card;
        else
            this.card = new AdaptiveCard(null);
    }
    card: ICard;
}

export class ActionSubmit extends ActionBase implements IActionSubmit {
    public constructor(el: IActionSubmit = null) {
        super("Action.ShowCard", el);
        if (el)
            this.data = el.data;
    }
    data?: any;
}


export class CardElement extends TypedElement implements ICardElement {
    public constructor(type: string, el: ICardElement = null) {
        super(type);
        if (el) {
            this.speak = el.speak;
        }
    }
    speak?: string;
}


export class ColumnSet extends CardElement implements IColumnSet {
    public constructor(el: IColumnSet = null) {
        super("ColumnSet", el);
        this.columns = [];
        if (el) {
            this.columns = el.columns ? el.columns : [];
        }
    }
    columns: IColumn[];
}

class ContainerBase extends CardElement implements IContainerBase {
    public constructor(type:string, el: IContainer = null) {
        super(type, el);
        this.items = [];
        if (el) {
            this.actions = (el.actions) ? el.actions : [];
            this.items = el.items ? el.items : [];
            this.selectAction = el.selectAction
            this.startGroup = el.startGroup;
        }
    }
    actions?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit)[];
    items?: (ITextBlock | IImage | IImageSet | IFactSet | IContainer | IColumnSet | IInputDate | IInputNumber | IInputText | IInputTime | IInputToggle)[];;
    selectAction?: (IActionHttp | IActionOpenUrl | IActionShowCard | IActionSubmit);
    startGroup?: boolean;
}

export class Container extends ContainerBase implements IContainer {
    public constructor(el: IContainer = null) {
        super("Container", el);
        this.items = [];
        if (el) {
            this.actions = (el.actions) ? el.actions : [];
            this.items = el.items ? el.items : [];
            this.selectAction = el.selectAction
            this.startGroup = el.startGroup;
        }
    }
}

export class Column extends ContainerBase implements IColumn {
    public constructor(el: IColumn = null) {
        super("Column",el);
        if (el) {
            this.size = el.size;
        }
    }

    size?: string;
}

export class Fact implements IFact {
    public constructor(el: IFact = null) {
        if (el) {
            this.name = el.name;
            this.speak = el.speak;
            this.value = el.value;
        }
    }
    name: string;
    speak?: string;
    value: string;
}

export class FactSet extends CardElement implements IFactSet {
    public constructor(el: IFactSet = null) {
        super("FactSet");
        this.facts = [];
        if (el) {
            this.facts = el.facts ? el.facts : [];
        }
    }

    facts: IFact[];
}

export class Image extends CardElement implements IImage {
    public constructor(el: IImage = null) {
        super("Image");
        if (el) {
            this.altText = el.altText;
            this.horizontalAlignment = el.horizontalAlignment;
            this.selectAction = el.selectAction;
            this.size = el.size;
            this.style = el.style;
            this.url = el.url;
        }
    }

    altText?: string;
    horizontalAlignment?: HorizontalAlignment;
    selectAction?: IActionBase;
    size?: ImageSize;
    style?: ImageStyle;
    url: string;
}

export class ImageSet extends CardElement implements IImageSet {
    public constructor(el: IImageSet = null) {
        super("ImageSet");
        this.images = [];
        if (el) {
            this.images = el.images ? el.images : [];
            this.size = el.size;
        }
    }
    images: IImage[];
    size?: ImageSize;
}

export class Input extends CardElement implements IInput {
    public constructor(type: string, el: IInput = null) {
        super(type);
        if (el) {
            this.id = el.id;
        }
    }
    id: string;
}

export class InputDate extends Input implements IInputDate {
    public constructor(el: IInputDate = null) {
        super("Input.Date", el);
        if (el) {
            this.max = el.max;
            this.min = el.min;
            this.placeholder = el.placeholder;
            ; this.value = el.value;
        }
    }
    max?: string;
    min?: string;
    placeholder?: string;
    value?: string;
}

export class InputNumber extends Input implements IInputNumber {
    public constructor(el: IInputNumber = null) {
        super("Input.Number");
        if (el) {
            this.max = el.max;
            this.min = el.min;
            this.placeholder = el.placeholder;
            this.value = el.value;
        }
    }
    max?: string;
    min?: string;
    placeholder?: string;
    value?: string;
}

export class InputText extends Input implements IInputText {
    public constructor(el: IInputText = null) {
        super("Input.Text");
        if (el) {
            this.isMultiline = el.isMultiline;
            this.maxLength = el.maxLength;
            this.style = el.style;
            this.placeholder = el.placeholder;
            this.value = el.value;
        }
    }
    isMultiline?: boolean;
    maxLength?: number;
    style?: TextInputStyle;
    placeholder?: string;
    value?: string;
}

export class InputTime extends Input implements IInputTime {
    public constructor(el: IInputTime = null) {
        super("Input.Time");
        if (el) {
            this.max = el.max;
            this.min = el.min;
            this.placeholder = el.placeholder;
            this.value = el.value;
        }
    }
    max?: string;
    min?: string;
    placeholder?: string;
    value?: string;
}

export class InputToggle extends Input implements IInputToggle {
    public constructor(el: IInputToggle = null) {
        super("Input.Toggle");
        if (el) {
            this.title = el.title;
            this.value = el.value;
            this.valueOn = el.valueOn;
            this.valueOff = el.valueOff;
        }
    }
    title: string;
    value?: string;
    valueOn?: string;
    valueOff?: string;
}
export class TextBlock extends TypedElement implements ITextBlock {
    public constructor(tb?: ITextBlock = null) {
        super("TextBlock");
        this.text = "";
        if (tb) {
            this.color = tb.color;
            this.horizontalAlignment = tb.horizontalAlignment;
            this.isSubtle = tb.isSubtle;
            this.size = tb.size;
            this.maxLines = tb.maxLines;
            this.text = tb.text;
            this.wrap = tb.wrap;
        }
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
