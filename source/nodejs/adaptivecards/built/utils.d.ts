import * as Enums from "./enums";
export interface ISeparationDefinition {
    spacing: number;
    lineThickness?: number;
    lineColor?: string;
}
export interface IInput {
    id: string;
    value: string;
}
export declare function processMarkdown(text: string): any;
export declare function getValueOrDefault<T>(obj: any, defaultValue: T): T;
export declare function isNullOrEmpty(value: string): boolean;
export declare function appendChild(node: Node, child: Node): void;
export declare function getEnumValueOrDefault(targetEnum: {
    [s: number]: string;
}, name: string, defaultValue: number): number;
export declare function parseHostConfigEnum(targetEnum: {
    [s: number]: string;
}, value: string | number, defaultValue: any): any;
export declare function renderSeparation(separationDefinition: ISeparationDefinition, orientation: Enums.Orientation): HTMLElement;
export declare function stringToCssColor(color: string): string;
export declare class StringWithSubstitutions {
    private _isProcessed;
    private _original;
    private _processed;
    substituteInputValues(inputs: Array<IInput>): void;
    get(): string;
    set(value: string): void;
}
