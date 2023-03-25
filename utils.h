/*
    metodos uteis
*/

int enable_logs = 1;

void logs(char c[]);
void err(char c[]);
void err(char c[]);

/// @brief Exibe um Log
/// @param c um texto a ser exibido
void
logs(char c[])
{
    if (enable_logs)
    {
        printf(" - logs: ");
        puts(c);
    }
}


/// @brief Saida especifica para erros
/// @param c Um texto de erro a ser exibido
void
err(char c[])
{
    printf(" - Error: ");
    puts(c);
}


/// @brief ativa os logs
void
logs_on()
{
    enable_logs = 1;
}


/// @brief desativa os logs
void
logs_off()
{
    enable_logs = 0;
}