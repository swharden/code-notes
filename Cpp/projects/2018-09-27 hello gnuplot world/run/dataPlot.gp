# Indicate how to render the plot and where to save it
set terminal png size 400,300
set terminal pngcairo nocrop enhanced
set output "output/data.png"

# Labels
set title "Data Plot"
set xlabel "Points"
set ylabel "Values"

# Grid
set style line 12 lc rgb'#808080' lt 0 lw 1
set grid back ls 12

# Legend
unset key

# Plot the data
plot "output/data.dat" with points pointtype 7 pointsize .5

# Axes limits
set autoscale y