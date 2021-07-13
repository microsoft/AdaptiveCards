import AdaptiveCards_bridge
import AppKit

class UnknownElementRenderer: BaseCardElementRendererProtocol, BaseActionElementRendererProtocol {
    static let shared = UnknownElementRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        switch  element.getFallbackType() {
        case .content:
            guard let fallbackElement = element.getFallbackContent() as? ACSBaseCardElement else {
                logError("Fallback Content is not of type ACSBaseCardElement")
                return NSView()
            }
            return RendererManager.shared.renderer(for: fallbackElement.getType()).render(element: fallbackElement, with: hostConfig, style: style, rootView: rootView, parentView: parentView, inputs: inputs, config: config)
        case .none, .drop:
            return NSView()
        @unknown default:
            return NSView()
        }
    }
    
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, targetHandlerDelegate: TargetHandlerDelegate, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        return NSView()
    }
}
