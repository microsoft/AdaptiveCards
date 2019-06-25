// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as ReactDOM from "react-dom";
import * as AC from "adaptivecards";

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

export abstract class ReactInputElement extends AC.Input {

    public value: any;
    protected abstract renderReact(): JSX.Element;

    protected internalRender(): HTMLElement {
        this.inputControlContainerElement.style.display = "block";
        return sharedInternalRender(this.renderReact);
    }

    protected handleChange = (event: React.FormEvent<HTMLInputElement | HTMLTextAreaElement>, newValue?: string) => {
        this.value = newValue;
    }
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
