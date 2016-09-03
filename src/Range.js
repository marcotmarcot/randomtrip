function Range(base, visited) {
    this.base = base;
    this.visited = visited;
    this.isLon = true;
    this.start = new Point(-90, -180);
    this.end = new Point(90, 180);
}

Range.prototype.addPicked = function(picked) {
    if (this.isLon) {
        // TODO: Implement newLon.
        this.start.lon = this.newLon(picked - 1);
        this.end.lon = this.newLon(picked + 1);
    } else {
        this.start.lat = this.newLat(picked - 1);
        this.end.lat = this.newLat(picked + 1);
    }
    this.isLon = !this.isLon;
}

Range.prototype.newLat = function(picked) {
    start = this.start.lat;
    end = this.end.lat;
    switch (picked) {
    case 0:
        return start;
    case this.base:
        return end;
    }
    lon = this.center().lon
    minDistance = function(lat) {
        return this.visited.minDistance(new Point(lat, lon));
    }
    probability = function(lat) {
        return integral(start, lat, 1000, minDistance);
    }
    total = probability(end);
    goal = total / this.base * picked;
    return binarySearch(start, end, goal, total/1000, probability)
}

Range.prototype.center = function() {
    return new Point((this.start.lat+this.end.lat)/2, (this.start.lon+this.end.lon)/2);
}

function integral(start, end, steps, f) {
    step = (end-start)/steps
    total = 0
    for (i = start; i < end; i += step) {
        total += f(i) * step
    }
    return total
}

function binarySearch(start, end, goal, precision, f) {
    while (true) {
        middle = (end+start)/2
        current = f(middle)
        if (Math.abs(current-goal) < precision) {
            return middle
        }
        if (current < goal) {
            start = middle
        } else {
            end = middle
        }
    }
}
