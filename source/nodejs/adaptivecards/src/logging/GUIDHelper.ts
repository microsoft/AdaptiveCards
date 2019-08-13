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
	 * Returns the singleton instance of the GUIDHelper.
	 * If the instance has not yet been created, then the instance is created,
	 * then returned.
	 * 
	 * @returns Singleton instance of GUIDHelper
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
	 * Creates a new unique GUID and resets tracking
	 */
	createGUID(): void {
		this.guid = uuidv4();
		this.hasRating = false;
	}

	/**
	 * Retrieves the unique GUID corresponding to the class
	 * 
	 * @remarks
	 * When this method is called, the class begins tracking
	 * the corresponding GUID to convey that certain events
	 * be tracked in a card's future (e.g., SubmitButtonClicked)
	 * 
	 * @returns GUID. If createGUID() has not yet been called, then an undefined object will be returned
	 */
	getGUID(): number {
		this.hasRating = true;
		return this.guid;
	}

	/**
	 * Returns a boolean indicating whether or not events corresponding to a unique card's GUID
	 * should be tracked in the future (e.g., SubmitButtonClicked)
	 * 
	 * @returns true if future events should be tracked, false otherwise
	 */
	isGUIDtracked(): boolean {
		return this.hasRating;
	}
}