
AR="alpine_linux_3-14"
STOR="/tmp/${AR}"
RMT_POOL="https://dl-cdn.alpinelinux.org/alpine/v3.14/main/x86_64"

source ./pkgs


function main()
{
    for pkg in ${PKGS[@]}; do
        printf "Downloading ${pkg}.apk\n"
        wget ${RMT_POOL}/${pkg}.apk -O ${STOR}/${pkg}.apk
    done
    cd ${STOR}/..
    tar cvzf ${AR}.tar.gz ${AR}
}


main

