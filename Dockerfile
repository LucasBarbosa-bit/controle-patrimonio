FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    pkg-config \
    libgtk-4-dev \
    && apt-get clean

WORKDIR /app
COPY . /app
CMD ["bash"]