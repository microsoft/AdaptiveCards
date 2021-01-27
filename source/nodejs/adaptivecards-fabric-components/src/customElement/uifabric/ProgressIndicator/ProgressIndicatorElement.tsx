
import { ProgressIndicator } from "@fluentui/react/lib/ProgressIndicator";
import * as React from "react";

export const getProgressIndicatorElement = (label: string = '', description: string = ''): JSX.Element => {
    return (
        <ProgressIndicator label={label} description={description}/>
    );
}