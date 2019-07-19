# Input.Rating Telemetry Design Specification 
 
## Abstract 
This design specification covers telemetry integration into the `Input.Rating` control, which will be included in a future release of Adaptive Cards. Telemetry integration is currently slated only for the JavaScript platform; however, this developer specification will be general enough to cover all platforms supported by Adaptive Cards. See more at the GitHub issue [3058](https://github.com/microsoft/AdaptiveCards/issues/3058) 
 
## 1. Feature Dependencies 
### 1.1 Dependencies on other features 
Because telemetry will be baked into the `Input.Rating` control as a result of the implementation of this design, this feature is inherently dependent on the `Input.Rating` control. Externally, this feature is dependent on the functionality of the 1DS SDK. 
 
### 1.2 Other features' dependencies on this feature 
There are currently no other existing features that directly depend on this feature. However, future telemetry for other elements will be based on the design presented here. 
 
## 2. Platform-Specific Considerations 
UWP, JS, and .NET are all currently supported by 1DS, allowing for relatively seamless integration of telemetry for these platforms. Mobile platforms (ie., Android and iOS) are not fully supported by 1DS, so future communication and cooperation with the 1DS team to achieve support for these platforms is necessary. 
 
## 3. Performance Implications 
“Perf-penalty in terms of runtime perf on foreground threads should not be affected; all our log event API calls are async. Background threads would kick in when there's time to upload. Total CPU time to upload would depend how much data you logged. In UTC mode - the perf penalty vs. trace logging would be near-zero. About the same.” - Max Golovanov (1DS) 
We can look further into how 1DS affects startup time and memory usage with comparison tests. The real-world perf numbers would depend on telemetry volume per minute. Due to call being made in the background, the performance implications shouldn’t be major, but will exist.  
 
 
## 4. Backwards Compatibility Concerns  
If the renderer is not up to date, we will not be able to receive telemetry, which is not a problem because ‘Input.Rating’ would not work correctly without the up-to-date renderer.  
 
## 5. Security Impact 
Security should be considered in the situation of protecting the token and telemetry pipeline from malicious parties. Although Adaptive Cards is open source, we do not plan on exposing the telemetry token to the public. Thus, distribution of Adaptive Cards versions with telemetry should be limited to internal use cases only (within Microsoft Corp. only). 
 
## 6. New APIs 
In progress. Will update based on finalization of logger interface. 
 
## 7. Testing Details 
### 7.1 
 
### 7.2 JSON Samples and Expected Output 
 
1) 
``` 
{ 
  "type": "AdaptiveCard", 
  "body": [ 
    { 
      "type": "Input.Rating", 
      "id": "userRating" 
      } 
    } 
  ], 
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json", 
  "version": "1.0" 
} 
 
``` 
Expected Values: 
 
| Property                     | Expected Value | 
|------------------------------|----------------| 
| CorrelationID                | any            | 
| AppID                        | any            | 
| DeviceID                     | any            | 
| OperationResult              | Success        | 
| NumberOfFeedbackControls     | 1              | 
| NumberOfElements             | 1              | 
| ElementNames                 | [Input.Rating] | 
| TotalDefaultRatingScalesUsed | 1              | 
| TotalDefaultStarImagesUsed   | 1              | 
| isDeveloper                  | any            | 
 
Note: This is not all going to be recorded in one event, but instead each element will be sent and in post processing it will be put together like this.  
 
## 8. Estimated Dev Cost 
With two full-time interns working on this feature, implementation of telemetry in JavaScript should take one month, with estimated delivery being mid-August. Within this time frame, progress in the UWP Adaptive Cards platform may also be a plausible stretch goal. 
 
## 9. JavaScript Architecture Details 
The main components of telemetry in the JavaScript platform will include the IACLogger wrapper interface as well as the 1DS-specific implementation of the logger interface. Creating a generalized logger interface will allow easy logging to multiple telemetry platforms if desired, as well as prevent reliance of the existing Adaptive Cards code on a specific telemetry platform. The only changes to the existing JavaScript Adaptive Cards code will only include instantiation and function calls to the generalized IACLogger API.  
### 9.1 ACLogger Telemetry Wrapper 
The following is the proposed interface for the IACLogger: 
 
### 9.2 Location of IACLogger in Existing Code 

```
interface IACLogger { 
 
    logWarn(message: string): void; 
 
    logErr(message: string): void; 
 
    logVerbose(message: string): void; 
 
    logInfo(message: string): void; 
 
    logEvent(event: string, eventSourceName: string, correlationID: string, valueSet?: object): void; 
 
} 
 
enum TelemetryProvider { 
    OneDataStrategy, 
    File 
} 
 
class ACLogger implements IACLogger { 
    private static instance: IACLogger; 
    private listProviders: Set<TelemetryProvider>; 
    private providers: IACLogger[]; 
 
    public static getLogger(): IACLogger { 
        if (instance) { 
            return instance; 
        } else { 
            // throw error/exception 
        } 
    } 
 
    public static setLogger(...providers: TelemetryProvider[]): void { 
        // for each instance in providers, instantiate if instance has not yet been instantiated 
        for (let provider of providers) { 
            if (!this.listProviders.has(provider)) { 
                switch (provider) { 
                    case TelemetryProvider.File: 
                        providers.push(new FileACLogger()); 
                        break; 
                    case TelemetryProvider.OneDataStrategy: 
                        providers.push(new 1DSLogger()); 
                        break; 
                    default: 
                    // throw exception 
                } 
            } 
        } 
    } 
     
    public logWarn(message: string): void { 
        // call log warn and log for all instantiated providers 
        for (let provider of this.providers) { 
            provider.logWarn(message); 
        } 
    } 
 
    // .... etc.... 
 
} 
 
class Example { 
    main(): void { 
        var myLogger: IACLogger = ACLogger.getLogger(); 
        myLogger.setLogger(TelemetryProvider.OneDataStrategy, TelemetryProvider.File); 
        myLogger.logInfo("Logging to both 1DS and File..."); 
    } 
} 
```


 
### 9.3 Enabling Telemetry 
 
### 9.4 1DS Implementation of ACLogger 
There will be a JavaScript file that will implement the 1DS-specific version of the IACLogger. The functions will pass in the necessary parameters and will make calls to 1DS to send the info. The calls to events will happen for each element render and in post processing through the correlationID we will be able to tie the elements together.   
