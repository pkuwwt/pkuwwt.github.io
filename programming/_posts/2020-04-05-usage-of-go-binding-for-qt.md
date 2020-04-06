---
vim: wrap expandtab ft=markdown
layout: blog
comments: true
tags: go qt
title: Usage of Go binding for Qt
---

The portability and deployment is important for development, while [Go binding for Qt](https://github.com/therecipe/qt) is the perfect combination of both.

## Install

Just refer to [therecipe/qt Installation](https://github.com/therecipe/qt#installation).

The essential steps are
```
export GO111MODULE=off
go get -v github.com/therecipe/qt/cmd/...
$(go env GOPATH)/bin/qtsetup -test=false
```

Before the installation, make sure that there are following directories in `$(go env GOPATH)/src/golang.org/x`: `mod`, `sys`, `text`, `tools`, `xerrors`, which can be installed with the following commands (for Mac or Linux):

```bash
mkdir -p $(go env GOPATH)/src/golang.org/x
cd $(go env GOPATH)/src/golang.org/x
git clone https://github.com/golang/mod.git
git clone https://github.com/golang/sys.git
git clone https://github.com/golang/text.git
git clone https://github.com/golang/tools.git
git clone https://github.com/golang/xerrors.git
```

## First example

There are examples in [therecipe/examples](https://github.com/therecipe/examples).

Here we give a `hello world` program `hello.go` for go-qt:

```go
package main

import (
	"os"
	"github.com/therecipe/qt/widgets"
)

func main() {
	app := widgets.NewQApplication(len(os.Args), os.Args)
	window := widgets.NewQMainWindow(nil, 0)
	button := widgets.NewQPushButton2("click", nil)
	button.ConnectClicked(func(bool){
		widgets.QMessageBox_Information(nil, "title", "Hello World", widgets.QMessageBox__Ok, widgets.QMessageBox__Ok)
	})
	window.SetCentralWidget(button)
	window.Show()
	app.Exec()
}
```

We can run it with
```
go run hello.go
```
or compile it with
```
go build hello.go
```

Now we get an executable `hello` as large as 133MB. Holy shit! However, it is a reasonable file size with all those Qt libraries compiled in statically.


