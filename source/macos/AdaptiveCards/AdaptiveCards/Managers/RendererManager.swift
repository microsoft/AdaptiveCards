import AdaptiveCards_bridge
import AppKit

protocol RendererManagerProtocol { }

class RendererManager: RendererManagerProtocol {
    static let shared = RendererManager()
    
    func renderer(for elementType: ACSCardElementType) -> BaseCardElementRendererProtocol {
        switch elementType {
        case .textBlock: return TextBlockRenderer.shared
        default: return UnknownElementRenderer.shared
        }
    }
}

class UnknownElementRenderer: BaseCardElementRendererProtocol {
    static let shared = UnknownElementRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        let view = NSView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.wantsLayer = true
        view.layer?.backgroundColor = NSColor.red.cgColor
        view.heightAnchor.constraint(equalToConstant: 50).isActive = true
        return view
    }
}
