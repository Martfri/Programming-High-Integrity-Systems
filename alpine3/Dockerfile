#  ############################################################
#
#                             +
#                ---====D                        @
#       o                    *
#                    *              o
#            |
#           -O-                         =( =         +
#      +     |                   *
#                   ____     ________
#                  /  _/__  / __/ __/    .
#                 _/ // _ \/ _/_\ \             +  .
#        *       /___/_//_/___/___/             |
#                                       -O-         @
#      +                                |
#                      *
#                   ,      .
#           .    `
#       @                +    `~---~~`           *
#
#                   *       .            o         +
#
#
#   Institute of Embedded Systems
#   Zurich University of Applied Sciences
#   8401 Winterthur, Switzerland
#
#
#   File:     Dockerfile
#
#
#   Purpose:  Dockerfile which declares
#             the Alpine Linux docker container
#             with all software packages needed
#             for the benl-AES implemenation
#             development.
#
#
#   Remarks:  - Testing framework: CUnit
#
#
#   Author:   <leiu@zhaw.ch>
#
#
#   Date:     10/2021
#
#  ############################################################

FROM scratch

# install packages from own server
ENV PKGS=/alpine_linux_3-14
ADD ${PKGS}/alpine-minirootfs-3.14.2-x86_64.tar.gz /
ARG PKGS_LST

# intentionally omit at the beginning:
# apk update
# apk upgrade

# Copy packages into container and install them.
COPY ${PKGS}/*.apk /root/
RUN cd /root && \
    apk add --allow-untrusted ${PKGS_LST}

# Remove the apk packages after installation.
RUN cd /root && \
    rm ./*.apk

# Copy flexelint to the container
COPY ${PKGS}/flint /root/
RUN cd /root && \
    mv ./flint /usr/bin/


# add user
ARG user_uid
ARG user_gid
ARG user_name

RUN addgroup -g $user_uid $user_name && \
    adduser -u $user_uid -G $user_name -h /home/$user_name -D $user_name
RUN cp -a /root/. /home/$user_name
RUN mkdir -p /home/$user_name/data


# Copy Script to Container
ENV SCRIPTS_DIR=/home/common/scripts/docker

RUN mkdir -p ${SCRIPTS_DIR}
COPY /scripts/run_make_user_data.sh \
     ${SCRIPTS_DIR}/run_make_user_data.sh
COPY /scripts/run_cmd.sh \
     ${SCRIPTS_DIR}/run_cmd.sh
RUN chmod +x ${SCRIPTS_DIR}/run_make_user_data.sh
RUN chmod +x ${SCRIPTS_DIR}/run_cmd.sh


# Copy vim configuration ...
COPY /config/.vim /home/$user_name/.vim
COPY /config/.vimrc /home/$user_name/.vimrc


# add rights
RUN chown -R $user_name /home/$user_name

CMD ["/bin/bash"]

