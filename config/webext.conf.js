module.exports = {
    verbose: true,
    build: {
        overwriteDest: true,
    },
    sourceDir: './dist',
    run: {
        // this doesnt really work, setting in package.json instead, see: https://github.com/mozilla/web-ext/issues/1862
        target: [
            "firefox-desktop",
            "chromium"
        ],
        startUrl: ['about:debugging'],
    }
};
