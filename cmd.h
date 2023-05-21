#define A 256

int input_parsing(char user_input[], char *parse[])
{
    int i = 0;
    fgets(user_input, A, stdin);
    user_input[strlen(user_input) - 1] = '\0';

    parse[i] = strtok(user_input, " ");
    while (parse[i] != NULL)
    {
        // printf("%s\n",parse[i]);
        i++;
        parse[i] = strtok(NULL, " ");
    }

    // i++;
    return i;
}

void exec_simple_command(char *parse[])
{
    int i;
    pid_t child = fork();
    if (child < 0)
    {
        perror("Fork failed!\n");
        exit(-1);
    }
    else if (child == 0)
    {
        /* Child's code */
        // printf("hey");
        kill(getpid(), SIGSTOP);
        execvp(parse[0], parse);
        exit(-2);
    }
    else
    {
        /* Father's code */
        waitpid(child, NULL, WUNTRACED);
        kill(child, SIGCONT);
        wait(NULL);
    }
}

void commands_with_ptrs(char *parse[], int arguments, char user_input[])
{
    int i, index1, index2, index3;
    bool case1 = false;
    bool case2 = false;
    bool case3 = false;
    int fd1, fd2;

    for (i = 0; i < arguments; i++)
    {
        if (strcmp(parse[i], "<") == 0)
        {
            index1 = i + 1;
            case1 = true;
        }
        else if (strcmp(parse[i], ">") == 0)
        {
            index2 = i + 1;
            case2 = true;
        }
        else if (strcmp(parse[i], ">>") == 0)
        {
            index3 = i + 1;
            case3 = true;
        }
    }

    if (case1 && case2)
    {
        fd1 = open(parse[index1], O_RDONLY);
        fd2 = open(parse[index2], O_WRONLY | O_CREAT, S_IRWXU);
        int initial_stdin = dup(STDIN_FILENO);
        int initial_stdout = dup(STDOUT_FILENO);

        pid_t child = fork();
        if (child < 0)
        {
            perror("Fork failed!");
            exit(-3);
        }
        else if (child == 0)
        {
            /* Child's code */
            kill(getpid(), SIGSTOP);
            dup2(fd1, STDIN_FILENO);
            dup2(fd2, STDOUT_FILENO);
            char *args[index1];
            int j;
            for (j = 0; j < (index1 - 1); j++)
            {
                args[j] = strdup(parse[j]);
                // printf("%s\n", args[j]);
            }
            // j++;
            args[j] = NULL;
            execvp(args[0], args);
            perror("Exec failed!");
        }
        else
        {
            /*Father's code */
            waitpid(child, NULL, WUNTRACED);
            kill(child, SIGCONT);
            wait(NULL);
            dup2(STDOUT_FILENO, initial_stdout);
            dup2(STDIN_FILENO, initial_stdin);
            close(fd1);
            close(fd2);
        }
    }
    else if (case1 && case3)
    {
        fd1 = open(parse[index1], O_RDONLY);
        fd2 = open(parse[index3], O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
        int initial_stdin = dup(STDIN_FILENO);
        int initial_stdout = dup(STDOUT_FILENO);

        pid_t child = fork();
        if (child < 0)
        {
            perror("Fork failed");
            exit(-3);
        }
        else if (child == 0)
        {
            /* Child's code */
            kill(getpid(), SIGSTOP);
            dup2(fd1, STDIN_FILENO);
            dup2(fd2, STDOUT_FILENO);
            char *args[index1];
            int j;
            for (j = 0; j < (index1 - 1); j++)
            {
                args[j] = strdup(parse[j]);
                // printf("%s\n", args[j]);
            }
            // j++;
            args[j] = NULL;
            execvp(args[0], args);
            perror("Exec failed!");
        }
        else
        {
            /* Father's code */
            waitpid(child, NULL, WUNTRACED);
            kill(child, SIGCONT);
            wait(NULL);
            dup2(STDOUT_FILENO, initial_stdout);
            dup2(STDIN_FILENO, initial_stdin);
            close(fd1);
            close(fd2);
        }
    }
    else if (case1)
    {
        fd1 = open(parse[index1], O_RDONLY);
        int initial_stdin = dup(STDIN_FILENO);

        pid_t child = fork();
        if (child < 0)
        {
            perror("Fork failed");
            exit(-3);
        }
        else if (child == 0)
        {
            /* Child's code */
            kill(getpid(), SIGSTOP);
            dup2(fd1, STDIN_FILENO);
            char *args[index1];
            int j;
            for (j = 0; j < (index1 - 1); j++)
            {
                args[j] = strdup(parse[j]);
                // printf("%s\n", args[j]);
            }
            // j++;
            args[j] = NULL;
            // exit(0);
            execvp(args[0], args);
            perror("Exec failed!");
        }
        else
        {
            /* Father's code */
            waitpid(child, NULL, WUNTRACED);
            kill(child, SIGCONT);
            wait(NULL);
            dup2(STDIN_FILENO, initial_stdin);
            close(fd1);
        }
    }
    else if (case2)
    {
        fd1 = open(parse[index2], O_WRONLY | O_CREAT, S_IRWXU);
        int initial_stdout = dup(STDOUT_FILENO);

        pid_t child = fork();
        if (child < 0)
        {
            perror("Fork failed");
            exit(-3);
        }
        else if (child == 0)
        {
            /* Child's code */
            kill(getpid(), SIGSTOP);
            dup2(fd1, STDOUT_FILENO);
            char *args[index2];
            int j;
            for (j = 0; j < (index2 - 1); j++)
            {
                args[j] = strdup(parse[j]);
                // printf("%s\n", args[j]);
            }
            // j++;
            args[j] = NULL;
            // exit(0);
            execvp(args[0], args);
            perror("Exec failed!");
        }
        else
        {
            /* Father's code */
            waitpid(child, NULL, WUNTRACED);
            kill(child, SIGCONT);
            wait(NULL);
            dup2(STDOUT_FILENO, initial_stdout);
            close(fd1);
        }
    }
    else if (case3)
    {
        fd1 = open(parse[index3], O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
        int initial_stdout = dup(STDOUT_FILENO);

        pid_t child = fork();
        if (child < 0)
        {
            perror("Fork failed");
            exit(-3);
        }
        else if (child == 0)
        {
            /* Child's code */
            kill(getpid(), SIGSTOP);
            dup2(fd1, STDOUT_FILENO);
            char *args[index3];
            int j;
            for (j = 0; j < (index3 - 1); j++)
            {
                args[j] = strdup(parse[j]);
                // printf("%s\n", args[j]);
            }
            // j++;
            args[j] = NULL;
            execvp(args[0], args);
            perror("Exec failed!");
        }
        else
        {
            /* Father's code */
            waitpid(child, NULL, WUNTRACED);
            kill(child, SIGCONT);
            wait(NULL);
            dup2(STDIN_FILENO, initial_stdout);
            close(fd1);
        }
    }
    else
    {
        exec_simple_command(parse);
    }
}

void commands_with_pipes(char *parse[], int arguments, char user_input[])
{
    int i;
    int index1, index2;
    bool found = false;

    for (i = 0; i < arguments; i++)
    {
        if (strcmp(parse[i], "|") == 0)
        {
            index1 = i - 1;
            index2 = i + 1;
            found = true;
        }
    }

    if (found)
    {
        int initial_stdin = dup(STDIN_FILENO);
        int initial_stdout = dup(STDOUT_FILENO);

        int pipe_fd[2];
        pipe(pipe_fd);
        pid_t child_1, child_2;

        child_1 = fork();
        if (child_1 < 0)
        {
            perror("Fork failed");
            exit(-1);
        }
        else if (child_1 == 0)
        {
            /* #1 Child's code */
            kill(getpid(), SIGSTOP);
            dup2(pipe_fd[1], STDOUT_FILENO);
            char *args[A];
            int j;
            for (j = 0; j <= index1; j++)
            {
                args[j] = strdup(parse[j]);
                // printf("%s\n", args[j]);
            }
            // j++;
            args[j] = NULL;
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            execvp(args[0], args);
            perror("Exec in piped commands failed");
        }
        else
        {
            /* Father's code */
            waitpid(child_1, NULL, WUNTRACED);
            kill(child_1, SIGCONT);
            // Creating second child
            child_2 = fork();
            if (child_2 < 0)
            {
                perror("Fork failed");
            }
            else if (child_2 == 0)
            {
                /* #2 Child's code */
                kill(getpid(), SIGSTOP);
                dup2(pipe_fd[0], STDIN_FILENO);
                char *args[A];
                int j;
                int i = 0;
                for (j = index2; j < arguments; j++)
                {
                    args[i] = strdup(parse[j]);
                    i++;
                    // printf("%s\n", args[j]);
                }
                // j++;
                args[i] = NULL;
                close(pipe_fd[0]);
                close(pipe_fd[1]);
                execvp(args[0], args);
                perror("Exec in piped commands failed");
            }
            else
            {
                /* Father's code */
                waitpid(child_2, NULL, WUNTRACED);
                kill(child_2, SIGCONT);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
                wait(NULL);
                wait(NULL);
            }
        }
        dup2(STDIN_FILENO, initial_stdin);
        dup2(STDOUT_FILENO, initial_stdout);
    }
    else
    {
        commands_with_ptrs(parse, arguments, user_input);
    }
}