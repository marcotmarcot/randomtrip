function Range(base) {
    this.base = base;
    this.start = 0;
    this.end = 1;
}

Range.prototype.addPicked = function(picked) {
    var newSize = this.newSize();
    this.start = this.start + (picked-1) * newSize;
    this.end = this.start + newSize;
}

Range.prototype.newSize = function() {
    return (this.end - this.start) / this.base;
}

Range.prototype.center = function() {
    return (this.end + this.start) / 2;
}
