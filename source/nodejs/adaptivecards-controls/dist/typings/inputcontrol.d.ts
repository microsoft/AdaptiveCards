export declare abstract class InputControl {
    private _rootElement;
    protected validateRootElement(rootElement: HTMLElement): void;
    protected keyDown(e: KeyboardEvent): void;
    protected readonly rootElement: HTMLElement;
    attach(rootElement: HTMLElement): void;
}
