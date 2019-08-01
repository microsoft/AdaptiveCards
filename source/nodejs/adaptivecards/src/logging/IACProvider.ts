export interface IACProvider {

	sendLogData(level: string, message: string): void;

	sendData(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

}