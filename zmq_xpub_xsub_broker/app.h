//
// Created by arkan on 10/7/2017.
//

#ifndef ZMQ_PUB_SUB_BROKER_APP_H
#define ZMQ_PUB_SUB_BROKER_APP_H

void *frontendSocket(void *context);
void *backendSocket(void *context) ;
int bindSocket(void *socket, char *endpoint);
void *newContext() ;
void destroyContext(void *context) ;
void closeSocket(void *socket) ;

#endif //ZMQ_PUB_SUB_BROKER_APP_H
