# base image
FROM centos:7

# update and install dependencies
RUN yum install -y epel-release && yum update -y && yum install -y \
gtk2{,.i686} unixODBC{,.i686} libxml2{,.i686} libXt.i686 libXtst.i686 libXdmcp.i686 \
xorg-x11-fonts dejavu-{sans,sans-mono,serif}-fonts 'liberation-*-fonts' \
xorg-x11-xauth xterm openmotif firefox nano vim sudo \
&& yum clean all && rm -rf /var/cache/yum \
&& ln -sf usr/lib64/libXm.so.4.0.3 /usr/lib64/libXm.so.3 && ldconfig

RUN yum update -y
RUN yum groupinstall "Development Tools" -y

# add user
ARG user_uid
ARG user_gid
ARG user_name
RUN     groupadd -g $user_uid $user_name && \
        adduser -u $user_uid -g $user_gid -N -M -d /home/$user_name $user_name
RUN cp -a /root/. /home/$user_name
RUN mkdir -p /home/$user_name/data

# Copy Script to Container
RUN mkdir -p /home/common/scripts/docker
COPY /scripts/run_make_user_data.sh /home/common/scripts/docker/run_make_user_data.sh
COPY /scripts/run_cmd.sh /home/common/scripts/docker/run_cmd.sh
RUN chmod +x /home/common/scripts/docker/run_make_user_data.sh
RUN chmod +x /home/common/scripts/docker/run_cmd.sh

# add rights
RUN chown -R $user_name /home/$user_name
