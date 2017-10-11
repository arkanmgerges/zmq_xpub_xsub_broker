#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmockery.h>
#include "../app.c"
#include <pthread.h>
#include <unistd.h>

void *contextDestroyer(void *context) {
    printf("Entering the thread and sleep 5 sec.\n");
    sleep(5);
    printf("Destroy the context from the thread\n");
    destroyContext(context);
}

void *publisher(void *context) {
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_connect (publisher, "tcp://localhost:5010");
    assert_true(rc == 0);
    sleep(1);
    printf("[publisher] Sending the string = HELLO\n");
    rc = s_send(publisher, "HELLO");
    assert_true(rc == 5);
    closeSocket(publisher);
}

void *subscriber(void *context) {
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    int rc = zmq_connect (subscriber, "tcp://localhost:5011");
    assert_true(rc == 0);
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "", 0);
    char *string = s_recv (subscriber);
    closeSocket(subscriber);
    printf("[subscriber] Receiving the string = %s\n", string);
    assert_true(strcmp(string, "HELLO") == 0);
    free(string);
}

void checkZmqBind(void **state) {
    pthread_t worker, pub, sub;

    void *context = newContext();
    assert_true(context != 0);
    printf("Start thread\n");
    pthread_create(&worker, NULL, contextDestroyer, context);
    pthread_create(&pub, NULL, publisher, context);
    pthread_create(&sub, NULL, subscriber, context);

    void *frontend = frontendSocket(context);
    assert_true (bindSocket(frontend, "tcp://*:5010") == 0);

    void *backend = backendSocket(context);
    assert_true (bindSocket(backend, "tcp://*:5011") == 0);

    printf("Start zmq proxy\n");
    //  Start the proxy
    zmq_proxy (frontend, backend, NULL);

    closeSocket(backend);
    closeSocket(frontend);
}

int main(int argc, char* argv[]) {
    const UnitTest tests[] = {
            unit_test(checkZmqBind),
    };

    return run_tests(tests);
}