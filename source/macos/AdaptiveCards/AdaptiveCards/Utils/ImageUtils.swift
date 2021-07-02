import AdaptiveCards_bridge
import AppKit
import CoreGraphics
import Foundation

class ImageUtils {
    static func getImageSizeAsCGSize(imageSize: ACSImageSize, with config: ACSHostConfig) -> CGSize {
        return getImageSizeAsCGSize(imageSize: imageSize, width: 0, height: 0, with: config, explicitDimensions: false)
    }
    
    static func getImageSizeAsCGSize(imageSize: ACSImageSize, width: CGFloat, height: CGFloat, with config: ACSHostConfig, explicitDimensions: Bool) -> CGSize {
        if explicitDimensions {
            var isAspectRatioNeeded = false
            var imageSizeAsCGSize = CGSize.zero
            if !(width > 0 && height > 0) {
                isAspectRatioNeeded = true
            }
            if width > 0 {
                imageSizeAsCGSize.width = width
                if isAspectRatioNeeded {
                    imageSizeAsCGSize.height = imageSizeAsCGSize.width
                }
            }
            if height > 0 {
                imageSizeAsCGSize.height = height
                if isAspectRatioNeeded {
                    imageSizeAsCGSize.width = imageSizeAsCGSize.height
                }
            }
            return imageSizeAsCGSize
        }
        
        var sz: Float = 0.0
        switch imageSize {
        case ACSImageSize.large:
            if let size = config.getImageSizes()?.largeSize {
                sz = size.floatValue
            }
        case ACSImageSize.medium:
            if let size = config.getImageSizes()?.mediumSize {
                sz = size.floatValue
            }
        case ACSImageSize.small:
            if let size = config.getImageSizes()?.smallSize {
                sz = size.floatValue
            }
        case ACSImageSize.auto, ACSImageSize.stretch, ACSImageSize.none:
            return CGSize.zero
        default:
            return CGSize.zero
        }
        return CGSize(width: CGFloat(sz), height: CGFloat(sz))
    }
    
    static func getAspectRatio(from size: CGSize) -> CGSize {
        var heightToWidthRatio: CGFloat = 0.0
        var widthToHeightRatio: CGFloat = 0.0
        if size.width > 0 {
            heightToWidthRatio = size.height / size.width
        }

        if size.height > 0 {
            widthToHeightRatio = size.width / size.height
        }
        return CGSize(width: widthToHeightRatio, height: heightToWidthRatio)
    }
}
