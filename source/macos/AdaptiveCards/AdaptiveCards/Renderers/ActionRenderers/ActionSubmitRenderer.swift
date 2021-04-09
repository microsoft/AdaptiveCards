import AdaptiveCards_bridge
import AppKit

class ActionSubmitRenderer: BaseActionElementRendererProtocol {
    static let shared = ActionSubmitRenderer()
    
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let submitAction = action as? ACSSubmitAction else {
            logError("Element is not of type ACSSubmitAction")
            return NSView()
        }
        
        let button: ACRButton
        
        if let iconUrl = submitAction.getIconUrl(), !iconUrl.isEmpty {
            button = ACRButton(wantsIcon: true)
            rootView.registerImageHandlingView(button, for: iconUrl)
        } else {
            button = ACRButton(wantsIcon: false)
        }
        button.title = submitAction.getTitle() ?? ""
        
        let target = ActionSubmitTarget(element: submitAction, delegate: rootView)
        target.configureAction(for: button)
        rootView.addTarget(target)
        return button
    }
}
