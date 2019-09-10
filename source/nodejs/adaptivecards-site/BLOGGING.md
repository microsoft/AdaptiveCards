# Authoring Blog Content

Writing a blog post is as the most enjoyable thing you'll do today! 💯

## Getting Started

A blog post is nothing more than a file authored in the markdown syntax you already know and love.

1. Create a new markdown file in `./pages/_posts/<year>` (e.g., `My-Cool-Blog-Post.md`)
2. Add post metadata to the top of the file (described below)
3. You can use all the normal markdown features you expect: images, hyperlinks, code snippets using ```, etc
4. To include images or other assets make a folder with the same name as your markdown file (e.g., `./pages/_posts/<year>/My-Cool-Blog-Post/`)
5. Add any images into the folder
6. Reference them in your markdown file using standard markdown image syntax (e.g., `![Image description](My-Cool-Blog-Post/myimage.png)`
7. In VS Code, click the "Open Preview to the Side" button to preview your post (`Ctrl-K, V`)
8. When you feel good, commit it and open a PR!

## Post Metadata

The only other content you need in the markdown file is called "front matter" and is YAML content that describes the post.

```yaml
---
title: <REQUIRED> The title of your post, should be short and sweet
subtitle: <REQUIRED> A slightly longer subtitle that describes the post content
date: <REQUIRED> The post date YYYY-MM-DD
github_username: <REQUIRED> Your GitHub username
featured_image: <OPTIONAL> A "hero" image that aids the post visually (approx dimensions 294x172)
twitter: <OPTIONAL> Your twitter handle
---
```

**Example metadata:**

```yaml
---
title: 🎉 Announcing Adaptive Cards 1.1
subtitle: All new drag-drop designer, a Media element, and more
date: 2018-10-12
featured_image: designer.png
github_username: matthidinger
twitter: matthidinger
---
```

### Check the post on the website

Next you'll want to see how your post looks on the actual website. As soon as you open a PR with your post, the build server will publish it to:

> `https://adaptivecardsci.z5.web.core.windows.net/pr/<PR_NUMBER>/blog`

Check it out, see how it looks, and send that URL to folks for feedback! When it's all good, merge it to master and it'll be live on `https://adaptivecards.io/blog`!

## Helpful VS Code extensions

- **[Paste Image](https://marketplace.visualstudio.com/items?itemName=mushan.vscode-paste-image)** lets your paste an image from your clipboard into your current VS Code project. This is so much nicer for quickly snipping screenshots, etc. 

  - **Usage:** `Ctrl+Alt+V` with an image in clipboard, enter filename

- **[Markdown paste](https://marketplace.visualstudio.com/items?itemName=telesoho.vscode-markdown-paste-image)** is great if you need to paste HTML content as markdown. 

	- **Usage:** `Ctrl+Alt+V` with HTML content in clipboard will convert it to markdown

