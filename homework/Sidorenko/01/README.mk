В задаче требовалость сравнить время выполнения обхода матрицы по стркам и по столбцам.
Значительный выигрыш по времени получается при обходе по строкам.
Это связано с тем, что элементы матрицы, расположенные в одной строке, в памяти локализованы рядом друг с другом.
В связи с этим при


 обходе по строкам процессору приходится значительно реже обращаться к памяти.
