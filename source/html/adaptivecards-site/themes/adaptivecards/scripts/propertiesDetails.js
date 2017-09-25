"use strict";

var markedschema = require("marked-schema");
var marked = require("marked");
var fs = require("fs");

hexo.extend.helper.register('propertiesDetails', function (properties) {
  var html = '';

  for (var name in properties) {
    if (properties.hasOwnProperty(name)) {
      var property = properties[name];

      // Get the markdown for the property and turn it into HTML
      var md = markedschema.generateMarkdown.createPropertyDetails(property, 3);
      html += marked(md, { headerPrefix: "dedupe-header" });


      // Load card example file into a div, using JS to render it later
      property.examples.forEach(function (example, i) {
        if (i === 0) {
          html += '<h3>Example</h3>';
        }

        var exampleContent = fs.readFileSync(example, "utf8");

        html += '<div class="w3-cell-row">';

        html += '<div class="w3-container w3-cell w3-card-2 w3-light-grey w3-mobile">';
        html += "<pre><code>" + exampleContent + "</code></pre>";
        html += "</div>";

        html += '<div class="w3-container w3-cell w3-card-2 w3-blue w3-mobile" style="min-width: 250px; max-width: 250px">';
        html += '<div class="adaptivecard">' + exampleContent + '</div>';
        html += '</div>';

        html += '</div>'; // w3-cell-row

      });

    }
  }

  return html;
});