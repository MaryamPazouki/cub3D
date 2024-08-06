#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>

typedef struct s_list
{
    char *content;
    struct s_list *next;
} t_list;



# define BUFFER_SIZE 10

void clear_list(t_list **lst, t_list *nl_node, char *buf)
{
    t_list *temp;

    while (*lst)
    {
        temp = (*lst)->next;
        free((*lst)->content);
        free(*lst);
        *lst = temp;
    }
    if (nl_node)
        free(nl_node);
    if (buf)
        free(buf);
}

char *get_next_line(int fd)
{
    static t_list *lst;
    char *line;
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;
    t_list *new_node;

    line = NULL;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        new_node = malloc(sizeof(t_list));
        if (!new_node)
        {
            clear_list(&lst, NULL, NULL);
            return (NULL);
        }
        new_node->content = strdup(buffer);
        new_node->next = lst;
        lst = new_node;
        // Append buffer to line
        if (!line)
            line = strdup(buffer);
        else
        {
            char *temp = line;
            line = malloc(strlen(line) + strlen(buffer) + 1);
            if (!line)
            {
                free(temp);
                clear_list(&lst, NULL, NULL);
                return (NULL);
            }
            strcpy(line, temp);
            strcat(line, buffer);
            free(temp);
        }
        // Check for newline character
        if (strchr(buffer, '\n'))
            break;
    }
    if (bytes_read == -1 || (bytes_read == 0 && !line))
    {
        clear_list(&lst, NULL, NULL);
        return (NULL);
    }
    return (line);
}

int main(void)
{
    int fd;
    char *line;
	// fd = open("example1.txt", O_RDONLY);
    // fd = open("example2.txt", O_RDONLY);
    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}