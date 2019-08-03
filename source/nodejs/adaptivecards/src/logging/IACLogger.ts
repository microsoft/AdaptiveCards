import { IACProvider } from "./IACProvider";

export interface IACLogger {

	logWarn(message: string): void; 
	
	logError(message: string): void; 
	
	logVerbose(message: string): void; 
	
	logInfo(message: string): void; 
	
	logEvent(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

	configureCustomProviders(...providers: IACProvider[]): void;

	configureDefaultProviders(): void;

}