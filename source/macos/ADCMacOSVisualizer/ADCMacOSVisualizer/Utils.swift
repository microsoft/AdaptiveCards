import AdaptiveCards
import Cocoa

extension NSColor {
    static func color(from hexString: String) -> NSColor? {
        var hexString = hexString.trimmingCharacters(in: .whitespacesAndNewlines).uppercased()

        if hexString.hasPrefix("#") {
            hexString.remove(at: hexString.startIndex)
        }
        
        guard hexString.count == 6 || hexString.count == 8 else {
            print("Not valid HexCode: \(hexString)")
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
            
        case 8: return NSColor(red: CGFloat((rgbValue & 0xFF000000) >> 24) / 255.0,
                               green: CGFloat((rgbValue & 0x00FF0000) >> 16) / 255.0,
                               blue: CGFloat((rgbValue & 0x0000FF00) >> 8) / 255.0,
                               alpha: CGFloat(rgbValue & 0x000000FF) / 255.0)
        default:
            print("Not valid HexCode: \(hexString)")
            return nil
        }
    }
}

struct Constants {
    // HexCodeFormat: #AARRGGBB
    static let lightThemeDefault = "#000000F2"
    static let lightThemeDefaultBorder = "#000000F2"
    static let lightThemeDefaultHover = "#000000CC"
    static let lightThemeDefaultPressed = "#000000B2"
    static let lightThemeDefaultPressedBorderColor = "#000000B2"
    static let lightThemeDefaultTextColor = "#FFFFFFF2"
    static let lightThemeDefaultSelectedTextColor = "#FFFFFFF2"
    
    static let lightThemePositive = "#FFFFFFFF"
    static let lightThemePositiveBorder = "#185E46FF"
    static let lightThemePositiveHover = "185E46FF"
    static let lightThemePositivePressed = "#134231FF"
    static let lightThemePositivePressedBorderColor = "#134231FF"
    static let lightThemePositiveTextColor = "#185E46FF"
    static let lightThemePositiveSelectedTextColor = "#FFFFFFF2"
    
    static let lightThemeDestructive = "#FFFFFFFF"
    static let lightThemeDestructiveBorder = "#AB0A15FF"
    static let lightThemeDestructiveHover = "AB0A15FF"
    static let lightThemeDestructivePressed = "F780D13FF"
    static let lightThemeDestructivePressedBorderColor = "#780D13FF"
    static let lightThemeDestructiveTextColor = "#AB0A15FF"
    static let lightThemeDestructiveSelectedTextColor = "#FFFFFFF2"
    
    static let darkThemeDefault = "#FFFFFFF2"
    static let darkThemeDefaultBorder = "#FFFFFFF2"
    static let darkThemeDefaultHover = "#FFFFFFCC"
    static let darkThemeDefaultPressed = "#FFFFFFB2"
    static let darkThemeDefaultPressedBorderColor = "#FFFFFFB2"
    static let darkThemeDefaultTextColor = "#000000F2"
    static let darkThemeDefaultSelectedTextColor = "#000000F2"
    
    static let darkThemePositive = "#1A1A1AFF"
    static let darkThemePositiveBorder = "#3CC29AFF"
    static let darkThemePositiveHover = "185E46FF"
    static let darkThemePositivePressed = "#134231FF"
    static let darkThemePositivePressedBorderColor = "#134231FF"
    static let darkThemePositiveTextColor = "#3CC29AFF"
    static let darkThemePositiveSelectedTextColor = "#FFFFFFF2"
    
    static let darkThemeDestructive = "#1A1A1AFF"
    static let darkThemeDestructiveBorder = "#FC8B98FF"
    static let darkThemeDestructiveHover = "AB0A15FF"
    static let darkThemeDestructivePressed = "#780D13FF"
    static let darkThemeDestructivePressedBorderColor = "#780D13FF"
    static let darkThemeDestructiveTextColor = "#FC8B98FF"
    static let darkThemeDestructiveSelectedTextColor = "#FFFFFFF2"
}
