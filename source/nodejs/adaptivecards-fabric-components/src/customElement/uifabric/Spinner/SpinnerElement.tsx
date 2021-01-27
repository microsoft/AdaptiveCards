import { Spinner, SpinnerSize } from "@fluentui/react/lib/Spinner";
import * as React from "react";

export const getSpinnerElement = (size: string): JSX.Element => {
    let spinnerSize = SpinnerSize[size]; //assuming size is valid string
    return (
        <Spinner size={spinnerSize}/>
    );
}