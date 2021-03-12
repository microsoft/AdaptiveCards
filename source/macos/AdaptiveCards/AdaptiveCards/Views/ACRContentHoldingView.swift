import AdaptiveCards_bridge
import AppKit

class ACRContentHoldingView: NSView {
    private weak var _viewgroup: ACRContentStackView?
    private weak var _imageViewHeightConstraint: NSLayoutConstraint?
    private weak var _heightConstraint: NSLayoutConstraint?
    weak var imageView: NSImageView?
    var imageProperties: ACRImageProperties?
    
    var isImageSet: Bool = true
    var isPersonStyle: Bool = false
    var hidePlayicon: Bool = false
    var isMediaType: Bool = false

    override public init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
    }

    public required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    required init(imageProperties: ACRImageProperties, imageView: NSImageView, viewgroup: ACRContentStackView) {
        let frame = CGRect(x: 0, y: 0, width: imageProperties.contentSize.width, height: imageProperties.contentSize.height)
        super.init(frame: frame)
        needsLayout = true
        self.imageProperties = imageProperties
        self.imageView = imageView
        _viewgroup = viewgroup
        self.addSubview(imageView)
    }
    
    override func layout() {
        super.layout()
        
        if isPersonStyle {
            let subview = self.subviews[0]
            let radius = subview.bounds.size.width / 2
            subview.wantsLayer = true
            subview.layer?.cornerRadius = radius
            subview.layer?.masksToBounds = true
        }
        
        var shouldUpdate = false
        if !(imageProperties?.hasExplicitDimensions ?? false) && _heightConstraint == nil {
            setHeightConstraint()
            shouldUpdate = true
        }

        if imageProperties?.acsImageSize == ACSImageSize.stretch {
            if _heightConstraint != nil && _imageViewHeightConstraint != nil {
                shouldUpdate = false
            }

            if _heightConstraint == nil {
                setHeightConstraint()
            }

            if _imageViewHeightConstraint == nil {
                setImageViewHeightConstraint()
            }
        }

        if shouldUpdate {
            _viewgroup?.invalidateIntrinsicContentSize()
        }
    }

    // update the intrinsic content size when the width become available
    private func updateIntrinsicContentSizeOfSelfAndViewGroup() {
        var width = imageProperties?.contentSize.width ?? 0
        if width > 0 {
            if imageProperties?.acsImageSize == ACSImageSize.stretch || (width > self.frame.size.width) {
                width = self.frame.size.width
            }
        }

        var height: CGFloat = 1

        let ratios = ImageUtils.getAspectRatio(from: imageProperties?.contentSize ?? CGSize.zero)
        height = width * ratios.height
        // update it to the new value
        imageProperties?.contentSize = CGSize(width: width, height: height)
    }

    private func setHeightConstraint() {
        updateIntrinsicContentSizeOfSelfAndViewGroup()
        _heightConstraint = setHeightConstraintUtil(heightAnchor: heightAnchor )
    }

    private func setImageViewHeightConstraint() {
        // set new height anchor to the height of new intrinsic contentsize
        _imageViewHeightConstraint = setHeightConstraintUtil(heightAnchor: self.imageView?.heightAnchor ?? NSLayoutDimension())
    }

    private func setHeightConstraintUtil(heightAnchor: NSLayoutDimension) -> NSLayoutConstraint {
        let constraint = heightAnchor.constraint(equalToConstant: imageProperties?.contentSize.height ?? 0)
        constraint.priority = NSLayoutConstraint.Priority(rawValue: 999)
        constraint.isActive = true
        return constraint
    }
 }
