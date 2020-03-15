---
vim: wrap expandtab ft=markdown
layout: blog
tags: android
title: Android From Command Line
---

## Prerequsites

Install java (at least java 8) and android-sdk first.

Add the following `PATH` in your `.bashrc` or `.zshrc` or whatever

```
export ANDROID_HOME=/path/to/your/android
export PATH=$PATH:$ANDROID_HOME/sdk/tools/:$ANDROID_HOME/sdk/platform-tools
```

`ANDROID_HOME` is needed for `gradle`, and related command lines are in the `sdk/tools` and `sdk/platform-tools`.

## Build app from command line

There is a `gradlew` script in every android project, so we can just use the following command lines

```
./gradlew tasks           # list available tasks
./gradlew assembleDebug   # initiate a debug build
./gradlew installDebug    # build and install on a running emmulator or connected devices
```

To build a release APK, we should sign it with our private key. Reference [sign your app from the command line](https://developer.android.com/studio/build/building-cmdline#sign_cmdline) for details.


## Deploy app to an emulator

Then try the following commands

```
emulator -list-avds
emulator -avd your_selected_avd_name
adb install project_dir/module_name/build/outputs/apk/you_app.apk
```

## Deploy app to a device

```
adb devices -l  # list all devices
adb -d -s your-selected-device-name \
	install -r -t project_dir/module_name/build/outputs/apk/you_app.apk
```

## Test app

```
./gradlew connectedAndroidTest
```

## Copy file from devices

```
adb -s your-device-name -d shell "run-as com.package.name \
	cat /data/data/com.package.name/path/to/file.txt" >file.txt
```

Or we can write a shell script as 

```
# adb_pull device-name com.xxx.xxx databases/file.db
adb_pull() {
	adb -s $1 -d shell "run-as $2 cat /data/data/$2/$3" >`basename $3`
}
```

## References

  * [Build your app from the command line](https://developer.android.com/studio/build/building-cmdline)
  * [How to build and apk from command line](https://medium.com/@authmane512/how-to-build-an-apk-from-command-line-without-ide-7260e1e22676)
  * [Test from the command line](https://developer.android.com/studio/test/command-line)

