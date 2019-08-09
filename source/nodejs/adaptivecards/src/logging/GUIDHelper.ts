const uuidv4 = require('uuid/v4');

/*
A helper class to generate, keep track of, and return a unique GUID
to correlate events throughout a unique card's life cycle.
*/
export class GUIDHelper {
	private guid: number;
	private static instance: GUIDHelper;
	private hasRating: boolean;

	private constructor() { }

	/**
	 * Returns the singleton instance of the ACLogger.
	 * If the instance has not yet been created, then the instance is created,
	 * then returned.
	 */
	static getOrCreate(): GUIDHelper {
		if (this.instance) {
			return this.instance;
		} else {
			this.instance = new GUIDHelper();
			return this.instance;
		}
	}

	/**
	 * Creates a unique GUID and resets tracking
	 */
	createGUID(): void {
		this.guid = uuidv4();
		this.hasRating = false;
	}

	/**
	 * 
	 */
	getGUID(): number {
		this.hasRating = true;
		return this.guid;
	}

	trackGUID(): boolean {
		return this.hasRating;
	}
}