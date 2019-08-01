/*import {IACLoggerInstance, IACLoggerStatic} from "./IACLogger-separate";
import { LogLevel } from "./log-enums";
import { IACProvider } from "./IACProvider";
import { ConsoleLogger } from "./ConsoleLogger"

function staticInterface<T>() {
	return <U extends T>(constructor: U) => {constructor};
}

@staticInterface<IACLoggerStatic>()
export class ACLogger implements IACLoggerInstance {
	private static instance: ACLogger;
	private static providers: IACProvider[];

	private constructor() {	}

	private log(level: LogLevel, message: string) {
		var stringLevel: string = "";

		switch (level) {
			case LogLevel.Warn:
				stringLevel = "warn";
				break;
			case LogLevel.Error:
				stringLevel = "error";
				break;
			case LogLevel.Verbose:
				stringLevel = "verbose";
				break;
			case LogLevel.Info:
				stringLevel = "info";
				break;
			default:
				// throw error, or console message?
		}

		for (var provider of ACLogger.providers) {
			provider.sendData(stringLevel, message);
		}
	}

	logWarn(message: string): void {
		this.log(LogLevel.Warn, message);
	}

	logError(message: string): void {
		this.log(LogLevel.Error, message);
	}

	logVerbose(message: string): void {
		this.log(LogLevel.Verbose, message);
	}

	logInfo(message: string): void {
		this.log(LogLevel.Info, message);
	}
	
	logEvent(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void {
		for (var provider of ACLogger.providers) {
			provider.sendData(event, eventSourceName, correlationID, valueSet);
		}
	}

	static getLogger(): ACLogger {
		if (ACLogger.instance) {
			return ACLogger.instance;
		} else {
			// throw new Error("Providers not yet configured!");
		}
	}

	static configureDefaultProviders(): void {
		var hasConsole = false;
		var has1DS = false;

		// check if defaults have already been instantiated
		ACLogger.providers.forEach(function(provider) {

			var providerName = Object.getPrototypeOf(provider).constructor.name;

			if (providerName === "ConsoleLogger") {
				hasConsole = true;
			} else if (providerName == "Microsoft1DS") {
				has1DS = true;
			}
		});

		if (!hasConsole) {
			// TODO: Implement Microsoft1DS Logging
			// ACLogger.providers.push(new Microsoft1DS());
		}

		if (!has1DS) {
			// TODO: Implement ConsoleLogger
			ACLogger.providers.push(new ConsoleLogger());
		}
	}

	static configureProviders(...providers: IACProvider[]) {
		providers.forEach(function(newProvider) {
			var hasProvider: boolean = false;
			var newProviderName: string = Object.getPrototypeOf(newProvider).constructor.name;

			// check if new provider is already configured
			ACLogger.providers.forEach(function(currentProvider) {
				if (newProviderName === Object.getPrototypeOf(currentProvider).constructor.name) {
					hasProvider = true;
				}
			});

			if (!hasProvider) {
				ACLogger.providers.push(newProvider);
			}
		});
	}

}
*/