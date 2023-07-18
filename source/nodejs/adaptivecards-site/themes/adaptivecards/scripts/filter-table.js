// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// Used for custom rendering of the table element
// We assume that the first header row cell contains the title of the table
// We then remove the cell from the table html
hexo.extend.filter.register('marked:renderer', function(renderer) {
  renderer.table = function(header, body) {

    // Example header string:
    // <tr>
    // <th>{Title here}</th>
    // <th>Property</th>
    // <th>Type</th>
    // <th>Required</th>
    // <th>Description</th>
    // <th>Version</th>
    // </tr>

    // Index of the closing tag for the first cell
    var closingIndex = header.indexOf("</th>");
    // Parse for the title
    var titleString = header.substring(9, closingIndex);
    // Parse for the remaining header row cells
    var remainingCells = header.substring(closingIndex + 5);
  
    if (body) body = `<tbody>${body}</tbody>`;

    return '<table aria-label="' + titleString + '">\n'
      + '<thead>\n'
      + '<tr>\n'
      + remainingCells
      + '</thead>\n'
      + body
      + '</table>\n';
  }
})