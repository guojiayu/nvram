#include <android/log.h>


#define LOG_TAG "NVRAM"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

int main() {
	LOGD("nvram service running");
	return 0;
}