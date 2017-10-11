# zmq_xpub_xsub_broker
ZeroMQ xpub-xsub broker - zmq v4.2.2

### Introduction
This is a zero mq broker for xpub and xsub, this will let you provide 2 arguments for frontend and backend endpoints, e.g. ./zmq-pub-sub-broker tcp://:5010 tcp://:5011 Where the first one (tcp://:5010) will act as xsub for frontend, this will let clients publishers (zmq_pub) to connect to it and publish messages, while (tcp://:5011) will act as backend with (xpub) that will let clients with type (zmq_sub) to subscribe to the messages sent from the frontend clients (zmq_pub socket type). The broker will send the messages from the frontend connected clients to the backend connected clients.

### Usage
For example to open port 5022 for frontend and 5023 for backend then you can issue the following command:
```sh
docker run -d -p 5022-5023:5022-5023 arkanmgerges/zmq_xpub_xsub_broker:1.0 tcp://:5022 tcp://:5023
```

By default the box will listen to the ports 5001 and 5002, but you need to make them public to your host by the following command:
```sh
docker run -d -p 5001-5002:5001-5002 arkanmgerges/zmq_xpub_xsub_broker:1.0
```
