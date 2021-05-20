# Table element for Adaptive Cards
This is a proposal for a simple Table element. The main goals of this element are:
- To allow the creation of table layouts in a straightforward way, as opposed to using a stack of ColumnSet elements which leads to a larger (potentially much larger) payload and potential headaches wrt column sizing
- To allow accessibility software to present table layouts as such, which is currently impossible

This is NOT a proposal for an advanced Table with features such as:
- Dynamic column sizing
- Dynamic column reordering
- Sorting by columns
- Etc.

## Design
### Table
| Name | Type | Required | Description |
| --- | --- | --- | --- |
| `columns` | `TableColumnDefinition[]` | No | Defines the table's columns (number of columns, and column sizes). See `TableColumnDefinition` below. |
| `rows` | `TableRow[]` | No | Defines the rows of the Table, each being a collection of cells. See `TableRow` below. Rows are not required, which allows empty Tables to be generated via templating without breaking the rendering of the whole card. |
| `showGridLines` | `Boolean` | No | Specifies if grid lines should be displayed around the table and its cells. Defaults to `true`. |
| `gridStyle` | string | No | When `showGridLines` is set to `true`, `gridStyle` controls the color of the grid. Its value must be a valid container style name (emphasis, accent, etc.). If `gridStyle` isn't specified, the style used is inherited from the Table's parent container.  This feature requires adding support for border colors in HostConfig (see below). |
| `horizontalCellContentAlignment` | `HorizontalAlignment` | No | Specifies how the content of each cell should be horizontally aligned by default. Defaults to `left`. This value can be overridden by setting `horizontalCellContentAlignment` on a column or row, or by setting the `horizontalAlignment` property on each individual element in a cell. |
| `verticalCellContentAlignment` | `VerticalAlignment` | No | Specifies how the content of each cell should be vertically aligned by default. Defaults to `top`. This value can be overridden by setting `verticalCellContentAlignment` on a column, row or cell. |
| `firstRowAsHeaders` | `Boolean` | No | Defines whether the first row of the Table should be treated as a header row. Defaults to `true`. When `firstRowAsHeaders` is set to true, that row and its cells will be recognized as such by accessibility software. A cell belonging to the header row will also apply the "columnHeader" text styles to all text blocks it contains. |

#### Notes on rendering Table

Examples:
![image](https://user-images.githubusercontent.com/1334689/115600996-1ec3b780-a292-11eb-98a9-ab534e1a7362.png)
![image](https://user-images.githubusercontent.com/1334689/115601162-4b77cf00-a292-11eb-86d5-0c1c81e5406a.png)

- When `showGridLines` is set to `true` (the default) a 1px wide grid should appear all around the table and in between cells
  - `HostConfig.table.cellSpacing` does not apply and is ignored when grid lines are displayed
  - Each cell gets padding in order for their content to not be "stuck" against the grid lines

Example:
![image](https://user-images.githubusercontent.com/1334689/115601270-6e09e800-a292-11eb-9634-8eee7296138d.png)


### TableColumnDefinition
| Name | Type | Required | Description |
| --- | --- | --- | --- |
| `horizontalCellContentAlignment` | `HorizontalAlignment` | No | Specifies how the content of each cell should be horizontally aligned by default within the column. Defaults to `left`. This value override the table setting, and can itself be overridden by setting `horizontalCellContentAlignment` on a row or by setting the `horizontalAlignment` property on each individual element in a cell. |
| `verticalCellContentAlignment` | `VerticalAlignment` | No | Specifies how the content of each cell should be vertically aligned by default within the column. Defaults to `top`. This value overrides the table setting and can itself be overridden by setting `verticalCellContentAlignment` on a row or cell. |
| `width` | `number` or `string` | No | Defines the width of the column. When expressed as a string, width represents an explicit number of pixels, and must be in the format "<positive number>px", e.g. "80px". When expressed as a number, width represents the weight of the column within the table. |

#### Computing effective column widths
- First, all explicitly sized columns are get the space they request
- The remaining space is then split between weighted columns according to their individual weight
  - Weights can be expressed as any positive number
  - The sum of all weights in a Table does not have to equal 100

### TableRow
| Name | Type | Required | Description |
| --- | --- | --- | --- |
| `cells` | `TableCell[]` | No | Defines the cells for this particular row. See `TableCell` below. When a row doesn't contain as many cells as there are columns defined on the Table, the remaining columns remain empty for that row. If there are more cells in a row than there are columns defined on the Table, the extra cells are not rendered. |
| `horizontalCellContentAlignment` | `HorizontalAlignment` | No | Specifies how the content of each cell should be horizontally aligned by default within the row. Defaults to `left`. This value override the table and column settings, and can itself be overridden by setting the `horizontalAlignment` property on each individual element in a cell. |
| `verticalCellContentAlignment` | `VerticalAlignment` | No | Specifies how the content of each cell should be vertically aligned by default within the row. Defaults to `top`. This value overrides the table and column settings and can itself be overridden by setting `verticalCellContentAlignment` on a cell. |
| `style` | `string` | No | Specifies the style of that row in terms of background color. `style` must be set to a valid container style name. When not specified, style is inherited from the row's parent container. |

### TableCell
`TableCell` extends `Container`, and thus inherits `Container`'s properties. It doesn't introduce additional properties.

As a descendent of `Container`, `TableCell` can contain any Adaptive Card element, including ColumnSet or even other Table elements.

### HostConfig changes
#### Introducing `borderColor` in container styles
In order to support grid lines (and furthermore stylable grid lines), a new `borderColor` property needs to be added in container style definitions in HostConfig.

Example:
```
{
    ...
    "containerStyles": {
        ...
        "accent": {
            "borderColor": "#62A8F7",
            "backgroundColor": "#C7DEF9",
            "foregroundColors": {
                "default": {
                    "default": "#333333",
                    "subtle": "#EE333333"
                },
                ...
            }
        },
        ...
    }
    ...
}
```

**NOTE**: given the above, we should consider adding the ability to put a border on any container.

#### Introducing the "columnHeader" text style
As mentioned above, cells that belong to the header row should apply a specific style to the TextBlocks they contains by default. Typically, text in header cells will be bold.

This will be done by applying by default a new "columnHeader" text style to header cells. Like with all text styles, it can be overridden by each individual TextBlock by setting their `size`, `weight`, `color`, `isSubtle` and `fontType` properties.

Example host config text styles section:
```
{
    ...
    "textStyles": {
        "columnHeader": {
            "size": "default",
            "weight": "bolder",
            "color": "default",
            "isSubtle": "false",
            "fontType": "default"
        },
        ...
    }
    ...
}
```
#### Introducing the `table` config, and its `cellSpacing` property

New `HostConfig.table.cellSpacing` property of number type is added, which represents an explicit number of pixels. This controls the empty space between cells both horizontally (between rows) and vertically (between columns).

This value is only used in the absence of grid lines and bleed. Formally, given any two adjacent cells, spacing must be applied between them if and only if:
  - the cells are in a `Table` with `showGridLines: false`
  - AND at least one of the two cells has `bleed: false`

`cellSpacing` must be greater than or equal to zero. Any other value will be interpreted as 0

The default value is 8

Each cell can have its own style (and thus background color). When rendering space between styled columns, empty space must visually appear.

Example:
```
{
    ...
    "table": {
        "cellSpacing": 8
    }
    ...
}
```

## Sample card
```json
{
    "type": "AdaptiveCard",
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "version": "1.3",
    "body": [
        {
            "type": "Table",
            "columns": [
                {
                    "width": 1
                },
                {
                    "width": 1
                },
                {
                    "width": 3
                }
            ],
            "rows": [
                {
                    "type": "TableRow",
                    "cells": [
                        {
                            "type": "TableCell",
                            "items": [
                                {
                                    "type": "TextBlock",
                                    "text": "Name",
                                    "wrap": true,
                                    "weight": "Bolder"
                                }
                            ]
                        },
                        {
                            "type": "TableCell",
                            "items": [
                                {
                                    "type": "TextBlock",
                                    "text": "Type",
                                    "wrap": true,
                                    "weight": "Bolder"
                                }
                            ]
                        },
                        {
                            "type": "TableCell",
                            "items": [
                                {
                                    "type": "TextBlock",
                                    "text": "Description",
                                    "wrap": true,
                                    "weight": "Bolder"
                                }
                            ]
                        }
                    ],
                    "style": "accent"
                },
                {
                    "type": "TableRow",
                    "cells": [
                        {
                            "type": "TableCell",
                            "items": [
                                {
                                    "type": "TextBlock",
                                    "text": "columns",
                                    "wrap": true
                                }
                            ]
                        },
                        {
                            "type": "TableCell",
                            "items": [
                                {
                                    "type": "TextBlock",
                                    "text": "TableColumnDefinition[]",
                                    "wrap": true
                                }
                            ]
                        },
                        {
                            "type": "TableCell",
                            "items": [
                                {
                                    "type": "TextBlock",
                                    "text": "Defines the table's columns (number of columns, and column sizes).",
                                    "wrap": true
                                }
                            ]
                        }
                    ]
                },
                {
                    "type": "TableRow",
                    "cells": [
                        {
                            "type": "TableCell",
                            "items": [
                                {
                                    "type": "TextBlock",
                                    "text": "rows",
                                    "wrap": true
                                }
                            ]
                        },
                        {
                            "type": "TableCell",
                            "items": [
                                {
                                    "type": "TextBlock",
                                    "text": "TableRow[]",
                                    "wrap": true
                                }
                            ]
                        },
                        {
                            "type": "TableCell",
                            "items": [
                                {
                                    "type": "TextBlock",
                                    "text": "Defines the rows of the Table, each being a collection of cells. Rows are not required, which allows empty Tables to be generated via templating without breaking the rendering of the whole card.",
                                    "wrap": true
                                }
                            ]
                        }
                    ]
                }
            ],
            "gridStyle": "accent"
        }
    ]
}
```

As rendered:
![image](https://user-images.githubusercontent.com/1334689/114483909-14345e80-9bbe-11eb-897f-564a812ec210.png)
