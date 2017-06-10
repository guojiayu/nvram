#include <android/log.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>



#define RLOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "NVRAM", __VA_ARGS__)
#define RLOGE(...) __android_log_print(ANDROID_LOG_DEBUG, "NVRAM", __VA_ARGS__)

namespace android {

static pthread_t s_tid_dispatch;
static int s_started = 0;

static pthread_mutex_t s_startupMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t s_startupCond = PTHREAD_COND_INITIALIZER;



static void *
readerLoop(void *param) {
	RLOGD("readerLoop start");
    int ret;
	int filedes[2];

    RLOGD("Constructing a new TCP socket...");
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  
    if (-1 == socket_fd) {
        RLOGE("ERROR create socket");
		exit(-1);
    }

    pthread_mutex_lock(&s_startupMutex);

    s_started = 1;
    pthread_cond_broadcast(&s_startupCond);

    pthread_mutex_unlock(&s_startupMutex);
	RLOGD("TCP socket created, fd=%d", socket_fd);


    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8000);

	while(1) {
		if (-1 == connect(socket_fd, (const sockaddr*) &addr, sizeof(addr))) {
			RLOGE("ERROR connect socket, sleep 3");
			sleep(5000);
		} else {
			RLOGD("socket %d connected", socket_fd);
		}
	}

	while(1) {
		RLOGD("readerLoop sleep....");
		sleep(3000);
	}
}


extern "C" void
NVRAM_startReaderThread(void) {
	RLOGD("NVRAM_startEventLoop.. s_started=%d", s_started);
    s_started = 0;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    int result = pthread_create(&s_tid_dispatch, &attr, readerLoop, NULL);
    if (result != 0) {
        RLOGE("Failed to create dispatch thread: %s", strerror(result));
        goto done;
    }

    while (s_started == 0) {
        pthread_cond_wait(&s_startupCond, &s_startupMutex);
    }

done:
    pthread_mutex_unlock(&s_startupMutex);
}


} /* namespace android */
