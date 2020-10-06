// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Downloader } from "./downloader";
import { BaseSerializationContext, BoolProperty, CustomProperty, ObjectProperty, property, PropertyDefinition, SerializableObject, SerializableObjectProperty, StringProperty, Version, Versions } from "./serialization";
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

    /*
    toJSON(sender: SerializableObject, target: PropertyBag, value: SchemaProperty[], context: BaseSerializationContext) {
        let serializedProperties: { [key: string]: any } = {};

        for (let schemaProperty of value) {
            serializedProperties[schemaProperty.name] = schemaProperty.toJSON(context);
        }

        context.serializeValue(target, this.name, serializedProperties);
    }
    */

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
    static readonly schemaProperty = new SerializableObjectProperty(Versions.v1_3, "schema", ComponentSchema);
    static readonly viewsProperty = new DictionaryProperty<object>(Versions.v1_3, "views");
    static readonly sampleDataProperty = new ObjectProperty(Versions.v1_3, "sampleData");

    @property(AdaptiveComponent.nameProperty)
    name: string;

    @property(AdaptiveComponent.schemaProperty)
    schema?: ComponentSchema;

    @property(AdaptiveComponent.viewsProperty)
    views: Dictionary<object>;

    @property(AdaptiveComponent.sampleDataProperty)
    sampleDate: any;

    //#endregion

    protected getSchemaKey(): string {
        return "AdaptiveComponent";
    }

    getView(name: string): object | undefined {
        if (this.views) {
            if (this.views.hasOwnProperty(name)) {
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

enum ComponentLoadStatus {
    NotLoaded,
    Loading,
    Loaded,
    LoadError
}

export type MulticastEventHandlerCallback<TArgs> = (args: TArgs) => void;

export class MulticastEvent<TArgs> {
    private _handlers: MulticastEventHandlerCallback<TArgs>[] = [];

    addHandler(handler: MulticastEventHandlerCallback<TArgs>) {
        this._handlers.push(handler);
    }

    raise(args: TArgs) {
        for (let handler of this._handlers) {
            handler(args);
        }
    }
}

export class AdaptiveComponentManager {
    private static _cache: Dictionary<AdaptiveComponent> = {};

    static getComponentUrl(name: string): string {
        // TODO: Remove when the service is available
        if (name === "Demo") {
            return "https://gist.githubusercontent.com/dclaux/978871cad39a8e36914b3b4a6efdd028/raw/bc143b6346031f78dc5fd8461ee715a553f7ed93/gistfile1.txt";
        }

        let baseUrl = GlobalSettings.componentRegistryBaseUrl;

        if (!baseUrl.endsWith("/")) {
            baseUrl += "/";
        }

        return baseUrl + name + ".json";
    }

    static readonly onComponentLoaded: MulticastEvent<AdaptiveComponent> = new MulticastEvent<AdaptiveComponent>();
    static readonly onComponentLoadError: MulticastEvent<string> = new MulticastEvent<string>();

    static loadComponent(name: string) {
        if (AdaptiveComponentManager._cache.hasOwnProperty(name)) {
            AdaptiveComponentManager.onComponentLoaded.raise(AdaptiveComponentManager._cache[name]);
        }
        else {
            let downloader = new Downloader(AdaptiveComponentManager.getComponentUrl(name));
            downloader.onSuccess = (s: Downloader) => {
                let parsedData = JSON.parse(s.data);

                if (typeof parsedData === "object") {
                    let component = new AdaptiveComponent();
                    component.parse(parsedData);

                    AdaptiveComponentManager._cache[name] = component;
                    AdaptiveComponentManager.onComponentLoaded.raise(component);
                }
            }
            downloader.onError = (s: Downloader) => {
                AdaptiveComponentManager.onComponentLoadError.raise(name);
            }
            downloader.download();
        }
    }
}

SchemaProperty.registerSchemaPropertyClass("string", StringSchemaProperty);