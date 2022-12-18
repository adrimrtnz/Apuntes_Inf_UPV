FROM tsr2223/ubuntu-zmq
COPY ./tsr.js tsr.js
RUN mkdir worker
WORKDIR worker
COPY ./workerReq.js myworker.js
# We assume that each worker is linked to the broker
# container.
CMD node myworker $BROKER_HOST $BROKER_PORT
