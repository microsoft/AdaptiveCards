import AdaptiveCards_bridge
import AppKit

protocol BaseInputHandler { }

protocol BaseCardElementRendererProtocol {
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView
}

protocol BaseActionElementRendererProtocol {
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView
}

protocol TargetHandler: NSObject {
    var delegate: TargetHandlerDelegate? { get set }
    func configureAction(for button: NSButton)
    func handleSelectionAction(for actionView: NSView)
}

protocol TargetHandlerDelegate: AnyObject {
    func handleOpenURLAction(actionView: NSView, urlString: String)
    func handleSubmitAction(actionView: NSView, dataJson: String?)
    func handleShowCardAction(button: NSButton, showCard: ACSAdaptiveCard)
}

protocol InputHandlingViewProtocol: NSView {
    var value: String { get }
    var key: String { get }
    var isValid: Bool { get }
}
