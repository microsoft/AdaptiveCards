export interface FullScreenElement extends HTMLElement {
    mozRequestFullScreen: () => void
    msRequestFullscreen: () => void
    onfullscreenchange: (this: Element, ev: Event) => any;
    onmozfullscreenchange: (this: Element, ev: Event) => any;
    MSFullscreenChange: (this: Element, ev: Event) => any;
}

export interface FullScreenDocument extends Document {
    exitFullscreen: () => void
    webkitExitFullscreen: () => void
    mozCancelFullScreen: () => void
    msExitFullscreen: () => void
    fullscreen: boolean
    webkitIsFullScreen: boolean
    mozFullScreen: boolean
}
