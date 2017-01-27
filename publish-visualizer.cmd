call git checkout master
call git pull --rebase
call npm run build
call git checkout gh-pages
call git reset HEAD .
call git pull --rebase
call move /Y .\visualizer\dist\bundle.js .\dist\bundle.js
call git checkout origin/master -- Visualizer\css
call move /Y .\visualizer\css\* .\css
call git add .
call git commit -m "Update published visualizer"
call git push origin gh-pages


{
"@type": "textBlock",
"text": "Testing this textblock thingie",
"wrap": "true",
"Size": "auto",
"textSize": "normal",
"horizontalAlignment": "left",
"TextWeight": "lighter"
}
    "@type": "AdaptiveCard",
    "body": [
        {
            "@type": "textBlock",
            "text": "Testing this textblock thingie",
            "wrap": "true",
            "Size": "auto",
            "textSize": "normal",
            "horizontalAlignment": "left",
            "TextWeight": "lighter"
        },
        {
            "@type": "TextBlock",
            "text": "This is the second line"
        }
    ]