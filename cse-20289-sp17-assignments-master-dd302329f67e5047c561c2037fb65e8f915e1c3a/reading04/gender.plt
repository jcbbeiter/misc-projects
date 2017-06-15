set terminal png
set grid
set key left
set style data histogram
set style histogram cluster gap 1
set style fill solid border
set boxwidth .95 relative
set ylabel "Students"
set xlabel "Class"

plot	'gender.dat' using 2:xtic(1) title "Females",\
	'gender.dat' using 3 title "Males"
