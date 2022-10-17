// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
const fetch = require("node-fetch");

/* from UHF MSDocsHeader-AdaptiveCards */

hexo.extend.filter.register("before_generate", async function (data) {
    const serviceEndpoint = "https://uhf.microsoft.com";
    const partnerId = "MSDocsAdaptivecards";
    const headerId = "MSDocsAdaptivecardsHeader";
    const footerId = "MSDocsAdaptivecardsFooter";
    // TODO: localize
    const serviceUrl =
        serviceEndpoint +
        "/" +
        "en-US" +
        "/shell/xml/" +
        partnerId +
        "?headerId=" +
        headerId +
        "&footerId=" +
        footerId;

    const response = await fetch(serviceUrl);
    const body = await response.text();

    const splitBody = body.split("<![CDATA[");

    hexo.config.uhf_css = splitBody[1].split("]]>")[0];
    hexo.config.uhf_javascript = splitBody[2].split("]]>")[0];
    hexo.config.uhf_footer = splitBody[4].split("]]>")[0];
});
