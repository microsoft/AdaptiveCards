// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as markdownit from "markdown-it";
import * as AAF from "adaptivecards-aaf";
import * as Shared from "./shared";
import "adaptivecards-aaf/dist/adaptivecards.css";
import { LocalProxyAdapter } from "./aaf-local-proxy-adapter";

window.onload = function() {
    let host = new AAF.AdaptiveAppHost();
    host.proxyAdapter = new LocalProxyAdapter();
    host.initialize(Shared.sampleCard, Shared.sampleData);

    document.getElementById("appHost").appendChild(host.renderedElement);
}
