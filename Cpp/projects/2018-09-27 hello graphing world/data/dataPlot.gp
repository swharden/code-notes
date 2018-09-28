set terminal png size 800,600
set output "dataPlot.png"
set title "Data Plot"
set xlabel "Points"
set ylabel "Values"
plot "data.dat" with linespoints