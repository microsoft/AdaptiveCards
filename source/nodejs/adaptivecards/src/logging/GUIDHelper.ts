const uuidv4 = require('uuid/v4');

export class GUIDHelper {
	private guid: number;
	private static instance: GUIDHelper;
	private hasRating: boolean;

	private constructor() { }

	static getOrCreate(): GUIDHelper {
		if (this.instance) {
			return this.instance;
		} else {
			this.instance = new GUIDHelper();
			return this.instance;
		}
	}

	createGUID(): void {
		this.guid = uuidv4();
		this.hasRating = false;
	}

	getGUID(): number {
		this.hasRating = true;
		return this.guid;
	}

	useGUID(): boolean {
		return this.hasRating;
	}
}