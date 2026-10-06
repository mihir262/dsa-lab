# Compare time complexities of bubble sort vs selection sort
# Usage: gnuplot plot_timings.gp

set terminal pngcairo size 1000,700 enhanced font "Arial,12"
set output "timings_plot.png"

set title "Time Complexity Comparison: Bubble Sort vs Selection Sort"
set xlabel "Input size (n)"
set ylabel "Time (seconds)"
set grid
set key left top

# Style
set style line 1 lc rgb "#1f77b4" lt 1 lw 2 pt 7 ps 1.2
set style line 2 lc rgb "#d62728" lt 1 lw 2 pt 5 ps 1.2

plot "timings.dat" using 1:2 with linespoints ls 1 title "Bubble Sort", \
     "timings.dat" using 1:3 with linespoints ls 2 title "Selection Sort"

set output
print "Wrote timings_plot.png"
