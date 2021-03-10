import AdaptiveCards_bridge
import AppKit

class ActionOpenURLRenderer: BaseActionElementRendererProtocol {
    static let shared = ActionOpenURLRenderer()
    
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let openURLAction = action as? ACSOpenUrlAction else {
            logError("Element is not of type ACSOpenUrlAction")
            return NSView()
        }
        
        let button = ACRButton()
        button.title = openURLAction.getTitle() ?? ""
        
        let target = ActionOpenURLTarget(element: openURLAction, delegate: rootView)
        target.configureAction(for: button)
        rootView.addTarget(target)
        
        return button
    }
}
