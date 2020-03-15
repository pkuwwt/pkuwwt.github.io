---
vim: wrap expandtab ft=markdown
layout: blog
tags: android
title: Android From Command Line
---

## Build app from command line

There is a `gradlew` script in every android project, so we can just use the following command lines

```
./gradlew tasks           # list available tasks
./gradlew assembleDebug   # initiate a debug build
./gradlew installDebug    # build and install on a running emmulator or connected devices
```

To build a release APK, we should sign it with our private key. Reference [sign your app from the command line](https://developer.android.com/studio/build/building-cmdline#sign_cmdline) for details.


## Deploy app to an emulator

Add the following `PATH` in your `.bashrc` or `.zshrc` or whatever

```
export ANDROID_SDK=/path/to/your/android/sdk
export PATH=$PATH:$ANDROID_SDK/emulator:$ANDROID_SDK/platform-tools
```

```
emulator -list-avds
emulator -avd your_selected_avd_name
adb install project_dir/module_name/build/outputs/apk/you_app.apk
```

## Deploy app to a device

```
adb devices -l  # list all devices
adb -d -s your-selected-device-name install -r -t project_dir/module_name/build/outputs/apk/you_app.apk
```

## Test app

## Copy file from devices

```
adb -s your-device-name -d shell "run-as com.package.name cat /data/data/com.package.name/path/to/file.txt" >file.txt
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

