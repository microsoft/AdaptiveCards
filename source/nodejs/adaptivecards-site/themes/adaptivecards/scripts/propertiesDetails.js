// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var markedschema = require("marked-schema");
var marked = require("marked");
var fs = require("fs");
var path = require("path");

hexo.extend.helper.register('propertiesDetails', function (properties) {
  var html = '<h2 class="w3-container">Properties</h2>';

  for (var name in properties) {
    if (properties.hasOwnProperty(name)) {
      var property = properties[name];

      // Get the markdown for the property and turn it into HTML
      html += '<div class="w3-container">';

      html += marked(markedschema.generateMarkdown.createPropertyDetails(property, 3), { headerPrefix: "dedupe-header" });
      html += '</div>'


      // Load card example file into a div, using JS to render it later
      property.examples.forEach(function (example, i) {
        if (i === 0) {
          html += '<h4 class="w3-container">Example</h4>';
        }

        var exampleContent = fs.readFileSync(example, "utf8");

        html += '<div class="w3-row reverse-order-mobile">';

        html += '<div class="w3-container w3-col s12 m7 l8 code-snippet">';
        html += "<pre><code class='json'>" + exampleContent + "</code></pre>";
        html += "</div>";

        html += '<div class="w3-container w3-col s12 m5 l4">';
        html += '<div class="adaptivecard">' + exampleContent + '</div>';
        html += '<a class="w3-btn w3-blue" target="_blank" href="/designer/index.html?card=/payloads/' + path.basename(example) + '">Try it Yourself Â»</a>';
        html += '</div>';

        html += '</div>'; // w3-cell-row

      });

    }
  }

  return html;
});
