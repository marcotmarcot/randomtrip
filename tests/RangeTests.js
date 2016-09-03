describe("Range", function() {
    var range;

    it("should divide the latitude in 6 parts with no visited", function() {
        r = new Range(6, new Visited([]))
        expect(r.newLat(0)).toBeCloseTo(-90, 1);
        expect(r.newLat(1)).toBeCloseTo(-60, 1);
        expect(r.newLat(2)).toBeCloseTo(-30, 1);
        expect(r.newLat(3)).toBeCloseTo(0, 1);
        expect(r.newLat(4)).toBeCloseTo(30, 1);
        expect(r.newLat(5)).toBeCloseTo(60, 1);
        expect(r.newLat(6)).toBeCloseTo(90, 1);
    });

    it("should integrate first degree functions correctly", function() {
        y = integral(0, 10, 1000000, function(x) {
            return x;
        });
        expect(y).toBeCloseTo(50);
    });

    it("should integrate cos functions correctly", function() {
        y = integral(0, Math.PI, 1000000, function(x) {
            return Math.cos(x);
        });
        expect(y).toBeCloseTo(0);
    });

    it("should do binary search correctly with a square function", function() {
        y = binarySearch(0, 10, 4, 0.000001, function(x) {
            return x * x;
        });
        expect(y).toBeCloseTo(2);
    });

    it("should do binary search correctly with a complex function", function() {
        y = binarySearch(0, 100, 9, 0.000001, function(x) {
            a = Math.sqrt(x + 7);
            return a * a;
        });
        expect(y).toBeCloseTo(2);
    });

    // it("should be constructed with base=6, start=0 and end=1", function() {
    //     expect(range.base).toEqual(6);
    //     expect(range.start).toEqual(0);
    //     expect(range.end).toEqual(1);
    // });

    // it("should be centered at 0.5", function() {
    //     expect(range.center()).toBeCloseTo(0.5);
    // });

    // it("should squeeze interval to [0, 1/base] when picked is 1", function() {
    //     range.addPicked(1);
    //     expect(range.start).toBeCloseTo(0);
    //     expect(range.end).toBeCloseTo(1 / range.base);
    // });

    // it("should squeeze interval to [2/base, 3/base] when picked is 3", function() {
    //     range.addPicked(3);
    //     expect(range.start).toBeCloseTo(2 / range.base);
    //     expect(range.end).toBeCloseTo(3 / range.base);
    // });

    // it("should squeeze interval to [5/base, 1] when picked is 6", function() {
    //     range.addPicked(6);
    //     expect(range.start).toBeCloseTo(5 / range.base);
    //     expect(range.end).toBeCloseTo(1);
    // });

    // it("should squeeze interval to [0, 1/base^2] when 1 is picked twice", function() {
    //     range.addPicked(1);
    //     range.addPicked(1);
    //     expect(range.start).toBeCloseTo(0);
    //     expect(range.end).toBeCloseTo(1 / (range.base*range.base));
    // });

    // it("should make a newSize of 1/6", function() {
    //     expect(range.newSize()).toBeCloseTo(1/6);
    // });
});
