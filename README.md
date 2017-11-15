# ZeroMQ XPUB XSUB Proxy Written in C Language
ZeroMQ xpub-xsub broker - zmq v4.2.2

### Introduction
This is a zero mq broker for xpub and xsub, this will let you provide 2 arguments for frontend and backend endpoints, e.g. ./zmq-pub-sub-broker tcp://\*:5010 tcp://\*:5011 Where the first one (tcp://\*:5010) will act as xsub for frontend, this will let clients publishers (zmq_pub) to connect to it and publish messages, while (tcp://\*:5011) will act as backend with (xpub) that will let clients with type (zmq_sub) to subscribe to the messages sent from the frontend clients (zmq_pub socket type). The broker will send the messages from the frontend connected clients to the backend connected clients.

### Usage
For example to open port 5022 for frontend and 5023 for backend then you can issue the following command:
```sh
docker run -d -p 5022-5023:5022-5023 arkanmgerges/zmq_xpub_xsub_broker tcp://*:5022 tcp://*:5023
```

By default the box will listen to the ports 5001 and 5002, but you need to make them public to your host by the following command:
```sh
docker run -d -p 5001-5002:5001-5002 arkanmgerges/zmq_xpub_xsub_broker
```


### Connect from Other Languages
After you run the box as shown in 'Usage', you can publish and subscribe, the following example is written in PHP, it shows how to connect
to the box and publish a message from a thread, and let the other thread to subscribe to all messages, in this way the subscriber will 
receive the messages published from other threads, or other apps that are publishing messages to the box (zmq_xpub_xsub_broker):

```php
<?php
/**
 * Created by Arkan M. Gerges
 */

$context = new ZMQContext();

// Connect the publisher
$pid = pcntl_fork();
    if ($pid == -1) {
        exit("Error forking...\n");
    } elseif ($pid == 0) {
        $endpoint = "tcp://192.168.99.100:5001";
        $publisher = $context->getSocket(ZMQ::SOCKET_PUB);
        $publisher->connect($endpoint);
        sleep(1);
        $publisher->send("[publisher] Hello From PHP!");
        $publisher->disconnect($endpoint);
        exit();
    }

// Connect the subscriber
$pid = pcntl_fork();
    if ($pid == -1) {
        exit("Error forking...\n");
    } elseif ($pid == 0) {
        $endpoint = "tcp://192.168.99.100:5002";
        $subscriber = $context->getSocket(ZMQ::SOCKET_SUB);
        $subscriber->connect($endpoint);
        // Subscribe to all messages
        $subscriber->setSockOpt(ZMQ::SOCKOPT_SUBSCRIBE, "");
        $string = $subscriber->recv();
        printf("[subscriber] message received: %s", $string);
        $subscriber->disconnect($endpoint);
        exit();
    }

// This while loop holds the parent process until all the child threads
// are complete - at which point the script continues to execute.
while(pcntl_waitpid(0, $status) != -1);
```
