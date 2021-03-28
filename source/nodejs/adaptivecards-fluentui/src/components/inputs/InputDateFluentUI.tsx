// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as FluentUI from "@fluentui/react";
import * as AC from "adaptivecards";
import * as Shared from "../../utils/shared";

export class InputDateFluentUI extends AC.DateInput {
  private handleSelectDate = (date: Date) => {
    this._value = date
      .toLocaleString(window.navigator.language, {
        year: "numeric",
        month: "2-digit",
        day: "2-digit",
      })
      .replace(/(\d+)\/(\d+)\/(\d+)/, "$3-$1-$2");
  };

  private _value;
  public get value(): any {
    return this._value || this.defaultValue;
  }

  public isSet(): any {
    return this._value !== undefined || this.defaultValue !== undefined;
  }

  protected internalRender(): HTMLElement {
    const element = Shared.sharedInternalRender(this.renderReact);

    element.style.width = "100%";
    return element;
  }

  private getDate = (
    dateString: string,
    errors?: AC.IValidationEvent[]
  ): Date => {
    try {
      return new Date(dateString + "T00:00:00");
    } catch (error) {
      Shared.raiseParseError(
        {
          phase: AC.ValidationPhase.Parse,
          event: AC.ValidationEvent.InvalidPropertyValue,
          message: error,
        },
        errors
      );
      return undefined;
    }
  };

  // NOT WORKING
  private onFormatDate = (date?: Date): string => {
    return !date
      ? ""
      : date.toLocaleString(window.navigator.language, { weekday: "short" }) +
          " " +
          (date.getMonth() + 1) +
          "/" +
          date.getDay() +
          "/" +
          date.getFullYear();
  };

  private onParseDateFromString = (val: string): Date => {
    const date = this.value || new Date();
    // const values = (val || '').trim().split('/');
    // const day = val.length > 0 ? Math.max(1, Math.min(31, parseInt(values[0], 10))) : date.getDate();
    // const month = val.length > 1 ? Math.max(1, Math.min(12, parseInt(values[1], 10))) - 1 : date.getMonth();
    // let year = val.length > 2 ? parseInt(values[2], 10) : date.getFullYear();
    // if (year < 100) {
    //   year += date.getFullYear() - (date.getFullYear() % 100);
    // }
    return new Date(this.defaultValue);
    //return new Date(year, month, day);
  };

  private renderReact = (): JSX.Element => {
    return (
      <FluentUI.DatePicker
        id={this.id}
        onSelectDate={this.handleSelectDate}
        value={this.defaultValue ? this.getDate(this.defaultValue) : undefined}
        //label={this.label}
        placeholder={this.placeholder}
        //formatDate={this.onFormatDate}
        //allowTextInput={true}
        parseDateFromString={this.onParseDateFromString}
        minDate={this.min ? this.getDate(this.min) : undefined}
        maxDate={this.max ? this.getDate(this.max) : undefined}
      />
    );
  };
}
