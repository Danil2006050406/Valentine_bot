FROM ubuntu:22.04

RUN apt update && apt install -y \
    build-essential \
    cmake \
    git \
    libssl-dev \
    zlib1g-dev \
    libcurl4-openssl-dev \
    libboost-all-dev

WORKDIR /app

# ===== УСТАНОВКА TGBOT =====
RUN git clone https://github.com/reo7sp/tgbot-cpp.git
WORKDIR /app/tgbot-cpp
RUN mkdir build && cd build && cmake .. && make && make install

WORKDIR /app

COPY . .

RUN cmake . && make

CMD ["./bot"]
