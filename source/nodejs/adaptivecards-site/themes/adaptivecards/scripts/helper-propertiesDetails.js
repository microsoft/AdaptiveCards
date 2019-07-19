// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var typedschema = require("ac-typed-schema");
var marked = require("marked");
var fs = require("fs");
var path = require("path");

hexo.extend.helper.register('propertiesDetails', function (properties, elementVersion, isSpec) {
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
				if (i === 0) {
					sampleHtml += '<h4 class="w3-container">Example</h4>';
				}

				var exampleContent = fs.readFileSync(example, "utf8");

				sampleHtml += '<div class="w3-row reverse-order-mobile">';

				sampleHtml += '<div class="w3-container w3-col s12 m7 l8 code-snippet">';
				sampleHtml += "<pre><code class='json'>" + exampleContent + "</code></pre>";
				sampleHtml += "</div>";

				sampleHtml += '<div class="w3-container w3-col s12 m5 l4">';
				sampleHtml += '<div class="adaptivecard">' + exampleContent + '</div>';
				sampleHtml += '<a class="w3-btn w3-blue" target="_blank" href="/designer/index.html?card=/payloads/' + path.basename(example) + '">Try it Yourself »</a>';
				sampleHtml += '</div>';

				sampleHtml += '</div>'; // w3-cell-row

				html += sampleHtml;
			} catch (err) {
				// Do nothing
			}

		});
	}
  });

  return html;
});
