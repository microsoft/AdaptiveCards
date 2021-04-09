import AdaptiveCards_bridge
import AppKit

class ActionOpenURLRenderer: BaseActionElementRendererProtocol {
    static let shared = ActionOpenURLRenderer()
    
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let openURLAction = action as? ACSOpenUrlAction else {
            logError("Element is not of type ACSOpenUrlAction")
            return NSView()
        }
        
        let button: ACRButton
        if let iconUrl = openURLAction.getIconUrl(), !iconUrl.isEmpty {
            button = ACRButton(wantsIcon: true)
            rootView.registerImageHandlingView(button, for: iconUrl)
        } else {
            button = ACRButton(wantsIcon: false)
        }
        button.title = openURLAction.getTitle() ?? ""
        
        let target = ActionOpenURLTarget(element: openURLAction, delegate: rootView)
        target.configureAction(for: button)
        rootView.addTarget(target)
        
        return button
    }
}
