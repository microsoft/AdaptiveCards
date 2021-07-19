import AdaptiveCards_bridge
import AppKit

class ActionSubmitRenderer: BaseActionElementRendererProtocol {
    static let shared = ActionSubmitRenderer()
    
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, targetHandlerDelegate: TargetHandlerDelegate, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let submitAction = action as? ACSSubmitAction else {
            logError("Element is not of type ACSSubmitAction")
            return NSView()
        }
        
        let button = ACRButton(actionElement: submitAction, iconPlacement: hostConfig.getActions()?.iconPlacement, buttonConfig: config.buttonConfig)
        if let iconUrl = submitAction.getIconUrl(), !iconUrl.isEmpty {
            rootView.registerImageHandlingView(button, for: iconUrl)
        }
        
        let target = ActionSubmitTarget(element: submitAction, delegate: targetHandlerDelegate)
        target.configureAction(for: button)
        rootView.addTarget(target)
        return button
    }
}
