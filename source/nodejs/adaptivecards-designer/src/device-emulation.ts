// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

export abstract class DeviceEmulation {
  readonly name: string;
  readonly maxWidth: string | null;

  constructor(name: string, maxWidth: string | null) {
    this.name = name;
    this.maxWidth = maxWidth;
  }

}
