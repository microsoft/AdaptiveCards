import { CardElementPeerInplaceEditor, DesignContext, DesignerPeerInplaceEditor, FieldPicker, PeerCommand, PropertySheet, PropertySheetCategory, StringPropertyEditor, TypedCardElementPeer } from "adaptivecards-designer";
import { Icon } from "./Icon";
import * as Adaptive from 'adaptivecards';


class IconPeerInplaceEditor extends CardElementPeerInplaceEditor<Icon> {
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
        this.cardElement.iconName = this._renderedElement.value;
    }

    render() {
        this._renderedElement = document.createElement("textarea");
        this._renderedElement.className = "acd-icon-inplace-editor";
        this._renderedElement.value = this.cardElement.iconName;
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

export class IconPeer extends TypedCardElementPeer<Icon> {
    static readonly iconNameProperty = new StringPropertyEditor(Adaptive.Versions.v1_2, "iconName", "Icon Name", true, true);

    protected createInplaceEditor(): DesignerPeerInplaceEditor {
        return new IconPeerInplaceEditor(this.cardElement);
    }

    protected internalGetTreeItemText(): string {
        return this.cardElement.iconName;
    }

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

        if (context.dataStructure) {
            commands.push(
                new PeerCommand(
                    {
                        name: "Bind...",
                        alwaysShowName: true,
                        toolTip: "Select a data field to bind this Icon to.",
                        execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                            let fieldPicker = new FieldPicker(context.dataStructure);
                            fieldPicker.onClose = (sender, wasCancelled) => {
                                if (!wasCancelled) {
                                    this.cardElement.iconName = fieldPicker.selectedField.asExpression();

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
            IconPeer.iconNameProperty);
    }

    getToolTip(): string {
        return "Double click to edit";
    }

    initializeCardElement() {
        if (!this.cardElement.iconName || this.cardElement.iconName == "") {
            this.cardElement.iconName = "Add";
        }
    }
}