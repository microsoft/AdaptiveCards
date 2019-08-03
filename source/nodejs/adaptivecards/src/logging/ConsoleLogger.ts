import { IACProvider } from "./IACProvider";

export class ConsoleLogger implements IACProvider {

	sendLogData(level: string, message: string) {
		console.log(level + " --- " + message);
	}

	sendData(event: any, eventSourceName: any, correlationID?: any, valueSet?: any) {
		console.log(event + " ---- " + eventSourceName);
		console.log("Correlation ID + optional valueSet " + correlationID + " --- " + valueSet);
	}

	
}