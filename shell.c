#include "shell.h"

void shell_help (char **argv)
{
	printf ("Usage: %s [options]|[map]\n", argv[0]);
	printf ("Options:\n========\n");
	printf ("  --help			Display this information\n");
	printf ("  --maps			Display all available maps\n");
	printf ("  --config			Display configuration data\n");
	exit (0);
}

void shell_maps ()
{
	DIR *dir;
	struct dirent *dp;
	FILE *fp;
	char c;
	char file[1024];
	char tmp_map[256];
	int is_map;

	extern char map_directory[256];

	if ((dir = opendir (map_directory)) == NULL)
	{
		printf ("Error. Cannot open default map directory (%s)", map_directory);
		exit (1);
	}

	printf ("Available maps:\n===============\n");
	while ((dp = readdir (dir)) != NULL)
	{
		if ((*dp).d_name[0] == '.')
			continue;

		snprintf (file, sizeof(file), "%s%s", map_directory, (*dp).d_name);
		if ((fp = fopen (file, "r")) == NULL)
		{
			printf ("Error. Loading map file.");
			exit (1);
		}

		while ((c = fgetc (fp)) != EOF)
		{
			if (c == 'w' || c == 'p' || c == 'c' || c == 'g' || c == '\n')
			{
				is_map = 1;
			}
			else
			{
				is_map = 0;
				break;
			}
		}
		if (is_map == 1)
		{
			printf ("%s\n", (*dp).d_name);
		}
	}

	if (closedir (dir) == -1)
	{
		printf ("Error. Cannot close default map directory (%s)", map_directory);
	}
	exit (0);
}
