function Point(lat, lon) {
    this.lat = lat;
    this.lon = lon;
}

// Returns the distance in km of the current Point and the Point o.
Point.prototype.distance = function(o) {
    // From http://www.movable-type.co.uk/scripts/latlong.html.
    p1 = radians(this.lat);
    p2 = radians(o.lat);
    dl = radians(o.lon - this.lon);
    R = 6371;
    return Math.acos(Math.sin(p1)*Math.sin(p2)+Math.cos(p1)*Math.cos(p2)*Math.cos(dl))*R;
}

function radians(degrees) {
    return degrees / 180 * Math.PI;
}
