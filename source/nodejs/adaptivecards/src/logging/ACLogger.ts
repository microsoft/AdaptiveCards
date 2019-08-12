import { IACProvider } from "./IACProvider";
import { LogLevel } from "./log-enums";
import { ConsoleLogger } from "./ConsoleLogger";
import { Microsoft1DSLogger } from "./Microsoft1DSLogger/Microsoft1DSLogger";
import { IACLogger } from "./IACLogger";

/*
	The implementation of the IACLogger to be used within the
	Adaptive Cards JS renderer.
*/
export class ACLogger implements IACLogger {

	private static instance: IACLogger;
	private providers: IACProvider[];

	private constructor() {	}

	private log(level: LogLevel, message: string): void {

		// if providers have not yet been configured, then exit
		if (!this.providers) {
			console.log("ERROR: Providers have not yet been configured!");
			return;
		}

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
				console.log("ERROR: LogLevel undefined.");
				return;
		}

		for (var provider of this.providers) {

			try {
				provider.sendLogData(stringLevel, message);
			} catch (e) {
				console.log("ERROR: Error logging to provider " + Object.getPrototypeOf(provider).constructor.name + " - " + e);
			}
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
		for (var provider of this.providers) {
			try {
				provider.sendData(event, eventSourceName, correlationID, valueSet);
			} catch (e) {
				console.log("ERROR: Error logging to provider " + Object.getPrototypeOf(provider).constructor.name + " - " + e);
			}
		}
	}

	/**
	 * Returns the singleton instance of the ACLogger.
	 * If the instance has not yet been created, then the instance is created,
	 * then returned.
	 */
	static getOrCreate(): IACLogger {
		if (!this.instance) {
			this.instance = new ACLogger();
		}

		return this.instance;
	}
	
	configureDefaultProviders(): void {

		if (!this.providers) {
			this.providers = [];
		}

		var hasConsole = false;
		var has1DS = false;

		// check if defaults have already been instantiated
		this.providers.forEach(function(provider) {

			var providerName = Object.getPrototypeOf(provider).constructor.name;

			if (providerName === "ConsoleLogger") {
				hasConsole = true;
			} else if (providerName == "Microsoft1DS") {
				has1DS = true;
			}
		});

		if (!hasConsole) {
			this.providers.push(new ConsoleLogger());
			
		}

		if (!has1DS) {
			this.providers.push(new Microsoft1DSLogger());
		}
	}
	

	configureCustomProviders(...providers: IACProvider[]): void {

		if (providers === undefined || providers.length == 0) {
			this.configureDefaultProviders();
			return;
		}

		if (!this.providers) {
			this.providers = [];
		}

		providers.forEach(function(newProvider) {
			var hasProvider: boolean = false;
			var newProviderName: string = Object.getPrototypeOf(newProvider).constructor.name;

			// check if new provider is already configured
			this.providers.forEach(function(currentProvider: IACProvider) {
				if (newProviderName === Object.getPrototypeOf(currentProvider).constructor.name) {
					hasProvider = true;
				}
			});

			if (!hasProvider) {
				this.providers.push(newProvider);
			}
		});
	}

}