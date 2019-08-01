import { IACLoggerV3 } from "./IACLogger-v3";
import { IACProvider } from "./IACProvider";
import { LogLevel } from "./log-enums";
import { ConsoleLogger } from "./ConsoleLogger";
const uuidv4 = require('uuid/v4');

export class ACLoggerV3 implements IACLoggerV3 {

	private static instance: ACLoggerV3;
	private providers: IACProvider[];
	private GUID: number;

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

		for (var provider of this.providers) {
			provider.sendLogData(stringLevel, message);
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
			provider.sendData(event, eventSourceName, correlationID, valueSet);
		}
	}

	static getLogger(): IACLoggerV3 {
		if (this.instance) {
			return this.instance;
		} else {
			console.log("Providers not yet configured!");
			// throw new Error("Providers not yet configured!");
		}
	}

	static configureDefaultProviders(): void {

		this.checkInitialize();

		var hasConsole = false;
		var has1DS = false;

		// check if defaults have already been instantiated
		this.instance.providers.forEach(function(provider) {

			var providerName = Object.getPrototypeOf(provider).constructor.name;

			if (providerName === "ConsoleLogger") {
				hasConsole = true;
			} else if (providerName == "Microsoft1DS") {
				has1DS = true;
			}
		});

		if (!hasConsole) {
			this.instance.providers.push(new ConsoleLogger());
			
		}

		if (!has1DS) {
			// TODO: Implement Microsoft1DS Logging
			// ACLogger.providers.push(new Microsoft1DS());
		}
	}

	static configureProviders(...providers: IACProvider[]) {

		this.checkInitialize();

		providers.forEach(function(newProvider) {
			var hasProvider: boolean = false;
			var newProviderName: string = Object.getPrototypeOf(newProvider).constructor.name;

			// check if new provider is already configured
			this.providers.forEach(function(currentProvider) {
				if (newProviderName === Object.getPrototypeOf(currentProvider).constructor.name) {
					hasProvider = true;
				}
			});

			if (!hasProvider) {
				this.providers.push(newProvider);
			}
		});
	}

	// checks if instance and providers have been initialized
	private static checkInitialize(): void {
		if (!this.instance) {
			this.instance = new ACLoggerV3();
		}

		if (!this.instance.providers) {
			this.instance.providers = [];
		}
	}

	createGUID(): void {
		this.GUID = uuidv4();
	}

	getGUID(): number {
		return this.GUID;
	}

}