import Foundation

public class TestUtils {
    // Dictionary to test image rendering in case image size is known before hand
    static let getImageDimens: [String: NSSize] = [
        "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg": NSSize(width: 400, height: 400),
        "https://messagecardplayground.azurewebsites.net/assets/LocationGreen_A.png": NSSize(width: 17.25, height: 26.25),
        "https://messagecardplayground.azurewebsites.net/assets/power_point.png": NSSize(width: 7, height: 12),
        "https://messagecardplayground.azurewebsites.net/assets/Gray_Dot.png": NSSize(width: 18, height: 18),
        "https://messagecardplayground.azurewebsites.net/assets/location_gray.png": NSSize(width: 4.5, height: 12),
        "https://messagecardplayground.azurewebsites.net/assets/LocationBlue_B.png": NSSize(width: 17.25, height: 26.25),
        "https://messagecardplayground.azurewebsites.net/assets/Conflict.png": NSSize(width: 7, height: 12),
        "https://messagecardplayground.azurewebsites.net/assets/CircleGreen_coffee.png": NSSize(width: 18.75, height: 18.75),
        "https://messagecardplayground.azurewebsites.net/assets/car.png": NSSize(width: 7, height: 12),
        "https://messagecardplayground.azurewebsites.net/assets/LocationRed_C.png": NSSize(width: 17.25, height: 26.25),
        "https://messagecardplayground.azurewebsites.net/assets/CircleBlue_flight.png": NSSize(width: 18.75, height: 18.75),
        "https://messagecardplayground.azurewebsites.net/assets/SeaTacMap.png": NSSize(width: 486.75, height: 189.75),
        "https://adaptivecards.io/content/pending.png": NSSize(width: 80.640000000000001, height: 24),
        "https://adaptivecards.io/content/up.png ": NSSize(width: 40, height: 40),
        "https://adaptivecards.io/content/down.png ": NSSize(width: 40, height: 40),
        "https://messagecardplayground.azurewebsites.net/assets/TxP_Flight.png": NSSize(width: 281.25, height: 99),
        "https://messagecardplayground.azurewebsites.net/assets/smallairplane.png": NSSize(width: 18, height: 18),
        "https://messagecardplayground.azurewebsites.net/assets/graydot2x2.png": NSSize(width: 1.5, height: 1.5),
        "https://adaptivecards.io/content/airplane.png": NSSize(width: 42.6, height: 42.6),
        "https://adaptivecards.io/content/cats/1.png": NSSize(width: 400, height: 400),
        "https://adaptivecards.io/content/cats/2.png": NSSize(width: 222.75, height: 222.75),
        "https://adaptivecards.io/content/cats/3.png": NSSize(width: 222.75, height: 222.75),
        "https://upload.wikimedia.org/wikipedia/commons/b/b2/Diver_Silhouette%2C_Great_Barrier_Reef.jpg": NSSize(width: 1920, height: 2560),
        "https://picsum.photos/300?image=882": NSSize(width: 300, height: 300),
        "https://messagecardplayground.azurewebsites.net/assets/Mostly%20Cloudy-Square.png": NSSize(width: 365, height: 324),
        "https://messagecardplayground.azurewebsites.net/assets/Drizzle-Square.png": NSSize(width: 365, height: 324)
    ]
}
