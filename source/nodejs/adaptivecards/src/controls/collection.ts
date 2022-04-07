// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export class Collection<TItem> {
    private _items: Array<TItem> = [];

    onItemAdded: (item: TItem) => void;
    onItemRemoved: (item: TItem) => void;

    get(index: number): TItem {
        return this._items[index];
    }

    add(item: TItem) {
        this._items.push(item);

        if (this.onItemAdded) {
            this.onItemAdded(item);
        }
    }

    remove(item: TItem) {
        const i = this._items.indexOf(item);

        if (i >= 0) {
            this._items = this._items.splice(i, 1);

            if (this.onItemRemoved) {
                this.onItemRemoved(item);
            }
        }
    }

    indexOf(item: TItem): number {
        return this._items.indexOf(item);
    }

    get length(): number {
        return this._items.length;
    }
}
