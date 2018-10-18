"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var SettingsManager = /** @class */ (function () {
    function SettingsManager() {
    }
    SettingsManager.determineIfStorageIsAvailable = function (type) {
        try {
            var storage = window[type];
            var x = '__storage_test__';
            storage.setItem(x, x);
            storage.removeItem(x);
            return true;
        }
        catch (e) {
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
    };
    SettingsManager.trySaveSetting = function (name, value) {
        if (SettingsManager.isLocalStorageAvailable) {
            localStorage.setItem(name, value);
        }
    };
    SettingsManager.tryLoadNumberSetting = function (name) {
        if (SettingsManager.isLocalStorageAvailable) {
            var returnValue = localStorage.getItem(name);
            return {
                succeeded: true,
                value: returnValue ? parseFloat(returnValue) : undefined
            };
        }
        else {
            return { succeeded: false };
        }
    };
    SettingsManager.tryLoadBooleanSetting = function (name, defaultValue) {
        if (SettingsManager.isLocalStorageAvailable) {
            var returnValue = localStorage.getItem(name);
            return {
                succeeded: true,
                value: returnValue ? returnValue == "true" : defaultValue
            };
        }
        else {
            return { succeeded: false };
        }
    };
    Object.defineProperty(SettingsManager, "isLocalStorageAvailable", {
        get: function () {
            if (!SettingsManager._isLocalStorageAvailable) {
                SettingsManager._isLocalStorageAvailable = SettingsManager.determineIfStorageIsAvailable("localStorage");
            }
            return SettingsManager._isLocalStorageAvailable;
        },
        enumerable: true,
        configurable: true
    });
    SettingsManager._isLocalStorageAvailable = undefined;
    return SettingsManager;
}());
exports.SettingsManager = SettingsManager;
//# sourceMappingURL=settings-manager.js.map