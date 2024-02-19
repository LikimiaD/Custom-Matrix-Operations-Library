FROM ubuntu

RUN apt-get update && apt install -y gcc g++ check make lcov

WORKDIR /home/user

COPY . .

RUN chmod +x /home/user/scripts/docker.sh

ENTRYPOINT [ "bash", "/home/user/scripts/docker.sh"]
