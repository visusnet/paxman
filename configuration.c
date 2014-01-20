#include "configuration.h"

char install_directory[MAX_DIR_LENGTH];
char map_directory[MAX_DIR_LENGTH];
char img_directory[MAX_DIR_LENGTH];
char default_map[MAX_DIR_LENGTH];
char font_directory[MAX_DIR_LENGTH];

void parseConfig (xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		if ((!xmlStrcmp (cur->name, (const xmlChar *) "install_directory")))
		{
			key = xmlNodeListGetString (doc, cur->xmlChildrenNode, 1);
			strncpy (install_directory, key, sizeof(install_directory));
			xmlFree (key);
		}
		else if ((!xmlStrcmp (cur->name, (const xmlChar *) "map_directory")))
		{
			key = xmlNodeListGetString (doc, cur->xmlChildrenNode, 1);
			strncpy (map_directory, key, sizeof(map_directory));
			xmlFree (key);
		}
		else if ((!xmlStrcmp (cur->name, (const xmlChar *) "img_directory")))
		{
			key = xmlNodeListGetString (doc, cur->xmlChildrenNode, 1);
			strncpy (img_directory, key, sizeof(img_directory));
			xmlFree (key);
		}
		else if ((!xmlStrcmp (cur->name, (const xmlChar *) "font_directory")))
		{
			key = xmlNodeListGetString (doc, cur->xmlChildrenNode, 1);
			strncpy (font_directory, key, sizeof(font_directory));
			xmlFree (key);
		}
		else if ((!xmlStrcmp (cur->name, (const xmlChar *) "default_map")))
		{
			key = xmlNodeListGetString (doc, cur->xmlChildrenNode, 1);
			strncpy (default_map, key, sizeof(default_map));
			xmlFree (key);
		}
	cur = cur->next;
	}
	return;
}

static void parseDoc (char *docname)
{
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile (docname);
fprintf(stderr, "%s\n", docname);
	if (doc == NULL )
	{
		fprintf (stderr, "Error: Document not parsed successfully.\n");
		exit (1);
	}

	cur = xmlDocGetRootElement (doc);

	if (cur == NULL)
	{
		fprintf (stderr, "Error: Empty document\n");
		xmlFreeDoc (doc);
		exit (1);
	}

	if (xmlStrcmp (cur->name, (const xmlChar *) "paxman"))
	{
		fprintf (stderr, "Error: Document of the wrong type, root node != paxman\n");
		xmlFreeDoc (doc);
		exit (1);
	}

	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		if ((!xmlStrcmp (cur->name, (const xmlChar *) "general")))
		{
			parseConfig (doc, cur);
		}
		cur = cur->next;
	}

	xmlFreeDoc (doc);
	return;
}

void dump_config (void)
{
	parseDoc (CONFIG_FILE);
	printf ("Config data:\n============\n");
	printf ("install_directory:\t%s\n", install_directory);
	printf ("map_directory:\t\t%s\n", map_directory);
	printf ("img_directory:\t\t%s\n", img_directory);
	printf ("font_directory:\t\t%s\n", font_directory);
	printf ("default_map:\t\t%s\n", default_map);
	exit (0);
}

void pm_configure (void)
{
	parseDoc (CONFIG_FILE);
}
