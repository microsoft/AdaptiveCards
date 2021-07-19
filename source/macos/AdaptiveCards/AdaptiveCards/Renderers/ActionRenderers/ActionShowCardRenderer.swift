import AdaptiveCards_bridge
import AppKit

class ActionShowCardRenderer: BaseActionElementRendererProtocol {
    static let shared = ActionShowCardRenderer()
    
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, targetHandlerDelegate: TargetHandlerDelegate, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let showCardAction = action as? ACSShowCardAction else {
            logError("Element is not of type ACSShowCardAction")
            return NSView()
        }
        
        let button = ACRButton(actionElement: showCardAction, iconPlacement: hostConfig.getActions()?.iconPlacement, buttonConfig: config.buttonConfig)
        if let iconUrl = showCardAction.getIconUrl(), !iconUrl.isEmpty {
            rootView.registerImageHandlingView(button, for: iconUrl)
        }

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
