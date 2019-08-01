import { ApplicationInsights } from '@ms/1ds-analytics-web-js'; //Imported for 1DS telemetry

class Microsoft1DSLogger {
	analytics: ApplicationInsights;
	constructor(){
		this.analytics = new ApplicationInsights();
		var config = {
		  instrumentationKey: "ec1a2b0d82c34dd79e5b7c5c6592b53b-8be431e3-9278-4fcc-be8d-281f5376ca36-7052",
		  channelConfiguration:{ // Post channel configuration
			  eventsLimitInMem: 50
		  },
		  propertyConfiguration: { // Properties Plugin configuration
			  userAgent: "Custom User Agent"
		  },
		  webAnalyticsConfiguration:{ // Web Analytics Plugin configuration
			  autoCapture: {
				scroll: false,
				pageView: false,
				onLoad: false,
				onUnload: false,
				click: false,
				resize: false,
				jsError: false
			  }
		  }
		}; 
		//Initialize SDK
		this.analytics.initialize(config, []);
	}
	sendLogData(level: string, message: string){
		this.analytics.trackEvent({
			name: "sendLogData",
			data: {
				level: level,
				message: message,
			},
			baseData: {
				//testbaseData1: "testbaseDataValue1"
			},
			//baseType: "testBaseType"
		});
	}

	sendData(event: string, eventSourceName: string, correlationID?: string, valueSet?: object){
		//if no valueSet send one event
		//if valueSet is empty send one event
		if (valueSet != undefined){
			//Create array of keys and values from the valueSet object
			for(const [key, value] of Object.entries(valueSet)){
				this.analytics.trackEvent({
					name: "sendData",
					data: {
						event: event,
						eventSourceName: eventSourceName,
						correlationID: correlationID,
						key: key,
						value: value,
					},
					baseData: {
						//testbaseData1: "testbaseDataValue1"
					},
					//baseType: "testBaseType"
				});
			}			
		}
		else {
			this.analytics.trackEvent({
				name: "sendData",
				data: {
					event: event,
					eventSourceName: eventSourceName,
					correlationID: correlationID,
				},
				baseData: {
					//testbaseData1: "testbaseDataValue1"
				},
				//baseType: "testBaseType"
			});
		}
	}
}
