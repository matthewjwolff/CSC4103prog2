all :
	make secret
	make choose
	make series
	make kitties

secret : secret.c
	gcc secret.c -o secret -lrt

choose : choose.c
	gcc choose.c -o choose

series : series.c
	gcc series.c -o series

kitties : kitties.c
	gcc kitties.c -o kitties
	echo "DO NOT EXECUTE KITTIES WITH THE TRIGGER ARGUMENT"
