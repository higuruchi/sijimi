FROM ubuntu:20.04 AS builder

WORKDIR /home

RUN apt update &&\
    apt install  -y build-essential vim
COPY ./src /home
RUN make

# ---------------------------

FROM ubuntu:20.04
COPY --from=builder /home/sijimi /app/main
WORKDIR /app

CMD ["/app/main"]