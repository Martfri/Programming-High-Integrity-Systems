
source ./pkgs

apks=()


function main()
{
    for pkg in ${PKGS[@]}; do
        apks+=(${pkg}.apk)
    done
    echo ${apks[@]}
}


main

