import * as Utils from '../utils/util';
import { ModelFactory } from './model-factory'

export class BaseModel {
    id;
    type;
    parent;
    children = [];
    payload;
    selectAction;
    isVisible = true;
    isFallbackActivated = false;
    fallback;
    fallbackType;
    requires;

    constructor(payload, parent) {
        this.parent = parent;
        this.id = payload.id;
        this.spacing = payload.spacing;
        this.separator = payload.separator;
        this.requires = payload.requires;
        if (this.id === undefined) {
            this.id = Utils.generateID();
        }
        if (payload.selectAction) {
            this.selectAction = payload.selectAction;
        }
        this.isVisible = payload.isVisible !== undefined ? payload.isVisible : true;
        if (payload.fallback) {
            if (payload.fallback == "drop") {
                this.fallbackType = "drop"
            } else {
                this.fallback = ModelFactory.createElement(payload.fallback, parent);
            }
        }
    }
}
