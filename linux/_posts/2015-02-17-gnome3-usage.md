---
layout: blog
comments: true
title: GNOME 3 Usage
---

## Shortcut

From [[https://wiki.gnome.org/Design/OS/KeyboardShortcuts]]

  * App List: `Alt-F1`
  * Command: `Alt-F2`
  * Switch Application: `Alt-Tab`
  * Switch between same kind of Application: `Alt-\``
  * System Tray: `Super-M`
  * Pre/Next Screen: `Ctrl-Alt-UpArrow/DownArrow`

## Shrink height of the title bar

Edit the value of `title_vertical_pad` in `/usr/share/themes/Adwaita/metacity-1/metacity-theme-3.xml`

  sudo sed -i "/title_vertical_pad/s/value=\"[0-9]\{1,2\}\"/value=\"0\"/g" /usr/share/themes/Adwaita/metacity-1/metacity-theme-3.xml

Then open command dialog with `Alt-F2`, and run `r` to refresh GNOME shell.

