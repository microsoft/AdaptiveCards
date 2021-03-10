import AdaptiveCards_bridge
import AppKit

class ACRCollectionView: NSCollectionView {
    var imageSet: ACSImageSet?
    var imageSize: ACSImageSize?
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
        layout.itemSize = ImageUtils.getImageSizeAsCGSize(imageSize: self.imageSize ?? .medium, width: 0, height: 0, with: hostConfig, explicitDimensions: false)
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
    func collectionView(_ collectionView: NSCollectionView, itemForRepresentedObjectAt indexPath: IndexPath) -> NSCollectionViewItem {
        guard let collectionView = collectionView as? ACRCollectionView, let hostConfig = collectionView.hostConfig, let item = collectionView.makeItem(withIdentifier: ACRCollectionViewItem.identifier, for: indexPath) as? ACRCollectionViewItem else { return NSCollectionViewItem() }
        guard let imageSet = collectionView.imageSet, let urlString = imageSet.getImages()[indexPath.item].getUrl() else { return item }
        item.setupItem(with: urlString, hostConfig: hostConfig, imageSize: collectionView.imageSize ?? .medium)
        return item
    }
    
    func collectionView(_ collectionView: NSCollectionView, numberOfItemsInSection section: Int) -> Int {
        guard let collectionView = collectionView as? ACRCollectionView, let newImageSet = collectionView.imageSet else { return 0 }
        return newImageSet.getImages().count
    }
    
    func numberOfSections(in collectionView: NSCollectionView) -> Int {
        return 1
    }
}

extension ACRCollectionViewDatasource: NSCollectionViewDelegate { }

extension ACRCollectionViewDatasource: NSCollectionViewDelegateFlowLayout { }
