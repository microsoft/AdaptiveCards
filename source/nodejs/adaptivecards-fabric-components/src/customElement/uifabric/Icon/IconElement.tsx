import { Icon } from "@fluentui/react/lib/Icon";
import * as React from "react";

export const getIconElement = (iconName: string): JSX.Element => {
    return (
        <Icon iconName={iconName}/>
    );
}