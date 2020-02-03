IF EXIST "dist\spec-generator-script.0.5.0.0.min.js" (
	ECHO Spec generator already built...
) ELSE (
	ECHO Building spec generator...
	cd ..
	npm install
	npx lerna bootstrap
	cd spec-generator
	npm run release
)

IF EXIST "dist\spec-generator-script.0.5.0.0.min.js" (
	node dist\spec-generator-script.0.5.0.0.min.js
) ELSE (
	ECHO Script wasn't found
	EXIT 1
)
