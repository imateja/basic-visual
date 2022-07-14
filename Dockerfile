FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update -y

RUN apt install -y build-essential cmake llvm-12 wget tar gperf bison flex

WORKDIR /usr/src/

COPY . /usr/src

RUN apt install -y '^libxcb.*-dev' libfontconfig1-dev libfreetype6-dev libx11-dev libx11-xcb-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev\
    libxcb-glx0-dev libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-shape0-dev\
    libxcb-randr0-dev libxcb-render-util0-dev libxcb-util-dev libxcb-xinerama0-dev libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev libxcb-xinerama0 libxcb-util1\ 
    libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev dbus-x11 at-spi2-core

WORKDIR /usr/src/Qt

RUN ../qtbase-everywhere-src-6.2.4/configure -nomake examples -nomake tests

RUN cmake --build .

RUN cmake --install .

COPY . /usr/src/basicVisual

WORKDIR /usr/src/basicVisual

RUN chmod +x run.sh

RUN ./run.sh

CMD ["build/basicVisual"]
