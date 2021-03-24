import AdaptiveCards_bridge
import AppKit

protocol BaseInputHandler { }

protocol BaseCardElementRendererProtocol {
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView
}

protocol BaseActionElementRendererProtocol {
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView
}

protocol TargetHandler: NSObject {
    var delegate: TargetHandlerDelegate? { get set }
    func configureAction(for button: NSButton)
}

protocol TargetHandlerDelegate: AnyObject {
    func handleOpenURLAction(button: NSButton, urlString: String)
    func handleSubmitAction(button: NSButton, dataJson: String?)
    func handleShowCardAction(button: NSButton, showCard: ACSAdaptiveCard)
}

protocol InputHandlingViewProtocol: NSView {
    var value: String { get }
    var key: String { get }
    var isValid: Bool { get }
}
