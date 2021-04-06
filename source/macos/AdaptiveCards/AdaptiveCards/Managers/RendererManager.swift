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
        case .container: return ContainerRenderer.shared
        case .dateInput: return InputDateRenderer.shared
        case .timeInput: return InputTimeRenderer.shared
        case .imageSet: return ImageSetRenderer.shared
        case .actionSet: return ActionSetRenderer.shared
        default: return UnknownElementRenderer.shared
        }
    }
    
    func actionRenderer(for elementType: ACSActionType) -> BaseActionElementRendererProtocol {
        switch elementType {
        case .openUrl: return ActionOpenURLRenderer.shared
        case .submit: return ActionSubmitRenderer.shared
        case .showCard: return ActionShowCardRenderer.shared
        default: return UnknownElementRenderer.shared
        }
    }
}
