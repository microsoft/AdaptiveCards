const uuidv4 = require('uuid/v4');

/*
A helper class to generate, keep track of, and return a unique GUID
to correlate events throughout a unique card's life cycle.
*/
export class GUIDHelper {
	private _guid: number;
	private static _instance: GUIDHelper;
	private _hasRating: boolean;

	private constructor() { }

	/**
	 * Returns the singleton instance of the GUIDHelper.
	 * If the instance has not yet been created, then the instance is created,
	 * then returned.
	 * 
	 * @returns Singleton instance of GUIDHelper
	 */
	static getOrCreate(): GUIDHelper {
		if (this._instance) {
			return this._instance;
		} else {
			this._instance = new GUIDHelper();
			return this._instance;
		}
	}

	/**
	 * Creates a new unique GUID and resets tracking
	 */
	createGUID(): void {
		this._guid = uuidv4();
		this._hasRating = false;
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
		return this._guid;
	}

	/**
	 * When called, indicates that logging calls should occur for a specific card
	 * in the future and GUIDs should be correlated
	 */
	trackGUID(): void {
		this._hasRating = true;
	}

	/**
	 * Returns a boolean indicating whether or not events corresponding to a unique card's GUID
	 * should be tracked in the future (e.g., SubmitButtonClicked)
	 * 
	 * @returns true if future events should be tracked, false otherwise
	 */
	isGUIDtracked(): boolean {
		return this._hasRating;
	}
}