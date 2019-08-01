import { IACLoggerV2 } from "./IACLogger-v2";
import { IACProvider } from "./IACProvider";
import { ConsoleLogger } from "./ConsoleLogger";

export abstract class IACLoggerAbstract implements IACLoggerV2 {
	private static instance: IACLoggerV2;
	private static providers: IACProvider[];

	abstract logWarn(message: string): void; 
	
	abstract logError(message: string): void; 
	
	abstract logVerbose(message: string): void; 
	
	abstract logInfo(message: string): void; 
	
	abstract logEvent(event: string, eventSourceName: string, correlationID?: string, valueSet?: object): void;

	static getLogger(): IACLoggerV2 {
		if (IACLoggerAbstract.instance) {
			return IACLoggerAbstract.instance;
		} else {
			// throw new Error("Providers not yet configured!");
		}
	}

	static configureDefaultProviders(): void {
		var hasConsole = false;
		var has1DS = false;

		// instantiate providers if not already instantiated
		if (!IACLoggerAbstract.providers) {
			IACLoggerAbstract.providers = [];
		}

		// check if defaults have already been instantiated
		IACLoggerAbstract.providers.forEach(function(provider) {

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
			IACLoggerAbstract.providers.push(new ConsoleLogger());
		}
	}

	static configureProviders(...providers: IACProvider[]) {

		// instantiate providers if not already instantiated
		if (!IACLoggerAbstract.providers) {
			IACLoggerAbstract.providers = [];
		}

		providers.forEach(function(newProvider) {
			var hasProvider: boolean = false;
			var newProviderName: string = Object.getPrototypeOf(newProvider).constructor.name;

			// check if new provider is already configured
			IACLoggerAbstract.providers.forEach(function(currentProvider) {
				if (newProviderName === Object.getPrototypeOf(currentProvider).constructor.name) {
					hasProvider = true;
				}
			});

			if (!hasProvider) {
				IACLoggerAbstract.providers.push(newProvider);
			}
		});
	}

	static getProviders(): IACProvider[] {
		return this.providers;
	}



}