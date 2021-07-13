import AdaptiveCards_bridge
import AppKit

class ActionShowCardRenderer: BaseActionElementRendererProtocol {
    static let shared = ActionShowCardRenderer()
    
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, targetHandlerDelegate: TargetHandlerDelegate, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let showCardAction = action as? ACSShowCardAction else {
            logError("Element is not of type ACSShowCardAction")
            return NSView()
        }
        
        let button: ACRButton
        let buttonStyle = ActionStyle(rawValue: showCardAction.getStyle() ?? "") ?? .default
        if let iconUrl = showCardAction.getIconUrl(), !iconUrl.isEmpty {
            button = ACRButton(wantsChevron: true, wantsIcon: true, style: buttonStyle, buttonConfig: config.buttonConfig)
            rootView.registerImageHandlingView(button, for: iconUrl)
        } else {
            button = ACRButton(wantsChevron: true, wantsIcon: false, style: buttonStyle, buttonConfig: config.buttonConfig)
        }
        button.title = showCardAction.getTitle() ?? ""

        guard let showCard = showCardAction.getCard() else {
            logError("ShowCard object is nil")
            return button
        }
        
        let target = ActionShowCardTarget(element: showCard, delegate: targetHandlerDelegate)
        target.configureAction(for: button)
        rootView.addTarget(target)
        
        return button
    }
}
