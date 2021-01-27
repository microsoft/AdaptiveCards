import { CardElementPeerInplaceEditor, DesignContext, DesignerPeerInplaceEditor, FieldPicker, PeerCommand, PropertySheet, PropertySheetCategory, StringPropertyEditor, TypedCardElementPeer } from "adaptivecards-designer";
import { ProgressIndicator } from "./ProgressIndicator";
import * as Adaptive from 'adaptivecards';


class ProgressIndicatorPeerInplaceEditor extends CardElementPeerInplaceEditor<ProgressIndicator> {
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
        this.cardElement.label = this._renderedElement.value;
    }

    render() {
        this._renderedElement = document.createElement("textarea");
        this._renderedElement.className = "acd-progressIndicator-inplace-editor";
        this._renderedElement.value = this.cardElement.label;
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

export class ProgressIndicatorPeer extends TypedCardElementPeer<ProgressIndicator> {
    static readonly labelProperty = new StringPropertyEditor(Adaptive.Versions.v1_2, "label", "Label", true, true);
    static readonly descriptionProperty = new StringPropertyEditor(Adaptive.Versions.v1_2, "description", "Description", true, true);

    protected createInplaceEditor(): DesignerPeerInplaceEditor {
        return new ProgressIndicatorPeerInplaceEditor(this.cardElement);
    }

    protected internalGetTreeItemText(): string {
        return this.cardElement.label;
    }

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

        if (context.dataStructure) {
            commands.push(
                new PeerCommand(
                    {
                        name: "Bind...",
                        alwaysShowName: true,
                        toolTip: "Select a data field to bind this progress indicator to.",
                        execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                            let fieldPicker = new FieldPicker(context.dataStructure);
                            fieldPicker.onClose = (sender, wasCancelled) => {
                                if (!wasCancelled) {
                                    this.cardElement.label = fieldPicker.selectedField.asExpression();

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
            ProgressIndicatorPeer.labelProperty,
            ProgressIndicatorPeer.descriptionProperty);
    }

    getToolTip(): string {
        return "Double click to edit";
    }

    initializeCardElement() {
        if (!this.cardElement.label || this.cardElement.label == "") {
            this.cardElement.label = "Indicator";
        }
        if (!this.cardElement.description || this.cardElement.description == "") {
            this.cardElement.description = "Loading details";
        }
    }
}