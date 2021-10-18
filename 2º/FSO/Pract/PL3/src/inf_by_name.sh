if test $# -eq 1
then
    n_process=$(ps | grep $1 | wc -l)
    pids=$(ps | grep $1 | awk '{print $1}')
    
    echo -e "Number of $1 process: $n_process\n"
    echo -e "PID\tSTATUS\t\t%MEM"
    
    for i in $pids
    do
        state=$(awk -F: '/^State/ {print $2}' /proc/$i/status)
        mem=$(ps u $i| awk '(NR>1) {print $4}')
        
        echo -e "$i$state\t$mem"
    done
else
    echo "1 argument was expected, $# were given"
fi
