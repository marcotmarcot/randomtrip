function Visited(points) {
    this.points = points;
}

Visited.prototype.minDistance = function(x) {
    // Earth perimeter is 40000km, so there should be no distance larger than
    // this.
    min = 100000
    this.points.forEach(function(point) {
        d = point.distance(x);
        if (d < min) {
            min = d;
        }
    });
    return min;
}
