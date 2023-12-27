# Archivo: grafica_tiempo.gp

# Configuración del terminal y la salida
set terminal pngcairo enhanced font 'arial,10' size 800, 600
set output 'grafica_tiempo.png'

# Configuración del título y las etiquetas de los ejes
set title 'Tiempo de ejecución en función del número de muestras por pixel'
set xlabel 'Número de muestras por pixel'
set ylabel 'Tiempo de ejecución (ms)'

# Configuración de la leyenda
set key right top

# Estilo de la línea y los puntos
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5

# Leer datos desde el archivo tiempos.txt
plot 'tiempos.txt' using 1:2 with linespoints ls 1 title 'Tiempo de ejecución'
