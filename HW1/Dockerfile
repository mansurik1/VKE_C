FROM gcc:latest

RUN apt update && \
    apt full-upgrade -y && \
    apt autoremove -y && \
    apt install git lcov cppcheck clang-format clang-tidy clang-tools python3-pip libc6-dbg cmake libgtest-dev tree less -y

RUN VERSION=1.1.0; \
    curl -sSL "https://github.com/facebook/infer/releases/download/v$VERSION/infer-linux64-v$VERSION.tar.xz" \
    | tar -C /opt -xJ && \
    ln -s "/opt/infer-linux64-v$VERSION/bin/infer" /usr/local/bin/infer

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
