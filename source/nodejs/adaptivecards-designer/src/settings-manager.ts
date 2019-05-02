// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export interface ILoadSettingResult<T> {
    succeeded: boolean;
    value?: T;
}

export class SettingsManager {
    private static _isLocalStorageAvailable: boolean = undefined;

    private static determineIfStorageIsAvailable(type: string): boolean {
        try {
            var storage = window[type];
            let x = '__storage_test__';

            storage.setItem(x, x);
            storage.removeItem(x);

            return true;
        }
        catch(e) {
            return e instanceof DOMException && (
                // everything except Firefox
                e.code === 22 ||
                // Firefox
                e.code === 1014 ||
                // test name field too, because code might not be present
                // everything except Firefox
                e.name === 'QuotaExceededError' ||
                // Firefox
                e.name === 'NS_ERROR_DOM_QUOTA_REACHED') &&
                // acknowledge QuotaExceededError only if there's something already stored
                storage.length !== 0;
        }
    }

    static trySaveSetting(name: string, value: string) {
        if (SettingsManager.isLocalStorageAvailable) {
            localStorage.setItem(name, value);
        }
    }

    static tryLoadStringSetting(name: string): ILoadSettingResult<string> {
        if (SettingsManager.isLocalStorageAvailable) {
            let returnValue = localStorage.getItem(name);
    
            return {
                succeeded: true,
                value: returnValue
            };
        }
        else {
            return { succeeded: false };
        }
    }
    
    static tryLoadNumberSetting(name: string): ILoadSettingResult<number> {
        if (SettingsManager.isLocalStorageAvailable) {
            let returnValue = localStorage.getItem(name);

            return {
                succeeded: true,
                value: returnValue ? parseFloat(returnValue) : undefined
            };
        }
        else {
            return { succeeded: false };
        }
    }

    static tryLoadBooleanSetting(name: string, defaultValue: boolean): ILoadSettingResult<boolean> {
        if (SettingsManager.isLocalStorageAvailable) {
            let returnValue = localStorage.getItem(name);

            return {
                succeeded: true,
                value: returnValue ? returnValue == "true" : defaultValue
            };
        }
        else {
            return { succeeded: false };
        }
    }

    static get isLocalStorageAvailable(): boolean {
        if (!SettingsManager._isLocalStorageAvailable) {
            SettingsManager._isLocalStorageAvailable = SettingsManager.determineIfStorageIsAvailable("localStorage");
        }

        return SettingsManager._isLocalStorageAvailable;
    }
}
