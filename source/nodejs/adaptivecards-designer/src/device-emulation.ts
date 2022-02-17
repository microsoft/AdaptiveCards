// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

export abstract class DeviceEmulation {
  readonly name: string;
  readonly styleSheet: string;

  constructor(name: string, styleSheet: string) {
    this.name = name;
    this.styleSheet = styleSheet;
  }

}
