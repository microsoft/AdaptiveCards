import { IACProvider } from "./IACProvider";

export class ConsoleLogger implements IACProvider {

	sendLogData(level: string, message: string) {
		console.log(level + " --- " + message);
	}

	sendData(event: any, eventSourceName: any, correlationID?: any, valueSet?: any) {
		console.log(event + " ---- " + eventSourceName);
		console.log("Other " + correlationID + " --- " + valueSet);
		if (valueSet) {
			console.log(valueSet["defaultScale"]);
		}
	}

	
}