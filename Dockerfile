FROM gcc:latest

RUN apt update && \
    apt full-upgrade -y && \
    apt autoremove -y && \
    apt install git lcov cppcheck clang-tidy python3-pip libc6-dbg cmake libgtest-dev tree -y

RUN pip install cpplint

WORKDIR /valgrind
RUN wget https://sourceware.org/pub/valgrind/valgrind-3.18.1.tar.bz2 && \
    tar xfv valgrind-3.18.1.tar.bz2 && \
    cd valgrind-3.18.1 && \
    ./autogen.sh && \
    ./configure && \
    make && \
    make install
WORKDIR /
RUN rm -rf valgrind

WORKDIR HW1
COPY *.c Dockerfile CMakeLists.txt .gitignore ./
COPY flight_lib ./flight_lib/
COPY tests ./tests/
COPY .git ./.git/
WORKDIR /
