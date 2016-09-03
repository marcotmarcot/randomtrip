describe("Point", function() {
    it("should return 336km as the distance between Belo Horizonte and Rio", function() {
        bh = new Point(-19.9178576, -44.0305233);
        rio = new Point(-22.9111718, -43.5887611);
        expect(bh.distance(rio)).toBeCloseTo(335.9671855666);
    });

    it("should return PI/2 radians with 90 degrees", function() {
        r = radians(90);
        expect(r).toBeCloseTo(Math.PI / 2);
    });
});
