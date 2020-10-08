// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Downloader } from "./downloader";
import { BaseSerializationContext, BoolProperty, CustomProperty, NumProperty, ObjectProperty, property, PropertyDefinition, SerializableObject, SerializableObjectProperty, StringProperty, Version, Versions } from "./serialization";
import { Dictionary, GlobalSettings, PropertyBag } from "./shared";

type SchemaPropertyClass = { new(): SchemaProperty };

export abstract class SchemaProperty extends SerializableObject {
    //#region Schema

    static readonly nameProperty = new StringProperty(Versions.v1_3, "name", true);
    static readonly displayNameProperty = new StringProperty(Versions.v1_3, "displayName", true);

    @property(SchemaProperty.nameProperty)
    name: string;

    @property(SchemaProperty.displayNameProperty)
    displayName: string;

    //#endregion

    private static _schemaPropertyMap: Dictionary<SchemaPropertyClass> = {};

    static registerSchemaPropertyClass(type: string, propertyClass: SchemaPropertyClass) {
        SchemaProperty._schemaPropertyMap[type] = propertyClass;
    }    

    static parse(property: any): SchemaProperty | undefined {
        if (typeof property === "object") {
            let propertyType = property["type"];

            if (typeof propertyType === "string" && SchemaProperty._schemaPropertyMap.hasOwnProperty(propertyType)) {
                let schemaProperty = new SchemaProperty._schemaPropertyMap[propertyType]();
                schemaProperty.parse(property);

                return schemaProperty;
            }
        }

        return undefined;
    }
}

export class StringSchemaProperty extends SchemaProperty {
    //#region Schema

    static readonly isMultilineProperty = new BoolProperty(Versions.v1_3, "isMultiline", false);

    @property(StringSchemaProperty.isMultilineProperty)
    isMultiline: boolean = false;

    //#endregion

    protected getSchemaKey(): string {
        return "StringSchemaProperty";
    }    
}

export class NumberSchemaProperty extends SchemaProperty {
    //#region Schema

    static readonly minProperty = new NumProperty(Versions.v1_3, "min");
    static readonly maxProperty = new NumProperty(Versions.v1_3, "max");

    @property(NumberSchemaProperty.minProperty)
    min?: number;

    @property(NumberSchemaProperty.maxProperty)
    max?: number;

    //#endregion

    protected getSchemaKey(): string {
        return "NumberSchemaProperty";
    }    
}

export class SchemaPropertiesProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): SchemaProperty[] {
        let result: SchemaProperty[] = [];
        let sourceValue = source[this.name];

        if (typeof sourceValue === "object") {
            for (let key in sourceValue) {
                let property = sourceValue[key];

                if (typeof property === "object") {
                    let schemaProperty = SchemaProperty.parse(property);

                    if (schemaProperty) {
                        schemaProperty.name = key;

                        result.push(schemaProperty);
                    }
                }
            }
        }

        return result;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: SchemaProperty[], context: BaseSerializationContext) {
        let serializedProperties: { [key: string]: any } = {};

        for (let schemaProperty of value) {
            serializedProperties[schemaProperty.name] = schemaProperty.toJSON(context);
        }

        context.serializeValue(target, this.name, serializedProperties);
    }

    constructor(readonly targetVersion: Version, readonly name: string) {
        super(targetVersion, name);
    }
}

export class DictionaryProperty<T extends object> extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): Dictionary<T> {
        let result: Dictionary<T> = {}
        let sourceValue = source[this.name];

        if (typeof sourceValue === "object") {
            for (let key in sourceValue) {
                let view = sourceValue[key];

                if (typeof view === "object") {
                    result[key] = view;
                }
            }
        }

        return result;
    }

    constructor(readonly targetVersion: Version, readonly name: string) {
        super(targetVersion, name);
    }
}

export class ComponentSchema extends SerializableObject {
    //#region Schema

    static readonly propertiesProperty = new SchemaPropertiesProperty(Versions.v1_3, "properties");

    @property(ComponentSchema.propertiesProperty)
    properties: SchemaProperty[];

    //#endregion

    protected getSchemaKey(): string {
        return "ComponentSchema";
    }    
}

export class AdaptiveComponent extends SerializableObject {
    //#region Schema

    static readonly nameProperty = new StringProperty(Versions.v1_3, "name", true);
    static readonly displayNameProperty = new StringProperty(Versions.v1_3, "displayName", true);
    static readonly descriptionProperty = new StringProperty(Versions.v1_3, "description", true);
    static readonly schemaProperty = new SerializableObjectProperty(Versions.v1_3, "schema", ComponentSchema);
    static readonly viewsProperty = new DictionaryProperty<object>(Versions.v1_3, "views");
    static readonly sampleDataProperty = new ObjectProperty(Versions.v1_3, "sampleData");

    @property(AdaptiveComponent.nameProperty)
    name: string;

    @property(AdaptiveComponent.displayNameProperty)
    displayName?: string;

    @property(AdaptiveComponent.descriptionProperty)
    description?: string;

    @property(AdaptiveComponent.schemaProperty)
    schema?: ComponentSchema;

    @property(AdaptiveComponent.viewsProperty)
    views: Dictionary<object>;

    @property(AdaptiveComponent.sampleDataProperty)
    sampleData: any;

    //#endregion

    protected getSchemaKey(): string {
        return "AdaptiveComponent";
    }

    getView(name: string | undefined): object | undefined {
        if (this.views) {
            if (name && this.views.hasOwnProperty(name)) {
                return this.views[name];
            }

            let propertyNames = Object.getOwnPropertyNames(this.views);

            if (propertyNames.length > 0) {
                return this.views[propertyNames[0]];
            }
        }

        return undefined;
    }
}

interface IComponentLoaderListener {
    onSuccess: (component: AdaptiveComponent) => void,
    onError: (error: string) => void
}

export class AdaptiveComponentManager {
    private static _cache: Dictionary<AdaptiveComponent> = {};
    private static _pendingDownloads: Dictionary<Downloader> = {};
    private static _listeners: Dictionary<IComponentLoaderListener[]> = {};

    private static addListener(componentName: string, listener: IComponentLoaderListener) {
        if (AdaptiveComponentManager._listeners.hasOwnProperty(componentName)) {
            AdaptiveComponentManager._listeners[componentName].push(listener);
        }
        else {
            AdaptiveComponentManager._listeners[componentName] = [ listener ];
        }
    }

    private static downloadSucceeded(component: AdaptiveComponent) {
        if (AdaptiveComponentManager._listeners.hasOwnProperty(component.name)) {
            let listeners = AdaptiveComponentManager._listeners[component.name];

            while (listeners.length > 0) {
                let listener = listeners.splice(0, 1)[0];
                listener.onSuccess(component);
            }
        }
    }

    private static downloadFailed(componentName: string, error: string) {
        if (AdaptiveComponentManager._listeners.hasOwnProperty(componentName)) {
            let listeners = AdaptiveComponentManager._listeners[componentName];

            while (listeners.length > 0) {
                let listener = listeners.splice(0, 1)[0];
                listener.onError(error);
            }
        }
    }

    static getComponentUrl(name: string): string {
        let baseUrl = GlobalSettings.componentRegistryBaseUrl;

        if (!baseUrl.endsWith("/")) {
            baseUrl += "/";
        }

        return baseUrl + name + ".json";
    }

    static loadComponent(
        name: string,
        onSuccess: (component: AdaptiveComponent) => void,
        onError: (error: string) => void) {
        if (AdaptiveComponentManager._cache.hasOwnProperty(name)) {
            onSuccess(AdaptiveComponentManager._cache[name]);
        }
        else {
            AdaptiveComponentManager.addListener(
                name,
                {
                    onSuccess: onSuccess,
                    onError: onError
                }
            );

            if (!AdaptiveComponentManager._pendingDownloads.hasOwnProperty(name)) {
                let downloader = new Downloader(AdaptiveComponentManager.getComponentUrl(name));

                downloader.onSuccess = (s: Downloader) => {
                    delete AdaptiveComponentManager._pendingDownloads[name];

                    let parsedData = JSON.parse(s.data);

                    if (typeof parsedData === "object") {
                        let component = new AdaptiveComponent();
                        component.parse(parsedData);

                        AdaptiveComponentManager._cache[name] = component;
                        AdaptiveComponentManager.downloadSucceeded(component);
                    }
                }

                downloader.onError = (s: Downloader) => {
                    AdaptiveComponentManager.downloadFailed(name, `Component ${name} couldn't be loaded.`);
                }

                AdaptiveComponentManager._pendingDownloads[name] = downloader;

                downloader.download();
            }
        }
    }
}

SchemaProperty.registerSchemaPropertyClass("string", StringSchemaProperty);
SchemaProperty.registerSchemaPropertyClass("number", NumberSchemaProperty);