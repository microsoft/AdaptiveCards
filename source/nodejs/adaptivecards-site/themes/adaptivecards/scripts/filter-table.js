// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// Used for custom rendering of the table element
// We check if the first header row cell contains the title of the table
// We then remove the title from the first cell
hexo.extend.filter.register('marked:renderer', function(renderer) {
  renderer.table = function(header, body) {

    // Example header string:
    // <tr>
    // <th><!-- TableTitle: ActionSet Inherited properties -->Property</th>
    // <th>Type</th>
    // <th>Required</th>
    // <th>Description</th>
    // <th>Version</th>
    // </tr>

    // Index for start of title
    var startingIndex = header.indexOf("<!-- TableTitle: ")
    // Index for end of title
    var closingIndex = header.indexOf(" -->");

    var titleString = "";
    var updatedHeader = header;

    // Only proceed if both indices are valid
    if (startingIndex !== -1 && closingIndex !== -1) {
        // Parse for the title. Should be: "<!-- TableTitle: Title -->"
        titleString = header.substring(startingIndex, closingIndex + 4);
        // Remove delimiters
        titleString = titleString.replace("<!-- TableTitle: ", "");
        titleString = titleString.replace(" -->", "");
        // Remove the title from the header
        updatedHeader = header.substring(0, startingIndex) + header.substring(closingIndex + 4);
    }
  
    if (body) body = `<tbody>${body}</tbody>`;

    // Use the title string for aria-label so that it is announced by screen readers
    return '<table aria-label="' + titleString + '">\n'
      + '<thead>\n'
      + updatedHeader
      + '</thead>\n'
      + body
      + '</table>\n';
  }
})