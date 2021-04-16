// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import i18next from "i18next";

var resBundle = require("i18next-resource-store-loader!../assets/languages/index.js");

i18next.init({
    debug: true, // TODO: remove
    lng: 'en',
    ns: 'designer',
    defaultNS: 'designer',
    resources: resBundle
});

export function __(key: any, options?: any) {
    const result = i18next.t(key, options);
    return result;
}
