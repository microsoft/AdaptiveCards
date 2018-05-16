var gulp = require('gulp');
var ts = require('gulp-typescript');
var merge = require('merge2');
var sass = require('gulp-sass');

gulp.task('scripts', function() {
  var tsResult = gulp.src('./src/*.ts')
    .pipe(ts({
        declarationFiles: true,
        noResolve: true,
        noImplicitAny: true,
        target: "es5"
      }));
 
  return merge([
    tsResult.dts.pipe(gulp.dest('dist')),
    tsResult.js.pipe(gulp.dest('dist'))
    ]);
});

gulp.task('sass', function () {
  gulp.src('./css/*.scss')
    .pipe(sass.sync().on('error', sass.logError))
    .pipe(gulp.dest('./css'));
});
 
gulp.task('watch', function () {
  gulp.watch('./css/*.scss', ['sass']);
  gulp.watch('./src/*.ts', ['scripts']);
});