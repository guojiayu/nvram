
REM adb remount
adb push libs\x86_64\libnvram.so system/lib64
adb push libs\x86_64\nvramd data/local
adb shell chmod +x data/local/nvramd
adb shell data/local/nvramd