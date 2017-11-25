import { Action, HostConfig } from "./adaptivecards";
import { IAdaptiveCard } from "./schema";
export interface RenderOptions {
    hostConfig?: HostConfig | string | object;
    onAction?: (action: Action) => void;
    onValidationError?: (error: string) => void;
}
export declare function render(card: IAdaptiveCard | string, options?: RenderOptions): HTMLElement;
