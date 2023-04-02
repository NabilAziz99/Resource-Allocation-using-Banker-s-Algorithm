	
clean:
	rm -f *.o banker

run:
	g++ banker.cpp -o banker
	./banker s1.txt

