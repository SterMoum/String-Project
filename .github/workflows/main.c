#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

void ap(char *command, char ***words, char ***sentences, char ***paragraphs, int *wc, int *sc, int *pc);

void fw(char *command,char **words,int wc);

void fs(char *command,char **sentences,int sc);

void fp(char *command,char **paragraphs,int pc);

void owf(char **words,int wc);

void owl(char **words,int wc);

int main()
{
    char **words = NULL;
    char **sentences = NULL;
    char **paragraphs = NULL;
    int wc = 0, sc = 0, pc = 0;

    char *command = calloc(SIZE, sizeof(char));
    char run = 1;

    while (run)
    {
        fgets(command, SIZE, stdin);
        command[strcspn(command, "\n")] = '\0';
        fflush(stdin);

        if (command[0] == 'a' && command[1] == 'p' && command[2] == ':')
        {
            ap(command+3, &words, &sentences, &paragraphs, &wc, &sc, &pc);
        }

        else if (command[0] == 'f' && command[1]=='w' && command[2]==':'){
            fw(command+3,words,wc);
        }
        else if (command[0]=='f' && command[1]=='s' && command[2]==':'){
            fs(command+3,sentences,sc);
        }

        else if (command[0] == 'f' && command[1]=='p' && command[2]==':'){
            fp(command+3,paragraphs,pc);
        }
        else if(command[0]=='o' && command[1]=='w' && command[2]=='f'){
            owf(words,wc);
        }
        else if(command[0]=='o' && command[1]=='w' && command[2]=='l'){
            owl(words,wc);
        }

        else if (command[0]=='q' && command[1]=='t')
            run=0;
        strcpy(command, "");
    }
    free(paragraphs);
    free(sentences);
    free(words);
    return 0;
}

void ap(char *command, char ***words, char ***sentences, char ***paragraphs, int *wc, int *sc, int *pc)
{
    char local_s[4096];
    int lc = 0;
    (*paragraphs) = realloc((*paragraphs), (*pc+1)*sizeof(char*));
    (*paragraphs)[*pc] = calloc(SIZE,sizeof(char));

    strcpy((*paragraphs)[*pc], command);
    (*paragraphs)[*pc][strlen((*paragraphs)[*pc])] = '\0';
    (*pc)++;

    for (int i = 0; i < strlen(command); i++)
    {
        if (
            command[i] != '.' &&
            command[i] != '?' &&
            command[i] != '!' &&
            command[i] != ';' &&
            command[i] != ','
            )
        {
            local_s[lc++] = command[i];
        }
        else if (
                 i > 0 &&
                command[i-1] != '.' &&
                command[i-1] != '?' &&
                command[i-1] != '!' &&
                command[i-1] != ';' &&
                command[i-1] != ','
            )
        {
            (*sentences) = realloc((*sentences), (*sc+1)*sizeof(char*));
            (*sentences)[*sc] = malloc(SIZE*sizeof(char));
            local_s[lc] = '\0';



            strcpy((*sentences)[*sc],local_s);
            lc = 0;
            (*sc)++;

           //free(space_checker);
        }
    }

    strcpy(local_s, "");
    lc = 0;
    for (int i = 0; i < strlen(command); i++)
    {
        if (
            ((command[i]>='A' && command[i]<='Z') ||
            (command[i]>='a' && command[i]<='z')) &&
            command[i] != '.' &&
            command[i] != '?' &&
            command[i] != '!' &&
            command[i] != ';' &&
            command[i] != ' ' &&
            command[i] != ',' &&
            command[i] != '(' &&
            command[i] != ')' &&
            command[i] != '-'
            )
        {
            local_s[lc++] = command[i];
        }
        else if (
                 i > 0 &&
                 ((command[i-1]>='A' && command[i-1]<='Z') ||
                 (command[i-1]>='a' && command[i-1]<='z')) &&
                 command[i-1] != '.' &&
                 command[i-1] != '?' &&
                 command[i-1] != '!' &&
                 command[i-1] != ';' &&
                 command[i-1] != ' ' &&
                 command[i-1] != ',' &&
                 command[i-1] != '(' &&
                 command[i-1] != ')' &&
                 command[i-1] != '-'
            )
        {
            *words = realloc(*words, (*wc+1)*sizeof(char*));
            (*words)[*wc] = calloc(SIZE, sizeof(char));
            local_s[lc] = '\0';
            strcpy((*words)[*wc],local_s);
            lc = 0;
            (*wc)++;
        }
    }
}
char contains(char **arr,char *str,int size)
{
    for(int i=0;i<size;i++){
        if(!strcmp(arr[i],str))
            return 1;
    }
    return 0;
}
void fw(char *command,char **words,int wc)
{
    char **temp = calloc(wc, sizeof(char*));
    for (int i = 0; i < wc; i++) temp[i] = calloc(SIZE, sizeof(char));
    int k=0;
    for(int i=0; i<wc; i++)
    {
        if(strstr(words[i],command)!= NULL)
        {
            if(!contains(temp,words[i],wc)) {
                printf("%s\n",words[i]);
                strcpy(temp[k++],words[i]);
            }
        }
    }
    free(temp);
}
void fs(char *command,char **sentences,int sc)
{
    char **temp = calloc(sc, sizeof(char*));
    for (int i = 0; i < sc; i++) temp[i] = calloc(SIZE, sizeof(char));
    int k=0;
    for(int i=0; i<sc; i++)
    {
        if(strstr(sentences[i],command)!= NULL)
        {
            if(!contains(temp,sentences[i],sc)) {
                printf("%s\n",sentences[i]);
                strcpy(temp[k++],sentences[i]);
            }
        }
    }
}
void fp(char *command,char **paragraphs,int pc)
{

    char **temp = calloc(pc, sizeof(char*));
    for (int i = 0; i < pc; i++) temp[i] = calloc(SIZE, sizeof(char));
    int k=0;

    for(int i=0; i<pc; i++)
    {
        if(strstr(paragraphs[i],command)!= NULL)
        {
            if(!contains(temp,paragraphs[i],pc)) {
                paragraphs[i][strlen(paragraphs[i])-1]='\0';
                printf("%s\n",paragraphs[i]);
                strcpy(temp[k++],paragraphs[i]);
            }
        }
    }

}


void owf(char **words, int wc)
{
    char **words_once = calloc(wc, sizeof(char*));
    for (int i = 0; i < wc; i++) words_once[i] = calloc(SIZE, sizeof(char));
    int w_o_counter = 0;
    //CONTAINS
    for (int i = 0; i < wc; i++)
    {
        char flag = 1;
        for (int j = 0; j < wc; j++)
        {
            if (!strcmp(words[i], words_once[j]))
            {
                flag = 0;
            }
        }
        if (flag)
        {
            strcpy(words_once[w_o_counter++], words[i]);
        }
    }
    //END_CONTAINS
    int count[w_o_counter];
    for (int i = 0; i < w_o_counter; i++) count[i] = 0;

    for (int i = 0; i < w_o_counter; i++)
    {
        for (int j = 0; j < wc; j++)
        {
            if (!strcmp(words_once[i], words[j]))
                count[i]++;
        }
    }
    for (int i = 0; i < w_o_counter; i++)
    {
        for (int j = 0; j < w_o_counter - 1 - i; j++)
        {
            if (count[j] < count[j+1])
            {
                int temp = count[j];
                count[j] = count[j+1];
                count[j+1] = temp;

                char ctemp[512];
                strcpy(ctemp, words_once[j]);
                strcpy(words_once[j], words_once[j+1]);
                strcpy(words_once[j+1], ctemp);
            }
            else if (count[j] == count[j+1])
            {
                if (strcmp(words_once[j], words_once[j+1]) > 0)
                {
                    char ctemp[512];
                    strcpy(ctemp, words_once[j]);
                    strcpy(words_once[j], words_once[j+1]);
                    strcpy(words_once[j+1], ctemp);
                }
            }
        }
    }

    for (int i = 0; i < w_o_counter; i++)
    {
        printf("%s [%d]\n", words_once[i], count[i]);
    }
}


void owl(char **words, int wc)
{
    char **words_once = calloc(wc, sizeof(char*));
    for (int i = 0; i < wc; i++) words_once[i] = calloc(SIZE, sizeof(char));
    int w_o_counter = 0;
    //CONTAINS
    for (int i = 0; i < wc; i++)
    {
        char flag = 1;
        for (int j = 0; j < wc; j++)
        {
            if (!strcmp(words[i], words_once[j]))
            {
                flag = 0;
            }
        }
        if (flag)
        {
            strcpy(words_once[w_o_counter++], words[i]);
        }
    }
    //END_CONTAINS
    int count[w_o_counter];
    for (int i = 0; i < w_o_counter; i++) count[i] = 0;

    for (int i = 0; i < w_o_counter; i++)
    {
        count[i] = strlen(words_once[i]);
    }
    for (int i = 0; i < w_o_counter; i++)
    {
        for (int j = 0; j < w_o_counter - 1 - i; j++)
        {
            if (count[j] > count[j+1])
            {
                int temp = count[j];
                count[j] = count[j+1];
                count[j+1] = temp;

                char ctemp[512];
                strcpy(ctemp, words_once[j]);
                strcpy(words_once[j], words_once[j+1]);
                strcpy(words_once[j+1], ctemp);
            }
            else if (count[j] == count[j+1])
            {
                if (strcmp(words_once[j], words_once[j+1]) > 0)
                {
                    char ctemp[512];
                    strcpy(ctemp, words_once[j]);
                    strcpy(words_once[j], words_once[j+1]);
                    strcpy(words_once[j+1], ctemp);
                }
            }
        }
    }

    for (int i = 0; i < w_o_counter; i++)
    {
        printf("%s [%d]\n", words_once[i], count[i]);
    }
}

