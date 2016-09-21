all :
	make secret
	make choose
	make series

secret : secret.c
	gcc secret.c -o secret -lrt

choose : choose.c
	gcc choose.c -o choose

series : series.c
	gcc series.c -o series
