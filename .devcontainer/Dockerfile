FROM ubuntu

# Update and install necessary packages
RUN apt update
RUN apt install -y cmake gdb mingw-w64

# For HomeBrew
RUN apt-get install -y build-essential procps curl file git

# Install HomeBrew
RUN mkdir /home/linuxbrew && \
  git clone https://github.com/Homebrew/brew /home/linuxbrew/.linuxbrew/Homebrew && \
  mkdir /home/linuxbrew/.linuxbrew/bin && \
  ln -s /home/linuxbrew/.linuxbrew/Homebrew/bin/brew /home/linuxbrew/.linuxbrew/bin

# Set environment variables
ENV PATH="/home/linuxbrew/.linuxbrew/bin:${PATH}"

RUN brew install wappon28dev/tap/cook-zip
