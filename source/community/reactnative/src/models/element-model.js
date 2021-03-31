import {BaseModel} from './base-model'
import { ElementType } from '../utils/enums'


export class TextBlockModel extends BaseModel {
    type = ElementType.TextBlock;

    constructor(payload, parent) {
        super(payload, parent);
        this.text = payload.text;
        this.color = payload.color;
        this.horizontalAlignment = payload.horizontalAlignment;
        this.isSubtle = payload.isSubtle || false;
        this.maxLines = payload.maxLines;
        this.size = payload.size;
        this.weight = payload.weight;
        this.wrap = payload.wrap || false;
        this.fontStyle = payload.fontStyle;
        this.altText = payload.altText;
    }
}

export class ImageModel extends BaseModel {
    type = ElementType.Image;

    constructor(payload, parent) {
        super(payload, parent);
        this.url = payload.url;
        this.altText = payload.altText;
        this.horizontalAlignment = payload.horizontalAlignment;
        this.size = payload.size;
        this.style = payload.style;
        this.backgroundColor = payload.backgroundColor;
        this.size = payload.size;
        this.width = payload.width;
        this.height = payload.height;
    }
}

export class MediaModel extends BaseModel {
    type = ElementType.Media;
    sources = [];

    constructor(payload, parent) {
        super(payload, parent);

        if (payload.sources) {
            payload.sources.forEach((item) => {
                if (item) {
                    this.sources.push(item);
                }
            });
        }
        this.poster = payload.poster;
        this.altText = payload.altText;
    }
}

export class RichTextBlockModel extends BaseModel {
    type = ElementType.RichTextBlock;

    constructor(payload, parent) {
        super(payload, parent);
        this.text = payload.text;
        this.color = payload.color;
        this.horizontalAlignment = payload.horizontalAlignment;
        this.isSubtle = payload.isSubtle || false;
        this.maxLines = payload.maxLines;
        this.size = payload.size;
        this.weight = payload.weight;
        this.wrap = payload.wrap || false;
        this.paragraphs = payload.paragraphs;
        this.fontStyle = payload.fontStyle;
    }
}

