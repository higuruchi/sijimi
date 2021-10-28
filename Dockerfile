FROM ubuntu:20.04 AS builder

WORKDIR /home

RUN apt update &&\
    apt install  -y build-essential

COPY ./src/* /home
RUN make sijimi

# ---------------------------

FROM ubuntu:20.04

COPY --from=builder /home/sijimi /app/
COPY --from=builder /home/.sijimirc /app/

WORKDIR /app
RUN groupadd -g 61000 docker &&\
    useradd -g 61000 -l -M -s /bin/bash -u 61000 docker

USER docker

CMD ["/app/sijimi"]