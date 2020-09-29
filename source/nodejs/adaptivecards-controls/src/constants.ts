// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
/**
 * @deprecated Use Constants.keys.tab instead.
 */
export const KEY_TAB = "Tab";
/**
 * @deprecated Use Constants.keys.enter instead.
 */
export const KEY_ENTER = "Enter";
/**
 * @deprecated Use Constants.keys.escape instead.
 */
export const KEY_ESCAPE = "Escape";
/**
 * @deprecated Use Constants.keys.space instead.
 */
export const KEY_SPACE = " ";
/**
 * @deprecated Use Constants.keys.up instead.
 */
export const KEY_UP = "Up";
/**
 * @deprecated Use Constants.keys.down instead.
 */
export const KEY_DOWN = "Down";
/**
 * @deprecated Use Constants.keys.delete instead.
 */
export const KEY_DELETE = "Delete";

export class Constants {
    static readonly keys = {
        tab: "Tab",
        enter: "Enter",
        escape: "Escape",
        space: " ",
        up: "Up",
        down: "Down",
        delete: "Delete"
    } as const;
}
