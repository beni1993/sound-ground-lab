all: wavein waveout change_lr invert

clean:
	rm -f wavein waveout change_lr invert

wavein: wavein.c
	gcc wavein.c -o wavein

waveout: waveout.c
	gcc waveout.c -o waveout

change_lr: change_lr.c
	gcc change_lr.c -o change_lr

invert: invert.c
	gcc invert.c -o invert
