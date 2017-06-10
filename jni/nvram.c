#include <android/log.h>
#include <stdint.h>


#define RLOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "NVRAMD", __VA_ARGS__)

extern void RIL_startEventLoop();

int main(int argc, char **argv) {
    RLOGD("**NVRAM Daemon Started**");

	NVRAM_startReaderThread();


done:
	
	RLOGD("starting sleep loop");
	while (1) {
		sleep(UINT32_MAX);
	}
}
