export declare class FullScreenHandler {
    private fullScrerenChanged;
    onFullScreenChanged: (isFullScreen: boolean) => void;
    constructor();
    enterFullScreen(): void;
    exitFullScreen(): void;
    toggleFullScreen(): void;
    readonly isFullScreen: boolean;
}
