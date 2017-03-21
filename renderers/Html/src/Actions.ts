import { CardElement, ICard, IContainer } from "./Interfaces";
import { Renderer } from "./Renderer";
import { InputBase } from "./Inputs";
import * as Utils from "./Utils";


export abstract class Action {
    private _owner: CardElement;

    title: string;

    static create(owner: CardElement, typeName: string): Action {
        switch (typeName) {
            case "Action.OpenUri":
                return new ActionOpenUri(owner);
            case "Action.Submit":
                return new ActionSubmit(owner);
            case "Action.Http":
                return new ActionHttp(owner);
            case "Action.ShowCard":
                return new ActionShowCard(owner);
            default:
                throw new Error("Unknown action type: " + typeName);
        }
    }

    get owner(): CardElement {
        return this._owner;
    }

    constructor(owner: CardElement) {
        this._owner = owner;
    }

    parse(json: any) {
        this.title = json["title"];
    }

    get hasUi(): boolean {
        return false;
    }
}

export class ActionOpenUri extends Action {

    public url : string;

    parse(json: any) {
        super.parse(json);

        this.url = json["url"];
    }
}

export class ActionShowCard extends Action {
    card: ICard;

    parse(json: any) {
        super.parse(json);

        if (json["card"] != undefined) {
            // TODO: UNCOMMENT THIS
            // TODO: This should inspect the type to construct the right type of card

            var renderer = new Renderer();
            this.card = renderer.parseCard(json["card"]);
        }
    }
}


export class ActionSubmit extends Action {
    data: any;
    inputs: Array<InputBase> = new Array<InputBase>();

    parse(json: any) {
        super.parse(json);


        if (json["inputs"] != undefined) {
            let inputArray = json["inputs"] as Array<any>;

            for (let i = 0; i < inputArray.length; i++) {
                //let input = InputBase.createInput(this.owner.container, inputArray[i]["type"]);

                //input.parse(inputArray[i]);

                //this.inputs.push(input);
            }
        }
    }
}


// TODO: Should we remove this and use SubmitAction?
export class ActionHttp extends Action {
    url: string;
    method:string;
    body: string;
    headers: string;

    parse(json: any) {
        super.parse(json);

        this.url = json["url"];
        this.body = json["body"];
        this.method = json["method"];
        this.headers = json["headers"];
    }
}

export enum ActionButtonStyle {
    Link,
    Push
}

export enum ActionButtonState {
    Normal,
    Expanded,
    Subdued
}

export class ActionButton {
    private _action: Action;
    private _style: ActionButtonStyle;
    private _onClick: Utils.EventDispatcher<ActionButton, void> = new Utils.EventDispatcher<ActionButton, void>();
    private _element: HTMLElement = null;
    private _state: ActionButtonState = ActionButtonState.Normal;
    private _text: string;

    private click() {
        this._onClick.dispatch(this, null);
    }

    private updateCssStyle() {
        let cssStyle = this._style == ActionButtonStyle.Link ? "linkButton " : "pushButton ";

        switch (this._state) {
            case ActionButtonState.Expanded:
                cssStyle += " expanded";
                break;
            case ActionButtonState.Subdued:
                cssStyle += " subdued";
                break;
        }

        this._element.className = cssStyle;
    }

    constructor(action: Action, style: ActionButtonStyle) {
        this._action = action;
        this._style = style;
        this._element = document.createElement("div");
        this._element.onclick = (e) => { this.click(); };

        this.updateCssStyle();
    }

    get action() {
        return this._action;
    }

    get onClick(): Utils.IEvent<ActionButton, void> {
        return this._onClick;
    }

    get text(): string {
        return this._text;
    }

    set text(value: string) {
        this._text = value;
        this._element.innerText = this._text;
    }

    get element(): HTMLElement {
        return this._element;
    }

    get state(): ActionButtonState {
        return this._state;
    }

    set state(value: ActionButtonState) {
        this._state = value;

        this.updateCssStyle();
    }
}


export class ActionBar extends CardElement {
    static buttonStyle: ActionButtonStyle = ActionButtonStyle.Push;
    
    constructor(container: IContainer) {
        super(container);
    }

    private _actionButtons: Array<ActionButton> = [];
    private _actionCardContainer: HTMLDivElement;
    private _actions: Array<Action> = [];
    private _expandedAction: Action = null;

    // private hideActionCardPane() {
    //     this._actionCardContainer.innerHTML = '';
    //     this._actionCardContainer.style.padding = "0px";
    //     this._actionCardContainer.style.marginTop = "0px";

    //     this.container.showBottomSpacer(this);
    // }

    // private showActionCardPane(action: Action) {
    //     this.container.hideBottomSpacer(this);

    //     this._actionCardContainer.innerHTML = '';
    //     this._actionCardContainer.style.padding = null;
    //     this._actionCardContainer.style.marginTop = this._actions.length > 1 ? null : "0px";

    //     Utils.appendChild(
    //         this._actionCardContainer,
    //         action.renderUi(this.container, this._actions.length > 1));
    // }

    // private actionClicked(actionButton: ActionButton) {
    //     if (!actionButton.action.hasUi) {
    //         for (var i = 0; i < this._actionButtons.length; i++) {
    //             this._actionButtons[i].state = ActionButtonState.Normal;
    //         }

    //         this.hideActionCardPane();

    //         alert("Executing action " + actionButton.text)
    //     }
    //     else {
    //         if (actionButton.action === this._expandedAction) {
    //             for (var i = 0; i < this._actionButtons.length; i++) {
    //                 this._actionButtons[i].state = ActionButtonState.Normal;
    //             }

    //             this._expandedAction = null;

    //             this.hideActionCardPane();
    //         }
    //         else {
    //             for (var i = 0; i < this._actionButtons.length; i++) {
    //                 if (this._actionButtons[i] !== actionButton) {
    //                     this._actionButtons[i].state = ActionButtonState.Subdued;
    //                 }
    //             }

    //             actionButton.state = ActionButtonState.Expanded;

    //             this._expandedAction = actionButton.action;

    //             this.showActionCardPane(actionButton.action);
    //         }
    //     }
    // }

    get actions(): Array<Action> {
        return this._actions;
    }

    get hideOverflow(): boolean {
        return false;
    }

    parse(json: any) {
        super.parse(json);
        var actions = json["actions"];

        if (actions != null) {
            var actionArray = actions as Array<any>;

            for (var i = 0; i < actionArray.length; i++) {
                let action = Action.create(this, actionArray[i]["type"]);

                action.parse(actionArray[i]);

                this._actions.push(action);
            }
        }
    }

    render(): HTMLElement {
        let element = document.createElement("div");
        element.className = "actionGroup";

        let buttonStrip = document.createElement("div");
        buttonStrip.className = "buttonStrip";

        this._actionCardContainer = document.createElement("div");
        this._actionCardContainer.className = "actionCardContainer";
        this._actionCardContainer.style.padding = "0px";
        this._actionCardContainer.style.marginTop = "0px";

        // if (this._actions.length == 1 && this._actions[0] instanceof ActionCard) {
        //     this.showActionCardPane(this._actions[0]);
        // }
        if (false) {

        }
        else {
            for (let i = 0; i < this._actions.length; i++) {
                let buttonStripItem = document.createElement("div");
                buttonStripItem.className = "buttonStripItem";

                let actionButton = new ActionButton(this._actions[i], ActionBar.buttonStyle);
                actionButton.text = this._actions[i].title;

                actionButton.onClick.subscribe(
                    (ab, args) => {
                        //this.actionClicked(ab);
                    });

                this._actionButtons.push(actionButton);

                if (i < this._actions.length - 1) {
                    buttonStripItem.className += " buttonStripItemSpacer";
                }

                Utils.appendChild(buttonStripItem, actionButton.element);
                Utils.appendChild(buttonStrip, buttonStripItem);
            }
        }

        Utils.appendChild(element, buttonStrip);
        Utils.appendChild(element, this._actionCardContainer);

        return element;
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';

        return null;
    }
}