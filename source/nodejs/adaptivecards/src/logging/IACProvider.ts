/*
	The IACProvider interface. All provider implementations must follow this interface
	in order to be used within the IACLogger.
*/
export interface IACProvider {

	/**
	 * Sends a log message to the telemetry provider.
	 * 
	 * @remarks
	 * Any errors originating from the telemetry platform will be logged to the console.
	 * 
	 * @param level - The level of the message to be logged
	 * @param message - The message to be logged
	 */
	sendLogData(level: string, message: string): void;

	/**
	 * Sends an event to the telemetry provider.
	 * 
	 * @remarks
	 * Any errors originating from the telemetry platform will be logged to the console.
	 * 
	 * @param event - The name of the event to be logged (e.g., RenderCard)
	 * @param eventSourceName - The name of the source element corresponding to the event (e.g., TextBlock)
	 * @param correlationID - (optional) The unique correlation identifier to correlate events relating to the same Adaptive Card 
	 * @param valueSet - (optional) An object containing key-value pairs corresponding to data for telemetry metrics (e.g., { defaultIconUsed: true })
	 */
	sendData(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

}