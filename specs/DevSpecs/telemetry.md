# Input.Rating Telemetry Design Specification 
 
## Abstract 
This design specification covers telemetry integration into the `Input.Rating` control, which will be included in a future release of Adaptive Cards. Telemetry integration is currently slated only for the JavaScript platform; however, this developer specification will be general enough to cover all platforms supported by Adaptive Cards. This telemetry design will focus on sending telemetry via the 1DS platform, but the design is flexible enough to allow for possible integration of other telemetry platforms in the future. See more at the GitHub issue [3058](https://github.com/microsoft/AdaptiveCards/issues/3058).
 
## 1. Feature Dependencies 
### 1.1 Dependencies on other features 
This feature is dependent on the functionality of the 1DS SDK for sending data up through the Microsoft telemetry pipeline.
 
### 1.2 Other features' dependencies on this feature 
There are currently no other existing features that directly depend on this feature. However, future telemetry integration for other elements will be based on the design presented here. 
 
## 2. Platform-Specific Considerations 
UWP, JS, and .NET are all currently supported by 1DS, allowing for relatively seamless integration of telemetry for these platforms. Mobile platforms (ie., Android and iOS) are not fully supported by 1DS, so future communication and cooperation with the 1DS team to achieve support for these platforms is necessary. 
 
## 3. Performance Implications 
> “Perf-penalty in terms of runtime perf on foreground threads should not be affected; all our log event API calls are async. Background threads would kick in when there's time to upload. Total CPU time to upload would depend how much data you logged. In UTC mode - the perf penalty vs. trace logging would be near-zero. About the same.” - Max Golovanov (1DS) 

We will look further into how 1DS affects startup time and memory usage with comparison tests. The real-world perf numbers would depend on telemetry volume per minute. The performance implications shouldn’t be major, but will exist.  
 
 
## 4. Backwards Compatibility Concerns  
There are no backwards compatibility concerns at this time.
 
## 5. Security Impact 
Security should be considered in the situation of protecting the token and telemetry pipeline from malicious parties. Although Adaptive Cards is open source, we do not plan on exposing the telemetry token to the public. Thus, distribution of Adaptive Cards versions with telemetry should be limited to internal use cases only (within Microsoft Corp. only). This may change upon further discussion with the 1DS team.
 
## 6. New APIs 
This feature will introduce the IACLogger, which provides the following interface (see [section 9.1](#91-aclogger-telemetry-wrapper) for examples and implementation details):

```
interface IACLogger { 
 
	logWarn(message: string): void; 
	
	logError(message: string): void; 
	
	logVerbose(message: string): void; 
	
	logInfo(message: string): void; 
	
	logEvent(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

	getLogger(): IACLogger;
	
	configureProviders(...providers: IACProvider[]): void;

	configureDefaultProviders(): void;
	
   }
```

This feature will also introduce the IACProvider, which provides the following interface:

```
interface IACProvider {

	sendData(level: string, message: string): void;

	sendData(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

}
```
 
## 7. Testing Details 
### 7.1 Preliminary Testing

Preliminary testing of the telemetry wrapper will be carried out by logging to the file system. Separation between the telemetry wrapper and the 1DS-specific telemetry implementation will make it easier to pinpoint any possible bugs or failures.

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
| CorrelationID                | N/A            | 
| AppID                        | N/A            | 
| DeviceID                     | N/A            | 
| OperationResult              | 0 - Success    | 
| NumberOfFeedbackControls     | 1              | 
| NumberOfElements             | 1              | 
| ElementNames                 | [Input.Rating] | 
| TotalDefaultRatingScalesUsed | 1              | 
| TotalDefaultStarImagesUsed   | 1              | 
| isDeveloper                  | N/A            | 
 
Note: This information will not be recorded in one `logEvent()` call. Rather, this output reflects the expected values after post-processing of telemetry data. In addition, the value "N/A" indicates that this is a property that will be generated on runtime/post-processing and does not have any relationship with the card JSON itself (and thus is not applicable to the example).
 
## 8. Estimated Dev Cost 
With two full-time interns working on this feature, implementation of telemetry in JavaScript should take one month, with estimated delivery being mid-August. Within this time frame, progress in the UWP Adaptive Cards platform may also be a plausible stretch goal. 
 
## 9. JavaScript Architecture Details 
The main components of telemetry in the JavaScript platform will include the IACLogger wrapper interface as well as the 1DS-specific implementation of the logger interface. Creating a generalized logger interface will allow easy logging to multiple telemetry platforms if desired, as well as prevent reliance of the existing Adaptive Cards code on a specific telemetry platform. The only changes to the existing JavaScript Adaptive Cards code will only include new instantiation and function calls to the generalized IACLogger API.  

### 9.1 ACLogger Telemetry Wrapper 
The following is the proposed interface for the IACLogger, along with example use cases: 

```
interface IACLogger { 
 
    logWarn(message: string): void; 
 
    logErr(message: string): void; 
 
    logVerbose(message: string): void; 
 
    logInfo(message: string): void; 
 
    logEvent(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void; 
 
}

interface IACProvider {

	sendData(level: string, message: string): void;

	sendData(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

}
 
class ACLogger implements IACLogger {
	private static instance: IACLogger;
	private static providers: IACProvider[];

	private constructor() {	}

	private log(level: LogLevel, message: string) {
		var stringLevel: string = "";

		switch (level) {
			case LogLevel.Warn:
				stringLevel = "warn";
				break;
			case LogLevel.Error:
				stringLevel = "error";
				break;
			case LogLevel.Verbose:
				stringLevel = "verbose";
				break;
			case LogLevel.Info:
				stringLevel = "info";
				break;
			default:
				// throw error, or console message?
		}

		for (var provider of ACLogger.providers) {
			provider.sendData(stringLevel, message);
		}
	}

	logWarn(message: string): void {
		this.log(LogLevel.Warn, message);
	}

	// etc...

	getLogger(): IACLogger {
		if (ACLogger.instance) {
			return ACLogger.instance;
		} else {
			// throw new Error("Providers not yet configured!");
		}
	}

	configureDefaultProviders(): void {
		// instantiate console and Microsoft1DS loggers if either have not yet been instantiated
	}

	configureProviders(...providers: IACProvider[]) {
		// for each specified provider, instantiate the provider if the implementation has not yet been instantiated

}
 
class Example { 
    main(): void { 
        var myLogger: IACLogger = ACLogger.getLogger(); 
        myLogger.configureDefaultProviders(); 
        myLogger.logInfo("Logging to both 1DS and File..."); 
    } 
} 
```
* ACLogger will be instantiated as a singleton, with the option to log to multiple telemetry platforms concurrently
* The `valueSet` parameter of the `logEvent()` function will be used to send information including whether or not the default icons and default rating quantities were used.
* Once instantiated, the logger will log to the console by default.

### 9.2 Logger Extensibility
The logger will be able to integrate with additional providers that are not specified. In addition, documentation will be provided for cases in which a user would like to implement logging in their own custom controls.
 
### 9.3 Location of IACLogger in Existing Code 

#### Instantiation
The instance of ACLogger will be instantiated when the constructor of the `AdaptiveCard` object is called. Because the logger will belong to the ACLogger class and will be retrieved statically, logging will be possible anywhere within the existing JavaScript code without the need for global variables.

#### Logging Events
In order to record AuthorCard and RenderCard events, `logEvent()` will be called specifically in the `toJSON()` and `parse()` functions. Integration into `toJSON()` will be necessary to keep track of all cards that are serialized and sent by an author using our authoring SDK. Regardless of how it is authored, a card must be `parse()`d before it can be rendered. Therefore, with the integration of an event call in this function along with some post-processing, cards that were authored using the object model can be separated from those that were not.

In terms of priorities, it is important to note that RenderCard is P0 and AuthorCard is P2; the capturing of the AuthorCard event is low priority.

One corner case arises when an individual both authors and renders a card on the same client (see figure below). In this case, the card is not `parse()`d and will not be captured in our telemetry pipeline. However, this case has been considered and ultimately deemed unnecessary for capture due to the low probability of this scenario occuring. Limiting scope to these two functions also facilitates modularity within existing code.

<img src="https://i.imgur.com/KZRMgWY.png"  width="600" height="auto">

The OnSubmitButtonClicked event will be captured in the corresponding event listener belonging to the `Action.Submit` class.
 
### 9.4 Enabling Telemetry 
Telemetry will be enabled or disabled through the use of environment variables.

### 9.5 1DS Implementation of ACLogger 
There will be a JavaScript file that will implement the 1DS-specific version of the IACLogger. The functions will pass in the necessary parameters and will make calls to 1DS to send the info. The calls to events will happen for each element render and in post processing through the correlationID we will be able to tie the elements together.   
