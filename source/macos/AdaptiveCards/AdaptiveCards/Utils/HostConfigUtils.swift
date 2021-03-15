import AdaptiveCards_bridge
import AppKit

extension ACSHostConfig {
    static func getTextBlockAlignment(from horizontalAlignment: ACSHorizontalAlignment) -> NSTextAlignment {
        switch horizontalAlignment {
        case .center: return .center
        case .left: return .left
        case .right: return .right
        @unknown default: return .left
        }
    }
    
    func getBackgroundColor(for containerStyle: ACSContainerStyle) -> NSColor? {
        guard let hexColorCode = getBackgroundColor(containerStyle) else {
            logError("HexColorCode is nil")
            return nil
        }
        return ColorUtils.color(from: hexColorCode)
    }
    
    func getBorderColor(for containerStyle: ACSContainerStyle) -> NSColor? {
        guard let hexColorCode = getBorderColor(containerStyle) else {
            logError("HexColorCode is nil")
            return nil
        }
        return ColorUtils.color(from: hexColorCode)
    }
    
    func getBorderThickness(for containerStyle: ACSContainerStyle) -> CGFloat? {
        guard let thickness = getBorderThickness(containerStyle) else {
            logError("HexColorCode is nil")
            return nil
        }
        return CGFloat(exactly: thickness)
    }
}

class FontUtils {
    static func getFont(for hostConfig: ACSHostConfig, with textProperties: ACSRichTextElementProperties) -> NSFont {
        var fontWeight = hostConfig.getFontWeight(textProperties.getFontType(), weight: textProperties.getTextWeight())?.intValue ?? 400

        if fontWeight <= 0 || fontWeight > 900 {
            fontWeight = 400
        }
        
        fontWeight -= 100
        fontWeight /= 100
        
        let resolvedFontFamily: String?
        if let family = hostConfig.getFontFamily(textProperties.getFontType()) {
            resolvedFontFamily = family
        } else {
            resolvedFontFamily = textProperties.getFontType() == .monospace ? "Courier New" : nil
        }
        
        guard let fontFamily = resolvedFontFamily, !fontFamily.isEmpty else {
            // Custom Font family not needed
            return getSystemFont(for: hostConfig, with: textProperties, fontWeight: fontWeight)
        }
        
        let fontWeights = ["UltraLight", "Thin", "Light", "Regular", "Medium", "Semibold", "Bold", "Heavy", "Black"]
        var descriptor = NSFontDescriptor(fontAttributes: [NSFontDescriptor.AttributeName.family: fontFamily, NSFontDescriptor.AttributeName.face: fontWeights[fontWeight]])
        descriptor = getItalicFontDescriptor(descriptor, italic: textProperties.getItalic())
        let size = hostConfig.getFontSize(textProperties.getFontType(), size: textProperties.getTextSize())?.intValue ?? 14
        guard let font = NSFont(descriptor: descriptor, size: CGFloat(size)) else {
            logError("Font with fontFamily '\(fontFamily)' not found. Returning system font.")
            return getSystemFont(for: hostConfig, with: textProperties, fontWeight: fontWeight)
        }
        return font
    }
    
    private static func getItalicFontDescriptor(_ descriptor: NSFontDescriptor, italic: Bool) -> NSFontDescriptor {
        return italic ? descriptor.withSymbolicTraits(.italic) : descriptor
    }
    
    private static func getSystemFont(for hostConfig: ACSHostConfig, with textProperties: ACSRichTextElementProperties, fontWeight: Int) -> NSFont {
        let fontWeights: [NSFont.Weight] = [.ultraLight, .thin, .light, .regular, .medium, .semibold, .bold, .heavy, .black]
        let size = hostConfig.getFontSize(textProperties.getFontType(), size: textProperties.getTextSize())?.intValue ?? 14
        let systemFont = NSFont.systemFont(ofSize: CGFloat(size), weight: fontWeights[fontWeight])
        if textProperties.getItalic() {
            guard let font = NSFont(descriptor: getItalicFontDescriptor(systemFont.fontDescriptor, italic: true), size: CGFloat(size)) else {
                logError("Generating System Italic font failed")
                return systemFont
            }
            return font
        }
        return systemFont
    }
}

class ColorUtils {
    static func color(from hexString: String) -> NSColor? {
        var hexString = hexString.trimmingCharacters(in: .whitespacesAndNewlines).uppercased()

        if hexString.hasPrefix("#") {
            hexString.remove(at: hexString.startIndex)
        }
        
        guard hexString.count == 6 || hexString.count == 8 else {
            logError("Not valid HexCode: \(hexString)")
            return nil
        }

        var rgbValue: UInt64 = 0
        Scanner(string: hexString).scanHexInt64(&rgbValue)
        
        // Need to revisit and validate
        switch hexString.count {
        case 6: return NSColor(red: CGFloat((rgbValue & 0xFF0000) >> 16) / 255.0,
                               green: CGFloat((rgbValue & 0x00FF00) >> 8) / 255.0,
                               blue: CGFloat(rgbValue & 0x0000FF) / 255.0,
                               alpha: CGFloat(1.0))
            
        case 8: return NSColor(red: CGFloat((rgbValue & 0x00FF0000) >> 16) / 255.0,
                               green: CGFloat((rgbValue & 0x0000FF00) >> 8) / 255.0,
                               blue: CGFloat((rgbValue & 0x000000FF)) / 255.0,
                               alpha: CGFloat(rgbValue & 0xFF000000) / 255.0)
        
        default:
            logError("Not valid HexCode: \(hexString)")
            return nil
        }
    }
}

class TextUtils {
    static func getMarkdownString(parserResult: ACSMarkdownParserResult) -> NSMutableAttributedString {
        let content: NSMutableAttributedString
        if parserResult.isHTML, let htmlData = parserResult.htmlData {
            do {
                content = try NSMutableAttributedString(data: htmlData, options: [.documentType: NSAttributedString.DocumentType.html], documentAttributes: nil)
                // Delete trailing newline character
                content.deleteCharacters(in: NSRange(location: content.length - 1, length: 1))
//                    textView.isSelectable = true
            } catch {
                content = NSMutableAttributedString(string: parserResult.parsedString)
            }
        } else {
            content = NSMutableAttributedString(string: parserResult.parsedString)
            // Delete <p> and </p>
            content.deleteCharacters(in: NSRange(location: 0, length: 3))
            content.deleteCharacters(in: NSRange(location: content.length - 4, length: 4))
        }
        return content
    }
}
