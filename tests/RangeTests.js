describe("Range", function() {
    var range;

    beforeEach(function() {
        range = new Range(6);
    });

    it("should be constructed with base=6, start=0 and end=1", function() {
        expect(range.base).toEqual(6);
        expect(range.start).toEqual(0);
        expect(range.end).toEqual(1);
    });
});
