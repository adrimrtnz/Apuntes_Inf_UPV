if test $# -ge 1
then
    echo -e "PID\tPPID\tESTADO\tCOMANDO"
    
    for i in $@
    do
        if test -d /proc/$i/
        then
            pid=$(awk '/^Pid/ {print $2}' /proc/$i/status)
            ppid=$(awk '/^PPid/ {print $2}' /proc/$i/status)
            status=$(awk '/^State/ {print $2}' /proc/$i/status)
            cmd=$(more /proc/$i/cmdline | tr "\000" " ")
            
            echo -e "$pid\t$ppid\t$status\t$cmd"
        fi
    done
    
else
    echo "At least 1 argument was expected"
fi
