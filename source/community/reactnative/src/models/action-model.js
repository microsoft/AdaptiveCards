import {BaseModel} from './base-model'
import { ElementType } from '../utils/enums'
import { ModelFactory } from './model-factory'

export class BaseActionModel extends BaseModel{
    constructor(parent, payload) {
        super(parent, payload);
        this.title = payload.title;
        this.iconUrl = payload.iconUrl;
        this.sentiment = payload.sentiment;
        this.ignoreInputValidation = payload.ignoreInputValidation;
    }
}

export class SubmitActionModel extends BaseActionModel{
    data;
    type = ElementType.ActionSubmit;
    constructor(parent, payload) {
        super(parent, payload);
        this.data = payload.data;
    }
}

export class OpenUrlActionModel extends BaseActionModel{
    url;
    type = ElementType.ActionOpenUrl;
    constructor(parent, payload) {
        super(parent, payload);
        this.url = payload.url;
    }
}

export class ShowCardActionModel extends BaseActionModel{
    card;
    type = ElementType.ActionShowCard;
    constructor(parent, payload) {
        super(parent, payload);
        this.card = ModelFactory.createElement(this,payload.card);
        this.children = [this.card];
    }
}

export class ToggleVisibilityActionModel extends BaseActionModel{
    targetElements;
    type = ElementType.ActionToggleVisibility;
    constructor(parent, payload) {
        super(parent, payload);
        this.targetElements = payload.targetElements;
    }
}
