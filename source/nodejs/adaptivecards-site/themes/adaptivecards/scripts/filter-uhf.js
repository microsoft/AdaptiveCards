// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
const fetch = require("node-fetch");

/* from UHF MSDocsHeader-AdaptiveCards */

hexo.extend.filter.register("before_generate", async function (data) {
	const url_for = hexo.extend.helper.get('url_for').bind(hexo);

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
        footerId + "&Preview=1";

    const response = await fetch(serviceUrl);
	const body = await response.text();
	
	const splitBody = body.split("<![CDATA[");
	
	let header = splitBody[3].split("]]>")[0];
	header = header.replace("urlForExplorer", url_for('explorer'));
	header = header.replace("urlForSamples", url_for('samples'));
	header = header.replace("urlForBlog", url_for('blog'));
	header = header.replace("urlForDesigner", url_for('designer'));

    hexo.config.uhf_css = splitBody[1].split("]]>")[0];
    hexo.config.uhf_javascript = splitBody[2].split("]]>")[0];
    hexo.config.uhf_header = header;
    hexo.config.uhf_footer = splitBody[4].split("]]>")[0];
});
