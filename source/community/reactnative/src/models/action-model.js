import { BaseModel } from './base-model'
import { ElementType } from '../utils/enums'
import { ModelFactory } from './model-factory'

export class BaseActionModel extends BaseModel {
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.title = payload.title;
        this.iconUrl = payload.iconUrl;
        this.sentiment = payload.style;
        this.ignoreInputValidation = payload.ignoreInputValidation;
        this.altText = payload.altText;
        this.isEnabled = payload.isEnabled == undefined ? true : payload.isEnabled; //isEnabled defaults to true
    }
}

export class SubmitActionModel extends BaseActionModel {
    data;
    type = ElementType.ActionSubmit;
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.data = payload.data;
    }
}

export class ExecuteActionModel extends BaseActionModel {
    data;
    type = ElementType.ActionExecute;
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.data = payload.data;
        this.verb = payload.verb;
    }
}

export class OpenUrlActionModel extends BaseActionModel {
    url;
    type = ElementType.ActionOpenUrl;
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.url = payload.url;
    }
}

export class ShowCardActionModel extends BaseActionModel {
    card;
    type = ElementType.ActionShowCard;
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.card = ModelFactory.createElement(payload.card, this, hostConfig);
        this.children = [this.card];
    }
}

export class ToggleVisibilityActionModel extends BaseActionModel {
    targetElements;
    type = ElementType.ActionToggleVisibility;
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.targetElements = payload.targetElements;
    }
}
