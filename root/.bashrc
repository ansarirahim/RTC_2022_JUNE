# ~/.bashrc: executed by bash(1) for non-login shells.
export http_proxy="http://Abdulr:Bushras%401@172.16.4.21:3128"
export https_proxy="https://Abdulr:Bushras%401@172.16.4.21:3128"
export ftp_proxy="ftp://Abdulr:Bushras%401@172.16.4.21:3128"
# Note: PS1 and umask are already set in /etc/profile. You should not
# need this unless you want different defaults for root.
# PS1='${debian_chroot:+($debian_chroot)}\h:\w\$ '
# umask 022

# You may uncomment the following lines if you want `ls' to be colorized:
# export LS_OPTIONS='--color=auto'
# eval "`dircolors`"
# alias ls='ls $LS_OPTIONS'
# alias ll='ls $LS_OPTIONS -l'
# alias l='ls $LS_OPTIONS -lA'
#
# Some more alias to avoid making mistakes:
# alias rm='rm -i'
# alias cp='cp -i'
# alias mv='mv -i'
command_not_found_handle () {
    printf "NACK\n\r"
    return 127
}
