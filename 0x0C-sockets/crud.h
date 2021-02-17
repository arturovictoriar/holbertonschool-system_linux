#ifndef API_H
#define API_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define NUM_CLNTS 16
#define BUFFER_SIZE 8192
#define CRLF "\xD\xA"
#define SP "\x20\x9"

#define JSON_FORMAT "{\"id\":%lu,\"title\":\"%s\",\"description\":\"%s\"}"
#define RES_200_FORMAT "HTTP/1.1 200 OK" CRLF \
			"Content-Length: %d" CRLF \
			"Content-Type: application/json" CRLF \
			CRLF \
			"%s"
#define RES_201_FORMAT "HTTP/1.1 201 Created" CRLF \
			"Content-Length: %d" CRLF \
			"Content-Type: application/json" CRLF \
			CRLF \
			JSON_FORMAT
#define RES_204_FORMAT "HTTP/1.1 204 No Content" CRLF \
			CRLF
#define RES_404_FORMAT "HTTP/1.1 404 Not Found" CRLF \
			CRLF
#define RES_411_FORMAT "HTTP/1.1 411 Length Required" CRLF \
			CRLF
#define RES_422_FORMAT "HTTP/1.1 422 Unprocessable Entity" CRLF \
			CRLF

#define OK 200
#define CREATED 201
#define NO_CONTENT 204
#define NOT_FOUND 404
#define LENGTH_REQUIRED 411
#define UNPRO_ENTITY 422

/**
 * enum Meths - All methods availables
 * @POST: post method id
 * @GET: get method id
 * @DELETE: delete method id
 *
 * Description: Structure for storing the methods id
 */
typedef enum Meths
{
	POST,
	GET,
	DELETE
} Meth;

/**
 * struct todo_s - store one todo
 * @title: todo's title
 * @description: todo's description
 * @id: todo's id
 * @next: next todo
 *
 * Description: Structure for handling a todo
 */
typedef struct todo_s
{
	char		*title;
	char		*description;
	ssize_t		id;
	struct todo_s	*next;
} todo_t;

/**
 * struct todo_db_s - store the all the todos
 * @todos: pointer with the first todo
 * @last_id: last id
 *
 * Description: Structure for handling all the todos
 */
typedef struct todo_db_s
{
	todo_t		*todos;
	ssize_t		last_id;
} todo_db_t;

/**
 * struct http_msg_s - Store the parse http message
 * @client: client host
 * @method: http method requested
 * @path: path requested
 * @query: query requested
 * @version: http version
 * @headers: pointer with all the headers
 * @body: pointer with all the body
 * @status: request status
 * @todo_db: pointer with all the todos
 * @last_todo: last todo
 *
 * Description: Structure for handling the http message
 */
typedef struct http_msg_s
{
	char		*client;
	char		*method;
	char		*path;
	char		*query;
	char		*version;
	char		*headers;
	char		*body;
	int		status;
	todo_db_t	*todo_db;
	todo_t		*last_todo;
} http_msg_t;

void err_socket(char *msg);

void client_res(int socket_client, http_msg_t *req_data);

int post_method(http_msg_t *req_data);
int post_res(int status, http_msg_t *req_data, char *res);

int get_method(http_msg_t *req_data);
int get_res(int status, http_msg_t *req_data, char *res);

int check_req(http_msg_t *req_data);
void create_res(int status, http_msg_t *req_data, char *res);

todo_db_t *create_todo_db(void);
todo_t *create_todo(void);
todo_t *save_new_todo(char *title, char *description, http_msg_t *req_data);
void free_todo(todo_t *todo);

http_msg_t parse_req(char *req);
void parse_title_description(char **t, char **d, http_msg_t *req_data);
void parse_content_length(char **cl, http_msg_t *req_data);
void parse_query_id(char **i, http_msg_t *req_data);

int delete_res(int status, http_msg_t *req_data, char *res);
int delete_method(http_msg_t *req_data);

#endif
