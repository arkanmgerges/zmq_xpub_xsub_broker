//
// Created by arkan on 10/7/2017.
//

#include "app.h"
#include "zhelpers.h"

void closeSocket(void *socket) {
    zmq_close(socket);
}

void destroyContext(void *context) {
    zmq_ctx_destroy (context);
}

void *newContext() {
    return zmq_ctx_new();
}

void *frontendSocket(void *context) {
    return zmq_socket (context, ZMQ_XSUB);
}

void *backendSocket(void *context) {
    return zmq_socket (context, ZMQ_XPUB);
}

int bindSocket(void *socket, char *endpoint) {
    return zmq_bind (socket, endpoint);
}