# use cent7 as OS
FROM cent7-base as install
ADD install /tmp/install/questa

# Install Questa
RUN mkdir -p /opt/mentor/questa/2020.4
RUN /tmp/install/questa/batchInstall.sh

FROM cent7-base

# Copy Script to Container
RUN mkdir -p /home/common/scripts/mentor
COPY /scripts/questa2020.4.sh /home/common/scripts/mentor/questa2020.4.sh
RUN chmod +x /home/common/scripts/mentor/questa2020.4.sh

# Copy Docker Script to Contrainer
RUN mkdir -p /home/common/scripts/docker
COPY /scripts/questa2020.4_entrypoint.sh /home/common/scripts/docker/questa2020.4_entrypoint.sh
RUN chmod +x /home/common/scripts/docker/questa2020.4_entrypoint.sh

# Copy Installation
COPY --from=install /opt/mentor/questa/2020.4 /opt/mentor/questa/2020.4

# Startup
ENTRYPOINT ["/home/common/scripts/docker/questa2020.4_entrypoint.sh"]
CMD ["/bin/bash"]
