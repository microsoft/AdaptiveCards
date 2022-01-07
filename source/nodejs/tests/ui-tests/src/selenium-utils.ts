// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { By } from "selenium-webdriver";

export class ByExtended extends By {
    static ariaLabel(ariaLabel: string, tagName?: string): By {
        return this.getXpathProperty("aria-label", ariaLabel);
    }

    static ariaDescription(ariaDescription: string, tagName?: string): By {
        return this.getXpathProperty("aria-description", ariaDescription);
    }

    static title(title: string, tagName?: string): By {
        return this.getXpathProperty("title", title);
    }

    static containsClass(className: string, tagName?: string): By {
        return By.xpath(new XpathBuilder().addAttributeContains(className, "class").buildXpath());
    }

    static getXpathProperty(propertyName: string, propertyValue: string, tagName?:string): By {
        const tag = tagName? tagName: '*';
        return By.xpath(new XpathBuilder().setTagName(tag).addAttributeEquals(propertyName, propertyValue).buildXpath());
    }
}

export class XpathBuilder {
    private tagName?: string;
    private expressions: string[] = [];

    setTagName(tagName: string): XpathBuilder {
        this.tagName = tagName;
        return this;
    }

    addAttributeEquals(attribute: string, value: string): XpathBuilder {
        return this.addEquality(value, attribute);
    }

    addTextEquals(value: string): XpathBuilder {
        return this.addEquality(value);
    }

    addAttributeStartsWith(value: string, attribute?:"string"): XpathBuilder {
        return this.addFunction("starts-with", value, attribute);
    }

    addAttributeContains(value: string, attribute?: string): XpathBuilder {
        return this.addFunction("contains", value, attribute);
    }

    private addEquality(value: string, attribute?: string): XpathBuilder {
        const attributeName = (attribute !== undefined) ? "@" + attribute : "text()"; 
        this.expressions.push(`${attributeName}='${value}'`);
        return this;
    }

    private addFunction(functionName: string, value: string, attribute?: string): XpathBuilder {
        const attributeName = (attribute !== undefined) ? "@" + attribute : "text()"; 
        this.expressions.push(`${functionName}(${attributeName},'${value}')`);
        return this;
    }

    private concatenateExpressions(): string {
        let concatenatedExpressions = "";
        let isFirst = true;
        
        for (const expression of this.expressions) 
        {
            if (!isFirst) {
                concatenatedExpressions += " and ";
            }
            concatenatedExpressions += expression;

            isFirst = false;
        }

        return concatenatedExpressions;
    }

    buildXpath(): string {
        const tagName = (this.tagName !== undefined) ? this.tagName : "*";
        const expressions = this.concatenateExpressions();
        return `//${tagName}[${expressions}]`;
    }

}