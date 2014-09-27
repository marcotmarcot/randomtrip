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

    it("should be centered at 0.5", function() {
        expect(range.center()).toEqual(0.5);
    });

    it("should squeeze interval to [0, 1/base] when picked is 1", function() {
        range.addPicked(1);
        expect(range.start).toBeCloseTo(0);
        expect(range.end).toBeCloseTo(1 / range.base);
    });

    it("should squeeze interval to [2/base, 3/base] when picked is 3", function() {
        range.addPicked(3);
        expect(range.start).toBeCloseTo(2 / range.base);
        expect(range.end).toBeCloseTo(3 / range.base);
    });

    it("should squeeze interval to [5/base, 1] when picked is 6", function() {
        range.addPicked(6);
        expect(range.start).toBeCloseTo(5 / range.base);
        expect(range.end).toBeCloseTo(1);
    });
});
