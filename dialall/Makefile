house_dial: house_dial.o house_network.o md5.o public.o 
	gcc $^ -g -o $@ -lpthread

house_dial.o: house_dial.h house_network.h public.h md5.h
house_network.o: house_network.h public.h md5.h
md5.o: md5.h
public.o: public.h

clean:
	rm -rf *.o house_dial

.PHONY: clean
	
