import AdaptiveCards_bridge
import AppKit

class ImageSetRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = ImageSetRenderer()
    // Has to be defined outside the render function
    let collectionViewDataSource = ACRCollectionViewDatasource()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let imageSet = element as? ACSImageSet else {
            logError("Element is not of type ACSImageSet")
            return NSView()
        }
        
        let colView = ACRCollectionView(frame: .zero, imageSet: imageSet, hostConfig: hostConfig)
        colView.translatesAutoresizingMaskIntoConstraints = false
        colView.dataSource = collectionViewDataSource
        colView.delegate = collectionViewDataSource
        return colView
    }
}
