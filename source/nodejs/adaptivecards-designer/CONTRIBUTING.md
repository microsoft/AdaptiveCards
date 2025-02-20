# Contributing to the Designer
This document covers information to help those wanting to contribute to the Adaptive Cards Designer.

## How to use the designer
The designer can be used in a few different ways.
1. Hosted on adaptivecards.io
2. Shipped as a standalone package. This allows developers to use the designer within their own sites and customize it.
3. Standalone app

## Renderer
Its important to note that the designer utilizes the javascript renderer **only**. The version that the designer uses can be configured by the container and by the user.

## Styling
Default styling for the designer is found at `src/adaptivecards-designer.css`. Note that containers also have styling for the rendered cards.

## `card-designer.ts`
The bulk of the designer is found within `src/card-designer.ts`. Most handling for the following features is included here:
1. Toolbar functionality
5. Card elements pane
6. Card surface
7. Card payload editor
8. Sample data editor
9. Card structure pane
10. Element properties pane
11. Error pane

Since the designer is meant to be extensible to external developers and resilient to new feautres, most of these features are implemented with shared classes. Notably:
- `Toolbar`
- `ToolbarButton`
- `ToolbarChoicePicker`
- `BasePaletteItem`
- `ElementPaletteItem`
- `DataPaletteItem`
- `SidePanel`
- `DataTreeItem`
- `TreeView`

The idea here is that you can simply create a new `ToolbarButton` when you want to add a new button to the main toolbar.

## Card Designer Surface
The area of the designer that displays the card is called the `CardDesignerSurface` (See `src/card-designer-surface.ts`).
It is easiest to think about the surface in two modes.

### Preview mode
When the designer is in preview mode, we will display the card as it is rendered. That is, you cannot modify the card without editing the JSON manually. This version is the most straighforward as there are no features beyond the renderer.

### Design mode
In design mode, the card designer surface is more complicated, because all card elements have an paired element called a `DesignerPeer` (See `src/designer-peers.ts`). That is, when we render the card in design mode, there will be a DesignerPeer overlaid on top of each element.
![image](https://github.com/user-attachments/assets/f9ecf217-6fe7-4ac5-a1a6-18429b2b1250)

The peers allow us to enable a drag and drop interface for the designer. For some element peers, we also have additional buttons attached that add functionality (Example: `ColumnSetPeer` include an "Add a column" button).

The goal of design mode is to allow developers to design the card **without** manually modifyin the JSON editor. When an element has been moved, deleted, or modified from the card surface, the JSON editor will reflect the changes.

## Containers
The designer has a concept of a "container" that allows us to mock a specific host app. The default containers can be found within `adaptivecards-designer/src/containers`. Containers can specify their own styling and custom rendering. When a designer container is initialized, we will render the container and attach it to the designer host (See `src/card-designer.ts`).

For instance, we have a container for the Widgets Board which allows for different themes and container sizes.
<img width="695" alt="image" src="https://github.com/user-attachments/assets/bf323569-3c0e-4778-9742-c4536ed008eb" />

Containers can also specify their own Host Config, and these are stored at `samples/HostConfig/`.

## Templating

## Card elements pane

## Element properties pane

## `adaptivecards-controls` usage

