import { BaseModel } from './base-model'
import { ModelFactory } from './model-factory';
import { ElementType } from '../utils/enums'
import { ImageModel } from './element-model'

class BaseContainerModel extends BaseModel {
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        if (payload.backgroundImage) {
            this.backgroundImage = payload.backgroundImage;;
        }
        this.verticalContentAlignment = payload.verticalContentAlignment;
        this.style = payload.style;
        this.bleed = payload.bleed || false;
        this.minHeight = payload.minHeight;
        this.altText = payload.altText;
    }
}

export class AdaptiveCardModel extends BaseContainerModel {
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.type = ElementType.AdaptiveCard;
        this.fallbackText = payload.fallbackText;
        this.version = payload.version;
        this.speak = payload.speak;
        this.children = [];
        this.actions = [];
        this.height = undefined;
        this.children.push(...ModelFactory.createGroup(payload.body, this, hostConfig));
        this.actions.push(...ModelFactory.createGroup(payload.actions, this, hostConfig));
        this.show = true;
    }
}

export class ContainerModel extends BaseContainerModel {
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.type = ElementType.Container;
        this.children = [];
        this.children.push(...ModelFactory.createGroup(payload.items, this, hostConfig));
        this.height = payload.height;
    }

    get items() {
        return this.children;
    }
}

export class ColumnSetModel extends BaseContainerModel {
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.type = ElementType.ColumnSet;
        this.children = [];
        if (payload.columns) {
            payload.columns.forEach((item) => {
                let column = new ColumnModel(item, this, hostConfig);
                if (column) {
                    this.children.push(column);
                }
            });
        }
        this.height = payload.height;
    }
    get columns() {
        return this.children;
    }
}

export class ColumnModel extends BaseContainerModel {
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.type = ElementType.Column;
        this.children = [];
        this.children.push(...ModelFactory.createGroup(payload.items, this, hostConfig));
        this.height = payload.height;
        if (payload.width) {
            if (payload.width === 'auto' || payload.width === 'stretch') {
                this.width = payload.width;
            } else {
                this.width = parseInt(payload.width, 10) < 0 ? 0 : payload.width;
            }
        }
    }
    get items() {
        return this.children;
    }
}

export class FactModel {
    constructor(payload) {
        this.type = 'Fact';
        this.title = payload.title;
        this.value = payload.value;
    }
}

export class FactSetModel extends BaseContainerModel {
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.type = ElementType.FactSet;
        this.children = [];
        if (payload.facts) {
            payload.facts.forEach((item) => {
                let fact = new FactModel(item, this, hostConfig);
                if (fact) {
                    this.children.push(fact);
                }
            });
        }
    }
    get facts() {
        return this.children;
    }
}

export class ImageSetModel extends BaseContainerModel {
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.type = ElementType.ImageSet;
        this.children = [];
        this.imageSize = payload.imageSize;
        if (payload.images) {
            payload.images.forEach((item) => {
                let image = new ImageModel(item, this, hostConfig);
                if (image) {
                    this.children.push(image);
                }
            });
        }
    }
    get images() {
        return this.children;
    }
}

export class ActionSetModel extends BaseContainerModel {
    constructor(payload, parent, hostConfig) {
        super(payload, parent, hostConfig);
        this.type = ElementType.ActionSet;
        this.children = [];
        this.children.push(...ModelFactory.createGroup(payload.actions, this, hostConfig));
        this.height = payload.height;
    }

    get actions() {
        return this.children;
    }

}



