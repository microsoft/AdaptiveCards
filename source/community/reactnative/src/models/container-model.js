import { BaseModel } from './base-model'
import { ModelFactory } from './model-factory';
import { ElementType } from '../utils/enums'
import { ImageModel } from './element-model'
import { HostCapabilities, HostConfigManager } from '../utils/host-config';

class BaseContainerModel extends BaseModel {
    constructor(payload, parent) {
        super(payload, parent);
        if (payload.backgroundImage) {
            this.backgroundImage = payload.backgroundImage;;
        }
        this.verticalContentAlignment = payload.verticalContentAlignment;
        this.style = payload.style;
        this.bleed = payload.bleed;
    }
}

export class AdaptiveCardModel extends BaseContainerModel {
    constructor(payload, parent) {
        super(payload, parent);
        this.type = ElementType.AdaptiveCard;
        this.fallbackText = payload.fallbackText;
        this.version = payload.version;
        this.speak = payload.speak;
        this.children = [];
        this.actions = [];
        this.children.push(...ModelFactory.createGroup(payload.body, this));
        this.actions.push(...ModelFactory.createGroup(payload.actions, this));
        this.show = true;
    }
}

export class ContainerModel extends BaseContainerModel {
    constructor(payload, parent) {
        super(payload, parent);
        this.type = ElementType.Container;
        this.children = [];
        this.children.push(...ModelFactory.createGroup(payload.items, this));
        this.height = payload.height;
        this.minHeight = payload.minHeight;
    }

    get items() {
        return this.children;
    }
}

export class ColumnSetModel extends BaseContainerModel {
    constructor(payload, parent) {
        super(payload, parent);
        this.type = ElementType.ColumnSet;
        this.children = [];
        if (payload.columns) {
            payload.columns.forEach((item) => {
                if(item.requires) {
                    let requirements = new HostCapabilities(item.requires)
                    let hostCapabilities = HostConfigManager.getHostConfig().getHostCapabilities()
                    if(requirements.satisfied(hostCapabilities)) {
                        this.addColumn(item)
                    } else if (item.fallback 
                        && typeof(item.fallback) === 'object' 
                        && item.fallback.type === 'Column' ) {
                        this.addColumn(item.fallback)
                    }
                } else {
                    this.addColumn(item)
                }
            });
        }
        this.height = payload.height;
    }
    get columns() {
        return this.children;
    }

    addColumn(item) {
        let column = new ColumnModel(item, this);
        if (column) {
            this.children.push(column);
        }
    }
}

export class ColumnModel extends BaseContainerModel {
    constructor(payload, parent) {
        super(payload, parent);
        this.type = ElementType.Column;
        this.children = [];
        this.children.push(...ModelFactory.createGroup(payload.items, this));
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
    constructor(payload, parent) {
        super(payload, parent);
        this.type = ElementType.FactSet;
        this.children = [];
        if (payload.facts) {
            payload.facts.forEach((item) => {
                let fact = new FactModel(item);
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
    constructor(payload, parent) {
        super(payload, parent);
        this.type = ElementType.ImageSet;
        this.children = [];
        this.imageSize = payload.imageSize;
        if (payload.images) {
            payload.images.forEach((item) => {
                let image = new ImageModel(item, this);
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
    constructor(payload, parent) {
        super(payload, parent);
        this.type = ElementType.ActionSet;
        this.children = [];
        this.children.push(...ModelFactory.createGroup(payload.actions, this));
        this.height = payload.height;
    }

    get actions() {
        return this.children;
    }

}



