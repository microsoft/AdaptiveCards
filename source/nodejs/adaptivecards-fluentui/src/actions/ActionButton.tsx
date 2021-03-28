// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import { PrimaryButton, CompoundButton } from "@fluentui/react";
import * as AC from "adaptivecards";

export interface ActionButtonProps {
    text: string;
    className?: string;
    iconUrl?: string;
    iconPlacement?: AC.ActionIconPlacement;
    iconSize?: number;
}

export const ActionButton = (props: ActionButtonProps) => (
    props.iconUrl ?
        <CompoundButton className={props.className} >
            <div style={
                {
                    display: "flex",
                    flexDirection: props.iconPlacement === AC.ActionIconPlacement.LeftOfTitle ? "row" : "column",
                    justifyContent: "center",
                }
            }><img src={props.iconUrl}
                style={
                    {
                        alignSelf: "center",
                        width: props.iconSize,
                        height: props.iconSize,
                        flex: "0 0 auto",
                    }
                } />
                <span style={{ alignSelf: "center" }}>{props.text}</span>
            </div>
        </CompoundButton> :
        <PrimaryButton
            className={props.className}
            text={props.text} />
);
