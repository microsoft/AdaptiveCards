import AdaptiveCards_bridge
import AppKit

protocol BaseInputHandler { }

protocol BaseCardElementRendererProtocol {
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView
}
