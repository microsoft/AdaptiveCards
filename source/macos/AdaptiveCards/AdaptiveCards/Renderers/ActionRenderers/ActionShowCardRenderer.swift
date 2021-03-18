import AdaptiveCards_bridge
import AppKit

class ActionShowCardRenderer: BaseActionElementRendererProtocol {
    static let shared = ActionShowCardRenderer()
    
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let showCardAction = action as? ACSShowCardAction else {
            logError("Element is not of type ACSShowCardAction")
            return NSView()
        }
        
        let button = ACRButton()
        button.title = showCardAction.getTitle() ?? ""

        let target = ActionShowCardTarget(element: showCardAction.getCard() ?? ACSAdaptiveCard(), delegate: rootView)
        target.configureAction(for: button)
        rootView.addTarget(target)
        
        return button
    }
}
