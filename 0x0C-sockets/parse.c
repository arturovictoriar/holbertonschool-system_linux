#include "crud.h"

/**
 * parse_req - parse the request
 * @req: request
 * Return: request data parsed
 */
http_msg_t parse_req(char *req)
{
	char *save_req = NULL, *cmplt_path = NULL, BODY_SEPARATOR[] = "\xD\xA\xD\xA";
	http_msg_t req_data;
	int i = 0, is_trim = 0, no_header = 0;

	memset(&req_data, '\0', sizeof(http_msg_t));
	save_req = req;
	/*Get the method, path, query and version*/
	req_data.method = strtok_r(req, " ", &save_req);
	cmplt_path = strtok_r(NULL, " ", &save_req);
	req_data.path = strtok(cmplt_path, "?");
	req_data.query = strtok(NULL, " ");
	req_data.version = strtok_r(NULL, "\xD", &save_req);
	if (save_req[0] == '\xA' && save_req[1] == '\xD' && save_req[2] == '\xA')
		no_header = 1;
	/*Get the headers and body data*/
	for (i = 0; save_req && save_req[i] != '\0'; i++)
	{
		if (is_trim == 0 && no_header == 0 &&
				save_req[i] != '\xD' && save_req[i] != '\xA')
		{
			/*Get the headers*/
			req_data.headers = &save_req[i];
			is_trim = 1;
		}
		if (save_req[i] == '\xD' && !strncmp(&save_req[i], BODY_SEPARATOR, 4))
		{
			save_req[i] = '\0';
			/*Get the body*/
			if (save_req[i + 4] != '\0')
				req_data.body = &save_req[i + 4];
			break;
		}
	}
	return (req_data);
}

/**
 * parse_content_length - look for the Content-length in headers
 * @cl: content length store
 * @req_data: http message
 * Return: nothing
 */
void parse_content_length(char **cl, http_msg_t *req_data)
{
	char *header = NULL, *key_header = NULL, DELIM[] = "\xD\xA";
	char *save_header = NULL, *val_header = NULL, *content_len = NULL;

	save_header = req_data->headers;
	header = strtok_r(req_data->headers, DELIM, &save_header);
	while (header)
	{
		key_header = strtok(header, ":");
		val_header = strtok(NULL, ":");
		if (!strcmp(key_header, "Content-Length"))
		{
			content_len = &val_header[1];
			break;
		}
		header = strtok_r(NULL, DELIM, &save_header);
	}
	/*Copy the content length in entry variables*/
	*cl = content_len;
}

/**
 * parse_title_description - Look for title and description in body
 * @t: title store
 * @d: description store
 * @req_data: http message
 * Return: nothing
 */
void parse_title_description(char **t, char **d, http_msg_t *req_data)
{
	char *pair = NULL, *save_pair = NULL, *key = NULL, *title = NULL;
	char *description = NULL, *value = NULL;

	save_pair = req_data->body;
	pair = strtok_r(req_data->body, "&", &save_pair);
	while (pair)
	{
		key = strtok(pair, "=");
		value = strtok(NULL, "=");
		if (!strcmp(key, "title"))
			title = value;
		else if (!strcmp(key, "description"))
			description = value;
		if (title && description)
			break;
		pair = strtok_r(NULL, "&", &save_pair);
	}
	/*Copy the title and description in entry variables*/
	*t = title;
	*d = description;
}

/**
 * parse_query_id - Look for an id in the query
 * @i: id store
 * @req_data: http message
 * Return: nothing
 */
void parse_query_id(char **i, http_msg_t *req_data)
{
	char *pair = NULL, *save_query = NULL, *key = NULL, *value = NULL;
	char *id = NULL;

	save_query = req_data->query;
	if (!save_query)
		return;
	pair = strtok_r(req_data->query, "&", &save_query);
	while (pair)
	{
		/*Split the key and value*/
		key = strtok(pair, "=");
		value = strtok(NULL, "=");
		if (!strcmp(key, "id"))
		{
			id = value;
			break;
		}
		pair = strtok_r(NULL, "&", &save_query);
	}

	*i = id;
}
