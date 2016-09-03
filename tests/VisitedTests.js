describe("Visited", function() {
    it("should return Rio's distance if the current point is Belo Horizonte and Rio and London are visited", function() {
        bh = new Point(-19.9178576, -44.0305233);
        rio = new Point(-22.9111718, -43.5887611);
        london = new Point(51.5285578, -0.2420229);
        visited = new Visited([rio, london]);
        expect(visited.minDistance(bh)).toBeCloseTo(335.9671855666);
    });
});
