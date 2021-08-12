# use cent7 with questa
FROM questa:2020.4 as install
ADD Quartus-20.1.1.720-linux.tar /tmp/install/quartus

# Install Quartus
RUN mkdir -p /opt/intel/intelFPGA/20.1
RUN /tmp/install/quartus/setup.sh --mode unattended --accept_eula 1 --installdir /opt/intel/intelFPGA/20.1

# Install Device Driver
ADD Quartus-20.1.1.720-devices-3.tar /tmp/install/device
RUN /tmp/install/device/dev3_setup.sh --mode unattended --accept_eula 1 --installdir /opt/intel/intelFPGA/20.1

# Install HLS
ADD HLSProSetup-21.2.0.72-linux.run /tmp/install/HLSProSetup-21.2.0.72-linux.run
RUN chmod +x /tmp/install/HLSProSetup-21.2.0.72-linux.run
RUN /tmp/install/HLSProSetup-21.2.0.72-linux.run --mode unattended --accept_eula 1 --installdir /opt/intel/intelFPGA/20.1

# set user
FROM questa:2020.4

# Copy Script to Container
RUN mkdir -p /home/common/scripts/intel
RUN mkdir -p /home/common/scripts/docker
COPY /scripts/quartus20.1_HLS.sh /home/common/scripts/intel/quartus20.1_HLS.sh
COPY /scripts/quartus20.1_HLS_entrypoint.sh /home/common/scripts/docker/quartus20.1_HLS_entrypoint.sh
RUN chmod +x /home/common/scripts/intel/quartus20.1_HLS.sh
RUN chmod +x /home/common/scripts/docker/quartus20.1_HLS_entrypoint.sh

# Copy Installation
COPY --from=install /opt/intel/intelFPGA/20.1 /opt/intel/intelFPGA/20.1

# Startup
ENTRYPOINT ["/home/common/scripts/docker/quartus20.1_HLS_entrypoint.sh"]
CMD ["/bin/bash"]
