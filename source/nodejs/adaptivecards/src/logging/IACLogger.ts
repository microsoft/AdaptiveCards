import { IACProvider } from "./IACProvider";

/*
	The IACLogger interface. All logger implementations must follow this interface.
*/
export interface IACLogger {

	/**
	 * Logs a warning message to all providers configured to the IACLogger.
	 * 
	 * @param message - The message to be logged
	 */
	logWarn(message: string): void; 
	
	/**
	 * Logs an error message to all providers configured to the IACLogger.
	 * 
	 * @param message - The message to be logged
	 */
	logError(message: string): void; 
	
	/**
	 * Logs a verbose message to all providers configured to the IACLogger.
	 * 
	 * @param message - The message to be logged
	 */
	logVerbose(message: string): void; 
	
	/**
	 * Logs an info message to all providers configured to the IACLogger.
	 * 
	 * @param message - The message to be logged
	 */
	logInfo(message: string): void; 
	
	/**
	 * Logs an event to all providers configured to the IACLogger.
	 * 
	 * @param event - The name of the event to be logged (e.g., RenderCard)
	 * @param eventSourceName - The name of the source element corresponding to the event (e.g., TextBlock)
	 * @param correlationID - (optional) The unique correlation identifier to correlate events relating to the same Adaptive Card 
	 * @param valueSet - (optional) An object containing key-value pairs corresponding to data for telemetry metrics (e.g., { defaultIconUsed: true })
	 */
	logEvent(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

	/**
	 * Configures the IACLogger to log to the instances of the providers specified in the parameters.
	 * 
	 * @remarks
	 * If an IACLogger is not configured before logging, then an error will be output to the console and no event/message will be logged.
	 * 
	 * @param providers - The custom instances of providers that IACLogger will log to, in comma-separated form. If no providers
	 * are given, then the Microsoft1DS and ConsoleLogger providers will be configured.
	 */
	configureCustomProviders(...providers: IACProvider[]): void;

	/**
	 * Configures the IACLogger to log to the Microsoft1DS telemetry platform and the console.
	 * 
	 * @remarks
	 * If an IACLogger is not configured before logging, then an error will be output to the console and no event/message will be logged.
	 * 
	 */
	configureDefaultProviders(): void;

}