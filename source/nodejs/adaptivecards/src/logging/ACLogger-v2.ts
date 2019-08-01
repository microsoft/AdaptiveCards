import { IACLoggerAbstract } from "./IACLoggerAbstract-v2";
import { LogLevel } from "./log-enums";

export class ACLoggerV2 extends IACLoggerAbstract {

	private constructor() {
		super();
	}

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

		for (var provider of ACLoggerV2.getProviders()) {
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
		for (var provider of ACLoggerV2.getProviders()) {
			provider.sendData(event, eventSourceName, correlationID, valueSet);
		}
	}

}