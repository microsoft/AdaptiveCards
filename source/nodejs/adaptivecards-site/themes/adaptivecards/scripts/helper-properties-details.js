// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var typedschema = require("ac-typed-schema");
var marked = require("marked");
var fs = require("fs");
var path = require("path");

hexo.extend.helper.register('properties_details', function (properties, elementVersion, isSpec) {
	const codeAndCard = hexo.extend.helper.get('code_and_card').bind(hexo);

	var html = '<h2 class="w3-container">Properties</h2>';

	properties.forEach((property, name) => {

		// Get the markdown for the property and turn it into HTML
		html += '<div class="w3-container">';

		html += marked(typedschema.markdown.createPropertyDetails(property, 3, null, false, true, elementVersion), { headerPrefix: "dedupe-header" });
		html += '</div>'


		// Load card example file into a div, using JS to render it later
		if (!isSpec) {
			property.cardExamples.forEach(function (example, i) {
				var sampleHtml = "";
				try {
					sampleHtml += codeAndCard(example);
					html += sampleHtml;
				} catch (err) {
					// Do nothing
				}

			});
		}
	});

	return html;
});
