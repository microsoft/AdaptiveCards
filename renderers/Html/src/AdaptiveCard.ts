import * as Utils from "./Utils";
import { ActionBar, Action, ActionButton, ActionButtonStyle } from "./Actions";
import { Size, TextSize, TextColor, TextWeight, HorizontalAlignment, ImageStyle } from "./Enums";
import { CardElement, IContainer, ICard } from "./Interfaces";
import { Container } from "./Elements";

import * as markdownIt from "markdown-it";
let markdownProcessor = new markdownIt();

export function processMarkdown(text: string): any {
    return markdownProcessor.render(text);
}

export class AdaptiveCard implements ICard {

    private _body = new Container(null, null, "body");
    private _actions: ActionBar = new ActionBar(this.body);
    private _onClick: Utils.EventDispatcher<AdaptiveCard, Action> = new Utils.EventDispatcher<AdaptiveCard, Action>();

    OnAction(): Utils.IEvent<ICard, Action> {
        return this._onClick;
    }

    get body() {
        return this._body;
    }

    get actions() {
        return this._actions;
    }

    parse(json: any) {
        this.body.parse(json);
        this.actions.parse(json);
    }

    render(): HTMLElement {
        let renderedContainer = this.body.internalRender();
        renderedContainer.className = "rootContainer";

        if (this.actions) {
            let actionsBar = this.actions.render();

            Utils.appendChild(renderedContainer, actionsBar);
        }

        return renderedContainer;
    }

    renderSpeech(): string {
        return this.body.renderSpeech();
    }
}

