import AdaptiveCards_bridge
import AppKit

class ActionShowCardRenderer: BaseActionElementRendererProtocol {
    static let shared = ActionShowCardRenderer()
    
    func render(action: ACSBaseActionElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let showCardAction = action as? ACSShowCardAction else {
            logError("Element is not of type ACSShowCardAction")
            return NSView()
        }
        
        let button: ACRButton
        if let iconUrl = showCardAction.getIconUrl(), !iconUrl.isEmpty {
            button = ACRButton(wantsChevron: true, wantsIcon: true)
            rootView.registerImageHandlingView(button, for: iconUrl)
        } else {
            button = ACRButton(wantsChevron: true, wantsIcon: false)
        }
        button.title = showCardAction.getTitle() ?? ""

        guard let showCard = showCardAction.getCard() else {
            logError("ShowCard object is nil")
            return button
        }
        
        let target = ActionShowCardTarget(element: showCard, delegate: rootView)
        target.configureAction(for: button)
        rootView.addTarget(target)
        
        return button
    }
}
