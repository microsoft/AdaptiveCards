export class Collection {
    constructor() {
        this._items = [];
        this.onItemAdded = null;
        this.onItemRemoved = null;
    }
    get(index) {
        return this._items[index];
    }
    add(item) {
        this._items.push(item);
        if (this.onItemAdded) {
            this.onItemAdded(item);
        }
    }
    remove(item) {
        var i = this._items.indexOf(item);
        if (i >= 0) {
            this._items = this._items.splice(i, 1);
            if (this.onItemRemoved) {
                this.onItemRemoved(item);
            }
        }
    }
    indexOf(item) {
        return this._items.indexOf(item);
    }
    get length() {
        return this._items.length;
    }
}
//# sourceMappingURL=collection.js.map