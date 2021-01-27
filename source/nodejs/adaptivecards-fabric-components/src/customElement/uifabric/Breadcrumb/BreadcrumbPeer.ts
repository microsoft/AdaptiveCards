import { CardElementPeerInplaceEditor, DesignContext, DesignerPeerInplaceEditor, EnumPropertyEditor, FieldPicker, NumberPropertyEditor, PeerCommand, PropertySheet, PropertySheetCategory, StringPropertyEditor, TypedCardElementPeer } from "adaptivecards-designer";
import { Breadcrumb } from "./Breadcrumb";
import * as Adaptive from 'adaptivecards';
import * as Enums from 'adaptivecards/lib/enums'


class BreadcrumbPeerInplaceEditor extends CardElementPeerInplaceEditor<Breadcrumb> {
    private _renderedElement: HTMLTextAreaElement;

    private close(applyChanges: boolean) {
        if (this.onClose) {
            this.onClose(applyChanges);
        }
    }

    initialize() {
        this._renderedElement.select();
    }

    applyChanges() {
        this.cardElement.items = this._renderedElement.value;
    }

    render() {
        this._renderedElement = document.createElement("textarea");
        this._renderedElement.className = "acd-breadcrumb-inplace-editor";
        this._renderedElement.value = this.cardElement.items;
        this._renderedElement.onkeydown = (e) => {
            switch (e.key) {
                case "Escape":
                   this.close(false);

                   e.preventDefault();
                   e.cancelBubble = true;

                   break;
                case "Enter":
                    this.close(true);

                    e.preventDefault();
                    e.cancelBubble = true;

                    break;
            }

            return !e.cancelBubble;
        };

        // this.cardElement.applyStylesTo(this._renderedElement);

        return this._renderedElement;
    }
}

export class BreadcrumbPeer extends TypedCardElementPeer<Breadcrumb> {
    static readonly itemsProperty = new StringPropertyEditor(Adaptive.Versions.v1_2, "items", "Items", true, true);
    static readonly fontTypeProperty = new EnumPropertyEditor(Adaptive.Versions.v1_2, "fontType", "Font type", Adaptive.FontType);
    static readonly sizeProperty = new EnumPropertyEditor(Adaptive.Versions.v1_2, "size", "Size", Adaptive.TextSize);
    static readonly weightProperty = new EnumPropertyEditor(Adaptive.Versions.v1_2, "weight", "Weight", Adaptive.TextWeight);
    static readonly colorProperty = new EnumPropertyEditor(Adaptive.Versions.v1_2, "color", "color", Adaptive.TextColor);
    

    protected createInplaceEditor(): DesignerPeerInplaceEditor {
        return new BreadcrumbPeerInplaceEditor(this.cardElement);
    }

    protected internalGetTreeItemText(): string {
        return this.cardElement.items;
    }

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

        if (context.dataStructure) {
            commands.push(
                new PeerCommand(
                    {
                        name: "Bind...",
                        alwaysShowName: true,
                        toolTip: "Select a data field to bind this Breadcrumb to.",
                        execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                            let fieldPicker = new FieldPicker(context.dataStructure);
                            fieldPicker.onClose = (sender, wasCancelled) => {
                                if (!wasCancelled) {
                                    this.cardElement.items = fieldPicker.selectedField.asExpression();

                                    this.changed(true);
                                }
                            }
                            fieldPicker.popup(clickedElement);
                        }
                    })
            );
        }
    }

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            BreadcrumbPeer.itemsProperty);

        // propertySheet.add(
        //     PropertySheetCategory.LayoutCategory,
        //     TextBlockPeer.wrapProperty,
        //     TextBlockPeer.maxLinesProperty);

        propertySheet.add(
            PropertySheetCategory.StyleCategory,
            BreadcrumbPeer.fontTypeProperty,
            BreadcrumbPeer.sizeProperty,
            BreadcrumbPeer.weightProperty,
            BreadcrumbPeer.colorProperty);
    }

    getToolTip(): string {
        return "Double click to edit";
    }

    initializeCardElement() {
        if (!this.cardElement.items || this.cardElement.items == "") {
            this.cardElement.items = "[{\"text\":\"Folder 1\",\"key\":\"f4\"},{\"text\":\"Folder 2\",\"key\":\"f2\"},{\"text\":\"Folder 3\",\"key\":\"f3\"}]";
        }
        this.cardElement.fontType = Enums.FontType.Default;
        this.cardElement.size = Enums.TextSize.Default;
        this.cardElement.weight = Enums.TextWeight.Default;
        this.cardElement.color = Enums.TextColor.Default;
    }
}