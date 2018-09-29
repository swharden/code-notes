set terminal png size 800,600
set output "output/data.png"
set title "Data Plot"
set xlabel "Points"
set ylabel "Values"
plot "output/data.dat" with linespoints