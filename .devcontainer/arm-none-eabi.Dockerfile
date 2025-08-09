# syntax=docker/dockerfile:1

# ------------------------------------------------------------------------------
# Base image for building the firmware
# ------------------------------------------------------------------------------
FROM debian:bookworm AS arm_none_eabi-base

# -------------------------------------------------------------------
# Configuration and Environment Variables
# -------------------------------------------------------------------
ARG ARM_TOOLCHAIN_VERSION=13.2.rel1
ARG ARM_DL_LINK=https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/${ARM_TOOLCHAIN_VERSION}/binrel/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz

ENV ARM_TOOLCHAIN_DIR=/opt/gnu_arm/${ARM_TOOLCHAIN_VERSION}
ENV PATH=${ARM_TOOLCHAIN_DIR}/bin:$PATH

# -------------------------------------------------------------------
# Base Tool Install
# -------------------------------------------------------------------
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    wget \
    bzip2 \
    ca-certificates \
    cmake \
    ninja-build \
    python3 \
    python3-pip \
    python3-venv \
    pipenv \
    doxygen \
    zip \
    jq \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# -------------------------------------------------------------------
# Install ARM Toolchain
# -------------------------------------------------------------------
RUN mkdir -p ${ARM_TOOLCHAIN_DIR} /tmp/arm-toolchain \
    && wget -qO- ${ARM_DL_LINK} | tar -xJ -C /tmp/arm-toolchain --strip-components=1 \
    && mv /tmp/arm-toolchain/* ${ARM_TOOLCHAIN_DIR} \
    && rm -rf /tmp/arm-toolchain

# -------------------------------------------------------------------
# Install Pipenv
# -------------------------------------------------------------------
# RUN python3 -m pip install pipenv==2023.7.9 --break-system-packages

# ------------------------------------------------------------------------------
# Dev image for devcontainer environment
# ------------------------------------------------------------------------------
FROM arm_none_eabi-base AS arm_none_eabi-dev

# -------------------------------------------------------------------
# Install Dev Tools and Debugging Utilities
# -------------------------------------------------------------------
RUN apt-get update && apt-get install -y --no-install-recommends \
    udev \
    tree \
    ssh \
    curl \
    libusb-1.0-0 \
    bash-completion \
    openocd \
    libnewlib-dev \
    libncurses5 \
    libncursesw5 \
    libncurses5-dev \
    libncursesw5-dev \
    libusb-1.0-0-dev \
    libftdi-dev \
    libhidapi-dev \
    libusb-dev \
    usbutils \
    build-essential \
    libssl-dev \
    zlib1g-dev \
    libbz2-dev \
    libreadline-dev \
    libsqlite3-dev \
    xz-utils \
    tk-dev \
    libxml2-dev \
    libxmlsec1-dev \
    libffi-dev \
    liblzma-dev \
    libglib2.0-0 \
    locales \
    sudo

# -------------------------------------------------------------------
# Locale Setup
# -------------------------------------------------------------------
RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
    locale-gen

ENV LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    LC_ALL=en_US.UTF-8

# -------------------------------------------------------------------
# Add Dev User
# -------------------------------------------------------------------
ARG USERNAME=dev
ARG WORKSPACE_NAME=workspace

RUN useradd -m $USERNAME \
    && echo "$USERNAME ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && usermod -a -G dialout,plugdev $USERNAME

USER $USERNAME
ENV SHELL=/bin/bash

# -------------------------------------------------------------------
# Install Pyenv and Python 3.8.18 (required by gdb)
# -------------------------------------------------------------------
ENV PYENV_ROOT=/home/$USERNAME/.pyenv
ENV PATH=$PYENV_ROOT/bin:$PATH

RUN curl https://pyenv.run | bash && \
    bash -c "source ~/.bashrc && pyenv install 3.8.18"

USER root
RUN mkdir -p /usr/local/bld-tools && \
    ln -s $PYENV_ROOT/versions/3.8.18 /usr/local/bld-tools/bld-tools-virtual-env

# -------------------------------------------------------------------
# JLink Installation
# -------------------------------------------------------------------
# Where to find the JLink file ?
ARG JLINK_LINK="https://www.segger.com/downloads/jlink/JLink_Linux_V824_x86_64.deb"
RUN curl \
    -L ${JLINK_LINK} \
    -d "accept_license_agreement=accepted" \
    -o /tmp/jlink.deb

# We don't install the JLink software right away because it will fail
# to update the udev rules for some reason:
# 7.676 Unpacking jlink (8.24.0) ...
# 9.131 Setting up jlink (8.24.0) ...
# 9.149 Updating udev rules via udevadm...
# 9.152 Failed to reload udevadm rules, retrying...
# 9.160 Failed to send reload request: No such file or directory
# 9.160 Error: Failed to update udevadm rules.
#
# Add an alias to the bashrc to install it manually later
RUN echo "alias jlink-install='sudo apt install -y /tmp/jlink.deb'" >> /home/$USERNAME/.bashrc

USER $USERNAME
CMD ["/bin/bash"]
