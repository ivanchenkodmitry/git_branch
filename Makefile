PREFIX=/usr/bin
OUT=git_br
default:
	gcc git_branch.c -o ${OUT} -std=c99
	
clean:
	rm ${OUT}
	
install:
	sudo cp ${OUT} ${PREFIX}
