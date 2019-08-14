/*
	A console logging implementation of the IACProvider.
	Allows for all logging from an IACLogger to be output to the console.
*/
import { IACProvider } from "./IACProvider";

export class ConsoleProvider implements IACProvider {

	sendLogData(level: string, message: string) {
		console.log("Log" + level.toUpperCase() + ": " + message);
	}

	sendData(event: any, eventSourceName: any, correlationID?: any, valueSet?: any) {
		console.log("LogEvent: " + event + "\nSource: " + eventSourceName + 
		"\nCorrelationID: " + correlationID + "\n" + "valueSet: " + valueSet);
	}

}