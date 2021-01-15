import {BaseModel} from './base-model'
import { ElementType } from '../utils/enums'
import { ModelFactory } from './model-factory'

export class BaseActionModel extends BaseModel{
    constructor(payload, parent) {
        super(payload, parent);
        this.title = payload.title;
        this.iconUrl = payload.iconUrl;
        this.sentiment = payload.style;
        this.ignoreInputValidation = payload.ignoreInputValidation;
        this.altText = payload.altText;
    }
}

export class SubmitActionModel extends BaseActionModel{
    data;
    type = ElementType.ActionSubmit;
    constructor(payload, parent) {
        super(payload, parent);
        this.data = payload.data;
    }
}

export class OpenUrlActionModel extends BaseActionModel{
    url;
    type = ElementType.ActionOpenUrl;
    constructor(payload, parent) {
        super(payload, parent);
        this.url = payload.url;
    }
}

export class ShowCardActionModel extends BaseActionModel{
    card;
    type = ElementType.ActionShowCard;
    constructor(payload, parent) {
        super(payload, parent);
        this.card = ModelFactory.createElement(payload.card, this);
        this.children = [this.card];
    }
}

export class ToggleVisibilityActionModel extends BaseActionModel{
    targetElements;
    type = ElementType.ActionToggleVisibility;
    constructor(payload, parent) {
        super(payload, parent);
        this.targetElements = payload.targetElements;
    }
}
