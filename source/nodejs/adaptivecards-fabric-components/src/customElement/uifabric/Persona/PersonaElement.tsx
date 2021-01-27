
import { Persona, PersonaSize, PersonaPresence } from "@fluentui/react/lib/Persona";
import * as React from "react";

export const getPersonaElement = (personaProps: string): JSX.Element => {
    const props = JSON.parse(personaProps);
    props.size = PersonaSize[props.size];
    props.presence = PersonaPresence[props.presence];
    return (
        <Persona {...props}/>
    );
}