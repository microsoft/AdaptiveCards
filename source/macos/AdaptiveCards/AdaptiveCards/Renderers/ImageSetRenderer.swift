import AdaptiveCards_bridge
import AppKit

class ImageSetRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = ImageSetRenderer()
 
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let imageSet = element as? ACSImageSet else {
            logError("Element is not of type ACSImageSet")
            return NSView()
        }
        
        var imageSize: ACSImageSize = imageSet.getImageSize()
        if imageSize == .stretch || imageSize == .none {
            imageSize = .medium
        }
        
        let datasource = ACRCollectionViewDatasource(acsImages: imageSet.getImages(), rootView: rootView, size: imageSize, hostConfig: hostConfig)
        rootView.addImageSetDatasource(datasource)
        
        let colView = ACRCollectionView(frame: .zero, imageSet: imageSet, hostConfig: hostConfig)
        colView.translatesAutoresizingMaskIntoConstraints = false
        colView.dataSource = datasource
        colView.delegate = datasource
        return colView
    }
}
