export interface IACLoggerV3 {

	logWarn(message: string): void; 
	
	logError(message: string): void; 
	
	logVerbose(message: string): void; 
	
	logInfo(message: string): void; 
	
	logEvent(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

	createGUID(): void ;

	getGUID(): number;
	
}