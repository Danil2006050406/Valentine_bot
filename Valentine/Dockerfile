FROM ubuntu:22.04

RUN apt update && apt install -y \
    build-essential \
    cmake \
    git \
    libssl-dev \
    zlib1g-dev

WORKDIR /app

COPY . .

RUN cmake . && make

CMD ["./bot"]
