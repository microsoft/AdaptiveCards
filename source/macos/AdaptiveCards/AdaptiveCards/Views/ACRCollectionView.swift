import AdaptiveCards_bridge
import AppKit

class ACRCollectionView: NSCollectionView {
    let imageSet: ACSImageSet
    let imageSize: ACSImageSize
    let hostConfig: ACSHostConfig
    var itemSize: CGSize
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    init(frame frameRect: NSRect, imageSet: ACSImageSet, hostConfig: ACSHostConfig) {
        self.imageSet = imageSet
        self.hostConfig = hostConfig
        // Initialise to nonzero Value
        self.itemSize = .init(width: 50, height: 50)
        switch imageSet.getImageSize() {
        case .stretch, .none:
            self.imageSize = .medium
        default:
            self.imageSize = imageSet.getImageSize()
        }
        super.init(frame: frameRect)
        
        let spacing: CGFloat = 0
        let layout = NSCollectionViewFlowLayout()
        layout.sectionInset = .init(top: spacing, left: spacing, bottom: spacing, right: spacing)
        layout.minimumLineSpacing = spacing
        layout.minimumInteritemSpacing = spacing
        if self.imageSize != .auto {
            itemSize = ImageUtils.getImageSizeAsCGSize(imageSize: self.imageSize, width: 0, height: 0, with: hostConfig, explicitDimensions: false)
        }
        collectionViewLayout = layout
        
        self.backgroundColors = [.clear]
        
        register(ACRCollectionViewItem.self, forItemWithIdentifier: ACRCollectionViewItem.identifier)
    }
    
    // Calculate ContentSize for CollectionView
    func newIntrinsicContentSize() -> CGSize {
        guard let layout = collectionViewLayout as? NSCollectionViewFlowLayout else { return CGSize(width: 0, height: 0) }
        let cellCounts = imageSet.getImages().count
        let spacing = layout.minimumInteritemSpacing
        let lineSpacing = layout.minimumLineSpacing
        let frameWidth = frame.size.width

        if frameWidth > 0, imageSize == .auto {
            let mediumImageSize = ImageUtils.getImageSizeAsCGSize(imageSize: .medium, width: 0, height: 0, with: hostConfig, explicitDimensions: false)
            let itemWidth = min(mediumImageSize.width, frameWidth)
            itemSize = NSSize(width: itemWidth, height: itemWidth)
        }
        
        let itemSizeWithSpacing = itemSize.width + spacing
        
        var numberOfItemsPerRow = Int(frameWidth / itemSizeWithSpacing)
        if CGFloat(numberOfItemsPerRow) * itemSizeWithSpacing + itemSize.width <= frameWidth {
            numberOfItemsPerRow += 1
        }
        
        guard numberOfItemsPerRow > 0 else { return CGSize(width: 0, height: 0) }
        
        let numberOfRows = Int(ceil(Float(cellCounts) / Float(numberOfItemsPerRow)))
    
        return CGSize(width: frameWidth, height: (CGFloat(numberOfRows) * (itemSize.height) + ((CGFloat(numberOfRows) - 1) * lineSpacing)))
    }
    
    override var intrinsicContentSize: NSSize {
        return newIntrinsicContentSize()
    }
    
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        guard let view = superview else { return }
        widthAnchor.constraint(equalTo: view.widthAnchor).isActive = true
    }
}

// MARK: DataSource for CollectionView
class ACRCollectionViewDatasource: NSObject, NSCollectionViewDataSource {
    let imageViews: [ImageSetImageView]
    let images: [ACSImage]
    let hostConfig: ACSHostConfig
    let imageSize: ACSImageSize
    
    init(acsImages: [ACSImage], rootView: ACRView, size: ACSImageSize, hostConfig: ACSHostConfig) {
        self.images = acsImages
        self.hostConfig = hostConfig
        self.imageSize = size
        var imageViews: [ImageSetImageView] = []
        for image in images {
            let imageView = ImageSetImageView()
            imageView.hostConfig = hostConfig
            imageView.imageSize = size
            let url = image.getUrl() ?? ""
            rootView.registerImageHandlingView(imageView, for: url)
            imageViews.append(imageView)
        }
        self.imageViews = imageViews
    }
    
    func collectionView(_ collectionView: NSCollectionView, itemForRepresentedObjectAt indexPath: IndexPath) -> NSCollectionViewItem {
        guard let item = collectionView.makeItem(withIdentifier: ACRCollectionViewItem.identifier, for: indexPath) as? ACRCollectionViewItem else { return NSCollectionViewItem() }
        
        item.setupBounds(with: imageViews[indexPath.item])
        return item
    }
    
    func collectionView(_ collectionView: NSCollectionView, numberOfItemsInSection section: Int) -> Int {
        return images.count
    }
    
    func numberOfSections(in collectionView: NSCollectionView) -> Int {
        return 1
    }
    
    func collectionView(_ collectionView: NSCollectionView, layout collectionViewLayout: NSCollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> NSSize {
        let resolvedSize: ACSImageSize
        let frameWidth = collectionView.bounds.width
        var itemSize: NSSize
        switch imageSize {
        case .stretch, .none:
            resolvedSize = .medium
        default:
            resolvedSize = imageSize
        }
        itemSize = ImageUtils.getImageSizeAsCGSize(imageSize: resolvedSize, width: 0, height: 0, with: hostConfig, explicitDimensions: false)
        if imageSize == .auto {
            let mediumImageSize = ImageUtils.getImageSizeAsCGSize(imageSize: .medium, width: 0, height: 0, with: hostConfig, explicitDimensions: false)
            let itemWidth = min(mediumImageSize.width, frameWidth)
            itemSize = NSSize(width: itemWidth, height: itemWidth)
        }
        return itemSize
    }
}

class ImageSetImageView: NSImageView, ImageHoldingView {
    var imageSize: ACSImageSize = .medium
    var hostConfig: ACSHostConfig?
    
    func setImage(_ image: NSImage) {
        guard let config = hostConfig else {
            self.image = image
            return
        }
        
        // If Image is smaller than cell, make image fit cell and maintain aspectRatio
        let imageRatio = ImageUtils.getAspectRatio(from: image.size)
        var maxImageSize = ImageUtils.getImageSizeAsCGSize(imageSize: imageSize, width: 0, height: 0, with: config, explicitDimensions: false)
        if imageRatio.height < 1 {
            maxImageSize.height *= imageRatio.height
        }
        image.size = maxImageSize
        self.image = image
    }
}

extension ACRCollectionViewDatasource: NSCollectionViewDelegate { }

extension ACRCollectionViewDatasource: NSCollectionViewDelegateFlowLayout { }
