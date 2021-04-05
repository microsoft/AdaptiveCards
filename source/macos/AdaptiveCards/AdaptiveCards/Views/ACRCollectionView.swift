import AdaptiveCards_bridge
import AppKit

class ACRCollectionView: NSCollectionView {
    var imageSet: ACSImageSet?
    var imageSize: ACSImageSize = .medium
    var hostConfig: ACSHostConfig?
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    init(frame frameRect: NSRect, imageSet: ACSImageSet, hostConfig: ACSHostConfig) {
        super.init(frame: frameRect)
        
        let spacing: CGFloat = 2
        self.imageSet = imageSet
        self.hostConfig = hostConfig
        self.imageSize = imageSet.getImageSize()
        
        if imageSet.getImageSize() == .auto || imageSet.getImageSize() == .stretch || imageSet.getImageSize() == .none {
            self.imageSize = .medium
        }
        
        let layout = NSCollectionViewFlowLayout()
        layout.sectionInset = .init(top: spacing, left: spacing, bottom: spacing, right: spacing)
        // TODO: Change minimumLineSpacing to 0 after adding images
        layout.minimumLineSpacing = spacing
        layout.minimumInteritemSpacing = spacing
        layout.itemSize = ImageUtils.getImageSizeAsCGSize(imageSize: self.imageSize, width: 0, height: 0, with: hostConfig, explicitDimensions: false)
        collectionViewLayout = layout
        
        self.backgroundColors = [.clear]
        
        register(ACRCollectionViewItem.self, forItemWithIdentifier: ACRCollectionViewItem.identifier)
    }
    
    func newIntrinsicContentSize() -> CGSize {
        guard let layout = collectionViewLayout as? NSCollectionViewFlowLayout else { return CGSize(width: 0, height: 0) }
        let cellCounts = imageSet?.getImages().count ?? 0
        let newImageSize = layout.itemSize
        let spacing = layout.minimumInteritemSpacing
        let lineSpacing = layout.minimumLineSpacing
        let frameWidth = frame.size.width
        let imageSizeWithSpacing = newImageSize.width + spacing
        
        var numberOfItemsPerRow = Int(frameWidth / imageSizeWithSpacing)
        if CGFloat(numberOfItemsPerRow) * imageSizeWithSpacing + newImageSize.width <= frameWidth {
            numberOfItemsPerRow += 1
        }
        
        guard numberOfItemsPerRow > 0 else { return CGSize(width: 0, height: 0) }
        
        let numberOfRows = Int(ceil(Float(cellCounts) / Float(numberOfItemsPerRow)))
    
        return CGSize(width: frameWidth, height: (CGFloat(numberOfRows) * (newImageSize.height) + ((CGFloat(numberOfRows) - 1) * lineSpacing)))
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
    
    init(acsImages: [ACSImage], rootView: ACRView, size: ACSImageSize, hostConfig: ACSHostConfig) {
        self.images = acsImages
        self.hostConfig = hostConfig
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
        guard let collectionView = collectionView as? ACRCollectionView,
              let hostConfig = collectionView.hostConfig,
              let item = collectionView.makeItem(withIdentifier: ACRCollectionViewItem.identifier, for: indexPath) as? ACRCollectionViewItem else { return NSCollectionViewItem() }
        
        item.setupBounds(with: imageViews[indexPath.item])
        return item
    }
    
    func collectionView(_ collectionView: NSCollectionView, numberOfItemsInSection section: Int) -> Int {
        return images.count
    }
    
    func numberOfSections(in collectionView: NSCollectionView) -> Int {
        return 1
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
