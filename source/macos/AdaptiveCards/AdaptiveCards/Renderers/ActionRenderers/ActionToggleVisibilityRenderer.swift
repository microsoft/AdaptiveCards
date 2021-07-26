import AdaptiveCards_bridge
import AppKit

class ActionToggleVisibilityRenderer: BaseActionElementRendererProtocol {
    static let shared = ActionToggleVisibilityRenderer()
    
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, targetHandlerDelegate: TargetHandlerDelegate, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let toggleVisibilityAction = action as? ACSToggleVisibilityAction else {
            logError("Element is not of type ACSToggleVisibilityAction")
            return NSView()
        }
        
        let button = ACRButton(actionElement: toggleVisibilityAction, iconPlacement: hostConfig.getActions()?.iconPlacement, buttonConfig: config.buttonConfig)
        if let iconUrl = toggleVisibilityAction.getIconUrl(), !iconUrl.isEmpty {
            rootView.registerImageHandlingView(button, for: iconUrl)
        }
        
        let target = ActionToggleVisibilityTarget(toggleTargets: toggleVisibilityAction.getTargetElements(), delegate: targetHandlerDelegate)
        target.configureAction(for: button)
        rootView.addTarget(target)
        
        return button
    }
}
