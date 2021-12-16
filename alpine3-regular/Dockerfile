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

# base image, freeze at 3.14, October 2021
FROM alpine:3.14

# update and install packages
RUN apk update           && \
    apk upgrade          && \
    apk add bash         && \
    apk add musl-dev     && \
    apk add libc6-compat && \
    apk add gcc          && \
    apk add make         && \
    apk add cunit-dev    && \
    apk add vim


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

