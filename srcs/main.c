#include "fdf.h"

#include <stdio.h>

int	main(int argc, char **argv)
{
	fdf	*data;
	char	*file_name;

	int	dummy = argc; //////////

	data = (fdf*)malloc(sizeof(fdf));
	file_name = argv[1];
	read_file(file_name, data);

	printf("main test: %s %p\n", file_name, data);
	return dummy; /////////////////////
}
