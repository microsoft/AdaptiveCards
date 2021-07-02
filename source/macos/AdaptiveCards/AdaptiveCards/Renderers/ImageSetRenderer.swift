import AdaptiveCards_bridge
import AppKit

class ImageSetRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = ImageSetRenderer()
 
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let imageSet = element as? ACSImageSet else {
            logError("Element is not of type ACSImageSet")
            return NSView()
        }
        let colView = ACRCollectionView(rootView: rootView, imageSet: imageSet, hostConfig: hostConfig)
        colView.translatesAutoresizingMaskIntoConstraints = false
        return colView
    }
}
