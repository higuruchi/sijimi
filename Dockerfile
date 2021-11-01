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

# WORKDIR /home/docker
RUN groupadd -g 1000 docker &&\
    useradd -m -u 1000 -g 1000  -s /app/sijimi docker

USER docker

CMD ["/app/sijimi"]