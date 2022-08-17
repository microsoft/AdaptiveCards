// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var typedschema = require("@microsoft/ac-typed-schema");
const { marked } = require("marked");
var fs = require("fs");
var path = require("path");

hexo.extend.helper.register('properties_details', function (locals, properties, elementVersion, isSpec) {
	const codeAndCard = hexo.extend.helper.get('code_and_card').bind(hexo);

    // TODO: actually pass locale
    typedschema.markdownConfig.locale = "en";

	var html = '<h2 class="w3-container">' + locals.data.explorer.en.properties + '</h2>';

	properties.forEach((property, name) => {

		// Get the markdown for the property and turn it into HTML
		html += '<div class="w3-container">';

		// mark header with class name like ac-schema-version-1.5
		html +=  `<div class="ac-schema-version-${elementVersion?.replace(/\./, '-')}" style="display: flex;">`
		html += marked.parse(typedschema.markdown.createPropertyDetailsHeader(property, 3), { headerPrefix: "dedupe-header" });
		html += '</div>'

		html += marked.parse(typedschema.markdown.createPropertyDetails(property, 3, null, false, true, elementVersion, false /* include header */));
		html += '</div>'


		// Load card example file into a div, using JS to render it later
		if (!isSpec) {
			property.cardExamples.forEach(function (example, i) {
				var sampleHtml = "";
				try {
					sampleHtml += codeAndCard(locals, example);
					html += sampleHtml;
				} catch (err) {
					// Do nothing
				}

			});
		}
	});

	return html;
});
