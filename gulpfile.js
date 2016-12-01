var gulp        = require("gulp"),
    browserify  = require("browserify"),
    source      = require("vinyl-source-stream"),
    buffer      = require("vinyl-buffer"),
    tslint      = require("gulp-tslint"),
    tsc         = require("gulp-typescript"),
    sourcemaps  = require("gulp-sourcemaps"),
    uglify      = require("gulp-uglify"),
    exec        = require("child_process").exec,
    browserSync = require('browser-sync').create();

var interactiveVisualizerPath = "Visualizer/";
var schemaPath = "schemas/adaptive-card.json";
var samplesPath = "samples/**/**.json"

gulp.task("lint", function() {
    return gulp.src([
        "src/**/**.ts",
        "test/**/**.test.ts"
    ])
    .pipe(tslint({
        formatter: "prose",
        configuration: "tslint.json"
    }))
    .pipe(tslint.report({
         summarizeFailureOutput: true
    }));
});

var tsProject = tsc.createProject("tsconfig.json");

gulp.task("build-visualizer", function() {
    return gulp.src(
        [
            interactiveVisualizerPath + "src/**.ts"
        ])
        .pipe(sourcemaps.init())
        .pipe(tsProject())
        .pipe(sourcemaps.write("./"))
        .pipe(gulp.dest(interactiveVisualizerPath + "dist/"));
});

gulp.task("bundle-visualizer", function() {

    var libraryName = "Visualizer";
    var mainTsFilePath = interactiveVisualizerPath + "dist/app.js";
    var outputFolder   = "dist/";
    var outputFileName = libraryName + ".min.js";

    var bundler = browserify({
        debug: true,
        standalone : libraryName
    });

    return bundler.add(mainTsFilePath)
        .bundle()
        .pipe(source(outputFileName))
        .pipe(buffer())
        .pipe(sourcemaps.init({ loadMaps: true }))
        .pipe(uglify())
        .pipe(sourcemaps.write('./'))
        .pipe(gulp.dest(outputFolder));
});

gulp.task("watch", ["default"], function() {

    browserSync.init({
        server: "."
    });

    gulp.watch([ "src/**/**.ts", "test/**/*.ts"], ["default"]);
    gulp.watch("dist/*.js").on('change', browserSync.reload);
});

gulp.task("validate-schema", function(cb) {
    exec("ajv validate -s " + schemaPath + " -d " + samplesPath, function (err, stdout, stderr) {
        console.log(stdout);
        console.log(stderr);
        cb(err);
    });
});