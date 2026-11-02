// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { formatText } from "../text-formatters";


function isoDate(tz: string = ""): string {
	return `2023-10-01T12:00:00${tz}`;
}

describe("Text Formatters", () => {
	test("UTC formatter", () => {
		const date = isoDate("Z");
		const res = formatText("en-GB", `{{DATE(${date}, SHORT)}} {{TIME(${date})}}`);
		expect(res).toBe("Sun, 1 Oct 2023 12:00");
	});

	describe("Timezone leading to date change", () => {
		test("Negative date change", () => {
			const date = isoDate("+13:00");
			const res = formatText("en-GB", `{{DATE(${date}, SHORT)}} {{TIME(${date})}}`);
			expect(res).toBe("Sat, 30 Sept 2023 23:00");
		});


		test("Positive date change", () => {
			const date = isoDate("-13:00");
			const res = formatText("en-GB", `{{DATE(${date}, SHORT)}} {{TIME(${date})}}`);
			expect(res).toBe("Mon, 2 Oct 2023 1:00");
		});
	});

	test("Date without timezone", () => {
		const date = isoDate();
		const res = formatText("en-GB", `{{DATE(${date}, SHORT)}} {{TIME(${date})}}`);
		expect(res).toBe("Sun, 1 Oct 2023 12:00");
	});
});