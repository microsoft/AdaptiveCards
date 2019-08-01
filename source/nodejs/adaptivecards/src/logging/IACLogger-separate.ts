/*

import { IACProvider} from "./IACProvider";
import { ACLogger } from "./ACLogger-separate";

export interface IACLoggerInstance {
	
	logWarn(message: string): void; 
	
	logError(message: string): void; 
	
	logVerbose(message: string): void; 
	
	logInfo(message: string): void; 
	
	logEvent(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

}

export interface IACLoggerStatic {
	
	getLogger(): ACLogger;
	
	configureProviders(...providers: IACProvider[]): void;

	configureDefaultProviders(): void;

}

*/