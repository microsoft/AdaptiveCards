// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

hexo.extend.generator.register("generator-connect", function (locals) {

    return {
        path: "connect/index.html",
        layout: "connect",
        data: {
            title: "Connect"
        }
    }
});
