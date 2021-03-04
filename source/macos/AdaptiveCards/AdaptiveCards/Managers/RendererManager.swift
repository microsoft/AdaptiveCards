import AdaptiveCards_bridge
import AppKit

protocol RendererManagerProtocol { }

class RendererManager: RendererManagerProtocol {
    static let shared = RendererManager()
    
    func renderer(for elementType: ACSCardElementType) -> BaseCardElementRendererProtocol {
        switch elementType {
        case .textBlock: return TextBlockRenderer.shared
        case .richTextBlock: return RichTextBlockRenderer.shared
        case .toggleInput: return InputToggleRenderer.shared
        case .numberInput: return InputNumberRenderer.shared
        case .textInput: return TextInputRenderer.shared
        case .choiceSetInput: return ChoiceSetInputRenderer.shared
        case .factSet: return FactSetRenderer.shared
        case .columnSet: return ColumnSetRenderer.shared
        case .column: return ColumnRenderer.shared
        case .image: return ImageRenderer.shared
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
        view.heightAnchor.constraint(equalToConstant: 20).isActive = true
        view.widthAnchor.constraint(equalToConstant: 20).isActive = true
        return view
    }
}
