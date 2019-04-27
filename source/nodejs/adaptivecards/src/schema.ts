// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export type Size = "auto" | "stretch" | "small" | "medium" | "large";
export type TextSize  = "small" | "default" | "medium" | "large" | "extraLarge";
export type HorizontalAlignment = "left" | "center" | "right";
export type VerticalAlignment = "top" | "center" | "bottom";
export type Spacing = "none" | "small" | "default" | "medium" | "large" | "extraLarge" | "padding";
export type TextWeight = "lighter" | "default" | "bolder";
export type TextColor = "default" | "dark" | "light" | "accent" | "good" | "warning" | "attention";
export type ContainerStyle = "default" | "emphasis";
export type ImageStyle = "default" | "person";

export interface IAction {
    id: string;
    title?: string;
}

export interface ISubmitAction extends IAction {
    type: "Action.Submit";
    data?: any;
}

export interface IOpenUrlAction extends IAction {
    type: "Action.OpenUrl";
    url: string;
}

export interface IShowCardAction extends IAction {
    type: "Action.ShowCard";
    card: IAdaptiveCard;
}

export interface ICardElement {
    id?: string;
    speak?: string;
    horizontalAlignment?: HorizontalAlignment;
    spacing?: Spacing;
    separator?: boolean;
    height?: "auto" | "stretch";
    [propName: string]: any;
}

export interface IBackgroundImage {
    url: string;
}

export interface ITextBlock extends ICardElement {
    type: "TextBlock";
    size?: TextSize;
    weight?: TextWeight;
    color?: TextColor;
    text: string;
    isSubtle?: boolean;
    wrap?: boolean;
    maxLines?: number;
}

export interface IContainer extends ICardElement {
    type: "Container";
    backgroundImage?: IBackgroundImage | string;
    style?: ContainerStyle;
    verticalContentAlignment?: VerticalAlignment;
    selectAction?: IAction;
    items?: ICardElement[];
}

export interface IColumn extends ICardElement {
    backgroundImage?: IBackgroundImage | string;
    style?: ContainerStyle;
    verticalContentAlignment?: VerticalAlignment;
    selectAction?: IAction;
    items?: ICardElement[];
    width?: number | "auto" | "stretch" | "auto";
}

export interface IColumnSet extends ICardElement {
    type: "ColumnSet";
    columns: IColumn[];
}

export interface IFact {
    title: string;
    value: string;
    speak?: string;
}

export interface IFactSet extends ICardElement {
    type: "FactSet";
    facts: IFact[];
}

export interface IImage extends ICardElement {
    type: "Image";
    altText?: string;
    selectAction?: IAction;
    size?: Size;
    style?: ImageStyle;
    url: string;
}

export interface IImageSet extends ICardElement {
    type: "ImageSet";
    images: IImage[];
    size?: Size;
}

export interface IInput extends ICardElement {
    id: string;
    value?: string;
}

export interface IDateInput extends IInput {
    type: "Input.Date";
    min?: string;
    max?: string;
    placeholder?: string;
}

export interface ITimeInput extends IInput {
    type: "Input.Time";
    min?: string;
    max?: string;
    placeholder?: string;
}

export interface INumberInput extends IInput {
    type: "Input.Number";
    min?: number;
    max?: number;
    placeholder?: string;
}

export interface ITextInput extends IInput {
    type: "Input.Text";
    isMultiline?: boolean;
    maxLength?: number;
    placeholder?: string;
}

export interface IToggleInput extends IInput {
    type: "Input.Toggle";
    title: string;
    valueOn?: string;
    valueOff?: string;
}

export interface IChoice {
    title: string;
    value: string;
}

export interface IChoiceSetInput extends IInput {
    type: "Input.ChoiceSet";
    isMultiSelect?: boolean;
    style?: "expanded" | "compact";
    placeholder?: string;
    choices: IChoice[];
}

export interface IVersion {
    major: number;
    minor: number;
}

export interface IAdaptiveCard extends ICardElement {
    type: "AdaptiveCard";
    version?: IVersion | string;
    backgroundImage?: IBackgroundImage | string;
    body?: (ITextBlock | IImage | IImageSet | IFactSet | IColumnSet | IContainer)[];
    actions?: (ISubmitAction | IOpenUrlAction | IShowCardAction)[];
    speak?: string;
}
