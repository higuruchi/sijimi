FROM ubuntu:20.04 AS builder

WORKDIR /home

RUN apt update &&\
    apt install  -y build-essential

# COPY ./src /home
# RUN make run

RUN groupadd -g 61000 docker &&\
    useradd -g 61000 -l -M -s /bin/bash -u 61000 docker

USER docker


# ---------------------------

# FROM ubuntu:20.04
# COPY --from=builder /home/sijimi /app/main
# WORKDIR /app

# CMD ["/app/main"]