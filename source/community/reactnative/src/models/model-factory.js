import * as Models from './index'
import { BaseModel } from './base-model'
import { ElementType } from '../utils/enums'
import * as Utils from '../utils/util'
import { Registry } from '../components/registration/registry';
import { HostCapabilities } from '../utils/host-config';

export class ModelFactory {
    static createElement(payload, parent, hostConfig) {
        
        if (!payload) {
            return undefined;
        }
        if (payload.requires) {
            let requirements = new HostCapabilities(payload.requires)
            let hostCapabilities = hostConfig.getHostCapabilities()
            const elementModel = this.getElement(payload, parent, hostConfig);
            if (elementModel && requirements.satisfied(hostCapabilities)) {
                return this.addCustomPropertyInModel(elementModel, payload)
            } else {
                return ModelFactory.checkForFallBack(payload, parent, hostConfig);
            }
        } else {
            const elementModel = this.getElement(payload, parent, hostConfig);
            if (elementModel) {
                return this.addCustomPropertyInModel(elementModel, payload)
            } else {
                return ModelFactory.checkForFallBack(payload, parent, hostConfig);
            }
        }
    }

    static getElement(payload, parent, hostConfig) {
        if (!payload) {
            return undefined;
        }
        switch (payload.type) {
            case ElementType.Image:
                return new Models.ImageModel(payload, parent, hostConfig);
            case ElementType.Media:
                return new Models.MediaModel(payload, parent, hostConfig);
            case ElementType.TextBlock:
                return new Models.TextBlockModel(payload, parent, hostConfig);
            case ElementType.RichTextBlock:
                return new Models.RichTextBlockModel(payload, parent, hostConfig);
            case ElementType.Column:
                return new Models.ColumnModel(payload, parent, hostConfig);
            case ElementType.ColumnSet:
                return new Models.ColumnSetModel(payload, parent, hostConfig);
            case ElementType.Container:
                return new Models.ContainerModel(payload, parent, hostConfig);
            case ElementType.FactSet:
                return new Models.FactSetModel(payload, parent, hostConfig);
            case ElementType.ImageSet:
                return new Models.ImageSetModel(payload, parent, hostConfig);
            case ElementType.TextInput:
                return new Models.TextInputModel(payload, parent, hostConfig);
            case ElementType.DateInput:
                return new Models.DateInputModel(payload, parent, hostConfig);
            case ElementType.TimeInput:
                return new Models.TimeInputModel(payload, parent, hostConfig);
            case ElementType.NumberInput:
                return new Models.NumberInputModel(payload, parent, hostConfig);
            case ElementType.ChoiceSetInput:
                return new Models.ChoiceSetModel(payload, parent, hostConfig);
            case ElementType.ToggleInput:
                return new Models.ToggleInputModel(payload, parent, hostConfig);
            case ElementType.AdaptiveCard:
                return new Models.AdaptiveCardModel(payload, parent, hostConfig);
            case ElementType.ActionOpenUrl:
                return new Models.OpenUrlActionModel(payload, parent, hostConfig);
            case ElementType.ActionSubmit:
                return new Models.SubmitActionModel(payload, parent, hostConfig);
            case ElementType.ActionExecute:
                return new Models.ExecuteActionModel(payload, parent, hostConfig);
            case ElementType.ActionShowCard:
                return new Models.ShowCardActionModel(payload, parent, hostConfig);
            case ElementType.ActionToggleVisibility:
                return new Models.ToggleVisibilityActionModel(payload, parent, hostConfig);
            case ElementType.ActionSet:
                return new Models.ActionSetModel(payload, parent, hostConfig);
            default:
                //Handling registered custom components
                const Element = Registry.getManager().getComponentOfType(payload.type);
                if (Element) {
                    return new BaseModel(payload, parent, hostConfig);
                } else {
                    return null;
                }
        }
    }

    static addCustomPropertyInModel(elementModel, payload) {
        for (let key in payload) {
            if (!elementModel.hasOwnProperty(key)) {
                elementModel[key] = payload[key];
            }
        }
        return elementModel
    }

    static createGroup(payload, parent, hostConfig) {
        let modelGroup = [];
        if (payload && payload.length > 0) {
            payload.forEach((item) => {
                let model = ModelFactory.createElement(item, parent, hostConfig);
                if (model) {
                    modelGroup.push(model);
                }
            });
        }
        return modelGroup;
    }

    static checkForFallBack(payload, parent, hostConfig) {
        if (!Utils.isNullOrEmpty(payload.fallback)) {
            if (payload.fallback !== "drop") {
                return ModelFactory.createElement(payload.fallback, parent, hostConfig);
            }
            else {
                return undefined;
            }
        } else {
            return undefined;
        }
    }
}