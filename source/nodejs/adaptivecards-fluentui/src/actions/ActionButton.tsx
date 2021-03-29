// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import { PrimaryButton, CompoundButton, DefaultButton } from "@fluentui/react";
import * as AC from "adaptivecards";

export interface ActionButtonProps {
  action: AC.Action;
  className?: string;
  iconPlacement?: AC.ActionIconPlacement;
  iconSize?: number;
}

export const ActionButton = (props: ActionButtonProps) => {
  if (props.action.iconUrl) {
    return (
      <CompoundButton className={props.className}>
        <div
          style={{
            display: "flex",
            flexDirection:
              props.iconPlacement === AC.ActionIconPlacement.LeftOfTitle
                ? "row"
                : "column",
            justifyContent: "center",
          }}
        >
          <img
            src={props.action.iconUrl}
            style={{
              alignSelf: "center",
              width: props.iconSize,
              height: props.iconSize,
              flex: "0 0 auto",
            }}
          />
          <span style={{ alignSelf: "center" }}>{props.action.title}</span>
        </div>
      </CompoundButton>
    );
  } else if (props.action.style === AC.ActionStyle.Positive) {
    return (
      <PrimaryButton className={props.className} text={props.action.title} />
    );
  } else {
    return (
      <DefaultButton className={props.className} text={props.action.title} />
    );
  }
};
