// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as ReactDOM from "react-dom";
import * as AC from "adaptivecards";
import { Button, IconButton, IconType, PrimaryButton, IStyle } from "@fluentui/react";

export const getDiv = (): HTMLDivElement => document.createElement("div");

const sharedInternalRender = (renderReact: () => JSX.Element): HTMLElement => {
    const div = getDiv();
    ReactDOM.render(renderReact(), div);
    return div;
};

export abstract class ReactCardElement extends AC.CardElement {

    protected abstract renderReact(): JSX.Element;

    protected internalRender(): HTMLElement {
        return sharedInternalRender(this.renderReact);
    }
}

export abstract class ReactCardElementContainer extends AC.Container {

    protected abstract renderReact(): JSX.Element;

    protected internalRender(): HTMLElement {
        return sharedInternalRender(this.renderReact);
    }
}

const inlineButtonRootStyle: IStyle = {
    marginLeft: 8,
};

export abstract class ReactInputElement extends AC.Input {

    private _value: string;
    private _inlineAction: AC.Action;
    protected abstract renderReact(): JSX.Element;

    protected internalRender(): HTMLElement {
        const element = sharedInternalRender(this.renderReact);
        element.style.width = "100%";
        return element;
    }

    protected overrideInternalRender(): HTMLElement {
        let inputControl = super.overrideInternalRender();

        if (this._inlineAction) {
            this.inputControlContainerElement.appendChild(this.buildInlineActionButton());
        }
        return inputControl;
    }

    protected handleChange = (event: React.FormEvent<HTMLInputElement | HTMLTextAreaElement>, newValue?: string) => {
        this._value = newValue;
    }

    get value(): string {
        return this._value;
    }

    set value(value: string) {
        this._value = value;
    }

    get inlineAction(): AC.Action {
        return this._inlineAction;
    }

    set inlineAction(action: AC.Action) {
        this._inlineAction = action;

        if (this._inlineAction) {
            this._inlineAction.setParent(this);
        }
    }

    private buildInlineActionButton = (): HTMLElement => {
        return sharedInternalRender(
            AC.isNullOrEmpty(this.inlineAction.iconUrl) ?
                this.buildTextOnlyInlineActionActionButton :
                this.inlineIconActionButton);
    }

    private inlineActionClickHandler = (e: React.MouseEvent<Button>): void => {
        e.stopPropagation();
        e.preventDefault();
        this._inlineAction.execute();
    }

    private inlineIconActionButton = (): JSX.Element => (
        <IconButton
            default={true}
            text={this._inlineAction.title}
            className={this.hostConfig.makeCssClassName("ac-inlineActionButton", "iconOnly")}
            styles={{
                icon: {
                    height: `100%`,
                },
                root: inlineButtonRootStyle,
            }}
            iconProps={{
                iconType: IconType.image,
                imageProps: {
                    height: "100%",
                    src: this._inlineAction.iconUrl,
                },
            }}
            onClick={this.inlineActionClickHandler}
        />
    )

    private buildTextOnlyInlineActionActionButton = (): JSX.Element => (
        <PrimaryButton
            className={this.hostConfig.makeCssClassName("ac-inlineActionButton", "textOnly")}
            text={this._inlineAction.title}
            onClick={this.inlineActionClickHandler}
            styles={{
                root: inlineButtonRootStyle,
            }}
        />
    )
}

export const raiseParseError = (error: AC.IValidationError, errors: Array<AC.IValidationError>) => {
    if (errors) {
        errors.push(error);
    }

    if (AC.AdaptiveCard.onParseError != null) {
        AC.AdaptiveCard.onParseError(error);
    }
};

export const getIntValue = (val: any, errors?: AC.IValidationError[], defaultValue: number = undefined): number => {
    try {
        return val ? parseInt(val, 10) : defaultValue;
    } catch (error) {
        raiseParseError({
            error: AC.ValidationError.InvalidPropertyValue,
            message: error,
        }, errors);
    }
};
