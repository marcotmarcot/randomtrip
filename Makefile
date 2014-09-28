.PHONY: dist clean

dist: dist/randomtrip.min.js dist/randomtrip.html

clean:
	rm -rf dist

dist/randomtrip.min.js: src/*.js
	@mkdir -p dist
	yui-compressor --type js -o $@ $<

dist/randomtrip.html: randomtrip.html
	@mkdir -p dist
	cp randomtrip.html dist/
