// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// Used for custom rendering of the table element
// We assume that the first header row cell contains the title of the table, wrapped in braces
// We then remove the title from the first cell
hexo.extend.filter.register('marked:renderer', function(renderer) {
  renderer.table = function(header, body) {

    // Example header string:
    // <tr>
    // <th>{ActionSet Inherited properties}Property</th>
    // <th>Type</th>
    // <th>Required</th>
    // <th>Description</th>
    // <th>Version</th>
    // </tr>

    // Index of the end of the title
    var closingIndex = header.indexOf("}");
    // Parse for the title
    var titleString = header.substring(10, closingIndex);
    // Remove the title from the header
    var updatedHeader = header.substring(0, 9) + header.substring(closingIndex + 1);
  
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