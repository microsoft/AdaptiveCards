import { CardElementPeerInplaceEditor, DesignContext, DesignerPeerInplaceEditor, FieldPicker, PeerCommand, PropertySheet, PropertySheetCategory, StringPropertyEditor, TypedCardElementPeer } from "adaptivecards-designer";
import { Persona } from "./Persona";
import * as Adaptive from 'adaptivecards';


class PersonaPeerInplaceEditor extends CardElementPeerInplaceEditor<Persona> {
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
        this.cardElement.personaProps = this._renderedElement.value;
    }

    render() {
        this._renderedElement = document.createElement("textarea");
        this._renderedElement.className = "acd-persona-inplace-editor";
        this._renderedElement.value = this.cardElement.personaProps;
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

export class PersonaPeer extends TypedCardElementPeer<Persona> {
    static readonly personaPropsProperty = new StringPropertyEditor(Adaptive.Versions.v1_2, "personaProps", "Persona props", true, true);

    protected createInplaceEditor(): DesignerPeerInplaceEditor {
        return new PersonaPeerInplaceEditor(this.cardElement);
    }

    protected internalGetTreeItemText(): string {
        return this.cardElement.personaProps;
    }

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

        if (context.dataStructure) {
            commands.push(
                new PeerCommand(
                    {
                        name: "Bind...",
                        alwaysShowName: true,
                        toolTip: "Select a data field to bind this persona to.",
                        execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                            let fieldPicker = new FieldPicker(context.dataStructure);
                            fieldPicker.onClose = (sender, wasCancelled) => {
                                if (!wasCancelled) {
                                    this.cardElement.personaProps = fieldPicker.selectedField.asExpression();

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
            PersonaPeer.personaPropsProperty);
    }

    getToolTip(): string {
        return "Double click to edit";
    }

    initializeCardElement() {
        if (!this.cardElement.personaProps || this.cardElement.personaProps == "") {
            this.cardElement.personaProps = "{\"imageUrl\":\"https:\/\/static2.sharepointonline.com\/files\/fabric\/office-ui-fabric-react-assets\/persona-female.png\",\"imageInitials\":\"AL\",\"text\":\"Annie Lindqvist\",\"secondaryText\":\"Software Engineer\",\"tertiaryText\":\"In a meeting\",\"optionalText\":\"Available at 4:00pm\",\"size\": \"size120\", \"presence\": \"online\"}";
        }
    }
}