// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { GlobalSettings, SizeAndUnit } from "./shared";
import * as Utils from "./utils";
import * as Enums from "./enums";
import { Strings } from "./strings";
import * as Serialization from "./serialization";


export enum PluginContributionPoints {

}


export interface IPlugin {

    name: string
    elementPrefix: string
    propertyPrefix: string
    version: string
    id: string
    hostConfig: []
    contributes: []


    beforeParse(source: Serialization.PropertyBag, context?: any) : any
    afterParse(source: Serialization.PropertyBag, context?: any) : any
    beforeRenderElement() : any
    afterRenderElement() : any
    beforeRender() : any
    afterRender() : any

    beforeSubmit() : any
    afterSubmit() : any

}