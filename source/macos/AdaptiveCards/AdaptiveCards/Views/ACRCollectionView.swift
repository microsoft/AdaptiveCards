import AdaptiveCards_bridge
import AppKit

class ACRCollectionView: NSScrollView {
    private struct Constants {
        static let padding: CGFloat = 0
    }
    
    private let imageSet: ACSImageSet
    private let imageSize: ACSImageSize
    private let hostConfig: ACSHostConfig
    private let imageViews: [ImageSetImageView]
    
    private var itemSize: CGSize {
        switch imageSize {
        case .stretch, .none:
            return ImageUtils.getImageSizeAsCGSize(imageSize: .medium, with: hostConfig)
        case .auto:
            let mediumSize = ImageUtils.getImageSizeAsCGSize(imageSize: .medium, with: hostConfig)
            let itemWidth = min(mediumSize.width, bounds.width - (2 * Constants.padding))
            return CGSize(width: itemWidth, height: itemWidth)
        default:
            return ImageUtils.getImageSizeAsCGSize(imageSize: imageSize, with: hostConfig)
        }
    }
    
    private lazy var collectionView: NSCollectionView = {
        let view = NSCollectionView()
        view.autoresizingMask = [.minXMargin, .minYMargin, .maxXMargin, .maxYMargin, .width, .height]
        view.itemPrototype = nil
        view.backgroundColors = [.clear]
        return view
    }()
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    init(rootView: ACRView, imageSet: ACSImageSet, hostConfig: ACSHostConfig) {
        self.imageSet = imageSet
        self.hostConfig = hostConfig
        self.imageSize = imageSet.getImageSize()
        self.imageViews = imageSet.getImages().map {
            let imageView = ImageSetImageView(imageSize: imageSet.getImageSize(), hostConfig: hostConfig)
            rootView.registerImageHandlingView(imageView, for: $0.getUrl() ?? "")
            return imageView
        }
        super.init(frame: .zero)
        
        let layout = NSCollectionViewFlowLayout()
        layout.sectionInset = NSEdgeInsets(top: Constants.padding, left: Constants.padding, bottom: Constants.padding, right: Constants.padding)
        layout.minimumLineSpacing = Constants.padding
        layout.minimumInteritemSpacing = Constants.padding

        collectionView.collectionViewLayout = layout
        collectionView.register(ACRCollectionViewItem.self, forItemWithIdentifier: ACRCollectionViewItem.identifier)
        collectionView.dataSource = self
        collectionView.delegate = self
        
        autoresizingMask = [.minXMargin, .minYMargin, .maxXMargin, .maxYMargin, .width, .height]
        wantsLayer = true
        documentView = collectionView
        
        // hide scroller
        hasVerticalScroller = false
        hasHorizontalScroller = false
        scrollerInsets = NSEdgeInsets(top: 0, left: 0, bottom: 0, right: -20)
        scrollerStyle = .overlay
        autohidesScrollers = true
    }
    
    // Calculate ContentSize for CollectionView
    private func calculateContentSize() -> CGSize? {
        guard bounds.width > 0 else {
            return nil
        }
        
        let cellCounts = imageSet.getImages().count
        let insets = 2 * Constants.padding
        let boundsWidth = bounds.width - insets
        let itemSizeWithSpacing = itemSize.width + Constants.padding
        
        var numberOfItemsPerRow = floor(boundsWidth / itemSizeWithSpacing)
        // if addtional image can be fit by removing spacing, do so
        if (numberOfItemsPerRow * itemSizeWithSpacing) + itemSize.width <= boundsWidth {
            numberOfItemsPerRow += 1
        }
        
        guard numberOfItemsPerRow > 0 else {
            return nil
        }
        
        let numberOfRows = ceil(CGFloat(cellCounts) / numberOfItemsPerRow)
        let calcHeight = (numberOfRows * itemSize.height) + insets + (numberOfRows - 1) * Constants.padding
        return CGSize(width: boundsWidth,
                      height: calcHeight - 1) // subracting 1pt because sometimes cells don't render if exact ht is passed
    }
    
    var pBoundsWidth: CGFloat?
    var pContentSize: CGSize?
    override func layout() {
        super.layout()
        guard window != nil, pBoundsWidth != bounds.width else { return }
        pBoundsWidth = bounds.width
        pContentSize = nil
    }
    
    override var intrinsicContentSize: NSSize {
        guard let contentSize = pContentSize else {
            guard let calcSize = calculateContentSize() else {
                return super.intrinsicContentSize
            }
            pContentSize = calcSize
            return calcSize
        }
        return contentSize
    }
    
    override func scrollWheel(with event: NSEvent) {
        // to disable scroll always
        nextResponder?.scrollWheel(with: event)
    }
    
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        guard let view = superview else { return }
        widthAnchor.constraint(equalTo: view.widthAnchor).isActive = true
    }
}

extension ACRCollectionView: NSCollectionViewDataSource {
    func collectionView(_ collectionView: NSCollectionView, numberOfItemsInSection section: Int) -> Int {
        return imageSet.getImages().count
    }
    
    func collectionView(_ collectionView: NSCollectionView, itemForRepresentedObjectAt indexPath: IndexPath) -> NSCollectionViewItem {
        guard let item = collectionView.makeItem(withIdentifier: ACRCollectionViewItem.identifier, for: indexPath) as? ACRCollectionViewItem else { return NSCollectionViewItem() }
        item.setupBounds(with: imageViews[indexPath.item])
        return item
    }
}

extension ACRCollectionView: NSCollectionViewDelegateFlowLayout {
    func collectionView(_ collectionView: NSCollectionView, layout collectionViewLayout: NSCollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> NSSize {
        return itemSize
    }
}

class ImageSetImageView: NSImageView, ImageHoldingView {
    let imageSize: ACSImageSize
    let hostConfig: ACSHostConfig
    
    init(imageSize: ACSImageSize, hostConfig: ACSHostConfig) {
        self.imageSize = imageSize.collectionItemResolvedSize
        self.hostConfig = hostConfig
        super.init(frame: .zero)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func setImage(_ image: NSImage) {
        // If Image is smaller than cell, make image fit cell and maintain aspectRatio
        let imageRatio = ImageUtils.getAspectRatio(from: image.size)
        var maxImageSize = ImageUtils.getImageSizeAsCGSize(imageSize: imageSize, with: hostConfig)
        if imageRatio.height < 1 {
            maxImageSize.height *= imageRatio.height
        }
        image.size = maxImageSize
        self.image = image
    }
}

extension ACSImageSize {
    var collectionItemResolvedSize: ACSImageSize {
        switch self {
        case .auto, .stretch, .none: return .medium
        default: return self
        }
    }
}
