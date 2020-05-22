---
vim: wrap expandtab ft=markdown
layout: blog
comments: true
tags: pkg node.js bundle
title: Bunlde node.js app to standalone executable with pkg
---

## Why we should bundle a node.js app?

There are a plenty of reasons 

  * Protect source code
  * Hide API credentials
  * Avoid npm or node
  * Dictate the node version
  * Remove comments or licenses
  * Improve performance
  * Just show off

## Install the tool `pkg`

```
npm install -g pkg
```

## Create a demo application

Create the project
```
mkdir demo
cd demo
npm init
```
There will be a file `package.json` with
```
"main": "index.js"
```

So we create a file `index.js`

```
const fs = require('fs');
const beautify = filePath => {
	let data = fs.readFileSync(filePath).toString();
	let object = JSON.parse(data);
	return JSON.stringify(object, false, 3);
};

module.exports = {
	beautify
};
```

Create another file `bin.js`
```
const {beautify} = require('.');
const file = process.argv[2];
console.log(beautify(file));
```

Given a test file `test.json`
```json
{"user":{"name":"jochem","email":"jochemstoel@gmail.com"}}
```

We can now execute
```
node bin.js test.json
```

## Bundle the code

Set property `bin` of `package.json` to `bin.js`, then execute

```
pkg .
```

By default, it will create three versions: Linux, Windows, MacOS. We can choose a specific one:

```
pkg -t node12-macos-x64 .
```

The required binaries are automatically downloaded from `https://github.com/zeit/pkg-fetch/releases`.
We can get them manually, for example `uploaded-v2.6-node-v12.2.0-win-x64`, and save it to `v2.6/node-v12.2.0-win-x64`, and then execute

```
PKG_CACHE_PATH=. pkg -t node12.2.0-win-x64 .
```

## Native code

If there are native code for some dependencies, just put these binary files in the same directory of the output.

For example, `node_modules/sqlite3/lib/binding/node-v72-darwin-x64/node_sqlite3.node`.

## Minify

The packaged code is not uglified and minized. We can use package `minify`.

## References

  * [Bundle your Node app to a single executable for Windows, Linux and OsX](https://dev.to/jochemstoel/bundle-your-node-app-to-a-single-executable-for-windows-linux-and-osx-2c89)

