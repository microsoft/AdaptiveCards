import { IACProvider } from "../logging/IACProvider";

export interface IACLogger { 
 
	logWarn(message: string): void; 
	
	logError(message: string): void; 
	
	logVerbose(message: string): void; 
	
	logInfo(message: string): void; 
	
	logEvent(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

	getLogger(): IACLogger;
	
	configureProviders(...providers: IACProvider[]): void;

	configureDefaultProviders(): void;
	
   }