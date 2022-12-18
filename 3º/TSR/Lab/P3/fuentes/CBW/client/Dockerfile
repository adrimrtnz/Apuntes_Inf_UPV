FROM tsr2223/ubuntu-zmq
COPY ./tsr.js tsr.js
RUN mkdir client
WORKDIR client
COPY ./cliente.js myclient.js
# We assume that each client is linked to the broker
# container.
CMD node myclient $BROKER_HOST $BROKER_PORT
