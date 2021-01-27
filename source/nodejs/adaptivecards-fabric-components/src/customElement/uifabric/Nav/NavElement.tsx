
import { Nav } from "@fluentui/react/lib/Nav";
import * as React from "react";

export const getNavElement = (groups: string): JSX.Element => {
    return (
        <Nav groups={JSON.parse(groups)}/>
    );
}