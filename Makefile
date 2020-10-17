all: wavein waveout

clean:
	rm wavein waveout

wavein: wavein.c
	gcc wavein.c -o wavein

waveout: waveout.c
	gcc waveout.c -o waveout
