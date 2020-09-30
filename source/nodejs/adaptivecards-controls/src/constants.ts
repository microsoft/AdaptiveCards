// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
/**
 * @deprecated Use Constants.keys.tab instead.
 */
export const KEY_TAB = 9;
/**
 * @deprecated Use Constants.keys.enter instead.
 */
export const KEY_ENTER = 13;
/**
 * @deprecated Use Constants.keys.escape instead.
 */
export const KEY_ESCAPE = 27;
/**
 * @deprecated Use Constants.keys.space instead.
 */
export const KEY_SPACE = 32;
/**
 * @deprecated Use Constants.keys.up instead.
 */
export const KEY_UP = 38;
/**
 * @deprecated Use Constants.keys.down instead.
 */
export const KEY_DOWN = 40;
/**
 * @deprecated Use Constants.keys.delete instead.
 */
export const KEY_DELETE = 46;

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
